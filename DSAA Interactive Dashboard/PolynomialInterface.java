import java.util.Scanner;

public class PolynomialInterface {
    private static final String RESET = "\033[0m";
    private static final String CYAN = "\033[1;36m";
    private static final String GREEN = "\033[1;32m";
    private static final String RED = "\033[1;31m";
    private static final String AMBER = "\033[1;33m";
    private static final String PURPLE = "\033[1;35m";

    static class Node {
        int coeff, exp;
        Node next;
        Node(int c, int e) { this.coeff = c; this.exp = e; this.next = null; }
    }

    static class Polynomial {
        Node head = null;
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
        System.out.println(" Think of this system as a dynamic warehouse storing mathematical expressions.\n");
        System.out.println(AMBER + " [STEP 1]" + RESET + " Populate Poly-1 or Poly-2 via options 1 and 2 by inputting elements.");
        System.out.println(AMBER + " [STEP 2]" + RESET + " Appreciate how sorted tracking operates under the hood:");
        System.out.println("   • " + GREEN + "Sorted Array Links:" + RESET + " Elements are auto-sorted in descending order of exponents.");
        System.out.println("   • " + GREEN + "Coefficient Merger:" + RESET + " Entering matching exponents merges their coefficients instantly.");
        System.out.println("   • " + GREEN + "Summation Kernel:" + RESET + "   Option 4 evaluates, merges, and presents the calculated results.");
        System.out.println(PURPLE + "==================================================\n" + RESET);
        System.out.print("Press " + AMBER + "[ENTER]" + RESET + " to initialize polynomial computational kernel...");
        scanner.nextLine();
    }

    private static void insert(Polynomial p, int c, int e) {
        if (c == 0) return;

        Node dummy = new Node(0, 999999);
        dummy.next = p.head;
        Node prev = dummy;
        Node curr = p.head;

        while (curr != null && curr.exp > e) {
            prev = curr;
            curr = curr.next;
        }

        if (curr != null && curr.exp == e) {
            curr.coeff += c;
        } else {
            Node newNode = new Node(c, e);
            newNode.next = curr;
            prev.next = newNode;
        }
        p.head = dummy.next;
    }

    private static void printPolynomial(Node head, String label) {
        if (head == null) {
            System.out.println(RED + "  [!] " + label + ": EMPTY REGISTER POOL" + RESET);
            return;
        }
        System.out.print(CYAN + "  [" + label + "]: " + RESET);
        Node curr = head;
        while (curr != null) {
            System.out.print(GREEN + curr.coeff + "x^" + curr.exp + RESET);
            if (curr.next != null) {
                System.out.print(AMBER + " + " + RESET);
            }
            curr = curr.next;
        }
        System.out.println();
    }

    private static Polynomial addPolynomials(Polynomial p1, Polynomial p2) {
        Polynomial result = new Polynomial();
        Node curr = p1.head;
        while (curr != null) {
            insert(result, curr.coeff, curr.exp);
            curr = curr.next;
        }
        curr = p2.head;
        while (curr != null) {
            insert(result, curr.coeff, curr.exp);
            curr = curr.next;
        }
        return result;
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

        Polynomial poly1 = new Polynomial();
        Polynomial poly2 = new Polynomial();

        System.out.println(CYAN + "==================================================");
        System.out.println("     [M] POLYNOMIAL COMPUTATION INTERFACE [M]");
        System.out.println("==================================================" + RESET);

        while (true) {
            System.out.println(CYAN + "\n [MAIN MENU]" + RESET);
            System.out.println("  1.  (+) Add Algebraic Term to POLY-1");
            System.out.println("  2.  (+) Add Algebraic Term to POLY-2");
            System.out.println("  3.  (#) Visualize Tracked Expression Maps");
            System.out.println("  4.  (=) Calculate Summation Product (P1 + P2)");
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
                case 2:
                    System.out.print(AMBER + "  [?] Enter Coefficient and Exponent [Format: c e]: " + RESET);
                    int c = scanner.nextInt();
                    int e = scanner.nextInt();
                    insert(choice == 1 ? poly1 : poly2, c, e);
                    System.out.println(GREEN + "  (+) Success: Linked term securely placed in polynomial node string." + RESET);
                    break;
                case 3:
                    printHeader("POLYNOMIAL DATA STRUCT STORAGE");
                    printPolynomial(poly1.head, "POLY-1");
                    printPolynomial(poly2.head, "POLY-2");
                    break;
                case 4:
                    if (poly1.head == null && poly2.head == null) {
                        System.out.println(RED + " [!] ERROR: OPERATIONAL EXPRESSION ARRAYS ARE COMPLETELY EMPTY" + RESET);
                    } else {
                        printHeader("ALGEBRAIC SUMMATION EVALUATION RESULT");
                        Polynomial res = addPolynomials(poly1, poly2);
                        printPolynomial(res.head, "RESULT");
                    }
                    break;
                default:
                    System.out.println(RED + " [!] WARNING: Operational instruction unrecognized." + RESET);
            }
        }
    }
}