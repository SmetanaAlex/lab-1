#pragma once
#define _CRT_SECURE_NO_WARNINGS_
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include <conio.h>
#include "Header.h"

using namespace std;

enum Role { client, admin };

struct User
{
	int id;
	char login[20] = {};
	int password;
	Role role;
	
};
struct Results {
int rez_id;
char res[20] = {};
char logins[20] = {};
int ids;
};
int read_adm(User user);
int read_user(User user);
int add(Results simple,int ustp);
int menu_add(int ustp);
int Admin(User user);
int Client(User user);
int menu_admin();
int menu_client();
int Registration();
int Authorization();
int Add_ress(User user);
int Creator();
int Authentication(User user);
//int global_user_id = 0;
int menu_start();
int write(Results simple ,int ustp);
int main()
{
	bool isRunning = true;
	while (isRunning)
	{
		int answer = 0;
		setlocale(LC_ALL, "Russian");
		answer = menu_start();
		switch (answer)
		{
		case 0:Authorization(); break;
		case 1:Registration(); break;
		case 2: system("cls"); cout << "Goodbye!\n__________________"; isRunning = false;
		}

	}
	/*ofstream w;
	w.open("users.dat", ios::binary);
	w.close();*/

}

int Authentication(User user)
{
	if (user.role == admin)
	{
		Admin(user);
	}
	if (user.role == client)
	{
		Client(user);
	}
	return 0;
}

int Admin(User user)
{
	bool isRunning = true;
	while (isRunning)
	{

		system("cls");
		cout << "Hello, admin!\n";
		cout << "Choose the option:\n";
		cout << "__________________\n";
		int tmp = menu_admin();
		switch (tmp)
		{
		case 0: Creator(); return 0; break;
		case 1:; read_adm( user);isRunning = 0; return 0; break;
		case 2:  Creator(); isRunning = 0; return 0; break;
		case 3: /*Delete(user);*/ system("pause"); isRunning = 0; return 0; break;
		case 4: Add_ress( user);  isRunning = 0; return 0; break;
		case 5: system("cls"); isRunning = 0; return 0; break;
		}
	}
	return 0;
}



int Client(User user)
{
	bool isRunning = true;
	while (isRunning)
	{
		system("cls");
		int tmp = menu_client();
		switch (tmp)
		{
		case 0:
		{cout << "Hello, client!\n";
		cout <<    read_user(user); isRunning = 0; break; }
		case 1: system("cls"); isRunning = 0; return 0;
		}
	}
	return 0;
}

int Registration()
{
	cin.clear();// while (cin.get() != '\n');
	User iteruser;
	int cnt = 0;
	ifstream f1("users.dat", ios::binary);

	while (f1.read((char*)&iteruser, sizeof(User))) {
		cnt++;
	}
	f1.close();
	bool isFirst = 1;
	if (cnt > 0)isFirst = 0;
	User cur;
	if (isFirst)cur.id = 1;
	else cur.id = cnt + 1;
	bool isRepeated = 0;
	while (!isRepeated) {
		system("cls");
		cout << "\n" << "Id = " << cur.id << "\n\n";
		cout << "Enter login: ";
		cin.getline(cur.login, 19);
		f1.open("users.dat", ios::binary);
		if (isFirst == 1)isRepeated = 1;
		else {
			while (f1.read((char*)&iteruser, sizeof(User))) {
				if (strcmp(cur.login, iteruser.login) == 0) {
					cout << "Login is taken!\n";
					system("pause");
					isRepeated = 0;
					break;
				}
				isRepeated = 1;
			}
		}
		f1.close();
	}

	cout << "Enter password: ";
	char password[20];
	cin.getline(password, 19);
	cout << "Choose your role:\n";
	cout << "1 ---> client\n2 ---> admin\n";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1: cur.role = client; break;
	case 2: cur.role = admin; break;
	}
	cur.password = md5(password, strlen(password));

	ofstream f("users.dat", ios::app, ios::binary);
	f.write((char*)&cur, sizeof(User));
	f.close();
	return 0;
}

