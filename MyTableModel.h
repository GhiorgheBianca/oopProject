#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Produs.h"
#include "Service.h"

using namespace std;

class MyTableModel : public QAbstractTableModel {
private:
	vector<Produs> produse;
	Service& service;
	bool flag = false;
public:
	MyTableModel(const vector<Produs>& produse, Service& service) : produse{ produse }, service{service} {}

	int rowCount(const QModelIndex& parent = QModelIndex())const override {
		return produse.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	void setFlag(bool value) {
		flag = value;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole())const override {
		if (role == Qt::TextColorRole) {
			Produs produs = produse[index.row()];
			if (produs.getPret() <= 50 && flag) {
				return QBrush{ Qt::red };
			}
		}

		if (role == Qt::DisplayRole()) {
			Produs produs = produse[index.row()];
			if (index.column() == 0) {
				return QString::number(produs.getId());
			}

			if (index.column() == 1) {
				return QString::fromStdString(produs.getNume());
			}

			if (index.column() == 2) {
				return QString::fromStdString(produs.getTip());
			}

			if (index.column() == 3) {
				return QString::number(produs.getPret());
			}

			if (index.column() == 4) {
				return QString::number(service.getVocale(produs));
			}
		}
		return QVariant{};
	}

	void setProduse(const vector<Produs> products) {
		this->produse = products;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}

	void refresh() {
		emit layoutChanged();
	}
};
