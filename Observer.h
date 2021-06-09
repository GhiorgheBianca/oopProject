#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Produs.h"
using namespace std;

class IObserver {
public:
	virtual void update() = 0;
};

class IObservable {
private:
	vector<IObserver*> clients;
public:
	void addObserver(IObserver* obs) {
		clients.push_back(obs);
	}

	void removeObserver(IObserver* obs) {
		clients.erase(remove(clients.begin(), clients.end(), obs), clients.end());
	}

	void notify() {
		for (auto& client : clients) {
			client->update();
		}
	}

};
