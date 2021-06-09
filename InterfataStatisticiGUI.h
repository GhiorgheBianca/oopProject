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
#include <QLabel>

#include "Service.h"
#include "Produs.h"
#include "MyTableModel.h"
#include <unordered_map>
#include "Observer.h"

using namespace std;


class InterfataStatisticiGUI : public QWidget, public IObserver {
private:
	Service& service;
	string tip;
	QVBoxLayout* l = new QVBoxLayout;
	QLabel* label = new QLabel;

public:
	InterfataStatisticiGUI(Service& service, string tip) :service{ service }, tip{tip} {
		unordered_map<string, int> map = service.statistici();
		setLayout(l);
		label->setText(QString::number(map[tip]));
		l->addWidget(label);
		setWindowTitle(QString::fromStdString(tip));
		service.addObserver(this);
	}

	void IObserver::update() override{
		unordered_map<string, int> map = service.statistici();
		label->setText(QString::number(map[tip]));
	}

	~InterfataStatisticiGUI() {
		service.removeObserver(this);
	}
};