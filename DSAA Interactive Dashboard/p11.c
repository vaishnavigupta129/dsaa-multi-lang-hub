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
    printf(" This system provides a unified interface for full-lifecycle Binary Search Tree maintenance:\n\n");
    printf(AMBER " [STEP 1]" RESET " Allocate integers via option 1 to grow your tree dynamically on the heap.\n");
    printf(AMBER " [STEP 2]" RESET " Run a rapid binary query search via option 2 to check node existence.\n");
    printf(AMBER " [STEP 3]" RESET " Remove any element via option 3, which handles three unique deletion states:\n");
    printf("   • " GREEN "Leaf Node:" RESET " Simply freed and replaced with null.\n");
    printf("   • " GREEN "Single-Child Node:" RESET " Drops the target and bypass-links directly to its only child.\n");
    printf("   • " GREEN "Dual-Child Node:" RESET " Replaces values with its structural in-order successor, then deletes.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize operational management kernel...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

// Unified operation function: mode 1=Insert, 2=Search, 3=Delete
Node* operate(Node* root, int val, int mode, int *found) {
    if (!root) {
        if (mode != 1) return NULL; // Not found for search/delete
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) return NULL;
        newNode->data = val;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (val < root->data) {
        root->left = operate(root->left, val, mode, found);
    } else if (val > root->data) {
        root->right = operate(root->right, val, mode, found);
    } else {
        // Target node located
        *found = 1;
        if (mode == 3) { // Deletion Logic
            // Case 1 & 2: One child or Leaf
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                free(root);
                return temp;
            }
            // Case 3: Two children (Find In-order Successor)
            Node* successor = root->right;
            while (successor->left) successor = successor->left;
            root->data = successor->data;
            root->right = operate(root->right, successor->data, 3, found);
        }
    }
    return root;
}

// Simple in-order visualization to check tree state
void visualize(Node* root) {
    if (!root) return;
    visualize(root->left);
    printf(CYAN "[%d] " RESET, root->data);
    visualize(root->right);
}

int main() {
    Node* root = NULL;
    int choice, val, found;

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] BST ADVANCED MANAGEMENT INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU]\n" RESET);
        printf("  1.  (+) Insert Node Variable Element\n");
        printf("  2.  (?) Query Scan Address Index (Search Target)\n");
        printf("  3.  (-) Delete Target Node Link (Re-balance Layout)\n");
        printf("  4.  (#) Traverse In-Order Visual Layout Sequence\n");
        printf("  5.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &choice) != 1) break;
        if (choice == 5) {
            printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
            break;
        }

        if (choice >= 1 && choice <= 3) {
            if (!root && choice > 1) {
                printf(RED " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY\n" RESET);
                continue;
            }
            printf(AMBER "  [?] Target Allocation Value: " RESET);
            scanf("%d", &val);
            found = 0;

            if (choice == 1) {
                root = operate(root, val, 1, &found);
                printf(GREEN "  (+) Success: Dynamic structural node safely allocated to heap.\n" RESET);
            } else if (choice == 2) {
                operate(root, val, 2, &found);
                if (found) printf(GREEN "  (*) Located: Query target key match [%d] verified inside tree registry.\n" RESET, val);
                else printf(RED "  [!] Missing: Query target match [%d] missing from active pointers.\n" RESET, val);
            } else {
                root = operate(root, val, 3, &found);
                if (found) printf(RED "  (-) Dropped: Node pointer [%d] removed and address chain re-linked.\n" RESET, val);
                else printf(RED "  [!] ERROR: Target index falls outside available balance parameters.\n" RESET);
            }
        } else if (choice == 4) {
            printHeader("BST IN-ORDER TRAVERSAL (SORTED MATRIX VIEW)");
            if (!root) printf(RED "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] " RESET);
            else { printf("  "); visualize(root); }
            printf("\n");
        } else {
            printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}