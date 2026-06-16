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
              << " This system provides a unified interface for full-lifecycle Binary Search Tree maintenance:\n\n"
              << AMBER << " [STEP 1]" << RESET << " Allocate integers via option 1 to grow your tree dynamically on the heap.\n"
              << AMBER << " [STEP 2]" << RESET << " Run a rapid binary query search via option 2 to check node existence.\n"
              << AMBER << " [STEP 3]" << RESET << " Remove any element via option 3, which handles three unique deletion states:\n"
              << "   • " << GREEN << "Leaf Node:" << RESET << " Simply freed and replaced with null.\n"
              << "   • " << GREEN << "Single-Child Node:" << RESET << " Drops the target and bypass-links directly to its only child.\n"
              << "   • " << GREEN << "Dual-Child Node:" << RESET << " Replaces values with its structural in-order successor, then deletes.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize operational management kernel...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

Node* operate(Node* root, int val, int mode, int& found) {
    if (!root) {
        if (mode != 1) return nullptr;
        return new Node(val);
    }

    if (val < root->data) {
        root->left = operate(root->left, val, mode, found);
    } else if (val > root->data) {
        root->right = operate(root->right, val, mode, found);
    } else {
        found = 1;
        if (mode == 3) {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            }
            Node* successor = root->right;
            while (successor->left) successor = successor->left;
            root->data = successor->data;
            root->right = operate(root->right, successor->data, 3, found);
        }
    }
    return root;
}

void visualize(Node* root) {
    if (!root) return;
    visualize(root->left);
    std::cout << CYAN << "[" << root->data << "] " << RESET;
    visualize(root->right);
}

int main() {
    Node* root = nullptr;
    int choice, val, found;

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] BST ADVANCED MANAGEMENT INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU]\n" << RESET
                  << "  1.  (+) Insert Node Variable Element\n"
                  << "  2.  (?) Query Scan Address Index (Search Target)\n"
                  << "  3.  (-) Delete Target Node Link (Re-balance Layout)\n"
                  << "  4.  (#) Traverse In-Order Visual Layout Sequence\n"
                  << "  5.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> choice)) break;
        if (choice == 5) {
            std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
            break;
        }

        if (choice >= 1 && choice <= 3) {
            if (!root && choice > 1) {
                std::cout << RED << " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY\n" << RESET;
                continue;
            }
            std::cout << AMBER << "  [?] Target Allocation Value: " << RESET;
            std::cin >> val;
            found = 0;

            if (choice == 1) {
                root = operate(root, val, 1, found);
                std::cout << GREEN << "  (+) Success: Dynamic structural node safely allocated to heap.\n" << RESET;
            } else if (choice == 2) {
                operate(root, val, 2, found);
                if (found) std::cout << GREEN << "  (*) Located: Query target key match [" << val << "] verified inside tree registry.\n" << RESET;
                else std::cout << RED << "  [!] Missing: Query target match [" << val << "] missing from active pointers.\n" << RESET;
            } else {
                root = operate(root, val, 3, found);
                if (found) std::cout << RED << "  (-) Dropped: Node pointer [" << val << "] removed and address chain re-linked.\n" << RESET;
                else std::cout << RED << "  [!] ERROR: Target index falls outside available balance parameters.\n" << RESET;
            }
        } else if (choice == 4) {
            printHeader("BST IN-ORDER TRAVERSAL (SORTED MATRIX VIEW)");
            if (!root) std::cout << RED << "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] ";
            else { std::cout << "  "; visualize(root); }
            std::cout << "\n";
        } else {
            std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}