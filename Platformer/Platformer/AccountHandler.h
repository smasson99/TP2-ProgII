#pragma once
// <smasson>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

namespace platformer
{
    class AccountHandler
    {
    public:
        static AccountHandler* GetInstance();
        bool validerAccount(string username, string password);
    private:
        AccountHandler();
        static AccountHandler* instance;
        const string accountPath = "Ressources\\Other\\accounts.txt";
    };
}
// </smasson>