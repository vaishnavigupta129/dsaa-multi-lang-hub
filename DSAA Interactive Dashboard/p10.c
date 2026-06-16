#include <stdio.h>
#include <stdlib.h>

// ANSI Color Codes for high-tech look
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  [#] %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" Think of this system as an elite search database operating via two distinct algorithms.\n\n");
    printf(AMBER " [STEP 1]" RESET " Allocate data size and input parameters via Main Menu option 1.\n");
    printf(AMBER " [STEP 2]" RESET " Select an analytical search scan mode:\n");
    printf("   • " GREEN "Linear Search (2):" RESET " Sweeps elements one by one. Works seamlessly on unsorted blocks.\n");
    printf("   • " GREEN "Binary Search (3):" RESET " Divides sorted collections in half repeatedly. (Requires Sorted Inputs!)\n");
    printf("   • " GREEN "Logarithmic Scale:" RESET " While Linear takes up to N steps, Binary finds targets in log(N) cuts.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize data lookup search kernel...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

void find(int a[], int n, int k, int mode) {
    int l = 0, r = n - 1, pos = -1;
    
    if (mode == 2) { // Linear Search
        printHeader("EXECUTING LINEAR SYSTEM SCAN");
        for (int i = 0; i < n; i++) {
            if (a[i] == k) { 
                pos = i; 
                break; 
            }
        }
    } else { // Binary Search
        printHeader("EXECUTING BINARY REGISTER SCAN");
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (a[m] == k) { 
                pos = m; 
                break; 
            }
            if (a[m] < k) l = m + 1;
            else r = m - 1;
        }
    }

    if (pos != -1) {
        printf(GREEN "  (+) Success: Element %d safely located at array index [%d]\n" RESET, k, pos);
    } else {
        printf(RED " [!] ERROR: Query target match missing from active registers.\n" RESET);
    }
}

int main() {
    int n = 0, k, opt, a[100];

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] DATA SEARCH & RETRIEVAL INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU] Active Blocks: %d elements recorded\n" RESET, n);
        printf("  1.  (+) Input Main Array Block Data\n");
        printf("  2.  (*) Run Linear Search query sequence\n");
        printf("  3.  (*) Run Binary Search query sequence (Requires Sorted Data)\n");
        printf("  4.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &opt) != 1) break;
        if (opt == 4) {
            printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
            break;
        }

        switch (opt) {
            case 1:
                printf(AMBER "  [?] Array Size Limit Allocation: " RESET);
                if (scanf("%d", &n) != 1 || n <= 0) { 
                    printf(RED " [!] ERROR: Target index falls outside variable parameters.\n" RESET); 
                    n = 0; 
                    continue; 
                }
                printf(AMBER "  [?] Enter %d Sequential Values: " RESET, n);
                for (int i = 0; i < n; i++) scanf("%d", &a[i]);
                printf(GREEN "  (+) Success: Array registers updated with committed values.\n" RESET, n);
                break;

            case 2:
            case 3:
                if (n == 0) { 
                    printf(RED " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY\n" RESET); 
                } else {
                    printf(AMBER "  [?] Enter Search Target Value: " RESET); 
                    scanf("%d", &k);
                    find(a, n, k, opt);
                }
                break;

            default:
                printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}