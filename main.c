#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Task structure
struct Task {
    char title[100];
    char description[500];
    char dueDate[20];
    char status[20];
    struct Task *next;
};

// Function prototypes
struct Task* createTask();
void addTask(struct Task **head);
void viewTasks(struct Task *head);
void markCompleted(struct Task *head);
void deleteTask(struct Task **head, int taskNumber);
void freeTasks(struct Task *head);

int main() {
    struct Task *head = NULL;
    int choice;

    do {
        printf("\nTask Manager\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(&head);
                break;
            case 2:
                viewTasks(head);
                break;
            case 3:
                markCompleted(head);
                break;
            case 4: {
                int taskNumber;
                printf("Enter the task number to delete: ");
                scanf("%d", &taskNumber);
                deleteTask(&head, taskNumber);
                break;
            }
            case 5:
                freeTasks(head);
                printf("Exiting the Task Manager. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

struct Task* createTask() {
    struct Task *newTask = (struct Task*)malloc(sizeof(struct Task));
    if (newTask == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    newTask->next = NULL;
    return newTask;
}

void addTask(struct Task **head) {
    struct Task *newTask = createTask();

    printf("Enter task details:\n");
    printf("Title: ");
    scanf("%s", newTask->title);

    printf("Description: ");
    scanf("%s", newTask->description);

    printf("Due Date: ");
    scanf("%s", newTask->dueDate);

    printf("Status: ");
    scanf("%s", newTask->status);

    // Add the new task to the front of the list
    newTask->next = *head;
    *head = newTask;

    printf("Task added successfully!\n");
}

void viewTasks(struct Task *head) {
    printf("\nTask List:\n");

    int taskNumber = 1;
    while (head != NULL) {
        printf("%d. Title: %s\n", taskNumber, head->title);
        printf("   Description: %s\n", head->description);
        printf("   Due Date: %s\n", head->dueDate);
        printf("   Status: %s\n", head->status);

        head = head->next;
        taskNumber++;
    }
}

void markCompleted(struct Task *head) {
    int taskNumber;
    printf("Enter the task number to mark as completed: ");
    scanf("%d", &taskNumber);

    // Traverse the list to find the specified task
    int i;
    for (i = 1; i < taskNumber && head != NULL; i++) {
        head = head->next;
    }

    if (head != NULL) {
        strcpy(head->status, "Completed");
        printf("Task marked as completed!\n");
    } else {
        printf("Task not found.\n");
    }
}

void deleteTask(struct Task **head, int taskNumber) {
    if (*head == NULL) {
        printf("Task list is empty. Cannot delete.\n");
        return;
    }

    struct Task *temp = *head;
    if (taskNumber == 1) {
        *head = (*head)->next;
        free(temp);
        printf("Task deleted successfully!\n");
        return;
    }

    // Traverse the list to find the task before the specified task
    int i;
    for (i = 1; i < taskNumber - 1 && temp->next != NULL; i++) {
        temp = temp->next;
    }

    if (temp->next != NULL) {
        struct Task *toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
        printf("Task deleted successfully!\n");
    } else {
        printf("Task not found.\n");
    }
}

void freeTasks(struct Task *head) {
    while (head != NULL) {
        struct Task *temp = head;
        head = head->next;
        free(temp);
    }
}
