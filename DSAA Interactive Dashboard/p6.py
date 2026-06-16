import os
import sys

RESET = "\033[0m"
CYAN = "\033[1;36m"
GREEN = "\033[1;32m"
RED = "\033[1;31m"
AMBER = "\033[1;33m"
PURPLE = "\033[1;35m"

class Node:
    def __init__(self, val):
        self.data = val
        self.next = None

class Queue:
    def __init__(self):
        self.front = None
        self.rear = None

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" Think of this program as a lineup of customers connected dynamically via pointers.\n")
    print(f"{AMBER} [STEP 1]{RESET} Interact with the core kernel functions below.")
    print(f"{AMBER} [STEP 2]{RESET} Observe your dynamic FIFO (First-In, First-Out) tracking:")
    print(f"   • {GREEN}Option 1 (Enqueue):{RESET} Appends a new node to the tail end of the [REAR] chain.")
    print(f"   • {GREEN}Option 2 (Dequeue):{RESET} Detaches and frees the oldest surviving element at [FRONT].")
    print(f"   • {GREEN}Option 3 (View):{RESET}    Outputs sequential address links maps terminated with a NULL string.")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize dynamic queue interface...")

def is_empty(q):
    return q.front is None

def enqueue(q):
    try:
        val = int(input(f"{AMBER} [?] Input Value to Enqueue: {RESET}"))
    except ValueError:
        print(f"{RED} [!] ERROR: Invalid processing frame data frame.{RESET}")
        return

    new_node = Node(val)
    if q.rear is None:
        q.front = q.rear = new_node
    else:
        q.rear.next = new_node
        q.rear = new_node
    print(f"{GREEN}  (+) Success: Dynamic node allocated and linked at rear pointer.{RESET}")

def dequeue(q):
    if is_empty(q):
        print(f"{RED}\n [!] UNDERFLOW: LINKED QUEUE CONTAINS ZERO ELEMENTS{RESET}")
        return
    
    temp = q.front
    data = temp.data
    q.front = q.front.next
    
    if q.front is None:
        q.rear = None
        
    print(f"{RED}  (-) Dropped: Front cell popped -> data [{data}] unlinked & freed{RESET}")

def display(q):
    print_header("DYNAMIC QUEUE MEMORY VISUALIZATION")
    if is_empty(q):
        print(f"{RED}  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n{RESET}")
        return
        
    temp = q.front
    print("  ", end="")
    while temp:
        if temp == q.front:
            print(f"{AMBER}[{temp.data}]{RESET} (FRONT) -> ", end="")
        elif temp == q.rear:
            print(f"{PURPLE}[{temp.data}]{RESET} (REAR) -> ", end="")
        else:
            print(f"{CYAN}[{temp.data}]{RESET} -> ", end="")
        temp = temp.next
    print(f"{PURPLE}NULL{RESET}")

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    q = Queue()

    print(f"{CYAN}==================================================")
    print("     [M] DYNAMIC LINKED QUEUE INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU]{RESET}")
        print("  1.  (+) Enqueue Allocation (Insert Element)")
        print("  2.  (-) Dequeue Destruction (Remove Element)")
        print("  3.  (#) Traverse Node Layout Sequence")
        print("  4.  [$] Run Pointer Diagnostic Status")
        print("  5.  (X) Terminate Control Kernel Execution")
        
        try:
            choice = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if choice == 1: enqueue(q)
        elif choice == 2: dequeue(q)
        elif choice == 3: display(q)
        elif choice == 4:
            print_header("HEAP STRUCT POINTER DIAGNOSTIC REPORT")
            # Python extracts identity hashes as hex equivalents for raw pointer simulation
            f_ptr = f"0x{id(q.front):02X}" if q.front else "NIL"
            r_ptr = f"0x{id(q.rear):02X}" if q.rear else "NIL"
            print(f"  [-] Front Structural Pointer:   {f_ptr}")
            print(f"  [-] Rear Structural Pointer :   {r_ptr}")
            print(f"  [-] Dynamic Memory State Empty: {RED + 'TRUE (NULL)' + RESET if is_empty(q) else GREEN + 'FALSE (Active Nodes)' + RESET}")
        elif choice == 5:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()