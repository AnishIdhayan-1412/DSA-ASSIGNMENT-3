/*1. You are given a task of implementing a simple contact management system using a  singly linked list. The system will manage contact names. Implement the following  operations using a singly linked list and switch case. After every operation, display the  current list of contacts. 
The operations to implement are: 
(i) Creation of the list: Allow the user to create a list of contact names by entering  them one by one. 
(ii) Insertion of a new contact: Insert a new contact's name into a specific position  in the list. The user should provide the name and the position at which it  should be inserted. 
(iii) Deletion of a contact: Delete a contact's name from the list based on their  position or name. Ask the user whether they want to delete by name or by  position. 
(iv) Traversal of the list: Display all the contact names in the list in the current  order. 
(v) Search for a contact: Search for a contact's name in the list and display  whether or not the contact is found, along with their position if present. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {               //creating structure
    char name[100];
    struct Node* next;       //declaring a pointer to the next node in the singly linked list
};

struct Node* head = NULL;    //declaring and initiating the head node as NULL

void displayContacts() {             // function to display the contacts
    struct Node* current = head;
    if (current == NULL) {                       // to check if the list is empty
        printf("Contact list is empty.\n");
        return;
    }
    while (current != NULL) {              // to diaplay the elements in the contacts lsit
        printf("%s -> ", current->name);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {                             //main function
    int choice, position, count, i;
    char name[100];

    while (1) {                                           //to choose what operation is gonna be done
        printf("\n1. Create the list of contacts\n");
        printf("2. Insert a new contact\n");
        printf("3. Delete a contact\n");
        printf("4. Display contact list\n");
        printf("5. Search for a contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {                              //switch case
            case 1:                                       // Create the list
                printf("Enter the number of contacts: ");
                scanf("%d", &count);
                for (i = 0; i < count; i++) {
                    printf("Enter contact name %d: ", i + 1);
                    scanf("%s", name);
                    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                    strcpy(newNode->name, name);
                    newNode->next = NULL;

                    if (head == NULL) {
                        head = newNode;                   // First node
                    } else {
                        struct Node* current = head;
                        while (current->next != NULL) {
                            current = current->next;                  // move to the end of the list
                        }
                        current->next = newNode;                     // insert at the end
                    }
                }
                displayContacts();
                break;

            case 2:                                         // Inserting a new contact
                printf("Enter the contact's name to insert: ");
                scanf("%s", name);
                printf("Enter the position (0-based index) to insert the contact: ");
                scanf("%d", &position);
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                strcpy(newNode->name, name);
                newNode->next = NULL;

                if (position == 0) {
                    newNode->next = head;
                    head = newNode;
                } else {
                    struct Node* current = head;
                    for (i = 0; i < position - 1 && current != NULL; i++) {
                        current = current->next;
                    }
                    if (current == NULL) {
                        printf("Position out of bounds!\n");
                        free(newNode);
                    } else {
                        newNode->next = current->next;
                        current->next = newNode;
                    }
                }
                displayContacts();
                break;

            case 3:                                      //  Delete a contact
                printf("Delete by name or position? (n/p): ");
                char delChoice;
                scanf(" %c", &delChoice);
                if (delChoice == 'n') {
                    printf("Enter the contact's name to delete: ");
                    scanf("%s", name);
                    struct Node* current = head;
                    struct Node* prev = NULL;
                    while (current != NULL && strcmp(current->name, name) != 0) {
                        prev = current;
                        current = current->next;
                    }
                    if (current == NULL) {
                        printf("Contact not found!\n");
                    } else {
                        if (prev == NULL) {
                            head = current->next;
                        } else {
                            prev->next = current->next;
                        }
                        free(current);
                    }
                } else if (delChoice == 'p') {
                    printf("Enter the position (0-based index) to delete the contact: ");
                    scanf("%d", &position);
                    struct Node* current = head;
                    struct Node* prev = NULL;
                    for (i = 0; i < position && current != NULL; i++) {
                        prev = current;
                        current = current->next;
                    }
                    if (current == NULL) {
                        printf("Position out of bounds!\n");
                    } else {
                        if (prev == NULL) {
                            head = current->next;
                        } else {
                            prev->next = current->next;
                        }
                        free(current);
                    }
                }
                displayContacts();
                break;

            case 4:                               // displaying contact list
                displayContacts();
                break;

            case 5:                                               // searching for a contact
                printf("Enter the contact's name to search: ");
                scanf("%s", name);
                struct Node* current = head;
                position = 0;
                while (current != NULL) {
                    if (strcmp(current->name, name) == 0) {
                        printf("%s found at position %d\n", name, position);
                        break;
                    }
                    current = current->next;
                    position++;
                }
                if (current == NULL) {
                    printf("%s not found.\n", name);
                }
                break;

            case 6:                                 // exiting from the program
                printf("Exiting the program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
