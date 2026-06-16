import os
import sys

RESET = "\033[0m"
CYAN = "\033[1;36m"
GREEN = "\033[1;32m"
RED = "\033[1;31m"
AMBER = "\033[1;33m"
PURPLE = "\033[1;35m"

MAX = 5
stack = [0] * MAX
top = -1

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  ◆ {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" Think of this program as a vertical stack of dinner plates.\n")
    print(f"{AMBER} [STEP 1]{RESET} Pick an option from the control menu below.")
    print(f"{AMBER} [STEP 2]{RESET} Understand the foundational LIFO rules:")
    print(f"   • {GREEN}Option 1 (Push):{RESET}  Slide a new item onto the very top of the stack.")
    print(f"   • {GREEN}Option 2 (Pop):{RESET}   Remove whichever item is currently resting on top.")
    print(f"   • {GREEN}Option 3 (Peep):{RESET}  Sneak a glance at the top item without removing it.")
    print(f"   • {GREEN}Option 4 (View):{RESET}  Draws a vertical diagram of your current storage.")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize structural memory pool...")

def is_full():
    return top == MAX - 1

def is_empty():
    return top == -1

def push():
    global top
    if is_full():
        print(f"{RED}\n [▼] OVERFLOW Error: Stack memory allocation limits reached.{RESET}")
    else:
        try:
            v = int(input(f"{AMBER} [?] Input Value to Push: {RESET}"))
            top += 1
            stack[top] = v
            print(f"{GREEN}  ▲ Success: Value {v} safely committed to address offset.{RESET}")
        except ValueError:
            print(f"{RED} [!] ERROR: Invalid numeric format.{RESET}")

def pop():
    global top
    if is_empty():
        print(f"{RED}\n [▼] UNDERFLOW Error: Operational array contains zero elements.{RESET}")
    else:
        v = stack[top]
        top -= 1
        print(f"{RED}  ▼ Dropped: Memory cell released -> element [{v}]{RESET}")

def peep():
    if is_empty():
        print(f"{RED}\n [!] STACK EMPTY: Registers have no top address target.{RESET}")
    else:
        print(f"{CYAN}  ➔ Current Pointer Position Element: [{stack[top]}]{RESET}")

def traverse():
    print_header("CORE REGISTRY MEMORY VISUALIZATION")
    if is_empty():
        print(f"{RED}  [ !! SYSTEM EMPTY REGISTER FLUSH !! ] \n{RESET}")
    else:
        for i in range(top, -1, -1):
            if i == top:
                print(f"{GREEN}     | {stack[i]:<3} |  ➔ [TOP POINTER]{RESET}")
            else:
                print(f"{CYAN}     | {stack[i]:<3} |{RESET}")
            print("     +-----+")

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    print(f"{CYAN}==================================================")
    print("     ■ LIFO STORAGE ARRAY CONTROL SYSTEM ■")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [SYSTEM STATUS] Active Allocations: {top + 1}/{MAX} bytes max{RESET}")
        print("  1.  [+] Push (Insert Value Element)")
        print("  2.  [-] Pop (Destroy & Return Element)")
        print("  3.  [*] Peep (Read Top Vector Variable)")
        print("  4.  [#] Traverse Structural Visual")
        print("  5.  [$] Run Full Hardware Diagnostics Status")
        print("  6.  [X] Terminate Control Kernel Execution")
        
        try:
            ch = input(f"{AMBER} >> Select Target Action Option: {RESET}")
            if ch == '6' or ch == '':
                print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
                break
            ch = int(ch)
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if ch == 1: push()
        elif ch == 2: pop()
        elif ch == 3: peep()
        elif ch == 4: traverse()
        elif ch == 5:
            print_header("HARDWARE ENVIRONMENT DIAGNOSTIC REPORT")
            print(f"  ■ Stack Register Allocation Capacity:  {MAX} cells")
            print(f"  ■ Active Allocated Cell Count:        {top + 1} cells")
            print(f"  ■ Boolean Condition Register Empty:   {RED + 'TRUE (1)' + RESET if is_empty() else GREEN + 'FALSE (0)' + RESET}")
            print(f"  ■ Boolean Condition Register Full:    {RED + 'TRUE (1)' + RESET if is_full() else GREEN + 'FALSE (0)' + RESET}")
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()