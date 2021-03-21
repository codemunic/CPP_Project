#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<iomanip>

using namespace std;

class book {
private:
	char author[20];
	char title[20];
	char publisher[20];
	int price;
	
public:
	/*
	book() {
		author = new char[20];
		title = new char[20];
		publisher = new char[20];
		price = new float;
		stock = new int;
	}
	*/
	int stock;
	void feeddata();
	void editdata();
	void showdata();
	bool search(char[], char[]);
	bool buybook();
	void gettitle() { cout << title; }

};

void book::feeddata() {
	cin.ignore();
	cout << "\nEnter Author Name: ";    cin.getline(author, 20);
	cout << "Enter Title Name: ";       cin.getline(title, 20);
	cout << "Enter Publisher Name: ";   cin.getline(publisher, 20);
	cout << "Enter Price: ";            cin >> price;
	cout << "Enter Stock Position: ";   cin >> stock;

}

void book::editdata() {

	cout << "\nEnter Author Name: ";    cin.getline(author, 20);
	cout << "Enter Title Name: ";       cin.getline(title, 20);
	cout << "Enter Publisher Name: ";   cin.getline(publisher, 20);
	cout << "Enter Price: ";            cin >> price;
	cout << "Enter Stock Position: ";   cin >> stock;

}

void book::showdata() {
	cout << "\nAuthor Name: " << author;
	cout << "\nTitle Name: " << title;
	cout << "\nPublisher Name: " << publisher;
	cout << "\nPrice: " << price;
	cout << "\nStock Available: " << stock;

}

bool book::search(char tbuy[20], char abuy[20]) {
	//cout << "In search" << endl;
 	if (strcmp(tbuy, title) == 0 && strcmp(abuy, author) == 0) {

	//if(tbuy==title && abuy==author){
		return 1;
	}
	else {
		return 0;
	}
}

bool book::buybook() {
	int count;
	cout << "\nEnter Number Of Books to buy: ";
	cin >> count;
	if (count <= stock) {
		stock = stock - count;
		cout << "\nBooks Bought Sucessfully";
		cout << "\nAmount: Rs. " << (price) * count;
		return true;
	}
	else
		cout << "\nRequired Copies not in Stock";
	return false;
}

//Function declaration
void BookDataFeed();
void PurchaseBook();
void SearchBook();
void modifybook();
void showallrecord();
void deletebook();



int main() {

	int choice;

	cout << "\n ********WELCOME TO YOUR LIBRARY DASHBOARD********"
		<< "\n1. Entry of New Book"
		<< "\n2. Buy Book"
		<< "\n3. Search For Book"
		<< "\n4. Edit Details Of Book"
		<< "\n5. Show All Book Record"
		<< "\n6. Clean Library"
		<< "\n7. Exit"
		<< "\n\nEnter your Choice: ";

	cin >> choice;

	switch (choice) {
	case 1:	BookDataFeed();
		main();

	case 2:
		PurchaseBook();
		main();

	case 3:
		SearchBook();
		main();



	case 4:
		modifybook();
		main();

	case 5:
		showallrecord();
		main();

	case 6:
		deletebook();
		cout << "\nAll books with 0 stock removed from library\n";
		main();

	case 7: exit(0);
	default: cout << "\nInvalid Choice Entered";

	}

	return 0;
}

void BookDataFeed() {
	book bk;
	bk.feeddata();
	ofstream oFile; // ofstream writing data
	oFile.open("bookrecord.dat", ios::binary | ios::app);//Binary handles newline character. App for writing data in same file app: append
	oFile.write(reinterpret_cast<char*> (&bk), sizeof(book));
	oFile.close();
	cout << "\n\nBook record Has Been Created ";
	cin.ignore();
	cin.get();
}

