#include "Bookshop.h"
#include <algorithm>
#include <conio.h>

Bookshop::Bookshop()
{

}


Bookshop::~Bookshop()
{
}



User* Bookshop::signIn()
{
	std::string email, password;
	std::cout << "������� ��� email" << std::endl;
	std::cin >> email;
	std::cout << "������� ������" << std::endl;
	std::cin >> password;
	accounts.readAccounts();
	std::vector<User*> accs;
	accs = accounts.getAccounts();
	for (auto acc : accs)
	{
		if (acc->getEmail() == email && acc->getPassword() == password)
		{
			if (acc->getUserType() == "admin")
				return new Admin(email, password);
			else if (acc->getUserType() == "buyer")
			{

				return new Buyer(email, password, bank.getPayment(email));
			}
			else
				continue;
		}
	}
	return NULL;
}

Buyer* Bookshop::signUp()
{
	std::string email, password;
	std::cout << "Enter your email" << std::endl;
	std::cin >> email;
	std::cout << "Enter password" << std::endl;
	std::cin >> password;
	accounts.readAccounts();
	std::vector<User*> accs;
	accs = accounts.getAccounts();
	for (auto acc : accs)
	{
		if (acc->getEmail() == email && acc->getPassword() == password)
		{
			std::cout << "������������ � ������ ������� ��� ����������" << std::endl;
			return NULL;
		}
	}
	CreditCard startCard(100);
	Buyer* newBuyer = new Buyer(email, password, startCard);
	accounts.addToUserBase(newBuyer);
	bank.addToBankBase(*newBuyer);
	bank.clearBankData();
	return newBuyer;
}
// �


int Bookshop::showAssortment(int mode, Buyer buyer, Cart *cart)
{
	catalog.readCatalog();
	std::vector<BookForSale> items;
	items = catalog.getAssortment();
	if (mode == 1)
		std::sort(items.begin(), items.end(), [](BookForSale book1, BookForSale book2) {return book1.getBook().getName() < book2.getBook().getName(); });
	else if (mode == 2)
		std::sort(items.begin(), items.end(), [](BookForSale book1, BookForSale book2) {return book1.getBook().getAuthor() < book2.getBook().getAuthor(); });
	else if (mode == 3)
		std::sort(items.begin(), items.end(), [](BookForSale book1, BookForSale book2) {return book1.getBook().getPrice() < book2.getBook().getPrice(); });
	else if (mode == 4)
		std::sort(items.begin(), items.end(), [](BookForSale book1, BookForSale book2) {return book1.getBook().getPrice() > book2.getBook().getPrice(); });

	int key = 0, code;
	int newMode = 5;
	do
	{
		int i = 0;
		system("cls");
		std::cout << "   |" << std::setw(41) << "        ������������ ������       " << "|" << std::setw(26) << "           �����          " << "|" << std::setw(12) << " ��������� " <<
			" |" << std::setw(9) << "���-��" << "|" << std::endl;
		std::cout << "   |" << "_________________________________________" << "|" << "__________________________" << "|" << "_____________" << "|" << "_________" << "|" << std::endl;
		for (i; i < items.size();)
		{
			if (i == key)
			{
				std::cout << "-> |" << std::setw(42) << items[i].getBook().getName() + "|" << std::setw(27) << items[i].getBook().getAuthor() + "|" << std::setw(14) <<
					std::to_string(items[i].getBook().getPrice()) + "�|" << std::setw(7) << std::to_string(items[i].getAmount()) << "��|" << '\n';
			}
			else
				std::cout << "   |" << std::setw(42) << items[i].getBook().getName() + "|" << std::setw(27) << items[i].getBook().getAuthor() + "|" << std::setw(14) <<
				std::to_string(items[i].getBook().getPrice()) + "�|" << std::setw(7) << std::to_string(items[i].getAmount()) << "��|" << '\n';
			i++;
		}
		std::cout << "   |" << "_________________________________________" << "|" << "__________________________" << "|" << "_____________" << "|" << "_________" << "|" << std::endl;

		if (key == items.size())
		{
			newMode = 1;
			std::cout << "\t-> �� ������������ ������ " << std::endl;
		}
		else
			std::cout << "�� ������������ ������" << std::endl;
		if (key == items.size() + 1)
		{
			newMode = 2;
			std::cout << "\t-> �� ������" << std::endl;
		}
		else
			std::cout << "�� ������" << std::endl;
		if (key == items.size() + 2)
		{
			newMode = 3;
			std::cout << "\t-> �� ���� (������� �������)" << std::endl;
		}
		else
			std::cout << "�� ���� (������� �������)" << std::endl;
		if (key == items.size() + 3)
		{
			newMode = 4;
			std::cout << "\t-> �� ���� (������� �������)" << std::endl;
		}
		else
			std::cout << "�� ���� (������� �������)" << std::endl;
		code = _getch();
		if (code == 80)
		{
			key++;
			if (key > items.size() + 3)
				key = 0;
		}
		if (code == 72)
		{
			key--;
			if (key < 0)
				key = items.size() + 3;
		}
		if (code == 13 && key < items.size())
		{
			int amount;
			std::cout << "������� �������� ���-��" << std::endl;
			std::cin >> amount;
			if (items[key].getAmount() >= amount)
				addToCart(items[key].getBook(), amount, buyer, cart);
			else
			{
				std::cout << "��������� ���-�� ������ ���������� �� ������" << std::endl;
				system("pause");
			}
		}
		if (code == 13 && key >= items.size())
		{
			catalog.clearAssortment();
			return newMode;
		}


	} while (code != 27);
	catalog.clearAssortment();
	return newMode;
}

