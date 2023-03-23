#include "sample3213.h"

void insertAtBeginning(struct Node** head_ref, int PID, int FD) {
    /*
    This function inserts a new node at the beginning of the linked list with the head_ref, PID and FD
    */
    struct Node* newNode = createNode(PID, FD);//creating new node
    newNode->next = *head_ref;//setting next of new node to head
    *head_ref = newNode;//setting head to new node
}

int countCommands(struct Node* head) {
  /**
   * This function prints the PID and FD of the list node. It 
   * requires list traversal.
   * Used for the threshold CLA
   * Returns the number of commands
   */
  int i = 0;//counter
  struct Node *traverse = head;//traversing node
  while( traverse != NULL){//traversing till end of list
    i++;//incrementing counter
    printf("%d (%d), ", traverse->PID, traverse->FD);//printing PID and FD
    traverse = traverse->next;//moving to next node
  }//end of while loop
  return i;//returning counter
}

int search(struct Node* head, int PID, int FD) {
  /**
   * This function counts and returns the length of the linked list. It 
   * requires list traversal.
   * Returns the FD of the node with PID
   * Return -1 if the head is NULL
   */
  if(head == NULL) return -1;//if list is empty
  struct Node *traverse = head;//traversing node
  while(traverse != NULL){//traversing till end of list
    if(traverse->PID == PID){//if PID is found
        if(traverse->PID == PID){//if FD is found
            return FD;//returning FD
        }//end of if
    }//end of if
    traverse = traverse->next;//moving to next node
  }//end of while loop
  return -1;//returning -1 if not found
}

struct Node* updater(struct Node* head, int PID, int FD) {
  /**
   * This function updates the FD of the node with PID
   * Returns the head of the linked list witht eh updated FD
   */
  int k = search(head, PID, FD);//searching for PID and FD
  if(k == -1){//if not found
    insertAtBeginning(&head, PID, FD);}//inserting at beginning
  else{//if found
  if(k < FD){//if FD is greater than previous FD
  struct Node *traverse = head;//traversing node
  while(traverse != NULL){//traversing till end of list
    if(traverse->PID == PID){//if PID is found
        traverse->FD = FD;//updating FD
        return head;//returning head
    }//end of if
    traverse = traverse->next;//moving to next node
  }}}//end of if
  return head;//returning head
}

//printing composite data
void print_entry_details(const char* pid, const char* fd, const char* filename, const char* inode, int *k, int threshold, int value) {
    /*
    This function prints the data of the file int composite format
    which is PID, FD, filename, inode
    It checks if the value is -1 or not, which is used for the CLA
    */
    if(value != -1){//if value is not -1
        int p = atoi(pid);//converting pid to intege
        if(value == p){//if value is equal to pid
        printf("%d\t%s\t%s\t%s\t%s\n", *k, pid, fd, inode, filename);//printing data
        }//end of if
    }
    else{//if value is -1
            printf("%d\t%s\t%s\t%s\t%s\n", *k, pid, fd, inode, filename);//printing data
        }
    *k = *k + 1;//incrementing counter
}

//printing per-process data
void print_entry_details_per_process(const char* pid, const char* fd, const char* filename, const char* inode, int *k, int threshold, int value) {
    /*
    This function prints the data of the file int per-process format
    which is PID, FD
    It checks if the value is -1 or not, which is used for the CLA
    */
    if(value != -1){//if value is not -1
        int p = atoi(pid);//converting pid to integer
        if(p == value){//if value is equal to pid
                printf("%d\t%s\t%s\n", *k, pid, fd);//printing data
}
    }
    else{
            printf("%d\t%s\t%s\n", *k, pid, fd);//printing data
}
    *k = *k + 1;//incrementing counter
}

//printing systemwide data
void print_entry_details_system_wide(const char* pid, const char* fd, const char* filename, const char* inode, int *k, int threshold, int value) {
    /*
    This function prints the data of the file int systemwide format
    which is PID, FD, filename
    It checks if the value is -1 or not, which is used for the CLA
    */
    if(value != -1){//if value is not -1
        int p = atoi(pid);//converting pid to integer
        if(p == value){//if value is equal to pid
                printf("%d\t%s\t%s\t%s\n", *k, pid, fd, inode);//printing data
        }
    }
    else{
            printf("%d\t%s\t%s\t%s\n", *k, pid, fd, inode);//printing data
}
    *k = *k + 1;//incrementing counter
}

