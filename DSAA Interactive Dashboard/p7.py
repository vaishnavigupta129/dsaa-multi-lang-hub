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
        self.prev = None
        self.next = None

head = None

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" Think of this program as a double-linked chain of data carriages moving both ways.\n")
    print(f"{AMBER} [STEP 1]{RESET} Fire up an action item from the main control register.")
    print(f"{AMBER} [STEP 2]{RESET} Choose a targeting sub-mode position variant:")
    print(f"   • {GREEN}Position 1 (Beg):{RESET} Snaps the new node directly onto the starting Head link.")
    print(f"   • {GREEN}Position 2 (End):{RESET} Explores through the sequence until finding a terminal tail.")
    print(f"   • {GREEN}Position 3 (Mid):{RESET} Tracks down a unique custom value, splicing inside inline.")
    print(f"   • {GREEN}Option 3 (View):{RESET}  Renders a visual dual-pointer arrow bidirectional layout map.")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize bidirectional kernel engine...")

def insert(pos_type):
    global head
    try:
        val = int(input(f"{AMBER} [?] Input Value: {RESET}"))
    except ValueError:
        print(f"{RED} [!] ERROR: Invalid item value frame format.{RESET}")
        return

    n = Node(val)
    t = head

    if not head:
        head = n
    elif pos_type == 1: # Beg
        n.next = head
        head.prev = n
        head = n
    elif pos_type == 2: # End
        while t.next:
            t = t.next
        t.next = n
        n.prev = t
    else: # Mid
        try:
            loc = int(input(f"{AMBER} [?] After which value?: {RESET}"))
        except ValueError:
            print(f"{RED} [!] ERROR: Target localization lookup parsed incorrectly.{RESET}")
            return
        while t and t.data != loc:
            t = t.next
        if not t:
            print(f"{RED} [!] ERROR: VALUE {loc} NOT FOUND IN ACTIVE REGISTERS!\n{RESET}")
            return
        n.next = t.next
        n.prev = t
        if t.next:
            t.next.prev = n
        t.next = n
    print(f"{GREEN}  (+) Success: Element {val} safely linked inside node sequence.{RESET}")

def del_node(pos_type):
    global head
    if not head:
        print(f"{RED}\n [!] UNDERFLOW: DOUBLY LINKED LIST CONTAIN ZERO ELEMENTS!{RESET}")
        return
    
    t = head

    if pos_type == 1: # Beg
        head = head.next
        if head:
            head.prev = None
    elif pos_type == 2: # End
        while t.next:
            t = t.next
        if t.prev:
            t.prev.next = None
        else:
            head = None
    else: # Mid
        try:
            loc = int(input(f"{AMBER} [?] Value to Delete: {RESET}"))
        except ValueError:
            print(f"{RED} [!] ERROR: Lookup targeting evaluation mismatch.{RESET}")
            return
        while t and t.data != loc:
            t = t.next
        if not t:
            print(f"{RED} [!] ERROR: TARGET VALUE {loc} NOT LOCATED!{RESET}")
            return
        if t.prev:
            t.prev.next = t.next
        else:
            head = t.next
        if t.next:
            t.next.prev = t.prev

    print(f"{RED}  (-) Dropped: Bidirectional link unlinked -> node data [{t.data}]{RESET}")

def display():
    print_header("DOUBLY LINKED POINTER VISUALIZATION")
    if not head:
        print(f"{RED}  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n{RESET}")
        return
    t = head
    print("  ", end="")
    print(f"{PURPLE}NULL {RESET}", end="")
    while t:
        print(f"{CYAN}<=>{RESET} [{t.data}] ", end="")
        t = t.next
    print(f"{PURPLE}<=> NULL{RESET}")

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    print(f"{CYAN}==================================================")
    print("     [M] DOUBLY LINKED LIST CONTROL INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU]{RESET}")
        print("  1.  (+) Insertion Interface")
        print("  2.  (-) Deletion Interface")
        print("  3.  (#) Visualize Node Layout Sequence")
        print("  4.  (X) Terminate Control Kernel Execution")
        
        try:
            choice = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if choice in (1, 2):
            try:
                sub = int(input(f"{CYAN}  (>) Position Variable Allocation [1:Beg 2:End 3:Mid]: {RESET}"))
            except ValueError:
                print(f"{RED} [!] WARNING: Sub-parameter allocation error.{RESET}")
                continue
            if 1 <= sub <= 3:
                if choice == 1: insert(sub)
                else: del_node(sub)
            else:
                print(f"{RED} [!] WARNING: Sub-parameter allocation error.{RESET}")
        elif choice == 3:
            display()
        elif choice == 4:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()