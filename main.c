/*
Version: 2.4
Author: Samuel Brucker

Sources:

Phind was used perform efficient research and for debugging, but it was NOT used for creating code. i.e., it helped me research a particular function or it helped me tweak a line to fix an ellusive error.

ChatGPT was used extensively for generating code. As can be discerned by many of the comments, it has touched a ton of the code for this project. While it smoothed over many gaps, the design and a ton fo the code is my own. 

Hostname: https://stackoverflow.com/questions/5190553/linux-c-get-server-hostname
gethostname() man page: https://man7.org/linux/man-pages/man2/sethostname.2.html

System Release: https://www.geeksforgeeks.org/getting-system-and-process-information-using-c-programming-and-shell-in-linux/

Get the System RAM: https://stackoverflow.com/questions/349889/how-do-you-determine-the-amount-of-linux-system-ram-in-c

Morgan Sander's program was reviewed and copied from for better input validation

The notes for the C Essentials were also reviewed, particularly for File and I/O functionality.
*/

#include <stdio.h>
#include <stdlib.h> //for exit() and maybe some other stuff
#include <sys/utsname.h> //for system and kernel information
#include <string.h> //for system memory
#include <unistd.h> //for sysconf
#include <sys/sysinfo.h> //for sysinfo
#include <time.h> //for the time
#include <limits.h> //for hostname
#include <stdbool.h> //for boolean vars. It's weird I need to import this
#include <errno.h> //for a little bit of error handling



//glory to ChatGPT and its guiding, sanity-saving light!
#define MAX_TIME_LENGTH 50 //This sets the length of the string for the time function
#define NUM_ITERATIONS 10

//Functions need to be defined before they are used in main(), for C. Because the function's code is below,
//it isn't considered defined without this line
void clearBuffer();
char* getCurrentTime();
char* getSysInfo();


float getCPUUtilization() {
    FILE *fp = popen("./bash/procUtil.sh", "r");
    if (fp == NULL) {
        perror("Error executing bash script");
        return -1; // Return -1 to indicate failure
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        float utilization = atof(buffer);
        pclose(fp);
        return utilization;
    }

    pclose(fp);
    return -1; // Return -1 to indicate failure
}


