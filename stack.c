#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 1000
#define MAX_LENGTH 256

typedef struct {
    int id;
    char description[MAX_LENGTH];
    int completed;
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;

void load_tasks(const char *filename);
void save_tasks(const char *filename);
void add_task(const char *description);
void list_tasks();
void delete_task(int id);
void mark_task_completed(int id);

int main() {
    char filename[] = "tasks.txt";
    load_tasks(filename);

    int choice;
    char description[MAX_LENGTH];
    int id;

    while (1) {
        printf("\nTo-Do List Manager\n");
        printf("1. Add Task\n");
        printf("2. List Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Mark Task Completed\n");
        printf("5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                fgets(description, MAX_LENGTH, stdin);
                description[strcspn(description, "\n")] = 0; // Remove newline
                add_task(description);
                break;
            case 2:
                list_tasks();
                break;
            case 3:
                printf("Enter task ID to delete: ");
                scanf("%d", &id);
                delete_task(id);
                break;
            case 4:
                printf("Enter task ID to mark as completed: ");
                scanf("%d", &id);
                mark_task_completed(id);
                break;
            case 5:
                save_tasks(filename);
                printf("Tasks saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void load_tasks(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No tasks found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%d %[^"] %d\n", &tasks[task_count].id, tasks[task_count].description, &tasks[task_count].completed) != EOF) {
        task_count++;
    }

    fclose(file);
    printf("Tasks loaded successfully.\n");
}

void save_tasks(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error saving tasks.\n");
        return;
    }

    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%d "%s" %d\n", tasks[i].id, tasks[i].description, tasks[i].completed);
    }

    fclose(file);
}

void add_task(const char *description) {
    if (task_count >= MAX_TASKS) {
        printf("Task limit reached. Cannot add more tasks.\n");
        return;
    }

    tasks[task_count].id = task_count + 1;
    strncpy(tasks[task_count].description, description, MAX_LENGTH);
    tasks[task_count].completed = 0;
    task_count++;
    printf("Task added successfully.\n");
}

void list_tasks() {
    if (task_count == 0) {
        printf("No tasks to display.\n");
        return;
    }

    printf("\nID Description Completed\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < task_count; i++) {
        printf("%d "%s" %s\n", tasks[i].id, tasks[i].description, tasks[i].completed ? "Yes" : "No");
    }
}

void delete_task(int id) {
    int found = 0;
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            found = 1;
            for (int j = i; j < task_count - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            task_count--;
            printf("Task deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Task not found.\n");
    }
}

void mark_task_completed(int id) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            tasks[i].completed = 1;
            printf("Task marked as completed.\n");
            return;
        }
    }

    printf("Task not found.\n");
}
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void initialize(Stack *stack);
int is_empty(Stack *stack);
int is_full(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int peek(Stack *stack);
void display(Stack *stack);
void menu();

int main() {
    Stack stack;
    initialize(&stack);

    int choice, value;

    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                break;
            case 2:
                value = pop(&stack);
                if (value != -1) {
                    printf("Popped value: %d\n", value);
                }
                break;
            case 3:
                value = peek(&stack);
                if (value != -1) {
                    printf("Top value: %d\n", value);
                }
                break;
            case 4:
                display(&stack);
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void initialize(Stack *stack) {
    stack->top = -1;
}

int is_empty(Stack *stack) {
    return stack->top == -1;
}

int is_full(Stack *stack) {
    return stack->top == MAX - 1;
}

void push(Stack *stack, int value) {
    if (is_full(stack)) {
        printf("Stack overflow. Cannot push %d.\n", value);
        return;
    }
    stack->data[++stack->top] = value;
    printf("Pushed %d onto the stack.\n", value);
}

int pop(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack underflow. Cannot pop.\n");
        return -1;
    }
    return stack->data[stack->top--];
}

int peek(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return stack->data[stack->top];
}

void display(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements: ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

void menu() {
    printf("\nStack Operations:\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Peek\n");
    printf("4. Display\n");
    printf("5. Exit\n");
}
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int front;
    int rear;
} Queue;

void initialize(Queue *queue);
int is_empty(Queue *queue);
int is_full(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
int peek(Queue *queue);
void display(Queue *queue);
void menu();

int main() {
    Queue queue;
    initialize(&queue);

    int choice, value;

    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&queue, value);
                break;
            case 2:
                value = dequeue(&queue);
                if (value != -1) {
                    printf("Dequeued value: %d\n", value);
                }
                break;
            case 3:
                value = peek(&queue);
                if (value != -1) {
                    printf("Front value: %d\n", value);
                }
                break;
            case 4:
                display(&queue);
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void initialize(Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

int is_empty(Queue *queue) {
    return queue->front == -1;
}

int is_full(Queue *queue) {
    return queue->rear == MAX - 1;
}

void enqueue(Queue *queue, int value) {
    if (is_full(queue)) {
        printf("Queue overflow. Cannot enqueue %d.\n", value);
        return;
    }
    if (is_empty(queue)) {
        queue->front = 0;
    }
    queue->data[++queue->rear] = value;
    printf("Enqueued %d into the queue.\n", value);
}

int dequeue(Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue underflow. Cannot dequeue.\n");
        return -1;
    }
    int value = queue->data[queue->front];
    if (queue->front == queue->rear) {
        initialize(queue);
    } else {
        queue->front++;
    }
    return value;
}

int peek(Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->data[queue->front];
}

void display(Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->data[i]);
    }
    printf("\n");
}

void menu() {
    printf("\nQueue Operations:\n");
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. Peek\n");
    printf("4. Display\n");
    printf("5. Exit\n");
}
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int data);
Node *insert(Node *root, int data);
void inorder(Node *root);
void preorder(Node *root);
void postorder(Node *root);
Node *search(Node *root, int key);
Node *find_min(Node *root);
Node *delete(Node *root, int key);
void menu();

int main() {
    Node *root = NULL;
    int choice, value;

    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                printf("Enter value to search: ");
                scanf("%d", &value);
                Node *found = search(root, value);
                if (found) {
                    printf("Value %d found in the tree.\n", value);
                } else {
                    printf("Value %d not found in the tree.\n", value);
                }
                break;
            case 6:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = delete(root, value);
                break;
            case 7:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node *insert(Node *root, int data) {
    if (root == NULL) {
        return create_node(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

Node *search(Node *root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return search(root->left, key);
    }

    return search(root->right, key);
}

Node *find_min(Node *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node *delete(Node *root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = delete(root->left, key);
    } else if (key > root->data) {
        root->right = delete(root->right, key);
    } else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }

    return root;
}

void menu() {
    printf("\nBinary Tree Operations:\n");
    printf("1. Insert\n");
    printf("2. Inorder Traversal\n");
    printf("3. Preorder Traversal\n");
    printf("4. Postorder Traversal\n");
    printf("5. Search\n");
    printf("6. Delete\n");
    printf("7. Exit\n");
}

