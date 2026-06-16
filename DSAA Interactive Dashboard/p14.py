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
graph = []
mst = []
elist = []
mst_ok = False

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  ◆ {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" This engine tracks Minimum Spanning Tree (MST) generations via greedy optimizations:\n")
    print(f"{AMBER} [STEP 1]{RESET} Choice 1 maps vertices. Supply edge sequences as: [Src] [Dst] [Weight].")
    print("           Terminate entry streams safely by giving '-1 -1 -1'.")
    print(f"{AMBER} [STEP 2]{RESET} Run a minimum path optimization track:")
    print(f"   • {GREEN}Prim's Algorithm (4):   {RESET} Grows the tree from a single starting root node, adding the cheapest global connection vertex step-by-step.")
    print(f"   • {GREEN}Kruskal's Algorithm (5):{RESET} Sorts all network edges by raw weight and links independent forest structures via Disjoint Set Union (DSU).")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize structural optimization matrix...")

def find_set(i, p):
    if p[i] == i:
        return i
    p[i] = find_set(p[i], p)
    return p[i]

def create():
    global V, graph, mst, elist, mst_ok
    print_header("GRAPH INITIALIZATION TOOL")
    try:
        V = int(input(f"{AMBER} [?] Enter number of vertices: {RESET}"))
        mst_ok = False
        elist = []
        
        graph = [[INF] * V for _ in range(V)]
        for i in range(V):
            graph[i][i] = 0
        mst = [[0] * V for _ in range(V)]
        
        print(f"{AMBER}\n [!] Enter edges as: [Origin] [Dest] [Weight]{RESET}")
        print(f"{CYAN}     (Type '-1 -1 -1' to finalize setup)\n{RESET}")
        
        while True:
            line = input("  ➔ ").split()
            if not line:
                continue
            o, d, w = int(line[0]), int(line[1]), int(line[2])
            if o == -1:
                break
            if 0 <= o < V and 0 <= d < V and o != d:
                graph[o][d] = graph[d][o] = w
                elist.append({'u': o, 'v': d, 'w': w})
                print(f"{GREEN}    ▲ Edge Saved: {o} <-> {d} (w: {w}){RESET}")
            else:
                print(f"{RED}    ▼ [!] Invalid node IDs or loop self-connection skipped.{RESET}")
        print(f"{GREEN}\n [■] SUCCESS: Graph captured with {len(elist)} active edges.{RESET}")
    except (ValueError, IndexError):
        print(f"{RED} [!] ERROR: Dynamic processing layer failure.{RESET}")
        V = 0

def add_mst_edge(u, v, w):
    global mst
    print(f"{CYAN}  (Node {u}) <==== [w: {w:2d}] ====> (Node {v}){RESET}")
    mst[u][v] = mst[v][u] = w

def prim():
    global V, graph, mst, mst_ok
    if not V:
        print(f"{RED} [!] EMPTY DATA: Please initialize a graph first.{RESET}")
        return
    print_header("PRIM'S MINIMUM SPANNING TREE")
    mst = [[0] * V for _ in range(V)]
    
    sel = [False] * V
    sel[0] = True
    edges, tot = 0, 0
    
    while edges < V - 1:
        min_w = INF
        x, y = -1, -1
        for i in range(V):
            if sel[i]:
                for j in range(V):
                    if not sel[j] and graph[i][j] < min_w:
                        min_w = graph[i][j]
                        x, y = i, j
        if min_w == INF:
            break
        sel[y] = True
        add_mst_edge(x, y, min_w)
        tot += min_w
        edges += 1
        
    if edges < V - 1:
        print(f"{RED}\n [▼] ANALYSIS FAIL: Network graph is disconnected!{RESET}")
    else:
        print(f"{GREEN}\n [■] MST GENERATION SUCCESS | Total Cost Weight: {tot}{RESET}")
        mst_ok = True

