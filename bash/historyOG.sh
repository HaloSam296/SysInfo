#!/bin/bash

#This is the program that can be user modified
#It's pretty simple, just gets the last x lines of history,
#with x being defined by the user


#Here's the super complicated and heavy bit of bash code:

tail -n 20 ~/.bash_history




#Trying out different methods:


#grep -e "$pattern" /home/*/.bash_history


#HISTFILE=$HOME/.bash_history
#history -r
#unset HISTFILE
#history