void PurchaseBook() {

	char titlebuy[20], authorbuy[20];

	cin.ignore();
	cout << "\nEnter Title Of Book: "; cin.getline(titlebuy, 20);
	cout << "Enter Author Of Book: ";  cin.getline(authorbuy, 20);

	book bk;
	bool purchased = false;

	fstream fl;  //fstream can both read and write. More memory it takes
	fl.open("bookrecord.dat", ios::binary | ios::in | ios::out);  // ios in for input, ios out for output

	if (!fl)
	{
		cout << "File could not be opened. Press any Key to exit...";
		cin.ignore();
		cin.get();
		return;
	}

	while (!fl.eof() && purchased == false)
	{
		fl.read(reinterpret_cast<char*> (&bk), sizeof(book));
		//cout << "Searching" << endl;

		if (bk.search(titlebuy, authorbuy))
		{
			bk.showdata();
			if (bk.buybook()) {
				purchased = true;
			}
			else {
				purchased = false;
			}

			if (purchased) {
				int pos = (-1) * static_cast<int>(sizeof(bk));
				fl.seekp(pos, ios::cur); // Set the seek cursor
				fl.write(reinterpret_cast<char*> (&bk), sizeof(book));
				break;
			}
		}
	}
	deletebook();
	if (purchased == false) {
		cout << "\nBook Purchased failed" << endl;
	}
	fl.close();
	cin.ignore();
	cin.get();
}

void SearchBook() {

	char titlebuy[20], authorbuy[20];

	cin.ignore();
	cout << "\nEnter Title Of Book: "; cin.getline(titlebuy, 20);
	cout << "Enter Author Of Book: ";  cin.getline(authorbuy, 20);

	book bk;
	ifstream iFile; // reading by ifstream
	iFile.open("bookrecord.dat", ios::binary);
	if (!iFile)
	{
		cout << "File could not be opened... Press any Key to exit";
		cin.ignore();
		cin.get();
		return;
	}

	bool flag = false;
	while (iFile.read(reinterpret_cast<char*> (&bk), sizeof(book)))
	{
		if (bk.search(titlebuy, authorbuy))
		{
			bk.showdata();
			flag = true;
		}
	}
	iFile.close();
	if (flag == false)
		cout << "\n\nrecord does not exist";
	cin.ignore();
	cin.get();

}

void modifybook() {

	char titlebuy[20], authorbuy[20];

	cin.ignore();
	cout << "\nEnter Title Of Book: "; cin.getline(titlebuy, 20);
	cout << "Enter Author Of Book: ";  cin.getline(authorbuy, 20);

	book bk;
	bool found = false;

	fstream fl;  //fstream can both read and write. More memory it takes
	fl.open("bookrecord.dat", ios::binary | ios::in | ios::out);  // ios in for input, ios out for output

	if (!fl)
	{
		cout << "File could not be opened. Press any Key to exit...";
		cin.ignore();
		cin.get();
		return;
	}

	while (!fl.eof() && found == false)
	{
		fl.read(reinterpret_cast<char*> (&bk), sizeof(book));
		if (bk.search(titlebuy, authorbuy))
		{
			cout << "Book found Successfully" << endl;
			bk.showdata();

			cout << "\nEnter the new details" << endl;
			bk.feeddata();   

			int pos = (-1) * static_cast<int>(sizeof(bk));
			fl.seekp(pos, ios::cur); // Set the seek cursor
			fl.write(reinterpret_cast<char*> (&bk), sizeof(book));
		}
	}
	fl.close();
	cin.ignore();
	cin.get();
}

void showallrecord() {
	book bk;
	ifstream iFile; // reading by ifstream
	iFile.open("bookrecord.dat", ios::binary);
	if (!iFile)
	{
		cout << "File could not be opened... Press any Key to exit";
		cin.ignore();
		cin.get();
		return;
	}

	while (iFile.read(reinterpret_cast<char*> (&bk), sizeof(book)))
	{
		bk.showdata();	
		cout << "\n#########################" << endl;
	}
	iFile.close();
	cin.ignore();
	cin.get();
}

void deletebook() {
	book bk;
	ifstream iFile;   //ifstream reads data from file
	iFile.open("bookrecord.dat", ios::binary);
	if (!iFile)
	{
		cout << "File could not be opened... Press any Key to exit...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream oFile;  //ofstream writes data to file
	oFile.open("Temp.dat", ios::out);
	iFile.seekg(0, ios::beg);
	while (iFile.read(reinterpret_cast<char*> (&bk), sizeof(book)))
	{
		if (bk.stock != 0)
		{
			oFile.write(reinterpret_cast<char*> (&bk), sizeof(book));
		}
		else {
			cout << "\nThis book is now unavailable: "; bk.gettitle();
		}
	}
	oFile.close();
	iFile.close();
	remove("bookrecord.dat");
	rename("Temp.dat", "bookrecord.dat");
	
	cin.ignore();
}



