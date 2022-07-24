#include <string>
#include <ctime>
using namespace std;

class Transaction
{
    private:
    //local instances
        string date;
        int type;
        double amount;
     
    public:
        // constructor
        Transaction(string op, float a);
        // destructor
        ~Transaction();
        // getter methods, no need for setter
        string getType();
        double getAmount();
        string getDate();

};