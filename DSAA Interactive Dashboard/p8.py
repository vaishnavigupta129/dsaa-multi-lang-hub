import os
import sys

RESET = "\033[0m"
CYAN = "\033[1;36m"
GREEN = "\033[1;32m"
RED = "\033[1;31m"
AMBER = "\033[1;33m"
PURPLE = "\033[1;35m"

class Node:
    def __init__(self, c, e):
        self.coeff = c
        self.exp = e
        self.next = None

class PolynomialList:
    def __init__(self):
        self.head = None

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" Think of this system as a dynamic warehouse storing mathematical expressions.\n")
    print(f"{AMBER} [STEP 1]{RESET} Populate Poly-1 or Poly-2 via options 1 and 2 by inputting elements.")
    print(f"{AMBER} [STEP 2]{RESET} Appreciate how sorted tracking operates under the hood:")
    print(f"   • {GREEN}Sorted Array Links:{RESET} Elements are auto-sorted in descending order of exponents.")
    print(f"   • {GREEN}Coefficient Merger:{RESET} Entering matching exponents merges their coefficients instantly.")
    print(f"   • {GREEN}Summation Kernel:{RESET}   Option 4 evaluates, merges, and presents the calculated results.")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize polynomial computational kernel...")

def insert(poly_obj, c, e):
    if c == 0:
        return
    
    # Use a dummy node setup to handle head pointer indirection comfortably in Python
    dummy = Node(0, 999999)
    dummy.next = poly_obj.head
    prev = dummy
    curr = poly_obj.head

    while curr and curr.exp > e:
        prev = curr
        curr = curr.next

    if curr and curr.exp == e:
        curr.coeff += c
    else:
        new_node = Node(c, e)
        new_node.next = curr
        prev.next = new_node
    
    poly_obj.head = dummy.next

def print_polynomial(head_node, label):
    if not head_node:
        print(f"{RED}  [!] {label}: EMPTY REGISTER POOL{RESET}")
        return
    print(f"{CYAN}  [{label}]: {RESET}", end="")
    curr = head_node
    while curr:
        print(f"{GREEN}{curr.coeff}x^{curr.exp}{RESET}", end="")
        if curr.next:
            print(f"{AMBER} + {RESET}", end="")
        curr = curr.next
    print()

def add_polynomials(p1, p2):
    res_list = PolynomialList()
    curr = p1.head
    while curr:
        insert(res_list, curr.coeff, curr.exp)
        curr = curr.next
    curr = p2.head
    while curr:
        insert(res_list, curr.coeff, curr.exp)
        curr = curr.next
    return res_list

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    poly1 = PolynomialList()
    poly2 = PolynomialList()

    print(f"{CYAN}==================================================")
    print("     [M] POLYNOMIAL COMPUTATION INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU]{RESET}")
        print("  1.  (+) Add Algebraic Term to POLY-1")
        print("  2.  (+) Add Algebraic Term to POLY-2")
        print("  3.  (#) Visualize Tracked Expression Maps")
        print("  4.  (=) Calculate Summation Product (P1 + P2)")
        print("  5.  (X) Terminate Control Kernel Execution")
        
        try:
            choice = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if choice == 5:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)

        if choice in (1, 2):
            try:
                inp = input(f"{AMBER}  [?] Enter Coefficient and Exponent [Format: c e]: {RESET}").split()
                c, e = int(inp[0]), int(inp[1])
                insert(poly1 if choice == 1 else poly2, c, e)
                print(f"{GREEN}  (+) Success: Linked term securely placed in polynomial node string.{RESET}")
            except (ValueError, IndexError):
                print(f"{RED} [!] ERROR: Invalid item values layout constraint rule error.{RESET}")
        elif choice == 3:
            print_header("POLYNOMIAL DATA STRUCT STORAGE")
            print_polynomial(poly1.head, "POLY-1")
            print_polynomial(poly2.head, "POLY-2")
        elif choice == 4:
            if not poly1.head and not poly2.head:
                print(f"{RED} [!] ERROR: OPERATIONAL EXPRESSION ARRAYS ARE COMPLETELY EMPTY{RESET}")
            else:
                print_header("ALGEBRAIC SUMMATION EVALUATION RESULT")
                res = add_polynomials(poly1, poly2)
                print_polynomial(res.head, "RESULT")
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()