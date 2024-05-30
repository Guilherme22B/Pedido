#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCRIPTION_SIZE 100

typedef struct Task {
    int id;
    char description[MAX_DESCRIPTION_SIZE];
    struct Task* prox;
} TASK;

typedef struct {
    TASK* front;
    TASK* rear;
} Queue;

typedef struct {
    TASK* top;
} Stack;

typedef struct {
    TASK* head;
} List;

Queue pendingQueue = {NULL, NULL};
Stack draftStack = {NULL};
List completedList = {NULL};

// CONSTRUCTOR
TASK* createTask(int id, char* description);
TASK* createTaskByScanf();

// LIST FUNCTIONS
void addToCompletedList(TASK* newTask);
TASK* removeFromCompletedListByItsId(int id);
void seeAllCompletedList();

// QUEUE FUNCTIONS
void putToPendingQueue(TASK* newTask);
TASK* getFromPendingQueue();
void seeAllPendingQueue();

// STACK FUNCTIONS
void pushToDraftStack(TASK* newTask);
TASK* popFromDraftStack();
void seeAllDraftStack();

// MENU
void displayMenu();

int main() {
    int choice;
    printf("################# TASK MANAGER SYSTEM #################\n");

    do {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        TASK* newTask = NULL;
        TASK* task = NULL;
        int id;

        switch (choice) {
            case 1:
                // CREATE A TASK, THEN ADD TO PENDING QUEUE
                newTask = createTaskByScanf();
                putToPendingQueue(newTask);
                break;

            case 2:
                // SEE ALL TASKS FROM PENDING QUEUE
                seeAllPendingQueue();
                break;

            case 3:
                // COMPLETE FIRST PENDING TASK
                task = getFromPendingQueue();
                if(task != NULL) {
                    addToCompletedList(task);
                }
                break;

            case 4:
                // SEE ALL TASKS FROM COMPLETED LIST
                seeAllCompletedList();
                break;

            case 5:
                // SET COMPLETED TASK TO DRAFT
                printf("Enter Task ID (number): ");
                scanf("%d", &id);
                task = removeFromCompletedListByItsId(id);
                if(task != NULL) {
                    pushToDraftStack(task);
                }
                break;

            case 6:
                // SEE ALL TASKS FROM DRAFT STACK
                seeAllDraftStack();
                break;

            case 7:
                // SET LAST DRAFT AS PENDING TASK
                task = popFromDraftStack();
                if(task != NULL) {
                    putToPendingQueue(task);
                }
                break;

            case 0:
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 0);

    printf("################# SYSTEM SHUT DOWN #################\n");
    return 0;
}

// CONSTRUCTOR
TASK* createTask(int id, char* description) {
    TASK* newTask = (TASK*) malloc(sizeof(TASK));
    newTask->id = id;
    strcpy(newTask->description, description);
    newTask->prox = NULL;
    return newTask;
}

TASK* createTaskByScanf() {
    int id;
    char description[MAX_DESCRIPTION_SIZE];

    printf("Enter Task ID (number): ");
    scanf("%d", &id);

    getchar();
    printf("Enter Task Description (string): ");
    fgets(description, MAX_DESCRIPTION_SIZE, stdin);
    description[strcspn(description, "\n")] = '\0';

    return createTask(id, description);
}

// LIST FUNCTIONS
void addToCompletedList(TASK* newTask) {
    newTask->prox = completedList.head;
    completedList.head = newTask;
    printf("Task added to Completed List\n");
}

TASK* removeFromCompletedListByItsId(int id) {
    TASK* prev = NULL;
    TASK* curr = completedList.head;
    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->prox;
    }
    if (curr == NULL) {
        printf("Task with ID %d not found in Completed List\n", id);
        return NULL;
    }
    if (prev == NULL) {
        completedList.head = curr->prox;
    } else {
        prev->prox = curr->prox;
    }
    curr->prox = NULL;
    return curr;
}

void seeAllCompletedList() {
    TASK* curr = completedList.head;
    if (curr == NULL) {
        printf("Completed List is empty\n");
        return;
    }
    printf("Completed List:\n");
    while (curr != NULL) {
        printf("ID: %d, Description: %s\n", curr->id, curr->description);
        curr = curr->prox;
    }
}

// QUEUE FUNCTIONS
void putToPendingQueue(TASK* newTask) {
    if (pendingQueue.rear == NULL) {
        pendingQueue.front = pendingQueue.rear = newTask;
    } else {
        pendingQueue.rear->prox = newTask;
        pendingQueue.rear = newTask;
    }
    printf("Task added to Pending Queue\n");
}

TASK* getFromPendingQueue() {
    if (pendingQueue.front == NULL) {
        printf("Pending Queue is empty\n");
        return NULL;
    }
    TASK* temp = pendingQueue.front;
    pendingQueue.front = pendingQueue.front->prox;
    if (pendingQueue.front == NULL) {
        pendingQueue.rear = NULL;
    }
    temp->prox = NULL;
    return temp;
}

void seeAllPendingQueue() {
    TASK* curr = pendingQueue.front;
    if (curr == NULL) {
        printf("Pending Queue is empty\n");
        return;
    }
    printf("Pending Queue:\n");
    while (curr != NULL) {
        printf("ID: %d, Description: %s\n", curr->id, curr->description);
        curr = curr->prox;
    }
}

// STACK FUNCTIONS
void pushToDraftStack(TASK* newTask) {
    newTask->prox = draftStack.top;
    draftStack.top = newTask;
    printf("Task pushed to Draft Stack\n");
}

TASK* popFromDraftStack() {
    if (draftStack.top == NULL) {
        printf("Draft Stack is empty\n");
        return NULL;
    }
    TASK* temp = draftStack.top;
    draftStack.top = draftStack.top->prox;
    temp->prox = NULL;
    return temp;
}

void seeAllDraftStack() {
    TASK* curr = draftStack.top;
    if (curr == NULL) {
        printf("Draft Stack is empty\n");
        return;
    }
    printf("Draft Stack:\n");
    while (curr != NULL) {
        printf("ID: %d, Description: %s\n", curr->id, curr->description);
        curr = curr->prox;
    }
}

// MENU
void displayMenu() {
    printf("\nMenu:\n");
    printf("1 - Create New Pending Task\n");
    printf("2 - See All Pending Tasks\n");
    printf("3 - Complete First Pending Task\n");
    printf("4 - See All Completed Tasks\n");
    printf("5 - Set Completed Task as Draft by its ID\n");
    printf("6 - See All Draft Tasks\n");
    printf("7 - Set Last Draft Task as Pending Task\n");
    printf("0 - Exit\n");
}
