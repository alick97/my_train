#!/bin/bash

# Get the parent process ID (PID)
parent_pid="$1"

# Check if a PID is provided
if [ -z "$parent_pid" ]; then
  echo "Usage: $0 <parent_pid>"
  exit 1
fi

# Function to get RSS and SHR for a given PID.  Improved error handling.
get_memory_info() {
  local pid="$1"
  if [ ! -d "/proc/$pid" ]; then
    return 1 # PID doesn't exist
  fi
  local rss=$(cat /proc/"$pid"/status | grep VmRSS | awk '{print $2}' || echo 0)
  local shr=$(cat /proc/"$pid"/status | grep VmShared | awk '{print $2}' || echo 0)
  echo "$rss $shr"
}

# Initialize total memory usage
total_rss_kb=0

# Recursive function to find all child processes and their memory usage
find_all_descendants() {
  local pid="$1"
  local children=$(pgrep -P "$pid")

  # Get memory info for the current process
  local memory_info=$(get_memory_info "$pid")
  if [ $? -ne 0 ]; then
    return 0 # Ignore if PID is invalid
  fi
  local rss_kb=$(echo "$memory_info" | awk '{print $1}')
  local shr_kb=$(echo "$memory_info" | awk '{print $2}')
  total_rss_kb=$((total_rss_kb + rss_kb - shr_kb))

  # Recursively call for each child
  for child_pid in $children; do
    find_all_descendants "$child_pid"
  done
}

# Find and process all descendants
find_all_descendants "$parent_pid"

# Calculate total memory usage in MB
total_rss_mb=$(echo "scale=2; $total_rss_kb / 1024" | bc)

# Print the result
echo "Total memory usage for process $parent_pid and all its descendants: $total_rss_mb MB"

