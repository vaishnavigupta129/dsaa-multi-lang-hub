import os
import sys

# ANSI Color Codes for high-tech look (matching your C macro definitions)
RESET = "\033[0m"
CYAN = "\033[1;36m"
GREEN = "\033[1;32m"
RED = "\033[1;31m"
AMBER = "\033[1;33m"
PURPLE = "\033[1;35m"

class Node:
    """Equivalent to structural 'struct Node' definition in C"""
    def __init__(self, data):
        self.data = data
        self.next = None

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" Think of this program as a chain of train cars (nodes) linked together.\n")
    print(f"{AMBER} [STEP 1]{RESET} Pick an option from the main menu.")
    print(f"{AMBER} [STEP 2]{RESET} Choose a specific position modifier when prompted:")
    print(f"   • {GREEN}1 (Beginning):{RESET} Add or remove from the very front of the train.")
    print(f"   • {GREEN}2 (Middle):{RESET} Add after a specific value, or remove a chosen value.")
    print(f"   • {GREEN}3 (End):{RESET} Add or remove from the very back of the train.")
    print(f"   • {GREEN}Option 3 (View):{RESET} Always use this to print your current link map.")
    print(f"{PURPLE}==================================================\n{RESET}")
    
    # Matching the buffer hold logic of getchar()
    input(f"Press {AMBER}[ENTER]{RESET} to initialize dynamic system...")

def list_operation(head, mode, node_type):
    """
    Handles Insertion and Deletion processes.
    Replaces the double-pointer allocation tracking used in C.
    """
    # Underflow Guard Clause
    if mode == 2 and head is None:
        print(f"{RED}\n [!] UNDERFLOW: LINKED LIST EMPTY{RESET}")
        return head

    temp = head
    prev = None

    if mode == 1:  # --- INSERTION ENGINE ---
        try:
            val = int(input(f"{AMBER} [?] Input Value: {RESET}"))
        except ValueError:
            print(f"{RED} [!] ERROR: INVALID NUMBER ENTRY{RESET}")
            return head
            
        nn = Node(val)  # Implicitly managed memory allocation (No malloc)

        # Insert at Beginning or if pool register is empty
        if node_type == 1 or head is None:
            nn.next = head
            head = nn
        
        # Insert at End
        elif node_type == 3:
            while temp.next:
                temp = temp.next
            temp.next = nn
            
        # Insert at Middle (After matching element)
        else:
            try:
                target = int(input(f"{AMBER} [?] After Value: {RESET}"))
            except ValueError:
                print(f"{RED} [!] ERROR: INVALID NUMBER ENTRY{RESET}")
                return head
                
            while temp and temp.data != target:
                temp = temp.next
            if temp:
                nn.next = temp.next
                temp.next = nn
            else:
                print(f"{RED} [!] ERROR: {target} NOT FOUND IN LIST{RESET}")
                return head
                
        print(f"{GREEN}  (+) Success: Node safely allocated to pointer offset sequence.{RESET}")

    else:  # --- DELETION ENGINE ---
        # Drop From Beginning
        if node_type == 1:
            head = head.next
            
        # Drop From End
        elif node_type == 3:
            while temp.next:
                prev = temp
                temp = temp.next
            if prev:
                prev.next = None
            else:
                head = None
                
        # Drop From Middle (Target value tracking match)
        else:
            try:
                target = int(input(f"{AMBER} [?] Delete Value: {RESET}"))
            except ValueError:
                print(f"{RED} [!] ERROR: INVALID NUMBER ENTRY{RESET}")
                return head
                
            while temp and temp.data != target:
                prev = temp
                temp = temp.next
            if temp:
                if prev:
                    prev.next = temp.next
                else:
                    head = temp.next
            else:
                print(f"{RED} [!] ERROR: TARGET NOT LOCATED{RESET}")
                return head

        print(f"{RED}  (-) Dropped: Memory cell unlinked -> node data [{temp.data}]{RESET}")
        del temp  # Clear local reference scope tracking pointer allocations
        
    return head

def main():
    head = None

    # Clear terminal platform-independently
    os.system('cls' if os.name == 'nt' else 'clear')

    print_user_guide()

    print(f"{CYAN}==================================================")
    print("     [M] SINGLY LINKED LIST CONTROL INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU]{RESET}")
        print("  1.  (+) Insertion Interface")
        print("  2.  (-) Deletion Interface")
        print("  3.  (#) Visualize Node Layout Sequence")
        print("  4.  (X) Terminate Control Kernel Execution")
        
        try:
            c = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if c == 3:
            print_header("DYNAMIC REGISTER NODE VISUALIZATION")
            t = head
            print("  ", end="")
            if not t:
                print(f"{RED}[ !! EMPTY MEMORY POOL REGISTER !! ]{RESET}", end="")
            while t:
                print(f"{CYAN}[{t.data}]{RESET} -> ", end="")
                t = t.next
            print(f"{PURPLE}NULL{RESET}")

        elif c == 4:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)

        elif 0 < c < 3:
            try:
                s = int(input(f"{CYAN}  (>) Position Variable Allocation [1:Beg 2:Mid 3:End]: {RESET}"))
            except ValueError:
                print(f"{RED} [!] WARNING: Sub-parameter allocation error.{RESET}")
                continue
                
            if 1 <= s <= 3:
                head = list_operation(head, c, s)
            else:
                print(f"{RED} [!] WARNING: Sub-parameter allocation error.{RESET}")
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()