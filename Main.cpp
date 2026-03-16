#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

string ADMIN_PASSCODE = "6767";
const int NUM_BANKS = 4;
string bankNames[NUM_BANKS] = {"BDO", "BPI", "Metrobank", "Security Bank"};
double localFees[NUM_BANKS] = {25, 20, 30, 15};
double intlFees[NUM_BANKS] = {150, 125, 200, 100};
double dailyLimits[NUM_BANKS] = {50000, 75000, 100000, 60000};

const int NUM_DENOMINATIONS = 3;
int denominations[NUM_DENOMINATIONS] = {500, 1000, 5000};
int billCount[NUM_DENOMINATIONS] = {500, 500, 500};

// Global vectors
vector<string> cardNumbers;
vector<string> encodedPINs;
vector<double> balances;
vector<string> userBanks;
vector<string> accountTypes;
vector<string> transactionTypes;
vector<double> transactionAmounts;
vector<double> transactionFees;
vector<int> transactionQuantities;

//  utility functions 
string encodeString(string plain) { return plain; }
string decodeString(string encoded) { return encoded; }
bool validateCardNumber(string card) { return true; }
double calculateFeeRecursive(double amount, int iterations) { return 20; }

void addAccount(string card, string pin, double balance, string bank, string type) {
    cardNumbers.push_back(card);
    encodedPINs.push_back(encodeString(pin));
    balances.push_back(balance);
    userBanks.push_back(bank);
    accountTypes.push_back(type);
}

//logTransaction 
void logTransaction(string type, double amount, double fee) {
    bool found = false;
    for (size_t i = 0; i < transactionTypes.size(); i++) {
        if (transactionTypes[i] == type) {
            transactionAmounts[i] += amount;
            transactionFees[i] += fee;
            transactionQuantities[i]++;
            found = true;
            break;
        }
    }
    
    if (!found) {
        transactionTypes.push_back(type);
        transactionAmounts.push_back(amount);
        transactionFees.push_back(fee);
        transactionQuantities.push_back(1);
    }
}


//  CSV 
void logTransactionCSV(string cardNum, string type, double amount, double fee) {
    ofstream file("transaction.csv", ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        file << (timeinfo->tm_mon + 1) << "/" << timeinfo->tm_mday << "/" 
             << (timeinfo->tm_year + 1900) << "," << timeinfo->tm_hour 
             << ":" << timeinfo->tm_min << "," << cardNum << "," << type 
             << "," << amount << "," << fee << endl;
        file.close();
    }
}

//function overload 
void logTransaction(const string& cardNum, const string& type, double amount, double fee = 0) {
    logTransaction(type, amount, fee);
    logTransactionCSV(cardNum, type, amount, fee);
}

void displayDateTime() {
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    cout << "Date: " << (timeinfo->tm_mon + 1) << "/"
         << timeinfo->tm_mday << "/"
         << (timeinfo->tm_year + 1900);
    cout << " Time: " << timeinfo->tm_hour << ":"
         << timeinfo->tm_min << endl;
}

int login();
void clientMenu();
void adminMenu();

int main() 
{
    addAccount("1234567", "1234", 10000, "BPI", "Local");
    logTransaction("Deposit", 5000, 0);  
    
    login();
    
    // Cleanup
    cardNumbers.clear();
    encodedPINs.clear();
    balances.clear();
    userBanks.clear();
    accountTypes.clear();
    transactionTypes.clear();
    transactionAmounts.clear();
    transactionFees.clear();
    transactionQuantities.clear();

    return 0;
}

int login() 
{
    int role;
    string passcode;
    
    cout << "=============================\n";
    cout << "          ARC ATM BANK\n";
    cout << "=============================\n\n";
    cout << "[1] User   [2] Admin   [3] Shutdown\n";
    cout << "Enter choice: ";
    cin >> role;

    if(role == 1)  
    {
        clientMenu();  
    }
        else if (role == 2) 
        {
            adminMenu();   
        }
    return role;
}


