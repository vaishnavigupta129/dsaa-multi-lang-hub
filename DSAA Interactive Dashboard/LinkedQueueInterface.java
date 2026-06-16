import java.util.Scanner;

public class LinkedQueueInterface {
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

    static class Queue {
        Node front, rear;
        Queue() { this.front = this.rear = null; }
    }

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
        System.out.println(" Think of this program as a lineup of customers connected dynamically via pointers.\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Interact with the core kernel functions below.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Observe your dynamic FIFO (First-In, First-Out) tracking:");
        System.out.println("   • " + GREEN + "Option 1 (Enqueue):" + RESET + " Appends a new node to the tail end of the [REAR] chain.");
        System.out.println("   • " + GREEN + "Option 2 (Dequeue):" + RESET + " Detaches and frees the oldest surviving element at [FRONT].");
        System.out.println("   • " + GREEN + "Option 3 (View):" + RESET + "    Outputs sequential address links maps terminated with a NULL string.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize dynamic queue interface...");
        scanner.nextLine();
    }

    private static boolean isEmpty(Queue q) { 
        return q.front == null; 
    }

    private static void enqueue(Queue q) {
        System.out.print(AMBER + " [?] Input Value to Enqueue: " + RESET);
        int val = scanner.nextInt();
        
        Node newNode = new Node(val);
        if (q.rear == null) {
            q.front = q.rear = newNode;
        } else {
            q.rear.next = newNode;
            q.rear = newNode;
        }
        System.out.println(GREEN + "  (+) Success: Dynamic node allocated and linked at rear pointer." + RESET);
    }

    private static void dequeue(Queue q) {
        if (isEmpty(q)) {
            System.out.println(RED + "\n [!] UNDERFLOW: LINKED QUEUE CONTAINS ZERO ELEMENTS" + RESET);
            return;
        }
        
        Node temp = q.front;
        int data = temp.data;
        q.front = q.front.next;
        
        if (q.front == null) {
            q.rear = null;
        }
        System.out.printf(RED + "  (-) Dropped: Front cell popped -> data [%d] unlinked & freed\n" + RESET, data);
    }

    private static void display(Queue q) {
        printHeader("DYNAMIC QUEUE MEMORY VISUALIZATION");
        if (isEmpty(q)) {
            System.out.println(RED + "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" + RESET);
            return;
        }
        
        Node temp = q.front;
        System.out.print("  ");
        while (temp != null) {
            if (temp == q.front) {
                System.out.print(AMBER + "[" + temp.data + "]" + RESET + " (FRONT) -> ");
            } else if (temp == q.rear) {
                System.out.print(PURPLE + "[" + temp.data + "]" + RESET + " (REAR) -> ");
            } else {
                System.out.print(CYAN + "[" + temp.data + "]" + RESET + " -> ");
            }
            temp = temp.next;
        }
        System.out.println(PURPLE + "NULL" + RESET);
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

        Queue q = new Queue();

        System.out.println(CYAN + "==================================================");
        System.out.println("     [M] DYNAMIC LINKED QUEUE INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.println(CYAN + "\n [MAIN MENU]" + RESET);
            System.out.println("  1.  (+) Enqueue Allocation (Insert Element)");
            System.out.println("  2.  (-) Dequeue Destruction (Remove Element)");
            System.out.println("  3.  (#) Traverse Node Layout Sequence");
            System.out.println("  4.  [$] Run Pointer Diagnostic Status");
            System.out.println("  5.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int choice = scanner.nextInt();

            switch (choice) {
                case 1: enqueue(q); break;
                case 2: dequeue(q); break;
                case 3: display(q); break;
                case 4:
                    printHeader("HEAP STRUCT POINTER DIAGNOSTIC REPORT");
                    String fPtr = (q.front != null) ? "0x" + Integer.toHexString(System.identityHashCode(q.front)).toUpperCase() : "NIL";
                    String rPtr = (q.rear != null) ? "0x" + Integer.toHexString(System.identityHashCode(q.rear)).toUpperCase() : "NIL";
                    System.out.printf("  [-] Front Structural Pointer:   %s\n", fPtr);
                    System.out.printf("  [-] Rear Structural Pointer :   %s\n", rPtr);
                    System.out.printf("  [-] Dynamic Memory State Empty: %s\n", isEmpty(q) ? RED + "TRUE (NULL)" + RESET : GREEN + "FALSE (Active Nodes)" + RESET);
                    break;
                case 5:
                    System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                    return;
                default:
                    System.out.println(RED + " [!] WARNING: Operational instruction unrecognized." + RESET);
            }
        }
    }
}