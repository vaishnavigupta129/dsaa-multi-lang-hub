import os
import sys

# ANSI Color Codes
RESET = "\033[0m"
CYAN = "\033[1;36m"
GREEN = "\033[1;32m"
RED = "\033[1;31m"
AMBER = "\033[1;33m"
PURPLE = "\033[1;35m"

MAX = 100
a = [0] * MAX
n = 0
total = 0

void = None # Simply a visual marker for matching style

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" Think of this program as a digital shelf with numbered slots.\n")
    print(f"{AMBER} [STEP 1]{RESET} Define how many total slots you want to use today.")
    print(f"{AMBER} [STEP 2]{RESET} Use the menu numbers below to manage your data:")
    print(f"   • {GREEN}Option 1 (Insert):{RESET} Type a value, then pick a slot (0, 1, 2...).")
    print(f"   • {GREEN}Option 6 (View):{RESET}   Always use this to see your current shelf map.")
    print(f"   • {GREEN}Option 2 (Delete):{RESET} Remove an item by typing its slot index number.")
    print(f"   • {GREEN}Option 5 (Sort):{RESET}   Organizes scrambled numbers from lowest to highest.")
    print(f"   • {GREEN}Option 3/4 (Search):{RESET}Finds what slot index a number is hiding in.")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize system config...")

def is_empty():
    global n
    if n <= 0:
        print(f"{RED}\n [!] UNDERFLOW: Operational array contains zero elements.\n{RESET}")
        return True
    return False

def insert():
    global n, total, a
    if n >= MAX or n >= total:
        print(f"{RED}\n [!] OVERFLOW: Allocation boundary limit reached.\n{RESET}")
        return
    try:
        v = int(input(f"{AMBER} [?] Enter Value: {RESET}"))
        p = int(input(f"{AMBER} [?] Enter Position (0 to {n}): {RESET}"))
    except ValueError:
        print(f"{RED} [!] ERROR: Invalid numeric input.\n{RESET}")
        return

    if p < 0 or p > n:
        print(f"{RED} [!] ERROR: Target index falls outside variable parameters.\n{RESET}")
        return

    # Shift elements
    for i in range(n, p, -1):
        a[i] = a[i-1]
    a[p] = v
    n += 1
    print(f"{GREEN}  (+) Success: Element safely committed to index register.\n{RESET}")

def delete_item():
    global n, a
    if is_empty():
        return
    try:
        p = int(input(f"{AMBER} [?] Index to Delete (0 to {n - 1}): {RESET}"))
    except ValueError:
        print(f"{RED} [!] ERROR: Invalid numeric input.\n{RESET}")
        return

    if p < 0 or p >= n:
        print(f"{RED} [!] ERROR: Target index falls outside variable parameters.\n{RESET}")
        return

    removed = a[p]
    for i in range(p, n - 1):
        a[i] = a[i+1]
    n -= 1
    print(f"{RED}  (-) Dropped: Memory cell released -> element [{removed}]\n{RESET}")

def search(mode):
    global n, a
    if is_empty():
        return
    try:
        v = int(input(f"{AMBER} [?] Search Value: {RESET}"))
    except ValueError:
        print(f"{RED} [!] ERROR: Invalid numeric input.\n{RESET}")
        return
        
    found = -1
    if mode == 1: # Linear
        for i in range(n):
            if a[i] == v:
                found = i
                break
    else: # Binary
        low = 0
        high = n - 1
        while low <= high:
            mid = (low + high) // 2
            if a[mid] == v:
                found = mid
                break
            if a[mid] < v:
                low = mid + 1
            else:
                high = mid - 1

    if found != -1:
        print(f"{GREEN}  (*) Located: Element matching query found at index [{found}]\n{RESET}")
    else:
        print(f"{RED} [!] ERROR: Query target match missing from active registers.\n{RESET}")

def bubble_sort():
    global n, a
    if is_empty():
        return
    for i in range(n - 1):
        for j in range(n - i - 1):
            if a[j] > a[j+1]:
                a[j], a[j+1] = a[j+1], a[j]
    print(f"{GREEN}  (^) Sort Complete: Active registry block sequences reordered.\n{RESET}")

def display():
    global n, a
    print_header("STATIC DATA ARRAY VISUALIZATION")
    if n == 0:
        print(f"{RED}  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n{RESET}")
        return
    print(f"{CYAN} INDEX : {RESET}", end="")
    for i in range(n):
        print(f"{i:<5}", end="")
    print(f"\n{CYAN} DATA  : {RESET}", end="")
    for i in range(n):
        print(f"[{a[i]}]  ", end="")
    print()

def main():
    global total
    os.system('cls' if os.name == 'nt' else 'clear')
    
    print_user_guide()

    print(f"{CYAN}==================================================")
    print("     [M] STATIC ARRAY CONTROL INTERFACE [M]")
    print(f"=================================================={RESET}")
    
    try:
        total = int(input(f"{AMBER} [?] Define Max Target Capacity: {RESET}"))
    except ValueError:
        print(f"{RED}Critical configuration failure. Exiting.{RESET}")
        return

    while True:
        print(f"{CYAN}\n [SYSTEM STATUS] Active Blocks: {n}/{total} entries utilized{RESET}")
        print("  1.  (+) Insert Element")
        print("  2.  (-) Delete Element")
        print("  3.  (*) Run Linear Search query")
        print("  4.  (*) Run Binary Search query")
        print("  5.  (^) Run Structural Bubble Sort")
        print("  6.  (#) Traverse Structural Visual")
        print("  7.  (X) Terminate Control Kernel Execution")
        
        choice = input(f"{AMBER} >>> Select Target Action Option: {RESET}")
        
        if choice == '1': insert()
        elif choice == '2': delete_item()
        elif choice == '3': search(1)
        elif choice == '4': search(2)
        elif choice == '5': bubble_sort()
        elif choice == '6': display()
        elif choice == '7':
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.\n{RESET}")

if __name__ == "__main__":
    main()