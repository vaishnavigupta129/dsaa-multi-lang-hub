import os
import sys

RESET = "\033[0m"
CYAN = "\033[1;36m"
GREEN = "\033[1;32m"
RED = "\033[1;31m"
AMBER = "\033[1;33m"
PURPLE = "\033[1;35m"

INF = 999
V = 0
g = []

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" This interface computes single-source shortest path segments across positive cost profiles:\n")
    print(f"{AMBER} [STEP 1]{RESET} Choice 1 maps vertices. Supply edge sequences as: [Src] [Dst] [Weight].")
    print("           Terminate entry streams safely by giving '-1 -1 -1'.")
    print(f"{AMBER} [STEP 2]{RESET} Run a shortest path trace (Choice 3) and select your target source node.")
    print(f"           Dijkstra's greedy expansion relaxes edge paths ($O(V^2)$) to map absolute routing structures.")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize routing core matrix...")

def path(curr, p):
    if p[curr] == -1:
        print(curr, end="")
        return
    path(p[curr], p)
    print(f" -> {curr}", end="")

def dijkstra():
    global V, g
    print_header("DIJKSTRA SHORTEST PATH GENERATOR")
    try:
        src = int(input(f"{AMBER}  [?] Select Starting Source Node (0 to {V - 1}): {RESET}"))
        if src < 0 or src >= V:
            print(f"{RED}  [!] ERROR: Selection falls outside boundaries.{RESET}")
            return
    except ValueError:
        print(f"{RED}  [!] ERROR: Invalid integer target address.{RESET}")
        return

    dist = [INF] * V
    p = [-1] * V
    vis = [False] * V
    dist[src] = 0

    for _ in range(V - 1):
        min_w = INF
        u = -1
        for v in range(V):
            if not vis[v] and dist[v] <= min_w:
                min_w = dist[v]
                u = v
        
        if u == -1 or min_w == INF:
            break
        vis[u] = True

        for v in range(V):
            if not vis[v] and g[u][v] and g[u][v] != INF and dist[u] + g[u][v] < dist[v]:
                dist[v] = dist[u] + g[u][v]
                p[v] = u

    print(f"{CYAN}\n  [ROUTE] Optimization Matrix Output:{RESET}")
    print("  -----------------------------------------------")
    print("  Dest\t\tDist\t\tPath Sequence")
    print("  -----------------------------------------------")
    for i in range(V):
        print(f"  [{i}]\t\t", end="")
        if dist[i] == INF:
            print(f"{RED}INF\t\tNo Path Available{RESET}")
        else:
            print(f"{GREEN}{dist[i]}\t\t{RESET}", end="")
            path(i, p)
            print()
    print("  -----------------------------------------------")

def create():
    global V, g
    print_header("GRAPH DATA INITIALIZATION")
    try:
        V = int(input(f"{AMBER}  [?] Total Vertices Allocation: {RESET}"))
        if V <= 0:
            print(f"{RED}  [!] ERROR: Vertex array configuration cannot be null.{RESET}")
            V = 0
            return
        
        g = [[INF] * V for _ in range(V)]
        for i in range(V):
            g[i][i] = 0

        print(f"{AMBER}  [?] Input Directed Edges [Format: Src Dest Wt] (-1 -1 -1 to stop):{RESET}")
        while True:
            line = input().split()
            if not line or len(line) < 3:
                continue
            o, d, w = int(line[0]), int(line[1]), int(line[2])
            if o == -1:
                break
            if 0 <= o < V and 0 <= d < V:
                g[o][d] = w
            else:
                print(f"{RED}  [!] Border violation parsing dropped edge connection.{RESET}")
        print(f"{GREEN}  (+) Success: Topography cost metrics securely saved.{RESET}")
    except (ValueError, IndexError):
        print(f"{RED}  [!] ERROR: Input evaluation token parsing error.{RESET}")
        V = 0

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    print(f"{CYAN}==================================================")
    print("     [M] DIJKSTRA SHORTEST PATH INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU]{RESET}")
        print("  1.  (+) Input Graph Edge Networks")
        print("  2.  (#) Print Cost Adjacency Matrix Map")
        print("  3.  (*) Calculate Shortest Path Solutions")
        print("  4.  (X) Terminate Control Kernel Execution")
        
        try:
            choice = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if choice == 1:
            create()
        elif choice == 2:
            if V == 0:
                print(f"{RED} [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY{RESET}")
                continue
            print_header("COST ADJACENCY MATRIX ROUTING LOOKUP")
            for i in range(V):
                print("  ", end="")
                for j in range(V):
                    if g[i][j] == INF:
                        print(f"{RED}INF\t{RESET}", end="")
                    else:
                        print(f"{GREEN}{g[i][j]}\t{RESET}", end="")
                print()
        elif choice == 3:
            if V == 0:
                print(f"{RED} [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY{RESET}")
                continue
            dijkstra()
        elif choice == 4:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()