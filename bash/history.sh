#!/bin/bash

#This is the program that can be user modified
#It's pretty simple, just gets the last x lines of history,
#with x being defined by the user


#Here's the super complicated and heavy bit of bash code:

#This sleep is here because I have a text line in the C program that says the new script was successfully created
#I want to give them a few seconds to read it
sleep 3

history | tail -n 5

#I know, terrifyingly complicated