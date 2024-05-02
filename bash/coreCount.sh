#!/bin/bash

getCoreCount() {
	#get core count
	coreCount=$(lscpu | grep -i 'core(s) per socket' | awk '{print $4}')
	
	#export core count
	echo "$coreCount"
}

getCoreCount


