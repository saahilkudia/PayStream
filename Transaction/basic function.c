#include <stdio.h>
int main() 
{
    long int available = 0; 
    long int withdraw, deposit;
    int ch;
    char c;
    do 
    {
        puts("Enter Your Choice:");
        puts("1. Withdraw");
        puts("2. Deposit");
        puts("3. Balance Inquiry");
        scanf("%d", &ch);
        switch (ch) 
        {
            case 1: 
            {
                puts("Enter Amount To Be Withdrawn:");
                scanf("%ld", &withdraw);
                if (withdraw > available) 
                {
                    printf("Sorry, Amount Cannot Be Withdrawn:Insufficient balance:\n");
                } 
                else 
                {
                    available = available - withdraw;
                    printf("Amount Withdrawn Successfully:\n", available);
                }
                break;
            }
            case 2: 
            {
                puts("Enter Amount To Be Deposited:");
                scanf("%ld", &deposit); 
                available = available + deposit;
                printf("Amount Deposited Successfully:\n", available);
                break;
            }
            case 3: 
            {
                printf("Available Balance: %ld\n", available);
                break;
            }
            default: {
                puts("Invalid Choice:Please enter a valid option");
            }
        }
        puts("Do You Want To Make Another Transaction? (y/n): ");
        scanf(" %c", &c);
    } 
    while (c == 'y');
    return 0;
}


