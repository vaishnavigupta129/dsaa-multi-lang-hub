import os
import sys

RESET = "\033[0m"
CYAN = "\033[1;36m"
GREEN = "\033[1;32m"
RED = "\033[1;31m"
AMBER = "\033[1;33m"
PURPLE = "\033[1;35m"

def print_header(title):
    print(f"{PURPLE}\n==================================================")
    print(f"  [#] {title}")
    print(f"=================================================={RESET}")

def print_user_guide():
    print(f"{CYAN}\n==================================================")
    print("         CRASH COURSE: HOW TO USE THIS SYSTEM")
    print(f"=================================================={RESET}")
    print(" Think of this system as an elite search database operating via two distinct algorithms.\n")
    print(f"{AMBER} [STEP 1]{RESET} Allocate data size and input parameters via Main Menu option 1.")
    print(f"{AMBER} [STEP 2]{RESET} Select an analytical search scan mode:")
    print(f"   • {GREEN}Linear Search (2):{RESET} Sweeps elements one by one. Works seamlessly on unsorted blocks.")
    print(f"   • {GREEN}Binary Search (3):{RESET} Divides sorted collections in half repeatedly. (Requires Sorted Inputs!)")
    print(f"   • {GREEN}Logarithmic Scale:{RESET} While Linear takes up to N steps, Binary finds targets in log(N) cuts.")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize data lookup search kernel...")

def find(arr, k, mode):
    n = len(arr)
    l, r = 0, n - 1
    pos = -1

    if mode == 2:  # Linear Search
        print_header("EXECUTING LINEAR SYSTEM SCAN")
        for i in range(n):
            if arr[i] == k:
                pos = i
                break
    else:  # Binary Search
        print_header("EXECUTING BINARY REGISTER SCAN")
        while l <= r:
            m = l + (r - l) // 2
            if arr[m] == k:
                pos = m
                break
            if arr[m] < k:
                l = m + 1
            else:
                r = m - 1

    if pos != -1:
        print(f"{GREEN}  (+) Success: Element {k} safely located at array index [{pos}]{RESET}")
    else:
        print(f"{RED} [!] ERROR: Query target match missing from active registers.{RESET}")

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    arr = []

    print(f"{CYAN}==================================================")
    print("     [M] DATA SEARCH & RETRIEVAL INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU] Active Blocks: {len(arr)} elements recorded{RESET}")
        print("  1.  (+) Input Main Array Block Data")
        print("  2.  (*) Run Linear Search query sequence")
        print("  3.  (*) Run Binary Search query sequence (Requires Sorted Data)")
        print("  4.  (X) Terminate Control Kernel Execution")
        
        try:
            opt = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if opt == 4:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)

        if opt == 1:
            try:
                n = int(input(f"{AMBER}  [?] Array Size Limit Allocation: {RESET}"))
                if n <= 0:
                    print(f"{RED} [!] ERROR: Target index falls outside variable parameters.{RESET}")
                    arr = []
                    continue
                inp = input(f"{AMBER}  [?] Enter {n} Sequential Values: {RESET}").split()
                arr = [int(x) for x in inp[:n]]
                print(f"{GREEN}  (+) Success: Array registers updated with committed values.{RESET}")
            except ValueError:
                print(f"{RED} [!] ERROR: Processing frame parse mismatch.{RESET}")
                arr = []
        elif opt in (2, 3):
            if not arr:
                print(f"{RED} [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY{RESET}")
            else:
                try:
                    k = int(input(f"{AMBER}  [?] Enter Search Target Value: {RESET}"))
                    find(arr, k, opt)
                except ValueError:
                    print(f"{RED} [!] ERROR: Numeric input parse failed.{RESET}")
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")

if __name__ == "__main__":
    main()