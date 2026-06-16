#include <stdio.h>
#include <stdlib.h>

// ANSI Color Codes for high-tech look
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

int adj[20][20], visited[20], n = 0;

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  [#] %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" This interface provides cross-platform traversal pipelines for exploring connected networks:\n\n");
    printf(AMBER " [STEP 1]" RESET " Map your network via choice 1. Input dimensions followed by rows of 1s and 0s.\n");
    printf("           (e.g., A connection from Node 0 to Node 1 means a '1' at Row 0, Column 1).\n");
    printf(AMBER " [STEP 2]" RESET " Select an analysis path algorithm variant:\n");
    printf("   • " GREEN "Breadth-First Search (2):" RESET " Level-by-level neighborhood sweep. Relies on an explicit FIFO Queue ($O(V^2)$).\n");
    printf("   • " GREEN "Depth-First Search (3):  " RESET " Probes deep into a line of vertices first. Relies on recursion Stack ($O(V^2)$).\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize topological network graph matrix...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

// Depth First Search: Recursive exploration
void dfs(int v) {
    int i;
    printf(GREEN "[%d] " RESET, v);
    visited[v] = 1;
    for (i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i]) {
            dfs(i);
        }
    }
}

// Breadth First Search: Queue-based exploration
void bfs(int start) {
    int q[20], f = 0, r = 0, i, v;
    
    // Reset visited array specifically for BFS
    for (i = 0; i < n; i++) visited[i] = 0;
    
    q[r++] = start;
    visited[start] = 1;
    
    while (f < r) {
        v = q[f++];
        printf(GREEN "[%d] " RESET, v);
        for (i = 0; i < n; i++) {
            if (adj[v][i] && !visited[i]) {
                q[r++] = i;
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int choice, src, i, j;
    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] GRAPH EXPLORATION & ANALYSIS INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU] Matrix Scope: %d vertices initialized\n" RESET, n);
        printf("  1.  (+) Input Network Topology (Adjacency Matrix Mapping)\n");
        printf("  2.  (*) Execute Breadth-First Search Stream (BFS Queue)\n");
        printf("  3.  (*) Execute Depth-First Search Stream (DFS Stack)\n");
        printf("  4.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &choice) != 1) break; 
        if (choice == 4) {
            printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
            break;
        }

        if (choice == 1) {
            printHeader("GRAPH STRUCT INTERACTIVE DATA INITIALIZATION");
            printf(AMBER "  [?] Enter Total Number of Vertices: " RESET);
            scanf("%d", &n);
            if (n <= 0 || n > 20) {
                printf(RED " [!] ERROR: Target limits outside operational constraints (1-20).\n" RESET);
                n = 0;
                continue;
            }
            printf(AMBER "  [?] Input Matrix Configuration Layout Line-by-Line:\n" RESET);
            for (i = 0; i < n; i++) {
                printf("  Row %d: ", i);
                for (j = 0; j < n; j++) {
                    scanf("%d", &adj[i][j]);
                }
            }
            printf(GREEN "  (+) Success: Topography map successfully bound to adjacent registry.\n" RESET);
        } else if (n == 0) {
            printf(RED " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY\n" RESET);
        } else {
            printf(AMBER "  [?] Target Starting Vertex Key Address (0 to %d): " RESET, n - 1);
            scanf("%d", &src);
            
            if (src < 0 || src >= n) {
                printf(RED " [!] ERROR: Target index falls outside variable parameters.\n" RESET);
                continue;
            }

            // Reset visited array for the chosen traversal
            for (i = 0; i < n; i++) visited[i] = 0;
            
            if (choice == 2) {
                printHeader("BFS EXPLORATION SEQUENCE GENERATED");
                printf("  Sequence Path: ");
                bfs(src);
            } else if (choice == 3) {
                printHeader("DFS EXPLORATION SEQUENCE GENERATED");
                printf("  Sequence Path: ");
                dfs(src);
            } else {
                printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
            }
            printf("\n");
        }
    }
    return 0;
}