#!/bin/bash

ranks=(2 3 4 5 6 7 8 9 10 jack queen king ace)
suits=(clubs diamonds hearts spades)

num=$RANDOM

rank_index=$((num % 13))
suit_index=$((num % 4))

echo "${ranks[$rank_index]} of ${suits[$suit_index]}"