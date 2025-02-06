#!/bin/bash

# $1 is starting directory name
# $2 is the target file name

traverse() {
    echo "Traversing $1"
    if [ ! -d "$1" ]
    then
        echo "Not a directory"
        return
    fi
    if [ `ls "$1" | wc -l` -eq 0 ]
    then
        echo "Empty directory"
        return
    fi

    entries=(ls "$1")
    for entry in "${entries[@]}"
    do
        echo "$entry"
        traverse "$entry"
    done
}

traverse "$1"