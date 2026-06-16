import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Arrays;

public class MstAnalysisEngine {
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

    private static final int INF = 999;

    static class Edge implements Comparable<Edge> {
        int u, v, w;
        Edge(int u, int v, int w) {
            this.u = u; this.v = v; this.w = w;
        }
        @Override
        public int compareTo(Edge o) {
            return this.w - o.w;
        }
    }

    private static int V = 0;
    private static int[][] graph = null;
    private static int[][] mst = null;
    private static ArrayList<Edge> elist = new ArrayList<>();
    private static boolean mstOk = false;
    private static final Scanner scanner = new Scanner(System.in);

    private static void printHeader(String title) {
        System.out.println(PURPLE + "\n==================================================");
        System.out.println("  ◆ " + title);
        System.out.println("==================================================" + RESET);
    }

    private static void printUserGuide() {
        System.out.println(CYAN + "\n==================================================");
        System.out.println("         CRASH COURSE: HOW TO USE THIS SYSTEM");
        System.out.println("==================================================" + RESET);
        System.out.println(" This engine tracks Minimum Spanning Tree (MST) generations via greedy optimizations:\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Choice 1 maps vertices. Supply edge sequences as: [Src] [Dst] [Weight].");
        System.out.println("           Terminate entry streams safely by giving '-1 -1 -1'.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Run a minimum path optimization track:");
        System.out.println("   • " + GREEN + "Prim's Algorithm (4):   " + RESET + " Grows the tree from a single starting root node, adding the cheapest global connection vertex step-by-step.");
        System.out.println("   • " + GREEN + "Kruskal's Algorithm (5):" + RESET + " Sorts all network edges by raw weight and links independent forest structures via Disjoint Set Union (DSU).");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize structural optimization matrix...");
        scanner.nextLine();
    }

    private static int findSet(int i, int[] p) {
        return (p[i] == i) ? i : (p[i] = findSet(p[i], p));
    }

    private static void create() {
        printHeader("GRAPH INITIALIZATION TOOL");
        System.out.print(AMBER + " [?] Enter number of vertices: " + RESET);
        V = scanner.nextInt();
        mstOk = false;
        elist.clear();

        graph = new int[V][V];
        mst = new int[V][V];
        for (int i = 0; i < V; i++) {
            Arrays.fill(graph[i], INF);
            graph[i][i] = 0;
        }

        System.out.println(AMBER + "\n [!] Enter edges as: [Origin] [Dest] [Weight]" + RESET);
        System.out.println(CYAN + "     (Type '-1 -1 -1' to finalize setup)\n" + RESET);
        while (true) {
            System.out.print("  ➔ ");
            int o = scanner.nextInt();
            int d = scanner.nextInt();
            int w = scanner.nextInt();
            if (o == -1) break;
            if (o >= 0 && o < V && d >= 0 && d < V && o != d) {
                graph[o][d] = graph[d][o] = w;
                elist.add(new Edge(o, d, w));
                System.out.printf(GREEN + "    ▲ Edge Saved: %d <-> %d (w: %d)\n" + RESET, o, d, w);
            } else {
                System.out.println(RED + "    ▼ [!] Invalid node IDs or loop self-connection skipped." + RESET);
            }
        }
        System.out.printf(GREEN + "\n [■] SUCCESS: Graph captured with %d active edges.\n" + RESET, elist.size());
    }

    private static void addMstEdge(int u, int v, int w) {
        System.out.printf(CYAN + "  (Node %d) <==== [w: %2d] ====> (Node %d)\n" + RESET, u, w, v);
        mst[u][v] = mst[v][u] = w;
    }

    private static void prim() {
        if (V == 0) { System.out.println(RED + " [!] EMPTY DATA: Please initialize a graph first." + RESET); return; }
        printHeader("PRIM'S MINIMUM SPANNING TREE");
        mst = new int[V][V];

        boolean[] sel = new boolean[V];
        sel[0] = true;
        int edges = 0, tot = 0;

        while (edges < V - 1) {
            int min = INF, x = -1, y = -1;
            for (int i = 0; i < V; i++) {
                if (sel[i]) {
                    for (int j = 0; j < V; j++) {
                        if (!sel[j] && graph[i][j] < min) {
                            min = graph[i][j]; x = i; y = j;
                        }
                    }
                }
            }
            if (min == INF) break;
            sel[y] = true;
            addMstEdge(x, y, min);
            tot += min;
            edges++;
        }
        if (edges < V - 1) {
            System.out.println(RED + "\n [▼] ANALYSIS FAIL: Network graph is disconnected!" + RESET);
        } else {
            System.out.printf(GREEN + "\n [■] MST GENERATION SUCCESS | Total Cost Weight: %d\n" + RESET, tot);
            mstOk = true;
        }
    }

