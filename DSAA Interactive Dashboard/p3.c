#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ANSI Color Codes for high-tech look
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

#define MAX 5
int stack[MAX], top = -1;

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  ◆ %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" Think of this program as a vertical stack of dinner plates.\n\n");
    printf(AMBER " [STEP 1]" RESET " Pick an option from the control menu below.\n");
    printf(AMBER " [STEP 2]" RESET " Understand the foundational LIFO rules:\n");
    printf("   • " GREEN "Option 1 (Push):" RESET "  Slide a new item onto the very top of the stack.\n");
    printf("   • " GREEN "Option 2 (Pop):" RESET "   Remove whichever item is currently resting on top.\n");
    printf("   • " GREEN "Option 3 (Peep):" RESET  "  Sneak a glance at the top item without removing it.\n");
    printf("   • " GREEN "Option 4 (View):" RESET  "  Draws a vertical diagram of your current storage.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize structural memory pool...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

int is_full() { return top == MAX - 1; }
int is_empty() { return top == -1; }

void push() {
    int v;
    if (is_full()) {
        printf(RED "\n [▼] OVERFLOW Error: Stack memory allocation limits reached.\n" RESET);
    } else {
        printf(AMBER " [?] Input Value to Push: " RESET);
        scanf("%d", &v);
        stack[++top] = v;
        printf(GREEN "  ▲ Success: Value %d safely committed to address offset.\n" RESET, v);
    }
}

void pop() {
    if (is_empty()) {
        printf(RED "\n [▼] UNDERFLOW Error: Operational array contains zero elements.\n" RESET);
    } else {
        int v = stack[top--];
        printf(RED "  ▼ Dropped: Memory cell released -> element [%d]\n" RESET, v);
    }
}

void peep() {
    if (is_empty()) {
        printf(RED "\n [!] STACK EMPTY: Registers have no top address target.\n" RESET);
    } else {
        printf(CYAN "  ➔ Current Pointer Position Element: [%d]\n" RESET, stack[top]);
    }
}

void traverse() {
    printHeader("CORE REGISTRY MEMORY VISUALIZATION");
    if (is_empty()) {
        printf(RED "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" RESET);
    } else {
        for (int i = top; i >= 0; i--) {
            if (i == top)
                printf(GREEN "     | %-3d |  ➔ [TOP POINTER]\n" RESET, stack[i]);
            else
                printf(CYAN "     | %-3d |\n" RESET, stack[i]);
            printf("     +-----+\n");
        }
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
    printf("     ■ LIFO STORAGE ARRAY CONTROL SYSTEM ■\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [SYSTEM STATUS] Active Allocations: %d/%d bytes max\n" RESET, top + 1, MAX);
        printf("  1.  [+] Push (Insert Value Element)\n");
        printf("  2.  [-] Pop (Destroy & Return Element)\n");
        printf("  3.  [*] Peep (Read Top Vector Variable)\n");
        printf("  4.  [#] Traverse Structural Visual\n");
        printf("  5.  [$] Run Full Hardware Diagnostics Status\n");
        printf("  6.  [X] Terminate Control Kernel Execution\n");
        printf(AMBER " >> Select Target Action Option: " RESET);
        
        if (scanf("%d", &ch) != 1 || ch == 6) {
            printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
            break;
        }

        switch (ch) {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: peep(); break;
            case 4: traverse(); break;
            case 5: 
                printHeader("HARDWARE ENVIRONMENT DIAGNOSTIC REPORT");
                printf("  ■ Stack Register Allocation Capacity:  %d cells\n", MAX);
                printf("  ■ Active Allocated Cell Count:        %d cells\n", top + 1);
                printf("  ■ Boolean Condition Register Empty:   %s\n", is_empty() ? RED "TRUE (1)" RESET : GREEN "FALSE (0)" RESET);
                printf("  ■ Boolean Condition Register Full:    %s\n", is_full() ? RED "TRUE (1)" RESET : GREEN "FALSE (0)" RESET);
                break;
            default: 
                printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}