#!/bin/bash

mapfile -t lines < dates.txt
for line in "${lines[@]}"; do
    echo "$line"
done