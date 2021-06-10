#include "ViewListGUI.h"
#include <QString>
#include <QMessageBox>

void ViewListGUI::initGUI() {
	lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	listView = new QListView;
	
	deleteButton = new QPushButton{ "delete" };

	idLineEdit = new QLineEdit;
	numeLineEdit = new QLineEdit;
	tipLineEdit = new QLineEdit;
	pretLineEdit = new QLineEdit;
	lyMain->addWidget(listView);
	lyMain->addWidget(idLineEdit);
	lyMain->addWidget(numeLineEdit);
	lyMain->addWidget(tipLineEdit);
	lyMain->addWidget(pretLineEdit);
	lyMain->addWidget(deleteButton);
}

void ViewListGUI::connectSignalsSlots() {
	QObject::connect(listView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		
		if (listView->selectionModel()->selectedIndexes().isEmpty()) {
			return;
		}
		auto selectedIndex = listView->selectionModel()->selectedIndexes().at(0);
		QString line = selectedIndex.data(Qt::DisplayRole).toString();
		idCurent = selectedIndex.data(Qt::UserRole).toInt();
		Produs p = service.findOne(idCurent);

		idLineEdit->setText(QString::number(idCurent));
		numeLineEdit->setText(QString::fromStdString(p.getNume()));
		tipLineEdit->setText(QString::fromStdString(p.getTip()));
		pretLineEdit->setText(QString::number(p.getPret()));
		});

	QObject::connect(deleteButton, &QPushButton::clicked, this, &ViewListGUI::deleteProdus);
}

void ViewListGUI::reloadList(vector<Produs> produse) {
	model = new MyListModel(produse);
	listView->setModel(model);
}

void ViewListGUI::deleteProdus() {
	try {

		if (listView->selectionModel()->selectedIndexes().isEmpty()) {
			throw exception("Nu ati selectat nimic!");
		}
		auto selectedIndex = listView->selectionModel()->selectedIndexes().at(0);
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