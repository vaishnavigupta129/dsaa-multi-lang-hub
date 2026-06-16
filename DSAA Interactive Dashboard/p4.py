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

top = None

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" Think of this program as a stack of boxes connected via pointers on a heap.\n")
    print(f"{AMBER} [STEP 1]{RESET} Interact with the core kernel functions below.")
    print(f"{AMBER} [STEP 2]{RESET} Observe your dynamic runtime behaviors:")
    print(f"   • {GREEN}Option 1 (Push):{RESET}  Spawns a node out of heap memory and updates the top layer.")
    print(f"   • {GREEN}Option 2 (Pop):{RESET}   Unlinks the top container, returning its data to cell zero.")
    print(f"   • {GREEN}Option 3 (Peep):{RESET}  Points explicitly to current node targets without unlinking.")
    print(f"   • {GREEN}Option 4 (View):{RESET}  Outputs sequential link maps terminated with a NULL string.")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize dynamic stack engine...")

def is_empty():
    return top is None

def is_full():
    # Python dynamically captures object assignments natively until OS cap
    return False

def push():
    global top
    try:
        val = int(input(f"{AMBER} [?] Input Value to Push: {RESET}"))
    except ValueError:
        print(f"{RED} [!] ERROR: Invalid processing frame input type.{RESET}")
        return

    n = Node(val)
    n.next = top
    top = n
    print(f"{GREEN}  (+) Success: Node safely pushed and linked to top address.{RESET}")

def pop():
    global top
    if is_empty():
        print(f"{RED}\n [!] UNDERFLOW: LINKED STACK CONTAIN ZERO ELEMENTS{RESET}")
        return
    t = top
    v = t.data
    top = top.next
    print(f"{RED}  (-) Dropped: Top heap cell popped -> element data [{v}]{RESET}")

def peep():
    if is_empty():
        print(f"{RED}\n [!] EMPTY: Operational reference pointer targets NULL.{RESET}")
    else:
        print(f"{CYAN}  (>) Current Stack Pointer Vector: [{top.data}]{RESET}")

def traverse():
    print_header("DYNAMIC STACK MEMORY VISUALIZATION")
    if is_empty():
        print(f"{RED}  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n{RESET}")
    else:
        t = top
        print("  ", end="")
        while t:
            if t == top:
                print(f"{GREEN}[{t.data}]{RESET} (TOP Pointer) -> ", end="")
            else:
                print(f"{CYAN}[{t.data}]{RESET} -> ", end="")
            t = t.next
        print(f"{PURPLE}NULL{RESET}")

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    print(f"{CYAN}==================================================")
    print("     [M] DYNAMIC LINKED STACK INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU]{RESET}")
        print("  1.  (+) Push Allocation (Insert Element)")
        print("  2.  (-) Pop Destruction (Remove Element)")
        print("  3.  (*) Peep Offset Address Reference")
        print("  4.  (#) Traverse Node Layout Sequence")
        print("  5.  [$] Run Heap Diagnostics Status")
        print("  6.  (X) Terminate Control Kernel Execution")
        
        try:
            ch = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if ch == 1: push()
        elif ch == 2: pop()
        elif ch == 3: peep()
        elif ch == 4: traverse()
        elif ch == 5:
            print_header("HEAP REGISTRY DIAGNOSTIC REPORT")
            print(f"  [-] Stack Pointer State Empty:   {RED + 'TRUE (NULL)' + RESET if is_empty() else GREEN + 'FALSE (Active Pointer)' + RESET}")
            print(f"  [-] System RAM Boundary Limit:   {GREEN + 'AVAILABLE (Dynamic Allocations Allowed)' + RESET}")
        elif ch == 6:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()