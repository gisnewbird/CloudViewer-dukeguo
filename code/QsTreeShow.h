#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QStandardItemModel>
#include "QsTree.h"

class QsTreeShow : public QDialog
{
	Q_OBJECT
public:
	QsTreeShow(std::vector<QsTree*> myTrees);

	~QsTreeShow();

public:
	QGroupBox *groupBox;
	QGridLayout *gridLayout;
	QTableView *tableView;
	QPushButton *pushButton;

	void setupUi(QDialog *Dialog)
	{
		if (Dialog->objectName().isEmpty())
			Dialog->setObjectName(QStringLiteral("Dialog"));
		Dialog->setFixedSize(558, 309);
		groupBox = new QGroupBox(Dialog);
		groupBox->setObjectName(QStringLiteral("groupBox"));
		groupBox->setGeometry(QRect(10, 10, 541, 261));
		gridLayout = new QGridLayout(groupBox);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));
		gridLayout->setHorizontalSpacing(0);
		gridLayout->setContentsMargins(0, 0, 0, 0);
		tableView = new QTableView(groupBox);
		tableView->setObjectName(QStringLiteral("tableView"));

		gridLayout->addWidget(tableView, 0, 0, 1, 1);

		pushButton = new QPushButton(Dialog);
		pushButton->setObjectName(QStringLiteral("pushButton"));
		pushButton->setGeometry(QRect(230, 280, 75, 23));

		retranslateUi(Dialog);

		QMetaObject::connectSlotsByName(Dialog);
	} // setupUi

	void retranslateUi(QDialog *Dialog)
	{
		Dialog->setWindowTitle(QApplication::translate("Dialog", "\345\215\225\346\234\250\345\217\202\346\225\260\347\273\237\350\256\241", Q_NULLPTR));
		groupBox->setTitle(QApplication::translate("Dialog", "\345\215\225\346\234\250\345\217\202\346\225\260", Q_NULLPTR));
		pushButton->setText(QApplication::translate("Dialog", "\345\257\274\345\207\272", Q_NULLPTR));
	} // retranslateUi
private slots:
	void exportTree();

};

