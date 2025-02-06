#!/bin/bash

while read -r line
do
    city=`cut -d "," -f 3 <<< "$line"`
    if [[ "$city" =~ [A-Z][a-z]*[[:space:]-][A-Z][a-z]* ]]
    then
        date=`echo "$line" | grep -E -o "[[:digit:]]{4}"`
        date=$((2024-$date))
        name=`cut -d "," -f 1 <<< "$line"`
        echo "$name: $date" >> ages.txt
    fi
done < $1

sort -t ":" -k2nr -k1d ages.txt
rm ages.txt