#include "WidgetListGUI.h"
#include <QString>
#include <QMessageBox>

void WidgetListGUI::initGUI() {
	lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	listWidget = new QListWidget;

	deleteButton = new QPushButton{ "delete" };

	idLineEdit = new QLineEdit;
	numeLineEdit = new QLineEdit;
	tipLineEdit = new QLineEdit;
	pretLineEdit = new QLineEdit;
	lyMain->addWidget(listWidget);
	lyMain->addWidget(idLineEdit);
	lyMain->addWidget(numeLineEdit);
	lyMain->addWidget(tipLineEdit);
	lyMain->addWidget(pretLineEdit);
	lyMain->addWidget(deleteButton);
}

void WidgetListGUI::connectSignalsSlots() {
	QObject::connect(listWidget, &QListWidget::itemSelectionChanged, [&]() {
		
		int id = 0;
		auto selectedElem = listWidget->selectedItems();
		if (!selectedElem.isEmpty()) {
			auto selectedItem = selectedElem.at(0);
			idCurent = selectedItem->data(Qt::UserRole).toInt();
			Produs p = service.findOne(idCurent);

			idLineEdit->setText(QString::number(idCurent));
			numeLineEdit->setText(QString::fromStdString(p.getNume()));
			tipLineEdit->setText(QString::fromStdString(p.getTip()));
			pretLineEdit->setText(QString::number(p.getPret()));
		}

		});

	QObject::connect(deleteButton, &QPushButton::clicked, this, &WidgetListGUI::deleteProdus);
}

void WidgetListGUI::reloadList(vector<Produs> produse) {
	listWidget->clear();
	for (const auto& produs : produse) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(std::to_string(produs.getId()) + "," + produs.getNume() + "," + produs.getTip() + "," + std::to_string(produs.getPret())));
		item->setData(Qt::UserRole, produs.getId());
		listWidget->addItem(item);
	}
}

void WidgetListGUI::deleteProdus() {
	try {

		if (listWidget->selectionModel()->selectedIndexes().isEmpty()) {
			throw exception("Nu ati selectat nimic!");
		}
		auto selectedIndex = listWidget->selectionModel()->selectedIndexes().at(0);
		QString line = selectedIndex.data(Qt::DisplayRole).toString();
		idCurent = selectedIndex.data(Qt::UserRole).toInt();

		service.deleteProdus(idCurent);
		reloadList(service.sorteazaCrescator());
		connectSignalsSlots();
	}
	catch (exception& ex) {
		QMessageBox::warning(this, "warning", QString::fromStdString(ex.what()));
	}
}