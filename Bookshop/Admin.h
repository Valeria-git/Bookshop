#pragma once
#include "Catalog.h"
#include "User.h"

class Admin :
	public User
{
	Catalog assortment;
public:
	Admin(std::string email, std::string password);
	~Admin();
	void addExpert();
	void addBook();
	void showAim();
	void findBook() override;
	void deleteBook();
	void readLog();
	void showInput();
};

