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

#define MAX 6
#define INF 999

typedef struct { int u, v, w; } Edge;
int graph[MAX][MAX], mst[MAX][MAX], V = 0, E_cnt = 0;
Edge elist[MAX * MAX];
bool mst_ok = false;

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  ◆ %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" This engine tracks Minimum Spanning Tree (MST) generations via greedy optimizations:\n\n");
    printf(AMBER " [STEP 1]" RESET " Choice 1 maps vertices. Supply edge sequences as: [Src] [Dst] [Weight].\n");
    printf("           Terminate entry streams safely by giving '-1 -1 -1'.\n");
    printf(AMBER " [STEP 2]" RESET " Run a minimum path optimization track:\n");
    printf("   • " GREEN "Prim's Algorithm (4):   " RESET " Grows the tree from a single starting root node, adding the cheapest global connection vertex step-by-step.\n");
    printf("   • " GREEN "Kruskal's Algorithm (5):" RESET " Sorts all network edges by raw weight and links independent forest structures via Disjoint Set Union (DSU).\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize structural optimization matrix...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

int cmp(const void* a, const void* b) { return ((Edge*)a)->w - ((Edge*)b)->w; }
int find(int i, int p[]) { return (p[i] == i) ? i : (p[i] = find(p[i], p)); }

void create() {
    int o, d, w;
    printHeader("GRAPH INITIALIZATION TOOL");
    printf(AMBER " [?] Enter number of vertices (Max %d): " RESET, MAX);
    scanf("%d", &V);
    E_cnt = mst_ok = 0;

    for (int i = 0; i < V; i++) 
        for (int j = 0; j < V; j++) graph[i][j] = (i == j) ? 0 : INF;

    printf(AMBER "\n [!] Enter edges as: [Origin] [Dest] [Weight]\n" RESET);
    printf(CYAN "     (Type '-1 -1 -1' to finalize setup)\n\n" RESET);
    while (1) {
        printf("  ➔ ");
        scanf("%d %d %d", &o, &d, &w);
        if (o == -1) break;
        if (o >= 0 && o < V && d >= 0 && d < V && o != d) {
            graph[o][d] = graph[d][o] = w;
            elist[E_cnt++] = (Edge){o, d, w};
            printf(GREEN "    ▲ Edge Saved: %d <-> %d (w: %d)\n" RESET, o, d, w);
        } else {
            printf(RED "    ▼ [!] Invalid node IDs or loop self-connection skipped.\n" RESET);
        }
    }
    printf(GREEN "\n [■] SUCCESS: Graph captured with %d active edges.\n" RESET, E_cnt);
}

void add_mst_edge(int u, int v, int w, int *edges, int *tot) {
    printf(CYAN "  (Node %d) <==== [w: %2d] ====> (Node %d)\n" RESET, u, w, v);
    mst[u][v] = mst[v][u] = w;
    (*tot) += w; (*edges)++;
}

void prim() {
    if (!V) { printf(RED " [!] EMPTY DATA: Please initialize a graph first.\n" RESET); return; }
    printHeader("PRIM'S MINIMUM SPANNING TREE");
    for (int i = 0; i < V; i++) for (int j = 0; j < V; j++) mst[i][j] = 0;

    bool sel[MAX] = {true};
    int edges = 0, tot = 0;

    while (edges < V - 1) {
        int min = INF, x = -1, y = -1;
        for (int i = 0; i < V; i++) if (sel[i])
            for (int j = 0; j < V; j++)
                if (!sel[j] && graph[i][j] < min) { min = graph[i][j]; x = i; y = j; }
        if (min == INF) break;
        sel[y] = true;
        add_mst_edge(x, y, min, &edges, &tot);
    }
    if (edges < V - 1) printf(RED "\n [▼] ANALYSIS FAIL: Network graph is disconnected!\n" RESET);
    else { printf(GREEN "\n [■] MST GENERATION SUCCESS | Total Cost Weight: %d\n" RESET, tot); mst_ok = true; }
}

void kruskal() {
    if (!V) { printf(RED " [!] EMPTY DATA: Please initialize a graph first.\n" RESET); return; }
    printHeader("KRUSKAL'S MINIMUM SPANNING TREE");
    for (int i = 0; i < V; i++) for (int j = 0; j < V; j++) mst[i][j] = 0;

    int p[MAX], edges = 0, tot = 0;
    for (int i = 0; i < V; i++) p[i] = i;
    qsort(elist, E_cnt, sizeof(Edge), cmp);

    for (int i = 0; i < E_cnt && edges < V - 1; i++) {
        int ru = find(elist[i].u, p), rv = find(elist[i].v, p);
        if (ru != rv) { p[ru] = rv; add_mst_edge(elist[i].u, elist[i].v, elist[i].w, &edges, &tot); }
    }
    if (edges < V - 1) printf(RED "\n [▼] ANALYSIS FAIL: Network graph is disconnected!\n" RESET);
    else { printf(GREEN "\n [■] MST GENERATION SUCCESS | Total Cost Weight: %d\n" RESET, tot); mst_ok = true; }
}

void draw_tree(int n, int parent, int depth, bool last) {
    for (int i = 0; i < depth - 1; i++) printf("  | ");
    if (depth > 0) printf("  +-- ");
    if (parent == -1) printf(GREEN "[Root Node %d]\n" RESET, n); 
    else printf(CYAN "Node %d" AMBER " (w:%d)\n" RESET, n, mst[parent][n]);

    int ch[MAX], c_cnt = 0;
    for (int i = 0; i < V; i++) if (mst[n][i] && i != parent) ch[c_cnt++] = i;
    for (int i = 0; i < c_cnt; i++) draw_tree(ch[i], n, depth + 1, i == c_cnt - 1);
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
    printf("     ■ CRITICAL MST CORE ENGINE & ANALYSIS ■\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [SYSTEM STATUS] Active Vertices: %d/%d | Active Edges: %d\n" RESET, V, MAX, E_cnt);
        printf("  1.  [+] Create Network Graph\n");
        printf("  2.  [#] Render Adjacency Matrix\n");
        printf("  3.  [*] Render Structural Map\n");
        printf("  4.  [^] Execute Prim's Path Mapping\n");
        printf("  5.  [^] Execute Kruskal's Path Mapping\n");
        printf("  6.  [$] Draw Hierarchical Tree Visual\n");
        printf("  7.  [X] Terminate Execution Engine\n");
        printf(AMBER " >> Select Target Action Option: " RESET);
        
        if (scanf("%d", &ch) != 1 || ch == 7) {
            printf(RED "\n [!] SHUTTING DOWN CORE SYSTEM OPERATIONS...\n" RESET);
            break;
        }

        if (ch == 1) create();
        else if (ch == 2 || ch == 3) {
            if (!V) { printf(RED " [!] ACCESS REJECTED: Network matrix layer is currently empty.\n" RESET); continue; }
            printHeader(ch == 2 ? "MATRIX DATA REPRESENTATION" : "GRAPH CONSOLIDATION MAP");
            for (int i = 0; i < V; i++) {
                if (ch == 3) printf(GREEN " (Node %d) " RESET, i);
                for (int j = 0; j < V; j++) {
                    if (ch == 2) {
                        if (graph[i][j] == INF) printf(RED " INF " RESET);
                        else printf(CYAN " %3d " RESET, graph[i][j]);
                    }
                    else if (graph[i][j] && graph[i][j] != INF) printf(CYAN " ==(%d)==> " RESET "[%d]", graph[i][j], j);
                }
                printf("\n");
            }
        } 
        else if (ch == 4) prim();
        else if (ch == 5) kruskal();
        else if (ch == 6) {
            if (mst_ok) { 
                printHeader("HIERARCHICAL TREE ARCHITECTURE"); 
                draw_tree(0, -1, 0, true); 
            } else {
                printf(RED " [!] CRITICAL ERROR: Active MST profile data missing. Run option 4 or 5 first.\n" RESET);
            }
        } else {
            printf(RED " [!] WARNING: Selection outside variable parameters.\n" RESET);
        }
    }
    return 0;
}