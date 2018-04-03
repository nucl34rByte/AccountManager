#include "stdafx.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <windows.h>

//	Account's account class. 
//	It stores a main methods and options of an account.
class Account {
public:
	//Statuses enumeration.
	static enum status{
		admin,
		user,
	};

	//Constructors
	Account(){}

	Account(std::string sLogin, std::string sPassword){
		this->sLogin = sLogin;
		this->sPassword = sPassword;
		this->stStatus = user;
	}

	Account(std::string sLogin, std::string sPassword, status stStatus){
		this->sLogin = sLogin;
		this->sPassword = sPassword;
		this->stStatus = stStatus;
	}

	//Metods
	std::string getLogin(){
		return sLogin;
	}
	
	status getStatus(){
		return stStatus;
	}

	bool changePassword(std::string sOldPassword, std::string sNewPassword){
		if (sOldPassword == this->sPassword){
			this->sPassword = sNewPassword;
			return true;
		}
		return false;
	}

	void changePassword(Account &uAccount, std::string sNewPassword){
		if (stStatus == admin){
			uAccount.sPassword = sNewPassword;
		}
	}
	
	void setUserToAdmin(Account &uAccount){
		if (stStatus == admin){
			uAccount.stStatus = admin;
		}
	}

	void setAdminToUser(Account &uAccount){
		if (stStatus == admin){
			uAccount.stStatus = user;
		}
	}

	bool isAuthCorrect(std::string sLogin, std::string sPassword){
		if (sPassword == this->sPassword && sLogin == this->sLogin){
			return true;
		}
		return false;
	}

private:
	//options
	std::string sLogin;
	std::string sPassword;
	status stStatus;
};


// Custom output functions
inline void printInfo(std::string sText){
	std::cout << "[INFO] " << sText << std::endl;
}

inline void printInput(std::string sText){
	std::cout << "[INPUT] " << sText;
}

inline void printOutput(std::string sText){
	std::cout << "[OUTPUT] " << sText << std::endl;
}

inline void printError(std::string sText){
	std::cout << "[ERROR] " << sText << std::endl;
}

// Print banner function
inline void printBanner(){
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "	AAAAA  CCCCC  CCCCC  OOOOO  N   N  TTTTT" << std::endl;
	std::cout << "	A   A  C      C      O   O  NN  N    T  " << std::endl;
	std::cout << "	AAAAA  C      C      O   O  N N N    T  " << std::endl;
	std::cout << "	A   A  C      C      O   O  N  NN    T  " << std::endl;
	std::cout << "	A   A  CCCCC  CCCCC  OOOOO  N   N    T  " << std::endl;

	std::cout << "" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "	M   M  AAAAA  N   N  AAAAA  GGGGG  EEEEE  RRRR " << std::endl;
	std::cout << "	MM MM  A   A  NN  N  A   A  G      E      R   R" << std::endl;
	std::cout << "	M M M  AAAAA  N N N  AAAAA  G      EEEEE  RRRR " << std::endl;
	std::cout << "	M   M  A   A  N  NN  A   A  G  GG  E      R   R" << std::endl;
	std::cout << "	M   M  A   A  N   N  A   A  GGGGG  EEEEE  R   R" << std::endl;

	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
	
	printInfo("Welcome to the program AccountManager.");
	system("pause");
	system("cls");
}

