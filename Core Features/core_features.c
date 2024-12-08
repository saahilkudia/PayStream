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

int generateAccountNumber(){
    return 100000 + rand() %900000;  //random six number using rand and ensuring that we always get six number
}

//function to create newAccounts
void createAccount(){
    Account newAccount;
    FILE *file = fopen("accounts.dat", "ab");
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
    
    //create account function finally completed
    printf("Account Created Successfully!!!");
}

//Authentication Function Starting
int authenticateUser(int accountNumber, char *enteredPassword){
    FILE *file = fopen("accounts.dat", "rb");
    if(file == NULL){
        printf("Error Opening File!!! \n");
        return 0;
    }
    Account acc;
    while(fread(&acc, sizeof(Account), 1, file)){
        if(acc.accountNumber == accountNumber && strcmp(acc.password, enteredPassword) == 0){
            fclose(file);
            return 1; //authentication successful 
        }
    }
    fclose(file);
    return 0;
}

//function to delete data
void deleteAccount(){
    int accountNumber;
    char password[50];

    printf("Enter Account Number to Delete: \n");
    scanf("%d", &accountNumber);

    printf("Enter Password: \n");
    scanf("%s", password);

    if(!authenticateUser(accountNumber, password)){
        printf("Authentication Failed! Account Number or Password \n");
        return;
    }

    FILE *file = fopen("accounts.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if(file == NULL || temp == NULL){
        printf("Error opening file!!!");
        return;
    }

    Account acc;
    int found = 0;

    while(fread(&acc, sizeof(Account), 1, file)){
        if(acc.accountNumber == accountNumber){
            found = 1;
            printf("Account with number %d deleted successfully", accountNumber);
        } else{
            fwrite(&acc, sizeof(Account), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if(!found){
        printf("Account not Found!!!");
    }
}

//function to create a new account

void viewAccount(){
    int accountNumber;
    char password[20];

    printf("Enter your Account Number: \n");
    scanf("%d", &accountNumber);

    printf("Enter your Password");
    scanf("%s", password);

    if(!authenticateUser(accountNumber, password)){
        printf("Authentication Failed!! Invalid Account Number or Password\n");
        return;
    }

    FILE *file = fopen("accounts.dat", "rb");
    if(file == NULL){
        printf("Enter opening file!!\n");
    }

    Account acc;
    int found = 0;

    while(fread(&acc, sizeof(Account), 1, file)){
        if(acc.accountNumber == accountNumber){
            printf("Account Number: %d\n", acc.accountNumber);
            printf("Name: %d\n", acc.name);
            printf("Email: %d\n", acc.email);
            printf("Account Type: %s\n",acc.accountType);
            printf("Balance %.2lf\n", acc.balance);
            found = 1;
        }
    }

    fclose(file);

    if(!found){
        printf("Account does not exisit");
    }
}

//function to update account

void updateAccount(){
    int accountNumber;
    char password[20];

    printf("Enter your Account Number: \n");
    scanf("%d", &accountNumber);
    
    printf("Enter your Password: \n");
    scanf("%s", password);

    if(!authenticateUser(accountNumber, password)){
        printf("Authentication Failed!!! Invalid Account Number or Password");
        return;
    }

    FILE *file = fopen("accounts.dat", "rb+");
    if(file == NULL){
        printf("Error Opening File \n");
        return;
    }

    Account acc;
    int found = 0;

    while(fread(&acc, sizeof(Account), 1, file)){
        if(acc.accountNumber == accountNumber){
            printf("Enter New Name: \n");
            getchar();
            fgets(acc.name, 50, stdin);
            strtok(acc.name, "\n");

            printf("Enter new Email: \n");
            getchar();
            fgets(acc.email, 50, stdin);
            strtok(acc.email, "\n");

            printf("Enter New Account Type: \n");
            scanf("%s", acc.accountType);

            printf("Enter New Balance: \n");
            scanf("%.lf", acc.balance);

            fseek(file, (long)-sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, file);
            found = 1;
            printf("Account updated successfully");
            break;
        }
    }

    fclose(file);

    if(!found){
        printf("Account not found! \n");

    }
}

//menu navigation system

void menu(){
    int choice;

    do{
        printf("\n Welcome to Paystream\n");
        printf("1. Create Account \n");
        printf("2. View Account \n");
        printf("3. Delete Account \n");
        printf("4. Update Account \n");
        printf("5. Exit \n");
        printf("Enter your choice \n");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                createAccount();
                break;
            
            case 2:
                viewAccount();
                break;

            case 3:
                deleteAccount();
                break;

            case 4:
                updateAccount();
                break;

            case 5:
                printf("Exiting the Program, Goodbye \n");
                break;
            
            default:
                printf("Invalid Choice, Try Again");
        }
    } while(choice != 5);
}

//main function code

int main(){
    srand(time(NULL)); //seed for random number genrator
    menu();
    return 0;
}