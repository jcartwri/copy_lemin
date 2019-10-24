#!/bin/bash
for (( i=1; i <= 10; i++ ))
do
    rm -rf big$i
    echo "$(./generator --big-superposition)" > big
    number1=$(cat big | grep -m 1 "#H" | cut -d' ' -f8)
    text=$(./lem-in < big)
    number3=$(echo "$text" | grep L | wc -l)

    echo задание: $number1 - наш: $number3

    delta=$(( $number1-1 ))
    if [ $number3 -lt $delta ]
    then
        echo "copy big$i"
        cp big big$i
    fi

    if [ $number1 -lt $number3 ]
    then
        echo "copy big$i"
        cp big big$i
    fi

done