void printMenu(Account::status stStatus){
	if (stStatus == Account::admin){
		std::cout << "" << std::endl;
		std::cout << "Administrator's menu:" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "1) Show the list of accounts." << std::endl;
		std::cout << "2) Create a new account." << std::endl;
		std::cout << "3) Delete an account." << std::endl;
		std::cout << "4) Change account password." << std::endl;
		std::cout << "5) Increase user rights before administrator." << std::endl;
		std::cout << "6) Reduce administrator rights to the user." << std::endl;
		std::cout << "7) Display this menu." << std::endl;
		std::cout << "0) Log out." << std::endl;
		std::cout << "99) Exit the program." << std::endl;
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;
	}
	else{
		std::cout << "" << std::endl;
		std::cout << "User's menu:" << std::endl;
		std::cout << "" << std::endl;
		std::cout << "1) Create a new user." << std::endl;
		std::cout << "2) Delete the current user." << std::endl;
		std::cout << "3) Change the password for the current user." << std::endl;
		std::cout << "4) Display this menu." << std::endl;
		std::cout << "0) Log out." << std::endl;
		std::cout << "99) Exit the program." << std::endl;
		std::cout << "" << std::endl;
		std::cout << "" << std::endl;
	}
}

int main(int argc, char* argv[]){
	setlocale(LC_ALL, "");

	bool isLogout = false;
	int nCurrentID = 0;
	std::string sDefaultLogin = "admin";
	std::string sDefaultPassword = "password";
	std::vector<Account> vAccounts(1);
	vAccounts[0] = Account(sDefaultLogin, sDefaultPassword, Account::admin);

	std::string sName, sPassword, sInput;
	printBanner();

	while (true) {
		do {
			std::cout << "" << std::endl;

			printInfo("Please, log in: ");
			printInput("ID: ");
			std::cin >> sInput;
			try {
				if (sInput.find('-') != std::string::npos){
					throw std::invalid_argument("");
				}
				nCurrentID = stoi(sInput);
			}
			catch (std::invalid_argument) {
				printError("Error! The ID must be an unsigned integer.");
				continue;
			}
			
			printInput("Enter your login: ");
			std::cin >> sName;

			printInput("Enter your password: ");
			std::cin >> sPassword;

			if (nCurrentID >= vAccounts.size()){
				printOutput("Authorisation error!");
			}
			else if (vAccounts[nCurrentID].isAuthCorrect(sName, sPassword)){
				printOutput("Access granted!");
			}
			else {
				printOutput("Authorisation error!");
			}	
		} while (!vAccounts[nCurrentID].isAuthCorrect(sName, sPassword));

		int iChoose;
		printMenu(vAccounts[nCurrentID].getStatus());

		while (true) {
			if (isLogout) {
				isLogout = false;
				break;
			}
			std::cout << "" << std::endl;
			printInput("Your choice: ");

			std::cin >> sInput;
			try{
				iChoose = stoi(sInput);
			}
			catch (std::invalid_argument) {
				printError("Your input is unrecognized.Try again!");
			}

			std::string sOldPassword, sNewPassword;
			int nID;

			if (vAccounts[nCurrentID].getStatus() == Account::admin) {
				switch (iChoose){
				case 1:
					for (int i = 0; i < vAccounts.size(); i++) {
						if (vAccounts[i].getStatus() == Account::admin){
							std::cout << "Status: admin; ";
						}
						else if (vAccounts[i].getStatus() == Account::user){
							std::cout << "Status: user; ";
						}
						std::cout << "ID: " << i << "; Login: " << vAccounts[i].getLogin() << std::endl;
					}
					break;
				case 2:
					printInput("Enter a name for the new user: ");
					std::cin >> sName;
					printInput("Enter the password for the new user: ");
					std::cin >> sPassword;

					vAccounts.push_back(Account(sName, sPassword));
					printOutput("OK!");
					std::cout << "" << std::endl;
					break;
				case 3:
					printInput("Enter account ID: ");
					std::cin >> sInput;

					try {
						if (sInput.find('-') != std::string::npos){
							throw std::invalid_argument("");
						}
						nID = stoi(sInput);
					}
					catch (std::invalid_argument){
						printError("Error! The ID must be an unsigned integer.");
						break;
					}
					if (nID >= vAccounts.size()){
						printError("User with this ID does not exist!");
						break;
					}
					if (nID == 0) {
						printError("Can not remove the root administrator!");
						break;
					}
					if (nID == nCurrentID) {
						isLogout = true;
					}

					vAccounts.erase(vAccounts.begin() + nID);
					printOutput("OK!");
					std::cout << "" << std::endl;
					break;
				case 4:
					printInput("Enter account ID: ");
					std::cin >> sInput;

					try {
						if (sInput.find('-') != std::string::npos){
							throw std::invalid_argument("");
						}
						nID = stoi(sInput);
					}
					catch (std::invalid_argument){
						printError("Error! The ID must be an unsigned integer.");
						break;
					}
					if (nID >= vAccounts.size()){
						printError("Error! User with this ID does not exist.");
						break;
					}
					if ((vAccounts[nID].getStatus() == Account::admin) && (nID != nCurrentID) && (nCurrentID != 0)){
						printError("Error! The password for another administrator can only be changed from the root administrator account or himself.");
						break;
					}

					printInput("Enter a new password: ");
					std::cin >> sNewPassword;

					vAccounts[nCurrentID].changePassword(vAccounts[nID], sNewPassword);
					printOutput("OK!");
					break;
				case 5:
					printInput("Enter account ID: ");
					std::cin >> sInput;

					try {
						if (sInput.find('-') != std::string::npos){
							throw std::invalid_argument("");
						}
						nID = stoi(sInput);
					}
					catch (std::invalid_argument){
						printError("Error! The ID must be an unsigned integer.");
						break;
					}
					if (nID >= vAccounts.size()){
						printError("User with this ID does not exist!");
						break;
					}
					if (vAccounts[nID].getStatus() == Account::admin){
						printError("Error! This account is already has admin rights!");
						break;
					}

					vAccounts[nCurrentID].setUserToAdmin(vAccounts[nID]);
					printOutput("OK!");
					break;
				case 6:
					printInput("Enter user ID: ");
					std::cin >> sInput;

					try {
						if (sInput.find('-') != std::string::npos){
							throw std::invalid_argument("");
						}
						nID = stoi(sInput);
					}
					catch (std::invalid_argument){
						printError("Error! The ID must be an unsigned integer.");
						break;
					}
					if (nID == 0) {
						printError("Error! Root user rights can not be decreased!");
						break;
					}
					if (nID >= vAccounts.size()){
						printError("User with this ID does not exist!");
						break;
					}
					if (vAccounts[nID].getStatus() == Account::user){
						printError("Error! This account is already has user rights!");
						break;
					}
					vAccounts[nCurrentID].setAdminToUser(vAccounts[nID]);
					break;
				case 7:
					printMenu(vAccounts[nCurrentID].getStatus());
					break;
				case 0:
					isLogout = true;
					break;
				case 99:
					printOutput("Bye!");
					return 0;
					break;
				default:
					printError("Your input is unrecognized. Try again!");
					break;
				}
			}
			else {
				switch (iChoose){
				case 1:
					printInput("Enter a name for the new user: ");
					std::cin >> sName;
					printInput("Enter the password for the new user: ");
					std::cin >> sPassword;

					vAccounts.push_back(Account(sName, sPassword));
					printOutput("OK!");
					std::cout << "" << std::endl;
					break;
				case 2:
					vAccounts.erase(vAccounts.begin() + nCurrentID);
					printOutput("OK!");
					isLogout = true;
					break;
				case 4:
					printInput("Enter the current password: ");
					std::cin >> sOldPassword;
					printInput("Enter a new password: ");
					std::cin >> sNewPassword;

					if (vAccounts[nCurrentID].changePassword(sOldPassword, sNewPassword)) {
						printOutput("OK!");
					}
					else{
						printError("The current password is incorrect, please try again!");
					}
					break;
				case 5:
					printMenu(vAccounts[nCurrentID].getStatus());
					break;
				case 0:
					isLogout = true;
					break;
				case 99:
					printOutput("Bye!");
					return 0;
					break;
				default:
					printError("Your input is not recognized. Please try again!");
					break;
				}
			}
		}
		continue;
	}
	return 0;
}

