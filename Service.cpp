#include "Service.h"
#include <algorithm>
#include <functional>

vector<Produs> Service::getAll() {
	return repo.getAll();
}

void Service::save(int id, string nume, string tip, float pret) {
	Produs p{ id, nume, tip, pret };
	validator.validate(p);
	repo.save(p);
	IObservable::notify();
}

vector<Produs> Service::sorteazaCrescator() {
	vector<Produs> produse = repo.getAll();

	sort(produse.begin(), produse.end(), [](Produs& p1, Produs& p2) {return p1.getPret() < p2.getPret(); });
	return produse;
}

int Service::getVocale(Produs p) {
	int fr = 0;
	string vocale = "aeiou";
	for (const auto& l : p.getNume()) {
		if (vocale.find(l) != string::npos) {
			fr++;
		}
	}
	return fr;
}

unordered_map<string, int> Service::statistici() {
	unordered_map<string, int> map;
	for (auto& p : repo.getAll()) {
		if (map.find(p.getTip()) != map.end()) {
			map[p.getTip()]++;
		}
		else {
			map[p.getTip()] = 1;
		}
	}
	return map;
}

Produs Service::findOne(int id) {
	if (id < 0) {
		throw exception("Produsul cu id-ul cautat nu exista!");
	}
	else {
		return repo.findOne(id);
	}
}

void Service::deleteProdus(int id) {
	repo.deleteProdus(id);
}