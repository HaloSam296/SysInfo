#!/bin/bash

checkConnection() {

	ping -c 1 google.com > /dev/null 2>&1

    if [ $? -eq 0 ]; then
        # If the ping is successful, return 1 to indicate a connection
        return 1
    else
        # If the ping fails, return 0 to indicate no connection
        return 0
    fi
}


checkStorageSpace() {
	FREE_SPACE=$(df -k . | awk 'NR==2{print $4}')
    
    # Check if the available space is less than 1GB (1,048,576 kilobytes)
    if [ $FREE_SPACE -lt 1048576 ]; then
        echo "Less than 1GB of free storage left."
        return 0
    else
        echo "At least 1GB of free storage available."
        return 1
    fi
}


getPackages() {

	#This if statement checks to make sure there is a network connection and 
	#enough storage space. Then it checks if the needed package, bc, is 
	#installed. If it isn't, it does so
	
	if checkConnection && checkStorageSpace; then
		
	    #now for bc
	    if ! command -v bc > /dev/null 2>&1; then
		    echo "bc is not installed. Installing now..."
		    sudo apt-get update
		    sudo apt-get install bc -y
		else
		    echo "bc is already installed."
		fi
		
	fi
}



#This is a mix of my own work and ChatGPT's
#But mostly ChatGPT's. It did a better job than I

#UPDATE: My code was buggy. ChatGPT replaced it due to time constraints :(
#I dislike how much I'm relying on ChatGPT for this project. A good portion is my work,
#but that portion is diminishing. I'm not learning as much as in my early programs.
#To be fair, I also just hate programming lol. Scripting it cool though, bash4life

getProcerUtil() {

	getPackages
	
	# Read total CPU usage from /proc/stat
    cpu_stat=(`grep '^cpu ' /proc/stat`)

    # Get total CPU time spent in user mode, system mode, and idle time
    user=${cpu_stat[1]}
    nice=${cpu_stat[2]}
    system=${cpu_stat[3]}
    idle=${cpu_stat[4]}
    iowait=${cpu_stat[5]}
    irq=${cpu_stat[6]}
    softirq=${cpu_stat[7]}
    steal=${cpu_stat[8]}
    guest=${cpu_stat[9]}
    guest_nice=${cpu_stat[10]}

    # Calculate total CPU time
    total_cpu_time=$((user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice))

    # Calculate idle CPU time
    idle_cpu_time=$idle

    # Calculate non-idle CPU time
    non_idle_cpu_time=$((total_cpu_time - idle_cpu_time))

    # Calculate total CPU utilization percentage
    total_utilization=$(echo "scale=2; ($non_idle_cpu_time / $total_cpu_time) * 100" | bc -l)
    
    echo $total_utilization
}

getProcerUtil

