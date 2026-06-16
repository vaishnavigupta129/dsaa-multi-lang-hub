#include <iostream>
#include <cstdlib>
#include <string>

#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

const int SIZE = 5;
int q[SIZE];
int front = -1, rear = -1;

void printHeader(const std::string& title) {
    std::cout << PURPLE << "\n==================================================\n"
              << "  [#] " << title << "\n"
              << "==================================================\n" << RESET;
}

void printUserGuide() {
    std::cout << CYAN << "\n==================================================\n"
              << "         CRASH COURSE: HOW TO USE THIS SYSTEM\n"
              << "==================================================\n" << RESET
              << " Think of this program as a circular racetrack divided into slots.\n\n"
              << AMBER << " [STEP 1]" << RESET << " Select options from the control matrix down below.\n"
              << AMBER << " [STEP 2]" << RESET << " Master the FIFO (First-In, First-Out) tracking logic:\n"
              << "   • " << GREEN << "Option 1 (Enqueue):" << RESET << " Enters an element at the [REAR] pointer.\n"
              << "   • " << GREEN << "Option 2 (Dequeue):" << RESET << " Extracts an element from the [FRONT] pointer.\n"
              << "   • " << GREEN << "Modulo Wrap-Around:" << RESET << " When data reaches slot 4, it wraps around back to slot 0!\n"
              << "   • " << GREEN << "Option 3 (View):" << RESET << "    Prints the layout path from Front to Rear explicitly.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize circular data matrix...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

bool isFull() { return (front == (rear + 1) % SIZE); }
bool isEmpty() { return (front == -1); }

void enqueue() {
    int data;
    if (isFull()) {
        std::cout << RED << "\n [!] OVERFLOW: CIRCULAR DATA RING REGISTER IS FULL\n" << RESET;
    } else {
        std::cout << AMBER << " [?] Input Value to Enqueue: " << RESET;
        std::cin >> data;
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        q[rear] = data;
        std::cout << GREEN << "  (+) Success: Value " << data << " committed to Ring Index " << rear << "\n" << RESET;
    }
}

void dequeue() {
    if (isEmpty()) {
        std::cout << RED << "\n [!] UNDERFLOW: CIRCULAR RING STORAGE CONTAIN ZERO ELEMENTS\n" << RESET;
    } else {
        int val = q[front];
        std::cout << RED << "  (-) Dropped: Address block released -> element [" << val << "] from index " << front << "\n" << RESET;
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }
}

void display() {
    printHeader("CIRCULAR RING MEMORY VISUALIZATION");
    if (isEmpty()) {
        std::cout << RED << "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" << RESET;
    } else {
        int i = front;
        std::cout << CYAN << " INDEX : " << RESET;
        int temp = front;
        while (true) {
            printf("%-5d", temp);
            if (temp == rear) break;
            temp = (temp + 1) % SIZE;
        }

        std::cout << CYAN << "\n DATA  : " << RESET;
        while (true) {
            if (i == front && i == rear) std::cout << GREEN << "[" << q[i] << "]" << RESET << "  ";
            else if (i == front) std::cout << AMBER << "[" << q[i] << "]" << RESET << "  ";
            else if (i == rear) std::cout << PURPLE << "[" << q[i] << "]" << RESET << "  ";
            else std::cout << "[" << q[i] << "]  ";

            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        std::cout << "\n" << AMBER << "  (Note: Front Node highlighted Amber | Rear Node highlighted Purple)" << RESET << "\n";
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
              << "     [M] CIRCULAR RING BUFFER CONTROL INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU]\n" << RESET
                  << "  1.  (+) Enqueue Interface (Insert Data)\n"
                  << "  2.  (-) Dequeue Interface (Delete Data)\n"
                  << "  3.  (#) Traverse Ring Buffer Visual Layout\n"
                  << "  4.  [$] Run Queue Segment Diagnostics Status\n"
                  << "  5.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;

        if (!(std::cin >> ch)) break;

        switch (ch) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: display(); break;
            case 4:
                printHeader("QUEUE HARDWARE DIAGNOSTIC REPORT");
                std::cout << "  [-] Active Memory Cells Max Bounds: " << SIZE << " units\n"
                          << "  [-] Current Front Address Offset:   " << front << "\n"
                          << "  [-] Current Rear Address Offset:    " << rear << "\n"
                          << "  [-] Ring Buffer Memory State Full:  " << (isFull() ? RED "TRUE (1)" RESET : GREEN "FALSE (0)" RESET) << "\n";
                break;
            case 5:
                std::cout << RED << "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" << RESET;
                exit(0);
            default:
                std::cout << RED << " [!] WARNING: Operational instruction unrecognized.\n" << RESET;
        }
    }
    return 0;
}