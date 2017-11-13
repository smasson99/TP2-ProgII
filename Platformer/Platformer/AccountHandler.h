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
		// <SBerube>
		enum Errorcode
		{
			OK, // 0
			NO_INPUT, // 1
			UNAME_SIZE, // 2
			UNAME_TAKEN, // 3
			PWORD_SIZE, // 4
			PWORD_INCOMPLETED, // 5
			FNAME_SIZE, // 6
			FNAME_INVALID, // 7
			LNAME_SIZE, // 8
			LNAME_INVALID, // 9
			EMAIL_INVALID // 10
		};
		void setModVariables(string user);
		string getModVariable(int index);
		// <S/Berube>
        static AccountHandler* GetInstance();
        bool validerAccount(string username, string password);
		// <SBerube>
		int newAccount(const string username, const string password, const string fName, const string lName, const string email) const;
		bool validerAddresseCourriel(const string addresseCourriel) const;
		// </SBerube>
    private:
		// Variable pour la modification
		string user;
		string pass;
		string fName;
		string lName;
		string email;

        AccountHandler();
        static AccountHandler* instance;
        const string accountPath = "Ressources\\Other\\accounts.txt";
    };
}
// </smasson>