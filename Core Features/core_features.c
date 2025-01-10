#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

// Structure definition for Account
typedef struct {
    int accountNumber;
    char name[50];
    char email[50];
    char accountType[10];
    char password[20];
    double balance;
} Account;

// Function to show password as asterisks
void getPassword(char *password, int maxLen) {
    int index = 0;
    char ch;
    printf("Enter your Password: ");
    while ((ch = getch()) != '\r') { // '\r' is Enter key
        if (ch == '\b') { // Backspace
            if (index > 0) {
                printf("\b \b");
                index--;
            }
        } else if (index < maxLen - 1) { // replace pass with asterisks
            password[index++] = ch;
            printf("*");
        }
    }
    password[index] = '\0'; // Null-terminate the password
    printf("\n");
}

// Function to generate a random account number
int generateNum() {
    return 100000 + rand() % 900000;
}

// Function to check if an account already exists
int doesAccountExist(int accountNumber) {
    FILE *file = fopen("accounts.dat", "rb");
    if (!file) return 0;

    Account acc;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accountNumber) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Function to get account details from the user
void getAccountDetails(Account *newAccount) {
    printf("Enter your Full Name: ");
    getchar(); // Clear the buffer
    fgets(newAccount->name, 50, stdin);
    strtok(newAccount->name, "\n");

    printf("Enter your E-mail: ");
    fgets(newAccount->email, 50, stdin);
    strtok(newAccount->email, "\n");

    printf("Enter Account Type: ");
    scanf("%s", newAccount->accountType);

    do {
        printf("Enter your Initial Balance: ");
        scanf("%lf", &newAccount->balance);
        if (newAccount->balance < 0) {
            printf("Balance cannot be negative!! Please Try Again\n");
        } else if (newAccount->balance < 100) {
            printf("Minimum Balance should be atleast 100!! Please Try Again\n");
        }
    } while (newAccount->balance < 100);

    // Password Input
    getPassword(newAccount->password, 20);
}

// Function to create an account
void createAccount() {
    Account newAccount;
    FILE *file = fopen("accounts.dat", "ab");
    if (!file) {
        printf("Error Opening File\n");
        return;
    }

    // Validate balance
    if (newAccount.balance < 0) {
        printf("Balance cannot be negative\n");
        fclose(file);
        return;
    }

    getAccountDetails(&newAccount);

    // Generate a unique account number
    do {
        newAccount.accountNumber = generateNum();
    } while (doesAccountExist(newAccount.accountNumber));

    printf("Account Number Generated: %d\n", newAccount.accountNumber);

    // Write account data to file
    fwrite(&newAccount, sizeof(Account), 1, file);
    fclose(file);
    printf("Account Created Successfully!!\n");
    printf(" \n");
}

// Function to authenticate a user with a maximum of 3 attempts
int authenticateUser(int accountNumber, char *enteredPassword) {
    FILE *file = fopen("accounts.dat", "rb");
    if (!file) {
        printf("Error opening file!!!\n");
        return 0;
    }

    Account acc;
    int attempts = 0;

    while (attempts < 3) {
        rewind(file); // Reset file pointer for each attempt
        int isAuthenticated = 0;

        while (fread(&acc, sizeof(Account), 1, file)) {
            if (acc.accountNumber == accountNumber && strcmp(acc.password, enteredPassword) == 0) {
                fclose(file);
                return 1; // Successful authentication
            }
        }

        // If not authenticated
        attempts++;
        if (attempts < 5) {
            printf("Invalid credentials. Attempts remaining: %d\n", 3 - attempts);
            getPassword(enteredPassword, 20);
        }
    }

    fclose(file);
    printf("Maximum login attempts reached. Access denied.\n");
    return 0; // Authentication failed
}

