import java.util.Scanner;

public class SortingSystemInterface {
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
        System.out.println(" This matrix tests sorting complexities across four distinct computing behaviors:\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Fire option 1 to allocate dynamic space and input raw registers.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Run a targeting execution strategy:");
        System.out.println("   • " + GREEN + "Bubble Sort (2):   " + RESET + " Sweeps elements iteratively, floating highest values ($O(N^2)$).");
        System.out.println("   • " + GREEN + "Selection Sort (3):" + RESET + " Scans looking for minimum elements, placing them at the front ($O(N^2)$).");
        System.out.println("   • " + GREEN + "Insertion Sort (4):" + RESET + " Inserts values back into a growing sorted left sub-array frame ($O(N^2)$).");
        System.out.println("   • " + GREEN + "Quick Sort (5):    " + RESET + " Logarithmic divide-and-conquer strategy using a pivot point ($O(N \\log N)$).");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize algorithmic sorting engine...");
        scanner.nextLine();
    }

    private static void swap(int[] a, int i, int j) {
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }

    private static void bubble(int[] a, int n) {
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - i - 1; j++)
                if (a[j] > a[j + 1]) swap(a, j, j + 1);
    }

    private static void selection(int[] a, int n) {
        for (int i = 0; i < n - 1; i++) {
            int min = i;
            for (int j = i + 1; j < n; j++) if (a[j] < a[min]) min = j;
            swap(a, min, i);
        }
    }

    private static void insertion(int[] a, int n) {
        for (int i = 1; i < n; i++) {
            int k = a[i], j = i - 1;
            while (j >= 0 && a[j] > k) { a[j + 1] = a[j]; j--; }
            a[j + 1] = k;
        }
    }

    private static int partition(int[] a, int l, int h) {
        int p = a[h], i = l - 1;
        for (int j = l; j < h; j++) if (a[j] < p) swap(a, ++i, j);
        swap(a, i + 1, h);
        return i + 1;
    }

    private static void quick(int[] a, int l, int h) {
        if (l < h) {
            int pi = partition(a, l, h);
            quick(a, l, pi - 1);
            quick(a, pi + 1, h);
        }
    }

    private static void display(int[] a, int n) {
        System.out.print(GREEN + "  (+) Sorted Sequence: " + RESET);
        for (int i = 0; i < n; i++) System.out.print(a[i] + " ");
        System.out.println();
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
        int[] arr = null;

        System.out.println(CYAN + "==================================================");
        System.out.println("     [M] ALGORITHMIC SORTING SYSTEM INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.printf(CYAN + "\n [MAIN MENU] Active Matrix: %d elements loaded\n" + RESET, n);
            System.out.println("  1.  (+) Load Data Buffer (Dynamic Array Input)");
            System.out.println("  2.  (*) Execute Bubble Sort Strategy");
            System.out.println("  3.  (*) Execute Selection Sort Strategy");
            System.out.println("  4.  (*) Execute Insertion Sort Strategy");
            System.out.println("  5.  (*) Execute Quick Sort Divide-and-Conquer");
            System.out.println("  6.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int choice = scanner.nextInt();

            if (choice == 6) {
                System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                break;
            }

            if (choice == 1) {
                System.out.print(AMBER + "  [?] Array Size Limit Allocation: " + RESET);
                n = scanner.nextInt();
                if (n <= 0) {
                    System.out.println(RED + " [!] ERROR: Target index falls outside variable parameters." + RESET);
                    n = 0;
                    continue;
                }
                arr = new int[n];
                System.out.printf(AMBER + "  [?] Enter %d Matrix Elements: " + RESET, n);
                for (int i = 0; i < n; i++) arr[i] = scanner.nextInt();
                System.out.println(GREEN + "  (+) Success: Matrix registers dynamically scaled and elements saved.");
                continue;
            }

            if (n == 0 || arr == null) {
                System.out.println(RED + " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY. RUN ACTION 1." + RESET);
                continue;
            }

            switch (choice) {
                case 2: printHeader("EXECUTING BUBBLE SORT STRATEGY"); bubble(arr, n); break;
                case 3: printHeader("EXECUTING SELECTION SORT STRATEGY"); selection(arr, n); break;
                case 4: printHeader("EXECUTING INSERTION SORT STRATEGY"); insertion(arr, n); break;
                case 5: printHeader("EXECUTING QUICK SORT DIVIDE-AND-CONQUER"); quick(arr, 0, n - 1); break;
                default: System.out.println(RED + " [!] WARNING: Operational instruction unrecognized."); continue;
            }
            display(arr, n);
        }
    }
}