void clientMenu() 
{
    string cardNum, pin;
    int accountIndex = -1;

    cout << "Enter your card number: ";
    std::cin >> cardNum;

    for (int i = 0; i < cardNumbers.size(); i++) 
    {
        if(cardNumbers[i] == cardNum) 
        {
            accountIndex = i;
            break;
        }
    }
            if (accountIndex == -1) 
            {
                cout << "\nCard not found\n";
                return;
            }
            

                cout << "Please Enter Your PIN: ";
                std::cin >> pin;

            if(encodeString(pin) != encodedPINs[accountIndex]) 
            {
                cout << "Incorrect PIN, sorry" << endl;
                return;
            }

    

    int choice;
    do 
    {
            time_t now = time(0);
            tm* timeinfo = localtime(&now);  
            
            std::cout << "\n===================\n" << endl;
            cout << "Date: " << timeinfo->tm_mon + 1 << "/" << timeinfo->tm_mday 
                << "/" << timeinfo->tm_year + 1900 << endl;
            cout << "Time: " << timeinfo->tm_hour << ":" << timeinfo->tm_min << endl;
            cout << "Bank: " << userBanks[accountIndex] << endl;
            cout << "Account Type: " << accountTypes[accountIndex] << endl;
            cout << "Current Balance (PHP): " << balances[accountIndex] << endl;
            cout << "------------------------------\n"; 

            cout << "\n=== CLIENT MENU ===\n";
            cout << "1. Check Balance\n";
            cout << "2. Withdraw\n";
            cout << "3. Transfer\n";
            cout << "4. Transaction History\n";
            cout << "5. Change Pin\n";
            cout << "6. LOGOUT\n";
            cout << "Enter choice: ";
            std::cin >> choice;
            
            if(choice == 1) 
            {
                cout << "Your Balance is: (PHP) " << balances[accountIndex] << endl;
            }
            else if (choice == 2) 
            {
                int opt;
                double amount = 0;
                int customAmount;
                
                cout << "\n=== WITHDRAW ===" << endl;
                cout << "1. Withdraw 100" << endl;
                cout << "2. Withdraw 500" << endl;
                cout << "3. Withdraw 1000" << endl;
                cout << "4. Withdraw 5000" << endl;
                cout << "5. Enter other amount" << endl;
                cout << "Choice: ";
                std::cin >> opt;

                if(opt == 1) amount = 100;
                else if(opt == 2) amount = 500;
                else if(opt == 3) amount = 1000;
                else if(opt == 4) amount = 5000;
                else if(opt == 5) 
                {
                    
                    cout << "\n----------\n";
                    cout << "Enter Amount: ";
                    std::cin >> customAmount;
                    amount = customAmount;
                }

                if (amount <= 0) 
                {
                    cout << "Amount Invalid\n\n" << endl;
                    continue;
                }

                if (amount > balances[accountIndex]) 
                {
                    cout << "\nYou don't have enough balance on your account\n";
                    continue;
                }
                
                double fee = 20;
                double totalDeduction = amount + fee;

                if(balances[accountIndex] >= totalDeduction)
                {
                    balances[accountIndex] -= totalDeduction; 
                    cout << "\nThe withdraw is successful\n" << endl;
                    
                    logTransaction("Withdrawal", amount, fee);  
                    
                    bool found = false;
                        for(int i = 0; i < (int)transactionTypes.size(); i++) 
                        {
                            if(transactionTypes[i] == "Withdraw") 
                            {
                                transactionQuantities[i]++;
                                found = true;
                                break;
                            }
                        }
                    if(!found) 
                    {
                        transactionTypes.push_back("Withdraw");
                        transactionAmounts.push_back(amount);
                        transactionFees.push_back(fee);
                        transactionQuantities.push_back(1);
                    }
                } 
                    else 
                    {
                        cout << "Not Enough Balance, Sorry\n" << endl;
                    }
            }
        
            else if (choice == 3) 
            {
                
                string receiver;
                double amount;
                
                cout << "\n=== TRANSFER MONEY ===\n";
                cout << "Enter Recipient Card Number: ";
                std::cin >> receiver;

                int receiverIndex = -1;
                for(int i = 0; i < (int)cardNumbers.size(); i++) 
                {
                    if(cardNumbers[i] == receiver) 
                    {
                        receiverIndex = i;
                        break;
                    }
                }

                if(receiverIndex == -1) 
                {
                    cout << "Recipient not found" << endl;
                } 
                    else 
                    {
                        cout << "Enter Amount: ";
                        std::cin >> amount;

                        if (amount <= 0) 
                        {
                            cout << "Amount Invalid";
                            continue;
                        }

                        if (amount > balances[accountIndex]) 
                        {
                            cout << "\nYou don't have enough balance on your account";
                            continue;
                        }
                        
                        double fee = 20;
                        if(balances[accountIndex] >= amount + fee) 
                        {
                            balances[accountIndex] -= (amount + fee);
                            balances[receiverIndex] += amount;
                            logTransaction("Transfer", amount, fee);  
                            
                            cout << "\nTransfer Successful. Thank you! " << endl;
                        } 
                        else
                        {
                            cout << "\nNot Enough Balance, Sorry" << endl;
                        }
                    }
            }
            else if (choice == 4) 
            {
                cout << "\n=== TRANSACTION HISTORY ===\n";
                
                if(transactionTypes.empty()) 
                { 
                    cout << "No new transactions has occured " << endl; 
                } 
                
                else 
                { 
                    for(int i = 0; i < (int)transactionTypes.size(); i++) 
                    {
                        cout << transactionTypes[i] << " | "
                            << transactionAmounts[i] << " | "
                            << transactionFees[i] << " | "
                            << "QTY: " << transactionQuantities[i] << endl;
                    } 
                }
            }
            else if(choice == 5) 
            {
                string oldPin, newPin;
                
                cout << "\n===PIN CHANGE===\n";
                cout << "Enter Old Pin: ";
                std::cin >> oldPin;

                if(encodeString(oldPin) == encodedPINs[accountIndex]) 
                {
                    cout << "Enter New Pin: ";
                    std::cin >> newPin;

                        if(newPin != oldPin) 
                        {
                            encodedPINs[accountIndex] = encodeString(newPin);
                            cout << "\nPIN has been changed successfully! " << endl;
                        } 
                            else 
                            {
                                cout << "\nPIN is the same. Please enter new pin. " << endl;
                            }
                } 
                    else 
                    {
                        cout << "Old pin incorrect" << endl;
                    }
            }
            else if (choice == 6)
            {
                    cout << "Logging out. Thank you! " << endl;
                    login();
            }
        } 
    while (choice != 6);
    }


