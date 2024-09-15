#include <iostream>
#include <string>

using namespace std;

class ATMUser {
protected:
    string username;
    string pin;
    double balance;

public:
    ATMUser(string username, string pin, double balance) : username(username), pin(pin), balance(balance) {}

    string getUsername() { return username; }
    bool verifyPIN(string enteredPIN) { return pin == enteredPIN; }
    double getBalance() { return balance; }
    void setBalance(double newBalance) { balance = newBalance; }

    virtual void performTransaction(double amount, bool isDeposit) = 0;
};

class ATMTransaction : public ATMUser {
public:
    ATMTransaction(string username, string pin, double balance) : ATMUser(username, pin, balance) {}

    void performTransaction(double amount, bool isDeposit) override {
        if (isDeposit) {
            balance += amount;
            cout << "Deposit successful! New balance: ₹" << balance << endl;
        } else {
            if (amount > balance) {
                cout << "Insufficient balance!" << endl;
            } else {
                balance -= amount;
                cout << "Withdrawal successful! New balance: ₹" << balance << endl;
            }
        }
    }
};

class ATMSystem {
private:
    ATMUser* users[50];
    int count;

public:
    ATMSystem() : count(0) {}

    void addUser(ATMUser* user) {
        if (count < 50) {
            users[count++] = user;
        } else {
            cout << "User database is full!" << endl;
        }
    }

    ATMUser* findUser(const string& username) {
        for (int i = 0; i < count; i++) {
            if (users[i]->getUsername() == username) {
                return users[i];
            }
        }
        return nullptr;
    }
};

int main() {
    ATMSystem atm;

    atm.addUser(new ATMTransaction("chalak", "1234", 500.0));
    atm.addUser(new ATMTransaction("aryan", "4321", 1000.0));
    atm.addUser(new ATMTransaction("palak", "5678", 2000.0));
    atm.addUser(new ATMTransaction("Ram", "8765", 1500.0));

    string username, pin;
    int choice;
    double amount;

    while (true) {
        cout << "\nATM System Menu:\n";
        cout << "1. Withdraw\n";
        cout << "2. Deposit\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 3) break;

        cout << "Enter username: ";
        cin >> username;

        ATMUser* user = atm.findUser(username);
        if (user == nullptr) {
            cout << "User not found!" << endl;
            continue;
        }

        cout << "Enter PIN: ";
        cin >> pin;
        if (!user->verifyPIN(pin)) {
            cout << "Invalid PIN!" << endl;
            continue;
        }

        cout << "Enter amount: ";
        cin >> amount;

        if (choice == 1) {
            user->performTransaction(amount, false);  // Withdraw
        } else if (choice == 2) {
            user->performTransaction(amount, true);   // Deposit
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
