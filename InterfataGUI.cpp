#include "InterfataGUI.h"
#include <qmessagebox.h>

void InterfataGUI::initGUI() {
	setLayout(qVlayout);
	
	tableView = new QTableView;
	qVlayout->addWidget(tableView);

	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	idLineEdit = new QLineEdit("");
	numeLineEdit = new QLineEdit("");
	tipLineEdit = new QLineEdit("");
	pretLineEdit = new QLineEdit("");

	formLDetalii->addRow("id", idLineEdit);
	formLDetalii->addRow("nume", numeLineEdit);
	formLDetalii->addRow("tip", tipLineEdit);
	formLDetalii->addRow("pret", pretLineEdit);

	saveButton = new QPushButton("Save");
	formLDetalii->addWidget(saveButton);

	qSlider = new QSlider;
	formLDetalii->addWidget(qSlider);

	qVlayout->addWidget(widDetalii);
}

void InterfataGUI::connectSignalsSlots() {
	QObject::connect(saveButton, &QPushButton::clicked, this, &InterfataGUI::saveProdus);
	QObject::connect(qSlider, &QSlider::valueChanged, this, &InterfataGUI::filtreazaSlider);
	QObject::connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() { 
		if (tableView->selectionModel()->selectedIndexes().isEmpty()) {
			return;
		}
		int selectedRow = tableView->selectionModel()->selectedIndexes().at(0).row();
		auto cell0index = tableView->model()->index(selectedRow, 0);
		auto cell1index = tableView->model()->index(selectedRow, 1);
		auto cell2index = tableView->model()->index(selectedRow, 2);
		auto cell3index = tableView->model()->index(selectedRow, 3);
		auto cell0value = tableView->model()->data(cell0index, Qt::DisplayRole).toString();
		auto cell1value = tableView->model()->data(cell1index, Qt::DisplayRole).toString();
		auto cell2value = tableView->model()->data(cell2index, Qt::DisplayRole).toString();
		auto cell3value = tableView->model()->data(cell3index, Qt::DisplayRole).toString();

		idLineEdit->setText(cell0value);
		numeLineEdit->setText(cell1value);
		tipLineEdit->setText(cell2value);
		pretLineEdit->setText(cell3value);
		});
}

void InterfataGUI::reloadList(vector<Produs>& produse) {
	model->setProduse(produse);
	model->refresh();
}

void InterfataGUI::saveProdus() {
	try {
		int id = idLineEdit->text().toInt();
		string nume = numeLineEdit->text().toStdString();
		string tip = tipLineEdit->text().toStdString();
		float pret = pretLineEdit->text().toFloat();
		
		service.save(id, nume, tip, pret);
		reloadList(service.sorteazaCrescator());
	}
	catch (exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
	}

}

/*
void InterfataGUI::filtreazaSlider() {
	int value = qSlider->value();
	if (value > 0) {
		for (int i = 0; i < service.getAll().size(); i++) {
			auto index = model->index(i, 3);
			QString data = model->data(index).toString();
			string text = data.toLocal8Bit().constData();
			//string text1 = data.toStdString();
			float pret = stof(text);

			if (pret <= 50) {
				model->setData(index, QColor(qrand() % 255, qrand() % 255, qrand() % 255), Qt::BackgroundRole);
			}
		}
	}
}
*/

void InterfataGUI::filtreazaSlider() {
	int value = qSlider->value();
	if (value > 50) {
		model->setFlag(true);
	}
	else {
		model->setFlag(false);
	}
	reloadList(service.sorteazaCrescator());
}