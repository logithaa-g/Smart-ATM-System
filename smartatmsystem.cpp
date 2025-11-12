#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ATM {
private:
    string accountNumber;
    string name;
    int pin;
    double balance;

public:
    // Constructor
    ATM(string accNo = "", string n = "", int p = 0, double b = 0.0) {
        accountNumber = accNo;
        name = n;
        pin = p;
        balance = b;
    }

    // Create a new account
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Set PIN: ";
        cin >> pin;
        balance = 0.0;

        saveToFile();
        cout << "\n Account created successfully!\n";
    }

    // Deposit money
    void depositMoney(double amount) {
        balance += amount;
        saveToFile();
        cout << " Deposit successful. New Balance: ₹" << balance << endl;
    }

    // Withdraw money
    void withdrawMoney(double amount) {
        if (amount > balance) {
            cout << " Insufficient balance!\n";
        } else {
            balance -= amount;
            saveToFile();
            cout << " Withdrawal successful. Remaining Balance: ₹" << balance << endl;
        }
    }

    // Check balance
    void checkBalance() {
        cout << "\nAccount Holder: " << name << endl;
        cout << "Available Balance: ₹" << balance << endl;
    }

    // Save details to file
    void saveToFile() {
        ofstream file(accountNumber + ".txt");
        file << accountNumber << endl;
        file << name << endl;
        file << pin << endl;
        file << balance << endl;
        file.close();
    }

    // Load details from file
    bool loadFromFile(string accNo, int enteredPin) {
        ifstream file(accNo + ".txt");
        if (!file)
            return false;

        string fileAccNo;
        int filePin;
        string fileName;
        double fileBalance;

        getline(file, fileAccNo);
        getline(file, fileName);
        file >> filePin >> fileBalance;

        if (enteredPin == filePin) {
            accountNumber = fileAccNo;
            name = fileName;
            pin = filePin;
            balance = fileBalance;
            file.close();
            return true;
        }
        file.close();
        return false;
    }
};

int main() {
    ATM user;
    int choice;
    cout << "Welcome to Smart ATM System \n";

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Create New Account\n";
        cout << "2. Login to Existing Account\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            user.createAccount();
        } 
        else if (choice == 2) {
            string accNo;
            int enteredPin;
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            cout << "Enter PIN: ";
            cin >> enteredPin;

            if (user.loadFromFile(accNo, enteredPin)) {
                cout << "\n Login Successful. Welcome, " << accNo << "!\n";
                int option;
                do {
                    cout << "\n--- ATM Menu ---\n";
                    cout << "1. Check Balance\n";
                    cout << "2. Deposit Money\n";
                    cout << "3. Withdraw Money\n";
                    cout << "4. Logout\n";
                    cout << "Enter choice: ";
                    cin >> option;

                    if (option == 1)
                        user.checkBalance();
                    else if (option == 2) {
                        double amount;
                        cout << "Enter deposit amount: ₹";
                        cin >> amount;
                        user.depositMoney(amount);
                    }
                    else if (option == 3) {
                        double amount;
                        cout << "Enter withdrawal amount: ₹";
                        cin >> amount;
                        user.withdrawMoney(amount);
                    }
                    else if (option == 4) {
                        cout << " Logging out...\n";
                    } else {
                        cout << " Invalid choice!\n";
                    }
                } while (option != 4);
            } else {
                cout << " Invalid Account Number or PIN!\n";
            }
        } 
        else if (choice == 3) {
            cout << "\nThank you for using Smart ATM. Goodbye!\n";
            break;
        } 
        else {
            cout << " Invalid input, try again.\n";
        }
    }
    return 0;
}
