#!/bin/bash

echo "Enter student name:"
read name

echo "Enter marks of 3 subjects:"
read m1 m2 m3

total=$((m1 + m2 + m3))

percentage=$((total / 3))

echo "Name: $name"
echo "Total Marks: $total"
echo "Percentage: $percentage%"

if [ $percentage -ge 60 ]
then
    echo "First Class"

elif [ $percentage -ge 50 ]
then
    echo "Second Class"

elif [ $percentage -ge 40 ]
then
    echo "Pass Class"

else
    echo "Fail"
fi