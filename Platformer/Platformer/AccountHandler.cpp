#include "AccountHandler.h"

using namespace platformer;
static string user;
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
// <SBerube>
int AccountHandler::newAccount(const string username, const string password, const string fName, const string lName, const string email) const
{
	// Vérification des champs obligatoirs
	if (username.size() == 0 || password.size() == 0 || fName.size() == 0 || lName.size() == 0 || email.size() == 0)
	{
		// les champs obligatoirs ne sont pas tous remplis.
		return Errorcode::NO_INPUT;
	}

	// Vérification du username
	if (username.size() < 3 || username.size() > 25)
	{
		// Username est trop court ou trop long.
		return Errorcode::UNAME_SIZE;
	}
	else
	{
		// On doit aller lire les usernames existants.
		{
			ifstream iFich(accountPath);
			string line;
			while (getline(iFich, line))
			{
				stringstream l(line);
				string user, trash;
				l >> user >> trash;
				if (user == username)
				{
					// username déjà occupé
					return Errorcode::UNAME_TAKEN;
				}
			}
		}
	}

	// Vérification du mot de passe.
	bool containsLower = false;
	bool containsCap = false;
	bool containsSpecial = false;
	if (password.size() < 5 || username.size() > 15)
	{
		// password est trop court ou trop long.
		return Errorcode::PWORD_SIZE;
	}
	for (size_t i = 0; i < password.size(); i++)
	{
		if (isupper(password.at(i)))
		{
			containsCap = true;
		}
		else if (islower(password.at(i)))
		{
			containsLower = true;
		}
		else if (!isalnum(password.at(i)))
		{
			containsSpecial = true;
		}
	}
	if (!containsCap || !containsLower || !containsSpecial)
	{
		// Password incomplet (1 minuscule, 1 majuscule et un charactère spécial)
		return Errorcode::PWORD_INCOMPLETED;
	}

	// Vérification du prénom
	if (fName.size() < 2 || fName.size() > 25)
	{
		// le prénom est d'une mauvaise taille
		return Errorcode::FNAME_SIZE;
	}
	for (size_t i = 0; i < fName.size(); i++)
	{
		if (!isalpha(fName.at(i)) && fName.at(i) != '.' && fName.at(i) != '-')
		{
			// Le prénom est invalide
			return Errorcode::FNAME_INVALID;
		}
	}

	// Vérification du nom
	if (lName.size() < 2 || lName.size() > 25)
	{
		// le nom est d'une mauvaise taille
		return Errorcode::LNAME_SIZE;
	}
	for (size_t i = 0; i < lName.size(); i++)
	{
		if (!isalpha(lName.at(i)) && lName.at(i) != '.' && lName.at(i) != '-')
		{
			// Le nom est invalide
			return Errorcode::LNAME_INVALID;
		}
	}

	// Vérification du email
	if (!validerAddresseCourriel(email))
	{
		// email invalide
		return Errorcode::EMAIL_INVALID;
	}


	// OK, les tests ont tous passé.
	return Errorcode::OK;
}
bool AccountHandler::validerAddresseCourriel(const string addresseCourriel) const
{
	bool pointFound = false;
	string prefix;
	string sufix;
	string domaine;
	prefix = addresseCourriel.substr(0, addresseCourriel.find_last_of('@'));
	domaine = addresseCourriel.substr(addresseCourriel.find_last_of('.') + 1, addresseCourriel.length() - addresseCourriel.find_last_of('.'));
	sufix = addresseCourriel.substr(addresseCourriel.find_last_of('@') + 1, (addresseCourriel.length() - prefix.length() - domaine.length() - 2));
	if (prefix == "" || sufix == "" || domaine == "")
	{
		return false;
	}
	if (domaine.length() > 3)
	{
		return false;
	}
	for (size_t i = 0; i < prefix.length(); i++)
	{
		if (!isalnum(prefix.at(i)) && prefix.at(i) != '_' && prefix.at(i) != '-')
		{
			return false;
		}
	}
	for (size_t i = 0; i < sufix.length(); i++)
	{
		if (!isalnum(sufix.at(i)) && sufix.at(i) != '_' && sufix.at(i) != '-' && sufix.at(i) != '.')
		{
			return false;
		}
	}
	for (size_t i = 0; i < domaine.length(); i++)
	{
		if (!isalnum(domaine.at(i)) && domaine.at(i) != '_' && domaine.at(i) != '-')
		{
			return false;
		}
	}
	for (size_t i = 0; i < sufix.length() - 1; i++)
	{
		if (sufix.at(i) == '.')
		{
			pointFound = true;
		}
		if (pointFound && sufix.at(i) == '.' && sufix.at(i + 1) != '.')
		{
			pointFound = false;
			return false;
		}
	}
	return true;
}
void AccountHandler::setModVariables(string user)
{
	// On doit aller lire les usernames existants.
	{
		ifstream iFich(accountPath);
		string line;
		while (getline(iFich, line))
		{
			stringstream l(line);
			string username, pass, fname, lname, email;
			l >> username >> pass >> fname >> lname >> email;
			if (username == user)
			{
				this->user = username;
				this->pass = pass;
				this->fName = fname;
				this->lName = lname;
				this->email = email;
			}
		}
	}
}
string AccountHandler::getModVariable(int index)
{
	switch(index)
	{
	case 1:
		return user;
		break;
	case 2:
		return pass;
		break;
	case 3:
		return fName;
		break;
	case 4:
		return lName;
		break;
	case 5:
		return email;
		break;
	}
	return "";
}
// </SBerube>
