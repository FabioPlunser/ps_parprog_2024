#!/bin/bash
USER=$(id -un)

while true; do
    sleep 1
    squeue | grep -q "$USER"
    if [ $? -ne 0 ]; then
        break
    fi
done

sleep 1
make gif