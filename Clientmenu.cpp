void clientMenu() {
    string cardNum, pin;
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
        cout << "\nCard not found\n";
        return;
    }

    cout << "Please Enter Your PIN: ";
    cin >> pin;

    if(encodeString(pin) != encodedPINs[accountIndex]) {
        cout << "Incorrect PIN, sorry" << endl;
        return;
    }

    int choice;
    do {
        time_t now = time(0);
        tm* timeinfo = localtime(&now);  
        
        cout << "\n===================\n" << endl;
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
        cin >> choice;
        
        if(choice == 1) {
            cout << "Your Balance is: (PHP) " << balances[accountIndex] << endl;
        }
        else if (choice == 2) {
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
            cin >> opt;

            if(opt == 1) amount = 100;
            else if(opt == 2) amount = 500;
            else if(opt == 3) amount = 1000;
            else if(opt == 4) amount = 5000;
            else if(opt == 5) {
                
                cout << "\n----------\n";
                cout << "Enter Amount: ";
                cin >> customAmount;
                amount = customAmount;
            }

            if (amount <= 0) {
                cout << "Amount Invalid\n\n" << endl;
                continue;
            }

            if (amount > balances[accountIndex]) {
                cout << "\nYou don't have enough balance on your account\n";
                continue;
            }
            
            double fee = 20;
            double totalDeduction = amount + fee;

            if(balances[accountIndex] >= totalDeduction) {
                balances[accountIndex] -= totalDeduction;  // ✅ FIXED: Use totalDeduction
                cout << "\nThe withdrawal was successful\n" << endl;
                
                logTransaction("Withdrawal", amount, fee);  // ✅ FIXED: Correct call
                
                
                bool found = false;
                for(int i = 0; i < (int)transactionTypes.size(); i++) {
                    if(transactionTypes[i] == "Withdrawal") {
                        transactionQuantities[i]++;
                        found = true;
                        break;
                    }
                }
                if(!found) {
                    transactionTypes.push_back("Withdrawal");
                    transactionAmounts.push_back(amount);
                    transactionFees.push_back(fee);
                    transactionQuantities.push_back(1);
                }
            } else {
                cout << "Not Enough Balance, Sorry\n" << endl;
            }
        }
    
        else if (choice == 3) {
            
            string receiver;
            double amount;
            
            cout << "\n=== TRANSFER MONEY ===\n";
            cout << "Enter Recipient Card Number: ";
            cin >> receiver;

            int receiverIndex = -1;
            for(int i = 0; i < (int)cardNumbers.size(); i++) {
                if(cardNumbers[i] == receiver) {
                    receiverIndex = i;
                    break;
                }
            }

            if(receiverIndex == -1) {
                cout << "Recipient not found" << endl;
            } else {
                cout << "Enter Amount: ";
                cin >> amount;

                if (amount <= 0) {
                    cout << "Amount Invalid";
                    continue;
                }

                if (amount > balances[accountIndex]) {
                    cout << "\nYou don't have enough balance on your account";
                    continue;
                }
                
                double fee = 20;
                if(balances[accountIndex] >= amount + fee) {
                    balances[accountIndex] -= (amount + fee);
                    balances[receiverIndex] += amount;
                    logTransaction("Transfer", amount, fee);  // ✅ FIXED
                    
                    cout << "\nTransfer Successful. Thank you! " << endl;
                } else {
                    cout << "\nNot Enough Balance, Sorry" << endl;
                }
            }
        }
        else if (choice == 4) {
            cout << "\n=== TRANSACTION HISTORY ===\n";
            
            if(transactionTypes.empty()) { 
                cout << "No new transactions has occured " << endl; 
            } 
            
            else { 
            for(int i = 0; i < (int)transactionTypes.size(); i++) {
                cout << transactionTypes[i] << " | "
                     << transactionAmounts[i] << " | "
                     << transactionFees[i] << " | "
                     << "QTY: " << transactionQuantities[i] << endl;
            } 
            }
        }
        else if(choice == 5) {
            string oldPin, newPin;
            
            cout << "\n===PIN CHANGE===\n";
            cout << "Enter Old Pin: ";
            cin >> oldPin;

            if(encodeString(oldPin) == encodedPINs[accountIndex]) {
                cout << "Enter New Pin: ";
                cin >> newPin;

                if(newPin != oldPin) {
                    encodedPINs[accountIndex] = encodeString(newPin);
                    cout << "\nPIN has been changed successfully! " << endl;
                } else {
                    cout << "\nPIN is the same. Please enter new pin. " << endl;
                }
            } else {
                cout << "Old pin incorrect" << endl;
            }
        }
        else if (choice == 6) {
            cout <<"\n===LOGOUT===\n"; 
            cout << "Logging out. Thank you! " << endl;
        }
    } while (choice != 6);
}
