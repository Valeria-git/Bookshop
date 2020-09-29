#include "Admin.h"
#include "Windows.h"
#include <iomanip>
#include "ValidData.h"
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Catalog.h"

//#include "User.h"

Admin::Admin(std::string email, std::string password) {

	this->email = email;
	this->password = password;
	this->userType = "admin";
}

Admin::~Admin() {

}

void Admin::addBook() {  // ������� ��� ����� ���� ����� ��� ���� ����������� ������ ���������� ������ �����


	std::string name, author;
	double price;
	int amount;

	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "������� �������� ������" << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin, name);
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	SetConsoleCP(866);
	std::cout << "������� ����� ������" << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin, author);
	SetConsoleCP(866);
	std::cout << "������� ��������� ������" << std::endl;
	price = ValidData<double>::getValidValue("������� ���������� �������� ��������");
	std::cout << "������� ���������� �������" << std::endl;
	amount = ValidData<int>::getValidValue("������� ���������� �������� ��������");
	Book book(name, author, price);
	BookForSale book4Sale(book, amount);
	assortment.addToCatalog(book4Sale);

}

void Admin::findBook()
{
	system("cls");
	std::string toFind;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "����� : " << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin, toFind);
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	SetConsoleCP(866);
	assortment.readCatalog();
	std::vector<BookForSale> catalogToFind;
	catalogToFind = assortment.getAssortment();
	bool isFound = false;
	for (auto book : catalogToFind)
	{
		int index = (book.getBook().getName() + book.getBook().getAuthor() + std::to_string(book.getBook().getPrice()) + std::to_string(book.getAmount())).find(toFind);
		if (index != std::string::npos)
		{
			std::cout << "|" << std::setw(25) << book.getBook().getName() + "|" << std::setw(25) << book.getBook().getAuthor() + "|" << std::setw(12) <<
				std::to_string(book.getBook().getPrice()) + "�|" << std::setw(5) << std::to_string(book.getAmount()) << "��|" << std::endl;
			isFound = true;
		}
	}
	if (!isFound)
		std::cout << "�� ������� ������� ������ �� �������" << std::endl;
	assortment.clearAssortment();
	system("pause");
}
void Admin::deleteBook()
{
	std::string name, author;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "������� �������� ������" << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin, name);
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	SetConsoleCP(866);
	/////////////
	std::cout << "������� ����� ������" << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin, author);
	SetConsoleCP(866);
	assortment.deleteBook(name, author);
}

void Admin::readLog()
{
	std::vector<BookForSale> soldItems;
	std::string LOG_FILE = "C:\\Users\\Lenovo\\source\\repos\\BookshopMy\\BookshopMy\\Log.txt";
	std::fstream read;
	read.open(LOG_FILE, std::fstream::in);
	if (!read.is_open())
	{
		read.open(LOG_FILE, std::fstream::in);
	}
	else {
		std::string buf;
		while (!read.eof())
		{
			buf.clear();
			getline(read, buf, '\n');
			if (buf.size() != 0)
			{
				char* dup = new char(strlen(buf.c_str()) + 1);
				dup = _strdup(buf.c_str());
				char* t = nullptr;
				std::string login = strtok_s(dup, "|", &t);
				std::string name = strtok_s(nullptr, "|", &t);
				std::string author = "";
				int amount = atoi(strtok_s(nullptr, "|", &t));
				double price = atof(strtok_s(nullptr, "|", &t)) / amount;

				Book book(name, author, price);
				BookForSale book4sale(book, amount);
				soldItems.push_back(book4sale);
			}
		}
		std::map<std::string, int> popularity;
		for (int i = 0; i < soldItems.size(); ++i)
		{
			if (!popularity.empty())
			{
				auto search = popularity.find(soldItems[i].getBook().getName());
				if (search != popularity.end())
				{
					//int oldAmount = search->second;
					//std::string oldString = search->first;
					//popularity.erase(search);
					search->second += soldItems[i].getAmount();
					//popularity.emplace(oldString, (oldAmount + soldItems[i].getAmount()));

				}
				else
					popularity.emplace(soldItems[i].getBook().getName(), soldItems[i].getAmount());
			}
			else
				popularity.emplace(soldItems[i].getBook().getName(), soldItems[i].getAmount());
		}
		if (!popularity.empty()) {
			std::map<std::string, int>::iterator iterator = popularity.begin();
			// Iterate over the map using Iterator till end.
			struct
			{
				std::string popNames;
				int popAmount;
			}typedef pops;

			std::vector<pops> finalPopItems;
			while (iterator != popularity.end())
			{
				pops pop;
				pop.popNames = iterator->first;
				pop.popAmount = iterator->second;
				finalPopItems.push_back(pop);
				iterator++;
			}
			if (!finalPopItems.empty()) {
				std::sort(finalPopItems.begin(), finalPopItems.end(), [](pops pop1, pops pop2) {return pop1.popAmount > pop2.popAmount; });
				std::cout << "\t|" << std::setw(25) << " ������������ ������     " << "|" << std::setw(20) <<
					"   ���-�� ��������� ������    " << "|" << std::endl;
				std::cout << "\t|" << std::setw(25) << "_________________________" << "|" << std::setw(20) <<
					"______________________________" << "|" << std::endl;
				for (auto item : finalPopItems)
				{
					std::cout << "\t|" << std::setw(25) << item.popNames << "|" << std::setw(30) <<
						item.popAmount << "|" << std::endl;
				}
				std::cout << "\t|" << std::setw(25) << "_________________________" << "|" << std::setw(20) <<
					"______________________________" << "|" << std::endl;
			}
			system("pause");
		}
	}
	read.close();
}
bool comp2(int a, int b) { return (a > b); }

