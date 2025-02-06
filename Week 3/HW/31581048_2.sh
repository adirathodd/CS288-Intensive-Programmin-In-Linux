#!/bin/bash

if [ -z "$1" ]
then
    read -p "Please enter the name of a file or directory: " input
else
    input="$1"
fi

if [ -d "$input" ]
then
    if [ ! -r "$input" ] && [ ! -x "$input" ]
    then
        echo "Warning: You do not have read and execute permissions on the directory."
    else
        file_count=0
        dir_count=0
        echo "Files and subdirectories with their sizes:"
        
        for item in "$input"/*
        do
            if [ -f "$item" ]
            then
                file_count=$((file_count + 1))
            elif [ -d "$item" ]
            then
                dir_count=$((dir_count + 1))
            fi
            echo "$(du -sh "$item")"
        done

        echo "Number of files: $file_count"
        echo "Number of subdirectories: $dir_count"
    fi
elif [ -f "$input" ]
then
    if [ ! -r "$input" ]
    then
        echo "Warning: You do not have read permission on the file."
    else
        word_count=$(wc -w < "$input")
        line_count=$(wc -l < "$input")
        char_count=$(wc -m < "$input")
        echo "Word count: $word_count"
        echo "Line count: $line_count"
        echo "Character count: $char_count"

        if [ "$char_count" -gt 10000 ]
        then
            echo "Category: Text Heavy"
        elif [ "$char_count" -ge 1000 ]
        then
            echo "Category: Moderately Sized"
        else
            echo "Category: Light File"
        fi
    fi
else
    echo "Error: The file or directory does not exist."
fi