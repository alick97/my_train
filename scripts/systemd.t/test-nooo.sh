#!/bin/bash
echo $$ $PPID
nohup bash /home/alick/workspace/test/systemd.t/t.sh >/dev/null &
echo "done $(date)"


