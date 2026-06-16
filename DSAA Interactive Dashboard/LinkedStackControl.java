import java.util.Scanner;

public class LinkedStackControl {
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

    static class Node {
        int data;
        Node next;
        Node(int val) { this.data = val; this.next = null; }
    }

    private static Node top = null;
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
        System.out.println(" Think of this program as a stack of boxes connected via pointers on a heap.\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Interact with the core kernel functions below.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Observe your dynamic runtime behaviors:");
        System.out.println("   • " + GREEN + "Option 1 (Push):" + RESET + "  Spawns a node out of heap memory and updates the top layer.");
        System.out.println("   • " + GREEN + "Option 2 (Pop):" + RESET + "   Unlinks the top container, returning its data to cell zero.");
        System.out.println("   • " + GREEN + "Option 3 (Peep):" + RESET + "  Points explicitly to current node targets without unlinking.");
        System.out.println("   • " + GREEN + "Option 4 (View):" + RESET + "  Outputs sequential link maps terminated with a NULL string.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize dynamic stack engine...");
        scanner.nextLine();
    }

    private static boolean isEmpty() { return top == null; }
    private static boolean isFull() { return false; } // Java Virtual Machine handles allocations via automatic garbage collection boundaries

    private static void push() {
        System.out.print(AMBER + " [?] Input Value to Push: " + RESET);
        int val = scanner.nextInt();
        Node n = new Node(val);
        n.next = top;
        top = n;
        System.out.println(GREEN + "  (+) Success: Node safely pushed and linked to top address." + RESET);
    }

    private static void pop() {
        if (isEmpty()) {
            System.out.println(RED + "\n [!] UNDERFLOW: LINKED STACK CONTAIN ZERO ELEMENTS" + RESET);
            return;
        }
        Node t = top;
        int v = t.data;
        top = top.next;
        System.out.println(RED + "  (-) Dropped: Top heap cell popped -> element data [" + v + "]" + RESET);
    }

    private static void peep() {
        if (isEmpty()) {
            System.out.println(RED + "\n [!] EMPTY: Operational reference pointer targets NULL." + RESET);
        } else {
            System.out.printf(CYAN + "  (>) Current Stack Pointer Vector: [%d]\n" + RESET, top.data);
        }
    }

    private static void traverse() {
        printHeader("DYNAMIC STACK MEMORY VISUALIZATION");
        if (isEmpty()) {
            System.out.println(RED + "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" + RESET);
        } else {
            Node t = top;
            System.out.print("  ");
            while (t != null) {
                if (t == top) {
                    System.out.print(GREEN + "[" + t.data + "]" + RESET + " (TOP Pointer) -> ");
                } else {
                    System.out.print(CYAN + "[" + t.data + "]" + RESET + " -> ");
                }
                t = t.next;
            }
            System.out.println(PURPLE + "NULL" + RESET);
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
        System.out.println("     [M] DYNAMIC LINKED STACK INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.println(CYAN + "\n [MAIN MENU]" + RESET);
            System.out.println("  1.  (+) Push Allocation (Insert Element)");
            System.out.println("  2.  (-) Pop Destruction (Remove Element)");
            System.out.println("  3.  (*) Peep Offset Address Reference");
            System.out.println("  4.  (#) Traverse Node Layout Sequence");
            System.out.println("  5.  [$] Run Heap Diagnostics Status");
            System.out.println("  6.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int ch = scanner.nextInt();

            switch (ch) {
                case 1: push(); break;
                case 2: pop(); break;
                case 3: peep(); break;
                case 4: traverse(); break;
                case 5:
                    printHeader("HEAP REGISTRY DIAGNOSTIC REPORT");
                    System.out.printf("  [-] Stack Pointer State Empty:   %s\n", isEmpty() ? RED + "TRUE (NULL)" + RESET : GREEN + "FALSE (Active Pointer)" + RESET);
                    System.out.printf("  [-] System RAM Boundary Limit:   %s\n", isFull() ? RED + "REACHED (0 Bytes Free)" + RESET : GREEN + "AVAILABLE (Dynamic Allocations Allowed)" + RESET);
                    break;
                case 6:
                    System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                    return;
                default:
                    System.out.println(RED + " [!] WARNING: Operational instruction unrecognized." + RESET);
            }
        }
    }
}