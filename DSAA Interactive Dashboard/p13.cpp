#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <string>

#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

int n = 0;
std::vector<std::vector<int>> adj;
std::vector<bool> visited;

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  [#] " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " This interface provides cross-platform traversal pipelines for exploring connected networks:\n\n"
              << AMBER << " [STEP 1]" << RESET << " Map your network via choice 1. Input dimensions followed by rows of 1s and 0s.\n"
              << "           (e.g., A connection from Node 0 to Node 1 means a '1' at Row 0, Column 1).\n"
              << AMBER << " [STEP 2]" << RESET << " Select an analysis path algorithm variant:\n"
              << "   • " << GREEN << "Breadth-First Search (2):" << RESET << " Level-by-level neighborhood sweep. Relies on an explicit FIFO Queue ($O(V^2)$).\n"
              << "   • " << GREEN << "Depth-First Search (3):  " << RESET << " Probes deep into a line of vertices first. Relies on recursion Stack ($O(V^2)$).\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize topological network graph matrix...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

void dfs(int v) {
    std::cout << GREEN << "[" << v << "] " << RESET;
    visited[v] = true;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i]) {
            dfs(i);
        }
    }
}

void bfs(int start) {
    std::fill(visited.begin(), visited.end(), false);
    std::queue<int> q;
    
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        std::cout << GREEN << "[" << v << "] " << RESET;
        for (int i = 0; i < n; i++) {
            if (adj[v][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int main() {
    int choice, src;

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] GRAPH EXPLORATION & ANALYSIS INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU] Matrix Scope: " << n << " vertices initialized\n" << RESET
                  << "  1.  (+) Input Network Topology (Adjacency Matrix Mapping)\n"
                  << "  2.  (*) Execute Breadth-First Search Stream (BFS Queue)\n"
                  << "  3.  (*) Execute Depth-First Search Stream (DFS Stack)\n"
                  << "  4.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> choice)) break;
        if (choice == 4) {
            std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
            break;
        }

        if (choice == 1) {
            printHeader("GRAPH STRUCT INTERACTIVE DATA INITIALIZATION");
            std::cout << AMBER << "  [?] Enter Total Number of Vertices: " << RESET;
            std::cin >> n;
            if (n <= 0) {
                std::cout << RED << " [!] ERROR: Invalid parameter count selected.\n" << RESET;
                n = 0;
                continue;
            }
            adj.assign(n, std::vector<int>(n, 0));
            visited.assign(n, false);
            std::cout << AMBER << "  [?] Input Matrix Configuration Layout Line-by-Line:\n" << RESET;
            for (int i = 0; i < n; i++) {
                std::cout << "  Row " << i << ": ";
                for (int j = 0; j < n; j++) {
                    std::cin >> adj[i][j];
                }
            }
            std::cout << GREEN << "  (+) Success: Topography map successfully bound to adjacent registry.\n" << RESET;
        } else if (n == 0) {
            std::cout << RED << " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY\n" << RESET;
        } else {
            std::cout << AMBER << "  [?] Target Starting Vertex Key Address (0 to " << n - 1 << "): " << RESET;
            std::cin >> src;

            if (src < 0 || src >= n) {
                std::cout << RED << " [!] ERROR: Target index falls outside variable parameters.\n" << RESET;
                continue;
            }

            std::fill(visited.begin(), visited.end(), false);

            if (choice == 2) {
                printHeader("BFS EXPLORATION SEQUENCE GENERATED");
                std::cout << "  Sequence Path: ";
                bfs(src);
            } else if (choice == 3) {
                printHeader("DFS EXPLORATION SEQUENCE GENERATED");
                std::cout << "  Sequence Path: ";
                dfs(src);
            } else {
                std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
            }
            std::cout << "\n";
        }
    }
    return 0;
}