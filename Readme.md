## Assignment 2: Recreating the System-Wide FD Tables by Divyansh Kachchhava
This program will build a tool to display the tables used by the OS to keep track of open files, assignation of File Descriptors (FD) and processess. It's very helpful to keep track of the files in the system

### Usage
To run the program, execute the following command:

``` css
Copy code
./fda [-p pid] [-t threshold] [-P] [-S] [-V] [-T] [-C]
```

-p pid: specifies the PID of the process to be analyzed.
-t threshold: specifies the threshold for the number of file descriptors that a process must have to be considered in the output.
-P: prints the file descriptors for each process in a per-process format.
-S: prints the file descriptors for each file system object in a system-wide format.
-V: prints the file descriptors for each vnode in a vnode format.
-T: prints the total number of file descriptors for each process that has file descriptors above the threshold.
-C: prints the file descriptors for each file system object in a composite format.

### Implementation
The program analyzes file descriptors by reading the /proc directory in Linux. The program first reads the directories for each process, and then reads the files for each file descriptor for each process. For each file descriptor, the program extracts the file name and inode number, and then prints the information as specified by the command line arguments.

The program uses linked lists to keep track of the file descriptors for each process. When a new file descriptor is encountered, the program checks if the process is already in the linked list, and if not, it adds the process to the list. The program then adds the file descriptor to the linked list for the process.

### Functions
The program is implemented using the following functions:

createNode(): creates a new node for the linked list.
insertAtBeginning(): inserts a new node at the beginning of the linked list.
countCommands(): prints the PID and FD of the list node, and returns the number of commands.
search(): counts and returns the length of the linked list, and returns the FD of the node with PID. Returns -1 if the head is NULL.
updater(): updates the FD of the node with PID, and returns the head of the linked list with the updated FD.
print_entry_details(): prints the data of the file in composite format.
print_entry_details_per_process(): prints the data of the file in per-process format.
print_entry_details_system_wide(): prints the data of the file in system-wide format.
print_entry_details_vnode(): prints the data of the file in Vnode format.
printf_threshold_details(): prints the data of the file in threshold format, and returns the total FDs of the process.
process_inode_entry(): processes the inode entry, and returns the updated list of the process.
process_pid_entry(): processes the PID entry, and returns the updated list of the process.
read_directory(): reads the directory and calls process_pid_entry(), and returns the updated list of the process.
