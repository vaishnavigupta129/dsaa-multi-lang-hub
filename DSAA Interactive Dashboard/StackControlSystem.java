import java.util.Scanner;

public class StackControlSystem {
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

    private static final int MAX = 5;
    private static final int[] stack = new int[MAX];
    private static int top = -1;
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
        System.out.println(" Think of this program as a vertical stack of dinner plates.\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Pick an option from the control menu below.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Understand the foundational LIFO rules:");
        System.out.println("   • " + GREEN + "Option 1 (Push):" + RESET + "  Slide a new item onto the very top of the stack.");
        System.out.println("   • " + GREEN + "Option 2 (Pop):" + RESET + "   Remove whichever item is currently resting on top.");
        System.out.println("   • " + GREEN + "Option 3 (Peep):" + RESET + "  Sneak a glance at the top item without removing it.");
        System.out.println("   • " + GREEN + "Option 4 (View):" + RESET + "  Draws a vertical diagram of your current storage.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize structural memory pool...");
        scanner.nextLine();
    }

    private static boolean isFull() { return top == MAX - 1; }
    private static boolean isEmpty() { return top == -1; }

    private static void push() {
        if (isFull()) {
            System.out.println(RED + "\n [▼] OVERFLOW Error: Stack memory allocation limits reached." + RESET);
        } else {
            System.out.print(AMBER + " [?] Input Value to Push: " + RESET);
            int v = scanner.nextInt();
            stack[++top] = v;
            System.out.printf(GREEN + "  ▲ Success: Value %d safely committed to address offset.\n" + RESET, v);
        }
    }

    private static void pop() {
        if (isEmpty()) {
            System.out.println(RED + "\n [▼] UNDERFLOW Error: Operational array contains zero elements." + RESET);
        } else {
            int v = stack[top--];
            System.out.printf(RED + "  ▼ Dropped: Memory cell released -> element [%d]\n" + RESET, v);
        }
    }

    private static void peep() {
        if (isEmpty()) {
            System.out.println(RED + "\n [!] STACK EMPTY: Registers have no top address target." + RESET);
        } else {
            System.out.printf(CYAN + "  ➔ Current Pointer Position Element: [%d]\n" + RESET, stack[top]);
        }
    }

    private static void traverse() {
        printHeader("CORE REGISTRY MEMORY VISUALIZATION");
        if (isEmpty()) {
            System.out.println(RED + "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" + RESET);
        } else {
            for (int i = top; i >= 0; i--) {
                if (i == top) {
                    System.out.printf(GREEN + "     | %-3d |  ➔ [TOP POINTER]\n" + RESET, stack[i]);
                } else {
                    System.out.printf(CYAN + "     | %-3d |\n" + RESET, stack[i]);
                }
                System.out.println("     +-----+");
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
        System.out.println("     ■ LIFO STORAGE ARRAY CONTROL SYSTEM ■");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.printf(CYAN + "\n [SYSTEM STATUS] Active Allocations: %d/%d bytes max\n" + RESET, top + 1, MAX);
            System.out.println("  1.  [+] Push (Insert Value Element)");
            System.out.println("  2.  [-] Pop (Destroy & Return Element)");
            System.out.println("  3.  [*] Peep (Read Top Vector Variable)");
            System.out.println("  4.  [#] Traverse Structural Visual");
            System.out.println("  5.  [$] Run Full Hardware Diagnostics Status");
            System.out.println("  6.  [X] Terminate Control Kernel Execution");
            System.out.print(AMBER + " >> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int ch = scanner.nextInt();

            if (ch == 6) {
                System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                break;
            }

            switch (ch) {
                case 1: push(); break;
                case 2: pop(); break;
                case 3: peep(); break;
                case 4: traverse(); break;
                case 5:
                    printHeader("HARDWARE ENVIRONMENT DIAGNOSTIC REPORT");
                    System.out.printf("  ■ Stack Register Allocation Capacity:  %d cells\n", MAX);
                    System.out.printf("  ■ Active Allocated Cell Count:        %d cells\n", top + 1);
                    System.out.printf("  ■ Boolean Condition Register Empty:   %s\n", isEmpty() ? RED + "TRUE (1)" + RESET : GREEN + "FALSE (0)" + RESET);
                    System.out.printf("  ■ Boolean Condition Register Full:    %s\n", isFull() ? RED + "TRUE (1)" + RESET : GREEN + "FALSE (0)" + RESET);
                    break;
                default:
                    System.out.println(RED + " [!] WARNING: Operational instruction unrecognized." + RESET);
            }
        }
    }
}