import java.util.Scanner;
import java.util.Arrays;

public class DijkstraInterface {
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

    private static final int INF = 999;
    private static int V = 0;
    private static int[][] g = null;
    private static final Scanner scanner = new Scanner(System.in);

    private static void printHeader(String title) {
        System.out.println(PURPLE + "\n==================================================");
        System.out.println("  [#] " + title);
        System.out.println("==================================================" + RESET);
    }

    private static void printUserGuide() {
        System.out.println(CYAN + "\n==================================================");
        System.out.println("         CRASH COURSE: HOW TO USE THIS SYSTEM");
        System.out.println("==================================================" + RESET);
        System.out.println(" This interface computes single-source shortest path segments across positive cost profiles:\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Choice 1 maps vertices. Supply edge sequences as: [Src] [Dst] [Weight].");
        System.out.println("           Terminate entry streams safely by giving '-1 -1 -1'.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Run a shortest path trace (Choice 3) and select your target source node.");
        System.out.println("           Dijkstra's greedy expansion relaxes edge paths ($O(V^2)$) to map absolute routing structures.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize routing core matrix...");
        scanner.nextLine();
    }

    private static void path(int curr, int[] p) {
        if (p[curr] == -1) {
            System.out.print(curr);
            return;
        }
        path(p[curr], p);
        System.out.print(" -> " + curr);
    }

    private static void dijkstra() {
        printHeader("DIJKSTRA SHORTEST PATH GENERATOR");
        System.out.print(AMBER + "  [?] Select Starting Source Node (0 to " + (V - 1) + "): " + RESET);
        int src = scanner.nextInt();
        if (src < 0 || src >= V) {
            System.out.println(RED + "  [!] ERROR: Selection falls outside boundaries." + RESET);
            return;
        }

        int[] dist = new int[V];
        int[] p = new int[V];
        boolean[] vis = new boolean[V];
        
        Arrays.fill(dist, INF);
        Arrays.fill(p, -1);
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
                if (!vis[v] && g[u][v] != 0 && g[u][v] != INF && dist[u] + g[u][v] < dist[v]) {
                    dist[v] = dist[u] + g[u][v];
                    p[v] = u;
                }
            }
        }

        System.out.println(CYAN + "\n  [ROUTE] Optimization Matrix Output:" + RESET);
        System.out.println("  -----------------------------------------------");
        System.out.println("  Dest\t\tDist\t\tPath Sequence");
        System.out.println("  -----------------------------------------------");
        for (int i = 0; i < V; i++) {
            System.out.printf("  [%d]\t\t", i);
            if (dist[i] == INF) {
                System.out.println(RED + "INF\t\tNo Path Available" + RESET);
            } else {
                System.out.print(GREEN + dist[i] + "\t\t" + RESET);
                path(i, p);
                System.out.println();
            }
        }
        System.out.println("  -----------------------------------------------");
    }

    private static void create() {
        printHeader("GRAPH DATA INITIALIZATION");
        System.out.print(AMBER + "  [?] Total Vertices Allocation: " + RESET);
        V = scanner.nextInt();
        if (V <= 0) {
            System.out.println(RED + "  [!] ERROR: Invalid tracking volume defined." + RESET);
            V = 0;
            return;
        }

        g = new int[V][V];
        for (int i = 0; i < V; i++) {
            Arrays.fill(g[i], INF);
            g[i][i] = 0;
        }

        System.out.println(AMBER + "  [?] Input Directed Edges [Format: Src Dest Wt] (-1 -1 -1 to stop):" + RESET);
        while (true) {
            int o = scanner.nextInt();
            int d = scanner.nextInt();
            int w = scanner.nextInt();
            if (o == -1) break;
            if (o >= 0 && o < V && d >= 0 && d < V) {
                g[o][d] = w;
            } else {
                System.out.println(RED + "  [!] Border violation omitted." + RESET);
            }
        }
        System.out.println(GREEN + "  (+) Success: Topography cost metrics securely saved." + RESET);
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
        System.out.println("     [M] DIJKSTRA SHORTEST PATH INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.println(CYAN + "\n [MAIN MENU]" + RESET);
            System.out.println("  1.  (+) Input Graph Edge Networks");
            System.out.println("  2.  (#) Print Cost Adjacency Matrix Map");
            System.out.println("  3.  (*) Calculate Shortest Path Solutions");
            System.out.println("  4.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int ch = scanner.nextInt();

            if (ch == 1) {
                create();
            } else if (ch == 2) {
                if (V == 0) {
                    System.out.println(RED + " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY" + RESET);
                    continue;
                }
                printHeader("COST ADJACENCY MATRIX ROUTING LOOKUP");
                for (int i = 0; i < V; i++) {
                    System.out.print("  ");
                    for (int j = 0; j < V; j++) {
                        if (g[i][j] == INF) System.out.print(RED + "INF\t" + RESET);
                        else System.out.print(GREEN + g[i][j] + "\t" + RESET);
                    }
                    System.out.println();
                }
            } else if (ch == 3) {
                if (V == 0) {
                    System.out.println(RED + " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY" + RESET);
                    continue;
                }
                dijkstra();
            } else if (ch == 4) {
                System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                System.exit(0);
            } else {
                System.out.println(RED + " [!] WARNING: Operational instruction unrecognized.");
            }
        }
    }
}