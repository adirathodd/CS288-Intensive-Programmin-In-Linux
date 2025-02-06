#!/bin/bash

echo "Please enter file name:"
read filename

if [ -f "$filename" ]; then
    cp "$filename" "$filename.bak"
    tail -n 10 "$filename"
    exit 0
elif [ -z "$filename" ]; then
    echo "No input provided. Please enter something next time."
    exit 1
else
    echo "File does not exist."
fi