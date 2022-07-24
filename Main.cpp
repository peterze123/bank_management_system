#include <iostream>
#include <string>
#include <cstdio>
#include <cctype>
#include "Account.h"
using namespace std;

/**
 * @brief Printing the header
 * 
 * @param option 
 * @return int 
 */
int headerPrint(int option){
    cout<<"\n";
    string header = "Main Window";
    string res = "";
    switch(option){
            case 1:
                header += " --> Show Balance";
                break;
            case 2:
                header += " --> Deposit(Enter the following information)";
                break;
            case 3:
                header += " --> Withdraw(Enter the following information)";
                break;
            case 4:
                header += " --> Show All Transaction";
                break;
            default:
                break;
    }
    res += header;
    res += "\n";
    for(int i = 0; i < header.length(); i++) {
        res += "=";
    }
    // give the length of the taielr
    cout << res << endl;
    return header.length();
}

/**
 * @brief Print the tail 
 * 
 */
void tailer(int length, string str){
    string res = "\n";
    for(int i = 0; i < length; i++) {
        res += "-";
    }
    res += "\n";
    // outputing
    res += str;
    res += "Press enter to go back to the Main Window\n";
    cout << res;
    // return with enter
    string tmp;
    tmp = cin.get();
    cin.ignore();
}

/**
 * @brief The Login Window
 * 
 * @param bank 
 * @return Account* 
 */
Account* startingInit(Account** bank){
    // The main menu
    headerPrint(0);
    cout << "Enter Your Account no: ";
    // error handling for non-numeric inputs 
    int acctNo;
    if (!(cin >> acctNo)){
        cin.clear();
        // ignoring the last line inputted, cites to stackoverflow
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        acctNo = 0;
    }
    // string could take any char
    string pass;
    cout << "Enter Your Password: ";
    cin >> pass;
    // validating does the account exist then returning the index of the account
    // please note that account number starts with 1 rather than 0
    for(int i = 0; i < 10; i++){
        if(pass == bank[i]->getPassword() && acctNo == bank[i]->getAcctNumber()){
            return bank[i];
        }
    }
    // if nothing found
    return NULL;
}

/**
 * @brief printing the main window
 * 
 * @return int 
 */
int selectionInit(){
    headerPrint(0);
    string output = "";
    output += "choose one of the following options: \n";
    output += "(1) Show balance \n";
    output += "(2) Desposit \n";
    output += "(3) Withdraw \n";
    output += "(4) Show All Transactions \n";
    output += "(5) Quit to Login Window \n";
    output += "Enter your choice: ";
    cout << output;
    // error handling for option
    int option;
    if (!(cin >> option)){
        cin.clear();
        // ignoring the last line inputted, cites to stackoverflow
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        option = 0;
    }
    return option;
}

/**
 * @brief showing the current balance
 * 
 * @param acct 
 */
void showBalance(Account* acct){
    int length = headerPrint(1);
    string output = "Your current balance is: $";
    // add tail
    cout << output;
    printf("%0.2lf", acct->getBalance());
    cout << endl;
    tailer(length,"");
}

/**
 * @brief helper method for withdraw and deposit to check if input is number
 * 
 * @param line 
 * @return int 
 */
int isNumeric(string line){
    for(int i = 0; i < line.length(); i++){
        if(isdigit(line[i]) == false && line[i] != '.'){
            return 0;
        }
    }
    return 1;
}

/**
 * @brief adding cash to the account
 * 
 * @param acct 
 */
