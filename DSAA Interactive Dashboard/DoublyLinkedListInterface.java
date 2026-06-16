import java.util.Scanner;

public class DoublyLinkedListInterface {
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

    static class Node {
        int data;
        Node prev, next;
        Node(int val) { this.data = val; this.prev = this.next = null; }
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
        System.out.println(" Think of this program as a double-linked chain of data carriages moving both ways.\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Fire up an action item from the main control register.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Choose a targeting sub-mode position variant:");
        System.out.println("   • " + GREEN + "Position 1 (Beg):" + RESET + " Snaps the new node directly onto the starting Head link.");
        System.out.println("   • " + GREEN + "Position 2 (End):" + RESET + " Explores through the sequence until finding a terminal tail.");
        System.out.println("   • " + GREEN + "Position 3 (Mid):" + RESET + " Tracks down a unique custom value, splicing inside inline.");
        System.out.println("   • " + GREEN + "Option 3 (View):" + RESET + "  Renders a visual dual-pointer arrow bidirectional layout map.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize bidirectional kernel engine...");
        scanner.nextLine();
    }

    private static void insert(int type) {
        System.out.print(AMBER + " [?] Input Value: " + RESET);
        int val = scanner.nextInt();
        Node n = new Node(val);
        Node t = head;

        if (head == null) {
            head = n;
        } else if (type == 1) { // Beg
            n.next = head;
            head.prev = n;
            head = n;
        } else if (type == 2) { // End
            while (t.next != null) t = t.next;
            t.next = n;
            n.prev = t;
        } else { // Mid
            System.out.print(AMBER + " [?] After which value?: " + RESET);
            int loc = scanner.nextInt();
            while (t != null && t.data != loc) t = t.next;
            if (t == null) {
                System.out.printf(RED + " [!] ERROR: VALUE %d NOT FOUND IN ACTIVE REGISTERS!\n" + RESET, loc);
                return;
            }
            n.next = t.next;
            n.prev = t;
            if (t.next != null) t.next.prev = n;
            t.next = n;
        }
        System.out.printf(GREEN + "  (+) Success: Element %d safely linked inside node sequence.\n" + RESET, val);
    }

    private static void del(int type) {
        if (head == null) {
            System.out.println(RED + "\n [!] UNDERFLOW: DOUBLY LINKED LIST CONTAIN ZERO ELEMENTS!" + RESET);
            return;
        }
        Node t = head;

        if (type == 1) { // Beg
            head = head.next;
            if (head != null) head.prev = null;
        } else if (type == 2) { // End
            while (t.next != null) t = t.next;
            if (t.prev != null) t.prev.next = null;
            else head = null;
        } else { // Mid
            System.out.print(AMBER + " [?] Value to Delete: " + RESET);
            int loc = scanner.nextInt();
            while (t != null && t.data != loc) t = t.next;
            if (t == null) {
                System.out.printf(RED + " [!] ERROR: TARGET VALUE %d NOT LOCATED!\n" + RESET, loc);
                return;
            }
            if (t.prev != null) t.prev.next = t.next;
            else head = t.next;
            if (t.next != null) t.next.prev = t.prev;
        }
        System.out.printf(RED + "  (-) Dropped: Bidirectional link unlinked -> node data [%d]\n" + RESET, t.data);
    }

    private static void display() {
        printHeader("DOUBLY LINKED POINTER VISUALIZATION");
        if (head == null) {
            System.out.println(RED + "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" + RESET);
            return;
        }
        Node t = head;
        System.out.print("  " + PURPLE + "NULL " + RESET);
        while (t != null) {
            System.out.print(CYAN + "<=>" + RESET + " [" + t.data + "] ");
            t = t.next;
        }
        System.out.println(PURPLE + "<=> NULL" + RESET);
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
        System.out.println("     [M] DOUBLY LINKED LIST CONTROL INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.println(CYAN + "\n [MAIN MENU]" + RESET);
            System.out.println("  1.  (+) Insertion Interface");
            System.out.println("  2.  (-) Deletion Interface");
            System.out.println("  3.  (#) Visualize Node Layout Sequence");
            System.out.println("  4.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int choice = scanner.nextInt();

            if (choice == 1 || choice == 2) {
                System.out.print(CYAN + "  (>) Position Variable Allocation [1:Beg 2:End 3:Mid]: " + RESET);
                int sub = scanner.nextInt();
                if (sub >= 1 && sub <= 3) {
                    if (choice == 1) insert(sub);
                    else del(sub);
                } else {
                    System.out.println(RED + " [!] WARNING: Sub-parameter allocation error." + RESET);
                }
            } else if (choice == 3) {
                display();
            } else if (choice == 4) {
                System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                return;
            } else {
                System.out.println(RED + " [!] WARNING: Operational instruction unrecognized." + RESET);
            }
        }
    }
}