def kruskal():
    global V, mst, elist, mst_ok
    if not V:
        print(f"{RED} [!] EMPTY DATA: Please initialize a graph first.{RESET}")
        return
    print_header("KRUSKAL'S MINIMUM SPANNING TREE")
    mst = [[0] * V for _ in range(V)]
    
    p = list(range(V))
    sorted_edges = sorted(elist, key=lambda edge: edge['w'])
    
    edges, tot = 0, 0
    for edge in sorted_edges:
        if edges >= V - 1:
            break
        ru = find_set(edge['u'], p)
        rv = find_set(edge['v'], p)
        if ru != rv:
            p[ru] = rv
            add_mst_edge(edge['u'], edge['v'], edge['w'])
            tot += edge['w']
            edges += 1
            
    if edges < V - 1:
        print(f"{RED}\n [▼] ANALYSIS FAIL: Network graph is disconnected!{RESET}")
    else:
        print(f"{GREEN}\n [■] MST GENERATION SUCCESS | Total Cost Weight: {tot}{RESET}")
        mst_ok = True

def draw_tree(n, parent, depth, last):
    global V, mst
    for _ in range(depth - 1):
        print("  | ", end="")
    if depth > 0:
        print("  +-- ", end="")
    if parent == -1:
        print(f"{GREEN}[Root Node {n}]{RESET}")
    else:
        print(f"{CYAN}Node {n}{AMBER} (w:{mst[parent][n]}){RESET}")
        
    ch = [i for i in range(V) if mst[n][i] and i != parent]
    for i, child in enumerate(ch):
        draw_tree(child, n, depth + 1, i == len(ch) - 1)

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()
    
    print(f"{CYAN}==================================================")
    print("     ■ CRITICAL MST CORE ENGINE & ANALYSIS ■")
    print(f"=================================================={RESET}")
    
    while True:
        print(f"{CYAN}\n [SYSTEM STATUS] Active Vertices: {V} | Active Edges: {len(elist)}{RESET}")
        print("  1.  [+] Create Network Graph")
        print("  2.  [#] Render Adjacency Matrix")
        print("  3.  [*] Render Structural Map")
        print("  4.  [^] Execute Prim's Path Mapping")
        print("  5.  [^] Execute Kruskal's Path Mapping")
        print("  6.  [$] Draw Hierarchical Tree Visual")
        print("  7.  [X] Terminate Execution Engine")
        
        try:
            choice = input(f"{AMBER} >> Select Target Action Option: {RESET}").strip()
            if not choice:
                continue
            ch = int(choice)
        except ValueError:
            print(f"{RED} [!] WARNING: Selection outside variable parameters.{RESET}")
            continue
            
        if ch == 7:
            print(f"{RED}\n [!] SHUTTING DOWN CORE SYSTEM OPERATIONS...\n{RESET}")
            sys.exit(0)
            
        if ch == 1:
            create()
        elif ch in (2, 3):
            if not V:
                print(f"{RED} [!] ACCESS REJECTED: Network matrix layer is currently empty.{RESET}")
                continue
            print_header("MATRIX DATA REPRESENTATION" if ch == 2 else "GRAPH CONSOLIDATION MAP")
            for i in range(V):
                if ch == 3:
                    print(f"{GREEN} (Node {i}) {RESET}", end="")
                for j in range(V):
                    if ch == 2:
                        if graph[i][j] == INF:
                            print(f"{RED} INF {RESET}", end="")
                        else:
                            print(f"{CYAN} {graph[i][j]:3d} {RESET}", end="")
                    elif graph[i][j] and graph[i][j] != INF:
                        print(f"{CYAN} ==({graph[i][j]})==> {RESET}[{j}]", end="")
                print()
        elif ch == 4:
            prim()
        elif ch == 5:
            kruskal()
        elif ch == 6:
            if mst_ok:
                print_header("HIERARCHICAL TREE ARCHITECTURE")
                draw_tree(0, -1, 0, True)
            else:
                print(f"{RED} [!] CRITICAL ERROR: Active MST profile data missing. Run option 4 or 5 first.{RESET}")
        else:
            print(f"{RED} [!] WARNING: Selection outside variable parameters.{RESET}")

if __name__ == "__main__":
    main()