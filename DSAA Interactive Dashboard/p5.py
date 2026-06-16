import os
import sys

RESET = "\033[0m"
CYAN = "\033[1;36m"
GREEN = "\033[1;32m"
RED = "\033[1;31m"
AMBER = "\033[1;33m"
PURPLE = "\033[1;35m"

SIZE = 5
q = [0] * SIZE
front = -1
rear = -1

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" Think of this program as a circular racetrack divided into slots.\n")
    print(f"{AMBER} [STEP 1]{RESET} Select options from the control matrix down below.")
    print(f"{AMBER} [STEP 2]{RESET} Master the FIFO (First-In, First-Out) tracking logic:")
    print(f"   • {GREEN}Option 1 (Enqueue):{RESET} Enters an element at the [REAR] pointer.")
    print(f"   • {GREEN}Option 2 (Dequeue):{RESET} Extracts an element from the [FRONT] pointer.")
    print(f"   • {GREEN}Modulo Wrap-Around:{RESET} When data reaches slot 4, it wraps around back to slot 0!")
    print(f"   • {GREEN}Option 3 (View):{RESET}    Prints the layout path from Front to Rear explicitly.")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize circular data matrix...")

def isFull():
    return front == (rear + 1) % SIZE

def isEmpty():
    return front == -1

def enqueue():
    global front, rear
    if isFull():
        print(f"{RED}\n [!] OVERFLOW: CIRCULAR DATA RING REGISTER IS FULL{RESET}")
    else:
        try:
            data = int(input(f"{AMBER} [?] Input Value to Enqueue: {RESET}"))
        except ValueError:
            print(f"{RED} [!] ERROR: Invalid processing frame data frame.{RESET}")
            return
        if front == -1:
            front = 0
        rear = (rear + 1) % SIZE
        q[rear] = data
        print(f"{GREEN}  (+) Success: Value {data} committed to Ring Index {rear}{RESET}")

def dequeue():
    global front, rear
    if isEmpty():
        print(f"{RED}\n [!] UNDERFLOW: CIRCULAR RING STORAGE CONTAIN ZERO ELEMENTS{RESET}")
    else:
        val = q[front]
        print(f"{RED}  (-) Dropped: Address block released -> element [{val}] from index {front}{RESET}")
        if front == rear:
            front = rear = -1
        else:
            front = (front + 1) % SIZE

def display():
    print_header("CIRCULAR RING MEMORY VISUALIZATION")
    if isEmpty():
        print(f"{RED}  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n{RESET}")
    else:
        i = front
        print(f"{CYAN} INDEX : {RESET}", end="")
        temp = front
        while True:
            print(f"{temp:<5}", end="")
            if temp == rear:
                break
            temp = (temp + 1) % SIZE
        
        print(f"\n{CYAN} DATA  : {RESET}", end="")
        while True:
            if i == front and i == rear:
                print(f"{GREEN}[{q[i]}]{RESET}  ", end="")
            elif i == front:
                print(f"{AMBER}[{q[i]}]{RESET}  ", end="")
            elif i == rear:
                print(f"{PURPLE}[{q[i]}]{RESET}  ", end="")
            else:
                print(f"[{q[i]}]  ", end="")
                
            if i == rear:
                break
            i = (i + 1) % SIZE
        print(f"\n{AMBER}  (Note: Front Node highlighted Amber | Rear Node highlighted Purple){RESET}")

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    print(f"{CYAN}==================================================")
    print("     [M] CIRCULAR RING BUFFER CONTROL INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU]{RESET}")
        print("  1.  (+) Enqueue Interface (Insert Data)")
        print("  2.  (-) Dequeue Interface (Delete Data)")
        print("  3.  (#) Traverse Ring Buffer Visual Layout")
        print("  4.  [$] Run Queue Segment Diagnostics Status")
        print("  5.  (X) Terminate Control Kernel Execution")
        
        try:
            ch = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if ch == 1: enqueue()
        elif ch == 2: dequeue()
        elif ch == 3: display()
        elif ch == 4:
            print_header("QUEUE HARDWARE DIAGNOSTIC REPORT")
            print(f"  [-] Active Memory Cells Max Bounds: {SIZE} units")
            print(f"  [-] Current Front Address Offset:   {front}")
            print(f"  [-] Current Rear Address Offset:    {rear}")
            print(f"  [-] Ring Buffer Memory State Full:  {RED + 'TRUE (1)' + RESET if isFull() else GREEN + 'FALSE (0)' + RESET}")
        elif ch == 5:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()