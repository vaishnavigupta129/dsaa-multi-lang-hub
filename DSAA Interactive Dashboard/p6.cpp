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

class Queue {
public:
    Node *front, *rear;
    Queue() : front(nullptr), rear(nullptr) {}
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
              << " Think of this program as a lineup of customers connected dynamically via pointers.\n\n"
              << AMBER << " [STEP 1]" << RESET << " Interact with the core kernel functions below.\n"
              << AMBER << " [STEP 2]" << RESET << " Observe your dynamic FIFO (First-In, First-Out) tracking:\n"
              << "   • " << GREEN << "Option 1 (Enqueue):" << RESET << " Appends a new node to the tail end of the [REAR] chain.\n"
              << "   • " << GREEN << "Option 2 (Dequeue):" << RESET << " Detaches and frees the oldest surviving element at [FRONT].\n"
              << "   • " << GREEN << "Option 3 (View):" << RESET << "    Outputs sequential address links maps terminated with a NULL string.\n"
              << PURPLE << "==================================================\n\n" << RESET
              << "Press " << AMBER << "[ENTER]" << RESET << " to initialize dynamic queue interface...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

bool isEmpty(Queue* q) { 
    return q->front == nullptr; 
}

void enqueue(Queue* q) {
    int val;
    Node* newNode = new(std::nothrow) Node(0);
    if (!newNode) { 
        std::cout << RED << "\n [!] FATAL: HEAP MEMORY EXHAUSTED\n" << RESET; 
        return; 
    }
    
    std::cout << AMBER << " [?] Input Value to Enqueue: " << RESET;
    std::cin >> val;
    
    newNode->data = val;
    newNode->next = nullptr;
    
    if (q->rear == nullptr) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    std::cout << GREEN << "  (+) Success: Dynamic node allocated and linked at rear pointer.\n" << RESET;
}

void dequeue(Queue* q) {
    if (isEmpty(q)) { 
        std::cout << RED << "\n [!] UNDERFLOW: LINKED QUEUE CONTAINS ZERO ELEMENTS\n" << RESET; 
        return; 
    }
    
    Node* temp = q->front;
    int data = temp->data;
    
    q->front = q->front->next;
    
    if (q->front == nullptr) {
        q->rear = nullptr;
    }
    
    delete temp;
    std::cout << RED << "  (-) Dropped: Front cell popped -> data [" << data << "] unlinked & freed\n" << RESET;
}

void display(Queue* q) {
    printHeader("DYNAMIC QUEUE MEMORY VISUALIZATION");
    if (isEmpty(q)) { 
        std::cout << RED << "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" << RESET; 
        return; 
    }
    
    Node* temp = q->front;
    std::cout << "  ";
    while (temp) {
        if (temp == q->front) 
            std::cout << AMBER << "[" << temp->data << "]" << RESET << " (FRONT) -> ";
        else if (temp == q->rear)
            std::cout << PURPLE << "[" << temp->data << "]" << RESET << " (REAR) -> ";
        else
            std::cout << CYAN << "[" << temp->data << "]" << RESET << " -> ";
            
        temp = temp->next;
    }
    std::cout << PURPLE << "NULL\n" << RESET;
}

int main() {
    Queue q;
    int choice;

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    printUserGuide();

    std::cout << CYAN << "==================================================\n"
              << "     [M] DYNAMIC LINKED QUEUE INTERFACE [M]\n"
              << "==================================================\n" << RESET;

    while (true) {
        std::cout << CYAN << "\n [MAIN MENU]\n" << RESET
                  << "  1.  (+) Enqueue Allocation (Insert Element)\n"
                  << "  2.  (-) Dequeue Destruction (Remove Element)\n"
                  << "  3.  (#) Traverse Node Layout Sequence\n"
                  << "  4.  [$] Run Pointer Diagnostic Status\n"
                  << "  5.  (X) Terminate Control Kernel Execution\n"
                  << AMBER << " >>> Select Target Action Option: " << RESET;
        
        if (!(std::cin >> choice)) break;

        switch (choice) {
            case 1: enqueue(&q); break;
            case 2: dequeue(&q); break;
            case 3: display(&q); break;
            case 4:
                printHeader("HEAP STRUCT POINTER DIAGNOSTIC REPORT");
                std::cout << "  [-] Front Structural Pointer:   " << (void*)q.front << "\n"
                          << "  [-] Rear Structural Pointer :   " << (void*)q.rear << "\n"
                          << "  [-] Dynamic Memory State Empty: " << (isEmpty(&q) ? RED "TRUE (NULL)" RESET : GREEN "FALSE (Active Nodes)" RESET) << "\n";
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