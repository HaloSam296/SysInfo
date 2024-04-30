Name: SysInfo
Author: Samuel Brucker
Version: 2.4
Date: 4/30/24 

GitHub: https://github.com/HaloSam296/SysInfo


Description:
SysInfo is a small command line C utility to retrieve system information. Currently, it can grab:
	-Date and Time
	-Hostname
	-Release Information
	-Kernel Version
	-Ram Information
	-Show Terminal History (modifies a script)
	-Confirm Script Modification
	-CPU Core Count
	-CPU Temperature (Not compatible with VMs)
	-CPU Utilization
These options are chosen through a menu.


Requirements:
	-GCC or another C compiler
	-Debian
		~~ This might work on other distributions or operating systems, but do not expect full functionality. This program is not intended to be ran on anything but Debian
	-bc and lm-sensors
		~~ These packages are used by Options 7 and 8: CPU Temperature and CPU Utilization.
		~~ If they are not already installed on the machine, the program will install them if there is 1GB of free space, and an Internet connection

Usage:
1. Using the command line, go to the directory (folder) where the program is stored.
	1a. You can do this using the `cd` command and pressing ENTER: `cd [path to the program]`

2. Compile the C program
	2a. If you are using GCC, this is done by: `gcc main.c -o run`
	2b. You will see warnings output when this happens, don't panic. The program will still function and compile.

3. Run the program using `./[file name]`
	3a. If you used the example GCC command in step 2a, the command would be: `./run`


4. Select the desired option in the program's menu