int main() {
	int choice;

	//This input validation is heavily inspired by Morgan's program
	bool loop = true;

	//Just making sure all the bash scripts are executable. Since there are several and they are in their own folder, I could see someone missing them
	system("chmod +x bash/*");



	printf("Hello! Third-party packages are needed to use Options 7 and 8. These packages are bc and lm-sensors.\n");
	printf("To check if these are installed, please run Option 9. If they are not installed, this option will do so automatically.\n");
	printf("Please ensure that you have at least 1GB of storage and an Internet connection. Thank you!\n\n\n");

	while (loop == true) {
		//Menu printing time yay
		printf("------------------------------------\n");
		printf("System Information Options\n");

		//Misc options
		printf("\nMiscellaneous:\n");
		printf("    1. Time and Date\n");
		printf("    2. Hostname\n");
		printf("    3. System Release Information\n");
		printf("    4. Kernel Version\n");
		printf("    5. Total System Memory\n");
		printf("    6. Show Terminal History (modifies a script)\n");
		printf("    7. Confirm Script Modification\n");

		//cpu options
		printf("\nCPU Options:\n");
		printf("    8. CPU Core Count\n");
		printf("    9. Average CPU Temperature (Incompatible with VMs)\n");
		printf("    10. CPU Utilization\n");


		//SysInfo Options
		printf("\nSysInfo Options:\n");
		printf("    11. Check for Packages\n");
		printf("    12. Exit\n");
		printf("------------------------------------");
		printf("\nEnter your choice: ");

		//input validations
		if (scanf("%d", &choice) != 1) {
			printf("Please enter a number between 1 and 12\n");
			clearBuffer();
			continue;
		}

		printf("\n\n");

		switch (choice) {
			case 1:
				//get the time
			    char  *curTime = getCurrentTime();
			    printf("Current time: %s", curTime);
			    free(curTime);	//This clears the curTime var from memory
				printf("\n\n");
				break;
				
			case 2:
				//Get hostname
				char *hostname = getSysInfo(2);
				printf("Hostname: %s", hostname);
				free(hostname);
				printf("\n\n");
				break;
				
			case 3:
				//Sysem Release
				char *sysRelease = getSysInfo(3);
				printf("System Release: %s", sysRelease);
				free(sysRelease);
				printf("\n\n");
				break;
				
			case 4:
				//Kernel Version
				char *kernVersion = getSysInfo(4);
				printf("Kernel Version: %s", kernVersion);
				free(kernVersion);
				printf("\n\n");
				break;

			case 5:
				//RAM Information
				char *RAMInfo = getSysInfo(5);
				printf("RAM Information: %s", RAMInfo);
				free(RAMInfo);
				printf("\n\n");
				break;

			case 6:
				//Show terminal history based on user input
				getSysInfo(10);
				break;
				


			case 7:
				//WIP
				char *fileDifCheck = getSysInfo(11);

				if (fileDifCheck == "0") {
					printf("There have been no modifications.");
				} else if (fileDifCheck == "1") {
					printf("The History script was successfully modified.");
				} else {
					printf("There was an error while checking for modifications. Have you ran Option 6 (Show Terminal History)?");
				}
				break;


				
			case 8:
				//CPU Core Count
				char *CPUInfo = getSysInfo(6);
				printf("CPU Core Count: %s", CPUInfo);
				free(CPUInfo);
				printf("\n\n");
				break;

			case 9:
				//CPU Temp
				char *CPUTemp = getSysInfo(7);
				printf("CPU Average Temperature: %s", CPUTemp);
				free(CPUTemp);
				printf("\n\n");
				break;

			case 10:
				//CPU Utilization
				char *procUtil = getSysInfo(8);
				free(procUtil);
				printf("\n\n");
				break;


			case 11:
				//Check for packages
				getSysInfo(9);
				break;


			case 12:
				//Exit case
				printf("Exiting, goodbye!\n");
				exit(0);

			default:
				printf("Invalid value. Please choose a number between 1 and 12.\n");
				break;
		}
	} 
	return 0;
}


//This is directly copied and pasted from Morgan's program
void clearBuffer() { // Ensures there was not more than 1 character inputted
    int c; // Reads that there was a character inputted
    while ((c = getchar()) != '\n' && c != EOF); // Reads what was inputted and checks to make sure it was not a new line or end of file character
}


/*This function gets the current system time and date
works and that I can't touch it anymore. Even moving my cursor over it is scary.
I don't know how all of it works, dates are always wonky in programming. I just know  it

Also, ChatGPT wrote pretty much all of it, with small tweaks from me
*/

char* getCurrentTime() {
    time_t current_time;
    struct tm *local_time; //To-Do: learn what a struct is
    char *time_str;

    //Memory allocation for the string. This doesn't look annoying at all
    time_str = (char*)malloc(MAX_TIME_LENGTH * sizeof(char));
    if (time_str == NULL) {
        perror("Memory allocation failed");
        //This exit/error line looks handy
        exit(EXIT_FAILURE);
    }

    //Call and store the current time
    time(&current_time);
    local_time = localtime(&current_time);

    //Format the string
    strftime(time_str, MAX_TIME_LENGTH, "%Y-%m-%d %H:%M:%S", local_time);

    return time_str;
    //EZ, Second simplest program I've totally ever written.
}


