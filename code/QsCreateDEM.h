#pragma once
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>
#include <QList>
#include <QString>
#include <QFileInfo>
#include <QProgressDialog>
#include <QTimer>
#include <QThread>
#include <QCoreApplication>

#include <gdal_alg.h>
#include <gdal_priv.h>

#include <liblas\liblas.hpp>

#include <QsPCloudIO.h>

class QsCreateDEM : public QDialog
{
	Q_OBJECT
public:
	QsCreateDEM();
	~QsCreateDEM();


public:
	QGroupBox *groupBox;
	QWidget *widget;
	QHBoxLayout *horizontalLayout_2;
	QRadioButton *rBtn3;
	QRadioButton *rBtn2;
	QRadioButton *rBtn1;
	QWidget *widget1;
	QHBoxLayout *horizontalLayout_3;
	QLabel *label_2;
	QLineEdit *lineEdit;
	QLabel *label_3;
	QLineEdit *lineEdit_2;
	QWidget *widget2;
	QHBoxLayout *horizontalLayout;
	QLabel *label;
	QLineEdit *openlEdit;
	QPushButton *openBtn;
	QWidget *widget3;
	QHBoxLayout *horizontalLayout_4;
	QLabel *label_4;
	QLineEdit *savlEdit;
	QPushButton *savBtn;
	QWidget *widget4;
	QHBoxLayout *horizontalLayout_5;
	QPushButton *okBtn;
	QSpacerItem *horizontalSpacer;
	QPushButton *canBtn;

	void setupUi(QDialog *Dialog)
	{
		if (Dialog->objectName().isEmpty())
			Dialog->setObjectName(QStringLiteral("Dialog"));
		Dialog->setFixedSize(451, 233);
		groupBox = new QGroupBox(Dialog);
		groupBox->setObjectName(QStringLiteral("groupBox"));
		groupBox->setGeometry(QRect(20, 50, 421, 91));
		widget = new QWidget(groupBox);
		widget->setObjectName(QStringLiteral("widget"));
		widget->setGeometry(QRect(20, 20, 391, 21));
		horizontalLayout_2 = new QHBoxLayout(widget);
		horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
		horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
		rBtn3 = new QRadioButton(widget);
		rBtn3->setObjectName(QStringLiteral("rBtn3"));
		rBtn3->setChecked(true);

		horizontalLayout_2->addWidget(rBtn3);

		rBtn2 = new QRadioButton(widget);
		rBtn2->setObjectName(QStringLiteral("rBtn2"));

		horizontalLayout_2->addWidget(rBtn2);

		rBtn1 = new QRadioButton(widget);
		rBtn1->setObjectName(QStringLiteral("rBtn1"));

		horizontalLayout_2->addWidget(rBtn1);

		widget1 = new QWidget(groupBox);
		widget1->setObjectName(QStringLiteral("widget1"));
		widget1->setGeometry(QRect(10, 60, 401, 23));
		horizontalLayout_3 = new QHBoxLayout(widget1);
		horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
		horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
		label_2 = new QLabel(widget1);
		label_2->setObjectName(QStringLiteral("label_2"));

		horizontalLayout_3->addWidget(label_2);

		lineEdit = new QLineEdit(widget1);
		lineEdit->setObjectName(QStringLiteral("lineEdit"));

		horizontalLayout_3->addWidget(lineEdit);

		label_3 = new QLabel(widget1);
		label_3->setObjectName(QStringLiteral("label_3"));

		horizontalLayout_3->addWidget(label_3);

		lineEdit_2 = new QLineEdit(widget1);
		lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

		horizontalLayout_3->addWidget(lineEdit_2);

		widget2 = new QWidget(Dialog);
		widget2->setObjectName(QStringLiteral("widget2"));
		widget2->setGeometry(QRect(20, 10, 421, 30));
		horizontalLayout = new QHBoxLayout(widget2);
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		horizontalLayout->setContentsMargins(0, 0, 0, 0);
		label = new QLabel(widget2);
		label->setObjectName(QStringLiteral("label"));

		horizontalLayout->addWidget(label);

		openlEdit = new QLineEdit(widget2);
		openlEdit->setObjectName(QStringLiteral("openlEdit"));

		horizontalLayout->addWidget(openlEdit);

		openBtn = new QPushButton(widget2);
		openBtn->setObjectName(QStringLiteral("openBtn"));

		horizontalLayout->addWidget(openBtn);

		widget3 = new QWidget(Dialog);
		widget3->setObjectName(QStringLiteral("widget3"));
		widget3->setGeometry(QRect(20, 150, 421, 30));
		horizontalLayout_4 = new QHBoxLayout(widget3);
		horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
		horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
		label_4 = new QLabel(widget3);
		label_4->setObjectName(QStringLiteral("label_4"));

		horizontalLayout_4->addWidget(label_4);

		savlEdit = new QLineEdit(widget3);
		savlEdit->setObjectName(QStringLiteral("savlEdit"));

		horizontalLayout_4->addWidget(savlEdit);

		savBtn = new QPushButton(widget3);
		savBtn->setObjectName(QStringLiteral("savBtn"));

		horizontalLayout_4->addWidget(savBtn);

		widget4 = new QWidget(Dialog);
		widget4->setObjectName(QStringLiteral("widget4"));
		widget4->setGeometry(QRect(100, 190, 242, 30));
		horizontalLayout_5 = new QHBoxLayout(widget4);
		horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
		horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
		okBtn = new QPushButton(widget4);
		okBtn->setObjectName(QStringLiteral("okBtn"));

		horizontalLayout_5->addWidget(okBtn);

		horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

		horizontalLayout_5->addItem(horizontalSpacer);

		canBtn = new QPushButton(widget4);
		canBtn->setObjectName(QStringLiteral("canBtn"));

		horizontalLayout_5->addWidget(canBtn);


		retranslateUi(Dialog);

		QMetaObject::connectSlotsByName(Dialog);
	} // setupUi

