#!/bin/bash

display_file() {
    local file=$1
    local start_line=1
    local end_line=10
    local total_lines=$(wc -l < "$file")

    while [ $start_line -le $total_lines ]
    do
        sed -n "${start_line},${end_line}p" "$file"
        start_line=$((end_line + 1))
        end_line=$((end_line + 10))
        if [ $start_line -le $total_lines ]
        then
            read -p "Do you want to display more? (yes/no): " choice
            if [ "$choice" == "no" ]
            then
                echo ""
                break
            else
                continue
            fi
        fi
    done
}

search_recent_files() {
    local dir=$1
    local recent_files=()
    local current_time=$(date +%s)

    for file in *
    do
        if [ -f "$file" ]
        then
            local file_mod_time=$(stat -f %m "$file")
            local time_diff=$((current_time - file_mod_time))
            if [ $time_diff -le 86400 ]
            then
                recent_files+=("$file")
            fi
        fi
    done

    echo "${recent_files[@]}"
}


while true
do
    read -p "Enter a directory name: " dir_name

    if [ ! -d "$dir_name" ]
    then
        read -p "Directory does not exist. Do you want to create it? (yes/no): " create_choice
        if [ "$create_choice" == "yes" ]
        then
            mkdir -p "$dir_name"
        elif [ "$create_choice" == "no" ]
        then
            echo "Exiting..."
            exit 1
        else
            echo "Invalid choice. Try again."
            continue
        fi
    fi

    cd "$dir_name" || exit 1

    while true
    do
        echo "Contents of $dir_name:"
        echo ""
        files=$(ls -1)
        count=1
        while IFS= read -r file
        do
            echo "$count. $file"
            count=$((count + 1))
        done <<< "$files"
        # ls -1
        echo ""
        read -p "Select a file or subdirectory (or type 'exit' to quit): " selection

        if [ "$selection" == "exit" ]
        then
            exit 0
        elif [ "$selection" -ge 1 ] && [ "$selection" -le $count ]
        then
            selection=$(echo "$files" | sed -n "${selection}p")

            if [ -f "$selection" ]
            then
                display_file "$selection"
            elif [ -d "$selection" ]
            then
                cd "$selection" || continue
                recent_files=$(search_recent_files ".")
                if [ -z "$recent_files" ]
                then
                    echo "No files modified in the last 24 hours."
                else
                    echo "Files modified in the last 24 hours:"
                    select recent_file in $recent_files
                    do
                        if [ -n "$recent_file" ]
                        then
                            display_file "$recent_file"
                            break
                        fi
                    done
                fi
                cd ..
            else
                echo "Invalid selection. Please try again."
            fi
        else
            echo "Invalid selection. Please try again."
        fi
    done
done