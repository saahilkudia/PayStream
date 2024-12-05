#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

typedef struct{
    int accountNumber;
    char name[50];
    char email[50];
    char accountType[10];
    char password[20];
    double balance;
} Account;

//function to create random account number of new user

int genAccountNum(){
    return 1000 + rand() %900000;  //random six number using rand and ensuring that we always get six number
}

//function to create newAccounts
void createAccount()///{
    Account newAccount;
    FILE *file = fopen("account.dat", "ab");
    if(file == NULL){
        printf("Error opening the file!!!");
        return;
    }

    newAccount.accountNumber = generateAccountNumber();
    printf("Account Number Generate %d\n", newAccount.accountNumber);

    printf("Enter your Full Name: ");
    getchar();
    fgets(newAccount.name, 50, stdin);
    strtok(newAccount.name, "\n");

    printf("Enter your E-mail");
    fgets(newAccount.email, 50, stdin);
    strtok(newAccount.email, "\n");

    printf("Enter account type (Savings/Current): ");
    scanf("%s", newAccount.accountType);

    printf("Enter initial balance to deposit: ");
    scanf("%.1f", &newAccount.balance);

    printf("Set your password (max 20 characters)");
    scanf("%s", newAccount.password);

    fwrite(&newAccount, sizeof(Account), 1, file);
    fclose(file);

    printf("My name is Muhammad Saahil");
}