int Authorization()
{
	User iteruser;
	int cnt = 0; 
	ifstream f1("users.dat", ios::binary);

	while (f1.read((char*)&iteruser, sizeof(User))) {
		cnt++;
	}
	f1.close();
	if (cnt > 0) {
		char strpassword[20] = {};
		bool isOk = 0;
		while (!isOk) {
			system("cls");
			ifstream f("users.dat", ios::binary);
			char login[20] = {};
			cout << "Enter login: ";
			
			//while (cin.get() == '\n')continue;
			cin.getline(login, 19);
			cin.clear();
			while (f.read((char*)&iteruser, sizeof(User))) {
				if (strcmp(iteruser.login, login) == 0) {
					isOk = 1;
					break;
				}
			}
			f.close();
			if (isOk == 1) {
				int passwordmd5;
				do {
					system("cls");
					cout << "Current login: " << login << '\n';
					cout << "Enter password: ";
					cin.getline(strpassword, 19);
					passwordmd5 = md5(strpassword, strlen(strpassword));
				} while (iteruser.password != passwordmd5); 
			}

		}

		system("cls");
		Authentication(iteruser);
		return 0;
	}
	else {
		cout << "There are no Users, registrate first!\n";
		system("pause");
		system("cls");
		return 0;
	}
}



int menu_start() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 3) % 3;
		if (key == 0) cout << "-> I'd like to sign in" << endl;
		else  cout << "   I'd like to sign in" << endl;
		if (key == 1) cout << "-> I'm new user, let me create a new account" << endl;
		else  cout << "   I'm new user, let me create a new account" << endl;
		if (key == 2) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}

