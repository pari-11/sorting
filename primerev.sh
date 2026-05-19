#!/bin/bash

echo "Enter a number:"
read num

temp=$num
rev=0
flag=0

# Reverse number
while [ $temp -gt 0 ]
do
    digit=$((temp % 10))
    rev=$((rev * 10 + digit))
    temp=$((temp / 10))
done

echo "Reverse of number is: $rev"

# Prime check
for ((i=2; i<num; i++))
do
    if [ $((num % i)) -eq 0 ]
    then
        flag=1
        break
    fi
done

if [ $num -le 1 ]
then
    echo "$num is not prime"

elif [ $flag -eq 0 ]
then
    echo "$num is prime"

else
    echo "$num is not prime"
fi