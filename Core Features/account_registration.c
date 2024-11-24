#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char username[50];
    char password[50];
    char email[100];
    double balance;
} Account;

void saveAccount(Account acc){
    FILE *file = fopen("accounts.dat", "a");

    if (file == NULL){
        printf("Error Opening File \n");
        return;
    }

    fwrite(&acc, sizeof(Account), 1, file);
    fclose(file);
}

//New account registration function

void registerAccount(){
    Account newAccount; //The values taken from the user will be placed in the newAccount Variable

    printf("Enter your Username: \n");
    scanf("%s", newAccount.username);
    printf("Enter your Password: \n");
    scanf("%s", newAccount.password);
    printf("Enter your E-mail:\n");
    scanf("%s", newAccount.email);

    newAccount.balance = 0.0;
    saveAccount(newAccount);

    printf("Account Created Successfully!!!");
}

int main(){
    int choice;

    printf("Welcome to Paystream \n");
    printf("1. Register your account \n");
    printf("Enter your choice \n");
    scanf("%d", &choice);

    if(choice == 1){
        registerAccount();
    } else{
        printf("Invalid Choice \n");
        return 0;
    }
}