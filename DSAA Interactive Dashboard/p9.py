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
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self):
        self.root = None

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" Think of this system as an ordered hierarchical web branching from a parent Root node.\n")
    print(f"{AMBER} [STEP 1]{RESET} Populate values via Option 1. Smaller values split left, larger values split right.")
    print(f"{AMBER} [STEP 2]{RESET} Run deep-dive recursive stream traces across three dimensions:")
    print(f"   • {GREEN}Pre-Order (1): {RESET} Evaluates parent hubs first, dipping into sub-branches next (Root->L->R).")
    print(f"   • {GREEN}In-Order (2):  {RESET} Ascends sequentially from left to right, listing elements sorted (L->Root->R).")
    print(f"   • {GREEN}Post-Order (3):{RESET} Sweeps leaves at the lowest layers before hitting upper hubs (L->R->Root).")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize hierarchical tree kernel...")

def insert(root_node, data):
    if root_node is None:
        return Node(data)

    if data < root_node.data:
        root_node.left = insert(root_node.left, data)
    elif data > root_node.data:
        root_node.right = insert(root_node.right, data)
    else:
        print(f"{AMBER}  [!] Duplicate Flagged: Node value {data} already exists within tree indexes.{RESET}")
    return root_node

def traverse(root_node, mode):
    if root_node is None:
        return

    if mode == 1:
        print(f"{GREEN}{root_node.data} {RESET}", end="")
    traverse(root_node.left, mode)
    if mode == 2:
        print(f"{GREEN}{root_node.data} {RESET}", end="")
    traverse(root_node.right, mode)
    if mode == 3:
        print(f"{GREEN}{root_node.data} {RESET}", end="")

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    tree = BinarySearchTree()

    print(f"{CYAN}==================================================")
    print("     [M] BINARY SEARCH TREE CONTROL INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU]{RESET}")
        print("  1.  (+) Insert Node Variable Element")
        print("  2.  (*) Execute Pre-Order Traversal Stream (Root->L->R)")
        print("  3.  (*) Execute In-Order Traversal Stream (L->Root->R)")
        print("  4.  (*) Execute Post-Order Traversal Stream (L->R->Root)")
        print("  5.  (X) Terminate Control Kernel Execution")
        
        try:
            choice = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if choice == 5:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)

        if choice == 1:
            try:
                val = int(input(f"{AMBER}  [?] Enter Element Map Value: {RESET}"))
                tree.root = insert(tree.root, val)
                print(f"{GREEN}  (+) Success: Node location calculated and variable saved.{RESET}")
            except ValueError:
                print(f"{RED} [!] ERROR: Processing frame parse mismatch.{RESET}")
        elif choice in (2, 3, 4):
            mode_labels = {2: "PRE-ORDER SEQUENCE (Root-L-R)", 3: "IN-ORDER SEQUENCE (L-Root-R)", 4: "POST-ORDER SEQUENCE (L-R-Root)"}
            print_header(mode_labels[choice])
            if tree.root is None:
                print(f"{RED}  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] {RESET}")
            else:
                print("  ", end="")
                traverse(tree.root, choice - 1)
                print()
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()