void Admin::addExpert() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	const  std::string EXPERT_FILE = "C:\\Users\\Lenovo\\source\\repos\\BookshopMy\\BookshopMy\\Expert.txt";
	std::string goals[6];

	std::cout << "������� ����" << std::endl;
	for (int i=0;i<5;i++) {
	
		std::getline(std::cin, goals[i]);
		
	}
	double o1, o2, o3, o4,o5;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "������� ������ ������ ����" << std::endl;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	o1 = ValidData<double>::getValidValueExpert("������� ���������� �������� ��������(�� 0 �� 100)");
	std::cout << "������� ������ ������ ����" << std::endl;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	o2 = ValidData<double>::getValidValueExpert("������� ���������� �������� ��������(�� 0 �� 100)");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "������� ������ ������� ����" << std::endl;
	o3 = ValidData<double>::getValidValueExpert("������� ���������� �������� ��������(�� 0 �� 100)");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "������� ������ ��������� ����" << std::endl;
	o4 = ValidData<double>::getValidValueExpert("������� ���������� �������� ��������(�� 0 �� 100)");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "������� ������ ����� ����" << std::endl;
	o5 = ValidData<double>::getValidValueExpert("������� ���������� �������� ��������(�� 0 �� 100)");
	
	int decision;
	std::cout << "�������� 1-�� �� ���� ������ ���� 2 + 3 + 4 + 5?" << std::endl;
	
	std::cin >> decision;
	if (decision == 1) { o1 =o2+o3+o4+o5+5; }
	else if (decision == 0) { o1 = o2 + o3 + o4 + o5 -5;}
	
	std::cout << "�������� 2-�� �� ���� ������ ���� 3 + 4 + 5?" << std::endl;
	
	std::cin >> decision;
	if (decision == 1) { o2 = o3 + o4 + o5 + 5; }
	else if (decision == 0) { o2 = o3 + o4 + o5 - 5; }
	
	std::cout << "�������� 3-�� �� ���� ������ ���� 4 + 5?" << std::endl;

	std::cin >> decision;
	if (decision == 1) { o3 =  o4 + o5 + 5; }
	else if (decision == 0) { o3 = o4 + o5 - 5; }
	

	double res = o1 + o2 + o3 + o4 + o5;
	double v[5];
	v[0] = o1 / res;
	v[1] = o2 / res;
	v[2] = o3 / res;
	v[3] = o4 / res;
	v[4] = o5 / res;
	double max = v[0];
	int maxIndex=0;
	for (int i = 0; i < 5; i++) {
		if (v[i] > max) {
			max = v[i];
			maxIndex = i;
		}
	}
	std::vector<double> sort_double_vector(v, v + 5);
	for (int i = 0; i < 5; i++) {
		std::cout << "��� " << i + 1 << "-��� ��������" << "���������� " << v[i] << std::endl;
	}
	{
		std::fstream add("EXPERT_FILE");
		add.open(EXPERT_FILE, std::fstream::out | std::fstream::app);
		//std::copy(sort_double_vector.begin(), sort_double_vector.end(), std::ostream_iterator<double>(add));
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		for (int i = 0; i < 6; i++) {
			
			add << goals[i] << std::endl;
			
		}
		for (int i = 0; i < 5; i++) {
			
			add << v[i] << std::endl;
		}
		add.close();
	}

	std::cout << "�������� �������� ���� �" <<maxIndex+1<<" �� ��� �����: "<<max << std::endl;
	
	std::sort(sort_double_vector.rbegin(), sort_double_vector.rend());
	std::cout << "�������������� �����" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout<< sort_double_vector[i] <<std::endl;
	}
	
	system("pause");
	
}
void Admin::showAim() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string line;
	const  std::string EXPERT_FILE = "C:\\Users\\Lenovo\\source\\repos\\BookshopMy\\BookshopMy\\Expert.txt";
	std::ifstream read(EXPERT_FILE, std::fstream::in);
	if (read.is_open())
	{
		while (!read.eof())
		{
			std::getline(read, line);
			std::cout << line << std::endl;
		}
		read.close();
	}
	system("pause");

	
}

void Admin::showInput()
{
	std::vector<BookForSale> soldItems;
	std::string LOG_FILE = "C:\\Users\\Lenovo\\source\\repos\\BookshopMy\\BookshopMy\\Log.txt";
	std::fstream read;
	read.open(LOG_FILE, std::fstream::in);
	if (!read.is_open())
	{
		read.open(LOG_FILE, std::fstream::in);
	}
	else {
		std::string buf;
		while (!read.eof())
		{
			buf.clear();
			getline(read, buf, '\n');
			if (buf.size() != 0)
			{
				char* dup = new char(strlen(buf.c_str()) + 1);
				dup = _strdup(buf.c_str());
				char* t = nullptr;
				std::string login = strtok_s(dup, "|", &t);
				std::string name = strtok_s(nullptr, "|", &t);
				std::string author = "";
				int amount = atoi(strtok_s(nullptr, "|", &t));
				double price = atof(strtok_s(nullptr, "|", &t)) / amount;

				Book book(name, author, price);
				BookForSale book4sale(book, amount);
				soldItems.push_back(book4sale);
			}
		}
		int sum = 0;
		if (!soldItems.empty()) {
			for (auto item : soldItems)
			{
				sum += (item.getBook().getPrice() * item.getAmount());
			}
			std::cout << "����� ������� ��������� : " << sum << "������" << std::endl;
		}
		system("pause");
	}

	
}