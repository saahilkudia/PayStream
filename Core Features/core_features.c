#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure definition for Account
typedef struct {
    int accountNumber;
    char name[50];
    char email[50];
    char accountType[10];
    char password[20];
    double balance;
} Account;

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

    printf("Enter your initial balance: ");
    scanf("%lf", &newAccount->balance);

    printf("Enter your Password: ");
    getchar();
    fgets(newAccount->password, 20, stdin);
    strtok(newAccount->password, "\n"); 
}

// Function to create an account
void createAccount() {
    Account newAccount;
    FILE *file = fopen("accounts.dat", "ab");
    if (!file) {
        printf("Error Opening File\n");
        return;
    }

    // Generate a unique account number
    do {
        newAccount.accountNumber = generateNum();
    } while (doesAccountExist(newAccount.accountNumber));

    printf("Account Number Generated: %d\n", newAccount.accountNumber);
    getAccountDetails(&newAccount);

    // Validate balance
    if (newAccount.balance < 0) {
        printf("Balance cannot be negative\n");
        fclose(file);
        return;
    }

    // Write account data to file
    fwrite(&newAccount, sizeof(Account), 1, file);
    fclose(file);
    printf("Account Created Successfully!!\n");
}

// Function to authenticate a user
int authenticateUser(int accountNumber, char *enteredPassword) {
    FILE *file = fopen("accounts.dat", "rb");
    if (!file) {
        printf("Error opening file!!!\n");
        return 0;
    }

    Account acc;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accountNumber && strcmp(acc.password, enteredPassword) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Function to delete an account
void deleteAccount() {
    int accountNumber;
    char password[20];
    printf("Enter the Account Number to Delete: \n");
    scanf("%d", &accountNumber);
    printf("Enter the Password: \n");
    scanf("%s", password);

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
    printf("Enter Password: ");
    scanf("%s", password);

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
    printf("Enter Password: ");
    scanf("%s", password);

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
            fseek(file, -(long)sizeof(Account), SEEK_CUR);
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

// Main menu function
void menu() {
    int choice;
    do {
        printf("1. Create Account\n");
        printf("2. View Account\n");
        printf("3. Delete Account\n");
        printf("4. Update Account\n");
        printf("5. Exit Program\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccount(); break;
            case 3: deleteAccount(); break;
            case 4: updateAccount(); break;
            case 5: printf("Exiting Program....\n"); break;
            default: printf("Invalid Choice, try again\n");
        }
    } while (choice != 5);
}

// Entry point of the program
int main() {
    srand(time(NULL)); // Seed random number generator
    menu();
    return 0;
}