//printing inode(vnode) data
void print_entry_details_vnode(const char* pid, const char* fd, const char* filename, const char* inode, int *k, int threshold, int value) {
    /*
    This function prints the data of the file int Vnode format
    which is FD, inode
    It checks if the value is -1 or not, which is used for the CLA
    */
    const char* a = fd;//converting fd to const char*
    const char* b = filename;//converting filename to const char*
    if(value != -1){//if value is not -1
        int p = atoi(pid);//converting pid to integer
        if(p == value){//if value is equal to pid
            printf("%d\t%s\t%s\n", *k, a, b);//printing data
        }
}
    else{
            printf("%d\t%s\t%s\t%s\n", *k, pid, a, b);//printing data
}
    *k = *k + 1;//incrementing counter
}

struct Node* printf_threshold_details(const char* pid, const char* fd, const char* filename, const char* inode, int *k, int threshold, int value, struct Node* list){
    /*
    This function prints the data of the file int threshold format
    which is PID (FD) It will return the total FDs of the process
    It keep itself updated with the total FDs of the process by using the updater function
    No duplicates are allowed becuase we use updater function
    */
    int z = atoi(fd);//converting fd to integer
    int p = atoi(pid);//converting pid to integer
    int f = atoi(fd);//converting fd to integer
    if(z > threshold){//if fd is greater than threshold
        list = updater(list, p, f);}//updating list
    return list; //returning list
}

struct Node*  process_inode_entry(DIR* dir, struct dirent* entry, const char* pid, const char* fd, int *k, int threshold, int value, int per_process_arguement, int system_wide_arguement, int vnodes_arguement, int threshold_arguement, int composite_arguement, struct Node* list) {
    /*
    This function processes the inode entry
    It checks if the file is a directory or not
    It take the input parameters dir, entry, pid, fd, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list
    and returns the updated list of the process
    As per the CLA it prints the data in the format specified by the CLA
    */
    char fd_path[1024];//declaring fd_path
    snprintf(fd_path, sizeof(fd_path), "/proc/%s/fd/%s", pid, fd);//storing path in fd_path
    char inode_path[1024];//declaring inode_path
    int inode;//declaring inode
    if ((inode = readlink(fd_path, inode_path, sizeof(inode_path)-1)) != -1) {//if inode is not -1
        inode_path[inode] = '\0';//storing null character
        struct stat sbuf;//declaring stat buffer
        if (stat(inode_path, &sbuf)) {//if stat is not 0
            char inode_str[32];//declaring inode_str
            snprintf(inode_str, sizeof(inode_str), "%lu", sbuf.st_ino);//storing inode in inode_str
            const char* FD = fd;//converting fd to const char*
            if(per_process_arguement == 1){//if per_process_arguement is 1
                print_entry_details_per_process(pid, FD, inode_str, inode_path, k, threshold, value);//calling print_entry_details_per_process
            }
            if(system_wide_arguement == 1){//if system_wide_arguement is 1
                print_entry_details_system_wide(pid, FD, inode_str, inode_path, k, threshold, value);//calling print_entry_details_system_wide
            }
            if(vnodes_arguement == 1){//if vnodes_arguement is 1
                print_entry_details_vnode(pid, FD, inode_str, inode_path, k, threshold, value);//calling print_entry_details_vnode
            }
            if(threshold_arguement == 1){//if threshold_arguement is 1
                list = printf_threshold_details(pid, FD, inode_str, inode_path, k, threshold, value, list);//calling printf_threshold_details
            }
            if((vnodes_arguement == 0 && per_process_arguement == 0 && system_wide_arguement == 0 && threshold_arguement == 0) || composite_arguement == 1){//if vnodes_arguement, per_process_arguement, system_wide_arguement, threshold_arguement are 0 or composite_arguement is 1
                print_entry_details(pid, FD, inode_str, inode_path, k, threshold, value);//calling print_entry_details
            }
        }
    }
    return list;//returning list
}

