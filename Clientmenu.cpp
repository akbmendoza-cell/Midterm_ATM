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
  double totalDeduction = amount + fee;

  if(balances[accountIndex] >= totalDeduction) 
  { 
     balances[accountIndex] -= totalDeduction; 

     logTransaction(cardNumbers[accountIndex], "Withdrawal", amount, fee); 
 
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
    double totalDeduction = amount + fee;

    
    if(balances[accountIndex] >= totalDeduction) { 
    balances[accountIndex] -= totalDeduction; 
    balances[receiverIndex] += amount; 

    logTransaction(cardNumbers[accountIndex], "Transfer", amount, fee); 
    
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
