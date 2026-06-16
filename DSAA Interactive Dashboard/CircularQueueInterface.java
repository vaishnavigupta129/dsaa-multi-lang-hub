import java.util.Scanner;

public class CircularQueueInterface {
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

    private static final int SIZE = 5;
    private static final int[] q = new int[SIZE];
    private static int front = -1, rear = -1;
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
        System.out.println(" Think of this program as a circular racetrack divided into slots.\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Select options from the control matrix down below.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Master the FIFO (First-In, First-Out) tracking logic:");
        System.out.println("   • " + GREEN + "Option 1 (Enqueue):" + RESET + " Enters an element at the [REAR] pointer.");
        System.out.println("   • " + GREEN + "Option 2 (Dequeue):" + RESET + " Extracts an element from the [FRONT] pointer.");
        System.out.println("   • " + GREEN + "Modulo Wrap-Around:" + RESET + " When data reaches slot 4, it wraps around back to slot 0!");
        System.out.println("   • " + GREEN + "Option 3 (View):" + RESET + "    Prints the layout path from Front to Rear explicitly.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize circular data matrix...");
        scanner.nextLine();
    }

    private static boolean isFull() { return (front == (rear + 1) % SIZE); }
    private static boolean isEmpty() { return (front == -1); }

    private static void enqueue() {
        if (isFull()) {
            System.out.println(RED + "\n [!] OVERFLOW: CIRCULAR DATA RING REGISTER IS FULL" + RESET);
        } else {
            System.out.print(AMBER + " [?] Input Value to Enqueue: " + RESET);
            int data = scanner.nextInt();
            if (front == -1) front = 0;
            rear = (rear + 1) % SIZE;
            q[rear] = data;
            System.out.printf(GREEN + "  (+) Success: Value %d committed to Ring Index %d\n" + RESET, data, rear);
        }
    }

    private static void dequeue() {
        if (isEmpty()) {
            System.out.println(RED + "\n [!] UNDERFLOW: CIRCULAR RING STORAGE CONTAIN ZERO ELEMENTS" + RESET);
        } else {
            int val = q[front];
            System.out.printf(RED + "  (-) Dropped: Address block released -> element [%d] from index %d\n" + RESET, val, front);
            if (front == rear) {
                front = rear = -1;
            } else {
                front = (front + 1) % SIZE;
            }
        }
    }

    private static void display() {
        printHeader("CIRCULAR RING MEMORY VISUALIZATION");
        if (isEmpty()) {
            System.out.println(RED + "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" + RESET);
        } else {
            int i = front;
            System.out.print(CYAN + " INDEX : " + RESET);
            int temp = front;
            while (true) {
                System.out.printf("%-5d", temp);
                if (temp == rear) break;
                temp = (temp + 1) % SIZE;
            }

            System.out.print(CYAN + "\n DATA  : " + RESET);
            while (true) {
                if (i == front && i == rear) System.out.print(GREEN + "[" + q[i] + "]" + RESET + "  ");
                else if (i == front) System.out.print(AMBER + "[" + q[i] + "]" + RESET + "  ");
                else if (i == rear) System.out.print(PURPLE + "[" + q[i] + "]" + RESET + "  ");
                else System.out.print("[" + q[i] + "]  ");

                if (i == rear) break;
                i = (i + 1) % SIZE;
            }
            System.out.println("\n" + AMBER + "  (Note: Front Node highlighted Amber | Rear Node highlighted Purple)" + RESET);
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
        System.out.println("     [M] CIRCULAR RING BUFFER CONTROL INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.println(CYAN + "\n [MAIN MENU]" + RESET);
            System.out.println("  1.  (+) Enqueue Interface (Insert Data)");
            System.out.println("  2.  (-) Dequeue Interface (Delete Data)");
            System.out.println("  3.  (#) Traverse Ring Buffer Visual Layout");
            System.out.println("  4.  [$] Run Queue Segment Diagnostics Status");
            System.out.println("  5.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int ch = scanner.nextInt();

            switch (ch) {
                case 1: enqueue(); break;
                case 2: dequeue(); break;
                case 3: display(); break;
                case 4:
                    printHeader("QUEUE HARDWARE DIAGNOSTIC REPORT");
                    System.out.printf("  [-] Active Memory Cells Max Bounds: %d units\n", SIZE);
                    System.out.printf("  [-] Current Front Address Offset:   %d\n", front);
                    System.out.printf("  [-] Current Rear Address Offset:    %d\n", rear);
                    System.out.printf("  [-] Ring Buffer Memory State Full:  %s\n", isFull() ? RED + "TRUE (1)" + RESET : GREEN + "FALSE (0)" + RESET);
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