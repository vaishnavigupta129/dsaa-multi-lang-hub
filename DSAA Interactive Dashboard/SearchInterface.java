import java.util.Scanner;

public class SearchInterface {
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

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
        System.out.println(" Think of this system as an elite search database operating via two distinct algorithms.\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Allocate data size and input parameters via Main Menu option 1.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Choose a targeting sub-mode position variant:");
        System.out.println("   • " + GREEN + "Linear Search (2):" + RESET + " Sweeps elements one by one. Works seamlessly on unsorted blocks.");
        System.out.println("   • " + GREEN + "Binary Search (3):" + RESET + " Divides sorted collections in half repeatedly. (Requires Sorted Inputs!)");
        System.out.println("   • " + GREEN + "Logarithmic Scale:" + RESET + " While Linear takes up to N steps, Binary finds targets in log(N) cuts.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize data lookup search kernel...");
        scanner.nextLine();
    }

    private static void find(int[] a, int n, int k, int mode) {
        int l = 0, r = n - 1, pos = -1;

        if (mode == 2) { // Linear Search
            printHeader("EXECUTING LINEAR SYSTEM SCAN");
            for (int i = 0; i < n; i++) {
                if (a[i] == k) {
                    pos = i;
                    break;
                }
            }
        } else { // Binary Search
            printHeader("EXECUTING BINARY REGISTER SCAN");
            while (l <= r) {
                int m = l + (r - l) / 2;
                if (a[m] == k) {
                    pos = m;
                    break;
                }
                if (a[m] < k) l = m + 1;
                else r = m - 1;
            }
        }

        if (pos != -1) {
            System.out.printf(GREEN + "  (+) Success: Element %d safely located at array index [%d]\n" + RESET, k, pos);
        } else {
            System.out.println(RED + " [!] ERROR: Query target match missing from active registers." + RESET);
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

        int n = 0;
        int k;
        int[] a = new int[100];

        System.out.println(CYAN + "==================================================");
        System.out.println("     [M] DATA SEARCH & RETRIEVAL INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.printf(CYAN + "\n [MAIN MENU] Active Blocks: %d elements recorded\n" + RESET, n);
            System.out.println("  1.  (+) Input Main Array Block Data");
            System.out.println("  2.  (*) Run Linear Search query sequence");
            System.out.println("  3.  (*) Run Binary Search query sequence (Requires Sorted Data)");
            System.out.println("  4.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int opt = scanner.nextInt();

            if (opt == 4) {
                System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                break;
            }

            switch (opt) {
                case 1:
                    System.out.print(AMBER + "  [?] Array Size Limit Allocation: " + RESET);
                    n = scanner.nextInt();
                    if (n <= 0 || n > 100) {
                        System.out.println(RED + " [!] ERROR: Target index falls outside variable parameters." + RESET);
                        n = 0;
                        continue;
                    }
                    System.out.printf(AMBER + "  [?] Enter %d Sequential Values: " + RESET, n);
                    for (int i = 0; i < n; i++) a[i] = scanner.nextInt();
                    System.out.println(GREEN + "  (+) Success: Array registers updated with committed values." + RESET);
                    break;

                case 2:
                case 3:
                    if (n == 0) {
                        System.out.println(RED + " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY" + RESET);
                    } else {
                        System.out.print(AMBER + "  [?] Enter Search Target Value: " + RESET);
                        k = scanner.nextInt();
                        find(a, n, k, opt);
                    }
                    break;

                default:
                    System.out.println(RED + " [!] WARNING: Operational instruction unrecognized.");
            }
        }
    }
}