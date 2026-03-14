
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
// Parallel vectors - keep in sync!


vector<string> encodedPINs;     
// Encoded passwords


vector<double> balances;        
// Account balances


vector<string> userBanks;        
// Which bank


vector<string> accountTypes;    
// "Local" or "International"



// For each account's transaction history
vector<string> transactionTypes;    


// "Withdrawal", "Deposit", "Transfer"
vector<double> transactionAmounts;
vector<double> transactionFees;
vector<int> transactionQuantities;  




int main()
{
   // Declare shared vectors ONCE here
    vector<string> cardNumbers;
    vector<string> encodedPINs;
    vector<double> balances;
    vector<string> userBanks; 
    vector<string> accountTypes; 
    vector<string> transactionTypes; 
    vector<double> transactionAmounts; 
    vector<double> transactionFees; 
    vector<string> transactionDates; 
    vector<string> transactionTimes; 
       
    while (true) {
        int role = login();  // No parameters needed

        if (role == 1)
        {
            clientMenu(cardNumbers, encodedPINs, balances, userBanks, 
               accountTypes, transactionTypes, transactionAmounts, 
               transactionFees, transactionDates, transactionTimes); 
                       
        } 
            else if (role == 2) 
            {
                adminMenu(cardNumbers, encodedPINs, balances
                      /*, ... other vectors */);  // Pass by reference
            }
    }



    return 0;
}
//functions

//function 1
int login() 
{
   int role;
   string passcode;
   

   std::cout << "[1] User   [2] Admin   [3] Shutdown\n";
   std::cout << "Enter choice: ";
   std::cin >> role;

   
    if(role == 2) 
    {
        std::cout << "Enter Admin Passcode: ";
        std::cin >> passcode;
        if(passcode != ADMIN_PASSCODE) return 0; // invalid
    }
    return role;  // 1, 2, or 3
    
}
//function 2
void displaymenu(const vector<string>& items,
                 const vector<double>& prices)
{
    cout << "=============================\n";
    cout << "          BPI ATM BANK\n";
    cout << "=============================\n\n";
   
}
// Client operations (pass by reference)

void clientMenu (vector<string>& cardNumbers, vector<string>& encodedPINs, vector<double>& balances, 
vector<string>& usersBank, vector<string>& accountTypes, vector<string>& typeTransaction, 
vector<double>& transcationAmounts, vector<double>& transactionFees, vector<string>& transactionDates, 
vector<string>& transactionTimes)  
{ 
string cardNum;
string pin
int accountIndex = -1; 

cout << "Enter your card number: "; 
cin >> cardNumbers; 

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
  cout << "Card not found"; 
  return; 
} 

cout << "Please Enter Your PIN:"; 
cin >> pin; 

if(encodeString(pin) != encodedPINs[accountIndex]) 
{ 
     cout << "Incorrect PIN, sorry"; 
   return; 
} 

int choice = 0; 

