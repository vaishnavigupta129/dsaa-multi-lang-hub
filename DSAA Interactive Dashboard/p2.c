#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ANSI Color Codes for high-tech look
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

struct Node { int data; struct Node* next; };

struct Node* create(int val) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    if (!n) {
        printf(RED "\n [!] OVERFLOW: SYSTEM MEMORY FULL\n" RESET);
    } else { 
        n->data = val; 
        n->next = NULL; 
    }
    return n;
}

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  [#] %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" Think of this program as a chain of train cars (nodes) linked together.\n\n");
    printf(AMBER " [STEP 1]" RESET " Pick an option from the main menu.\n");
    printf(AMBER " [STEP 2]" RESET " Choose a specific position modifier when prompted:\n");
    printf("   • " GREEN "1 (Beginning):" RESET " Add or remove from the very front of the train.\n");
    printf("   • " GREEN "2 (Middle):"    RESET " Add after a specific value, or remove a chosen value.\n");
    printf("   • " GREEN "3 (End):"       RESET " Add or remove from the very back of the train.\n");
    printf("   • " GREEN "Option 3 (View):" RESET " Always use this to print your current link map.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize dynamic system...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

void op(struct Node** h, int mode, int type) {
    if (mode == 2 && !*h) { 
        printf(RED "\n [!] UNDERFLOW: LINKED LIST EMPTY\n" RESET); 
        return; 
    }
    
    int val, target;
    struct Node *temp = *h, *prev = NULL;

    if (mode == 1) { // Insertion
        printf(AMBER " [?] Input Value: " RESET); scanf("%d", &val);
        struct Node* nn = create(val); if (!nn) return;

        if (type == 1 || !*h) { 
            nn->next = *h; *h = nn; 
        } else if (type == 3) { 
            while (temp->next) temp = temp->next; 
            temp->next = nn; 
        } else { 
            printf(AMBER " [?] After Value: " RESET); scanf("%d", &target);
            while (temp && temp->data != target) temp = temp->next;
            if (temp) { nn->next = temp->next; temp->next = nn; }
            else { printf(RED " [!] ERROR: %d NOT FOUND IN LIST\n" RESET, target); free(nn); return; }
        }
        printf(GREEN "  (+) Success: Node safely allocated to pointer offset sequence.\n" RESET);
    } else { // Deletion
        if (type == 1) { temp = *h; *h = (*h)->next; }
        else if (type == 3) { 
            while (temp->next) { prev = temp; temp = temp->next; }
            if (prev) prev->next = NULL; else *h = NULL;
        } else {
            printf(AMBER " [?] Delete Value: " RESET); scanf("%d", &target);
            while (temp && temp->data != target) { prev = temp; temp = temp->next; }
            if (temp) { if (prev) prev->next = temp->next; else *h = temp->next; }
            else { printf(RED " [!] ERROR: TARGET NOT LOCATED\n" RESET); return; }
        }
        printf(RED "  (-) Dropped: Memory cell unlinked -> node data [%d]\n" RESET, temp->data); 
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    int c, s;

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] SINGLY LINKED LIST CONTROL INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU]\n" RESET);
        printf("  1.  (+) Insertion Interface\n");
        printf("  2.  (-) Deletion Interface\n");
        printf("  3.  (#) Visualize Node Layout Sequence\n");
        printf("  4.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET); 
        scanf("%d", &c);

        if (c == 3) {
            printHeader("DYNAMIC REGISTER NODE VISUALIZATION");
            struct Node* t = head;
            printf("  ");
            if (!t) printf(RED "[ !! EMPTY MEMORY POOL REGISTER !! ]" RESET);
            while (t) { 
                printf(CYAN "[%d]" RESET " -> ", t->data); 
                t = t->next; 
            }
            printf(PURPLE "NULL\n" RESET);
        } else if (c == 4) {
            printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
            exit(0);
        } else if (c < 3 && c > 0) {
            printf(CYAN "  (>) Position Variable Allocation [1:Beg 2:Mid 3:End]: " RESET); 
            scanf("%d", &s);
            if (s >= 1 && s <= 3) {
                op(&head, c, s);
            } else {
                printf(RED " [!] WARNING: Sub-parameter allocation error.\n" RESET);
            }
        } else {
            printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}