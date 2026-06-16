#include <iostream>
#include <cstdlib>
#include <string>

#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

const int MAX = 5;
int stack[MAX];
int top = -1;

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  ◆ " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " Think of this program as a vertical stack of dinner plates.\n\n"
              << AMBER << " [STEP 1]" << RESET << " Pick an option from the control menu below.\n"
              << AMBER << " [STEP 2]" << RESET << " Understand the foundational LIFO rules:\n"
              << "   • " << GREEN << "Option 1 (Push):" << RESET << "  Slide a new item onto the very top of the stack.\n"
              << "   • " << GREEN << "Option 2 (Pop):" << RESET << "   Remove whichever item is currently resting on top.\n"
              << "   • " << GREEN << "Option 3 (Peep):" << RESET << "  Sneak a glance at the top item without removing it.\n"
              << "   • " << GREEN << "Option 4 (View):" << RESET << "  Draws a vertical diagram of your current storage.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize structural memory pool...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

bool is_full() { return top == MAX - 1; }
bool is_empty() { return top == -1; }

void push() {
    int v;
    if (is_full()) {
        std::cout << RED << "\n [▼] OVERFLOW Error: Stack memory allocation limits reached.\n" << RESET;
    } else {
        std::cout << AMBER << " [?] Input Value to Push: " << RESET;
        std::cin >> v;
        stack[++top] = v;
        std::cout << GREEN << "  ▲ Success: Value " << v << " safely committed to address offset.\n" << RESET;
    }
}

void pop() {
    if (is_empty()) {
        std::cout << RED << "\n [▼] UNDERFLOW Error: Operational array contains zero elements.\n" << RESET;
    } else {
        int v = stack[top--];
        std::cout << RED << "  ▼ Dropped: Memory cell released -> element [" << v << "]\n" << RESET;
    }
}

void peep() {
    if (is_empty()) {
        std::cout << RED << "\n [!] STACK EMPTY: Registers have no top address target.\n" << RESET;
    } else {
        std::cout << CYAN << "  ➔ Current Pointer Position Element: [" << stack[top] << "]\n" << RESET;
    }
}

void traverse() {
    printHeader("CORE REGISTRY MEMORY VISUALIZATION");
    if (is_empty()) {
        std::cout << RED << "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" << RESET;
    } else {
        for (int i = top; i >= 0; i--) {
            if (i == top) {
                printf(GREEN "     | %-3d |  ➔ [TOP POINTER]\n" RESET, stack[i]);
            } else {
                printf(CYAN "     | %-3d |\n" RESET, stack[i]);
            }
            std::cout << "     +-----+\n";
        }
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
              << "     ■ LIFO STORAGE ARRAY CONTROL SYSTEM ■\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [SYSTEM STATUS] Active Allocations: " << (top + 1) << "/" << MAX << " bytes max\n" << RESET
                  << "  1.  [+] Push (Insert Value Element)\n"
                  << "  2.  [-] Pop (Destroy & Return Element)\n"
                  << "  3.  [*] Peep (Read Top Vector Variable)\n"
                  << "  4.  [#] Traverse Structural Visual\n"
                  << "  5.  [$] Run Full Hardware Diagnostics Status\n"
                  << "  6.  [X] Terminate Control Kernel Execution\n"
                  << AMBER << " >> Select Target Action Option: " << RESET;

        if (!(std::cin >> ch) || ch == 6) {
            std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
            break;
        }

        switch (ch) {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: peep(); break;
            case 4: traverse(); break;
            case 5:
                printHeader("HARDWARE ENVIRONMENT DIAGNOSTIC REPORT");
                std::cout << "  ■ Stack Register Allocation Capacity:  " << MAX << " cells\n"
                          << "  ■ Active Allocated Cell Count:        " << (top + 1) << " cells\n"
                          << "  ■ Boolean Condition Register Empty:   " << (is_empty() ? RED "TRUE (1)" RESET : GREEN "FALSE (0)" RESET) << "\n"
                          << "  ■ Boolean Condition Register Full:    " << (is_full() ? RED "TRUE (1)" RESET : GREEN "FALSE (0)" RESET) << "\n";
                break;
            default:
                std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}