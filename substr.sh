#!/bin/bash

str=$1
sub=$2

count=$(echo "$str" | grep -o "$sub" | wc -l)

if [ $count -gt 0 ]
then
    echo "Substring found"
    echo "Occurrence count: $count"
else
    echo "Substring not found"
fi