while choice(choice != 6) 
{ 

  time_t now = time(0); 
  tm* timeinfo = localtime(&now); 

cout << "===================" << endl; 
cout << "Date: " << timeinfo->tm_mon + 1 << "/" << timeinfo->tm_mday << "/" << timeinfo->tm_year + 1900 << endl;  
cout << "Time: " << timeinfo->tm_hour << ":" << timeinfo->tm_min << endl; 
cout << "Bank: " << usersBank[accountIndex] << endl; 
cout << "Account Type: " << accountTypes[accountIndex] << endl; 
cout << "Current Balance (PHP): " << balances[accountIndex] << endl;

cout << "=== CLIENT MENU ===" << endl; 
cout << "1. Check Balance" << endl; 
cout << "2. Withdraw" << endl; 
cout << "3. Transfer" << endl; 
cout << "4. Transaction History" << endl; 
cout << "5. Change Pin" << endl; 
cout << "6. LOGOUT" << endl; 

cout << "Enter your choice: " << endl; 
cin >> choice; 

if(choice == 1) 
{ 
  cout << "Your Balance is: (PHP) " << balances[accountIndex] << endl; 
} 
else if (choice == 2) 
{ 

  int opt; 
  double amount; 

cout << "1. Withdraw 100" << endl; 
cout << "2. Withdraw 500" << endl; 
cout << "3. Withdraw 1000" << endl; 
cout << "4. Withdraw 5000" << endl; 
cout << "Choice: " << endl; 
cin >> opt; 

if(opt == 1) 
  amount = 100; 
else if(opt == 2) 
  amount = 500; 
else if(opt == 3) 
  amount = 1000; 
else if(opt == 4)
  amount = 5000; 
else 
{ 
  cout << "Enter Amount: " << endl; 
  cin >> amount; 
} 

if(amount <= 0) { 
   cout << "Amount Invalid" << endl; 
   continue ; 
} 

double fee = 20; 

if(balances[accountIndex] >= amount + fee) { 
     balances[accountIndex] -= (amount + fee); 

  int b5000 = 0;
  int b1000 = 0; 
  int b500 = 0; 
  int b100 = 0; 

    calculateBills(amount, b5000, b1000, b500, b100); 

  cout << "=== RECEIPT ==="<< endl; 
  cout << "Amount: " << amount << endl; 
  cout << "Fee: " << fee << endl; 
  cout << "5000 bills: " << b5000 << endl; 
  cout << "1000 bills: " << b1000 << endl; 
  cout << "500 bills: " << b500 << endl; 
  cout << "100 bills: " << b100 << endl; 

  transactionTypes.push_back("Withdraw"); 
  transactionAmounts.push_back(amount); 
  transactionFees.push_back(fee); 
  transactionTimes.push_back("recent"); 
} 
  else
{ 
  cout << "Not Enough Balance, Sorry" << endl; 
} 
  } 
  else if (choice == 3) { 
    string receiver; 
    double amount; 

    cout << "Enter Recipient Card Number: "; 
    cin >> receiver; 

  int receiverIndex = -1;

  for(int i = 0; i < cardNumbers.size(); i++) { 
    if(cardNumbers[i] == receiver) { 
      receiverIndex = i; 
    break; 
    } 
  } 

  if(receiverIndex == -1) { 
    cout << "Recepient not found" << endl; 
  } 
  else { 
    cout << "Enter Amount: " << endl; 
    cin >> amount; 

  if (amount <= 0) { 
    cout << "Amount Invalid";  
    continue; 
  }  

      
    double fee = 20; 

    if(balances[accountIndex] >= amount + fee) { 
    balances[accountIndex] -= (amount + fee); 
    balances[receiverIndex] += amount; 

    cout << "Transfer Successful. Thank you! " << endl; 

    transactionTypes.push_back("Transfer"); 
    transactionAmounts.push_back(amount);
    transactionFees.push_back(fee); 
    transactionTimes.push_back("recent"); 
  }
      
else { 
  cout << "Not Enough Balance, Sorry" << endl; 
} 
  } 
    }

else if (choice == 4) { 
    cout << "=== TRANSACTION HISTORY === "; 

int start = 0; 

    if(transactionTypes.size() > 10) 
      start = transactionTypes.size() - 10; 
    for(int i = start; i < transactionTypes.size(); i++) { 
    cout << transactionTypes[i] << " | "   
     << transactionAmounts[i] << " | "   
     << transactionFees[i] << " | "  
     << transactionTimes[i] << " | " << endl; 
      
  } 
} 

else if(choice == 5) { 
    string oldPin; 
    string newPin; 

    cout << "Enter Old Pin: " << endl; 
    cin >> oldPin; 

    if(encodeString(oldPin) == encodedPINs[accountIndex]) { 
      cout << "Enter New Pin: " << endl; 
      cin >> newPin; 

      if(newPin != oldPin) { 
      encodedPINs[accountIndex] = encodeString(newPin); 
      cout << "PIN has been changed successfully! " << endl; 
    } 
      else { 
      cout << "PIN is the same. Please enter new pin. " << endl; 
    } 
  } 
  else { 
    cout << "Old pin incorrect" << endl; 
  } 
} 
  else if (choice == 6)  { 
      cout << "Logging out. Thank you! " << endl; 
    } 
  } 
} 

// Admin operations (pass by reference)
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

void logTransaction(const string& cardNum,
                    const string& type,
                    double amount)
{

}

// Display current date and time
void displayDateTime() {
    time_t now = time(0);
    tm* timeinfo = localtime(&now);

    cout << "Date: " << (timeinfo->tm_mon + 1) << "/"
         << timeinfo->tm_mday << "/"
         << (timeinfo->tm_year + 1900);
    cout << " Time: " << timeinfo->tm_hour << ":"
         << timeinfo->tm_min << endl;
}
