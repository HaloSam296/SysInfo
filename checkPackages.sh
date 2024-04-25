#!/bin/bash



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
        #Return 1 if a success
        pingResponse=1
    else
        #Return 0 if a failure
        pingResponse=0
    fi
    
    return $pingResponse
}




#The main function
getPackages() {

    checkStorageSpace
    checkConnection

    #This if statement checks to make sure there is a network connection and
    #enough storage space. Then it checks if the needed packages, lm-sensors and bc, are installed. 
    #If they aren't, it tries to install them.

    if [ "$storageResponse" = 1 ] && [ "$pingResponse" = 1 ]; then
        # lm-sensors
        if ! command -v sensors >/dev/null 2>&1; then
            sudo apt update
            sudo apt install lm-sensors -y
            # Check if the installation is successful
            if ! command -v sensors &>/dev/null; then
                echo -e "\n\nInstallation of lm-sensors failed. Is your connection stable?"
            else
                echo -e "\n\nInstallation of lm-sensors succeeded!"
                sleep 4
            fi
        else
            echo "lm-sensors is already installed."
        fi

        # bc
        if ! command -v bc >/dev/null 2>&1; then
            sudo apt update
            sudo apt install bc -y
            # Check if the installation is successful
            if ! command -v bc &>/dev/null; then
                echo -e "\n\nInstallation of bc failed. Is your connection stable?"
            else
                echo -e "\n\nInstallation of bc succeeded!"
                sleep 4
            fi
        else
            echo "bc is already installed."
        fi
    else
        echo "Installations failed. Is there an Internet connection and at least 1GB of storage?"
    fi
}

sleep 6
#Run the function
getPackages