	void retranslateUi(QDialog *Dialog)
	{
		Dialog->setWindowTitle(QApplication::translate("Dialog", "\347\224\237\346\210\220DEM", 0));
		groupBox->setTitle(QApplication::translate("Dialog", "\345\217\202\346\225\260\350\256\276\347\275\256", 0));
		rBtn3->setText(QApplication::translate("Dialog", "\346\234\200\351\202\273\350\277\221\346\217\222\345\200\274", 0));
		rBtn2->setText(QApplication::translate("Dialog", "\347\247\273\345\212\250\345\235\207\345\200\274\346\217\222\345\200\274", 0));
		rBtn1->setText(QApplication::translate("Dialog", "\345\217\215\350\267\235\347\246\273\345\212\240\346\235\203\346\217\222\345\200\274", 0));
		label_2->setText(QApplication::translate("Dialog", "\346\240\274\347\275\221\345\244\247\345\260\217\357\274\232", 0));
		lineEdit->setText(QApplication::translate("Dialog", "1", 0));
		label_3->setText(QApplication::translate("Dialog", "\346\217\222\345\200\274\345\215\212\345\276\204\357\274\232", 0));
		lineEdit_2->setText(QApplication::translate("Dialog", "3", 0));
		label->setText(QApplication::translate("Dialog", "\345\234\260\351\235\242\347\202\271\344\272\221\346\226\207\344\273\266\357\274\232", 0));
		openBtn->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200", 0));
		label_4->setText(QApplication::translate("Dialog", "\350\276\223\345\207\272DEM\357\274\232", 0));
		savBtn->setText(QApplication::translate("Dialog", "\344\277\235\345\255\230", 0));
		okBtn->setText(QApplication::translate("Dialog", "\347\241\256\345\256\232", 0));
		canBtn->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));
	} // retranslateUi

	private:
		QProgressDialog* progDlg;
		QTimer* timer;
		int currentValue;

	private slots:
	void openFile();
	void saveFile();
	void createDem();

	void updateProgressDialog();
	void stopProgress();

	private :
		void lasDEM();
		void txtDEM();
};

