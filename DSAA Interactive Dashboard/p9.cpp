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
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
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
              << " Think of this system as an ordered hierarchical web branching from a parent Root node.\n\n"
              << AMBER << " [STEP 1]" << RESET << " Populate values via Option 1. Smaller values split left, larger values split right.\n"
              << AMBER << " [STEP 2]" << RESET << " Run deep-dive recursive stream traces across three dimensions:\n"
              << "   • " << GREEN << "Pre-Order (1): " << RESET << " Evaluates parent hubs first, dipping into sub-branches next (Root->L->R).\n"
              << "   • " << GREEN << "In-Order (2):  " << RESET << " Ascends sequentially from left to right, listing elements sorted (L->Root->R).\n"
              << "   • " << GREEN << "Post-Order (3):" << RESET << " Sweeps leaves at the lowest layers before hitting upper hubs (L->R->Root).\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize hierarchical tree kernel...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

Node* insert(Node* root, int data) {
    if (!root) {
        return new(std::nothrow) Node(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        std::cout << AMBER << "  [!] Duplicate Flagged: Node value " << data << " already exists within tree indexes.\n" << RESET;
    }
    return root;
}

void traverse(Node* root, int mode) {
    if (!root) return;

    if (mode == 1) std::cout << GREEN << root->data << " " << RESET;
    traverse(root->left, mode);
    if (mode == 2) std::cout << GREEN << root->data << " " << RESET;
    traverse(root->right, mode);
    if (mode == 3) std::cout << GREEN << root->data << " " << RESET;
}

int main() {
    Node* root = nullptr;
    int choice, val;

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] BINARY SEARCH TREE CONTROL INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU]\n" << RESET
                  << "  1.  (+) Insert Node Variable Element\n"
                  << "  2.  (*) Execute Pre-Order Traversal Stream (Root->L->R)\n"
                  << "  3.  (*) Execute In-Order Traversal Stream (L->Root->R)\n"
                  << "  4.  (*) Execute Post-Order Traversal Stream (L->R->Root)\n"
                  << "  5.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> choice)) break;
        if (choice == 5) {
            std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
            break;
        }

        switch (choice) {
            case 1:
                std::cout << AMBER << "  [?] Enter Element Map Value: " << RESET;
                if (std::cin >> val) {
                    root = insert(root, val);
                    std::cout << GREEN << "  (+) Success: Node location calculated and variable saved.\n" << RESET;
                }
                break;
            case 2:
                printHeader("PRE-ORDER SEQUENCE (Root-L-R)");
                if (!root) std::cout << RED << "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" << RESET;
                else { std::cout << "  "; traverse(root, 1); std::cout << "\n"; }
                break;
            case 3:
                printHeader("IN-ORDER SEQUENCE (L-Root-R)");
                if (!root) std::cout << RED << "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" << RESET;
                else { std::cout << "  "; traverse(root, 2); std::cout << "\n"; }
                break;
            case 4:
                printHeader("POST-ORDER SEQUENCE (L-R-Root)");
                if (!root) std::cout << RED << "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" << RESET;
                else { std::cout << "  "; traverse(root, 3); std::cout << "\n"; }
                break;
            default:
                std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}