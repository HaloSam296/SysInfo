#!/bin/bash


#I got a weird error I haven't encountered before. StackOverflow and research helped
#me understand the error a little, but not enough to fix it.
#Thus, ChatGPT:

# Set LC_NUMERIC to force decimal separator to period
export LC_NUMERIC=C


#Courtesy of mostly ChatGPT
getCPUTemp() {

    #check if lm-sensors is installed
    if ! command -v sensors &>/dev/null; then
        echo "lm-sensors not found, please run the installation option."
        exit 1 #stop the script
    fi

	# Get the CPU temperatures
	temperatures=$(sensors | awk '/Core/{gsub("[^0-9.]", "", $3); print $3}' | sed 's/+//')

	# Calculate the average temperature
	total=0
	count=0
	for temp in $temperatures; do
	    total=$(echo "$total + $temp" | bc)
	    count=$((count + 1))
	done

	average=$(echo "scale=2; $total / $count" | bc)

	echo $average

}

cpuTemp=$(getCPUTemp)

echo $cpuTemp
