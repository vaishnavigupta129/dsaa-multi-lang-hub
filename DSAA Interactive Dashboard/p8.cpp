#include <iostream>
#include <cstdlib>
#include <string>

#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

struct Node {
    int coeff, exp;
    Node* next;
    Node(int c, int e) : coeff(c), exp(e), next(nullptr) {}
};

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  [#] " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " Think of this system as a dynamic warehouse storing mathematical expressions.\n\n"
              << AMBER << " [STEP 1]" << RESET << " Populate Poly-1 or Poly-2 via options 1 and 2 by inputting elements.\n"
              << AMBER << " [STEP 2]" << RESET << " Appreciate how sorted tracking operates under the hood:\n"
              << "   • " << GREEN << "Sorted Array Links:" << RESET << " Elements are auto-sorted in descending order of exponents.\n"
              << "   • " << GREEN << "Coefficient Merger:" << RESET << " Entering matching exponents merges their coefficients instantly.\n"
              << "   • " << GREEN << "Summation Kernel:" << RESET << "   Option 4 evaluates, merges, and presents the calculated results.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize polynomial computational kernel...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

void insert(Node** head, int c, int e) {
    if (c == 0) return;
    
    while (*head && (*head)->exp > e) {
        head = &(*head)->next;
    }

    if (*head && (*head)->exp == e) {
        (*head)->coeff += c;
    } else {
        Node* newNode = new Node(c, e);
        newNode->next = *head;
        *head = newNode;
    }
}

void printPolynomial(Node* head, const std::string& label) {
    if (!head) {
        std::cout << RED << "  [!] " << label << ": EMPTY REGISTER POOL\n" << RESET;
        return;
    }
    std::cout << CYAN << "  [" << label << "]: " << RESET;
    while (head) {
        std::cout << GREEN << head->coeff << "x^" << head->exp << RESET;
        if (head->next) std::cout << AMBER << " + " << RESET;
        head = head->next;
    }
    std::cout << "\n";
}

Node* addPolynomials(Node* p1, Node* p2) {
    Node* result = nullptr;
    for (Node* curr = p1; curr; curr = curr->next) {
        insert(&result, curr->coeff, curr->exp);
    }
    for (Node* curr = p2; curr; curr = curr->next) {
        insert(&result, curr->coeff, curr->exp);
    }
    return result;
}

int main() {
    Node *p1 = nullptr, *p2 = nullptr;
    int choice, c, e;

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] POLYNOMIAL COMPUTATION INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU]\n" << RESET
                  << "  1.  (+) Add Algebraic Term to POLY-1\n"
                  << "  2.  (+) Add Algebraic Term to POLY-2\n"
                  << "  3.  (#) Visualize Tracked Expression Maps\n"
                  << "  4.  (=) Calculate Summation Product (P1 + P2)\n"
                  << "  5.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> choice)) break;
        if (choice == 5) {
            std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
            break;
        }

        switch (choice) {
            case 1:
            case 2:
                std::cout << AMBER << "  [?] Enter Coefficient and Exponent [Format: c e]: " << RESET;
                if (std::cin >> c >> e) {
                    insert(choice == 1 ? &p1 : &p2, c, e);
                    std::cout << GREEN << "  (+) Success: Linked term securely placed in polynomial node string.\n" << RESET;
                }
                break;
            case 3:
                printHeader("POLYNOMIAL DATA STRUCT STORAGE");
                printPolynomial(p1, "POLY-1");
                printPolynomial(p2, "POLY-2");
                break;
            case 4:
                if (!p1 && !p2) {
                    std::cout << RED << " [!] ERROR: OPERATIONAL EXPRESSION ARRAYS ARE COMPLETELY EMPTY\n" << RESET;
                } else {
                    printHeader("ALGEBRAIC SUMMATION EVALUATION RESULT");
                    Node* res = addPolynomials(p1, p2);
                    printPolynomial(res, "RESULT");
                }
                break;
            default:
                std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}