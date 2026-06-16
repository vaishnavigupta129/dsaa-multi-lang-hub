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

#define M 20  // Increased threshold buffer
#define INF 999

int g[M][M], V = 0;

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  [#] %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" This interface computes single-source shortest path segments across positive cost profiles:\n\n");
    printf(AMBER " [STEP 1]" RESET " Choice 1 maps vertices. Supply edge sequences as: [Src] [Dst] [Weight].\n");
    printf("           Terminate entry streams safely by giving '-1 -1 -1'.\n");
    printf(AMBER " [STEP 2]" RESET " Run a shortest path trace (Choice 3) and select your target source node.\n");
    printf("           Dijkstra's greedy expansion relaxes edge paths ($O(V^2)$) to map absolute routing structures.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize routing core matrix...");
    while(getchar() != '\n'); 
    getchar();
}

void path(int curr, int p[]) {
    if (p[curr] == -1) { 
        printf("%d", curr); 
        return; 
    }
    path(p[curr], p); 
    printf(" -> %d", curr);
}

void dijkstra() {
    int src, dist[M], p[M]; 
    bool vis[M] = {false};
    
    printHeader("DIJKSTRA SHORTEST PATH GENERATOR");
    printf(AMBER "  [?] Select Starting Source Node (0 to %d): " RESET, V - 1); 
    scanf("%d", &src);
    if (src < 0 || src >= V) {
        printf(RED "  [!] ERROR: Selection falls outside boundaries.\n" RESET);
        return;
    }

    for (int i = 0; i < V; i++) { 
        dist[i] = INF; 
        p[i] = -1; 
    }
    dist[src] = 0;

    for (int c = 0; c < V - 1; c++) {
        int min = INF, u = -1;
        for (int v = 0; v < V; v++) {
            if (!vis[v] && dist[v] <= min) { 
                min = dist[v]; 
                u = v; 
            }
        }
        if (u == -1 || min == INF) break;
        vis[u] = true;
        
        for (int v = 0; v < V; v++) {
            if (!vis[v] && g[u][v] && g[u][v] != INF && dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v]; 
                p[v] = u;
            }
        }
    }

    printf(CYAN "\n  [ROUTE] Optimization Matrix Output:\n" RESET);
    printf("  -----------------------------------------------\n");
    printf("  Dest\t\tDist\t\tPath Sequence\n");
    printf("  -----------------------------------------------\n");
    for (int i = 0; i < V; i++) {
        printf("  [%d]\t\t", i);
        if (dist[i] == INF) {
            printf(RED "INF\t\tNo Path Available\n" RESET);
        } else { 
            printf(GREEN "%d\t\t" RESET, dist[i]); 
            path(i, p); 
            printf("\n"); 
        }
    }
    printf("  -----------------------------------------------\n");
}

void create() {
    int o, d, w;
    printHeader("GRAPH DATA INITIALIZATION");
    printf(AMBER "  [?] Total Vertices Allocation (Max %d): " RESET, M); 
    scanf("%d", &V);
    if (V <= 0 || V > M) {
        printf(RED "  [!] ERROR: Input outside allocated constraints (1-%d).\n" RESET, M);
        V = 0;
        return;
    }
    
    for (int i = 0; i < V; i++) 
        for (int j = 0; j < V; j++) g[i][j] = (i == j) ? 0 : INF;
        
    printf(AMBER "  [?] Input Directed Edges [Format: Src Dest Wt] (-1 -1 -1 to stop):\n" RESET);
    while (scanf("%d %d %d", &o, &d, &w) && o != -1) {
        if (o >= 0 && o < V && d >= 0 && d < V) {
            g[o][d] = w;
        } else {
            printf(RED "  [!] Edge bounds violation rejected.\n" RESET);
        }
    }
    printf(GREEN "  (+) Success: Topography cost metrics securely saved.\n" RESET);
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
    printf("     [M] DIJKSTRA SHORTEST PATH INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU]\n" RESET);
        printf("  1.  (+) Input Graph Edge Networks\n");
        printf("  2.  (#) Print Cost Adjacency Matrix Map\n");
        printf("  3.  (*) Calculate Shortest Path Solutions\n");
        printf("  4.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &ch) != 1) break;
        
        if (ch == 1) {
            create();
        } else if (ch == 2) {
            if (V == 0) {
                printf(RED " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY\n" RESET);
                continue;
            }
            printHeader("COST ADJACENCY MATRIX ROUTING LOOKUP");
            for(int i = 0; i < V; i++) { 
                printf("  ");
                for(int j = 0; j < V; j++) {
                    if (g[i][j] == INF) printf(RED "INF\t" RESET);
                    else printf(GREEN "%d\t" RESET, g[i][j]);
                }
                printf("\n"); 
            }
        } else if (ch == 3) {
            if (V == 0) {
                printf(RED " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY\n" RESET);
                continue;
            }
            dijkstra();
        } else if (ch == 4) {
            printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
            exit(0);
        } else {
            printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}