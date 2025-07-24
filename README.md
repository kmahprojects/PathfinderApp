# PathfinderApp

This is a simple C++ application for finding a path through a matrix of integers.

## 🧭 Problem Description

- The goal is to find a path from the start to the end of the matrix where:
  - The sum of the numbers in the path must be **greater than 0**
  - Only **0s** can appear at the **start** and **end**
  - Movement is allowed in four directions: **up, down, left, right**
  - Each position may only be used **once** in a path

There are two implementations:
- `pathfinderRecursion.cpp` – uses recursion
- `pathfinderStack.cpp` – uses a stack-based approach

---

## ⚙️ How to Compile and Run

### Step 1: Open Terminal in the Project Folder

Navigate to the folder where your `.cpp` files are located.

### Step 2: Compile

Use the following command, replacing `<filename>` with either `pathfinderRecursion` or `pathfinderStack`:

```bash
g++ -pedantic -Wall -Wextra -std=c++17 <filename>.cpp -o pathfinder
```

### Step 3: Run

Either double click the pathfinder.exe program created, or run it with the command

pathfinder.exe

There are sample matrixes in the folders, you may also test it with ones you've created.
