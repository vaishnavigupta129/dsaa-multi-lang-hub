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
    printf(" This matrix tests sorting complexities across four distinct computing behaviors:\n\n");
    printf(AMBER " [STEP 1]" RESET " Fire option 1 to allocate dynamic space and input raw registers.\n");
    printf(AMBER " [STEP 2]" RESET " Run a targeting execution strategy:\n");
    printf("   • " GREEN "Bubble Sort (2):   " RESET " Sweeps elements iteratively, floating highest values (O(N^2)).\n");
    printf("   • " GREEN "Selection Sort (3):" RESET " Scans looking for minimum elements, placing them at the front (O(N^2)).\n");
    printf("   • " GREEN "Insertion Sort (4):" RESET " Inserts values back into a growing sorted left sub-array frame (O(N^2)).\n");
    printf("   • " GREEN "Quick Sort (5):    " RESET " Logarithmic divide-and-conquer strategy using a pivot point (O(N \\log N)).\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize algorithmic sorting engine...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void bubble(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) swap(&a[j], &a[j + 1]);
}

void selection(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) if (a[j] < a[min]) min = j;
        swap(&a[min], &a[i]);
    }
}

void insertion(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int k = a[i], j = i - 1;
        while (j >= 0 && a[j] > k) { a[j + 1] = a[j]; j--; }
        a[j + 1] = k;
    }
}

int partition(int a[], int l, int h) {
    int p = a[h], i = l - 1;
    for (int j = l; j < h; j++) if (a[j] < p) swap(&a[++i], &a[j]);
    swap(&a[i + 1], &a[h]);
    return i + 1;
}

void quick(int a[], int l, int h) {
    if (l < h) {
        int pi = partition(a, l, h);
        quick(a, l, pi - 1); 
        quick(a, pi + 1, h);
    }
}

void display(int a[], int n) {
    printf(GREEN "  (+) Sorted Sequence: " RESET);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int choice, n = 0, *arr = NULL;

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] ALGORITHMIC SORTING SYSTEM INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU] Active Matrix: %d elements loaded\n" RESET, n);
        printf("  1.  (+) Load Data Buffer (Dynamic Array Input)\n");
        printf("  2.  (*) Execute Bubble Sort Strategy\n");
        printf("  3.  (*) Execute Selection Sort Strategy\n");
        printf("  4.  (*) Execute Insertion Sort Strategy\n");
        printf("  5.  (*) Execute Quick Sort Divide-and-Conquer\n");
        printf("  6.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &choice) != 1) break;
        if (choice == 6) {
            printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
            break;
        }

        if (choice == 1) {
            printf(AMBER "  [?] Array Size Limit Allocation: " RESET);
            if (scanf("%d", &n) != 1 || n <= 0) { 
                printf(RED " [!] ERROR: Target index falls outside variable parameters.\n" RESET); 
                n = 0; 
                continue; 
            }
            arr = (int*)realloc(arr, n * sizeof(int));
            printf(AMBER "  [?] Enter %d Matrix Elements: " RESET, n);
            for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
            printf(GREEN "  (+) Success: Matrix registers dynamically scaled and elements saved.\n" RESET);
            continue;
        }

        if (n == 0 || arr == NULL) {
            printf(RED " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY. RUN ACTION 1.\n" RESET);
            continue;
        }

        switch (choice) {
            case 2: printHeader("EXECUTING BUBBLE SORT STRATEGY"); bubble(arr, n); break;
            case 3: printHeader("EXECUTING SELECTION SORT STRATEGY"); selection(arr, n); break;
            case 4: printHeader("EXECUTING INSERTION SORT STRATEGY"); insertion(arr, n); break;
            case 5: printHeader("EXECUTING QUICK SORT DIVIDE-AND-CONQUER"); quick(arr, 0, n - 1); break;
            default: printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET); continue;
        }
        display(arr, n);
    }

    free(arr);
    return 0;
}