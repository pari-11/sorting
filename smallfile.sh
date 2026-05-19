#!/bin/bash

smallest=""

for file in *
do
    if [ -f "$file" ]
    then
        if [ -z "$smallest" ] || [ ${#file} -lt ${#smallest} ]
        then
            smallest="$file"
        fi
    fi
done

echo "Smallest file name is: $smallest"