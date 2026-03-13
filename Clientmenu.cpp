
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
cout << "Date: " << t->tm_mon + 1 << "/" << t->tm_mday << "/" << t->tm_year + 1900 << endl; 
cout << "Time: " << t->tm_hour << ":" << t->tm_min << endl; 
cout << "Bamks: " << userBanks[accountIndex] << endl; 
cout << "Account Type: " << accountTypes[accountIndex] << endl; 
cout << "Current Balance (PHP): " << balances[accountIndex] << endl; 

cout << "=== CLIENT MENU ===" << endl; 
cout << "1. Check Balance" << endl; 
cout << "2. Withdraw" << endl; 
cout << "3. Transfer" << endl; 
cout << "4. Transaction History" << endl; 
cout << "5. Change Pin" << endl; 
cout << "6. LOGOUT" << endl; 

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
