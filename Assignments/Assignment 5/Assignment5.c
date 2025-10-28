//Name : EECS Assignment 5
//Description : CEO Email Prioritization program in c
//Inputs : file labeled Assignment5_test.txt
//outputs : Next email and number of unread emails
// Collaborators :
//Sources : ChatGPT for info on structs and MaxHeaps in c
//Author : Luke Coffman
//Creation Date : 10/21/25

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#ifdef _WIN32
#define strcasecmp _stricmp
#endif



typedef enum { BOSS, SUBORDINATE, PEER, IMPORTANT_PERSON, OTHER_PERSON} SenderCategory; //Boss == 0, Subordinate ==1,etc. Ranks categories
typedef struct { int year, month, day;} Date; //Stores integers year, month, and date to be initialized later

typedef struct { //Defines the structure of an EMAIL
    SenderCategory sender;
    char subject[256]; // Fiexed array of 256 to hold the subject line
    Date date; //Email's date stored as a Date struct
    int arrival_seq; // Tracks recent arrivals and arrival order in an int
} Email;

typedef struct {// Defines Structure of Heap
    Email* data; //Pointer to email
    int size; //Number of emails in the heap
    int cap; // Total capacity
} Heap;


typedef struct Executive {  //Defines structure of Executive
    char filename[256]; // Stores a copy of the filename
    Heap heap; // Stored heap in executive

} Executive;

//Constructor for Executive
void Executive_init(Executive* e, const char* filename);

//Main method
void Executive_run(Executive* e); 

void Executive_Email(Executive* e, const char* sender, const char* subject, const char* date);// Handles EMAIL labeled lines
void Executive_Next(Executive* e);//Handels NEXT labeled lines
void Executive_Read(Executive* e);//Handles READ labeled lines
void Executive_Count(Executive* e);//Handles COUNT labeled lines

FILE* get_valid_file_input(char* filename, size_t size){
    FILE* file = NULL;

    while (1) {
        printf("Enter the input filename: ");
        if (!fgets(filename, size, stdin)) {
            printf("Input error.\n");
            continue;
        }

        // Remove newline if present
        filename[strcspn(filename, "\n")] = '\0';

        // Try to open the file for reading
        file = fopen(filename, "r");
        if (file) {
            printf("Successfully opened '%s'.\n", filename);
            return file; // Return open file pointer
        } else {
            printf("Error: Could not open '%s'. Please try again.\n", filename);
        }
    }
}


// Heap functions
void heap_init(Heap* h, int capacity);
void heap_insert(Heap* h, Email item);
Email heap_peek(const Heap* h);
Email heap_pop(Heap* h);
int compare_email(const Email* a, const Email* b);


int main(void){
    char filename[256]; //initialize string for filenmae
    FILE* file = get_valid_file_input(filename, sizeof(filename)); //get a valid file input from the user

    Executive exec;                     //Create Executive object
    Executive_init(&exec, filename);    //Initialize exec with filename
    fclose(file);                       //Close file 

    Executive_run(&exec);               //Run program
    return 0;
}

void Executive_init(Executive* e, const char* filename){

    strcpy(e->filename, filename); //copy filename string
    heap_init(&e->heap, 10); //Initialize heap with capacity of 10


}

void Executive_run(Executive * e){ // main running function
    FILE* f = fopen(e->filename, "r");//open file for reading
    if(!f){ //If file fails to open
        printf("Error: could not open %s\n", e->filename);
        return;
    }

    char line[256];  //buffer to store each line from the fuile
    
    while (fgets(line, sizeof(line), f)) {  // each line until the file is done
        //remove newline character at the end
        line[strcspn(line, "\n")] = '\0';

        // Also remove trailing '\r' if present
        size_t L = strlen(line);
        if (L > 0 && line[L - 1] == '\r') {
            line[L - 1] = '\0';
            L--;
        }


        //Skip empty lines
        if (strlen(line)==0){
            continue;
        }

        //Handle EMAIL command
        if (strncmp(line, "EMAIL ", 6)==0){ //If line starts with EMAIL
            char sender[64], subject[256],date[32]; //Buffers to store parsed data
            
            
            //Parse line EMAIL sender Subject date
            if (sscanf(line + 6, "%[^,], %[^,], %31s", sender, subject, date) == 3){ //If parsing is successful
                while (isspace((unsigned char)sender[0])) {
                    memmove(sender, sender + 1, strlen(sender) + 1);
                }
                while (isspace((unsigned char)subject[0])) {
                    memmove(subject, subject + 1, strlen(subject) + 1);
                }
                while (isspace((unsigned char)date[0])) {
                    memmove(date, date + 1, strlen(date) + 1);
                }
                Executive_Email(e, sender, subject, date);

            }else{
                printf("Invalid EMAIL format %s\n", line);
            }

        }

        //Handle NEXT command
        else if(strcmp(line, "NEXT") == 0){
            Executive_Next(e);
        }
        //Handle READ command
        else if(strcmp(line, "READ") == 0){
            Executive_Read(e);
        }
        //Handle COUNT command
        else if (strcmp(line, "COUNT") == 0){
            Executive_Count(e);
        }
        else{
            printf("Unknown command: %s\n", line); 
        }
        

    }
    fclose(f)   ; //Close file when done

}

