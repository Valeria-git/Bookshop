#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "Catalog.h"
#include "UserBase.h"
#include "Admin.h"
#include "Buyer.h"
#include "Cart.h"
#include "Bank.h"
class Bookshop
{
	std::map<std::string, Cart&> carts;
	Catalog catalog;
	UserBase accounts;
	Bank bank;
	bool enoughMoney(Buyer buyer, double totalPurchaseValue);

public:
	void addToCart(Book book, int amount, Buyer buyer, Cart* cart);
	void showBuyersCart(Buyer buyer);
	void addToLog(Buyer buyer, std::vector<BookForSale> order);
	int showAssortment(int mode, Buyer buyer, Cart *cart); // 1 - ���������� �� �������� �����, 2 - ���������� �� ������, 3 - �� ���������
	void buyBooks(Buyer buyer);
	Bookshop();
	~Bookshop();
	Buyer* signUp();
	User* signIn();
};

