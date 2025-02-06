#!/bin/bash
traverse() {
echo $1
if [ ! -d "$1" ]; then
    return
fi
if [ `ls "$1" | wc -l` -eq 0 ]; then
   return
fi
size=$(du -s "$1" | cut -f 1)

if [ $size -eq 0 ]; then
    echo "$1"
fi

local entries=("$1"/*)
local entry
for entry in "${entries[@]}"
do
    traverse "$entry"
done
}

traverse "$1"