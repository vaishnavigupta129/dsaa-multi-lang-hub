import java.util.Scanner;

public class ArrayControlInterface {
    // ANSI Color Codes
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

    private static final int MAX = 100;
    private static int[] a = new int[MAX];
    private static int n = 0;
    private static int total = 0;
    private static Scanner scanner = new Scanner(System.in);

    private static void printHeader(String title) {
        System.out.println(PURPLE + "\n==================================================");
        System.out.println("  [#] " + title);
        System.out.println("==================================================" + RESET);
    }

    private static void printUserGuide() {
        System.out.println(CYAN + "\n==================================================");
        System.out.println("         CRASH COURSE: HOW TO USE THIS SYSTEM");
        System.out.println("==================================================" + RESET);
        System.out.println(" Think of this program as a digital shelf with numbered slots.\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Define how many total slots you want to use today.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Use the menu numbers below to manage your data:");
        System.out.println("   • " + GREEN + "Option 1 (Insert):" + RESET + " Type a value, then pick a slot (0, 1, 2...).");
        System.out.println("   • " + GREEN + "Option 6 (View):" + RESET + "   Always use this to see your current shelf map.");
        System.out.println("   • " + GREEN + "Option 2 (Delete):" + RESET + " Remove an item by typing its slot index number.");
        System.out.println("   • " + GREEN + "Option 5 (Sort):" + RESET + "   Organizes scrambled numbers from lowest to highest.");
        System.out.println("   • " + GREEN + "Option 3/4 (Search):" + RESET + "Finds what slot index a number is hiding in.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize system config...");
        scanner.nextLine();
    }

    private static boolean isEmpty() {
        if (n <= 0) {
            System.out.println(RED + "\n [!] UNDERFLOW: Operational array contains zero elements.\n" + RESET);
            return true;
        }
        return false;
    }

    private static void insert() {
        if (n >= MAX || n >= total) {
            System.out.println(RED + "\n [!] OVERFLOW: Allocation boundary limit reached.\n" + RESET);
            return;
        }
        System.out.print(AMBER + " [?] Enter Value: " + RESET);
        int v = scanner.nextInt();
        System.out.print(AMBER + " [?] Enter Position (0 to " + n + "): " + RESET);
        int p = scanner.nextInt();

        if (p < 0 || p > n) {
            System.out.println(RED + " [!] ERROR: Target index falls outside variable parameters.\n" + RESET);
            return;
        }

        for (int i = n++; i > p; i--) a[i] = a[i - 1];
        a[p] = v;
        System.out.println(GREEN + "  (+) Success: Element safely committed to index register.\n" + RESET);
    }

    private static void deleteItem() {
        if (isEmpty()) return;
        System.out.print(AMBER + " [?] Index to Delete (0 to " + (n - 1) + "): " + RESET);
        int p = scanner.nextInt();

        if (p < 0 || p >= n) {
            System.out.println(RED + " [!] ERROR: Target index falls outside variable parameters.\n" + RESET);
            return;
        }

        int removed = a[p];
        for (int i = p; i < --n; i++) a[i] = a[i + 1];
        System.out.println(RED + "  (-) Dropped: Memory cell released -> element [" + removed + "]\n" + RESET);
    }

    private static void search(int mode) {
        if (isEmpty()) return;
        System.out.print(AMBER + " [?] Search Value: " + RESET);
        int v = scanner.nextInt();

        int found = -1;
        if (mode == 1) { // Linear
            for (int i = 0; i < n; i++) {
                if (a[i] == v) { found = i; break; }
            }
        } else { // Binary
            int low = 0, high = n - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (a[mid] == v) { found = mid; break; }
                if (a[mid] < v) low = mid + 1;
                else high = mid - 1;
            }
        }

        if (found != -1) System.out.println(GREEN + "  (*) Located: Element matching query found at index [" + found + "]\n" + RESET);
        else System.out.println(RED + " [!] ERROR: Query target match missing from active registers.\n" + RESET);
    }

    private static void bubbleSort() {
        if (isEmpty()) return;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (a[j] > a[j + 1]) {
                    int t = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = t;
                }
            }
        }
        System.out.println(GREEN + "  (^) Sort Complete: Active registry block sequences reordered.\n" + RESET);
    }

    private static void display() {
        printHeader("STATIC DATA ARRAY VISUALIZATION");
        if (n == 0) {
            System.out.println(RED + "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" + RESET);
            return;
        }
        System.out.print(CYAN + " INDEX : " + RESET);
        for (int i = 0; i < n; i++) System.out.printf("%-5d", i);
        System.out.print(CYAN + "\n DATA  : " + RESET);
        for (int i = 0; i < n; i++) System.out.printf("[%d]  ", a[i]);
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

        System.out.println(CYAN + "==================================================");
        System.out.println("     [M] STATIC ARRAY CONTROL INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        System.out.print(AMBER + " [?] Define Max Target Capacity: " + RESET);
        total = scanner.nextInt();

        while (true) {
            System.out.printf(CYAN + "\n [SYSTEM STATUS] Active Blocks: %d/%d entries utilized\n" + RESET, n, total);
            System.out.println("  1.  (+) Insert Element");
            System.out.println("  2.  (-) Delete Element");
            System.out.println("  3.  (*) Run Linear Search query");
            System.out.println("  4.  (*) Run Binary Search query");
            System.out.println("  5.  (^) Run Structural Bubble Sort");
            System.out.println("  6.  (#) Traverse Structural Visual");
            System.out.println("  7.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int choice = scanner.nextInt();

            switch (choice) {
                case 1: insert(); break;
                case 2: deleteItem(); break;
                case 3: search(1); break;
                case 4: search(2); break;
                case 5: bubbleSort(); break;
                case 6: display(); break;
                case 7:
                    System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                    return;
                default:
                    System.out.println(RED + " [!] WARNING: Operational instruction unrecognized.\n" + RESET);
            }
        }
    }
}