#!/bin/bash

scanf=0
printf=0
lines=0
total=0

while read -r line; do
    lines=$((lines+1))
    if [ `grep -o -E "scanf" <<< "$line"` ]; then
        echo "$line" >> scanf_log.txt
        scanf=$((scanf + 1))
        total=$((total + 1))
    elif [ `grep -o -E "printf" <<< "$line"` ]; then
        echo "$line" >> printf_log.txt
        printf=$((printf + 1))
        total=$((total + 1))
    fi
done < "$1"

total_percentage=$(echo "scale=2; $total * 100 / $lines" | bc)
scanf_percentage=$(echo "scale=2; $scanf * 100 / $lines" | bc)
printf_percentage=$(echo "scale=2; $printf * 100 / $lines" | bc)


echo "Total lines: $lines"
echo "Total Scanf & Printf Percentage: $total_percentage%"
echo
echo "Total scanf: $scanf"
echo "Scanf Percentage: $scanf_percentage%"
echo
echo "Total printf: $printf"
echo "Printf Percentage: $printf_percentage%"