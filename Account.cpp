#include <string>
#include <vector>
#include "Account.h"
using namespace std;

//initializing the static variables
int Account::account_no = 1;

// constructor
Account::Account(string password, double initBalance){
    // id increment
    this->acct_no = this->account_no;
    account_no += 1;
    // assign password and balance
    this->transCount = 0;
    this->password = password;
    this->balance = initBalance;
}

//destructor
Account::~Account(){
    for(int i = 0; i < transCount; i++){
        delete(trans[i]);
    }
    this->trans.clear();
}

//getters
int Account::getAcctNumber(){
    return this->acct_no;
}

string Account::getPassword(){
    return this->password;
}

double Account::getBalance(){
    return this->balance;
}

vector<Transaction*> Account::getTrans(){
    return this->trans;
}

int Account::getTransCount(){
    return transCount;
}

//setter for getBalance
void Account::setBalance(double amount){
    this->balance = amount;
}

//
void Account::addTrans(Transaction* t){
    transCount++;
    this->trans.push_back(t);
    // modifying the balance
    if(t->getType() == "withdraw"){
        this->balance -= t->getAmount();
    }
    else{
        this->balance += t->getAmount();
    }
}