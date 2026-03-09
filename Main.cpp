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
    // ... more vectors ...

    while (true) {
        int role = login();  // No parameters needed

        if (role == 1)
        {
            clientMenu(cardNumbers, encodedPINs, balances
                       /*, ... other vectors */);  // Pass by reference
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
void clientMenu(vector<string>& cardNumbers,
                vector<string>& pins,
                vector<double>& balances
                /*, ... other vectors if needed */)
{


}

// Admin operations (pass by reference)
void adminMenu(vector<string>& cardNumbers,
               vector<double>& balances,
               string& adminPasscode
               /*, ... other vectors if needed */)
{



}
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



