#include <stdio.h>
#include <stdlib.h>

// ANSI Color Codes for high-tech look
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node *front, *rear;
};

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  [#] %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" Think of this program as a lineup of customers connected dynamically via pointers.\n\n");
    printf(AMBER " [STEP 1]" RESET " Interact with the core kernel functions below.\n");
    printf(AMBER " [STEP 2]" RESET " Observe your dynamic FIFO (First-In, First-Out) tracking:\n");
    printf("   • " GREEN "Option 1 (Enqueue):" RESET " Appends a new node to the tail end of the [REAR] chain.\n");
    printf("   • " GREEN "Option 2 (Dequeue):" RESET " Detaches and frees the oldest surviving element at [FRONT].\n");
    printf("   • " GREEN "Option 3 (View):" RESET "    Outputs sequential address links maps terminated with a NULL string.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize dynamic queue interface...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

void init(struct Queue* q) { 
    q->front = q->rear = NULL; 
}

int isEmpty(struct Queue* q) { 
    return q->front == NULL; 
}

void enqueue(struct Queue* q) {
    int val;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) { 
        printf(RED "\n [!] FATAL: HEAP MEMORY EXHAUSTED\n" RESET); 
        return; 
    }
    
    printf(AMBER " [?] Input Value to Enqueue: " RESET);
    scanf("%d", &val);
    
    newNode->data = val;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf(GREEN "  (+) Success: Dynamic node allocated and linked at rear pointer.\n" RESET);
}

void dequeue(struct Queue* q) {
    if (isEmpty(q)) { 
        printf(RED "\n [!] UNDERFLOW: LINKED QUEUE CONTAINS ZERO ELEMENTS\n" RESET); 
        return; 
    }
    
    struct Node* temp = q->front;
    int data = temp->data;
    
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    printf(RED "  (-) Dropped: Front cell popped -> data [%d] unlinked & freed\n" RESET, data);
}

void display(struct Queue* q) {
    printHeader("DYNAMIC QUEUE MEMORY VISUALIZATION");
    if (isEmpty(q)) { 
        printf(RED "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" RESET); 
        return; 
    }
    
    struct Node* temp = q->front;
    printf("  ");
    while (temp) {
        if (temp == q->front) 
            printf(AMBER "[%d]" RESET " (FRONT) -> ", temp->data);
        else if (temp == q->rear)
            printf(PURPLE "[%d]" RESET " (REAR) -> ", temp->data);
        else
            printf(CYAN "[%d]" RESET " -> ", temp->data);
            
        temp = temp->next;
    }
    printf(PURPLE "NULL\n" RESET);
}

int main() {
    struct Queue q;
    init(&q);
    int choice;

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] DYNAMIC LINKED QUEUE INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU]\n" RESET);
        printf("  1.  (+) Enqueue Allocation (Insert Element)\n");
        printf("  2.  (-) Dequeue Destruction (Remove Element)\n");
        printf("  3.  (#) Traverse Node Layout Sequence\n");
        printf("  4.  [$] Run Pointer Diagnostic Status\n");
        printf("  5.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: enqueue(&q); break;
            case 2: dequeue(&q); break;
            case 3: display(&q); break;
            case 4:
                printHeader("HEAP STRUCT POINTER DIAGNOSTIC REPORT");
                printf("  [-] Front Structural Pointer:   %p\n", (void*)q.front);
                printf("  [-] Rear Structural Pointer :   %p\n", (void*)q.rear);
                printf("  [-] Dynamic Memory State Empty: %s\n", isEmpty(&q) ? RED "TRUE (NULL)" RESET : GREEN "FALSE (Active Nodes)" RESET);
                break;
            case 5: 
                printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
                exit(0);
            default: 
                printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}