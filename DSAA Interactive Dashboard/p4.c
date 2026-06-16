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
    struct Node *next; 
} *top = NULL;

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  [#] %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" Think of this program as a stack of boxes connected via pointers on a heap.\n\n");
    printf(AMBER " [STEP 1]" RESET " Interact with the core kernel functions below.\n");
    printf(AMBER " [STEP 2]" RESET " Observe your dynamic runtime behaviors:\n");
    printf("   • " GREEN "Option 1 (Push):" RESET "  Spawns a node out of heap memory and updates the top layer.\n");
    printf("   • " GREEN "Option 2 (Pop):" RESET "   Unlinks the top container, returning its data to cell zero.\n");
    printf("   • " GREEN "Option 3 (Peep):" RESET "  Points explicitly to current node targets without unlinking.\n");
    printf("   • " GREEN "Option 4 (View):" RESET "  Outputs sequential link maps terminated with a NULL string.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize dynamic stack engine...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

int is_empty() { return top == NULL; }

int is_full() { 
    struct Node *t = malloc(sizeof(struct Node)); 
    if(t) { free(t); return 0; } 
    return 1; 
}

void push() {
    int val;
    struct Node *n = malloc(sizeof(struct Node));
    if (!n) {
        printf(RED "\n [!] OVERFLOW: SYSTEM MEMORY DEPLETED\n" RESET);
        return;
    }
    printf(AMBER " [?] Input Value to Push: " RESET);
    scanf("%d", &val);
    
    n->data = val; 
    n->next = top; 
    top = n;
    printf(GREEN "  (+) Success: Node safely pushed and linked to top address.\n" RESET);
}

void pop() {
    if (is_empty()) {
        printf(RED "\n [!] UNDERFLOW: LINKED STACK CONTAIN ZERO ELEMENTS\n" RESET);
        return;
    }
    struct Node *t = top; 
    int v = t->data; 
    top = top->next; 
    free(t);
    printf(RED "  (-) Dropped: Top heap cell popped -> element data [%d]\n" RESET, v);
}

void peep() {
    if (is_empty()) {
        printf(RED "\n [!] EMPTY: Operational reference pointer targets NULL.\n" RESET);
    } else {
        printf(CYAN "  (>) Current Stack Pointer Vector: [%d]\n" RESET, top->data);
    }
}

void traverse() {
    printHeader("DYNAMIC STACK MEMORY VISUALIZATION");
    if (is_empty()) {
        printf(RED "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" RESET);
    } else {
        struct Node *t = top;
        printf("  ");
        while (t) {
            if (t == top)
                printf(GREEN "[%d]" RESET " (TOP Pointer) -> ", t->data);
            else
                printf(CYAN "[%d]" RESET " -> ", t->data);
            t = t->next;
        }
        printf(PURPLE "NULL\n" RESET);
    }
}

int main() {
    int ch;
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] DYNAMIC LINKED STACK INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU]\n" RESET);
        printf("  1.  (+) Push Allocation (Insert Element)\n");
        printf("  2.  (-) Pop Destruction (Remove Element)\n");
        printf("  3.  (*) Peep Offset Address Reference\n");
        printf("  4.  (#) Traverse Node Layout Sequence\n");
        printf("  5.  [$] Run Heap Diagnostics Status\n");
        printf("  6.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &ch) != 1) break;

        switch (ch) {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: peep(); break;
            case 4: traverse(); break;
            case 5: 
                printHeader("HEAP REGISTRY DIAGNOSTIC REPORT");
                printf("  [-] Stack Pointer State Empty:   %s\n", is_empty() ? RED "TRUE (NULL)" RESET : GREEN "FALSE (Active Pointer)" RESET);
                printf("  [-] System RAM Boundary Limit:   %s\n", is_full() ? RED "REACHED (0 Bytes Free)" RESET : GREEN "AVAILABLE (Dynamic Allocations Allowed)" RESET);
                break;
            case 6: 
                printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
                exit(0);
            default: 
                printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}