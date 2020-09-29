
#include "Menu.h"
#include "C:\Users\Lenovo\source\repos\BookshopMy\BookshopMy\EnterAndMatrix.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <iomanip>
//#include "ValidData.h"
////////
using namespace std;

ofstream &operator<<(ofstream &a, Enter &b)
{
	a << b.login << endl << b.password << endl; return a;
}

ifstream &operator >> (ifstream &a, Enter &b)
{
	a >> b.login >> b.password; return a;
}

ostream &operator<<(ostream &a, Enter &b)
{
	a << "Логин " << b.login << endl << "Пароль " << b.password << endl << endl; return a;
}

istream &operator >> (istream &a, Enter &b)
{
	cout << "Логин: ";
	a >> b.login;
	cout << "Пароль: ";
	a >> b.password;
	return a;
}
////


void main() {
	setlocale(LC_ALL, "ru");
	//system("color F0");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	WORD wstock_matersionRequested;
	WSADATA wsaData;
	int err;
	wstock_matersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wstock_matersionRequested, &wsaData);
	if (err != 0) { return; }

	int mainMenuNum = 0;
	Bookshop* shop = new Bookshop();
	Menu menu;
	while (true)
	{
		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in dest_addr;
		dest_addr.sin_family = AF_INET;
		dest_addr.sin_port = htons(1280);
		dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		connect(s, (sockaddr *)&dest_addr, sizeof(dest_addr));
		char string[20];
		char buf[20];
		char buf1[20];
		char name[20];
		Enter ob;
		vector<Enter> mas;
		Enter buf2;
		//		Matrix matrix;

		char res[20];
		int result;
		int choice = 0;

		std::cout.setf(std::ios::right);
		std::cout.width(50);
		std::cout << "|  Войдите или Зарегистрируйтесь  |" << std::endl;
		std::cout << "1.Вход" << std::endl;
		std::cout << "2.Регистрация" << std::endl;
		std::cout << "3.Выход" << std::endl;
		int flag;
	//	ValidData<int> checkValid;
		//cin >> flag;
		flag=ValidData<int>::getValidValue("Введите корректное числовое значение");
		//flag = checkValid.getValidValue("Введите корректный выбор ");

		itoa(flag, string, 10);
		send(s, string, 20, 0);
		// std::cin >> mainMenuNum; 
		//mainMenuNum = menu.getValidValue<int>("Введите корректный выбор ");
		switch (flag)
		{
		case 1:
		{
			User* startUser = shop->signIn();
			if (startUser != NULL)
			{
				if (typeid(*startUser).name() == typeid(Admin).name())
				{

					menu.adminMode(dynamic_cast<Admin*>(startUser));
				}
				else if (typeid(*startUser).name() == typeid(Buyer).name())
				{
					menu.buyerMode(dynamic_cast<Buyer*>(startUser), shop);
				}
			}
			else
			{
				std::cout << "Попробуйте снова" << std::endl;
				break;
			}
			break;
		}
		case 2:
		{
			User* startUser = shop->signUp();
			if (startUser != NULL)
				menu.buyerMode(dynamic_cast<Buyer*>(startUser), shop);

			// работаем  только как с покупателем
			break;
		}
		case 3:
			delete shop;
			exit(0);
		default:
			break;
		}
	}

}
