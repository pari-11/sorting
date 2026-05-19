#!/bin/bash

echo "1. Decimal to Binary"
echo "2. Binary to Decimal"
echo "Enter your choice:"
read ch

if [ $ch -eq 1 ]
then
    echo "Enter decimal number:"
    read num

    bin=""

    while [ $num -gt 0 ]
    do
        rem=$((num % 2))
        bin="$rem$bin"
        num=$((num / 2))
    done

    echo "Binary number is: $bin"

elif [ $ch -eq 2 ]
then
    echo "Enter binary number:"
    read bin

    dec=0
    base=1

    while [ $bin -gt 0 ]
    do
        digit=$((bin % 10))

        dec=$((dec + digit * base))

        base=$((base * 2))

        bin=$((bin / 10))
    done

    echo "Decimal number is: $dec"

else
    echo "Invalid choice"
fi