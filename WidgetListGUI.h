#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qLineedit.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qformlayout.h>
#include <QSlider>
#include <QAbstractListModel>
#include <QListView>

#include "MylistModel.h"
#include "Service.h"
#include "Produs.h"

class WidgetListGUI : public QWidget {
private:
	Service& service;
	int idCurent = 0;
	QListWidget* listWidget;
	QHBoxLayout* lyMain;
	QLineEdit* idLineEdit;
	QLineEdit* numeLineEdit;
	QLineEdit* tipLineEdit;
	QLineEdit* pretLineEdit;
	QPushButton* deleteButton;

	void initGUI();
	void connectSignalsSlots();
	void reloadList(vector<Produs> produse);
	void deleteProdus();

public:
		WidgetListGUI(Service& service) : service{ service } {
		initGUI();
		reloadList(service.sorteazaCrescator());
		connectSignalsSlots();
	}
};

