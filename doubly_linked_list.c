/*2. You are tasked with implementing a simple contact management system using a  doubly linked list. The system will manage contact names. Implement the following  operations using a doubly linked list and switch-case. After every operation, display  the current list of contacts. 
The operations to implement are: 
(i) Creation of the list: 
Allow the user to create a list of contact names by entering them one by one. (ii) Insertion of a new contact: 
Insert a new contact’s name into a specific position in the list. The user should  provide the name and the position at which it should be inserted. 
(iii)Deletion of a contact: 
Delete a contact’s name from the list based on their position or name. Ask the user  whether they want to delete by name or by position. 
(iv)Traversal of the list (in both directions): 
Display all the contact names in the list in the current order (forward traversal)  and then display them in reverse order (backward traversal). 
(v) Search for a contact: 
Search for a contact’s name in the list and display whether or not the contact is  found, along with their position if present.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {                        //creating structure
    char name[100];
    struct Node* prev;                //creating pointer nodes
    struct Node* next;
};

struct Node* head = NULL;                     //initiating nodes as null
struct Node* tail = NULL;

void displayContacts() {                      //function to display contacts
    struct Node* current = head;
    printf("Contact list (forward): ");
    while (current != NULL) {                    // printing the list in forward manner
        current = current->next;
    }
    printf("NULL\n");

    current = tail;
    printf("Contact list (backward): ");             //pirnting list in backward manner
    while (current != NULL) {
        printf("%s <-> ", current->name);
        current = current->prev;
    }
    printf("NULL\n");
}

void createList(int count) {           //function to create list
    for (int i = 0; i < count; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        printf("Enter contact name %d: ", i + 1);
        scanf("%s", newNode->name);
        newNode->prev = tail;
        newNode->next = NULL;

        if (tail != NULL) {            
            tail->next = newNode;
        } else {
            head = newNode; // First node
        }
        tail = newNode; // Update tail
    }
    displayContacts();
}

void insertContact(char* name, int position) {                           // function to insert an element
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->prev = NULL;
    newNode->next = NULL;

    if (position == 0) {                            // Insert at head
        newNode->next = head;
        if (head != NULL) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == NULL) {                           // First insertion
            tail = newNode;
        }
    } else {
        struct Node* current = head;
        for (int i = 0; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }
        if (current != NULL) {
            newNode->next = current->next;
            newNode->prev = current;
            current->next = newNode;
            if (newNode->next != NULL) {
                newNode->next->prev = newNode;
            } else {
                tail = newNode;                      // Update tail if inserted at the end
            }
        } else {
            printf("Position out of bounds!\n");
            free(newNode);
        }
    }
    displayContacts();
}

void deleteContact(char* name, int position, int byName) {
    struct Node* current;
    if (byName) {
        current = head;
        while (current != NULL && strcmp(current->name, name) != 0) {
            current = current->next;
        }
    } else {
        current = head;
        for (int i = 0; i < position && current != NULL; i++) {
            current = current->next;
        }
    }

    if (current != NULL) {
        if (current->prev != NULL) {
            current->prev->next = current->next;
        } else {
            head = current->next;               // updating head if needed
        }
        if (current->next != NULL) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;                   // updating tail if needed
        }
        free(current);
        displayContacts();
    } else {
        printf("Contact not found!\n");
    }
}

void searchContact(char* name) {                  //function to search elements
    struct Node* current = head;
    int position = 0;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("%s found at position %d\n", name, position);
            return;
        }
        current = current->next;
        position++;
    }
    printf("%s not found\n", name);
}

int main() {               //main function
    int choice;
    char name[100];
    int position, count;

    while (1) {                         //choosing what operation to be done
        printf("1. Create the list of contacts\n");
        printf("2. Insert a new contact\n");
        printf("3. Delete a contact\n");
        printf("4. Display contact list\n");
        printf("5. Search for a contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {                       //switch case
            case 1:                             //creating the list
                printf("Enter the number of contacts: ");
                scanf("%d", &count);
                createList(count);
                break;
            case 2:                    //inserting an element 
                printf("Enter the contact's name to insert: ");
                scanf("%s", name);
                printf("Enter the position (0-based index) to insert the contact: ");
                scanf("%d", &position);
                insertContact(name, position);
                break;
            case 3:                  //delete contact with name or position
                printf("Delete by name or position? (n/p): ");
                char option;
                scanf(" %c", &option);
                if (option == 'n') {
                    printf("Enter the name to delete: ");
                    scanf("%s", name);
                    deleteContact(name, -1, 1);
                } else {
                    printf("Enter the position (0-based index) to delete the contact: ");
                    scanf("%d", &position);
                    deleteContact(NULL, position, 0);
                }
                break;
            case 4:
                displayContacts();
                break;
            case 5:                             //search contact
                printf("Enter the contact's name to search: ");
                scanf("%s", name);
                searchContact(name);
                break;
            case 6:                                     //exit progrmam
                printf("Exiting the program...\n");
                return 0;
            default:                                    //default message if there is any invalid choice is given
                printf("Invalid choice! Please try again.\n");
        }
    }
}
