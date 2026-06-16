import java.util.Scanner;

public class BinarySearchTreeInterface {
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

    static class Node {
        int data;
        Node left, right;
        Node(int val) { this.data = val; this.left = this.right = null; }
    }

    private static Node root = null;
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
        System.out.println(" Think of this system as an ordered hierarchical web branching from a parent Root node.\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Populate values via Option 1. Smaller values split left, larger values split right.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Run deep-dive recursive stream traces across three dimensions:");
        System.out.println("   • " + GREEN + "Pre-Order (1): " + RESET + " Evaluates parent hubs first, dipping into sub-branches next (Root->L->R).");
        System.out.println("   • " + GREEN + "In-Order (2):  " + RESET + " Ascends sequentially from left to right, listing elements sorted (L->Root->R).");
        System.out.println("   • " + GREEN + "Post-Order (3):" + RESET + " Sweeps leaves at the lowest layers before hitting upper hubs (L->R->Root).");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize hierarchical tree kernel...");
        scanner.nextLine();
    }

    private static Node insert(Node currentRoot, int data) {
        if (currentRoot == null) {
            return new Node(data);
        }

        if (data < currentRoot.data) {
            currentRoot.left = insert(currentRoot.left, data);
        } else if (data > currentRoot.data) {
            currentRoot.right = insert(currentRoot.right, data);
        } else {
            System.out.printf(AMBER + "  [!] Duplicate Flagged: Node value %d already exists within tree indexes.\n" + RESET, data);
        }
        return currentRoot;
    }

    private static void traverse(Node currentRoot, int mode) {
        if (currentRoot == null) return;

        if (mode == 1) System.out.print(GREEN + currentRoot.data + " " + RESET);
        traverse(currentRoot.left, mode);
        if (mode == 2) System.out.print(GREEN + currentRoot.data + " " + RESET);
        traverse(currentRoot.right, mode);
        if (mode == 3) System.out.print(GREEN + currentRoot.data + " " + RESET);
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
        System.out.println("     [M] BINARY SEARCH TREE CONTROL INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.println(CYAN + "\n [MAIN MENU]" + RESET);
            System.out.println("  1.  (+) Insert Node Variable Element");
            System.out.println("  2.  (*) Execute Pre-Order Traversal Stream (Root->L->R)");
            System.out.println("  3.  (*) Execute In-Order Traversal Stream (L->Root->R)");
            System.out.println("  4.  (*) Execute Post-Order Traversal Stream (L->R->Root)");
            System.out.println("  5.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int choice = scanner.nextInt();

            if (choice == 5) {
                System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                break;
            }

            switch (choice) {
                case 1:
                    System.out.print(AMBER + "  [?] Enter Element Map Value: " + RESET);
                    int val = scanner.nextInt();
                    root = insert(root, val);
                    System.out.println(GREEN + "  (+) Success: Node location calculated and variable saved." + RESET);
                    break;
                case 2:
                    printHeader("PRE-ORDER SEQUENCE (Root-L-R)");
                    if (root == null) System.out.println(RED + "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] " + RESET);
                    else { System.out.print("  "); traverse(root, 1); System.out.println(); }
                    break;
                case 3:
                    printHeader("IN-ORDER SEQUENCE (L-Root-R)");
                    if (root == null) System.out.println(RED + "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] " + RESET);
                    else { System.out.print("  "); traverse(root, 2); System.out.println(); }
                    break;
                case 4:
                    printHeader("POST-ORDER SEQUENCE (L-R-Root)");
                    if (root == null) System.out.println(RED + "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] " + RESET);
                    else { System.out.print("  "); traverse(root, 3); System.out.println(); }
                    break;
                default:
                    System.out.println(RED + " [!] WARNING: Operational instruction unrecognized.");
            }
        }
    }
}