#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  [#] " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " Think of this system as an elite search database operating via two distinct algorithms.\n\n"
              << AMBER << " [STEP 1]" << RESET << " Allocate data size and input parameters via Main Menu option 1.\n"
              << AMBER << " [STEP 2]" << RESET << " Select an analytical search scan mode:\n"
              << "   • " << GREEN << "Linear Search (2):" << RESET << " Sweeps elements one by one. Works seamlessly on unsorted blocks.\n"
              << "   • " << GREEN << "Binary Search (3):" << RESET << " Divides sorted collections in half repeatedly. (Requires Sorted Inputs!)\n"
              << "   • " << GREEN << "Logarithmic Scale:" << RESET << " While Linear takes up to N steps, Binary finds targets in log(N) cuts.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize data lookup search kernel...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

void find(const std::vector<int>& a, int k, int mode) {
    int n = a.size();
    int l = 0, r = n - 1, pos = -1;

    if (mode == 2) { // Linear Search
        printHeader("EXECUTING LINEAR SYSTEM SCAN");
        for (int i = 0; i < n; i++) {
            if (a[i] == k) {
                pos = i;
                break;
            }
        }
    } else { // Binary Search
        printHeader("EXECUTING BINARY REGISTER SCAN");
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (a[m] == k) {
                pos = m;
                break;
            }
            if (a[m] < k) l = m + 1;
            else r = m - 1;
        }
    }

    if (pos != -1) {
        std::cout << GREEN << "  (+) Success: Element " << k << " safely located at array index [" << pos << "]\n" << RESET;
    } else {
        std::cout << RED << " [!] ERROR: Query target match missing from active registers.\n" << RESET;
    }
}

int main() {
    int n = 0, k, opt;
    std::vector<int> a;

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] DATA SEARCH & RETRIEVAL INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU] Active Blocks: " << n << " elements recorded\n" << RESET
                  << "  1.  (+) Input Main Array Block Data\n"
                  << "  2.  (*) Run Linear Search query sequence\n"
                  << "  3.  (*) Run Binary Search query sequence (Requires Sorted Data)\n"
                  << "  4.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> opt)) break;
        if (opt == 4) {
            std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
            break;
        }

        switch (opt) {
            case 1:
                std::cout << AMBER << "  [?] Array Size Limit Allocation: " << RESET;
                if (!(std::cin >> n) || n <= 0) {
                    std::cout << RED << " [!] ERROR: Target index falls outside variable parameters.\n" << RESET;
                    n = 0;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    continue;
                }
                a.resize(n);
                std::cout << AMBER << "  [?] Enter " << n << " Sequential Values: " << RESET;
                for (int i = 0; i < n; i++) std::cin >> a[i];
                std::cout << GREEN << "  (+) Success: Array registers updated with committed values.\n" << RESET;
                break;

            case 2:
            case 3:
                if (n == 0) {
                    std::cout << RED << " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY\n" << RESET;
                } else {
                    std::cout << AMBER << "  [?] Enter Search Target Value: " << RESET;
                    std::cin >> k;
                    find(a, k, opt);
                }
                break;

            default:
                std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}