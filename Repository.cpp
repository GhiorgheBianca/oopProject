#include "Repository.h"
#include <fstream>
#include <sstream>

vector<Produs> Repository::getAll() {
	return produse;
}

int Repository::size() {
	return produse.size();
}

void Repository::save(Produs produs) {
	if (!exists(produs.getId())) {
		produse.push_back(produs);
		writeToFile();
	}
	else {
		throw exception("Produs deja existent!");
	}
}

bool Repository::exists(int id) {
	for (Produs p : produse) {
		if (p.getId() == id) {
			return true;
		}
	}
	return false;
}

void Repository::readFromFile() {
	ifstream fin(filename);

	if (!fin.is_open()) {
		throw exception("Nu s-a putut deschide fisierul!\n");
	}
	else {
		string line;
		while (getline(fin, line)) {
			string delimitator = ",";
			size_t poz = 0;
			string element_nr;

			int id = 0;
			string nume, tip;
			float pret;

			poz = line.find(delimitator);
			element_nr = line.substr(0, poz);
			id = stoi(element_nr, nullptr); //TRANSFORMAM DIN STRING IN INT
			line.erase(0, poz + 1);

			poz = line.find(delimitator);
			nume = line.substr(0, poz);
			line.erase(0, poz + 1);

			poz = line.find(delimitator);
			tip = line.substr(0, poz);
			line.erase(0, poz + 1);

			poz = line.find(delimitator);
			element_nr = line.substr(0, poz);
			pret = stof(element_nr, nullptr); //TRANSFORMAM DIN STRING IN FLOAT
			line.erase(0, poz + 1);

			Produs p{ id, nume, tip, pret };
			save(p);
		}
		fin.close();
	}
}

void Repository::writeToFile() {
	ofstream fout(filename);

	for (Produs p : produse) {
		fout << p.getId() << "," << p.getNume() << "," << p.getTip() << "," << p.getPret() << "\n";
	}

	fout.close();
}

void Repository::deleteDataFromFile() {
	ofstream fout(filename);

	fout << "";

	fout.close();
}


Produs Repository::findOne(int id) {
	for (Produs p : produse) {
		if (p.getId() == id) {
			return p;
		}
	}
	throw exception("Produsul cu id-ul cautat nu exista!");
}

void Repository::deleteProdus(int id) {
	int poz = 0;
	for (Produs p : produse) {
		if (p.getId() == id) {
			break;
		}
		poz++;
	}
	if (poz < produse.size()) {
		produse.erase(produse.begin() + poz);
		writeToFile();
	}
	else {
		throw exception("Nu exista produsul!");
	}
}