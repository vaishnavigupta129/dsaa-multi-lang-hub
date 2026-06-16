import os
import sys

RESET = "\033[0m"
CYAN = "\033[1;36m"
GREEN = "\033[1;32m"
RED = "\033[1;31m"
AMBER = "\033[1;33m"
PURPLE = "\033[1;35m"

n = 0
adj = []
visited = []

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" This interface provides cross-platform traversal pipelines for exploring connected networks:\n")
    print(f"{AMBER} [STEP 1]{RESET} Map your network via choice 1. Input dimensions followed by rows of 1s and 0s.")
    print("           (e.g., A connection from Node 0 to Node 1 means a '1' at Row 0, Column 1).")
    print(f"{AMBER} [STEP 2]{RESET} Select an analysis path algorithm variant:")
    print(f"   • {GREEN}Breadth-First Search (2):{RESET} Level-by-level neighborhood sweep. Relies on an explicit FIFO Queue ($O(V^2)$).")
    print(f"   • {GREEN}Depth-First Search (3):  {RESET} Probes deep into a line of vertices first. Relies on recursion Stack ($O(V^2)$).")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize topological network graph matrix...")

def dfs(v):
    global n, adj, visited
    print(f"{GREEN}[{v}] {RESET}", end="")
    visited[v] = True
    for i in range(n):
        if adj[v][i] == 1 and not visited[i]:
            dfs(i)

def bfs(start):
    global n, adj, visited
    visited = [False] * n
    q = []
    
    q.append(start)
    visited[start] = True
    
    while q:
        v = q.pop(0)
        print(f"{GREEN}[{v}] {RESET}", end="")
        for i in range(n):
            if adj[v][i] == 1 and not visited[i]:
                q.append(i)
                visited[i] = True

def main():
    global n, adj, visited
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    print(f"{CYAN}==================================================")
    print("     [M] GRAPH EXPLORATION & ANALYSIS INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU] Matrix Scope: {n} vertices initialized{RESET}")
        print("  1.  (+) Input Network Topology (Adjacency Matrix Mapping)")
        print("  2.  (*) Execute Breadth-First Search Stream (BFS Queue)")
        print("  3.  (*) Execute Depth-First Search Stream (DFS Stack)")
        print("  4.  (X) Terminate Control Kernel Execution")
        
        try:
            choice = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if choice == 4:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)

        if choice == 1:
            print_header("GRAPH STRUCT INTERACTIVE DATA INITIALIZATION")
            try:
                n = int(input(f"{AMBER}  [?] Enter Total Number of Vertices: {RESET}"))
                if n <= 0:
                    print(f"{RED} [!] ERROR: Target limits must be greater than zero.{RESET}")
                    n = 0
                    continue
                adj = []
                print(f"{AMBER}  [?] Input Matrix Configuration Layout Line-by-Line:{RESET}")
                for i in range(n):
                    row_tokens = input(f"  Row {i}: ").split()
                    row_data = [int(x) for x in row_tokens[:n]]
                    # Fallback buffering if line entry is too short
                    while len(row_data) < n:
                        row_data.append(0)
                    adj.append(row_data)
                visited = [False] * n
                print(f"{GREEN}  (+) Success: Topography map successfully bound to adjacent registry.{RESET}")
            except ValueError:
                print(f"{RED} [!] ERROR: Processing frame parse mismatch.{RESET}")
                n = 0
                adj = []
        elif n == 0:
            print(f"{RED} [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY{RESET}")
        else:
            try:
                src = int(input(f"{AMBER}  [?] Target Starting Vertex Key Address (0 to {n - 1}): {RESET}"))
                if src < 0 or src >= n:
                    print(f"{RED} [!] ERROR: Target index falls outside variable parameters.{RESET}")
                    continue
                
                visited = [False] * n
                
                if choice == 2:
                    print_header("BFS EXPLORATION SEQUENCE GENERATED")
                    print("  Sequence Path: ", end="")
                    bfs(src)
                elif choice == 3:
                    print_header("DFS EXPLORATION SEQUENCE GENERATED")
                    print("  Sequence Path: ", end="")
                    dfs(src)
                else:
                    print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
                print()
            except ValueError:
                print(f"{RED} [!] ERROR: Integer token casting exception.{RESET}")

if __name__ == "__main__":
    main()