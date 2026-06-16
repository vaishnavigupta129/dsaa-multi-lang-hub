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
    int data;
    struct Node *left, *right;
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
    printf(" Think of this system as an ordered hierarchical web branching from a parent Root node.\n\n");
    printf(AMBER " [STEP 1]" RESET " Populate values via Option 1. Smaller values split left, larger values split right.\n");
    printf(AMBER " [STEP 2]" RESET " Run deep-dive recursive stream traces across three dimensions:\n");
    printf("   • " GREEN "Pre-Order (1): " RESET " Evaluates parent hubs first, dipping into sub-branches next (Root->L->R).\n");
    printf("   • " GREEN "In-Order (2):  " RESET " Ascends sequentially from left to right, listing elements sorted (L->Root->R).\n");
    printf("   • " GREEN "Post-Order (3):" RESET " Sweeps leaves at the lowest layers before hitting upper hubs (L->R->Root).\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize hierarchical tree kernel...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

Node* insert(Node* root, int data) {
    if (!root) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) {
            printf(RED " [!] MEMORY ALLOCATION STRUCT FAULT\n" RESET);
            return NULL;
        }
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        printf(AMBER "  [!] Duplicate Flagged: Node value %d already exists within tree indexes.\n" RESET, data);
    }
    return root;
}

// m: 1=Pre-order, 2=In-order, 3=Post-order
void traverse(Node* root, int mode) {
    if (!root) return;

    if (mode == 1) printf(GREEN "%d " RESET, root->data);
    traverse(root->left, mode);
    if (mode == 2) printf(GREEN "%d " RESET, root->data);
    traverse(root->right, mode);
    if (mode == 3) printf(GREEN "%d " RESET, root->data);
}

int main() {
    Node* root = NULL;
    int choice, val;

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] BINARY SEARCH TREE CONTROL INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU]\n" RESET);
        printf("  1.  (+) Insert Node Variable Element\n");
        printf("  2.  (*) Execute Pre-Order Traversal Stream (Root->L->R)\n");
        printf("  3.  (*) Execute In-Order Traversal Stream (L->Root->R)\n");
        printf("  4.  (*) Execute Post-Order Traversal Stream (L->R->Root)\n");
        printf("  5.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &choice) != 1) break;
        if (choice == 5) {
            printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
            break;
        }

        switch (choice) {
            case 1:
                printf(AMBER "  [?] Enter Element Map Value: " RESET);
                if (scanf("%d", &val) == 1) {
                    root = insert(root, val);
                    printf(GREEN "  (+) Success: Node location calculated and variable saved.\n" RESET);
                }
                break;
            case 2:
                printHeader("PRE-ORDER SEQUENCE (Root-L-R)");
                if (!root) printf(RED "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" RESET);
                else { printf("  "); traverse(root, 1); printf("\n"); }
                break;
            case 3:
                printHeader("IN-ORDER SEQUENCE (L-Root-R)");
                if (!root) printf(RED "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" RESET);
                else { printf("  "); traverse(root, 2); printf("\n"); }
                break;
            case 4:
                printHeader("POST-ORDER SEQUENCE (L-R-Root)");
                if (!root) printf(RED "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" RESET);
                else { printf("  "); traverse(root, 3); printf("\n"); }
                break;
            default:
                printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}