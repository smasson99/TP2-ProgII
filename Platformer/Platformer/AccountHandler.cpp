#include "AccountHandler.h"

using namespace platformer;

AccountHandler* AccountHandler::instance = nullptr;

AccountHandler::AccountHandler()
{

}

AccountHandler* AccountHandler::GetInstance()
{
    if (instance == nullptr)
        instance = new AccountHandler();
    return instance;
}

bool AccountHandler::validerAccount(string username, string password)
{
    bool isOk = false;
    {
        ifstream iFich(accountPath);
        string line;
        while (getline(iFich, line))
        {
            stringstream l(line);
            string user, pass;
            l >> user >> pass;
            if (user == username && pass == password)
            {
                isOk = true;
                break;
            }
        }
    }
    return isOk;
}