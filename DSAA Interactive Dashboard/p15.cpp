#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

const int INF = 999;
int V = 0;
std::vector<std::vector<int>> g;

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  [#] " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " This interface computes single-source shortest path segments across positive cost profiles:\n\n"
              << AMBER << " [STEP 1]" << RESET << " Choice 1 maps vertices. Supply edge sequences as: [Src] [Dst] [Weight].\n"
              << "           Terminate entry streams safely by giving '-1 -1 -1'.\n"
              << AMBER << " [STEP 2]" << RESET << " Run a shortest path trace (Choice 3) and select your target source node.\n"
              << "           Dijkstra's greedy expansion relaxes edge paths ($O(V^2)$) to map absolute routing structures.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize routing core matrix...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

void path(int curr, const std::vector<int>& p) {
    if (p[curr] == -1) {
        std::cout << curr;
        return;
    }
    path(p[curr], p);
    std::cout << " -> " << curr;
}

void dijkstra() {
    int src;
    printHeader("DIJKSTRA SHORTEST PATH GENERATOR");
    std::cout << AMBER << "  [?] Select Starting Source Node (0 to " << V - 1 << "): " << RESET;
    std::cin >> src;
    if (src < 0 || src >= V) {
        std::cout << RED << "  [!] ERROR: Selection falls outside boundaries.\n" << RESET;
        return;
    }

    std::vector<int> dist(V, INF);
    std::vector<int> p(V, -1);
    std::vector<bool> vis(V, false);
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

    std::cout << CYAN << "\n  [ROUTE] Optimization Matrix Output:\n" << RESET
              << "  -----------------------------------------------\n"
              << "  Dest\t\tDist\t\tPath Sequence\n"
              << "  -----------------------------------------------\n";
    for (int i = 0; i < V; i++) {
        std::cout << "  [" << i << "]\t\t";
        if (dist[i] == INF) {
            std::cout << RED << "INF\t\tNo Path Available\n" << RESET;
        } else {
            std::cout << GREEN << dist[i] << "\t\t" << RESET;
            path(i, p);
            std::cout << "\n";
        }
    }
    std::cout << "  -----------------------------------------------\n";
}

void create() {
    int o, d, w;
    printHeader("GRAPH DATA INITIALIZATION");
    std::cout << AMBER << "  [?] Total Vertices Allocation: " << RESET;
    std::cin >> V;
    if (V <= 0) {
        std::cout << RED << "  [!] ERROR: Vertex configuration payload cannot be zero.\n" << RESET;
        V = 0;
        return;
    }

    g.assign(V, std::vector<int>(V, INF));
    for (int i = 0; i < V; i++) g[i][i] = 0;

    std::cout << AMBER << "  [?] Input Directed Edges [Format: Src Dest Wt] (-1 -1 -1 to stop):\n" << RESET;
    while (std::cin >> o >> d >> w && o != -1) {
        if (o >= 0 && o < V && d >= 0 && d < V) {
            g[o][d] = w;
        } else {
            std::cout << RED << "  [!] Out-of-bounds edge target omitted.\n" << RESET;
        }
    }
    std::cout << GREEN << "  (+) Success: Topography cost metrics securely saved.\n" << RESET;
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
              << "     [M] DIJKSTRA SHORTEST PATH INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU]\n" << RESET
                  << "  1.  (+) Input Graph Edge Networks\n"
                  << "  2.  (#) Print Cost Adjacency Matrix Map\n"
                  << "  3.  (*) Calculate Shortest Path Solutions\n"
                  << "  4.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> ch)) break;

        if (ch == 1) {
            create();
        } else if (ch == 2) {
            if (V == 0) {
                std::cout << RED << " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY\n" << RESET;
                continue;
            }
            printHeader("COST ADJACENCY MATRIX ROUTING LOOKUP");
            for (int i = 0; i < V; i++) {
                std::cout << "  ";
                for (int j = 0; j < V; j++) {
                    if (g[i][j] == INF) std::cout << RED << "INF\t" << RESET;
                    else std::cout << GREEN << g[i][j] << "\t" << RESET;
                }
                std::cout << "\n";
            }
        } else if (ch == 3) {
            if (V == 0) {
                std::cout << RED << " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY\n" << RESET;
                continue;
            }
            dijkstra();
        } else if (ch == 4) {
            std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
            std::exit(0);
        } else {
            std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}