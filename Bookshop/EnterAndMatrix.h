#pragma once
#pragma once
#include "iostream"
#include <vector>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)


using namespace std;

class Enter {
public:
	char login[20];
	char password[20];
public:
	Enter()
	{
		login[0] = NULL;
		password[0] = NULL;
	}
	friend ofstream &operator <<(ofstream &a, Enter &b);
	friend ifstream &operator >>(ifstream &a, Enter &b);
	~Enter() {}
};