int menu_admin()
{
	int key = 0;
	int code;
	do {
		system("cls");
		cout << "Hello, admin!\n";
		cout << "Choose the option:\n";
		cout << "__________________\n";

		key = (key + 6) % 6;
		if (key == 0) cout << "-> Create" << endl;
		else  cout << "   Create" << endl;
		if (key == 1) cout << "-> Read" << endl;
		else  cout << "   Read" << endl;
		if (key == 2) cout << "-> Update" << endl;
		else  cout << "   Update" << endl;
		if (key == 3) cout << "-> Delete" << endl;
		else  cout << "   Delete" << endl;
		if (key == 4) cout << "-> Update results" << endl;
		else  cout << "  Update results" << endl;
		if (key == 5) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}

int menu_client()
{
	int key = 0;
	int code;
	do {
		system("cls");
		cout << "Hello, client!\n";
		cout << "Choose the option:\n";
		cout << "__________________\n";
		key = (key + 2) % 2;
		if (key == 0) cout << "-> Results" << endl;
		else  cout << "   Results" << endl;
		if (key == 1) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}

int Add_ress (User user) {
	cin.clear();
	while (cin.get() != '\n');
	Results iteruser;
	int cnt = 0;
	ifstream f1("results.dat", ios::binary);

	while (f1.read((char*)&iteruser, sizeof(User))) {
		cnt++;
	}
	f1.close();
	bool isFirst = 1;
	if (cnt > 0)isFirst = 0;
	Results cur;
	if (isFirst)cur.rez_id = 1;
	else cur.rez_id = cnt + 1;
	bool isRepeated = 0;
	while (!isRepeated) {
		system("cls");
		cout << "\n" << "Id = " << cur.rez_id << "\n\n";
		cout << "Enter result: ";
		cin.clear();
		cin.getline(cur.res, 19);
		f1.open("results.dat", ios::binary);
		if (isFirst == 1)isRepeated = 1;
		else {
			while (f1.read((char*)&iteruser, sizeof(User))) {
				if (strcmp(cur.res, iteruser.res) == 0) {
					cout << "Login is taken!\n";
					system("pause");
					isRepeated = 0;
					break;
				}
				isRepeated = 1;
			}
		}
		f1.close();
	}
	ofstream f("results.dat", ios::app, ios::binary);
	f.write((char*)&cur, sizeof(User));
	f.close();
	Admin(user);
	return 0;
}

int Creator() {
//////////////////////////////////////////////////////////////////////////////////////////////////////
cout << "patient login\n";
Results simple;
cin.clear();
cin.getline(simple.logins,20);
User cuc;
cout << "1" << endl;
///////////////////
ifstream k1("users.dat", ios::binary);
 k1.open ("users.dat", ios::binary);
 
			while (k1.read((char*)&cuc, sizeof(User))) {
				if (strcmp(cuc.login, simple.logins)==0 ) {
					cout << "Login is taken!\n";
					system("pause");
					break;
				}
				else cout << "2" << endl;
			}	
k1.close();////////////////////////
Results iteruser;
int cnt = 0;
ifstream f1("amigos.dat", ios::binary);
while (f1.read((char*)&iteruser, sizeof(User))) {
	cnt++;
}
f1.close();
bool isFirst = 1;
if (cnt > 0)isFirst = 0;
if (isFirst)simple.rez_id = 1;
else simple.rez_id =cnt+1 ;
int ustp = 1;
///////////////////////
cout << cnt << endl;
system("pause");/////
add( simple ,ustp);
return 0;
}

int add(Results simple, int ustp) {
	bool isRunning = true;
	while (isRunning)
	{

		int tmp = menu_add( ustp);
		switch (tmp)
		{
		case 0: write( simple,ustp); return 0; break;
		case 1:  ustp++; add( simple, ustp); isRunning = 0; return 0; break;
		case 2: ustp--; add(simple, ustp);  isRunning = 0; return 0; break;
		case 3: menu_admin(); system("pause"); isRunning = 0; return 0; break;
		}
	}
	return 0;
}

int menu_add(int ustp){
	int key = 0;
	Results rr;
	int code;
	do {
		system("cls");
		ifstream k1("results.dat",ios::binary);
		while (k1.read((char*)&rr, sizeof(User))) {
			if (rr.rez_id == ustp) {
				cout << rr.res<<endl;
			}
		}
		k1.close() ;
		cout << "Choose the option:\n";
		cout << "__________________\n";

		key = (key + 4) % 4;
		if (key == 0) cout << "-> Yes" << endl;
		else  cout << "   Yes" << endl;
		if (key == 1) cout << "-> Next" << endl;
		else  cout << "   Next" << endl;
		if (key == 2) cout << "-> Previus (i know about mistake)" << endl;
		else  cout << "   Previus" << endl;
		if (key == 3) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}

int write(Results simple, int ustp)
{
	Results rr;
	ifstream k1("results.dat", ios::binary);
	while (k1.read((char*)&rr, sizeof(Results))) {
		if (rr.rez_id == ustp) {
			strcpy_s(simple.res, rr.res);
		}
	}
	k1.close();
	ofstream f("amigos.dat", ios::app, ios::binary);
	f.write((char*)&simple, sizeof(User));
	f.close();
	return 0;
}
int read_adm(User user) {
	User ded;
	Results k1;
	ifstream f("amigos.dat", ios::binary);
	cout << "Enter login: ";
	cin.getline(ded.login, 19);
	while (f.read((char*)&k1, sizeof(Results))) {
		if (!strcmp(k1.logins, ded.login) == 0) {
			cout << k1.res << endl;
		}
	}
	system("pause");
	f.close();
	Admin(user);
	return 0;
}

int read_user(User user){
	Results k1;
	ifstream f("results.dat", ios::binary);
	cout <<"Glad that you have chosen my DDDDDDDDD : " << user.login << " :)\n";
	while (f.read((char*)&k1, sizeof(Results))) {
		if (!strcmp(k1.logins, user.login) ) {
			cout << k1.res/*rez_id*/ << endl;
			
		}

	}
	 system("pause");
	f.close();
	Client( user);
   
	return 0;
}
