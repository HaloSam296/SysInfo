Name: SysInfo
Author: Samuel Brucker
Version: 2
Date: 4/17/24 


Description:
SysInfo is a small command line C utility to retrieve system information. Currently, it can grab:
	-Date and Time
	-Hostname
	-Release Information
	-Kernel Version
	-Ram Information
	-CPU Core Count
	-CPU Temperature
	-CPU Approximate Utilization
These options are chosen through a menu.


Requirements:
	-GCC or another C compiler
	-Debian
		~~ This might work on other distributions or operating systems, but do not expect full functionality. This program is not intended to be ran on anything but Debian

Usage:
1. Using the command line, go to the directory (folder) where the program is stored.
	1a. You can do this using the `cd` command and pressing ENTER: `cd [path to the program]`

3. Make the Bash files executable
	3a. Run "sudo chmod +x [Bash File Name]" for each of the three Bash files
	4a. You will to type in your sudo password initially. The characters are hidden from you,
	    but they will still be inputted.

2. Compile the C program
	2a. If you are using GCC, this is done by: `gcc main.c -o run`
	2b. You will see warnings output when this happens, don't panic. The program will still function and compile.

3. Run the program using `./[file name]`
	3a. If you used the example GCC command in step 2a, the command would be: `./run`


4. Select the desired option in the program's menu



