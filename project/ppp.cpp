////inheritance,
//abstract class,
//base class
//,polymorphysm,
//pure virtual class,
//operator overloading,
//overriding
//,template...
//stl
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
class Transaction;
template <typename T>
class ATM;
class Account {
private:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    Account(string num, string name)
        : accountNumber(num), accountHolderName(name), balance(0.0) {}

    string getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }
    Account& operator+=(double amount) {
        deposit(amount);
        return *this;
    }

    Account& operator-=(double amount) {
        withdraw(amount);
        return *this;
    }

    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    void deposit(double amount) {
        balance += amount;
    }

};

class Transaction {
private:
    int transactionId;
    string transactionType;
    double amount;

public:
    Transaction(int id, string type, double amt)
        : transactionId(id), transactionType(type), amount(amt) {}

    int getTransactionId() const { return transactionId; }
    string getTransactionType() const { return transactionType; }
    double getAmount() const { return amount; }


    virtual void performTransaction(Account& account) = 0;
};
class WithdrawTransaction : public Transaction {
public:
    WithdrawTransaction(int id, string type, double amt)
        : Transaction(id, type, amt) {}

    void performTransaction(Account& account) override {
        if (account.withdraw(getAmount())) {
            cout << getTransactionType() << " successful. Amount: " << getAmount() << endl;
        } else {
            cout << "Insufficient balance. " << getTransactionType() << " failed." << endl;
        }
    }
};

class DepositTransaction : public Transaction {
public:
    DepositTransaction(int id, string type, double amt)
        : Transaction(id, type, amt) {}

    void performTransaction(Account& account) override {
        account.deposit(getAmount());
        cout << getTransactionType() << " successful. Amount: " << getAmount() << endl;
    }
};



template <typename T>
class ATM {
private:


    int transactionCounter;

public:
    vector<T*> transactions;
     vector<Account> accounts;
    ATM() : transactionCounter(0) {

    }

    ~ATM() {

        for (T* transaction : transactions) {
            delete transaction;
        }
    }

    void login()
    {
        cout<<"=====ENTER YOUR ID:======"<<endl;
        cout<<"------Enter Password :----- "<<endl;
        string s;
        string t;
        cin>>t;
        cin >> s;
        if(t=="2107025" && s == "123"){
            showMenu();
        }else{
            cout << "Wrong PASSWORD OR ID,Try again" << endl;
            login();
        }
    }
    void showMenu() {
        int option;
        double amount;
        do {
            cout << "---- ATM Menu ----" << endl;
            cout << " " << endl;
            cout << "---- WELCOME BACK RUHAN ----" << endl;
            cout << "1. Withdraw" << endl;
            cout << "2. Deposit" << endl;
            cout << "3. Display Transactions" << endl;
            cout << "4. Exit" << endl;
            cout << "Choose an option: ";
            cin >> option;

            switch (option) {
                case 1: {
                    cout << "Enter the amount to withdraw: ";
                    cin >> amount;
                    transactions.push_back(new WithdrawTransaction(++transactionCounter, "Withdraw", amount));
                    executeTransaction();
                    break;
                }
                case 2: {
                    cout << "Enter the amount to deposit: ";
                    cin >> amount;
                    transactions.push_back(new DepositTransaction(++transactionCounter, "Deposit", amount));
                    executeTransaction();
                    break;
                }
                case 3:
                    displayTransactions();
                    break;
                case 4:
                    cout << "Exiting ATM. Thank you!" << endl;
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
        } while (option != 4);
    }

    void executeTransaction() {
        if (!transactions.empty()) {
            T* lastTransaction = transactions.back();
            for (Account& account : accounts) {
                lastTransaction->performTransaction(account);
            }
        }
    }

    void displayTransactions() const {
        cout << "---- Transaction History ----" << endl;
        for (const T* transaction : transactions) {
            cout << "Transaction ID: " << transaction->getTransactionId()
                 << " | Transaction Type: " << transaction->getTransactionType()
                 << " | Amount: " << transaction->getAmount() << endl;
        }
    }
};
template <typename T>
void writeAccountInfoToFile(string filename, vector<T*> transactions) {
    ofstream file(filename);

    if (file.is_open()) {
        file << "---- Transaction History ----" << endl;
        for (T* transaction : transactions) {
            file << "Transaction ID: " << transaction->getTransactionId()
                 << " | Transaction Type: " << transaction->getTransactionType()
                 << " | Amount: " << transaction->getAmount() << endl;
        }

        file.close();
    }
}


int main() {
    ATM<Transaction> atm;

    Account F("2107025","RUHAN");
    atm.login();
    writeAccountInfoToFile<Transaction>("account_info.txt", atm.transactions);

    return 0;
}

