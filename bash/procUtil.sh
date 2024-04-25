#!/bin/bash

#This is a mix of my own work and ChatGPT's

getProcerUtil() {
	
    #check if bc is installed
    #it comes native on Ubuntu desktop, so there shouldn't be any issues
    if ! command -v bc &>/dev/null; then
        echo "bc not found, please run the installation option."
        exit 1 #stop the script
    fi


	# Read total CPU usage from /proc/stat
    cpu_stat=($(grep '^cpu ' /proc/stat))

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
    
    echo "$total_utilization"
}


#run the function

procUtil=$(getProcerUtil)

echo $procUtil