
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
    vector<int> transactionQuantities; 
       
    while (true) 
    {
        int role = login();  // No parameters needed

        if (role == 1)
        {
            clientMenu
                        (
                            cardNumbers, 
                            encodedPINs, 
                            balances, 
                            userBanks, 
                            accountTypes, 
                            transactionTypes, 
                            transactionAmounts, 
                            transactionFees,  
                            transactionQuantities
                        ); 
                       
        } 
            else if (role == 2) 
            {
                adminMenu
                        ( 
                            cardNumbers,
                            balances,
                            ADMIN_PASSCODE, 
                            userBanks, 
                            encodedPINs, 
                            accountTypes, 
                            NUM_DENOMINATIONS, 
                            denominations,
                            billCount
                        );  // Pass by reference
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

void clientMenu 
               (vector<string>& cardNumbers, vector<string>& encodedPINs, vector<double>& balances, 
               vector<string>& usersBank, vector<string>& accountTypes, vector<string>& transactionTypes, 
               vector<double>& transactionAmounts, vector<double>& transactionFees, vector<int>& transactionQuantities)  
{ 

string cardNum;
string pin; 
int accountIndex = -1; 

  cout << "Enter your card number: "; 
  cin >> cardNum; 

  for (int i = 0; i < cardNumbers.size(); i++) { 
  if(cardNumbers[i] == cardNum) { 
  accountIndex = i; 
  break; 
  } 
} 
  if (accountIndex == -1) { 
    cout << "Card not found"; 
    return; 
} 

  cout << "Please Enter Your PIN:"; 
  cin >> pin; 

  if(encodeString(pin) != encodedPINs[accountIndex]) { 
    cout << "Incorrect PIN, sorry" << endl; 
    
  return; 
} 

  int choice;  

do { 

    time_t now = time(0); 
    tm* timeinfo = locatltime(&now);
   
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

  cout << "Enter choice: " << endl; 
  cin >> choice; 
    
  if(choice == 1) { 
    cout << "Your Balance is: (PHP) " << balances[accountIndex] << endl;

} 
  else if (choice == 2) 
{ 

int opt; 
double amount = 0; 
int customAmount; 
   
  cout << "=== WITHDRAW ===" << endl; 
  cout << "1. Withdraw 100" << endl; 
  cout << "2. Withdraw 500" << endl; 
  cout << "3. Withdraw 1000" << endl; 
  cout << "4. Withdraw 5000" << endl; 
  cout << "5. Enter other amount" << endl; 
  cout << "Choice: " << endl; 
  cin >> opt; 

if(opt == 1){ 
  amount = 100;
} 
else if(opt == 2){ 
  amount = 500;
} 
else if(opt == 3){  
  amount = 1000;
} 
else if(opt == 4){ 
  amount = 5000;
} 
else if(opt == 5) { 
    cout << "Enter Amount: " << endl; 
    cin >> customAmount;
    amount = customAmount; 
  } 

  if (amount <= 0) { 
    cout << "Amount Invalid" << endl;
    continue; 
  } 

  if (amount > balances[accountIndex]) { 
     cout << "You don't have enough balance on your account" << endl; 
     continue; 
  } 
   
  double fee = 20; 

  if(balances[accountIndex] >= amount + fee) 
  { 
     balances[accountIndex] -= (amount + fee); 

    cout << "The withdraw is successfull"<< endl; 
    bool found = false; 
  
  for(int i = 0; i < transactionTypes.size(); i++) { 
      if(transactionTypes[i] == "Withdraw" && 
        transactionAmounts[i] == amount && 
        transactionFees[i] == fee) { 
         
        transactionQuantities[i]++; 
        found = true; 
        break; 
      } 
    } 
  if(!found) { 
     
    transactionTypes.push_back("Withdraw"); 
    transactionAmounts.push_back(amount); 
    transactionFees.push_back(fee); 
    transactionQuantities.push_back(1); 
    } 
     
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
    cout << "Recipient not found" << endl; 
  } 
  else 
  { 
    cout << "Enter Amount: " << endl; 
    cin >> amount; 

  if (amount <= 0) 
  { 
    cout << "Amount Invalid";  
    continue; 
  }  

  if (amount > balances[accountIndex]) { 
     cout << "You don't have enough balance on your account"; 
     continue; 
  } 
     
    double fee = 20; 

    if(balances[accountIndex] >= amount + fee) { 
    balances[accountIndex] -= (amount + fee); 
    balances[receiverIndex] += amount; 

    cout << "Transfer Successful. Thank you! " << endl; 
    bool  found = false; 

      for(int i = 0; i < transactionTypes.size(); i++) 
        { 
          if(transactionTypes[i] == "Transfer" && 
            transactionAmounts[i] == amount && 
            transactionFees[i] == fee) 
          { 
            transactionQuantities[i]++; 
            found = true; 
            break; 
          } 
         }
      
      if(!found)
      { 
        transactionTypes.push_back("Transfer"); 
        transactionAmounts.push_back(amount); 
        transactionFees.push_back(fee); 
        transactionQuantities.push_back(1); 
      } 
    } 
else 
      { 
    cout << "Not Enough Balance, Sorry" << endl; 
    } 
  } 
}

else if (choice == 4) 
{ 
    cout << "=== TRANSACTION HISTORY === " << endl; 

    for(int i = 0; i < transactionTypes.size(); i++) 
      { 
        cout << transactionTypes[i] << " | "
          << transactionAmounts[i] << " | "
          << transactionFees[i] << " | "
          << "QTY: " << transactionQuantities[i] << endl; 
  } 
} 

else if(choice == 5) { 
    string oldPin, newPin; 

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
  } while (choice != 6); 
} 

// Admin operations (pass by reference)
void adminMenu (vector<string>& cardNumbers,
               vector<double>& balances,
               string& ADMIN_PASSCODE, vector<string>& userBanks, 
               vector<string>& encodedPINs, vector<string>& accountTypes, 
               const int NUM_DENOMINATIONS, int denominations[], int billCount[]
               /*, ... other vectors if needed */)
{
    //Admin Authentication
    int attempt = 0;
    string encoded_pw;
    while (attempt < 3)
    {
        cout << "Enter Admin Password: ";
        cin >> encoded_pw;
        
        if (encoded_pw == ADMIN_PASSCODE) {
            cout << "Login Successful.";
            continue;
        }
        else {
            cout << "Password Wrong.";
            attempt++;
        }
    }
    
    if (attempt == 3)
    {
        return ;
    }
    
    //Admin Menu
    bool Menu = true;
    while (Menu) {
        int choice;
        std::cout << "------------------------" << endl;
        std::cout << "      ADMIN MENU" << endl;
        std::cout << "------------------------" << endl;
        
        std::cout << "(A) Cash Management" << endl;
        std::cout << "(B) User Account Management" << endl;
       std::cout << "(C) Admin Credential Management" << endl;
        std::cout << "(D) Machine Refilling" << endl;
        std::cout << "(E) Exit" << endl;
        std::cin >> choice;
        
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
        // Declare adminID and adminName vectors
        vector<string> adminID = {"A001", "A002", "A003"};
        vector<string> adminName = {"Alice", "Bob", "Charlie"};

        switch (choice) 
        {

            //Cash Management
            case 'A':
            case 'a':
                std::cout << " CASH MANAGEMENT " << endl;
                totalCash = 0;
                for (int i = 0; i < NUM_DENOMINATIONS; i++) 
                {
                    sum = denominations[i] * billCount[i];
                    cout << denominations[i] << "               " << billCount[i] << "               " << sum << endl;
                    totalCash += sum;
                }
                break;

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
                        cout << adminID[i] << "         " << adminName[i]; //make vector for adminID and adminName
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
            
            //EXIT
            case 'E':
            case 'e':
                cout << "Exiting Admin System";
            break;
                
            default:
                cout << "Invalid.";
                continue;
        } //switch menu end
        
        return;
        
    } //while menu end

    
    
} //exit

void logTransaction(const string& cardNum,
                    const string& type,
                    double amount);

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
