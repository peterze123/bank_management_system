#include <string>
#include "Transaction.h"
using namespace std;

// constructor
Transaction::Transaction(string op, float a){
    // set date of transaction
    // based on local time rather than UTC time
    time_t now = time(0);
    this->date = ctime(&now);
    // determining type of transaction
    if("withdraw" == op){
        this->type = 0;
    }
    else{
        this->type = 1;
    }
    // amount
    this->amount = a;
};

//destructor
Transaction::~Transaction(){
}

// getters
double Transaction::getAmount(){
    return this->amount;
}

string Transaction::getType(){
    if(this->type == 0){
        return "withdraw";
    }
    else{
        return "deposit";
    }
}

string Transaction::getDate(){
    return this->date;
}