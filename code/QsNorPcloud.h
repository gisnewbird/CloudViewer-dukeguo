#pragma once
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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <QList>
#include <QVector>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QTimer>
#include <QThread>
#include <QCoreApplication>
#include <QString>

#include <gdal_alg.h>
#include <gdal_priv.h>
#include <liblas\liblas.hpp>
#include <gdal.h>

//#include <QsPCloudIO.h>
class QsNorPcloud : public QDialog
{
	Q_OBJECT
public:
	QsNorPcloud();
	~QsNorPcloud();
public:
	QGroupBox *groupBox;
	QWidget *widget;
	QHBoxLayout *horizontalLayout_3;
	QLabel *label_2;
	QLineEdit *lineEdit;
	QLabel *label_3;
	QLineEdit *lineEdit_2;
	QWidget *widget1;
	QHBoxLayout *horizontalLayout;
	QLabel *label;
	QLineEdit *openlEdit;
	QPushButton *openBtn;
	QWidget *widget2;
	QHBoxLayout *horizontalLayout_2;
	QLabel *label_5;
	QLineEdit *openlEdit_2;
	QPushButton *openBtn_2;
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
		Dialog->setFixedSize(424, 247);
		groupBox = new QGroupBox(Dialog);
		groupBox->setObjectName(QStringLiteral("groupBox"));
		groupBox->setGeometry(QRect(10, 90, 401, 61));
		widget = new QWidget(groupBox);
		widget->setObjectName(QStringLiteral("widget"));
		widget->setGeometry(QRect(30, 30, 351, 23));
		horizontalLayout_3 = new QHBoxLayout(widget);
		horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
		horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
		label_2 = new QLabel(widget);
		label_2->setObjectName(QStringLiteral("label_2"));

		horizontalLayout_3->addWidget(label_2);

		lineEdit = new QLineEdit(widget);
		lineEdit->setObjectName(QStringLiteral("lineEdit"));

		horizontalLayout_3->addWidget(lineEdit);

		label_3 = new QLabel(widget);
		label_3->setObjectName(QStringLiteral("label_3"));

		horizontalLayout_3->addWidget(label_3);

		lineEdit_2 = new QLineEdit(widget);
		lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

		horizontalLayout_3->addWidget(lineEdit_2);

		widget1 = new QWidget(Dialog);
		widget1->setObjectName(QStringLiteral("widget1"));
		widget1->setGeometry(QRect(13, 10, 401, 30));
		horizontalLayout = new QHBoxLayout(widget1);
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		horizontalLayout->setContentsMargins(0, 0, 0, 0);
		label = new QLabel(widget1);
		label->setObjectName(QStringLiteral("label"));

		horizontalLayout->addWidget(label);

		openlEdit = new QLineEdit(widget1);
		openlEdit->setObjectName(QStringLiteral("openlEdit"));

		horizontalLayout->addWidget(openlEdit);

		openBtn = new QPushButton(widget1);
		openBtn->setObjectName(QStringLiteral("openBtn"));

		horizontalLayout->addWidget(openBtn);

		widget2 = new QWidget(Dialog);
		widget2->setObjectName(QStringLiteral("widget2"));
		widget2->setGeometry(QRect(10, 50, 401, 30));
		horizontalLayout_2 = new QHBoxLayout(widget2);
		horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
		horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
		label_5 = new QLabel(widget2);
		label_5->setObjectName(QStringLiteral("label_5"));

		horizontalLayout_2->addWidget(label_5);

		openlEdit_2 = new QLineEdit(widget2);
		openlEdit_2->setObjectName(QStringLiteral("openlEdit_2"));

		horizontalLayout_2->addWidget(openlEdit_2);

		openBtn_2 = new QPushButton(widget2);
		openBtn_2->setObjectName(QStringLiteral("openBtn_2"));

		horizontalLayout_2->addWidget(openBtn_2);

		widget3 = new QWidget(Dialog);
		widget3->setObjectName(QStringLiteral("widget3"));
		widget3->setGeometry(QRect(10, 160, 401, 30));
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
		widget4->setGeometry(QRect(100, 210, 242, 30));
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
		Dialog->setWindowTitle(QApplication::translate("Dialog", "\347\202\271\344\272\221\345\275\222\344\270\200\345\214\226", 0));
		groupBox->setTitle(QApplication::translate("Dialog", "\345\217\202\346\225\260\350\256\276\347\275\256", 0));
		label_2->setText(QApplication::translate("Dialog", "\346\240\274\347\275\221\345\244\247\345\260\217\357\274\232", 0));
		lineEdit->setText(QApplication::translate("Dialog", "1", 0));
		label_3->setText(QApplication::translate("Dialog", "\346\217\222\345\200\274\345\215\212\345\276\204\357\274\232", 0));
		lineEdit_2->setText(QApplication::translate("Dialog", "10", 0));
		label->setText(QApplication::translate("Dialog", "\345\234\260\351\235\242\347\202\271\344\272\221\346\226\207\344\273\266\357\274\232", 0));
		openBtn->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200", 0));
		label_5->setText(QApplication::translate("Dialog", "\351\235\236\345\234\260\351\235\242\347\202\271\344\272\221\346\226\207\344\273\266\357\274\232", 0));
		openBtn_2->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200", 0));
		label_4->setText(QApplication::translate("Dialog", "\345\275\222\344\270\200\345\214\226\347\202\271\344\272\221\357\274\232", 0));
		savBtn->setText(QApplication::translate("Dialog", "\344\277\235\345\255\230", 0));
		okBtn->setText(QApplication::translate("Dialog", "\347\241\256\345\256\232", 0));
		canBtn->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));
	} // retranslateUi
private slots:
	void openFile();
	void openFile2();
	void saveFile();
	void norPcloud();
	void updateProgressDialog();
	void stopProgress();
private:
	QProgressDialog* progDlg;
	QTimer* timer;
	int currentValue;
private:
	void lasNorPcloud();
	void txtNorPcloud();;
};

