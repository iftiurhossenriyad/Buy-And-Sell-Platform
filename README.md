# Buy & Sell Platform Using Data Structures and Algorithms

## Project Proposal

### Project Title
**Buy & Sell Platform Using Data Structures and Algorithms**

### Team Members
* **MILTON ROY** — Student ID: 2404001
* **MD. IFTIUR HOSSEN RIYAD** — Student ID: 2404011  
* **Department of Cyber Security Engineering**  
* **University of Frontier Technology, Bangladesh**

### Instructor
* **MD. ABDULLAH** — Lecturer, Department of Cyber Security Engineering  
* **University of Frontier Technology, Bangladesh**

---

## Project Overview
This project aims to develop a simple console-based Buy & Sell platform that demonstrates the practical use of data structures and algorithms. The system allows users to add products, view product listings, search for items, and sort products efficiently.

## Problem Statement
Managing product information manually becomes difficult as the number of items increases. Without proper data organization and efficient algorithms, searching and sorting become slow and inefficient. This project addresses that problem by building a structured platform using core DSA concepts.

## Objectives
* Design a simple product management system for buying and selling.
* Apply data structures such as arrays, stacks, and queues.
* Implement searching and sorting algorithms effectively.
* Store user information and support product management operations.
* Demonstrate the real-world application of DSA in a small-scale system.

## Key Features
* Add, view, and search products
* Sort products by price or name
* Store user information
* Delete or recycle products
* Use file-based data persistence

## Technology Stack
* **Programming Language:** C++
* **Development Environment:** Visual Studio Code / Code::Blocks / Dev C++ / Terminal
* **Data Structures:** Array, Stack, Queue
* **Algorithms:** Linear Search, Binary Search, Bubble Sort, Quick Sort
* **Database:** File-based storage (locally generated `database.txt`, `users.txt`)

---

## 🛠️ How to Clone, Build, and Run

First, clone this repository to your local machine using terminal or command prompt:
```bash
git clone https://github.com/iftiurhossenriyad/Buy-And-Sell-Platform.git
cd Buy-And-Sell-Platform

```

### 🪟 On Windows

1. Open Command Prompt / PowerShell / Git Bash inside the cloned directory (`Buy-And-Sell-Platform`).
2. Compile all source files:
```cmd
g++ main.cpp Algorithms.cpp Database.cpp DataStructures.cpp Platform.cpp Product.cpp User.cpp -o BuyAndSellPlatform.exe

```


3. Run the Application:
```cmd
BuyAndSellPlatform.exe

```



### 🐉 On Kali Linux / Debian / Ubuntu

1. Install dependencies (if `g++` is not already installed):
```bash
sudo apt update && sudo apt install -y build-essential g++ git

```


2. Compile all source files:
```bash
g++ -std=c++11 main.cpp Algorithms.cpp Database.cpp DataStructures.cpp Platform.cpp Product.cpp User.cpp -o BuyAndSellPlatform

```


3. Grant execution permissions and run the application:
```bash
chmod +x BuyAndSellPlatform
./BuyAndSellPlatform

```



> **Note:** Always run the application from the project root directory so that local database files (`database.txt` and `users.txt`) are dynamically created, read, and updated correctly.

---

## Scope

The project focuses on a console-based system for basic product and user management. Advanced features such as online payment, full user authentication, and web integration are beyond the current scope.

## Expected Deliverables

* Complete C++ source code
* Project documentation
* Functional demonstration of the system