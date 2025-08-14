
LOG_FILE=/tmp/ccc.out

function signal_handler {
  echo "Received signal: $1" | tee -a $LOG_FILE
  exit 1
}

trap 'signal_handler SIGHUP' SIGHUP
trap 'signal_handler SIGINT' SIGINT
trap 'signal_handler SIGTERM' SIGTERM

while :; do
    echo "run $$ $PPID $(date)" | tee -a $LOG_FILE
sleep 1
done
