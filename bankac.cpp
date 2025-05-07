#include <iostream>
#include <vector>
using namespace std;

class Transaction {
public:
    string type;
    double amount;

    Transaction(string t, double a) {
        type = t;
        amount = a;
    }
};

class Account {
private:
    int accNo;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int number, double initial) {
        accNo = number;
        balance = initial;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposited: " << amount << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
            return;
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdraw", amount));
        cout << "Withdrawn: " << amount << endl;
    }

    void displayDetails() {
        cout << "Account Number: " << accNo << endl;
        cout << "Current Balance: " << balance << endl;
        cout << "Recent Transactions:\n";
        for (auto& t : transactions) {
            cout << t.type << ": " << t.amount << endl;
        }
    }

    int getAccNo() {
        return accNo;
    }

    double getBalance() {
        return balance;
    }

    void transfer(Account &toAcc, double amount) {
        if (amount > balance) {
            cout << "Transfer failed: Insufficient funds." << endl;
            return;
        }
        withdraw(amount);
        toAcc.deposit(amount);
        cout << "Transferred " << amount << " to Account " << toAcc.getAccNo() << endl;
    }
};

class Customer {
private:
    string name;
    Account account;

public:
    Customer(string cname, int accNo, double initialBal) : account(accNo, initialBal) {
        name = cname;
    }

    void showCustomerDetails() {
        cout << "Customer Name: " << name << endl;
        account.displayDetails();
    }

    Account& getAccount() {
        return account;
    }
};

int main() {
    Customer c1("Alice", 1001, 5000);
    Customer c2("Bob", 1002, 3000);

    c1.getAccount().deposit(2000);
    c1.getAccount().withdraw(1000);
    c1.getAccount().transfer(c2.getAccount(), 1500);

    cout << "\n-- Alice's Account --\n";
    c1.showCustomerDetails();

    cout << "\n-- Bob's Account --\n";
    c2.showCustomerDetails();

    return 0;
}