//Straight from geekforgeeks woo!
//Update: This is no longer straight from geekforgeeks. It's heavily edited
//Worth mentioning is that I added the switch statement and edited this quite a bit
char* getSysInfo(int info) {
	struct utsname sysInfo;

	if (uname(&sysInfo) != 0) {
	        perror("uname");
    	}


	switch (info) {
		case 1:
			return strdup(sysInfo.sysname); //Kernel Name

		case 2:
			return strdup(sysInfo.nodename); //Host Name

		case 3:
			return strdup(sysInfo.release); //Kernal release

		case 4:
			return strdup(sysInfo.version); //Kernel Version

		case 5:
			//This monstrosity gets the system memory. Thank you SO and ChatGPT
			{
			FILE *meminfo = fopen("/proc/meminfo", "r");
		            if (meminfo == NULL) {
                		perror("Error opening /proc/meminfo");
		                return NULL;
		            }
		            char line[128];
		            while (fgets(line, 128, meminfo) != NULL) {
		                if (strncmp(line, "MemTotal:", 9) == 0) {
		                    char *memTotal = strdup(line + 9);
		                    fclose(meminfo);

		                    //convert memory size to GB, courtesy of ChatGPT

		                    return memTotal;
		                }
		            }
		            fclose(meminfo);
		            break;


			}

		case 6:
				//This section didn't work and I had a lot of trouble with it,
				//buuuut I can do it much more easily in bash
				//ChatGPT was very much here
				FILE *fp; //set fp as a file
				char path[1035];
			    fp = popen("./bash/coreCount.sh","r"); //opens the bash script with read perms

			    //if the read fails, print this error
			    if (fp == NULL) {
			        printf("Failed to run bash script \n");
			        return NULL; // Return NULL to indicate failure
			    }

			    //I need to research this one. No clue what it does
			    fgets(path, sizeof(path)-1, fp);
			    pclose(fp);

			    // Dynamically allocate memory for coreCount
			    char *coreCount = malloc(sizeof(path)); // Allocate memory for the same size as path
			    if (coreCount == NULL) {
			        printf("Memory allocation failed\n");
			        return NULL; // Return NULL to indicate failure
			    }

			    // Copy the content of path into coreCount
			    strcpy(coreCount, path);

			    return coreCount;

		case 7:
			//avg CPU Temp
		    FILE *fp2;
		    fp2 = popen("./bash/avgTemp.sh", "r");
		    if (fp2 == NULL) {
		        printf("Failed to run bash script \n");
		        return NULL;
		    }

		    if (fgets(path, sizeof(path), fp2) != NULL) {
		        // Remove newline character, if present
		        path[strcspn(path, "\n")] = '\0';

		        // Dynamically allocate memory for CPUTemp
		        char *CPUTemp = strdup(path);
		        if (CPUTemp == NULL) {
		            printf("Memory allocation failed\n");
		            return NULL;
		        }

		        // Append the temperature with the Celsius symbol
		        strcat(CPUTemp, "°C");
		        pclose(fp2);
		        return CPUTemp;
		    } else {
		        pclose(fp2);
		        return NULL;
		    }

		case 8:
			//Get total CPU Utilization

		{
		    float utilization_array[NUM_ITERATIONS];
		    float sum = 0;

		    // Get CPU utilization values and store them in the array
		    for (int i = 0; i < NUM_ITERATIONS; i++) {
		        float utilization = getCPUUtilization();
		        if (utilization == -1) {
		            printf("Failed to get CPU utilization\n");
		            return NULL;
		        }
		        utilization_array[i] = utilization;
		        sum += utilization;
		    }

		    // Calculate the average CPU utilization
		    float average_utilization = sum / NUM_ITERATIONS;

		    // Dynamically allocate memory for procUtil
		    char *procUtil = malloc(50); // Adjust size accordingly
		    if (procUtil == NULL) {
		        printf("Memory allocation failed\n");
		        return NULL; // Return NULL to indicate failure
		    }

		    // Print the array of CPU utilization values
		    for (int i = 0; i < NUM_ITERATIONS; i++) {
		        printf("CPU Utilization %d: %.2f%%\n", i + 1, utilization_array[i]);
		    }

		    // Print the average CPU utilization
		    printf("Average CPU Utilization: %.2f%%\n", average_utilization);

		    // Convert the average utilization to string and store it in procUtil
		    sprintf(procUtil, "%.2f%%", average_utilization);

		    return procUtil;
		}


		case 9:
			//Check for the packages lm-sensors and bc 
			printf("The program will now check for lm-sensors and bc.\nIf it needs to install any packages, you will likely be prompted for your sudo password. Please enter it.\n");
			printf("After entering your password, please wait until the program has finished running. Depending on your Internet connection, this could take a couple minutes, but it should only be several seconds.\n");
			printf("Finally, please ensure that you do have a working Internet connection and at least 1GB of free space.");

			//pause so the user can read the words, if they wish
			char useless;
		
			printf("\n\nPlease hit Enter to continue:\n");
			scanf("%c", &useless);

			//run the script
			system("bash bash/checkPackages.sh");
			break;



		case 10:
			//show terminal history based on user input
			
			//Prepare an int to store the number of lines desired by the user
			int lineNum;

			//set up the paths for the script versions
			char oGScript[] = "bash/historyOG.sh";
			char newScript[] = "bash/historyNEW.sh";
			char command[1000]; //memory buffer so I have space to store the new command. ChatGPT helped here

			//User input
			printf("Please enter how many lines of history you would like: ");
			scanf("%d", &lineNum);

			//open OG script to read and copy from
			FILE *oGFile = fopen(oGScript, "r");
			//error handling if file is missing
			if (oGFile == NULL) {
				perror("ERROR: Could not open original history script!");
			}

			//open new script to write to
			FILE *newFile = fopen(newScript, "w");
			if (newFile == NULL) {
				//ChatGPT did this error handling
				if (errno == EACCES) {
					printf("Permission denied to create new file. Please run this C program as sudo.\n");
				} else {
					perror("Error creating new script");
				}
				fclose(oGFile);
			}


			//ChatGPT helped with this copying bit

			while (fgets(command, sizeof(command), oGFile) != NULL) {
				// Find the line containing "tail -n" and modify it
				if (strstr(command, "tail -n") != NULL) {
					// Replace the number in the command with user's input
					snprintf(command, sizeof(command), "tail -n %d ~/.bash_history\n", lineNum);
				}
				// Write the modified or unchanged line to the new script
				fprintf(newFile, "%s", command);
			}

			//now to clean up after ourselves
			fclose(oGFile);
			fclose(newFile);
			
			printf("New script successfully created! Running now...\n\n\n");

			system("chmod +x bash/historyNEW.sh");
			system("bash bash/historyNEW.sh");
			break;



		case 11:
			//Verify that the original bash script (historyOG) has been copied and modified 

			//ChatGPT was here first
			//I (Sam) was here second
			FILE *OGfile = fopen("bash/historyOG.sh", "r");
			FILE *NEWfile = fopen("bash/historyNEW.sh", "r");

			if (OGfile == NULL || newFile == NULL) {
				perror("Error opening file");
				if (OGfile) fclose(OGfile);
				if (newFile) fclose(newFile);
				return "-1"; // Error opening file
			}

			char line1[1000];
			char line2[1000];

			while (fgets(line1, sizeof(line1), OGfile) && fgets(line2, sizeof(line2), newFile)) {
				if (strcmp(line1, line2) != 0) {
					fclose(OGfile);
					fclose(newFile);
					return "1"; // Files are different
				}
			}

			if (feof(OGfile) != feof(newFile)) {
				fclose(OGfile);
				fclose(newFile);
				return "1"; // Files have different lengths
			}

			fclose(OGfile);
			fclose(newFile);
			return "0"; // Files are the same


		default:
			printf("ERROR: Something went wrong in the program.\n");
			break;
	}
}
