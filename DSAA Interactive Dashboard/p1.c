#include <stdio.h>
#include <stdlib.h>

// ANSI Color Codes for high-tech look
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

#define MAX 100
int a[MAX], n = 0, total;

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  [#] %s\n", title);
    printf("==================================================\n" RESET);
}

// FIXED: Cleaned buffer catch to wait perfectly for keypress
void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" Think of this program as a digital shelf with numbered slots.\n\n");
    printf(AMBER " [STEP 1]" RESET " Define how many total slots you want to use today.\n");
    printf(AMBER " [STEP 2]" RESET " Use the menu numbers below to manage your data:\n");
    printf("   • " GREEN "Option 1 (Insert):" RESET " Type a value, then pick a slot (0, 1, 2...).\n");
    printf("   • " GREEN "Option 6 (View):" RESET "   Always use this to see your current shelf map.\n");
    printf("   • " GREEN "Option 2 (Delete):" RESET " Remove an item by typing its slot index number.\n");
    printf("   • " GREEN "Option 5 (Sort):" RESET "   Organizes scrambled numbers from lowest to highest.\n");
    printf("   • " GREEN "Option 3/4 (Search):" RESET "Finds what slot index a number is hiding in.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize system config...");
    
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Robust buffer purge
}

int is_empty() {
    if (n <= 0) { 
        printf(RED "\n [!] UNDERFLOW: Operational array contains zero elements.\n" RESET); 
        return 1; 
    }
    return 0;
}

// Simple internal helper to check if array layout is sorted
int is_sorted() {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i+1]) return 0;
    }
    return 1;
}

void insert() {
    int v, p, i;
    if (n >= MAX || n >= total) { 
        printf(RED "\n [!] OVERFLOW: Allocation boundary limit reached.\n" RESET); 
        return; 
    }
    printf(AMBER " [?] Enter Value: " RESET); scanf("%d", &v);
    printf(AMBER " [?] Enter Position (0 to %d): " RESET, n); scanf("%d", &p);

    if (p < 0 || p > n) { 
        printf(RED " [!] ERROR: Target index falls outside variable parameters.\n" RESET); 
        return; 
    }

    for (i = n++; i > p; i--) a[i] = a[i-1];
    a[p] = v;
    printf(GREEN "  (+) Success: Element safely committed to index register.\n" RESET);
}

void delete_item() {
    int p, i;
    if (is_empty()) return;
    printf(AMBER " [?] Index to Delete (0 to %d): " RESET, n - 1); scanf("%d", &p);

    if (p < 0 || p >= n) { 
        printf(RED " [!] ERROR: Target index falls outside variable parameters.\n" RESET); 
        return; 
    }

    int removed = a[p];
    for (i = p; i < --n; i++) a[i] = a[i+1];
    printf(RED "  (-) Dropped: Memory cell released -> element [%d]\n" RESET, removed);
}

void search(int mode) {
    if (is_empty()) return;
    int v, i, found = -1;
    printf(AMBER " [?] Search Value: " RESET); scanf("%d", &v);

    if (mode == 1) { // Linear Search
        for (i = 0; i < n; i++) if (a[i] == v) { found = i; break; }
    } else { // Binary Search
        // FIXED: Safeguard check against unsorted query structures
        if (!is_sorted()) {
            printf(AMBER " [!] NOTICE: Memory block unsorted. Initializing fallback logic...\n" RESET);
            // Fallback to linear search so the user doesn't get a corrupt "Not Found" error
            for (i = 0; i < n; i++) if (a[i] == v) { found = i; break; }
        } else {
            int low = 0, high = n - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2; // FIXED: Prevent overflow architecture bugs
                if (a[mid] == v) { found = mid; break; }
                (a[mid] < v) ? (low = mid + 1) : (high = mid - 1);
            }
        }
    }

    if (found != -1) printf(GREEN "  (*) Located: Element matching query found at index [%d]\n" RESET, found);
    else printf(RED " [!] ERROR: Query target match missing from active registers.\n" RESET);
}

void bubble_sort() {
    if (is_empty()) return;
    int i, j, t;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (a[j] > a[j+1]) { t = a[j]; a[j] = a[j+1]; a[j+1] = t; }
    printf(GREEN "  (^) Sort Complete: Active registry block sequences reordered.\n" RESET);
}

void display() {
    printHeader("STATIC DATA ARRAY VISUALIZATION");
    if (n == 0) {
        printf(RED "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" RESET);
        return;
    }
    printf(CYAN " INDEX : " RESET);
    for (int i = 0; i < n; i++) printf("%-5d", i);
    printf(CYAN "\n DATA  : " RESET);
    for (int i = 0; i < n; i++) printf("[%d]  ", a[i]);
    printf("\n");
}

int main() {
    int choice;
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] STATIC ARRAY CONTROL INTERFACE [M]\n");
    printf("==================================================\n" RESET);
    
    printf(AMBER " [?] Define Max Target Capacity: " RESET);
    scanf("%d", &total);

    while (1) {
        printf(CYAN "\n [SYSTEM STATUS] Active Blocks: %d/%d entries utilized\n" RESET, n, total);
        printf("  1.  (+) Insert Element\n");
        printf("  2.  (-) Delete Element\n");
        printf("  3.  (*) Run Linear Search query\n");
        printf("  4.  (*) Run Binary Search query\n");
        printf("  5.  (^) Run Structural Bubble Sort\n");
        printf("  6.  (#) Traverse Structural Visual\n");
        printf("  7.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &choice) != 1) {
            // Clear input stream if strings/characters accidentally get passed
            while (getchar() != '\n');
            printf(RED " [!] ERROR: Invalid numeric token input.\n" RESET);
            continue;
        }

        switch (choice) {
            case 1: insert(); break;
            case 2: delete_item(); break;
            case 3: search(1); break;
            case 4: search(2); break;
            case 5: bubble_sort(); break;
            case 6: display(); break;
            case 7: 
                printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
                return 0;
            default: printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}