struct Node*  process_pid_entry(DIR* dir, struct dirent* entry, int *k, int threshold, int value, int per_process_arguement, int system_wide_arguement, int vnodes_arguement, int threshold_arguement, int composite_arguement, struct Node* list) {
    /*
    This function processes the pid entry
    It takes the input parameters dir, entry, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list
    It returns the updated list of the process
    */
    char path[1024];//declaring path
    snprintf(path, sizeof(path), "/proc/%s/fd", entry->d_name);//storing path in path
    DIR* proc_fd_dir;//declaring proc_fd_dir
    if ((proc_fd_dir = opendir(path)) == NULL) return list;//if proc_fd_dir is null return list
    struct dirent* fd_entry;//declaring fd_entry
    while ((fd_entry = readdir(proc_fd_dir)) != NULL) {//while fd_entry is not null
        list = process_inode_entry(proc_fd_dir, fd_entry, entry->d_name, fd_entry->d_name, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list);//calling process_inode_entry
    }
    closedir(proc_fd_dir);//closing proc_fd_dir
    return list;//returning list
}//end of process_pid_entry

struct Node*  read_directory(DIR* dir, int *k, int threshold, int value, int per_process_arguement, int system_wide_arguement, int vnodes_arguement, int threshold_arguement, int composite_arguement, struct Node* list) {
    /*
    This function reads the directory and calls process_pid_entry
    It takes the input parameters dir, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list
    It returns the updated list of the process
    */
    struct dirent* entry;//declaring entry
    while ((entry = readdir(dir)) != NULL) {//while entry is not null
        if (entry->d_name[0] < '0' || entry->d_name[0] > '9') continue;//if entry is not a number continue
        list = process_pid_entry(dir, entry, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list);//calling process_pid_entry
    }
    return list;//returning list
}//end of read_directory

