#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Repository.h"
#include "Produs.h"
#include "Validator.h"
#include "Observer.h"

using namespace std;


class Service : public IObservable {
private:
	Repository& repo;
	Validator& validator;

public:
	Service(Repository& repo, Validator& validator) : repo{ repo }, validator{ validator }{}

	vector<Produs> getAll();

	void save(int id, string nume, string tip, float pret);

	vector<Produs> sorteazaCrescator();

	int getVocale(Produs p);

	unordered_map<string, int> statistici();

	Produs findOne(int id);

	void deleteProdus(int id);
};
