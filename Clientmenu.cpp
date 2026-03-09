
void clientMenu (vector<string>& cardNumbers, 
                 vector<string>& encodedPINs, 
                 vector<double>& balance, 
                 vector<string>& optionsBank, 
                 vector<string>& typeAccount, 
                 vector<string>& typeTransaction, 
                 vector<double>& transcationAmounts, 
                 vector<double>& transactionFees, 
                 vector<string>& transactionDates, 
                 vector<string>& transactionTimes)  
{ 
string cardNum;
string pin
int accountIndex = -1; 

// To find card, if accountIndex == -1. Card not found

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

// Entering of Pin 

cout << "Please Enter Your PIN:"; 
cin >> pin; 