void Bookshop::buyBooks(Buyer buyer)
{
	if (!carts.empty())
	{
		Cart cart = carts.find(buyer.getEmail())->second;
		if (!cart.getOrder().empty())
		{
			if (enoughMoney(buyer, cart.sumUp()))
			{
				buyer.pay(cart.sumUp()); // ��������� ������ � �����
				catalog.substractOrder(cart.getOrder());
				bank.clearBankData();
				bank.substractBalance(buyer.getEmail(), cart.sumUp());// ��������� ����� ��������� ����� �� ������
				addToLog(buyer, cart.getOrder());
				cart.getOrder().clear();
				std::cout << "������� ��������� " << cart.sumUp() << " ������ ������� � ������ �����" << std::endl;
				system("pause");
			}
			else {
				cart.getOrder().clear();
				std::cout << "������������ �������" << std::endl;
				system("pause");
			}
		}
		else
		{
			std::cout << "������� �����" << std::endl;
			system("pause");
		}
	}
	else
	{
		std::cout << "������� �����" << std::endl;
		system("pause");
	}

}

bool Bookshop::enoughMoney(Buyer buyer, double totalPurchaseValue)
{
	if (buyer.getPayment().getBalance() >= totalPurchaseValue)
		return true;
	return false;

}

void Bookshop::addToCart(Book book, int amount, Buyer buyer, Cart* cart)
{
	this->carts.emplace(buyer.getEmail(), *cart);
	if (catalog.checkAvailability(book, amount))
	{
		cart->addItem(book, amount);
		std::cout << "\"" << book.getName() << "\"" << " ������� ��������� � �������" << std::endl;
		system("pause");
	}
	else
		std::cout << "���������� ��������� �������" << std::endl;
}

void Bookshop::showBuyersCart(Buyer buyer)
{

	if (!carts.empty())
	{
		Cart cart = carts.find(buyer.getEmail())->second;
		std::vector<BookForSale> items;
		items = cart.getOrder();
		if (!items.empty())
		{
			double total = 0;
			std::cout << "   |" << std::setw(41) << "        ������������ ������       " << "|" << std::setw(26) << "           �����          " << "|" << std::setw(12) << " ��������� " <<
				" |" << std::setw(9) << "���-��" << "|" << std::endl;
			std::cout << "   |" << "_________________________________________" << "|" << "__________________________" << "|" << "_____________" << "|" << "_________" << "|" << std::endl;
			for (auto item : items)
			{
				total += (item.getBook().getPrice() * item.getAmount());
				std::cout << "   |" << std::setw(42) << item.getBook().getName() + "|" << std::setw(27) << item.getBook().getAuthor() + "|" << std::setw(14) <<
					std::to_string(item.getBook().getPrice()) + "�|" << std::setw(7) << std::to_string(item.getAmount()) << "��|" << '\n';
			}
			std::cout << "����� : " << total << "�" << std::endl;;
		}
		else
			std::cout << "������� �����" << std::endl;
	}
	else
		std::cout << "������� �����" << std::endl;
}


void Bookshop::addToLog(Buyer buyer, std::vector<BookForSale> order)
{

	std::string LOG_FILE = "C:\\Users\\Lenovo\\source\\repos\\BookshopMy\\BookshopMy\\Log.txt";
	std::fstream add;
	add.open(LOG_FILE.c_str(), std::fstream::out | std::fstream::app);
	for (auto item : order)
	{
		add << buyer.getEmail() << "|" << item.getBook().getName() << "|" << item.getAmount() << "|"
			<< item.getBook().getPrice()*item.getAmount() << '\n';
	}
	add.close();

}