void deposit(Account* acct){
    int length = headerPrint(2);
    cout<<"The amount you want to deposit: ";
    // inputing the amount
    // inputing as string and converting later because double could hold chars as well
    string in = "";
    if (!(cin >> in)){
        cin.clear();
        // ignoring the last line inputted, cites to stackoverflow
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // check if the amount is valid
    // since double could take in characters, check if it is a number
    double adder = -1;
    if(isNumeric(in)){ 
        try{
            adder = stof(in);
        }catch(exception &err){
            adder = -1;
        }
    }
    // check if positive
    if(adder < 0){
        tailer(length,"The transaction was not successful, please enter a positive numeric value! ");
    }
    else{   
        acct->addTrans(new Transaction("deposit", adder));
        tailer(length,"Well done, this was added to your balance successfully... ");
    }
}

/**
 * @brief withdrawing cash from account
 * 
 * @param acct 
 */
void withdraw(Account* acct){
    int length = headerPrint(3);
    cout<<"The amount you want to withdraw: ";
    // inputing the amount
    // inputing as string and converting later because double could hold chars as well
    string in = "";
    if (!(cin >> in)){
        cin.clear();
        // ignoring the last line inputted, cites to stackoverflow
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // check if the amount is valid
    // since double could take in characters, check if it is a number
    double with = -1;
    if(isNumeric(in)){ 
        try{
            with = stof(in);
        }catch(exception &err){
            with = -1;
        }
    }
    // check if positive
    if(with < 0){
        tailer(length,"The transactionw was not successful, please enter a positive numeric value! ");
    }
    else if (with > acct->getBalance()){
        tailer(length,"The transactionw was not successful, please enter value smaller than your balance! ");
    }
    else{   
        acct->addTrans(new Transaction("withdraw", with));
        tailer(length,"Please take your money then... ");
    }
}

/**
 * @brief displaying the transactions
 * 
 * @param acct 
 */
void displayTrans(Account* acct){
    int length = headerPrint(4);
    cout << endl;
    cout <<  "Account no: " << to_string(acct->getAcctNumber()) << endl;
    // hodler for max-length
    int dateLen = 4; // length for "date"
    int typeLen = 8; // the longest possible string is withdraw with 7 spaces 
    int amountLen = 6; // length for "amount"
    // finding the max-length for date
    for(int i = 0; i < acct->getTransCount(); i++){
        //date
        int cDate = acct->getTrans()[i]->getDate().length();
        if(cDate > dateLen){
            dateLen = cDate;
        }
        // amount 
        int cAmount = to_string(acct->getTrans()[i]->getAmount()).length();
        if(cAmount > amountLen){
            amountLen = cAmount;
        } 
    }
    //
    string dateForm = "|%-" + to_string(dateLen) + "s ";
    //
    string typeForm = "|%-" + to_string(typeLen) + "s ";
    //
    string amountFormHeader = "|%-" + to_string(amountLen) + "s ";
    //
    string amountForm = "|%-" + to_string(amountLen) + "0.2lf ";
    // displaying header
    for(int i = 0; i < dateLen + typeLen + amountLen + 5; i++){
        cout << "-";
    }
    cout<<endl;
    printf(dateForm.c_str(), "Date");
    printf(typeForm.c_str(), "Type");
    printf(amountFormHeader.c_str(), "Amount");
    cout<<endl;
    for(int i = 0; i < dateLen + typeLen + amountLen  + 5; i++){
        cout << "-";
    }
    cout<<endl;
    // displaying contents
    for(int i = 0; i < acct->getTransCount(); i++){
        string date = acct->getTrans()[i]->getDate();
        date.erase(remove(date.begin(), date.end(), '\n'),date.end());
        printf(dateForm.c_str(), date.c_str());
        printf(typeForm.c_str(), acct->getTrans()[i]->getType().c_str());
        printf(amountForm.c_str(), acct->getTrans()[i]->getAmount());
        cout << endl;
    } 
    // footer
    for(int i = 0; i < dateLen + typeLen + amountLen  + 5; i++){
        cout << "-";
    }
    //
    tailer(0, "");
}

/**
 * @brief the main Function
 * 
 * @return int 
 */
int main(){
    // public array of acocunts
    Account** bank = new Account*[10];
    // initializng each a   ccount
    for(int i = 0; i < 10; i++){
        string password = "12345";
        double amount = 5000.0;
        bank[i] = new Account(password, amount);
    }
    // Initializing the main window and loging into the account
    // repeat if wrong 
    while(true){
        Account* acct;
        while(true){
            acct = startingInit(bank);
            if(acct != NULL){
                break;
            }
            else{
                cout<<"Please enter a valid account account!\n";
            }
        }
        // access the account, 4 options page
        // main function
        while(true){
            int option = selectionInit();
            if(option == 1 || option == 2 || option == 3 || option == 4 || option == 5){
                if(option == 1){
                    showBalance(acct);
                }
                else if(option == 2){
                    deposit(acct);
                }
                else if(option == 3){
                    withdraw(acct);
                }
                else if(option == 4){
                    displayTrans(acct);
                }
                else{
                    break;
                }
            }
            else{
                cout<<"Please enter a valid option!\n";
            }
        }
    }
    delete [] bank;
}