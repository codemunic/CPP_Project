#include <iostream>
#include <fstream>  // For file operation
#include <sys/types.h> 
#include <sys/stat.h> 
#include <string>


using namespace std;

bool logIn();
void registeruser();
void password_reset();


int main() {
	int choice;
	
	cout << " " << endl;
	cout << "*********************LOGIN SYSTEM********************** " << endl;
	
	cout << "1: Register\n2: Login\n3: Forgot Password\n4: Exit\nYour choice: "; cin >> choice;
	if (choice == 1) {
		registeruser();

		main();
	}
	else if (choice == 2) {
		bool status = logIn();
		if (!status) {
			cout << "Incorrect Username or password" << endl;
			main();
		}
		else {
			cout << "Logged In successfully " << endl;
			cout << "Welcome to your dashboard :)" << endl;
			cin.get();
			cin.get();
			main();
		}
	}
	
	else if(choice==3){
		password_reset();
	}
	else if(choice==4){
		return 1;
	}
	
	else{
		cout << "Please select from the given options " << endl;
		main();
	}
	return 0;
}



bool logIn() {
	string username, password, un, pw;

	cout << "Enter Username: "; 
	cin >> username;
	cout << "Enter Password: ";
	cin >> password;

	// ifstream for reading a file
	//ifstream read("data//" + username + ".txt");

	
	/*
	getline(read, un);
	getline(read, pw);

	if (username == un && password == pw) {
		return true;
	}
	else {
		return false;
	}
	*/

	ifstream entered("data/userdata.txt");
	bool ret = 0;
	while(entered >> un >> pw){
		if(un==username && pw == password){
			ret = 1;
			break;
		}
	}
	
	entered.close();
	
	if(ret==1){
		return true;
	}
	
	return false;
}

void registeruser(){
	string username, password;

	cout << "Enter the username: "; cin >> username;
	cout << "Enter the password: "; cin >> password;

	int check = mkdir("data",0777);
	
	/*

	if(check==-1){
		cout << "Making directory fail" << endl;
	}
	*/

	// ofstream for creating a file
	
	
	/*
	ofstream file;
	file.open("data//" + username + ".txt");
	file << username << endl << password;
	file.close();
	*/
	
	
	// Check if the entered username is already registered
	
	string un,pw;
	ifstream entered("data/userdata.txt");
	bool ret = 0;
	while(entered >> un >> pw){
		if(un==username){
			ret = 1;
			break;
		}
	}
	
	entered.close();
	
	if(ret==1){
		cout << "Sorry, Username is already taken. Please try different username or Check for password " << endl;
		main();
	}
	
	// if username is not present, then register
	
	ofstream file("data/userdata.txt", ios::app);

	file << username << "\t" << password << endl;


	cout << "User Registered Successfully " << endl;
	
}


void password_reset(){
	string username, password, un, pw;
	
	cout << "Please enter your username: ";
	cin >> username;
	
	ifstream entered("data/userdata.txt");
	
	bool ret = 0;
	while(entered >> un >> pw){
		if(un==username){
			ret = 1;
			password = pw;
			break;
		}
	}
	
	entered.close();
	
	if(ret==0){
		cout << "Sorry, This username doesn't exists. Please register yourself" << endl;
		main();
	}
	else{
		cout << "Your Password is "+ password << endl;
		cout << "Please login again " << endl;
		main();
	}
	
}

