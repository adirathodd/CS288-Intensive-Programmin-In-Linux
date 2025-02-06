#!/bin/bash

if [ -z "$1" ]; then
    echo "Not a valid directory path"
    exit 1
fi

traverse_directory() {
    local dir="$1"
    for x in "$dir"/*; {
        if [ -d "$x" ]; then
            traverse_directory "$x"
        elif [ -f "$x" ] && [[ "$x" = *.txt ]]; then
            grep -E -o "[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}" "$x" >> "unique_emails.txt"
        fi
    }
}

traverse_directory "$1"

sort -u -o unique_emails.txt unique_emails.txt

echo "Unique email addresses have been saved to unique_emails.txt"