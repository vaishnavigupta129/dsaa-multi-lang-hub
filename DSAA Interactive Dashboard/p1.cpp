#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

// ANSI Color Codes
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

const int MAX = 100;
int a[MAX];
int n = 0;
int total = 0;

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  [#] " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " Think of this program as a digital shelf with numbered slots.\n\n"
              << AMBER << " [STEP 1]" << RESET << " Define how many total slots you want to use today.\n"
              << AMBER << " [STEP 2]" << RESET << " Use the menu numbers below to manage your data:\n"
              << "   • " << GREEN << "Option 1 (Insert):" << RESET << " Type a value, then pick a slot (0, 1, 2...).\n"
              << "   • " << GREEN << "Option 6 (View):" << RESET << "   Always use this to see your current shelf map.\n"
              << "   • " << GREEN << "Option 2 (Delete):" << RESET << " Remove an item by typing its slot index number.\n"
              << "   • " << GREEN << "Option 5 (Sort):" << RESET << "   Organizes scrambled numbers from lowest to highest.\n"
              << "   • " << GREEN << "Option 3/4 (Search):" << RESET << "Finds what slot index a number is hiding in.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize system config...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

bool is_empty() {
    if (n <= 0) {
        std::cout << RED << "\n [!] UNDERFLOW: Operational array contains zero elements.\n" << RESET;
        return true;
    }
    return false;
}

void insert() {
    int v, p;
    if (n >= MAX || n >= total) {
        std::cout << RED << "\n [!] OVERFLOW: Allocation boundary limit reached.\n" << RESET;
        return;
    }
    std::cout << AMBER << " [?] Enter Value: " << RESET; std::cin >> v;
    std::cout << AMBER << " [?] Enter Position (0 to " << n << "): " << RESET; std::cin >> p;

    if (p < 0 || p > n) {
        std::cout << RED << " [!] ERROR: Target index falls outside variable parameters.\n" << RESET;
        return;
    }

    for (int i = n++; i > p; i--) a[i] = a[i-1];
    a[p] = v;
    std::cout << GREEN << "  (+) Success: Element safely committed to index register.\n" << RESET;
}

void delete_item() {
    if (is_empty()) return;
    int p;
    std::cout << AMBER << " [?] Index to Delete (0 to " << n - 1 << "): " << RESET; std::cin >> p;

    if (p < 0 || p >= n) {
        std::cout << RED << " [!] ERROR: Target index falls outside variable parameters.\n" << RESET;
        return;
    }

    int removed = a[p];
    for (int i = p; i < --n; i++) a[i] = a[i+1];
    std::cout << RED << "  (-) Dropped: Memory cell released -> element [" << removed << "]\n" << RESET;
}

void search(int mode) {
    if (is_empty()) return;
    int v, found = -1;
    std::cout << AMBER << " [?] Search Value: " << RESET; std::cin >> v;

    if (mode == 1) { // Linear
        for (int i = 0; i < n; i++) {
            if (a[i] == v) { found = i; break; }
        }
    } else { // Binary
        int low = 0, high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (a[mid] == v) { found = mid; break; }
            (a[mid] < v) ? (low = mid + 1) : (high = mid - 1);
        }
    }

    if (found != -1) std::cout << GREEN << "  (*) Located: Element matching query found at index [" << found << "]\n" << RESET;
    else std::cout << RED << " [!] ERROR: Query target match missing from active registers.\n" << RESET;
}

void bubble_sort() {
    if (is_empty()) return;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
    std::cout << GREEN << "  (^) Sort Complete: Active registry block sequences reordered.\n" << RESET;
}

void display() {
    printHeader("STATIC DATA ARRAY VISUALIZATION");
    if (n == 0) {
        std::cout << RED << "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" << RESET;
        return;
    }
    std::cout << CYAN << " INDEX : " << RESET;
    for (int i = 0; i < n; i++) printf("%-5d", i);
    std::cout << CYAN << "\n DATA  : " << RESET;
    for (int i = 0; i < n; i++) printf("[%d]  ", a[i]);
    std::cout << "\n";
}

int main() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] STATIC ARRAY CONTROL INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    std::cout << AMBER << " [?] Define Max Target Capacity: " << RESET;
    std::cin >> total;

    int choice;
    while (true) {
        std::cout << CYAN << "\n [SYSTEM STATUS] Active Blocks: " << n << "/" << total << " entries utilized\n" << RESET
                  << "  1.  (+) Insert Element\n"
                  << "  2.  (-) Delete Element\n"
                  << "  3.  (*) Run Linear Search query\n"
                  << "  4.  (*) Run Binary Search query\n"
                  << "  5.  (^) Run Structural Bubble Sort\n"
                  << "  6.  (#) Traverse Structural Visual\n"
                  << "  7.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> choice)) break;

        switch (choice) {
            case 1: insert(); break;
            case 2: delete_item(); break;
            case 3: search(1); break;
            case 4: search(2); break;
            case 5: bubble_sort(); break;
            case 6: display(); break;
            case 7:
                std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
                return 0;
            default:
                std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}