#!/bin/bash

#1. 
a=`grep -E -o -i ".*[Aa].*a.*a.*" dictionary.txt | wc -l`
echo "1:"
echo "${a}"

#2.
e=`grep -i -o -E "^[^eE]*[eE][^eE]+[eE][^eE]+[eE][^eE]*$" dictionary.txt | wc -l`
echo "2:"
echo "${e}"

#3.
echo "3:"
grep -o -E ".*[Ee]e.*" dictionary.txt | rev | cut -c 1-4 | rev | sort | uniq -c | sort -nr | head -n 3