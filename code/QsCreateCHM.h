#pragma once
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <QFileDialog>
#include <QMessageBox>


#include <gdal_priv.h>

class QsCreateCHM : public QDialog
{
	Q_OBJECT
public:
	QsCreateCHM();
	~QsCreateCHM();

public:
	QWidget *widget;
	QHBoxLayout *horizontalLayout;
	QLabel *label;
	QLineEdit *dsmLE;
	QPushButton *dsmBtn;
	QWidget *widget1;
	QHBoxLayout *horizontalLayout_2;
	QLabel *label_2;
	QLineEdit *demLE;
	QPushButton *demBtn;
	QWidget *widget2;
	QHBoxLayout *horizontalLayout_3;
	QLabel *label_3;
	QLineEdit *chmLE;
	QPushButton *savBtn;
	QWidget *widget3;
	QHBoxLayout *horizontalLayout_4;
	QPushButton *okBtn;
	QSpacerItem *horizontalSpacer;
	QPushButton *calBtn;

	void setupUi(QDialog *Dialog)
	{
		if (Dialog->objectName().isEmpty())
			Dialog->setObjectName(QStringLiteral("Dialog"));
		Dialog->setFixedSize(400, 193);
		widget = new QWidget(Dialog);
		widget->setObjectName(QStringLiteral("widget"));
		widget->setGeometry(QRect(20, 20, 371, 30));
		horizontalLayout = new QHBoxLayout(widget);
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		horizontalLayout->setContentsMargins(0, 0, 0, 0);
		label = new QLabel(widget);
		label->setObjectName(QStringLiteral("label"));

		horizontalLayout->addWidget(label);

		dsmLE = new QLineEdit(widget);
		dsmLE->setObjectName(QStringLiteral("dsmLE"));

		horizontalLayout->addWidget(dsmLE);

		dsmBtn = new QPushButton(widget);
		dsmBtn->setObjectName(QStringLiteral("dsmBtn"));

		horizontalLayout->addWidget(dsmBtn);

		widget1 = new QWidget(Dialog);
		widget1->setObjectName(QStringLiteral("widget1"));
		widget1->setGeometry(QRect(20, 60, 371, 30));
		horizontalLayout_2 = new QHBoxLayout(widget1);
		horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
		horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
		label_2 = new QLabel(widget1);
		label_2->setObjectName(QStringLiteral("label_2"));

		horizontalLayout_2->addWidget(label_2);

		demLE = new QLineEdit(widget1);
		demLE->setObjectName(QStringLiteral("demLE"));

		horizontalLayout_2->addWidget(demLE);

		demBtn = new QPushButton(widget1);
		demBtn->setObjectName(QStringLiteral("demBtn"));

		horizontalLayout_2->addWidget(demBtn);

		widget2 = new QWidget(Dialog);
		widget2->setObjectName(QStringLiteral("widget2"));
		widget2->setGeometry(QRect(20, 100, 371, 30));
		horizontalLayout_3 = new QHBoxLayout(widget2);
		horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
		horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
		label_3 = new QLabel(widget2);
		label_3->setObjectName(QStringLiteral("label_3"));

		horizontalLayout_3->addWidget(label_3);

		chmLE = new QLineEdit(widget2);
		chmLE->setObjectName(QStringLiteral("chmLE"));

		horizontalLayout_3->addWidget(chmLE);

		savBtn = new QPushButton(widget2);
		savBtn->setObjectName(QStringLiteral("savBtn"));

		horizontalLayout_3->addWidget(savBtn);

		widget3 = new QWidget(Dialog);
		widget3->setObjectName(QStringLiteral("widget3"));
		widget3->setGeometry(QRect(90, 150, 242, 30));
		horizontalLayout_4 = new QHBoxLayout(widget3);
		horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
		horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
		okBtn = new QPushButton(widget3);
		okBtn->setObjectName(QStringLiteral("okBtn"));

		horizontalLayout_4->addWidget(okBtn);

		horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

		horizontalLayout_4->addItem(horizontalSpacer);

		calBtn = new QPushButton(widget3);
		calBtn->setObjectName(QStringLiteral("calBtn"));

		horizontalLayout_4->addWidget(calBtn);


		retranslateUi(Dialog);

		QMetaObject::connectSlotsByName(Dialog);
	} // setupUi

	void retranslateUi(QDialog *Dialog)
	{
		Dialog->setWindowTitle(QApplication::translate("Dialog", "\347\224\237\346\210\220CHM", 0));
		label->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200DSM\357\274\232", 0));
		dsmBtn->setText(QApplication::translate("Dialog", "\350\276\223\345\205\245", 0));
		label_2->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200DEM\357\274\232", 0));
		demBtn->setText(QApplication::translate("Dialog", "\350\276\223\345\205\245", 0));
		label_3->setText(QApplication::translate("Dialog", "\350\276\223\345\207\272CHM\357\274\232", 0));
		savBtn->setText(QApplication::translate("Dialog", "\344\277\235\345\255\230", 0));
		okBtn->setText(QApplication::translate("Dialog", "\347\241\256\345\256\232", 0));
		calBtn->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));
	} // retranslateUi

	private slots:
	void openDSM();
	void openDEM();
	void saveCHM();
	void createCHM();


};

