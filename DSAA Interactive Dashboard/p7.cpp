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
    Node *prev, *next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

Node* head = nullptr;

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  [#] " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " Think of this program as a double-linked chain of data carriages moving both ways.\n\n"
              << AMBER << " [STEP 1]" << RESET << " Fire up an action item from the main control register.\n"
              << AMBER << " [STEP 2]" << RESET << " Choose a targeting sub-mode position variant:\n"
              << "   • " << GREEN << "Position 1 (Beg):" << RESET << " Snaps the new node directly onto the starting Head link.\n"
              << "   • " << GREEN << "Position 2 (End):" << RESET << " Explores through the sequence until finding a terminal tail.\n"
              << "   • " << GREEN << "Position 3 (Mid):" << RESET << " Tracks down a unique custom value, splicing inside inline.\n"
              << "   • " << GREEN << "Option 3 (View):" << RESET << "  Renders a visual dual-pointer arrow bidirectional layout map.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize bidirectional kernel engine...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

void insert(int type) {
    int val, loc;
    std::cout << AMBER << " [?] Input Value: " << RESET;
    std::cin >> val;
    Node* n = new Node(val);
    Node* t = head;

    if (!head) {
        head = n;
    } else if (type == 1) { // Beg
        n->next = head;
        head->prev = n;
        head = n;
    } else if (type == 2) { // End
        while (t->next) t = t->next;
        t->next = n;
        n->prev = t;
    } else { // Mid
        std::cout << AMBER << " [?] After which value?: " << RESET;
        std::cin >> loc;
        while (t && t->data != loc) t = t->next;
        if (!t) {
            std::cout << RED << " [!] ERROR: VALUE " << loc << " NOT FOUND IN ACTIVE REGISTERS!\n" << RESET;
            delete n;
            return;
        }
        n->next = t->next;
        n->prev = t;
        if (t->next) t->next->prev = n;
        t->next = n;
    }
    std::cout << GREEN << "  (+) Success: Element " << val << " safely linked inside node sequence.\n" << RESET;
}

void del(int type) {
    if (!head) {
        std::cout << RED << "\n [!] UNDERFLOW: DOUBLY LINKED LIST CONTAIN ZERO ELEMENTS!\n" << RESET;
        return;
    }
    Node* t = head;
    int loc;

    if (type == 1) { // Beg
        head = head->next;
        if (head) head->prev = nullptr;
    } else if (type == 2) { // End
        while (t->next) t = t->next;
        if (t->prev) t->prev->next = nullptr;
        else head = nullptr;
    } else { // Mid
        std::cout << AMBER << " [?] Value to Delete: " << RESET;
        std::cin >> loc;
        while (t && t->data != loc) t = t->next;
        if (!t) {
            std::cout << RED << " [!] ERROR: TARGET VALUE " << loc << " NOT LOCATED!\n" << RESET;
            return;
        }
        if (t->prev) t->prev->next = t->next;
        else head = t->next;
        if (t->next) t->next->prev = t->prev;
    }
    std::cout << RED << "  (-) Dropped: Bidirectional link unlinked -> node data [" << t->data << "]\n" << RESET;
    delete t;
}

void display() {
    printHeader("DOUBLY LINKED POINTER VISUALIZATION");
    if (!head) {
        std::cout << RED << "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" << RESET;
        return;
    }
    Node* t = head;
    std::cout << "  " << PURPLE << "NULL " << RESET;
    while (t) {
        std::cout << CYAN << "<=>" << RESET << " [" << t->data << "] ";
        t = t->next;
    }
    std::cout << PURPLE << "<=> NULL\n" << RESET;
}

int main() {
    int choice, sub;
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] DOUBLY LINKED LIST CONTROL INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU]\n" << RESET
                  << "  1.  (+) Insertion Interface\n"
                  << "  2.  (-) Deletion Interface\n"
                  << "  3.  (#) Visualize Node Layout Sequence\n"
                  << "  4.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> choice)) break;

        if (choice == 1 || choice == 2) {
            std::cout << CYAN << "  (>) Position Variable Allocation [1:Beg 2:End 3:Mid]: " << RESET;
            std::cin >> sub;
            if (sub >= 1 && sub <= 3) {
                if (choice == 1) insert(sub);
                else del(sub);
            } else {
                std::cout << RED << " [!] WARNING: Sub-parameter allocation error.\n" << RESET;
            }
        } else if (choice == 3) {
            display();
        } else if (choice == 4) {
            std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
            exit(0);
        } else {
            std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}