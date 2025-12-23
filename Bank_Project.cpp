#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include<Windows.h>
using namespace std;

struct Clyent {
	string Accountnumber;
	string pinCode;
	string name;
	string Phone;
	string Blance;
};

fstream DataCLYfile;
vector <string> fillVetor() {
	vector <string> CLYE;
	string line;
	DataCLYfile.open("D:\\my_programe\\nasa\\DataClyents.txt", ios::in);
	if (DataCLYfile.is_open()) {
		while (getline(DataCLYfile, line))
		{
			CLYE.push_back(line);
		}
		DataCLYfile.close();
	}
	return CLYE;

}

void nl(int n,char c) {
	for (int i = 0; i < n;i++) {
		cout << c;
	}
	cout << endl;
}
void screen() {
	nl(50,'=');
	cout << "                \033[1;34mMain Menu Screen\033[0m\n";
	nl(50,'=');
	cout << "           "   << "=>1< Show Client List.\n"
		<< "           "   << "=>2< Add New Client.\n"
		<< "           "   << "=>3< Delete Client.\n"
		<< "           "   << "=>4< Update Client Info.\n"
		<< "           "   << "=>5< Find Client.\n"
		<< "           " << "=>6< Clear All Clients.\n"
		<< "           "   << "=>7< Exit."<<endl;
	nl(50,'=');
	cout << "Choose What do you want do? ==> 1,2,....,6 <==: ";
}

vector<string> splitToVector(string Dataclyent, string delam = "||") {
	int pos;
	vector<string> c;

	while ((pos = Dataclyent.find(delam)) != string::npos) {
		c.push_back(Dataclyent.substr(0, pos));
		Dataclyent.erase(0, pos + delam.length());
	}

	c.push_back(Dataclyent);
	return c;
}

void display(vector <string >& Clyents) {

	cout << "                                             Client List ("<<Clyents.size()<<") Client(s)\n";
	nl(105,'_');
	vector <string> c;
	cout << "\n| Account Number | Pin Code | Client Name                         | Phone            |Balance\n";
	nl(105,'_');
	cout << "\n                               Waiting Loading Data From File.... \n";
	Sleep(2000);
	system("cls");
	cout << "                                             Client List (" << Clyents.size() << ") Client(s)\n";
	nl(105, '_');
	cout << "\n| Account Number | Pin Code | Client Name                         | Phone            |Balance\n";
	nl(105, '_');
	for (string CLY : Clyents) {
		c= splitToVector(CLY);
		cout << "| " << left << setw(15) << c[0]
			<< "| " << left << setw(9) << c[1]
			<< "| " << left << setw(35) << c[2]
			<< "| " << left << setw(16) << c[3]
			<< "| " << left << setw(7) << c[4] << endl;
	
		
	}


	cout<<"\nMain Menu  ";
		system("pause");
	
}
string joindataclyent(Clyent clyadd, string delam = "||") {
	string join="";
	join += clyadd.Accountnumber + delam;
	join += clyadd.pinCode + delam;
	join += clyadd.name + delam;
	join += clyadd.Phone + delam;
	join += clyadd.Blance ;
	return join;

}

bool uniqeAccountnumber(string checkk) {
	string line;
	Clyent clientsearch;
	vector <string> c;
	cout << "\nCheck Accoount is Unique Or Not....\n ";
	Sleep(500);
	DataCLYfile.open("D:\\my_programe\\nasa\\DataClyents.txt", ios::in);
	if (DataCLYfile.is_open()) {
		while (getline(DataCLYfile, line))
		{
			c = splitToVector(line);

			if (c[0] == checkk) {
				DataCLYfile.close();
				return true; 
			}
		}
		DataCLYfile.close();
	}
	return false; 
}

