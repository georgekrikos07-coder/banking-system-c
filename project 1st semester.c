#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 25

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    double balance;
} Account;

void show_login_menu();
bool login(Account *acc);
void create_new_Account(Account *acc);
void show_menu();
void deposit(Account *acc);
void withdraw(Account *acc);
void save_account(Account acc);
void load_account(Account *acc);
void remove_newline(char str[]);

int main() {
    int choice, choice2;
    Account acc;
    bool account_loaded = false;
    
    do {
        show_login_menu();
        printf("Choose option: ");
        scanf("%d", &choice2);
        getchar();

        switch (choice2) {
            case 1:
                load_account(&acc);
                if (login(&acc)) {
                    account_loaded = true;
                } else {
                    printf("Access denied\n");
                    return 0;
                }
                break;
            case 2:
                create_new_Account(&acc);
                save_account(acc);
                account_loaded = true;
                break;
            case 3:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid option\n");
                break;
        }
    } while (!account_loaded);
    
    do {
        show_menu();
        printf("Choose option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Balance: %.2f €\n", acc.balance);
                break;
            case 2:
                deposit(&acc);
                break;
            case 3:
                withdraw(&acc);
                break;
            case 4:
                save_account(acc);
                printf("Account saved. Goodbye!\n");
                break;
            default: 
                printf("Invalid option\n");
        }
    } while (choice != 4);

    return 0;
}

bool login(Account *acc) {
    char input[MAX_LEN];
    int tries = 3;

    while (tries > 0) {
        printf("Enter password: ");
        fgets(input, MAX_LEN, stdin);
        remove_newline(input);

        if (strcmp(input, acc->password) == 0) {
            printf("Welcome %s\n", acc->username);
            return true;
        }

        tries--;
        printf("Wrong password (%d tries left)\n", tries);
    }
    return false;
}

void show_login_menu() {
    printf("\n----- BANK LOGIN -----\n");
    printf("1. Login (existing user)\n");
    printf("2. Create a new account\n");
    printf("3. Exit\n");
}

void show_menu() {
    printf("\n----- BANK MENU -----\n");
    printf("1. Show balance\n");
    printf("2. Deposit money\n");
    printf("3. Withdraw money\n");
    printf("4. Save and Exit\n");
}

void load_account(Account *acc) {
    FILE *fp = fopen("account.txt", "r");

    if (fp == NULL) {
        printf("No account file found.\n");
        strcpy(acc->username, "");
        strcpy(acc->password, "");
        acc->balance = 0.0;
        return;
    }

    fgets(acc->username, MAX_LEN, fp);
    remove_newline(acc->username);

    fgets(acc->password, MAX_LEN, fp);
    remove_newline(acc->password);

    fscanf(fp, "%lf", &acc->balance);

    fclose(fp);
    printf("Account loaded for user: %s\n", acc->username);
}

void deposit(Account *acc) {
    double amount;

    printf("Amount to deposit: ");
    scanf("%lf", &amount);
    getchar();

    if (amount <= 0) {
        printf("Invalid amount\n");
        return;
    }
    acc->balance += amount;
    printf("Deposited %.2f €. New balance: %.2f €\n", amount, acc->balance);
}

void withdraw(Account *acc) {
    double amount;

    printf("Amount to withdraw: ");
    scanf("%lf", &amount);
    getchar();

    if (amount <= 0 || amount > acc->balance) {
        printf("Transaction denied\n");
        return;
    }
    acc->balance -= amount;
    printf("Withdrew %.2f €. New balance: %.2f €\n", amount, acc->balance);
}

void create_new_Account(Account *acc) {
    printf("\n----- CREATE NEW ACCOUNT -----\n");
    printf("Enter username: ");
    fgets(acc->username, MAX_LEN, stdin);
    remove_newline(acc->username);
    
    printf("Enter password: ");
    fgets(acc->password, MAX_LEN, stdin);
    remove_newline(acc->password);
    
    acc->balance = 0.0;
    
    printf("\nAccount created successfully!\n");
    printf("Welcome %s! Your starting balance is %.2f €\n", acc->username, acc->balance);
}

void save_account(Account acc) {
    FILE *fp = fopen("account.txt", "w");

    if (fp == NULL) {
        printf("Error saving account!\n");
        return;
    }

    fprintf(fp, "%s\n", acc.username);
    fprintf(fp, "%s\n", acc.password);
    fprintf(fp, "%.2f\n", acc.balance);

    fclose(fp);
    printf("Account saved successfully!\n");
}

void remove_newline(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}


