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
    struct Node *prev, *next;
};

struct Node* head = NULL;

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  [#] %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" Think of this program as a double-linked chain of data carriages moving both ways.\n\n");
    printf(AMBER " [STEP 1]" RESET " Fire up an action item from the main control register.\n");
    printf(AMBER " [STEP 2]" RESET " Choose a targeting sub-mode position variant:\n");
    printf("   • " GREEN "Position 1 (Beg):" RESET " Snaps the new node directly onto the starting Head link.\n");
    printf("   • " GREEN "Position 2 (End):" RESET " Explores through the sequence until finding a terminal tail.\n");
    printf("   • " GREEN "Position 3 (Mid):" RESET " Tracks down a unique custom value, splicing inside inline.\n");
    printf("   • " GREEN "Option 3 (View):" RESET "  Renders a visual dual-pointer arrow bidirectional layout map.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize bidirectional kernel engine...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

struct Node* create(int val) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    if (!n) { 
        printf(RED "\n [!] FATAL: HEAP MEMORY EXHAUSTED!\n" RESET); 
        exit(1); 
    }
    n->data = val; 
    n->next = n->prev = NULL;
    return n;
}

void insert(int type) {
    int val, loc;
    printf(AMBER " [?] Input Value: " RESET); scanf("%d", &val);
    struct Node *n = create(val), *t = head;

    if (!head) { 
        head = n; 
    } else if (type == 1) { // Beg
        n->next = head; 
        head->prev = n; 
        head = n;
    } else if (type == 2) { // End
        while (t->next) t = t->next;
        t->next = n; 
        n->prev = t;
    } else { // Mid (After value)
        printf(AMBER " [?] After which value?: " RESET); scanf("%d", &loc);
        while (t && t->data != loc) t = t->next;
        if (!t) { 
            printf(RED " [!] ERROR: VALUE %d NOT FOUND IN ACTIVE REGISTERS!\n" RESET, loc); 
            free(n); 
            return; 
        }
        n->next = t->next; 
        n->prev = t;
        if (t->next) t->next->prev = n;
        t->next = n;
    }
    printf(GREEN "  (+) Success: Element %d safely linked inside node sequence.\n" RESET, val);
}

void del(int type) {
    if (!head) { 
        printf(RED "\n [!] UNDERFLOW: DOUBLY LINKED LIST CONTAIN ZERO ELEMENTS!\n" RESET); 
        return; 
    }
    struct Node *t = head;
    int loc;

    if (type == 1) { // Beg
        head = head->next;
        if (head) head->prev = NULL;
    } else if (type == 2) { // End
        while (t->next) t = t->next;
        if (t->prev) t->prev->next = NULL; 
        else head = NULL;
    } else { // Mid
        printf(AMBER " [?] Value to Delete: " RESET); scanf("%d", &loc);
        while (t && t->data != loc) t = t->next;
        if (!t) { 
            printf(RED " [!] ERROR: TARGET VALUE %d NOT LOCATED!\n" RESET, loc); 
            return; 
        }
        if (t->prev) t->prev->next = t->next; 
        else head = t->next;
        if (t->next) t->next->prev = t->prev;
    }
    printf(RED "  (-) Dropped: Bidirectional link unlinked -> node data [%d]\n" RESET, t->data);
    free(t);
}

void display() {
    printHeader("DOUBLY LINKED POINTER VISUALIZATION");
    if (!head) { 
        printf(RED "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" RESET); 
        return; 
    }
    struct Node* t = head;
    printf("  ");
    printf(PURPLE "NULL " RESET);
    while (t) {
        printf(CYAN "<=>" RESET " [%d] ", t->data);
        t = t->next;
    }
    printf(PURPLE "<=> NULL\n" RESET);
}

int main() {
    int choice, sub;
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] DOUBLY LINKED LIST CONTROL INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU]\n" RESET);
        printf("  1.  (+) Insertion Interface\n");
        printf("  2.  (-) Deletion Interface\n");
        printf("  3.  (#) Visualize Node Layout Sequence\n");
        printf("  4.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1 || choice == 2) {
            printf(CYAN "  (>) Position Variable Allocation [1:Beg 2:End 3:Mid]: " RESET); 
            scanf("%d", &sub);
            if (sub >= 1 && sub <= 3) {
                if (choice == 1) insert(sub);
                else del(sub);
            } else {
                printf(RED " [!] WARNING: Sub-parameter allocation error.\n" RESET);
            }
        } else if (choice == 3) {
            display();
        } else if (choice == 4) {
            printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
            exit(0);
        } else {
            printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}