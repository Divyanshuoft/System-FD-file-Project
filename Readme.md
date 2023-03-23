Assignment 2: Recreating the System-Wide FD Tables by Divyansh Kachchhava
This program will build a tool to display the tables used by the OS to keep track of open files, assignation of File Descriptors (FD) and processess. It's very helpful to keep track of the files in the system
 
What's we are concerned with?
- C source code file
- C Header file
- Makeme file
- Readme file

Usage
To run the program, execute the following command:
- 2 ways: using make or to directly run the C file
- open your terminal
- type make command
- type ./sample3213 to see the defualt behaviour ie. the composite table to see all the PID, FD, Filename and Inode value in the machine files
- Furhter featues: ./sample3213 --per-process --Vnodes --systemWide --composite --threshold=integer can be used to see other tables
Note: the individual commands --per-process --Vnodes --systemWide --composite --threshold=integer can also be passed to see the result of the individual table (It won't comprise of anything else)
Extra feature: If the user want to just view a specific PID number they can enter the PID number as ./sample3213 PID number which they wanna see
Another way of runnning the file:
gcc filepath of the file containing C file
./a.out to see the result

--threshold=FD: specifies the threshold for the number of file descriptors that a process must have to be considered in the output.
Note: the result will only inculde the PID and the FD of the files which have the FD above the threshold, it will return the total number of FD for a given process
--per-process: prints the file descriptors for each process in a per-process format. It displays the format PID, FD
--systemWide: prints the file descriptors for each file system object in a system-wide format. It displays the format PID, FD, Filename
--Vnodes: prints the file descriptors for each vnode in a vnode format. It displays the format FD, IndodeValue
--composite: prints the file descriptors for each file system object in a composite format. It displays the format PID, FD, Filename, InodeValue
Note: If we pass the value (only the positional argument), like we want to see a specific PID then the result will appear in that sense where the program is concerned with just the specified PID and it displays it's information
What happens if multiple CLA occur: the program will handle them individually and if repeatedly same CLA occurs than the program will only show unique output for every individual CLA

Implementation
The program analyzes file descriptors by reading the /proc directory in Linux. The program first reads the directories for each process, and then reads the files for each file descriptor for each process. For each file descriptor, the program extracts the file name and inode number, and then prints the information as specified by the command line arguments.

The program uses linked lists to keep track of the file descriptors for each process. When a new file descriptor is encountered, the program checks if the process is already in the linked list, and if not, it adds the process to the list. The program then adds the file descriptor to the linked list for the process. Why I use linkedlist? becuase we really don't know the total capacity of the files we are handling, it may change and to avoid data wastage, we use dynamic memory allocation.

Used libraries: stdio.h, stdlib.h, dirent.h, unistd.h, sys/stat.h, string.h

Functions
The program is implemented using the following functions:

createNode(): creation of a node
This function creates a new node and returns it. with PID and FD

insertAtBeginning(): inserts a new node at the beginning of the linked list:
This function prints the PID and FD of the list node. It 
requires list traversal.
Used for the threshold CLA
Returns the number of commands

countCommands(): prints the PID and FD of the list node, and returns the number of commands
This function counts and returns the length of the linked list. It 
requires list traversal.
Returns the FD of the node with PID
Return -1 if the head is NULL

search(): counts and returns the length of the linked list, and returns the FD of the node with PID. Returns -1 if the head is NULL.
This function updates the FD of the node with PID
Returns the head of the linked list witht eh updated FD

updater(): updates the FD of the node with PID, and returns the head of the linked list with the updated FD.
This function prints the data of the file int composite format
which is PID, FD, filename, inode
It checks if the value is -1 or not, which is used for the CLA

print_entry_details(): prints the data of the file in composite format.
This function prints the data of the file int composite format
which is PID, FD, Filename, InodeValue
It checks if the value is -1 or not, which is used for the CLA

print_entry_details_per_process(): prints the data of the file in per-process format.
This function prints the data of the file int per-process format
which is PID, FD
It checks if the value is -1 or not, which is used for the CLA

print_entry_details_system_wide(): prints the data of the file in system-wide format.
This function prints the data of the file int systemwide format
which is PID, FD, filename
It checks if the value is -1 or not, which is used for the CLA

print_entry_details_vnode(): prints the data of the file in Vnode format.
This function prints the data of the file int Vnode format
which is FD, inode
It checks if the value is -1 or not, which is used for the CLA

printf_threshold_details(): prints the data of the file in threshold format, and returns the total FDs of the process.
This function prints the data of the file int threshold format
which is PID (FD) It will return the total FDs of the process
It keep itself updated with the total FDs of the process by using the updater function
No duplicates are allowed becuase we use updater function

process_inode_entry(): processes the inode entry, and returns the updated list of the process.
This function processes the inode entry
It checks if the file is a directory or not
It take the input parameters dir, entry, pid, fd, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement,threshold_arguement, composite_arguement, list
and returns the updated list of the process
As per the CLA it prints the data in the format specified by the CLA

process_pid_entry(): processes the PID entry, and returns the updated list of the process.
This function processes the pid entry
It takes the input parameters dir, entry, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list
It returns the updated list of the process

read_directory(): reads the directory and calls process_pid_entry(), and returns the updated list of the process.
This function reads the directory and calls process_pid_entry
It takes the input parameters dir, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list
It returns the updated list of the process