void Executive_Email(Executive* e, const char* sender, const char* subject, const char* date) {
    Email newEmail;  
    newEmail.arrival_seq = e->heap.size + 1;  // Assign arrival order based on heap size

    //Parse sender
    if (strcasecmp(sender, "Boss") == 0)
        newEmail.sender = BOSS;
    else if (strcasecmp(sender, "Subordinate") == 0)
        newEmail.sender = SUBORDINATE;
    else if (strcasecmp(sender, "Peer") == 0)
        newEmail.sender = PEER;
    else if (strcasecmp(sender, "Important Person") == 0)
        newEmail.sender = IMPORTANT_PERSON;
    else
        newEmail.sender = OTHER_PERSON;

    //Copy Subject
    strncpy(newEmail.subject, subject, sizeof(newEmail.subject) - 1);
    newEmail.subject[sizeof(newEmail.subject) - 1] = '\0';  // Ensure null termination  

    //Parse date
    if (sscanf(date, "%d-%d-%d",
               &newEmail.date.month,
               &newEmail.date.day,
               &newEmail.date.year) != 3) {
        printf("Invalid date format: %s\n", date);
        return;
    }
    //Insert new email into heap
    heap_insert(&e->heap, newEmail);

}

void Executive_Next(Executive* e) {
    //Handle case where there are no emails
    if (e->heap.size == 0) {
        printf("No unread emails.\n");
        return;
    }

    //Get top email using heap_peek()
    Email next = heap_peek(&e->heap);

    //Print the next email’s information
    printf("Next email to read:\n");
    printf("   From   : ");
    switch (next.sender) {
        case BOSS: printf("Boss\n"); break; //Print sender category
        case SUBORDINATE: printf("Subordinate\n"); break;
        case PEER: printf("Peer\n"); break;
        case IMPORTANT_PERSON: printf("Important Person\n"); break;
        default: printf("Other Person\n"); break;
    }
    printf("   Subject: %s\n", next.subject); //Print subject line
    printf("   Date   : %02d-%02d-%04d\n", next.date.month, next.date.day, next.date.year); //Print date in MM-DD-YYYY format
}

void Executive_Read(Executive* e) {
    if (e->heap.size == 0) {
        printf("No emails in queue.\n");
        return;
    }

    Email read = heap_pop(&e->heap);  // remove top

    // Only a brief confirmation (no details), to avoid repeating what NEXT just showed
    printf("Email read: %s\n", read.subject);
    printf("Remaining unread emails: %d\n", e->heap.size);
}



void Executive_Count(Executive* e) {
    if (e->heap.size == 0)
        printf("No unread emails.\n");
    else if (e->heap.size == 1)
        printf("There is 1 unread email.\n");
    else
        printf("There are %d unread emails.\n", e->heap.size);
}

int compare_email(const Email* a, const Email* b) {
    // Compare sender category (importance)
    if (a->sender != b->sender)
        return b->sender - a->sender; // Lower enum value = higher priority

    // Compare year (earlier = higher priority)
    if (a->date.year != b->date.year)
        return b->date.year - a->date.year;

    // Compare month
    if (a->date.month != b->date.month)
        return b->date.month - a->date.month;

    // Compare day
    if (a->date.day != b->date.day)
        return b->date.day - a->date.day;

    // Compare arrival sequence (earlier = higher priority)
    return b->arrival_seq - a->arrival_seq;
}


void heap_init(Heap* h, int capacity){
    //Allocates memory for the data array to stoe Email elements
    //Each element is an email struct

    h->data = (Email*)malloc(sizeof(Email) * capacity);

    //Check if memory allocation failed
    if (!h->data){
        printf("Memory allocation failed\n");
        exit(1);
    }
    h->size =0;
    h->cap = capacity;


}

void heap_insert(Heap* h, Email item){
    //Insert new email into the heap

    //Check if heap is full
    if (h->size >= h->cap){
        h->cap *=2; //Double capacity
        h->data = (Email*)realloc(h->data, sizeof(Email) * h->cap); //Reallocate memory

        if (!h->data){
            printf("Memory reallocation failed\n");
            exit(1);
        }
    }

    //Place new item at the end of the array

    int i = h->size;
    h->data[i] = item;
    h->size++;

    //Bubble up to maintain heap property

    while( i > 0){
        int parent = (i-1)/2;

        if(compare_email(&h->data[i], &h->data[parent]) > 0){
            Email temp = h->data[parent]; // temp variable for swapping

            //Swap parent and child
            h->data[parent] = h->data[i];
            h->data[i] = temp;

            i = parent; //Move up to parent index
        } else {
            break; //Heap property satisfied
        }
    }
}

Email heap_peek(const Heap* h){

    //Check if heap is empty
    if (h->size == 0){
        printf("Heap is empty\n");
        exit(1);
    }

    return h->data[0]; //Return the root element
}

Email heap_pop(Heap* h){

    //Check if heap is empty

    if (h->size == 0){
        printf("Heap is empty\n");
        exit(1);
    }

    //Store the root email
    Email root = h->data[0];

    h->data[0] = h->data[h->size -1]; //Move last element to root
    h->size--; //Decrease size

    //Bubble down to maintain heap property
    int i = 0; //Start at root
    while(1){
        int left = 2*i +1; //Left child index
        int right = 2*i +2; //Right child index
        int largest = i; //Assume current is largest

        //Compare left child
        if(left < h->size && compare_email(&h->data[left], &h->data[largest]) > 0){
            largest = left;
        }

        //Compare right child
        if (right < h->size && compare_email(&h->data[right], &h->data[largest]) > 0){
            largest = right;
        }
        if (largest != i){
            //Swap current with largest child
            Email temp = h->data[i];
            h->data[i] = h->data[largest];
            h->data[largest] = temp;

            i = largest; //Move down to largest child index
        } else {
            break; //Heap property satisfied
        }
    }
    return root; //Return the original root email
}

