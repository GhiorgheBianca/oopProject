#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qLineedit.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qformlayout.h>
#include <QSlider>
#include <QAbstractListModel>

#include "Service.h"
#include "Produs.h"

class MyListModel : public QAbstractListModel {
private:
	vector<Produs> produse;
public:
	MyListModel(const vector<Produs>& produse) : produse{ produse } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return produse.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			string textLine = std::to_string(produse[index.row()].getId()) + "," + produse[index.row()].getNume() + "," + produse[index.row()].getTip() + "," + std::to_string(produse[index.row()].getPret());
			return QString::fromStdString(textLine);
		}

		if (role == Qt::UserRole) {
			return QString::number(produse[index.row()].getId());
		}

		if (role == Qt::BackgroundRole) {
			if (produse[index.row()].getTip() == "mancare") {
				return QColor(Qt::red);
			}
		}
		return QVariant{};
	}
};