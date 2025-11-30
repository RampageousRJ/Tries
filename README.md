# Tries

## Project Description

The **Tries** repository is a collection of implementations and utilities for working with Trie data structures. It includes both basic and advanced Trie implementations in C++, as well as helper scripts to manage and test Trie data structures using test cases.

## Installation Instructions

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/tries.git
   cd tries
   ```

2. **Build the C++ components:**
   - Basic Trie:
     ```bash
     cd tries_basic
     g++ main.cpp -o trie_basic
     ```
   - Advanced Trie:
     ```bash
     cd ../tries_advanced
     g++ main.cpp -o trie_advanced
     ```

3. **Setup Python Environment (for `convert_testcase.py`):**
   - Ensure Python 3.x is installed.
   - Navigate to the root directory and run:
     ```bash
     python convert_testcase.py
     ```

## Usage

- **Basic Trie Implementation:**
  - Execute the basic Trie program:
    ```bash
    ./tries_basic/trie_basic
    ```

- **Advanced Trie Implementation:**
  - Execute the advanced Trie program:
    ```bash
    ./tries_advanced/trie_advanced
    ```

- **Test Case Conversion:**
  - Use `convert_testcase.py` to convert or handle `testcase.txt`:
    ```bash
    python convert_testcase.py
    ```

## Features

- **Basic Trie Implementation:** Found in `tries_basic/main.cpp`, this version provides essential Trie operations.
- **Advanced Trie Implementation:** Located in `tries_advanced/main.cpp`, it offers enhanced features and optimizations for Trie data structure.
- **Test Case Management:** The `convert_testcase.py` script facilitates conversion and management of test cases listed in `testcase.txt`.
