#include "QsTreeShow.h"



QsTreeShow::QsTreeShow(std::vector<QsTree*> myTrees)
{
	setupUi(this);
	connect(pushButton, SIGNAL(clicked()), this, SLOT(exportTree()));
	QStandardItemModel* model = new QStandardItemModel();
	model->setColumnCount(6);
	model->setHeaderData(0, Qt::Horizontal, QStringLiteral("X×ø±ê"));
	model->setHeaderData(1, Qt::Horizontal, QStringLiteral("Y×ø±ê"));
	model->setHeaderData(2, Qt::Horizontal, QStringLiteral("Z×ø±ê"));
	model->setHeaderData(3, Qt::Horizontal, QStringLiteral("Ê÷¸ß/m"));
	model->setHeaderData(4, Qt::Horizontal, QStringLiteral("ÐØ¾¶/cm"));
	model->setHeaderData(5, Qt::Horizontal, QStringLiteral("¹Ú·ù/m"));
	this->tableView->setModel(model);
	this->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
	this->tableView->setColumnWidth(0, 100);
	this->tableView->setColumnWidth(1, 100);
	this->tableView->setColumnWidth(2, 100);
	this->tableView->setColumnWidth(3, 75);
	this->tableView->setColumnWidth(4, 75);
	this->tableView->setColumnWidth(5, 75);
	for (int i = 0; i < myTrees.size(); i++)
	{
		model->setItem(i, 0, new QStandardItem(QString::number(myTrees[i]->X,'f',3)));
		model->setItem(i, 1, new QStandardItem(QString::number(myTrees[i]->Y, 'f', 3)));
		model->setItem(i, 2, new QStandardItem(QString::number(myTrees[i]->Z, 'f', 3)));
		model->setItem(i, 3, new QStandardItem(QString::number(myTrees[i]->H, 'f', 1)));
		model->setItem(i, 4, new QStandardItem(QString::number(myTrees[i]->D, 'f', 1)));
		model->setItem(i, 5, new QStandardItem(QString::number(myTrees[i]->C, 'f', 1)));
		model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
		model->item(i, 1)->setTextAlignment(Qt::AlignCenter);
		model->item(i, 2)->setTextAlignment(Qt::AlignCenter);
		model->item(i, 3)->setTextAlignment(Qt::AlignCenter);
		model->item(i, 4)->setTextAlignment(Qt::AlignCenter);
		model->item(i, 5)->setTextAlignment(Qt::AlignCenter);

	}
}


QsTreeShow::~QsTreeShow()
{
}


void QsTreeShow::exportTree()
{

}
