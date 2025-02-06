#!/bin/bash

while read -r line; do
    count=$(grep -o -E "at" <<< "$line" | wc -l)
    sed -n "s/at/@/${count}p" <<< "$line"
done < $1