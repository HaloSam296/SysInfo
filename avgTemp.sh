#!/bin/bash


#I got a weird error I haven't encountered before. STackOverflow and research helped
#me understand the error a little, but not enough to fix it.
#Thus, ChatGPT:

# Set LC_NUMERIC to force decimal separator to period
export LC_NUMERIC=C



checkStorageSpace() {

    FREE_SPACE=$(df -k . | awk 'NR==2{print $4}')

    # Check if the available space is less than 1GB (1,048,576 kilobytes)
    if [ $FREE_SPACE -lt 1048576 ]; then
        echo "Less than 1GB of free storage left."
        storageResponse=0
    else
        echo "At least 1GB of free storage available."
        storageResponse=1
    fi

    return $storageResponse
}

checkConnection() {

    ping -c 1 google.com >/dev/null 2>&1

    if [ $? -eq 0 ]; then
        # If the ping is successful, return 1 to indicate a connection
        pingResponse=1
    else
        # If the ping fails, return 0 to indicate no connection
        pingResponse=0
    fi
    
    return $pingResponse
}



getPackages() {

    #This if statement checks to make sure there is a network connection and
    #enough storage space. Then it checks if the needed package, lm-sensors, is
    #installed. If it isn't, it does so

    if storageResponse==1 && pingResponse==1; then

        #now for lm-sensors
        if ! command -v sensors >/dev/null 2>&1; then
            echo "lm-sensors is not installed. Your screen will be busy for several seconds"
            echo "\n\nInstalling now..."
            
            sleep 5
            
            sudo apt update
            sudo apt install lm-sensors -y
            
            #check to see if install is successful
            if ! command -v sensors &>/dev/null; then
       			echo "\n\nInstallation failed. Is your connection stable?"
    		else
    			echo "\n\nInstallation succeeded!"
    			sleep 4
    		fi
            
        else
            echo "lm-sensors is already installed."
        fi
        
    else
    	echo "There either is not an internet connection, or not enough storage"
    fi
}

#Courtesy of mostly ChatGPT
getCPUTemp() {

    if ! command -v sensors &>/dev/null; then
        echo "Installing lm-sensors"

        getPackages #Download and install lm-sensors
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

	#Told old code to get CPU Temp
	#will be deleted once the script is finished.

    #	if [ -f "/sys/class/thermal/thermal_zone0/temp" ]; then
    #        # Read the temperature in millidegrees Celsius
    #        temp=$(cat /sys/class/thermal/thermal_zone0/temp)
    # Convert millidegrees Celsius to degrees Celsius
    #        celsius=$(($temp / 1000))
    #celcius+="°C"
    #        echo $celsius
    #    else
    #        echo "Error: Temperature file not found." >&2
    #        exit 1
    #    fi

    #END FUNCTION IS RIGHT HERE
}

cpuTemp=$(getCPUTemp)

echo $cpuTemp
