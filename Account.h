#include <string>
#include <vector>
#include "Transaction.h"
using namespace std;

class Account
{
    private:
        // transId used to resize the trans array
        static int account_no;

        // local instances
        int transCount;
        int acct_no;
        string password;
        double balance;
        vector<Transaction*> trans;

    public:
        // constructor
        Account(string password, double initBalance);

        //destructor
        ~Account();

        // getter methods
        int getAcctNumber();
        string getPassword();
        double getBalance();
        vector<Transaction*> getTrans();
        int getTransCount();
        //setter for balance
        void setBalance(double amount);
        // add_transaction
        void addTrans(Transaction* t);
};