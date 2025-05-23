#include <iostream>
#include <string>
#include <iomanip>
#include <list>
#include <algorithm>
using namespace std;

// Account structure
struct Account {
    unsigned long long account_number;
    string holder_name;
    int deposit;
    char type;

    Account(unsigned long long acc_no, string name, int dep, char acc_type)
        : account_number(acc_no), holder_name(name), deposit(dep), type(toupper(acc_type)) {}
};

// Bank class using STL
class Bank {
private:
    list<Account> accounts;

    auto findAccount(unsigned long long acc_no) {
        return find_if(accounts.begin(), accounts.end(),
            [acc_no](const Account& acc) { return acc.account_number == acc_no; });
    }

public:
    void createAccount() {
        unsigned long long acc_no;
        string name;
        int dep;
        char acc_type;

        cout << "\nEnter Account Number (12 digits): ";
        cin >> acc_no;
        while (to_string(acc_no).length() != 12) {
            cout << "Invalid. Please enter 12-digit number: ";
            cin >> acc_no;
        }

        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Account Type (S for Savings, C for Current): ";
        cin >> acc_type;
        acc_type = toupper(acc_type);
        while (acc_type != 'S' && acc_type != 'C') {
            cout << "Invalid type. Enter S or C: ";
            cin >> acc_type;
            acc_type = toupper(acc_type);
        }

        cout << "Enter Initial Deposit: ";
        cin >> dep;

        accounts.emplace_back(acc_no, name, dep, acc_type);
        cout << "Account created successfully!\n";
    }

    void displayAllAccounts() {
        cout << "\nAll Account Details:\n";
        cout << "-----------------------------------------------\n";
        cout << "Acc No       | Name               | Type | Balance\n";
        cout << "-----------------------------------------------\n";
        for (const auto& acc : accounts) {
            cout << setw(12) << acc.account_number << " | "
                 << setw(18) << acc.holder_name << " | "
                 << setw(4) << acc.type << " | "
                 << setw(7) << acc.deposit << "\n";
        }
    }

    void displayAccount(unsigned long long acc_no) {
        auto it = findAccount(acc_no);
        if (it != accounts.end()) {
            cout << "Account No: " << it->account_number << "\n";
            cout << "Holder Name: " << it->holder_name << "\n";
            cout << "Type: " << it->type << "\n";
            cout << "Balance: " << it->deposit << "\n";
        } else {
            cout << "Account not found.\n";
        }
    }

    void depositAmount(unsigned long long acc_no) {
        auto it = findAccount(acc_no);
        if (it != accounts.end()) {
            int amt;
            cout << "Enter amount to deposit: ";
            cin >> amt;
            it->deposit += amt;
            cout << "Deposit successful. Updated balance: " << it->deposit << "\n";
        } else {
            cout << "Account not found.\n";
        }
    }

    void withdrawAmount(unsigned long long acc_no) {
        auto it = findAccount(acc_no);
        if (it != accounts.end()) {
            int amt;
            cout << "Enter amount to withdraw: ";
            cin >> amt;
            if ((it->type == 'S' && it->deposit - amt < 500) ||
                (it->type == 'C' && it->deposit - amt < 1000)) {
                cout << "Insufficient funds for minimum balance.\n";
            } else {
                it->deposit -= amt;
                cout << "Withdrawal successful. Updated balance: " << it->deposit << "\n";
            }
        } else {
            cout << "Account not found.\n";
        }
    }

    void deleteAccount(unsigned long long acc_no) {
        auto it = findAccount(acc_no);
        if (it != accounts.end()) {
            accounts.erase(it);
            cout << "Account deleted successfully.\n";
        } else {
            cout << "Account not found.\n";
        }
    }
};

int main() {
    Bank bank;
    int choice;
    unsigned long long acc_no;

    do {
        cout << "\n=== BANK MANAGEMENT SYSTEM (By Prem Kalyan) ===\n";
        cout << "1. Create New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Display Account\n";
        cout << "4. Deposit Amount\n";
        cout << "5. Withdraw Amount\n";
        cout << "6. Delete Account\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bank.createAccount();
            break;
        case 2:
            bank.displayAllAccounts();
            break;
        case 3:
            cout << "Enter Account No: ";
            cin >> acc_no;
            bank.displayAccount(acc_no);
            break;
        case 4:
            cout << "Enter Account No: ";
            cin >> acc_no;
            bank.depositAmount(acc_no);
            break;
        case 5:
            cout << "Enter Account No: ";
            cin >> acc_no;
            bank.withdrawAmount(acc_no);
            break;
        case 6:
            cout << "Enter Account No: ";
            cin >> acc_no;
            bank.deleteAccount(acc_no);
            break;
        case 7:
            cout << "Thank you for using the Bank Management System.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
