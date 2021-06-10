#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qLineedit.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qformlayout.h>
#include <QSlider>

#include "Service.h"
#include "Produs.h"
#include "MyTableModel.h"

using namespace std;


class WidgetTableGUI : public QWidget {
private:
	Service& service;
	QFormLayout* qVlayout = new QFormLayout;
	QTableWidget* tableWidget;

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
	WidgetTableGUI(Service& service) :service{ service } {
		initGUI();
		connectSignalsSlots();
		reloadList(service.sorteazaCrescator());
	}
};