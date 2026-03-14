
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
string ADMIN_PASSCODE = "6767";
const int NUM_BANKS = 4;
string bankNames[NUM_BANKS] = {"BDO", "BPI", "Metrobank", "Security Bank"};
double localFees[NUM_BANKS] = {25, 20, 30, 15};
double intlFees[NUM_BANKS] = {150, 125, 200, 100};
double dailyLimits[NUM_BANKS] = {50000, 75000, 100000, 60000};
const int NUM_DENOMINATIONS = 2;
int denominations[NUM_DENOMINATIONS] = {500, 1000};
int billCount[NUM_DENOMINATIONS] = {500, 500}; // Current count of each 

// Utility functions
string encodeString(string plain);
string decodeString(string encoded);
bool validateCardNumber(string card);
double calculateFeeRecursive(double amount, int iterations);
vector<string> cardNumbers;

void adminMenu (vector<string>& cardNumbers,
               vector<double>& balances,
               string& ADMIN_PASSCODE, 
               vector<string>& userBanks, 
               vector<string>& encodedPINs, 
               vector<string>& accountTypes, 
               const int NUM_DENOMINATIONS, 
               int &denominations_NUM_DENOMINATIONS,
               int &billCountNUM_DENOMINATIONS
               /*, ... other vectors if needed */)
{
    //Admin Authentication
    int attempt = 0;
    string encoded_pw;
    while (attempt < 3)
    {
        cout << "Enter Admin Password: ";
        cin >> encoded_pw;
        
            if (encoded_pw == ADMIN_PASSCODE)
            {
                cout << "Login Successful.";
                continue;
            }
                else
                {
                    cout << "Password Wrong.";
                    attempt++;
                }
    
        if (attempt == 3) 
        {
            break;
        }
    }
    //Admin Menu
    bool Menu = true;
    while (Menu) 
    {
        int choice;
        cout << "------------------------" << endl;
        cout << "      ADMIN MENU" << endl;
        cout << "------------------------" << endl;
        
        cout << "(A) Cash Management" << endl;
        cout << "(B) User Account Management" << endl;
        cout << "(C) Admin Credential Management" << endl;
        cout << "(D) Machine Refilling" << endl;
        cout << "(E) Exit" << endl;
        cin >> choice;
        
        switch (choice) 
        {
            case 'A':
            case 'a':
                int sum;
                cout << " CASH MANAGEMENT " << endl;
                int totalCash = 0;
                
                for (int i = 0; i < denominations[NUM_DENOMINATIONS]; i++) 
                {
                    sum = denominations[i] * billCount[i];
                    cout << denominations[i] << "               " << billCount << "               " << sum;
                    totalCash =+ sum;
                    break;
                }
            
            case 'B':
            case 'b':
                cout << " USER ACCOUNT MANAGEMENT " << endl;
                cout << endl;
                int useracc_choice;
                string new_cardNumber, new_Pin, new_userBanks, new_accountTypes, new_Balance;
                
                cout << "1 - Create Account\n";
                cout << "2 - View All Account\n";
                cout << "3 - Delete Account\n";
                cout << "4 - Reset PIN\n";
                cin >> useracc_choice;
                
                if (useracc_choice == 1) 
                {
                    cout << "Card Number: ";
                    cin >> new_cardNumber;
                    cardNumbers.push_back(new_cardNumber);
                    
                    cout << "PIN: ";
                    cin >> new_Pin;
                    encodedPINs.push_back(new_Pin);
                    
                    cout << "Bank: ";
                    cin >> new_userBanks;
                    userBanks.push_back(new_userBanks);
                    
                    cout << "Account Type: ";
                    cin >> new_accountTypes;
                    accountTypes.push_back(new_accountTypes);
                    
                    cout << "Initial Balance: ";
                    cin >> new_Balance;
                    balances.push_back(new_Balance);
                    
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
                    int cardNo, index;
                    cout << "Delete Account\n\n";
                    
                    cout << "Card Number to delete: ";
                    cin >> cardNo;
                    int index = -1; // Initialize index to -1 (or use size() if unsigned) to indicate "not found"

                    for (int i = 0; i < cardNumbers.size(); ++i) 
                    {
                        if (cardNumbers[i] == cardNo) 
                        {
                            index = i;
                            break; // Stop searching once found
                        }
                    }

                    if (index != -1) 
                    {
                        cardNumbers.erase(index);
                        encodedPINs.erase(index);
                        userBanks.erase(index);
                        accountTypes.erase(index);
                        balances.erase(index);
                    } 
                        else 
                        {
                            std::cout << "Card No. " << index << " not found." << endl;
                        }
                }
                            else if (useracc_choice == 4) 
                            {
                                int cardNo, index;
                                cout << "Reset Pin\n\n";
                                
                                cout << "Card Number: ";
                                cin >> cardNo;
                                int index = -1; // Initialize index to -1 (or use size() if unsigned) to indicate "not found"
                                
                                for (int i = 0; i < cardNumbers.size(); ++i) 
                                {
                                    if (cardNumbers[i] == cardNo) 
                                    {
                                        index = i;
                                        break; // Stop searching once found
                                    }
                                }
                                
                                cout << "New PIN: ";
                                cin >> n;
                                
                                PIN.at(index) == n;
                                
                            }
            break;
                
            case 'C': 
            case 'c':
                string newPassword, currentPassword, change;
                
                cout << " ADMIN CREDENTIAL MANAGEMENT \n\n" << endl;
                cout << "Do you want to change passcode? (yes/no)"
                cout << change;
                
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
                            ADMIN_PASSCODE = newPassword;
                            cout << "Password Changed Successfully.";
                    }
                    else {
                        cout << "Wrong Password.";
                    }
                }
                
                int view;
                cout << "1 - View Admin List";
                cin >> view;
                
                if (view == 1) {
                    for (int i = 0; i < 3; i++) {
                        cout << adminID[i] << "         " << adminName[i]; //make vector for adminID and adminName
                    }
                }
                
                break;
                
            case 'D':
            case 'd':
                time_t now = time(0);
                tm* localTime = localtime(&now);
            
                // Check if current time is between 8:00 and 8:15
                if (localTime->tm_hour != 8 || localTime->tm_min > 15) {
                    cout << "Refill allowed only from 8:00 AM to 8:15 AM." << endl;
                    return;
                }
            
                // Refill bills
                billCount[0] += 50; // Add 50 bills of the first denomination
                cout << "Refill successful." << endl;
                break;
            
            case 'E':
            case 'e':
                cout << "Exiting Admin System";
                
            default:
                cout << "Invalid.";
                continue;
        } //switch menu end
        
        return;
        
    } //while menu end

    return 0;
    
} //exit
