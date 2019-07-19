#pragma once

/************************************************************************/
/*                     实现常见点云数据格式的转换  las->txt                                               */
/************************************************************************/

#pragma once


#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QException>
#include <QErrorMessage>


#include <liblas\liblas.hpp>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/segmentation/progressive_morphological_filter.h>

class QsConvertFormat : public QDialog
{
	Q_OBJECT
public:
	QsConvertFormat();
	~QsConvertFormat();

	QLabel *label;
	QLabel *label_2;
	QLineEdit *openEdit;
	QLineEdit *saveEdit;
	QPushButton *okBtn;
	QPushButton *cancleBtn;
	QGroupBox *groupBox;
	QRadioButton *space;
	QRadioButton *douhao;
	QRadioButton *tab;
	QPushButton *openBtn;
	QPushButton *savBtn;

	void setupUi(QDialog *Dialog)
	{
		if (Dialog->objectName().isEmpty())
			Dialog->setObjectName(QStringLiteral("Dialog"));
		Dialog->setFixedSize(350, 203);
		label = new QLabel(Dialog);
		label->setObjectName(QStringLiteral("label"));
		label->setGeometry(QRect(10, 20, 71, 21));
		label_2 = new QLabel(Dialog);
		label_2->setObjectName(QStringLiteral("label_2"));
		label_2->setGeometry(QRect(10, 130, 71, 21));
		openEdit = new QLineEdit(Dialog);
		openEdit->setObjectName(QStringLiteral("openEdit"));
		openEdit->setGeometry(QRect(80, 20, 171, 20));
		saveEdit = new QLineEdit(Dialog);
		saveEdit->setObjectName(QStringLiteral("saveEdit"));
		saveEdit->setGeometry(QRect(80, 130, 171, 20));
		okBtn = new QPushButton(Dialog);
		okBtn->setObjectName(QStringLiteral("okBtn"));
		okBtn->setGeometry(QRect(70, 170, 75, 23));
		cancleBtn = new QPushButton(Dialog);
		cancleBtn->setObjectName(QStringLiteral("cancleBtn"));
		cancleBtn->setGeometry(QRect(200, 170, 75, 23));
		//groupBox = new QGroupBox(Dialog);
		//groupBox->setObjectName(QStringLiteral("groupBox"));
		//groupBox->setGeometry(QRect(10, 50, 321, 61));
		//space = new QRadioButton(groupBox);
		//space->setObjectName(QStringLiteral("space"));
		//space->setGeometry(QRect(30, 30, 89, 16));
		//space->setChecked(true);
		//douhao = new QRadioButton(groupBox);
		//douhao->setObjectName(QStringLiteral("douhao"));
		//douhao->setGeometry(QRect(120, 30, 89, 16));
		//tab = new QRadioButton(groupBox);
		//tab->setObjectName(QStringLiteral("tab"));
		//tab->setGeometry(QRect(220, 30, 89, 16));
		openBtn = new QPushButton(Dialog);
		openBtn->setObjectName(QStringLiteral("openBtn"));
		openBtn->setGeometry(QRect(260, 20, 75, 23));
		savBtn = new QPushButton(Dialog);
		savBtn->setObjectName(QStringLiteral("savBtn"));
		savBtn->setGeometry(QRect(270, 130, 75, 23));

		retranslateUi(Dialog);

		QMetaObject::connectSlotsByName(Dialog);
	} // setupUi

	void retranslateUi(QDialog *Dialog)
	{
		Dialog->setWindowTitle(QApplication::translate("Dialog", "\347\202\271\344\272\221\346\240\274\345\274\217\350\275\254\346\215\242(las->pcd)", 0));
		label->setText(QApplication::translate("Dialog", "\350\276\223\345\205\245\346\226\207\344\273\266\357\274\232", 0));
		label_2->setText(QApplication::translate("Dialog", "\350\276\223\345\207\272\346\226\207\344\273\266\357\274\232", 0));
		okBtn->setText(QApplication::translate("Dialog", "\347\241\256\345\256\232", 0));
		cancleBtn->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));
		/*groupBox->setTitle(QApplication::translate("Dialog", "\345\210\206\345\211\262\347\254\246", 0));
		space->setText(QApplication::translate("Dialog", "\347\251\272\346\240\274", 0));
		douhao->setText(QApplication::translate("Dialog", "\351\200\227\345\217\267", 0));
		tab->setText(QApplication::translate("Dialog", "\345\210\266\350\241\250\347\254\246", 0));*/
		openBtn->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200", 0));
		savBtn->setText(QApplication::translate("Dialog", "\344\277\235\345\255\230", 0));
	} // retranslateUi


private slots:
	void openFile();
	void saveFile();

	int las2pcd();//las格式转pcd格式


};