Clyent Readclientdata() {
	Clyent clyaddd;
	cout << "Enter Account Number: ";
	getline(cin >> ws, clyaddd.Accountnumber);

    while (uniqeAccountnumber(clyaddd.Accountnumber)) {
		cout << "Client with [" << clyaddd.Accountnumber << "] already exists, Enter another Account Number: ";
		getline(cin >> ws, clyaddd.Accountnumber);
	}

	cout << "Enter PinCode: ";
	getline(cin , clyaddd.pinCode);
	cout << "Enter Name: ";
	getline(cin  , clyaddd.name);
	cout << "Enter Phone: ";
	getline(cin  , clyaddd.Phone);
	cout << "Enter Account Balance: ";
	getline(cin , clyaddd.Blance);
	return clyaddd;
}
void addClyent(vector <string > Clyents) {
	nl(50, '-');
	cout <<"         Add New Clients Sccreen\n";
	nl(50, '-');
	cout << "Adding New Client:\n" << endl;
	Clyent clyadd= Readclientdata();
	DataCLYfile.open("D:\\my_programe\\nasa\\DataClyents.txt", ios::out|ios::app);
	if (DataCLYfile.is_open()) {
		DataCLYfile<< joindataclyent(clyadd)<<endl;

	}
	DataCLYfile.close();


}

void Delete(vector<string>& Clyents) {

	nl(50, '.');
	cout << "         Delete Client Screen\n";
	nl(50, '.');

	string accnum;
	bool checkfound = false;

	cout << "Enter Account Number to Delete Client: ";
	cin >> accnum;


	for (string& CLY : Clyents) {

		vector<string> data = splitToVector(CLY);

		if (data[0] == accnum) {
			checkfound = true;

			cout << "The Following are the client Details : \n";
			nl(50, '-');
			cout << "Account Number => " << data[0] << endl;
			cout << "Pin Code       => " << data[1] << endl;
			cout << "Name           => " << data[2] << endl;
			cout << "Phone          => " << data[3] << endl;
			cout << "Balance        => " << data[4] << endl;
			nl(50, '-');

			char ans;
			cout << "Are you sure you want to delete this client? Y/N: ";
			cin >> ans;

			if (toupper(ans) == 'Y') {
				CLY = "";
				cout << "Deleting...........";
				Sleep(1000);
				cout << "\nClient with Account Number ==> " << accnum << " <== Deleted Sccussfuly\n";
				
			}
			else {
				cout << "\nMain Menu\n";
				system("pause");
				return;
			}
			break;
		}
	}

	if (!checkfound) {
		cout << "Client with Account Number ==> " << accnum << " <== Not Found\n";
		system("pause");
		return;
	}


	ofstream DataCLYfile("D:\\my_programe\\nasa\\DataClyents.txt", ios::out);

	for (string CLY : Clyents) {
		if (!CLY.empty())
			DataCLYfile << CLY << endl;
	}

	DataCLYfile.close();
	system("pause");
}


