#pragma once
#include <iostream>
#include <string>
using namespace std;

class Produs {
private:
	int id;
	string nume;
	string tip;
	float pret;

public:
	Produs(int id, const string& nume, const string& tip, float pret) : id{ id }, nume{ nume }, tip{ tip }, pret{ pret }{}

	int getId() const {
		return id;
	}

	string getNume() const  {
		return nume;
	}

	string getTip() const {
		return tip;
	}

	float getPret() const {
		return pret;
	}
};