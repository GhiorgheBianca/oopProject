#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Produs.h"
using namespace std;

class Repository {
private:
	vector<Produs> produse;
	string filename;

public:
	Repository(string filename) : filename{ filename } {
		readFromFile();
	}

	vector<Produs> getAll();

	int size();

	void save(Produs produs);

	bool exists(int id);

	void readFromFile();

	void writeToFile();

	void deleteDataFromFile();

	Produs findOne(int id);

	void deleteProdus(int id);

};
