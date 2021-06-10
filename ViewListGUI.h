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
#include <QListView>

#include "MylistModel.h"
#include "Service.h"
#include "Produs.h"

class ViewListGUI : public QWidget {
private:
	Service& service;
	int idCurent = 0;
	QListView* listView;
	MyListModel* model;
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
	ViewListGUI(Service& service) : service{ service } {
		initGUI();
		listView->setUniformItemSizes(true);
		//model = new MyListModel{ service.sorteazaCrescator()};
		//listView->setModel(model);
		reloadList(service.sorteazaCrescator());
		connectSignalsSlots();
	}
};

