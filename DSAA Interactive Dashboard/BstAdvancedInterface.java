import java.util.Scanner;

public class BstAdvancedInterface {
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

    // Java wrapper helper object to simulate dynamic pointer-to-pointer modifications
    static class OperationResult {
        Node root;
        boolean found;
        OperationResult(Node r, boolean f) { this.root = r; this.found = f; }
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
        System.out.println(" This system provides a unified interface for full-lifecycle Binary Search Tree maintenance:\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Allocate integers via option 1 to grow your tree dynamically on the heap.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Run a rapid binary query search via option 2 to check node existence.");
        System.out.println(AMBER + " [STEP 3]" + RESET + " Remove any element via option 3, which handles three unique deletion states:");
        System.out.println("   • " + GREEN + "Leaf Node:" + RESET + " Simply freed and replaced with null.");
        System.out.println("   • " + GREEN + "Single-Child Node:" + RESET + " Drops the target and bypass-links directly to its only child.");
        System.out.println("   • " + GREEN + "Dual-Child Node:" + RESET + " Replaces values with its structural in-order successor, then deletes.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize operational management kernel...");
        scanner.nextLine();
    }

    private static OperationResult operate(Node currentRoot, int val, int mode) {
        if (currentRoot == null) {
            if (mode != 1) return new OperationResult(null, false);
            return new OperationResult(new Node(val), false);
        }

        boolean found = false;
        if (val < currentRoot.data) {
            OperationResult res = operate(currentRoot.left, val, mode);
            currentRoot.left = res.root;
            found = res.found;
        } else if (val > currentRoot.data) {
            OperationResult res = operate(currentRoot.right, val, mode);
            currentRoot.right = res.root;
            found = res.found;
        } else {
            found = true;
            if (mode == 3) {
                if (currentRoot.left == null || currentRoot.right == null) {
                    Node temp = currentRoot.left != null ? currentRoot.left : currentRoot.right;
                    return new OperationResult(temp, true);
                }
                Node successor = currentRoot.right;
                while (successor.left != null) {
                    successor = successor.left;
                }
                currentRoot.data = successor.data;
                OperationResult res = operate(currentRoot.right, successor.data, 3);
                currentRoot.right = res.root;
            }
        }
        return new OperationResult(currentRoot, found);
    }

    private static void visualize(Node currentRoot) {
        if (currentRoot == null) return;
        visualize(currentRoot.left);
        System.out.print(CYAN + "[" + currentRoot.data + "] " + RESET);
        visualize(currentRoot.right);
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
        System.out.println("     [M] BST ADVANCED MANAGEMENT INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.println(CYAN + "\n [MAIN MENU]" + RESET);
            System.out.println("  1.  (+) Insert Node Variable Element");
            System.out.println("  2.  (?) Query Scan Address Index (Search Target)");
            System.out.println("  3.  (-) Delete Target Node Link (Re-balance Layout)");
            System.out.println("  4.  (#) Traverse In-Order Visual Layout Sequence");
            System.out.println("  5.  (X) Terminate Control Kernel Execution");
            System.out.print(AMBER + " >>> Select Target Action Option: " + RESET);

            if (!scanner.hasNextInt()) break;
            int choice = scanner.nextInt();

            if (choice == 5) {
                System.out.println(RED + "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" + RESET);
                break;
            }

            if (choice >= 1 && choice <= 3) {
                if (root == null && choice > 1) {
                    System.out.println(RED + " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY" + RESET);
                    continue;
                }
                System.out.print(AMBER + "  [?] Target Allocation Value: " + RESET);
                int val = scanner.nextInt();

                if (choice == 1) {
                    root = operate(root, val, 1).root;
                    System.out.println(GREEN + "  (+) Success: Dynamic structural node safely allocated to heap." + RESET);
                } else if (choice == 2) {
                    boolean found = operate(root, val, 2).found;
                    if (found) System.out.printf(GREEN + "  (*) Located: Query target key match [%d] verified inside tree registry.\n" + RESET, val);
                    else System.out.printf(RED + "  [!] Missing: Query target match [%d] missing from active pointers.\n" + RESET, val);
                } else {
                    OperationResult res = operate(root, val, 3);
                    root = res.root;
                    if (res.found) System.out.printf(RED + "  (-) Dropped: Node pointer [%d] removed and address chain re-linked.\n" + RESET, val);
                    else System.out.println(RED + "  [!] ERROR: Target index falls outside available balance parameters." + RESET);
                }
            } else if (choice == 4) {
                printHeader("BST IN-ORDER TRAVERSAL (SORTED MATRIX VIEW)");
                if (root == null) System.out.print(RED + "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] " + RESET);
                else { System.out.print("  "); visualize(root); }
                System.out.println();
            } else {
                System.out.println(RED + " [!] WARNING: Operational instruction unrecognized.");
            }
        }
    }
}