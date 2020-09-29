#include "Menu.h"
#include "Windows.h"


void Menu::buyerMode(Buyer* b, Bookshop* shop)
{
	system("cls");
	Buyer buyer = *b;
	int buyerNum = 0;

	std::string author, name;
	double price;
	int amount;
	bool existence = false, largerAmount = false;;
	std::vector<BookForSale> assortment;
	Catalog* catalog = new Catalog();
	Cart* cart = new Cart();
	while (true)
	{

		buyerNum = manageInputBuyerMenu();
		switch (buyerNum)
		{
		case 1:
		{
			system("cls");
			int mode = 0;
			while (mode != 5)
				mode = shop->showAssortment(mode, *b, cart);
			break;
		}
		case 2:
			system("cls");
			b->findBook();
			break;
		case 3:
			system("cls");
			shop->showBuyersCart(buyer);
			system("pause");
			break;
		case 4:
			shop->buyBooks(buyer);
			break;
		case 5:
			system("cls");
			return;
		default:
			break;
		}
	}

}

void Menu::adminMode(Admin* admin)
{
	system("cls");
	int adminNum;
	while (true)
	{
		adminNum = manageInputAdminMenu();
		switch (adminNum)
		{
		case 1:

			admin->findBook();
			break;
		case 2:
			system("cls");
			admin->addBook();
			break;
		case 3:
			system("cls");
			admin->deleteBook();
			break;
		case 5:
			system("cls");
			admin->showInput();
			break;
		case 4:
			system("cls");
			admin->readLog();
			break;
		case 6:
			system("cls");
			///////////////////
			admin->addExpert();
			break;
		case 7:
			system("cls");
			admin->showAim();
			break;
		case 8:
			system("cls");
			return;
		default:
			break;

		}
	}
}

int Menu::manageInputAdminMenu()
{
	int key = 1, code;
	do {
		system("cls");
		std::cout << "\n\t\t     |     �����������������     |     " << std::endl;
		if (key == 1)
			std::cout << "\t-> ����� ������� �� ��������" << std::endl;
		else
			std::cout << "\t����� ������� �� ��������" << std::endl;
		if (key == 2)
			std::cout << "\t-> �������� ����� ������� ��� ��������� ���������� ������������" << std::endl;
		else
			std::cout << "\t�������� ����� ������� ��� ��������� ���������� ������������" << std::endl;
		if (key == 3)
			std::cout << "\t-> ������� ������������ �������" << std::endl;
		else
			std::cout << "\t������� ������������ �������" << std::endl;
		if (key == 4)
			std::cout << "\t-> ������� ��� ����������� �������" << std::endl;
		else
			std::cout << "\t������� ��� ����������� �������" << std::endl;
		if (key == 5)
			std::cout << "\t-> ������� ����� �������" << std::endl;
		else
			std::cout << "\t������� ����� �������" << std::endl;
		if (key == 6)
			std::cout << "\t-> �������� ����" << std::endl;
		else
			std::cout << "\t�������� ����" << std::endl;
		if (key == 7)
			std::cout << "\t-> ������� ������������ ����" << std::endl;
		else
			std::cout << "\t������� ������������ ����" << std::endl;
		if (key == 8)
			std::cout << "\t-> � ������� ����" << std::endl;
		else
			std::cout << "\t� ������� ����" << std::endl;
		code = _getch();
		if (code == 80)
		{
			key++;
			if (key > 8)
				key = 1;
		}
		if (code == 72)
		{
			key--;
			if (key < 1)
				key = 8;
		}
	} while (code != 13);
	return key;
}

int Menu::manageInputBuyerMenu()
{
	int key = 1, code;
	do {
		system("cls");
		std::cout << "\n\t\t      |     ����������     |     " << std::endl;
		if (key == 1)
			std::cout << "\t-> �������� �������" << std::endl;
		else
			std::cout << "\t�������� �������" << std::endl;
		if (key == 2)
			std::cout << "\t-> ����� �����" << std::endl;
		else
			std::cout << "\t����� �����" << std::endl;
		if (key == 3)
			std::cout << "\t-> ����������� �������" << std::endl;
		else
			std::cout << "\t����������� �������" << std::endl;
		if (key == 4)
			std::cout << "\t-> �������� �������" << std::endl;
		else
			std::cout << "\t�������� �������" << std::endl;
		if (key == 5)
			std::cout << "\t-> � ������� ����" << std::endl;
		else
			std::cout << "\t� ������� ����" << std::endl;
		code = _getch();
		if (code == 80)
		{
			key++;
			if (key > 5)
				key = 1;
		}
		if (code == 72)
		{
			key--;
			if (key < 1)
				key = 5;
		}
	} while (code != 13);
	return key;
}


Menu::Menu()
{
}


Menu::~Menu()
{
}
