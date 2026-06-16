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
    print(" This system provides a unified interface for full-lifecycle Binary Search Tree maintenance:\n")
    print(f"{AMBER} [STEP 1]{RESET} Allocate integers via option 1 to grow your tree dynamically on the heap.")
    print(f"{AMBER} [STEP 2]{RESET} Run a rapid binary query search via option 2 to check node existence.")
    print(f"{AMBER} [STEP 3]{RESET} Remove any element via option 3, which handles three unique deletion states:")
    print(f"   • {GREEN}Leaf Node:{RESET} Simply freed and replaced with null.")
    print(f"   • {GREEN}Single-Child Node:{RESET} Drops the target and bypass-links directly to its only child.")
    print(f"   • {GREEN}Dual-Child Node:{RESET} Replaces values with its structural in-order successor, then deletes.")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize operational management kernel...")

# Unified operation function. Returns (updated_node, found_boolean)
def operate(root_node, val, mode):
    if root_node is None:
        if mode != 1:
            return None, False
        return Node(val), False

    found = False
    if val < root_node.data:
        root_node.left, found = operate(root_node.left, val, mode)
    elif val > root_node.data:
        root_node.right, found = operate(root_node.right, val, mode)
    else:
        found = True
        if mode == 3:  # Deletion logic
            if root_node.left is None or root_node.right is None:
                temp = root_node.left if root_node.left else root_node.right
                return temp, True
            
            # Find In-order Successor
            successor = root_node.right
            while successor.left:
                successor = successor.left
            root_node.data = successor.data
            root_node.right, _ = operate(root_node.right, successor.data, 3)
            
    return root_node, found

def visualize(root_node):
    if root_node is None:
        return
    visualize(root_node.left)
    print(f"{CYAN}[{root_node.data}] {RESET}", end="")
    visualize(root_node.right)

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    tree = BinarySearchTree()

    print(f"{CYAN}==================================================")
    print("     [M] BST ADVANCED MANAGEMENT INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU]{RESET}")
        print("  1.  (+) Insert Node Variable Element")
        print("  2.  (?) Query Scan Address Index (Search Target)")
        print("  3.  (-) Delete Target Node Link (Re-balance Layout)")
        print("  4.  (#) Traverse In-Order Visual Layout Sequence")
        print("  5.  (X) Terminate Control Kernel Execution")
        
        try:
            choice = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if choice == 5:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)

        if choice in (1, 2, 3):
            if tree.root is None and choice > 1:
                print(f"{RED} [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY{RESET}")
                continue
                
            try:
                val = int(input(f"{AMBER}  [?] Target Allocation Value: {RESET}"))
            except ValueError:
                print(f"{RED} [!] ERROR: Processing frame parse mismatch.{RESET}")
                continue

            if choice == 1:
                tree.root, _ = operate(tree.root, val, 1)
                print(f"{GREEN}  (+) Success: Dynamic structural node safely allocated to heap.{RESET}")
            elif choice == 2:
                _, found = operate(tree.root, val, 2)
                if found:
                    print(f"{GREEN}  (*) Located: Query target key match [{val}] verified inside tree registry.{RESET}")
                else:
                    print(f"{RED}  [!] Missing: Query target match [{val}] missing from active pointers.{RESET}")
            else:
                tree.root, found = operate(tree.root, val, 3)
                if found:
                    print(f"{RED}  (-) Dropped: Node pointer [{val}] removed and address chain re-linked.{RESET}")
                else:
                    print(f"{RED}  [!] ERROR: Target index falls outside available balance parameters.{RESET}")
        elif choice == 4:
            print_header("BST IN-ORDER TRAVERSAL (SORTED MATRIX VIEW)")
            if tree.root is None:
                print(f"{RED}  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] {RESET}", end="")
            else:
                print("  ", end="")
                visualize(tree.root)
            print()
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()