// Function to delete an account
void deleteAccount() {
    int accountNumber;
    char password[20];
    printf("Enter the Account Number to Delete: \n");
    scanf("%d", &accountNumber);
    getPassword(password, 20);

    if (!authenticateUser(accountNumber, password)) {
        printf("Authentication Failed\n");
        return;
    }

    FILE *file = fopen("accounts.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!file || !temp) {
        printf("Error opening file!!\n");
        return;
    }

    Account acc;
    int found = 0;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber != accountNumber) {
            fwrite(&acc, sizeof(Account), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (found) {
        printf("Account Deleted Successfully!!\n");
    } else {
        printf("Account not found\n");
    }
}

// Function to view account details
void viewAccount() {
    int accountNumber;
    char password[20];
    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    getPassword(password, 20);

    if (!authenticateUser(accountNumber, password)) {
        printf("Authentication Failed!!!\n");
        return;
    }

    FILE *file = fopen("accounts.dat", "rb");
    if (!file) {
        printf("Error Opening File!!!\n");
        return;
    }

    Account acc;
    int found = 0;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accountNumber) {
            printf("Account No: %d\n", acc.accountNumber);
            printf("Name: %s\n", acc.name);
            printf("Email: %s\n", acc.email);
            printf("Account Type: %s\n", acc.accountType);
            printf("Balance: %.2lf\n", acc.balance);
            found = 1; // Account found
            break;
        }
    }
    fclose(file);
    if (!found) {
        printf("Account not Found!!\n");
    }
}

// Function to update account details
void updateAccount() {
    int accountNumber;
    char password[20];
    printf("Enter Account Number to Update: ");
    scanf("%d", &accountNumber);
    getPassword(password, 20);

    if (!authenticateUser(accountNumber, password)) {
        printf("Authentication Failed!!\n");
        return;
    }

    FILE *file = fopen("accounts.dat", "rb+");
    if (!file) {
        printf("Error Opening File!!!\n");
        return;
    }

    Account acc;
    int found = 0;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accountNumber) {
            getAccountDetails(&acc);
            fseek(file, -(long)sizeof(Account), SEEK_CUR); // from conio.h
            fwrite(&acc, sizeof(Account), 1, file);
            found = 1;
            printf("Account Updated Successfully!!\n");
            break;
        }
    }
    fclose(file);
    if (!found) {
        printf("Account not found!!\n");
    }
}

//function for transaction system
void transaction_system() {
    FILE *file;
    Account acc;
    int acc_number, found = 0;

    printf("\n--- Transaction System ---\n");

    // Input account number
    printf("Enter Account Number: ");
    scanf("%d", &acc_number);

    char password[20];
    getPassword(password, 20);

    // Authenticate user
    if (!authenticateUser(acc_number, password)) {
        printf("Authentication Failed!!!\n");
        return;
    }

    // Open file for reading and writing
    file = fopen("accounts.dat", "rb+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    // Search for the account
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == acc_number) {
            found = 1;

            int option;
            float amount;

            do {
                printf("\n1. Withdraw\n2. Deposit\n3. Balance Inquiry\n4. Exit\n");
                printf("Choose an option: ");
                scanf("%d", &option);

                switch (option) {
                    case 1: // Withdraw
                        printf("Enter amount to withdraw: ");
                        scanf("%f", &amount);
                        if (amount > 0 && amount <= acc.balance) {
                            acc.balance -= amount;
                            printf("Withdrawal successful! New balance: %.2f\n", acc.balance);
                        } else {
                            printf("Invalid amount! Either negative or exceeds balance.\n");
                        }
                        break;

                    case 2: // Deposit
                        printf("Enter amount to deposit: ");
                        scanf("%f", &amount);
                        if (amount > 0) {
                            acc.balance += amount;
                            printf("Deposit successful! New balance: %.2f\n", acc.balance);
                        } else {
                            printf("Invalid amount! Cannot deposit a negative value.\n");
                        }
                        break;

                    case 3: // Balance Inquiry
                        printf("Current balance: %.2f\n", acc.balance);
                        break;

                    case 4: // Exit
                        printf("Exiting transaction system.\n");
                        break;

                    default:
                        printf("Invalid option! Try again.\n");
                        break;
                }
            } while (option != 4);

            // Update the account in the file
            fseek(file, -(long)sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, file);
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}

// Main Function
int main() {
    srand(time(0)); // Seed the random number generator
    int choice;
    do {
        printf("Welcome to the Banking System\n");
        printf("1. Create Account\n");
        printf("2. View Account\n");
        printf("3. Update Account\n");
        printf("4. Delete Account\n");
        printf("5. Transaction System\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                updateAccount();
                break;
            case 4:
                deleteAccount();
                break;
            case 5:
                transaction_system();
                break;
            case 6:
                printf("Thank you for using the Banking System\n");
                break;
            default:
                printf("Invalid Choice\n");
                break;
        }
    } while (choice != 6);

    return 0;
}