import java.util.Scanner;
import java.util.LinkedList;
import java.util.Queue;

public class GraphInterface {
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

    private static int[][] adj = new int[20][20];
    private static boolean[] visited = new boolean[20];
    private static int n = 0;
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
        System.out.println(" This interface provides cross-platform traversal pipelines for exploring connected networks:\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Map your network via choice 1. Input dimensions followed by rows of 1s and 0s.");
        System.out.println("           (e.g., A connection from Node 0 to Node 1 means a '1' at Row 0, Column 1).");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Select an analysis path algorithm variant:");
        System.out.println("   • " + GREEN + "Breadth-First Search (2):" + RESET + " Level-by-level neighborhood sweep. Relies on an explicit FIFO Queue ($O(V^2)$).");
        System.out.println("   • " + GREEN + "Depth-First Search (3):  " + RESET + " Probes deep into a line of vertices first. Relies on recursion Stack ($O(V^2)$).");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize topological network graph matrix...");
        scanner.nextLine();
    }

    private static void dfs(int v) {
        System.out.print(GREEN + "[" + v + "] " + RESET);
        visited[v] = true;
        for (int i = 0; i < n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                dfs(i);
            }
        }
    }

    private static void bfs(int start) {
        for (int i = 0; i < n; i++) visited[i] = false;
        Queue<Integer> q = new LinkedList<>();
        
        q.add(start);
        visited[start] = true;
        
        while (!q.isEmpty()) {
            int v = q.poll();
            System.out.print(GREEN + "[" + v + "] " + RESET);
            for (int i = 0; i < n; i++) {
                if (adj[v][i] == 1 && !visited[i]) {
                    q.add(i);
                    visited[i] = true;
                }
            }
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
        System.out.println("     [M] GRAPH EXPLORATION & ANALYSIS INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.printf(CYAN + "\n [MAIN MENU] Matrix Scope: %d vertices initialized\n" + RESET, n);
            System.out.println("  1.  (+) Input Network Topology (Adjacency Matrix Mapping)");
            System.out.println("  2.  (*) Execute Breadth-First Search Stream (BFS Queue)");
            System.out.println("  3.  (*) Execute Depth-First Search Stream (DFS Stack)");
            System.out.println("  4.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int choice = scanner.nextInt();

            if (choice == 4) {
                System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                break;
            }

            if (choice == 1) {
                printHeader("GRAPH STRUCT INTERACTIVE DATA INITIALIZATION");
                System.out.print(AMBER + "  [?] Enter Total Number of Vertices: " + RESET);
                n = scanner.nextInt();
                if (n <= 0 || n > 20) {
                    System.out.println(RED + " [!] ERROR: Matrix bounds limited between 1 and 20 elements.");
                    n = 0;
                    continue;
                }
                System.out.println(AMBER + "  [?] Input Matrix Configuration Layout Line-by-Line:" + RESET);
                for (int i = 0; i < n; i++) {
                    System.out.printf("  Row %d: ", i);
                    for (int j = 0; j < n; j++) {
                        adj[i][j] = scanner.nextInt();
                    }
                }
                System.out.println(GREEN + "  (+) Success: Topography map successfully bound to adjacent registry." + RESET);
            } else if (n == 0) {
                System.out.println(RED + " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY" + RESET);
            } else {
                System.out.printf(AMBER + "  [?] Target Starting Vertex Key Address (0 to %d): " + RESET, n - 1);
                int src = scanner.nextInt();

                if (src < 0 || src >= n) {
                    System.out.println(RED + " [!] ERROR: Target index falls outside variable parameters.");
                    continue;
                }

                for (int i = 0; i < n; i++) visited[i] = false;

                if (choice == 2) {
                    printHeader("BFS EXPLORATION SEQUENCE GENERATED");
                    System.out.print("  Sequence Path: ");
                    bfs(src);
                } else if (choice == 3) {
                    printHeader("DFS EXPLORATION SEQUENCE GENERATED");
                    System.out.print("  Sequence Path: ");
                    dfs(src);
                } else {
                    System.out.println(RED + " [!] WARNING: Operational instruction unrecognized.");
                }
                System.out.println();
            }
        }
    }
}