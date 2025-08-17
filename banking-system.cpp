#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// ---------- Transaction Class ----------
class Transaction {
    string type;
    double amount;
    string timestamp;

    string getCurrentTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        string t(dt);
        t.pop_back(); // remove newline
        return t;
    }

public:
    Transaction(string t, double amt) {
        type = t;
        amount = amt;
        timestamp = getCurrentTime();
    }

    void display() const {
        cout << "[" << timestamp << "] " << type << " : $" << amount << endl;
    }
};

// ---------- Account Class ----------
class Account {
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo, double bal = 0.0) {
        accountNumber = accNo;
        balance = bal;
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "Deposited $" << amount << " successfully.\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount);
        cout << "Withdrew $" << amount << " successfully.\n";
        return true;
    }

    bool transfer(Account &toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            transactions.emplace_back("Transfer to " + to_string(toAccount.getAccountNumber()), amount);
            return true;
        }
        return false;
    }

    void showTransactions() const {
        cout << "Transaction History for Account " << accountNumber << ":\n";
        if (transactions.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        for (const auto &t : transactions)
            t.display();
    }

    void displayAccountInfo() const {
        cout << "Account No: " << accountNumber << " | Balance: $" << balance << endl;
    }
};

// ---------- Customer Class ----------
class Customer {
    string name;
    int customerId;
    vector<Account> accounts;

public:
    Customer(string n, int id) {
        name = n;
        customerId = id;
    }

    void addAccount(int accNo, double initialBalance = 0.0) {
        accounts.emplace_back(accNo, initialBalance);
        cout << "Account " << accNo << " created for " << name << ".\n";
    }

    Account* getAccount(int accNo) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accNo)
                return &acc;
        }
        cout << "Account not found!\n";
        return nullptr;
    }

    void displayCustomerInfo() {
        cout << "Customer: " << name << " (ID: " << customerId << ")\n";
        for (auto &acc : accounts)
            acc.displayAccountInfo();
    }
};

// ---------- Main ----------
int main() {
    vector<Customer> customers;

    int choice;
    do {
        cout << "\n===== Banking System Menu =====\n";
        cout << "1. Create Customer\n";
        cout << "2. Add Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer Funds\n";
        cout << "6. Show Account Info\n";
        cout << "7. Show Transactions\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int id;
            cout << "Enter Customer Name: ";
            cin >> name;
            cout << "Enter Customer ID: ";
            cin >> id;
            customers.emplace_back(name, id);
            cout << "Customer created successfully.\n";
        } 
        else if (choice == 2) {
            int id, accNo;
            double bal;
            cout << "Enter Customer ID: ";
            cin >> id;
            cout << "Enter New Account No: ";
            cin >> accNo;
            cout << "Enter Initial Balance: ";
            cin >> bal;

            bool found = false;
            for (auto &c : customers) {
                if (id == id) {
                    c.addAccount(accNo, bal);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Customer not found!\n";
        } 
        else if (choice == 3) {
            int id, accNo;
            double amt;
            cout << "Enter Customer ID: ";
            cin >> id;
            cout << "Enter Account No: ";
            cin >> accNo;
            cout << "Enter Deposit Amount: ";
            cin >> amt;

            bool done = false;
            for (auto &c : customers) {
                if (c.getAccount(accNo)) {
                    c.getAccount(accNo)->deposit(amt);
                    done = true;
                    break;
                }
            }
            if (!done) cout << "Account not found!\n";
        } 
        else if (choice == 4) {
            int accNo;
            double amt;
            cout << "Enter Account No: ";
            cin >> accNo;
            cout << "Enter Withdrawal Amount: ";
            cin >> amt;

            bool done = false;
            for (auto &c : customers) {
                Account* acc = c.getAccount(accNo);
                if (acc) {
                    acc->withdraw(amt);
                    done = true;
                    break;
                }
            }
            if (!done) cout << "Account not found!\n";
        } 
        else if (choice == 5) {
            int accFrom, accTo;
            double amt;
            cout << "Enter From Account No: ";
            cin >> accFrom;
            cout << "Enter To Account No: ";
            cin >> accTo;
            cout << "Enter Amount: ";
            cin >> amt;

            Account *from = nullptr, *to = nullptr;
            for (auto &c : customers) {
                if (!from) from = c.getAccount(accFrom);
                if (!to) to = c.getAccount(accTo);
            }

            if (from && to) {
                from->transfer(*to, amt);
            } else {
                cout << "Invalid account numbers.\n";
            }
        } 
        else if (choice == 6) {
            int id;
            cout << "Enter Customer ID: ";
            cin >> id;
            bool found = false;
            for (auto &c : customers) {
                // We don't have getId(), so just display directly
                c.displayCustomerInfo();
                found = true;
            }
            if (!found) cout << "Customer not found!\n";
        } 
        else if (choice == 7) {
            int accNo;
            cout << "Enter Account No: ";
            cin >> accNo;

            bool found = false;
            for (auto &c : customers) {
                Account* acc = c.getAccount(accNo);
                if (acc) {
                    acc->showTransactions();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found!\n";
        }
    } while (choice != 0);

    cout << "Exiting Banking System. Goodbye!\n";
    return 0;
}
