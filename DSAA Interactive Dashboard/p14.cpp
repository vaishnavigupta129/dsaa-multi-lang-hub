#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>

#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

const int INF = 999;

struct Edge {
    int u, v, w;
};

int V = 0;
std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> mst;
std::vector<Edge> elist;
bool mst_ok = false;

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  ◆ " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " This engine tracks Minimum Spanning Tree (MST) generations via greedy optimizations:\n\n"
              << AMBER << " [STEP 1]" << RESET << " Choice 1 maps vertices. Supply edge sequences as: [Src] [Dst] [Weight].\n"
              << "           Terminate entry streams safely by giving '-1 -1 -1'.\n"
              << AMBER << " [STEP 2]" << RESET << " Run a minimum path optimization track:\n"
              << "   • " << GREEN << "Prim's Algorithm (4):   " << RESET << " Grows the tree from a single starting root node, adding the cheapest global connection vertex step-by-step.\n"
              << "   • " << GREEN << "Kruskal's Algorithm (5):" << RESET << " Sorts all network edges by raw weight and links independent forest structures via Disjoint Set Union (DSU).\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize structural optimization matrix...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

int find_set(int i, std::vector<int>& p) {
    return (p[i] == i) ? i : (p[i] = find_set(p[i], p));
}

void create() {
    int o, d, w;
    printHeader("GRAPH INITIALIZATION TOOL");
    std::cout << AMBER << " [?] Enter number of vertices: " << RESET;
    std::cin >> V;
    mst_ok = false;
    elist.clear();

    graph.assign(V, std::vector<int>(V, INF));
    for (int i = 0; i < V; i++) graph[i][i] = 0;
    mst.assign(V, std::vector<int>(V, 0));

    std::cout << AMBER << "\n [!] Enter edges as: [Origin] [Dest] [Weight]\n" << RESET
              << CYAN << "     (Type '-1 -1 -1' to finalize setup)\n\n" << RESET;
    while (true) {
        std::cout << "  ➔ ";
        std::cin >> o >> d >> w;
        if (o == -1) break;
        if (o >= 0 && o < V && d >= 0 && d < V && o != d) {
            graph[o][d] = graph[d][o] = w;
            elist.push_back({o, d, w});
            std::cout << GREEN << "    ▲ Edge Saved: " << o << " <-> " << d << " (w: " << w << ")\n" << RESET;
        } else {
            std::cout << RED << "    ▼ [!] Invalid node IDs or loop self-connection skipped.\n" << RESET;
        }
    }
    std::cout << GREEN << "\n [■] SUCCESS: Graph captured with " << elist.size() << " active edges.\n" << RESET;
}

void add_mst_edge(int u, int v, int w, int& edges, int& tot) {
    std::cout << CYAN << "  (Node " << u << ") <==== [w: " << w << "] ====> (Node " << v << ")\n" << RESET;
    mst[u][v] = mst[v][u] = w;
    tot += w;
    edges++;
}

