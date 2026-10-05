# PayStream

### A Console-Based Mini Banking System Built in C

![Language](https://img.shields.io/badge/Language-C-blue)
![Interface](https://img.shields.io/badge/Interface-Console-lightgrey)
![Storage](https://img.shields.io/badge/Storage-Binary%20Files-orange)
![Project](https://img.shields.io/badge/Project-University-green)

PayStream is a console-based mini banking system developed in **C** as my **first university programming project**.

The project was created as a group project to apply fundamental programming concepts to a practical banking scenario. It provides basic account management and transaction functionality while storing account information locally using binary file handling.

Although simple compared with my later software projects, PayStream represents the beginning of my software development journey and my first experience building a complete application around a real-world problem.

---

## Features

### Account Management

Users can create and manage banking accounts through the console interface.

Supported operations include:

- Create a new account
- Generate a unique six-digit account number
- View account information
- Update account details
- Delete an account
- Store account information persistently

Each account contains:

```text
Account Number
Full Name
Email
Account Type
Password
Balance
```

---

## Authentication

Account operations are protected using account-number and password authentication.

Password input is hidden from the console using asterisks while being entered.

The application also limits unsuccessful authentication attempts before denying access.

---

## Transaction System

Authenticated users can access a basic transaction system supporting:

```text
Withdraw
Deposit
Balance Inquiry
```

Transactions update the account balance stored in the local account file.

The application also performs basic validation such as preventing withdrawals that exceed the available balance and rejecting invalid deposit or withdrawal amounts.

---

## File-Based Persistence

PayStream uses C file handling to persist account information.

Account records are stored in:

```text
accounts.dat
```

The application reads and writes `Account` structures using binary file operations such as:

```c
fread()
fwrite()
fseek()
```

This allowed account information and balances to persist between application sessions without requiring a database.

---

## Account Structure

The core account model is represented using a C structure:

```c
typedef struct {
    int accountNumber;
    char name[50];
    char email[50];
    char accountType[10];
    char password[20];
    double balance;
} Account;
```

This structure is used throughout the application for account creation, authentication, transactions, updates, and file storage.

---

## Application Flow

```text
                 PayStream
                     │
                     ▼
              Main Banking Menu
                     │
       ┌─────────────┼─────────────┐
       │             │             │
       ▼             ▼             ▼
 Create Account  Manage Account  Transactions
       │             │             │
       ▼             ▼             ▼
Generate ID      Authenticate    Authenticate
       │             │             │
       ▼        ┌────┼────┐    ┌───┼────┐
 Store Data     View Update Delete Deposit Withdraw
       │                         │
       └──────────────┬──────────┘
                      ▼
                 accounts.dat
```

---

## Technologies & Concepts

| Area | Technology / Concept |
|---|---|
| Language | C |
| Interface | Console / CLI |
| Data Storage | Binary Files |
| Data Modeling | C Structures |
| Persistence | File I/O |
| Authentication | Account Number + Password |
| Programming Style | Procedural Programming |
| Development Focus | Programming Fundamentals |

The project demonstrates concepts including:

- Structures
- Functions
- Pointers
- File handling
- Binary file operations
- Conditional logic
- Loops
- Input validation
- String handling
- Random number generation
- Basic authentication
- CRUD operations

---

## Project Structure

```text
PayStream/
│
├── Core Features/
│   └── core_features.c
│
├── Transaction/
│   └── basic function.c
│
├── accounts.dat
│
├── .gitignore
└── README.md
```

### `Core Features/core_features.c`

Contains the integrated banking application, including:

- Account creation
- Account authentication
- Account viewing
- Account updating
- Account deletion
- Deposit and withdrawal operations
- Balance inquiry
- Binary file persistence

### `Transaction/basic function.c`

Contains an earlier standalone implementation of the transaction functionality.

It implements:

- Deposits
- Withdrawals
- Balance inquiries

This component formed part of the project's development before transaction functionality was incorporated into the main banking application.

---

## Running the Project

### Requirements

A C compiler such as GCC is required.

The application uses `conio.h` and `getch()` for hidden password input, so it is primarily designed for environments where those functions are available, particularly Windows-based C development environments.

### Compile

From the project directory:

```bash
gcc "Core Features/core_features.c" -o paystream
```

### Run

On Windows:

```bash
paystream.exe
```

The application will display the main banking menu:

```text
Welcome to the Banking System

1. Create Account
2. View Account
3. Update Account
4. Delete Account
5. Transaction System
6. Exit
```

---

## Academic Context

PayStream was developed as a **group project during my first semester of university**.

It was one of my earliest substantial programming projects and provided practical experience turning fundamental C programming concepts into a complete application.

The project helped establish foundations that I later applied to larger systems involving backend development, databases, APIs, financial workflows, and business automation.

---

## Limitations

PayStream was designed as an educational project rather than a production banking application.

Some intentional limitations of its scope include:

- Local file-based storage
- Console-only interface
- Platform-dependent password input
- Basic authentication
- No password hashing
- No database
- No network or API layer
- No transaction history or audit ledger

These limitations reflect the project's purpose as an early programming and university project.

---

## What I Learned

Building PayStream provided practical experience with:

- Designing a program around a real-world problem
- Breaking functionality into reusable functions
- Working with C structures
- Reading and writing persistent data
- Implementing CRUD operations
- Handling user authentication
- Validating financial transactions
- Collaborating on a group software project
- Integrating separately developed functionality into a larger program

PayStream became an early foundation for the more advanced business and financial systems I later developed.

---

## Author

**Muhammad Saahil Kudia**

BS Applied Computing  
Iqra University

GitHub: [@saahilkudia](https://github.com/saahilkudia)

---

## Project Status

**Completed Academic Project**

PayStream is preserved as part of my development portfolio to document the progression from foundational C programming to larger backend and business software systems.