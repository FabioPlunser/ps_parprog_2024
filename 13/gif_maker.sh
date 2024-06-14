#!/bin/bash
USERS="$@"

while true; do
    sleep 1
    job_exists=0
    for u in $USERS 
    do
        squeue | grep -q "$u"
        if [ $? -eq 0 ]; then
            job_exists=1
            break
        fi
    done
    if [ $job_exists -eq 0 ]; then
        break
    fi
done

sleep 1
make gif