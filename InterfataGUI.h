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

#include "Service.h"
#include "Produs.h"
#include "MyTableModel.h"

using namespace std;


class InterfataGUI : public QWidget {
private:
	Service& service;
	QFormLayout* qVlayout = new QFormLayout;
	QTableView* tableView;
	MyTableModel* model;

	QLineEdit* idLineEdit;
	QLineEdit* numeLineEdit;
	QLineEdit* tipLineEdit;
	QLineEdit* pretLineEdit;

	QPushButton* saveButton;

	QSlider* qSlider;


	void initGUI();
	void connectSignalsSlots();
	void reloadList(vector<Produs>& produse);
	void saveProdus();
	void filtreazaSlider();

public:
	InterfataGUI(Service& service) :service{ service } {
		initGUI();
		model = new MyTableModel{ service.sorteazaCrescator(), service };
		tableView->setModel(model);
		connectSignalsSlots();
		reloadList(service.sorteazaCrescator());
	}
};