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
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* top = nullptr;

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  [#] " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " Think of this program as a stack of boxes connected via pointers on a heap.\n\n"
              << AMBER << " [STEP 1]" << RESET << " Interact with the core kernel functions below.\n"
              << AMBER << " [STEP 2]" << RESET << " Observe your dynamic runtime behaviors:\n"
              << "   • " << GREEN << "Option 1 (Push):" << RESET << "  Spawns a node out of heap memory and updates the top layer.\n"
              << "   • " << GREEN << "Option 2 (Pop):" << RESET << "   Unlinks the top container, returning its data to cell zero.\n"
              << "   • " << GREEN << "Option 3 (Peep):" << RESET << "  Points explicitly to current node targets without unlinking.\n"
              << "   • " << GREEN << "Option 4 (View):" << RESET << "  Outputs sequential link maps terminated with a NULL string.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize dynamic stack engine...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

bool is_empty() { return top == nullptr; }

bool is_full() {
    Node* t = new(std::nothrow) Node(0);
    if (t) { delete t; return false; }
    return true;
}

void push() {
    int val;
    Node* n = new(std::nothrow) Node(0);
    if (!n) {
        std::cout << RED << "\n [!] OVERFLOW: SYSTEM MEMORY DEPLETED\n" << RESET;
        return;
    }
    std::cout << AMBER << " [?] Input Value to Push: " << RESET;
    std::cin >> val;

    n->data = val;
    n->next = top;
    top = n;
    std::cout << GREEN << "  (+) Success: Node safely pushed and linked to top address.\n" << RESET;
}

void pop() {
    if (is_empty()) {
        std::cout << RED << "\n [!] UNDERFLOW: LINKED STACK CONTAIN ZERO ELEMENTS\n" << RESET;
        return;
    }
    Node* t = top;
    int v = t->data;
    top = top->next;
    delete t;
    std::cout << RED << "  (-) Dropped: Top heap cell popped -> element data [" << v << "]\n" << RESET;
}

void peep() {
    if (is_empty()) {
        std::cout << RED << "\n [!] EMPTY: Operational reference pointer targets NULL.\n" << RESET;
    } else {
        std::cout << CYAN << "  (>) Current Stack Pointer Vector: [" << top->data << "]\n" << RESET;
    }
}

void traverse() {
    printHeader("DYNAMIC STACK MEMORY VISUALIZATION");
    if (is_empty()) {
        std::cout << RED << "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" << RESET;
    } else {
        Node* t = top;
        std::cout << "  ";
        while (t) {
            if (t == top)
                std::cout << GREEN << "[" << t->data << "]" << RESET << " (TOP Pointer) -> ";
            else
                std::cout << CYAN << "[" << t->data << "]" << RESET << " -> ";
            t = t->next;
        }
        std::cout << PURPLE << "NULL\n" << RESET;
    }
}

int main() {
    int ch;
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] DYNAMIC LINKED STACK INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU]\n" << RESET
                  << "  1.  (+) Push Allocation (Insert Element)\n"
                  << "  2.  (-) Pop Destruction (Remove Element)\n"
                  << "  3.  (*) Peep Offset Address Reference\n"
                  << "  4.  (#) Traverse Node Layout Sequence\n"
                  << "  5.  [$] Run Heap Diagnostics Status\n"
                  << "  6.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> ch)) break;

        switch (ch) {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: peep(); break;
            case 4: traverse(); break;
            case 5:
                printHeader("HEAP REGISTRY DIAGNOSTIC REPORT");
                std::cout << "  [-] Stack Pointer State Empty:   " << (is_empty() ? RED "TRUE (NULL)" RESET : GREEN "FALSE (Active Pointer)" RESET) << "\n"
                          << "  [-] System RAM Boundary Limit:   " << (is_full() ? RED "REACHED (0 Bytes Free)" RESET : GREEN "AVAILABLE (Dynamic Allocations Allowed)" RESET) << "\n";
                break;
            case 6:
                std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
                exit(0);
            default:
                std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}