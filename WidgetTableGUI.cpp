#include "WidgetTableGUI.h"
#include <qmessagebox.h>

void WidgetTableGUI::initGUI() {
	setLayout(qVlayout);

	tableWidget = new QTableWidget{ 0,5 };
	tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Id"));
	tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Nume"));
	tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Tip"));
	tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Pret"));
	tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Nr vocale"));
	qVlayout->addWidget(tableWidget);

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

void WidgetTableGUI::connectSignalsSlots() {
	QObject::connect(saveButton, &QPushButton::clicked, this, &WidgetTableGUI::saveProdus);
	QObject::connect(qSlider, &QSlider::valueChanged, this, &WidgetTableGUI::filtreazaSlider);
	QObject::connect(tableWidget, &QTableWidget::itemSelectionChanged, [&]() {
		auto selected_elem = tableWidget->selectedItems();
		if (!selected_elem.isEmpty()) {
			int nr_row = tableWidget->selectedItems().at(0)->row();
			auto id = tableWidget->item(nr_row, 0)->data(Qt::DisplayRole).toInt();
			Produs p = service.findOne(id);

			idLineEdit->setText(QString::number(id));
			numeLineEdit->setText(QString::fromStdString(p.getNume()));
			tipLineEdit->setText(QString::fromStdString(p.getTip()));
			pretLineEdit->setText(QString::number(p.getPret()));
		}
		});
}

void WidgetTableGUI::reloadList(vector<Produs>& produse) {
	tableWidget->clear();
	tableWidget->setRowCount(0);

	for (const auto& produs : produse) {
		tableWidget->insertRow(tableWidget->rowCount());
		tableWidget->setItem(tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::number(produs.getId())));
		tableWidget->setItem(tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(produs.getNume())));
		tableWidget->setItem(tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString::fromStdString(produs.getTip())));
		tableWidget->setItem(tableWidget->rowCount() - 1, 3, new QTableWidgetItem(QString::number(produs.getPret())));
		tableWidget->setItem(tableWidget->rowCount() - 1, 4, new QTableWidgetItem(QString::number(service.getVocale(produs))));
	}
}

void WidgetTableGUI::saveProdus() {
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
void WidgetTableGUI::filtreazaSlider() {
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

void WidgetTableGUI::filtreazaSlider() {
	int value = qSlider->value();
	if (value > 50) {
		for (int i = 0; i < tableWidget->rowCount(); i++) {
			//auto data = tableWidget->item(i, 3)->text();
			auto id = tableWidget->item(i, 0)->data(Qt::DisplayRole).toInt();
			Produs p = service.findOne(id);
			//if (tableWidget->item(i, 0)->text().toFloat() < 50) {
			if (p.getPret() < 50) {
				for (int j = 0; j < tableWidget->columnCount(); j++) {
					QTableWidgetItem* cell = tableWidget->item(i, j);
					//cell->setBackground(QBrush{ Qt::red, Qt::SolidPattern });
					cell->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
				}
			}
		}
	}
	else {
		for (int i = 0; i < tableWidget->rowCount(); i++) {
			if (tableWidget->item(i, 3)->data(Qt::DisplayRole).toFloat() > 50) {
				for (int j = 0; j < tableWidget->columnCount(); j++) {
					auto cell = tableWidget->item(i, j);
					cell->setBackground(QBrush{ Qt::white, Qt::SolidPattern });
				}

			}
		}
	}
	reloadList(service.sorteazaCrescator());
}