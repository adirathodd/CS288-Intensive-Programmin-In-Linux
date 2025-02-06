#!/bin/bash

echo "Welcome to the Rock, Paper, Scissors game! You will be playing against the computer."
echo ""
echo "HERE ARE THE RULES:"
echo "Rock beats Scissors by crushing them"
echo "Scissors beats Paper by cutting it"
echo "Paper beats Rock by covering it"
echo ""

winner=False

until [ $winner == True ]
do

    echo "Please enter your choice (rock, paper, or scissors):"
    read p1_choice
    echo ""

    choices=("rock" "paper" "scissors")
    p2_choice=${choices[$RANDOM % 3]}

    echo "Player 2 chose $p2_choice"
    echo ""
    
    if [ $p1_choice == $p2_choice ]
    then
        echo "It's a tie!"
    elif [ $p1_choice == "rock" ] && [ $p2_choice == "scissors" ]
    then
        echo "Player 1 wins!"
        winner=True
    elif [ $p1_choice == "scissors" ] && [ $p2_choice == "paper" ]
    then
        echo "Player 1 wins!"
        winner=True
    elif [ $p1_choice == "paper" ] && [ $p2_choice == "rock" ]
    then
        echo "Player 1 wins!"
        winner=True
    else
        echo "Player 2 wins!"
        winner=True
    fi
done