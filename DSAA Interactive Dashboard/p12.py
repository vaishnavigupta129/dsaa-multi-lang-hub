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
    print(" This matrix tests sorting complexities across four distinct computing behaviors:\n")
    print(f"{AMBER} [STEP 1]{RESET} Fire option 1 to allocate dynamic space and input raw registers.")
    print(f"{AMBER} [STEP 2]{RESET} Run a targeting execution strategy:")
    print(f"   • {GREEN}Bubble Sort (2):   {RESET} Sweeps elements iteratively, floating highest values (O(N^2)).")
    print(f"   • {GREEN}Selection Sort (3):{RESET} Scans looking for minimum elements, placing them at the front (O(N^2)).")
    print(f"   • {GREEN}Insertion Sort (4):{RESET} Inserts values back into a growing sorted left sub-array frame (O(N^2)).")
    print(f"   • {GREEN}Quick Sort (5):    {RESET} Logarithmic divide-and-conquer strategy using a pivot point (O(N \\log N)).")
    print(f"{PURPLE}==================================================\n{RESET}")
    input(f"Press {AMBER}[ENTER]{RESET} to initialize algorithmic sorting engine...")

def bubble(a):
    n = len(a)
    for i in range(n - 1):
        for j in range(n - i - 1):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]

def selection(a):
    n = len(a)
    for i in range(n - 1):
        min_idx = i
        for j in range(i + 1, n):
            if a[j] < a[min_idx]:
                min_idx = j
        a[min_idx], a[i] = a[i], a[min_idx]

def insertion(a):
    n = len(a)
    for i in range(1, n):
        k = a[i]
        j = i - 1
        while j >= 0 and a[j] > k:
            a[j + 1] = a[j]
            j -= 1
        a[j + 1] = k

def partition(a, l, h):
    p = a[h]
    i = l - 1
    for j in range(l, h):
        if a[j] < p:
            i += 1
            a[i], a[j] = a[j], a[i]
    a[i + 1], a[h] = a[h], a[i + 1]
    return i + 1

def quick(a, l, h):
    if l < h:
        pi = partition(a, l, h)
        quick(a, l, pi - 1)
        quick(a, pi + 1, h)

def display(a):
    print(f"{GREEN}  (+) Sorted Sequence: {RESET}", end="")
    print(" ".join(map(str, a)))

def main():
    os.system('cls' if os.name == 'nt' else 'clear')
    print_user_guide()

    arr = []

    print(f"{CYAN}==================================================")
    print("     [M] ALGORITHMIC SORTING SYSTEM INTERFACE [M]")
    print(f"=================================================={RESET}")

    while True:
        print(f"{CYAN}\n [MAIN MENU] Active Matrix: {len(arr)} elements loaded{RESET}")
        print("  1.  (+) Load Data Buffer (Dynamic Array Input)")
        print("  2.  (*) Execute Bubble Sort Strategy")
        print("  3.  (*) Execute Selection Sort Strategy")
        print("  4.  (*) Execute Insertion Sort Strategy")
        print("  5.  (*) Execute Quick Sort Divide-and-Conquer")
        print("  6.  (X) Terminate Control Kernel Execution")
        
        try:
            choice = int(input(f"{AMBER} >>> Select Target Action Option: {RESET}"))
        except ValueError:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        if choice == 6:
            print(f"{RED}\n [!] CORE KERNEL POWER DOWN INTERRUPT ISSUED...\n{RESET}")
            sys.exit(0)

        if choice == 1:
            try:
                n = int(input(f"{AMBER}  [?] Array Size Limit Allocation: {RESET}"))
                if n <= 0:
                    print(f"{RED} [!] ERROR: Target index falls outside variable parameters.{RESET}")
                    arr = []
                    continue
                inp = input(f"{AMBER}  [?] Enter {n} Matrix Elements: {RESET}").split()
                arr = [int(x) for x in inp[:n]]
                print(f"{GREEN}  (+) Success: Matrix registers dynamically scaled and elements saved.{RESET}")
            except ValueError:
                print(f"{RED} [!] ERROR: Processing frame parse mismatch.{RESET}")
                arr = []
            continue

        if not arr:
            print(f"{RED} [!] ERROR: OPERATIONAL SEARCH STORAGE IS COMPLETELY EMPTY. RUN ACTION 1.{RESET}")
            continue

        if choice == 2:
            print_header("EXECUTING BUBBLE SORT STRATEGY")
            bubble(arr)
        elif choice == 3:
            print_header("EXECUTING SELECTION SORT STRATEGY")
            selection(arr)
        elif choice == 4:
            print_header("EXECUTING INSERTION SORT STRATEGY")
            insertion(arr)
        elif choice == 5:
            print_header("EXECUTING QUICK SORT DIVIDE-AND-CONQUER")
            quick(arr, 0, len(arr) - 1)
        else:
            print(f"{RED} [!] WARNING: Operational instruction unrecognized.{RESET}")
            continue

        display(arr)

if __name__ == "__main__":
    main()