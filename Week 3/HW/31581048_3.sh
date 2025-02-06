#!/bin/bash

if [ "$#" -lt 3 ]
then
    echo "Error: At least three filenames must be provided."
    exit 1
fi
timestamp=$(date +"%Y%m%d")

backup_dir="backup_$timestamp"
mkdir -p "$backup_dir"

log_file="$backup_dir/backup_log.txt"
touch "$log_file"

for file in "$@"
do
    if [ -f "$file" ]
    then
        cp "$file" "$backup_dir"
        base_name=$(basename "$file")
        new_name="${base_name}_$timestamp"
        mv "$backup_dir/$base_name" "$backup_dir/$new_name"
        echo "$file -> $new_name" >> "$log_file"
    else
        echo "Warning: File '$file' does not exist. Skipping."
    fi
done

echo "Backup process completed. Backup directory: $backup_dir"