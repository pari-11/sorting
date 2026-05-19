#!/bin/bash

# Check if input file is given
if [ $# -eq 0 ]
then
    echo "Usage: ./script.sh inputfile"
    exit 1
fi

# Clear old contents if files already exist
> even
> odd

# Read numbers from file
for num in $(cat "$1")
do
    if [ $((num % 2)) -eq 0 ]
    then
        echo "$num" >> even
    else
        echo "$num" >> odd
    fi
done

echo "Even numbers stored in file: even"
echo "Odd numbers stored in file: odd"