void Update(vector<string>& Clyents) {

	nl(50, '.');
	cout << "         Update Client Screen\n";
	nl(50, '.');

	string accnum;
	bool checkfound = false;

	cout << "Enter Account Number to Update Client: ";
	cin >> accnum;


	for (string& CLY : Clyents) {

		vector<string> data = splitToVector(CLY);

		if (data[0] == accnum) {
			checkfound = true;

			cout << "The Following are the client Details : \n";
			nl(50, '-');
			cout << "Account Number => " << data[0] << endl;
			cout << "Pin Code       => " << data[1] << endl;
			cout << "Name           => " << data[2] << endl;
			cout << "Phone          => " << data[3] << endl;
			cout << "Balance        => " << data[4] << endl;
			nl(50, '-');

			char ans;
			cout << "Are you sure you want to Update this client? Y/N: ";
			cin >> ans;

			if (toupper(ans) == 'Y') {
				Clyent cc;
				cc.Accountnumber = accnum;
				cout << "Enter PinCode: ";
				getline(cin>>ws,cc.pinCode);
				cout << "Enter Name: ";
				getline(cin, cc.name);
				cout << "Enter Phone: ";
				getline(cin, cc.Phone);
				cout << "Enter Account Balance: ";
				getline(cin, cc.Blance);
				CLY=joindataclyent(cc);
				cout << "Updating...........";
				Sleep(1000);
				cout << "\nClient with Account Number ==> " << accnum << " <== Updated Sccussfuly\n";


			}
			else {
				cout << "\nMain Menu\n";
				system("pause");
				return;
			}
			break;
		}
	}

	if (!checkfound) {
		cout << "Client with Account Number ==> " << accnum << " <== Not Found\n";
		system("pause");
		return;
	}


	ofstream DataCLYfile("D:\\my_programe\\nasa\\DataClyents.txt", ios::out);

	for (string CLY : Clyents) {
		if (!CLY.empty())
			DataCLYfile << CLY << endl;
	}

	DataCLYfile.close();
	system("pause");
}
void Find(vector<string>& Clyents) {
	nl(50, '.');
	cout << "         Find Client Screen\n";
	nl(50, '.');
	string accnum;
	bool checkfound = false;
	cout << "Enter Account Number to Find Client: ";
	cin >> accnum;


	for (string& CLY : Clyents) {

		vector<string> data = splitToVector(CLY);

		if (data[0] == accnum) {
			checkfound = true;

			cout << "The Following are the client Details : \n";
			nl(50, '-');
			cout << "Account Number => " << data[0] << endl;
			cout << "Pin Code       => " << data[1] << endl;
			cout << "Name           => " << data[2] << endl;
			cout << "Phone          => " << data[3] << endl;
			cout << "Balance        => " << data[4] << endl;
			nl(50, '-');
			cout << "\nMain Menu  ";
			system("pause");
		}
		}

	if (!checkfound) {
		cout << "Client with Account Number ==> " << accnum << " <== Not Found\n";
		system("pause");
		return;
	}
}
void clear(vector<string>& Clyents) {
	nl(50, '.');
	cout << "         Clear All Clients Screen\n";
	nl(50, '.');
	char ans;
	cout << "Are you sure you want to Clear All Clients? Y/N: ";
	cin >> ans;
	if (toupper(ans) == 'Y') {
		ofstream DataCLYfile("D:\\my_programe\\nasa\\DataClyents.txt", ios::out);
		DataCLYfile.close();
		Clyents.clear();
		cout << "Clearing All Clients...........";
		Sleep(1000);
		cout << "\nAll Clients Cleared Sccussfuly\n";
	}
	else {
		cout << "\nMain Menu\n";
		system("pause");
		return;
	}
	cout << "\nMain Menu  ";
	system("pause");
}

void choose() {

	string input;
	int choose;

	while (true) {

		vector<string> Clyents = fillVetor();
		system("cls");
		screen();

		cin >> input;

		try {
			choose = stoi(input);  
		}
		catch (...) {
			cout << "Invalid input! Please enter a number.\n";
			system("pause");
			continue;
		}

		system("cls");

		switch (choose) {

		case 1:
			display(Clyents);
			break;

		case 2: {
			char ans;
			do {
				system("cls");
				addClyent(Clyents);
				cout << "Adding...........";
				Sleep(1000);
				cout << "\nClient Added Successfully, Do you Want add More => Y/N <=: ";
				cin >> ans;
			} while (toupper(ans) == 'Y');

			cout << "\nMain Menu  ";
			system("pause");
			break;
		}

		case 3:
			Delete(Clyents);
			break;
		case 4:
			Update(Clyents);
			break;
		case 5:
			Find(Clyents);
			break;
		case 6:
			clear(Clyents);
			break;
		case 7:
			cout << "Exiting....";
			Sleep(1000);
			system("cls");
			cout << "\n\n\n\n\n\n                    Thank You  =============== S A K R  =============== \n\n\n\n\n\n\n\n\n";
			return;

		default:
			cout << "\nEnter Valid Choice\nMain Menu   ";
			system("pause");
		}
	}
}


int main()
{

	choose();

}

