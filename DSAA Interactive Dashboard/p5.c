#include <stdio.h>
#include <stdlib.h>

// ANSI Color Codes for high-tech look
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define AMBER   "\033[1;33m"
#define PURPLE  "\033[1;35m"

#define SIZE 5
int q[SIZE], front = -1, rear = -1;

void printHeader(char* title) {
    printf(PURPLE "\n==================================================\n");
    printf("  [#] %s\n", title);
    printf("==================================================\n" RESET);
}

void printUserGuide() {
    printf(CYAN "\n==================================================\n");
    printf("         CRASH COURSE: HOW TO USE THIS SYSTEM\n");
    printf("==================================================\n" RESET);
    printf(" Think of this program as a circular racetrack divided into slots.\n\n");
    printf(AMBER " [STEP 1]" RESET " Select options from the control matrix down below.\n");
    printf(AMBER " [STEP 2]" RESET " Master the FIFO (First-In, First-Out) tracking logic:\n");
    printf("   • " GREEN "Option 1 (Enqueue):" RESET " Enters an element at the [REAR] pointer.\n");
    printf("   • " GREEN "Option 2 (Dequeue):" RESET " Extracts an element from the [FRONT] pointer.\n");
    printf("   • " GREEN "Modulo Wrap-Around:" RESET " When data reaches slot 4, it wraps around back to slot 0!\n");
    printf("   • " GREEN "Option 3 (View):" RESET "    Prints the layout path from Front to Rear explicitly.\n");
    printf(PURPLE "==================================================\n\n" RESET);
    printf("Press " AMBER "[ENTER]" RESET " to initialize circular data matrix...");
    while(getchar() != '\n'); // Clear buffer
    getchar();
}

int isFull() {
    return (front == (rear + 1) % SIZE);
}

int isEmpty() {
    return (front == -1);
}

void enqueue() {
    int data;
    if (isFull()) {
        printf(RED "\n [!] OVERFLOW: CIRCULAR DATA RING REGISTER IS FULL\n" RESET);
    } else {
        printf(AMBER " [?] Input Value to Enqueue: " RESET);
        scanf("%d", &data);
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        q[rear] = data;
        printf(GREEN "  (+) Success: Value %d committed to Ring Index %d\n" RESET, data, rear);
    }
}

void dequeue() {
    if (isEmpty()) {
        printf(RED "\n [!] UNDERFLOW: CIRCULAR RING STORAGE CONTAIN ZERO ELEMENTS\n" RESET);
    } else {
        int val = q[front];
        printf(RED "  (-) Dropped: Address block released -> element [%d] from index %d\n" RESET, val, front);
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
        printf(RED "  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n" RESET);
    } else {
        int i = front;
        printf(CYAN " INDEX : " RESET);
        int temp = front;
        while(1) {
            printf("%-5d", temp);
            if (temp == rear) break;
            temp = (temp + 1) % SIZE;
        }
        
        printf(CYAN "\n DATA  : " RESET);
        while (1) {
            if (i == front && i == rear) printf(GREEN "[%d]" RESET "  ", q[i]);
            else if (i == front) printf(AMBER "[%d]" RESET "  ", q[i]);
            else if (i == rear) printf(PURPLE "[%d]" RESET "  ", q[i]);
            else printf("[%d]  ", q[i]);
            
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        printf("\n" AMBER "  (Note: Front Node highlighted Amber | Rear Node highlighted Purple)" RESET "\n");
    }
}

int main() {
    int ch;
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printUserGuide();

    printf(CYAN "==================================================\n");
    printf("     [M] CIRCULAR RING BUFFER CONTROL INTERFACE [M]\n");
    printf("==================================================\n" RESET);

    while (1) {
        printf(CYAN "\n [MAIN MENU]\n" RESET);
        printf("  1.  (+) Enqueue Interface (Insert Data)\n");
        printf("  2.  (-) Dequeue Interface (Delete Data)\n");
        printf("  3.  (#) Traverse Ring Buffer Visual Layout\n");
        printf("  4.  [$] Run Queue Segment Diagnostics Status\n");
        printf("  5.  (X) Terminate Control Kernel Execution\n");
        printf(AMBER " >>> Select Target Action Option: " RESET);
        
        if (scanf("%d", &ch) != 1) break;

        switch (ch) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: display(); break;
            case 4:
                printHeader("QUEUE HARDWARE DIAGNOSTIC REPORT");
                printf("  [-] Active Memory Cells Max Bounds: %d units\n", SIZE);
                printf("  [-] Current Front Address Offset:   %d\n", front);
                printf("  [-] Current Rear Address Offset:    %d\n", rear);
                printf("  [-] Ring Buffer Memory State Full:  %s\n", isFull() ? RED "TRUE (1)" RESET : GREEN "FALSE (0)" RESET);
                break;
            case 5: 
                printf(RED "\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n" RESET);
                exit(0);
            default: 
                printf(RED " [!] WARNING: Operational instruction unrecognized.\n" RESET);
        }
    }
    return 0;
}