void prim() {
    if (!V) { std::cout << RED << " [!] EMPTY DATA: Please initialize a graph first.\n" << RESET; return; }
    printHeader("PRIM'S MINIMUM SPANNING TREE");
    mst.assign(V, std::vector<int>(V, 0));

    std::vector<bool> sel(V, false);
    sel[0] = true;
    int edges = 0, tot = 0;

    while (edges < V - 1) {
        int min = INF, x = -1, y = -1;
        for (int i = 0; i < V; i++) {
            if (sel[i]) {
                for (int j = 0; j < V; j++) {
                    if (!sel[j] && graph[i][j] < min) {
                        min = graph[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }
        if (min == INF) break;
        sel[y] = true;
        add_mst_edge(x, y, min, edges, tot);
    }
    if (edges < V - 1) {
        std::cout << RED << "\n [▼] ANALYSIS FAIL: Network graph is disconnected!\n" << RESET;
    } else {
        std::cout << GREEN << "\n [■] MST GENERATION SUCCESS | Total Cost Weight: " << tot << "\n" << RESET;
        mst_ok = true;
    }
}

void kruskal() {
    if (!V) { std::cout << RED << " [!] EMPTY DATA: Please initialize a graph first.\n" << RESET; return; }
    printHeader("KRUSKAL'S MINIMUM SPANNING TREE");
    mst.assign(V, std::vector<int>(V, 0));

    std::vector<int> p(V);
    for (int i = 0; i < V; i++) p[i] = i;

    std::sort(elist.begin(), elist.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    int edges = 0, tot = 0;
    for (size_t i = 0; i < elist.size() && edges < V - 1; i++) {
        int ru = find_set(elist[i].u, p);
        int rv = find_set(elist[i].v, p);
        if (ru != rv) {
            p[ru] = rv;
            add_mst_edge(elist[i].u, elist[i].v, elist[i].w, edges, tot);
        }
    }
    if (edges < V - 1) {
        std::cout << RED << "\n [▼] ANALYSIS FAIL: Network graph is disconnected!\n" << RESET;
    } else {
        std::cout << GREEN << "\n [■] MST GENERATION SUCCESS | Total Cost Weight: " << tot << "\n" << RESET;
        mst_ok = true;
    }
}

void draw_tree(int n, int parent, int depth, bool last) {
    for (int i = 0; i < depth - 1; i++) std::cout << "  | ";
    if (depth > 0) std::cout << "  +-- ";
    if (parent == -1) {
        std::cout << GREEN << "[Root Node " << n << "]\n" << RESET;
    } else {
        std::cout << CYAN << "Node " << n << AMBER << " (w:" << mst[parent][n] << ")\n" << RESET;
    }

    std::vector<int> ch;
    for (int i = 0; i < V; i++) if (mst[n][i] && i != parent) ch.push_back(i);
    for (size_t i = 0; i < ch.size(); i++) {
        draw_tree(ch[i], n, depth + 1, i == ch.size() - 1);
    }
}

int main() {
    int ch;
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     ■ CRITICAL MST CORE ENGINE & ANALYSIS ■\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [SYSTEM STATUS] Active Vertices: " << V << " | Active Edges: " << elist.size() << "\n" << RESET
                  << "  1.  [+] Create Network Graph\n"
                  << "  2.  [#] Render Adjacency Matrix\n"
                  << "  3.  [*] Render Structural Map\n"
                  << "  4.  [^] Execute Prim's Path Mapping\n"
                  << "  5.  [^] Execute Kruskal's Path Mapping\n"
                  << "  6.  [$] Draw Hierarchical Tree Visual\n"
                  << "  7.  [X] Terminate Execution Engine\n"
                  << AMBER << " >> Select Target Action Option: " << RESET;

        if (!(std::cin >> ch) || ch == 7) {
            std::cout << RED << "\n [!] SHUTTING DOWN CORE SYSTEM OPERATIONS...\n" << RESET;
            break;
        }

        if (ch == 1) create();
        else if (ch == 2 || ch == 3) {
            if (!V) { std::cout << RED << " [!] ACCESS REJECTED: Network matrix layer is currently empty.\n" << RESET; continue; }
            printHeader(ch == 2 ? "MATRIX DATA REPRESENTATION" : "GRAPH CONSOLIDATION MAP");
            for (int i = 0; i < V; i++) {
                if (ch == 3) std::cout << GREEN << " (Node " << i << ") " << RESET;
                for (int j = 0; j < V; j++) {
                    if (ch == 2) {
                        if (graph[i][j] == INF) std::cout << RED << " INF " << RESET;
                        else std::printf(CYAN " %3d " RESET, graph[i][j]);
                    }
                    else if (graph[i][j] && graph[i][j] != INF) {
                        std::cout << CYAN << " ==(" << graph[i][j] << ")==> " << RESET << "[" << j << "]";
                    }
                }
                std::cout << "\n";
            }
        } 
        else if (ch == 4) prim();
        else if (ch == 5) kruskal();
        else if (ch == 6) {
            if (mst_ok) { 
                printHeader("HIERARCHICAL TREE ARCHITECTURE"); 
                draw_tree(0, -1, 0, true); 
            } else {
                std::cout << RED << " [!] CRITICAL ERROR: Active MST profile data missing. Run option 4 or 5 first.\n" << RESET;
            }
        } else {
            std::cout << RED << " [!] WARNING: Selection outside variable parameters.\n" << RESET;
        }
    }
    return 0;
}