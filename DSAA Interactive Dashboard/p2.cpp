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

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  [#] " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " Think of this program as a chain of train cars (nodes) linked together.\n\n"
              << AMBER << " [STEP 1]" << RESET << " Pick an option from the main menu.\n"
              << AMBER << " [STEP 2]" << RESET << " Choose a specific position modifier when prompted:\n"
              << "   • " << GREEN << "1 (Beginning):" << RESET << " Add or remove from the very front of the train.\n"
              << "   • " << GREEN << "2 (Middle):"    << RESET << " Add after a specific value, or remove a chosen value.\n"
              << "   • " << GREEN << "3 (End):"       << RESET << " Add or remove from the very back of the train.\n"
              << "   • " << GREEN << "Option 3 (View):" << RESET << " Always use this to print your current link map.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize dynamic system...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

void op(Node** h, int mode, int type) {
    if (mode == 2 && !*h) {
        std::cout << RED << "\n [!] UNDERFLOW: LINKED LIST EMPTY\n" << RESET;
        return;
    }

    int val, target;
    Node* temp = *h;
    Node* prev = nullptr;

    if (mode == 1) { // Insertion
        std::cout << AMBER << " [?] Input Value: " << RESET; std::cin >> val;
        Node* nn = new Node(val);

        if (type == 1 || !*h) {
            nn->next = *h; *h = nn;
        } else if (type == 3) {
            while (temp->next) temp = temp->next;
            temp->next = nn;
        } else {
            std::cout << AMBER << " [?] After Value: " << RESET; std::cin >> target;
            while (temp && temp->data != target) temp = temp->next;
            if (temp) { nn->next = temp->next; temp->next = nn; }
            else { std::cout << RED << " [!] ERROR: " << target << " NOT FOUND IN LIST\n" << RESET; delete nn; return; }
        }
        std::cout << GREEN << "  (+) Success: Node safely allocated to pointer offset sequence.\n" << RESET;
    } else { // Deletion
        if (type == 1) { temp = *h; *h = (*h)->next; }
        else if (type == 3) {
            while (temp->next) { prev = temp; temp = temp->next; }
            if (prev) prev->next = nullptr; else *h = nullptr;
        } else {
            std::cout << AMBER << " [?] Delete Value: " << RESET; std::cin >> target;
            while (temp && temp->data != target) { prev = temp; temp = temp->next; }
            if (temp) { if (prev) prev->next = temp->next; else *h = temp->next; }
            else { std::cout << RED << " [!] ERROR: TARGET NOT LOCATED\n" << RESET; return; }
        }
        std::cout << RED << "  (-) Dropped: Memory cell unlinked -> node data [" << temp->data << "]\n" << RESET;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;
    int c, s;

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] SINGLY LINKED LIST CONTROL INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU]\n" << RESET
                  << "  1.  (+) Insertion Interface\n"
                  << "  2.  (-) Deletion Interface\n"
                  << "  3.  (#) Visualize Node Layout Sequence\n"
                  << "  4.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;
        std::cin >> c;

        if (c == 3) {
            printHeader("DYNAMIC REGISTER NODE VISUALIZATION");
            Node* t = head;
            std::cout << "  ";
            if (!t) std::cout << RED << "[ !! EMPTY MEMORY POOL REGISTER !! ]" << RESET;
            while (t) {
                std::cout << CYAN << "[" << t->data << "]" << RESET << " -> ";
                t = t->next;
            }
            std::cout << PURPLE << "NULL\n" << RESET;
        } else if (c == 4) {
            std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
            exit(0);
        } else if (c < 3 && c > 0) {
            std::cout << CYAN << "  (>) Position Variable Allocation [1:Beg 2:Mid 3:End]: " << RESET;
            std::cin >> s;
            if (s >= 1 && s <= 3) {
                op(&head, c, s);
            } else {
                std::cout << RED << " [!] WARNING: Sub-parameter allocation error.\n" << RESET;
            }
        } else {
            std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}