    private static void kruskal() {
        if (V == 0) { System.out.println(RED + " [!] EMPTY DATA: Please initialize a graph first." + RESET); return; }
        printHeader("KRUSKAL'S MINIMUM SPANNING TREE");
        mst = new int[V][V];

        int[] p = new int[V];
        for (int i = 0; i < V; i++) p[i] = i;
        Collections.sort(elist);

        int edges = 0, tot = 0;
        for (int i = 0; i < elist.size() && edges < V - 1; i++) {
            Edge edge = elist.get(i);
            int ru = findSet(edge.u, p);
            int rv = findSet(edge.v, p);
            if (ru != rv) {
                p[ru] = rv;
                addMstEdge(edge.u, edge.v, edge.w);
                tot += edge.w;
                edges++;
            }
        }
        if (edges < V - 1) {
            System.out.println(RED + "\n [▼] ANALYSIS FAIL: Network graph is disconnected!" + RESET);
        } else {
            System.out.printf(GREEN + "\n [■] MST GENERATION SUCCESS | Total Cost Weight: %d\n" + RESET, tot);
            mstOk = true;
        }
    }

    private static void drawTree(int n, int parent, int depth, boolean last) {
        for (int i = 0; i < depth - 1; i++) System.out.print("  | ");
        if (depth > 0) System.out.print("  +-- ");
        if (parent == -1) {
            System.out.printf(GREEN + "[Root Node %d]\n" + RESET, n);
        } else {
            System.out.printf(CYAN + "Node %d" + AMBER + " (w:%d)\n" + RESET, n, mst[parent][n]);
        }

        ArrayList<Integer> ch = new ArrayList<>();
        for (int i = 0; i < V; i++) if (mst[n][i] != 0 && i != parent) ch.add(i);
        for (int i = 0; i < ch.size(); i++) {
            drawTree(ch.get(i), n, depth + 1, i == ch.size() - 1);
        }
    }

    public static void main(String[] args) {
        try {
            if (System.getProperty("os.name").contains("Windows")) {
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            } else {
                new ProcessBuilder("clear").inheritIO().start().waitFor();
            }
        } catch (Exception ignored) {}

        printUserGuide();

        System.out.println(CYAN + "==================================================");
        System.out.println("     ■ CRITICAL MST CORE ENGINE & ANALYSIS ■");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.printf(CYAN + "\n [SYSTEM STATUS] Active Vertices: %d | Active Edges: %d\n" + RESET, V, elist.size());
            System.out.println("  1.  [+] Create Network Graph");
            System.out.println("  2.  [#] Render Adjacency Matrix");
            System.out.println("  3.  [*] Render Structural Map");
            System.out.println("  4.  [^] Execute Prim's Path Mapping");
            System.out.println("  5.  [^] Execute Kruskal's Path Mapping");
            System.out.println("  6.  [$] Draw Hierarchical Tree Visual");
            System.out.println("  7.  [X] Terminate Execution Engine");
            System.out.print(AMBER + " >> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int ch = scanner.nextInt();
            if (ch == 7) {
                System.out.println(RED + "\n [!] SHUTTING DOWN CORE SYSTEM OPERATIONS...\n" + RESET);
                break;
            }

            if (ch == 1) create();
            else if (ch == 2 || ch == 3) {
                if (V == 0) { System.out.println(RED + " [!] ACCESS REJECTED: Network matrix layer is currently empty." + RESET); continue; }
                printHeader(ch == 2 ? "MATRIX DATA REPRESENTATION" : "GRAPH CONSOLIDATION MAP");
                for (int i = 0; i < V; i++) {
                    if (ch == 3) System.out.print(GREEN + " (Node " + i + ") " + RESET);
                    for (int j = 0; j < V; j++) {
                        if (ch == 2) {
                            if (graph[i][j] == INF) System.out.print(RED + " INF " + RESET);
                            else System.out.printf(CYAN + " %3d " + RESET, graph[i][j]);
                        }
                        else if (graph[i][j] != 0 && graph[i][j] != INF) {
                            System.out.printf(CYAN + " ==(%d)==> " + RESET + "[%d]", graph[i][j], j);
                        }
                    }
                    System.out.println();
                }
            } 
            else if (ch == 4) prim();
            else if (ch == 5) kruskal();
            else if (ch == 6) {
                if (mstOk) { 
                    printHeader("HIERARCHICAL TREE ARCHITECTURE"); 
                    drawTree(0, -1, 0, true); 
                } else {
                    System.out.println(RED + " [!] CRITICAL ERROR: Active MST profile data missing. Run option 4 or 5 first." + RESET);
                }
            } else {
                System.out.println(RED + " [!] WARNING: Selection outside variable parameters.");
            }
        }
    }
}