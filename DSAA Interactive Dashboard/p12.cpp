#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

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
              << " This matrix tests sorting complexities across four distinct computing behaviors:\n\n"
              << AMBER << " [STEP 1]" << RESET << " Fire option 1 to allocate dynamic space and input raw registers.\n"
              << AMBER << " [STEP 2]" << RESET << " Run a targeting execution strategy:\n"
              << "   • " << GREEN << "Bubble Sort (2):   " << RESET << " Sweeps elements iteratively, floating highest values (O(N^2)).\n"
              << "   • " << GREEN << "Selection Sort (3):" << RESET << " Scans looking for minimum elements, placing them at the front (O(N^2)).\n"
              << "   • " << GREEN << "Insertion Sort (4):" << RESET << " Inserts values back into a growing sorted left sub-array frame (O(N^2)).\n"
              << "   • " << GREEN << "Quick Sort (5):    " << RESET << " Logarithmic divide-and-conquer strategy using a pivot point (O(N \\log N)).\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize algorithmic sorting engine...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

void bubble(std::vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) std::swap(a[j], a[j + 1]);
}

void selection(std::vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) if (a[j] < a[min]) min = j;
        std::swap(a[min], a[i]);
    }
}

void insertion(std::vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int k = a[i], j = i - 1;
        while (j >= 0 && a[j] > k) { a[j + 1] = a[j]; j--; }
        a[j + 1] = k;
    }
}

int partition(std::vector<int>& a, int l, int h) {
    int p = a[h], i = l - 1;
    for (int j = l; j < h; j++) if (a[j] < p) std::swap(a[++i], a[j]);
    std::swap(a[i + 1], a[h]);
    return i + 1;
}

void quick(std::vector<int>& a, int l, int h) {
    if (l < h) {
        int pi = partition(a, l, h);
        quick(a, l, pi - 1);
        quick(a, pi + 1, h);
    }
}

void display(const std::vector<int>& a) {
    std::cout << GREEN << "  (+) Sorted Sequence: " << RESET;
    for (int val : a) std::cout << val << " ";
    std::cout << "\n";
}

int main() {
    int choice, n = 0;
    std::vector<int> arr;

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] ALGORITHMIC SORTING SYSTEM INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU] Active Matrix: " << n << " elements loaded\n" << RESET
                  << "  1.  (+) Load Data Buffer (Dynamic Array Input)\n"
                  << "  2.  (*) Execute Bubble Sort Strategy\n"
                  << "  3.  (*) Execute Selection Sort Strategy\n"
                  << "  4.  (*) Execute Insertion Sort Strategy\n"
                  << "  5.  (*) Execute Quick Sort Divide-and-Conquer\n"
                  << "  6.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> choice)) break;
        if (choice == 6) {
            std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
            break;
        }

        if (choice == 1) {
            std::cout << AMBER << "  [?] Array Size Limit Allocation: " << RESET;
            if (!(std::cin >> n) || n <= 0) {
                std::cout << RED << " [!] ERROR: Target index falls outside variable parameters.\n" << RESET;
                n = 0;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            arr.resize(n);
            std::cout << AMBER << "  [?] Enter " << n << " Matrix Elements: " << RESET;
            for (int i = 0; i < n; i++) std::cin >> arr[i];
            std::cout << GREEN << "  (+) Success: Matrix registers dynamically scaled and elements saved.\n" << RESET;
            continue;
        }

        if (n == 0) {
            std::cout << RED << " [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY. RUN ACTION 1.\n" << RESET;
            continue;
        }

        switch (choice) {
            case 2: printHeader("EXECUTING BUBBLE SORT STRATEGY"); bubble(arr); break;
            case 3: printHeader("EXECUTING SELECTION SORT STRATEGY"); selection(arr); break;
            case 4: printHeader("EXECUTING INSERTION SORT STRATEGY"); insertion(arr); break;
            case 5: printHeader("EXECUTING QUICK SORT DIVIDE-AND-CONQUER"); quick(arr, 0, n - 1); break;
            default: std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET; continue;
        }
        display(arr);
    }
    return 0;
}