void adminMenu() 
{
    int attempt = 0;
    string encoded_pw;
    while (attempt < 3) 
    {
        cout << "Enter Admin Password: ";
        cin >> encoded_pw;
        
        if (encoded_pw == ADMIN_PASSCODE) 
        {
            cout << "Login Successful.\n";
            break;
        } 
        else 
        {
            cout << "Password Wrong.\n";
            attempt++;
        }
    }
    
    if (attempt == 3) return;
    
    bool Menu = true;
    while (Menu) 
    {
        char choice;
        cout << "------------------------\n";
        cout << "      ADMIN MENU\n";
        cout << "------------------------\n";
        cout << "(A) Cash Management\n";
        cout << "(B) User Account Management\n";
        cout << "(C) Admin Credential Management\n";
        cout << "(D) Machine Refilling\n";
        cout << "(E) Exit\n";
        cin >> choice;
         // Declare all variables used in switch cases before the switch statement
         int sum = 0;
        int totalCash = 0;
        int useracc_choice = 0;
        string new_cardNumber, new_Pin, new_userBanks, new_accountTypes, new_Balance;
        int cardNo = 0, index = -1;
        string n;
        string newPassword, currentPassword, change;
        int view = 0;
        time_t now;
        tm* localTime = nullptr;
        vector<string> adminID = {"A001", "A002", "A003"};
        vector<string> adminName = {"Romeo", "Aljosh", "Camille"};
        switch(choice) 
        {
            
            
            case 'A':
            case 'a': 
            {
                int totalCash = 0;
                for (int i = 0; i < NUM_DENOMINATIONS; i++) 
                {
                    int sum = denominations[i] * billCount[i];
                    cout << denominations[i] << " * " << billCount[i] << " = " << sum << endl;
                    totalCash += sum;
                }
                cout << "Total: " << totalCash << endl;
                break;
            }

            //USER ACCOUNT Management
            case 'B':
            case 'b':
                std::cout << " USER ACCOUNT MANAGEMENT " << endl;
                std::cout << endl;
                
                std::cout << "1 - Create Account\n";
                std::cout << "2 - View All Account\n";
                std::cout << "3 - Delete Account\n";
                std::cout << "4 - Reset PIN\n";
                std::cin >> useracc_choice;
                
                if (useracc_choice == 1) 
                {
                    cout << "Card Number: ";
                    std::cin >> new_cardNumber;
                    cardNumbers.push_back(new_cardNumber);
                    
                    cout << "PIN: ";
                    std::cin >> new_Pin;
                    encodedPINs.push_back(new_Pin);
                    
                    cout << "Bank: ";
                    cin >> new_userBanks;
                    userBanks.push_back(new_userBanks);
                    
                    cout << "Account Type: ";
                    cin >> new_accountTypes;
                    accountTypes.push_back(new_accountTypes);
                    
                    cout << "Initial Balance: ";
                    cin >> new_Balance;
                    balances.push_back(stod(new_Balance));
                    
                }
                
                    else if (useracc_choice == 2) 
                    {
                        cout << "Viewing all accounts...\n\n\n";
                        cout << "Card Number" << "       " << "Bank" << "       " << "Account Type" << "       " << "Initial Balance" << endl;
                        
                            for (int i = 0; i < cardNumbers.size(); i++) 
                            {
                                cout << cardNumbers[i] << "       " << userBanks[i] << "       " << accountTypes[i] << "       " << balances[i] << endl;
                            }
                        
                    }
                
                        else if (useracc_choice == 3) 
                        {
                            cout << "Delete Account\n\n";
                            cout << "Card Number to delete: ";
                            std::cin >> cardNo;
                            
                            index = -1; // Initialize index to -1 (or use size() if unsigned) to indicate "not found"

                                for (int i = 0; i < cardNumbers.size(); ++i) 
                                {
                                    if (cardNumbers[i] == to_string(cardNo)) 
                                    {
                                        index = i;
                                        break; // Stop searching once found
                                    }
                                }

                            if (index != -1) 
                            {
                                cardNumbers.erase(cardNumbers.begin() + index);
                                encodedPINs.erase(encodedPINs.begin() + index);
                                userBanks.erase(userBanks.begin() + index);
                                accountTypes.erase(accountTypes.begin() + index);
                                balances.erase(balances.begin() + index);
                            } 
                                else 
                                {
                                    std::cout << "Card No. " << cardNo << " not found." << endl;
                                }
                        }
                
                            else if (useracc_choice == 4) 
                            {
                                cout << "Reset Pin\n\n";
                                cout << "Card Number: ";
                                cin >> cardNo;
                                
                                index = -1; // Initialize index to -1 (or use size() if unsigned) to indicate "not found"

                                for (int i = 0; i < cardNumbers.size(); ++i) 
                                {
                                    if (cardNumbers[i] == to_string(cardNo)) 
                                    {
                                        index = i;
                                        break; // Stop searching once found
                                    }
                                }
                            
                                cout << "New PIN: ";
                                std::cin >> n;
                            
                                if (index != -1) 
                                {
                                    encodedPINs.at(index) = n;
                                }
                            
                        }
            break;
            
            //ADMIN CREDENTIAL MANAGEMENT
            case 'C': 
            case 'c':
                cout << " ADMIN CREDENTIAL MANAGEMENT \n\n" << endl;
                cout << "Do you want to change passcode? (yes/no)";
                cin >> change;
                
                if (change == "Yes" || change == "yes") 
                {
                    cout << "Current Password: ";
                    cin >> currentPassword; 
                    
                    if (currentPassword == ADMIN_PASSCODE) 
                    {
                        cout << "New Password: ";
                        cin >> newPassword;
                        
                        if (newPassword == ADMIN_PASSCODE) 
                        {
                            cout << "Same Password Not Allowed.";
                        }
                            else 
                            {
                                ADMIN_PASSCODE = newPassword;
                                cout << "Password Changed Successfully.";
                            }
                    }
                    else 
                    {
                        cout << "Wrong Password.";
                    }
                }
                
                cout << "1 - View Admin List";
                cin >> view;
                
                if (view == 1) 
                {
                    for (int i = 0; i < 3; i++) 
                    {
                        cout << adminID[i] << "         " << adminName[i]<< " ";
                        cout<<"\n\n";  //make vector for adminID and adminName
                    }
                }
                
            break;
                
            //Machine Refilling
            case 'D':
            case 'd':
                now = time(0);
                localTime = localtime(&now);
            
                // Check if current time is between 8:00 and 8:15
                if (localTime->tm_hour != 8 || localTime->tm_min > 15) 
                {
                    cout << "Refill allowed only from 8:00 AM to 8:15 AM." << endl;
                    return;
                }
            
                // Refill bills
                billCount[0] += 50; // Add 50 bills of the first denomination
                cout << "Refill successful." << endl;
            break;
            
            // Add other cases as needed...
            case 'E':
            case 'e':
                Menu = false;
                login();
                break;
            default:
                cout << "Invalid\n";
        }
    }
}