int main(int argc, char *argv[]) {//main function
    /*
    This function is the main function
    It's input parameters are argc and argv
    It returns 0 on success
    It's responsible for parsing the command line arguments and calling the functions
    */
    DIR* dir;//declaring dir
    if ((dir = opendir("/proc")) == NULL) {//if dir is null
        perror("opendir() error");//print error
        return EXIT_FAILURE;//return failure
    }//end of if
    int threshold = -1;//declaring threshold
    int a = 1;//declaring a
    int *k = &a;//declaring k
    int value = -1;//declaring value
    struct Node* list = NULL;//declaring list
    int threshold_arguement = 0;//declaring threshold_arguement
    int per_process_arguement = 0;//declaring per_process_arguement
    int system_wide_arguement = 0;//declaring system_wide_arguement
    int vnodes_arguement = 0;//declaring vnodes_arguement
    int composite_arguement = 0;//declaring composite_arguement
    if(argc == 1){//if argc is 1
            printf("SR.No.\tPID\tFD\tFilename\tInode\n");//print
            printf("===============================================\n");//print
            read_directory(dir, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list);//calling read_directory
            composite_arguement = 0;//setting composite_arguement to 0
            printf("===============================================\n");//print
            closedir(dir);//closing dir
            *k = 1;//setting k to 1
            if ((dir = opendir("/proc")) == NULL) {
            perror("opendir() error");//print error
            return EXIT_FAILURE;}//return failure
        }
    if(argc == 2 && strcmp(argv[1], "--per-process") != 0 && strcmp(argv[1], "--systemWide") != 0 && strcmp(argv[1], "--Vnodes") != 0 && strcmp(argv[1], "--composite") != 0 && (strncmp(argv[1], "--threshold=", 12) != 0)){
            value = atoi(argv[1]);//setting value to argv[1]
            printf(">>> Target PID: %d\n\n", value);//print
            printf("SR.No.\tPID\tFD\tFilename\tInode\n");//print
            printf("===============================================\n");//print
            read_directory(dir, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list);//calling read_directory
            composite_arguement = 0;//setting composite_arguement to 0
            printf("===============================================\n");//print
            *k = 1;//setting k to 1
            closedir(dir);//closing dir
            if ((dir = opendir("/proc")) == NULL) {//if dir is null
            perror("opendir() error");//print error
            return EXIT_FAILURE;}//return failure
        } 
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--per-process") != 0 && strcmp(argv[i], "--systemWide") != 0 && strcmp(argv[i], "--Vnodes") != 0 && strcmp(argv[i], "--composite") != 0 && (strncmp(argv[i], "--threshold=", 12) != 0)){
            value = atoi(argv[i]);}//setting value to argv[1]
    }
    *k = 1;//setting k to 1
    for (int i = 1; i < argc; i++) {//for loop
        if(strcmp(argv[i], "--per-process") != 0 && strcmp(argv[i], "--systemWide") != 0 && strcmp(argv[i], "--Vnodes") != 0 && strcmp(argv[i], "--composite") != 0 && (strncmp(argv[i], "--threshold=", 12) != 0)){
            value = atoi(argv[i]);}//setting value to argv[1]
        if (strcmp(argv[i], "--per-process") == 0) {//if argv[i] is --per-process
            if(value != -1){//if value is not -1
                printf(">>> Target PID: %d\n\n", value);//print
            }//end of if
            printf("SR.No.\tPID\tFD\n");//print
            printf("===============================================\n");//print
            per_process_arguement = 1;//setting per_process_arguement to 1
            read_directory(dir, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list);//calling read_directory
            per_process_arguement = 0;//setting per_process_arguement to 0
            printf("===============================================\n");//print
            closedir(dir);//closing dir
            *k = 1;//setting k to 1
            if ((dir = opendir("/proc")) == NULL) {//if dir is null
            perror("opendir() error");//print error
            return EXIT_FAILURE;}//return failure
        } 
        *k = 1;//setting k to 1
        if (strcmp(argv[i], "--systemWide") == 0) {//if argv[i] is --systemWide
            if(value != -1){//if value is not -1
                printf(">>> Target PID: %d\n\n", value);//print
            }//end of if
            printf("SR.No.\tPID\tFD\tFilename\n");//print
            printf("===============================================\n");//print
            system_wide_arguement = 1;//setting system_wide_arguement to 1
            read_directory(dir, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list);//calling read_directory
            system_wide_arguement = 0;//setting system_wide_arguement to 0
            printf("===============================================\n");//print
            closedir(dir);//closing dir
            *k = 1;//setting k to 1
            if ((dir = opendir("/proc")) == NULL) {//if dir is null
            perror("opendir() error");//print error
            return EXIT_FAILURE;}//return failure
        } 
        *k = 1;//setting k to 1
        if (strcmp(argv[i], "--Vnodes") == 0) {//if argv[i] is --Vnodes
            if(value != -1){//if value is not -1
                printf(">>> Target PID: %d\n\n", value);//print
            }
            printf("SR.No.\tFD\tInode\n");//print
            printf("===============================================\n");//print
            vnodes_arguement = 1;//setting vnodes_arguement to 1
            read_directory(dir, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list);//calling read_directory
            vnodes_arguement = 0;//setting vnodes_arguement to 0
            printf("===============================================\n");//print
            closedir(dir);//closing dir
            *k = 1;//setting k to 1
            if ((dir = opendir("/proc")) == NULL) {//if dir is null
            perror("opendir() error");//print error
            return EXIT_FAILURE;}//return failure
        }
        *k = 1;//setting k to 1
        if (strcmp(argv[i], "--composite") == 0) {//if argv[i] is --composite
            if(value != -1){//if value is not -1
                printf(">>> Target PID: %d\n\n", value);//print
            }
            printf("SR.No.\tPID\tFD\tFilename\tInode\n");//print
            printf("===============================================\n");//print
            composite_arguement = 1;//setting composite_arguement to 1`
            read_directory(dir, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list);//calling read_directory
            composite_arguement = 0;//setting composite_arguement to 0
            printf("===============================================\n");//print
            closedir(dir);//closing dir
            *k = 1;//setting k to 1
            if ((dir = opendir("/proc")) == NULL) {//if dir is null
            perror("opendir() error");//print error
            return EXIT_FAILURE;}//return failure
        } 
        *k = 1;//setting k to 1
        if (strncmp(argv[i], "--threshold=", 12) == 0) {//if argv[i] is --threshold=
            if(value != -1){//if value is not -1
                printf(">>> Target PID: %d\n\n", value);//print
            }
            threshold_arguement = 1;//setting threshold_arguement to 1
            threshold = atoi(argv[i]+12);//setting threshold to argv[i]+12
            printf("## Offending processes -- #FD threshold=%d\n", threshold);//print
            printf("===============================================\n");//print
            list = read_directory(dir, k, threshold, value, per_process_arguement, system_wide_arguement, vnodes_arguement, threshold_arguement, composite_arguement, list);//calling read_directory
            countCommands(list);//calling countCommands
            printf("\n");//print
            *k = 1;//setting k to 1
            threshold_arguement = 0;//setting threshold_arguement to 0
            printf("===============================================\n");//print
            closedir(dir);//closing dir
            if ((dir = opendir("/proc")) == NULL) {//if dir is null
            perror("opendir() error");//print error
            return EXIT_FAILURE;}}}//return failure
    closedir(dir);//closing dir
    return EXIT_SUCCESS;//return EXIT status
    return 0;//return 0
}