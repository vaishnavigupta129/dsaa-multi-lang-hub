#include <stdio.h>
#include <stdlib.h>

// ANSI Color Codes for high-tech look
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

typedef struct Node {
    int coeff, exp;
    struct Node* next;
} Node;

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  [#] %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" Think of this system as a dynamic warehouse storing mathematical expressions.\n\n");
    printf(AMBER " [STEP 1]" RESET " Populate Poly-1 or Poly-2 via options 1 and 2 by inputting elements.\n");
    printf(AMBER " [STEP 2]" RESET " Appreciate how sorted tracking operates under the hood:\n");
    printf("   • " GREEN "Sorted Array Links:" RESET " Elements are auto-sorted in descending order of exponents.\n");
    printf("   • " GREEN "Coefficient Merger:" RESET " Entering matching exponents merges their coefficients instantly.\n");
    printf("   • " GREEN "Summation Kernel:" RESET "   Option 4 evaluates, merges, and presents the calculated results.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize polynomial computational kernel...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

void insert(Node** head, int c, int e) {
    if (c == 0) return; // Ignore zero coefficients
    
    // Traverse to the correct sorted position (descending exponents)
    while (*head && (*head)->exp > e) {
        head = &(*head)->next;
    }

    // If exponent already exists, merge coefficients
    if (*head && (*head)->exp == e) {
        (*head)->coeff += c;
    } else {
        // Otherwise, create a new term node
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) return;
        newNode->coeff = c;
        newNode->exp = e;
        newNode->next = *head;
        *head = newNode;
    }
}

void printPolynomial(Node* head, char* label) {
    if (!head) {
        printf(RED "  [!] %s: EMPTY REGISTER POOL\n" RESET, label);
        return;
    }
    printf(CYAN "  [%s]: " RESET, label);
    while (head) {
        printf(GREEN "%dx^%d" RESET, head->coeff, head->exp);
        if (head->next) printf(AMBER " + " RESET);
        head = head->next;
    }
    printf("\n");
}

Node* addPolynomials(Node* p1, Node* p2) {
    Node* result = NULL;
    // Insert all terms from P1 into Result
    for (Node* curr = p1; curr; curr = curr->next) {
        insert(&result, curr->coeff, curr->exp);
    }
    // Insert all terms from P2 into Result (merging happens automatically in insert)
    for (Node* curr = p2; curr; curr = curr->next) {
        insert(&result, curr->coeff, curr->exp);
    }
    return result;
}

int main() {
    Node *p1 = NULL, *p2 = NULL;
    int choice, c, e;

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] POLYNOMIAL COMPUTATION INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU]\n" RESET);
        printf("  1.  (+) Add Algebraic Term to POLY-1\n");
        printf("  2.  (+) Add Algebraic Term to POLY-2\n");
        printf("  3.  (#) Visualize Tracked Expression Maps\n");
        printf("  4.  (=) Calculate Summation Product (P1 + P2)\n");
        printf("  5.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &choice) != 1) break;
        if (choice == 5) {
            printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
            break;
        }

        switch (choice) {
            case 1:
            case 2:
                printf(AMBER "  [?] Enter Coefficient and Exponent [Format: c e]: " RESET);
                if (scanf("%d %d", &c, &e) == 2) {
                    insert(choice == 1 ? &p1 : &p2, c, e);
                    printf(GREEN "  (+) Success: Linked term securely placed in polynomial node string.\n" RESET);
                }
                break;
            case 3:
                printHeader("POLYNOMIAL DATA STRUCT STORAGE");
                printPolynomial(p1, "POLY-1");
                printPolynomial(p2, "POLY-2");
                break;
            case 4:
                if (!p1 && !p2) {
                    printf(RED " [!] ERROR: OPERATIONAL EXPRESSION ARRAYS ARE COMPLETELY EMPTY\n" RESET);
                } else {
                    printHeader("ALGEBRAIC SUMMATION EVALUATION RESULT");
                    Node* res = addPolynomials(p1, p2);
                    printPolynomial(res, "RESULT");
                }
                break;
            default:
                printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}