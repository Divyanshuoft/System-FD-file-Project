#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

struct Node {
    //structure for linked list
    int PID;//process id
    int FD;//file descriptor
    struct Node* next;//pointer to next node
};

struct Node* createNode(int PID, int FD) {
    /*
    This function creates a new node and returns it. with PID and FD
    */
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));//allocating memory for new node
    newNode->PID = PID;//setting PID of new node
    newNode->FD = FD;//setting FD of new node
    newNode->next = NULL;//setting next of new node to NULL
    return newNode;//returning new node
}

/*
    This function inserts a new node at the beginning of the linked list with the head_ref, PID and FD
*/
void insertAtBeginning(struct Node** head_ref, int PID, int FD);

/**
   * This function prints the PID and FD of the list node. It 
   * requires list traversal.
   * Used for the threshold CLA
   * Returns the number of commands
*/
int countCommands(struct Node* head);

/**
   * This function counts and returns the length of the linked list. It 
   * requires list traversal.
   * Returns the FD of the node with PID
   * Return -1 if the head is NULL
   */
int search(struct Node* head, int PID, int FD);

/**
   * This function updates the FD of the node with PID
   * Returns the head of the linked list witht eh updated FD
   */
struct Node* updater(struct Node* head, int PID, int FD);

/*
    This function prints the data of the file int composite format
    which is PID, FD, filename, inode
    It checks if the value is -1 or not, which is used for the CLA
    */
void print_entry_details(const char* pid, const char* fd, const char* filename, const char* inode, int *k, int threshold, int value);

/*
    This function prints the data of the file int per-process format
    which is PID, FD
    It checks if the value is -1 or not, which is used for the CLA
    */
void print_entry_details_per_process(const char* pid, const char* fd, const char* filename, const char* inode, int *k, int threshold, int value);

/*
    This function prints the data of the file int systemwide format
    which is PID, FD, filename
    It checks if the value is -1 or not, which is used for the CLA
    */
void print_entry_details_system_wide(const char* pid, const char* fd, const char* filename, const char* inode, int *k, int threshold, int value);

/*
    This function prints the data of the file int Vnode format
    which is FD, inode
    It checks if the value is -1 or not, which is used for the CLA
    */
void print_entry_details_vnode(const char* pid, const char* fd, const char* filename, const char* inode, int *k, int threshold, int value);

/*
    This function prints the data of the file int threshold format
    which is PID (FD) It will return the total FDs of the process
    It keep itself updated with the total FDs of the process by using the updater function
    No duplicates are allowed becuase we use updater function
    */
struct Node* printf_threshold_details(const char* pid, const char* fd, const char* filename, const char* inode, int *k, int threshold, int value, struct Node* list);

/*
    This function processes the inode entry
    It checks if the file is a directory or not
    It take the input parameters dir, entry, pid, fd, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list
    and returns the updated list of the process
    As per the CLA it prints the data in the format specified by the CLA
    */
struct Node*  process_inode_entry(DIR* dir, struct dirent* entry, const char* pid, const char* fd, int *k, int threshold, int value, int per_process_arguement, int system_wide_arguement, int vnodes_arguement, int threshold_arguement, int composite_arguement, struct Node* list);

/*
    This function processes the pid entry
    It takes the input parameters dir, entry, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list
    It returns the updated list of the process
    */
struct Node*  process_pid_entry(DIR* dir, struct dirent* entry, int *k, int threshold, int value, int per_process_arguement, int system_wide_arguement, int vnodes_arguement, int threshold_arguement, int composite_arguement, struct Node* list);

/*
    This function reads the directory and calls process_pid_entry
    It takes the input parameters dir, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list
    It returns the updated list of the process
    */
struct Node*  read_directory(DIR* dir, int *k, int threshold, int value, int per_process_arguement, int system_wide_arguement, int vnodes_arguement, int threshold_arguement, int composite_arguement, struct Node* list);