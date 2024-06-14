#!/bin/bash
USER=$(id -un)
MAKE_COMMAND="$@"

while true; do
    sleep 1
    squeue | grep -q "$USER"
    if [ $? -ne 0 ]; then
        break
    fi
done

sleep 1
make $MAKE_COMMAND