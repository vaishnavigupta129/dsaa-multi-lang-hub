import java.util.Scanner;

public class LinkedListControlInterface {
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

    private static Node head = null;
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
        System.out.println(" Think of this program as a chain of train cars (nodes) linked together.\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Pick an option from the main menu.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Choose a specific position modifier when prompted:");
        System.out.println("   • " + GREEN + "1 (Beginning):" + RESET + " Add or remove from the very front of the train.");
        System.out.println("   • " + GREEN + "2 (Middle):"    + RESET + " Add after a specific value, or remove a chosen value.");
        System.out.println("   • " + GREEN + "3 (End):"       + RESET + " Add or remove from the very back of the train.");
        System.out.println("   • " + GREEN + "Option 3 (View):" + RESET + " Always use this to print your current link map.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize dynamic system...");
        scanner.nextLine();
    }

    private static void op(int mode, int type) {
        if (mode == 2 && head == null) {
            System.out.println(RED + "\n [!] UNDERFLOW: LINKED LIST EMPTY" + RESET);
            return;
        }

        Node temp = head;
        Node prev = null;

        if (mode == 1) { // Insertion
            System.out.print(AMBER + " [?] Input Value: " + RESET);
            int val = scanner.nextInt();
            Node nn = new Node(val);

            if (type == 1 || head == null) {
                nn.next = head; head = nn;
            } else if (type == 3) {
                while (temp.next != null) temp = temp.next;
                temp.next = nn;
            } else {
                System.out.print(AMBER + " [?] After Value: " + RESET);
                int target = scanner.nextInt();
                while (temp != null && temp.data != target) temp = temp.next;
                if (temp != null) { nn.next = temp.next; temp.next = nn; }
                else { System.out.println(RED + " [!] ERROR: " + target + " NOT FOUND IN LIST" + RESET); return; }
            }
            System.out.println(GREEN + "  (+) Success: Node safely allocated to pointer offset sequence." + RESET);
        } else { // Deletion
            if (type == 1) { head = head.next; }
            else if (type == 3) {
                while (temp.next != null) { prev = temp; temp = temp.next; }
                if (prev != null) prev.next = null; else head = null;
            } else {
                System.out.print(AMBER + " [?] Delete Value: " + RESET);
                int target = scanner.nextInt();
                while (temp != null && temp.data != target) { prev = temp; temp = temp.next; }
                if (temp != null) { if (prev != null) prev.next = temp.next; else head = temp.next; }
                else { System.out.println(RED + " [!] ERROR: TARGET NOT LOCATED" + RESET); return; }
            }
            System.out.println(RED + "  (-) Dropped: Memory cell unlinked -> node data [" + temp.data + "]" + RESET);
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
        System.out.println("     [M] SINGLY LINKED LIST CONTROL INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.println(CYAN + "\n [MAIN MENU]" + RESET);
            System.out.println("  1.  (+) Insertion Interface");
            System.out.println("  2.  (-) Deletion Interface");
            System.out.println("  3.  (#) Visualize Node Layout Sequence");
            System.out.println("  4.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            int c = scanner.nextInt();

            if (c == 3) {
                printHeader("DYNAMIC REGISTER NODE VISUALIZATION");
                Node t = head;
                System.out.print("  ");
                if (t == null) System.out.print(RED + "[ !! EMPTY MEMORY POOL REGISTER !! ]" + RESET);
                while (t != null) {
                    System.out.print(CYAN + "[" + t.data + "]" + RESET + " -> ");
                    t = t.next;
                }
                System.out.println(PURPLE + "NULL" + RESET);
            } else if (c == 4) {
                System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                return;
            } else if (c < 3 && c > 0) {
                System.out.print(CYAN + "  (>) Position Variable Allocation [1:Beg 2:Mid 3:End]: " + RESET);
                int s = scanner.nextInt();
                if (s >= 1 && s <= 3) {
                    op(c, s);
                } else {
                    System.out.println(RED + " [!] WARNING: Sub-parameter allocation error." + RESET);
                }
            } else {
                System.out.println(RED + " [!] WARNING: Operational instruction unrecognized." + RESET);
            }
        }
    }
}