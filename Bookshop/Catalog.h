#pragma once
#include <sstream>
#include <fstream>
#include <vector>
#include "BookForSale.h"
#include <iomanip>
class Catalog
{
	std::vector<BookForSale> assortment;
	const  std::string BOOKS_FILE = "C:\\Users\\Lenovo\\source\\repos\\BookshopMy\\BookshopMy\\Books.txt";
	const  std::string EXPERT_FILE = "C:\\Users\\Lenovo\\source\\repos\\BookshopMy\\BookshopMy\\Expert.txt";
public:
	void addToExpert(double o1, double o2, double o3, double o4);
	void readExpert();
	void clearAssortment();
	bool checkAvailability(Book book, int amount);
	void substractOrder(std::vector<BookForSale> book);
	void substractOrder(BookForSale book);
	void deleteBook(std::string name, std::string author);

	void readCatalog();
	void addToCatalog(BookForSale book);
	std::vector<BookForSale> getAssortment();
};

