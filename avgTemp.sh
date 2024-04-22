#!/bin/bash

#Courtesy of mostly ChatGPT
getCPUTemp() {

	if [ -f "/sys/class/thermal/thermal_zone0/temp" ]; then
        # Read the temperature in millidegrees Celsius
        temp=$(cat /sys/class/thermal/thermal_zone0/temp)

        # Convert millidegrees Celsius to degrees Celsius
        celsius=$(($temp / 1000))

		#celcius+="°C"
        echo $celsius
    else
        echo "Error: Temperature file not found." >&2
        exit 1
    fi
}

cpuTemp=$(getCPUTemp)

echo $cpuTemp

