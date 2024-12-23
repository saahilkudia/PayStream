#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int accountNumber;
    char name[50];
    char email[50];
    char accountType[10];
    char password[20];
    double balance;
} Account;

int generateNum(){
    return 100000 + rand() % 900000; //Random Number Generator
}

int doesAccountExsist(int accountNumber){
    FILE *file = fopen("accounts.dat", "rb");
    if(!file) return 0;

    Account acc;
    while(fread(&acc, sizeof(Account), 1, file)){
        if(acc.accountNumber == accountNumber){
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void getAccountDetails(Account *newAccount){
    printf("Enter your Full Name: ");
    getchar(); fgets(newAccount -> name, 50, stdin); strtok(newAccount -> name, "\n");

    printf("Enter your E-mail: ");
    getchar(); fgets(newAccount -> email, 50, stdin); strtok(newAccount -> email, "\n");

    printf("Enter Account Type: ");
    scanf("%s", newAccount -> accountType);

    printf("Enter your initial balance: ");
    scanf("%lf", &newAccount->balance);
    getchar(); // Clear the buffer again

    printf("Enter your Password: ");
    getchar(); // Clear buffer from previous input
    fgets(newAccount->password, 20, stdin);
    strtok(newAccount->password, "\n");
}

void createAccount(){
    Account newAccount;
    FILE *file = fopen("accounts.dat", "ab");
    if(!file){
        printf("Error Opening File");
        return;
    }

    do{
        newAccount.accountNumber = generateNum();
    } while(doesAccountExsist(newAccount.accountNumber));

    printf("Account Number Generated: %d\n", newAccount.accountNumber);
    getAccountDetails(&newAccount); //stroring in the above function

    if(newAccount.balance < 0){
        printf("Balance cannot be negetive\n");
        fclose(file);
        return;
    }

    fwrite(&newAccount, sizeof(Account), 1, file);
    fclose(file);
    printf("Account Created Successfully!!\n");
}

int authenticateUser(int accountNumber, char *enteredPassword){
    FILE *file = fopen("accounts.dat", "rb");
    if(!file){
        printf("Error opening file!!!\n");
        return 0;
    }

    Account acc;
    while(fread(&acc, sizeof(Account), 1, file)){
        if(acc.accountNumber == accountNumber && strcmp(acc.password, enteredPassword) == 0){
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void deleteAccount(){
    int accountNumber;
    char password[20];
    printf("Enter the Account NUmber to Delete: \n");
    scanf("%d", &accountNumber);
    printf("Enter the Password: \n");
    scanf("%s", password);

    if(!authenticateUser(accountNumber, password)){
        printf("Authentication Failed");
        return;
    }

    FILE *file = fopen("accounts.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if(!file || !temp){
        printf("Enter opening file!!\n");
        return;
    }

    Account acc;
    int found = 0;
    while(fread(&acc, sizeof(Account), 1, file)){
        if(acc.accountNumber != accountNumber){
            fwrite(&acc, sizeof(Account), 1, temp);
        } else{
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if(found){
        printf("Account Deleted Successfully!!\n");
    } else{
        printf("Account not found\n");
    }
}

void viewAccount(){
    int accountNumber;
    char password[20];
    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    printf("Enter Password: ");
    scanf("%s", password);

    if(!authenticateUser(accountNumber, password)){
        printf("Authentication Failed!!!\n");
        return;
    }

    FILE *file = fopen("accounts.dat", "rb");
    if(!file){
        printf("Error Opening File!!!\n");
        return;
    }

    Account acc;
    int found = 0;
    while(fread(&acc, sizeof(Account), 1, file)){
        if(acc.accountNumber == accountNumber){
            printf("Account No: %d\n", acc.accountNumber);
            printf("Name: %s\n", acc.name);
            printf("Email: %s\n", acc.email);
            printf("Account Type: %s\n", acc.accountType);
            printf("Balance %2lf\n", acc.balance);
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found){
        printf("Account not Found!!\n");
    }
}

void updateAccount(){
    int accountNumber;
    char password[20];
    printf("Enter Account Number to Update: ");
    scanf("%d", &accountNumber);
    printf("Enter Passowrd: ");
    scanf("%s", password);

    if(!authenticateUser(accountNumber, password)){
        printf("Authentication Failed!!\n");
        return;
    }

    FILE *file = fopen("accounts.dat", "rb+");
    if(!file){
        printf("Error Opening File!!!\n");
        return;
    }

    Account acc;
    int found = 0;
    while (fread(&acc, sizeof(Account), 1, file)){
        if(acc.accountNumber == accountNumber){
            getAccountDetails(&acc);
            fseek(file, -(long)sizeof(Account), SEEK_CUR);
            fwrite(file, sizeof(Account), 1, file);
            found = 1;
            printf("Account Updated Successfully!!\n");
            break;
        }
    }
    fclose(file);
    if(!found){
        printf("Account not found!!\n");
    }
}

void menu(){
    int choice;
    do{
        printf("1. Create Account\n");
        printf("2. View Account\n");
        printf("3. Delete Account\n");
        printf("4. Upadte Account\n");
        printf("5. Exit Program\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch(choice){
            case 1: createAccount(); break;
            case 2: viewAccount(); break;
            case 3: deleteAccount(); break;
            case 4: updateAccount(); break;
            case 5: printf("Exiting Program....\n");
            default: printf("Invalid Choice, try again\n");
        }
    } while(choice != 5);
}

int main(){
    srand(time(NULL)); //Random Number Activate
    menu();
    return 0;
}