#pragma once
#pragma once
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <vector>
#include <string>

#include <PointCloud.h>
#include <CSF.h>


class QsCSFLvBo :public QDialog
{
	Q_OBJECT
public:
	QsCSFLvBo();
	~QsCSFLvBo();

public:
	QHBoxLayout *horizontalLayout_7;
	QVBoxLayout *verticalLayout_3;
	QHBoxLayout *horizontalLayout;
	QLabel *label;
	QLineEdit *openlEdit;
	QPushButton *openBtn;
	QGroupBox *groupBox;
	QVBoxLayout *verticalLayout;
	QHBoxLayout *horizontalLayout_2;
	QLabel *label_2;
	QLineEdit *gridWidth;
	QLabel *label_3;
	QLineEdit *buLyd;
	QHBoxLayout *horizontalLayout_3;
	QLabel *label_6;
	QLineEdit *ddcs;
	QLabel *label_5;
	QLineEdit *flyz;
	QCheckBox *checkBox;
	QGroupBox *groupBox_2;
	QVBoxLayout *verticalLayout_2;
	QHBoxLayout *horizontalLayout_4;
	QLabel *label_4;
	QLineEdit *savlEdit;
	QPushButton *savBtn;
	QHBoxLayout *horizontalLayout_5;
	QLabel *label_7;
	QLineEdit *savlEdit_2;
	QPushButton *savBtn_2;
	QHBoxLayout *horizontalLayout_6;
	QSpacerItem *horizontalSpacer;
	QPushButton *okBtn;
	QSpacerItem *horizontalSpacer_2;
	QPushButton *canBtn;
	QPushButton *helpBtn;
	QGroupBox *helpGBox;
	QGridLayout *gridLayout;
	QTextEdit *textEdit;

	void setupUi(QDialog *Dialog)
	{
		if (Dialog->objectName().isEmpty())
			Dialog->setObjectName(QStringLiteral("Dialog"));
		Dialog->resize(896, 300);
		horizontalLayout_7 = new QHBoxLayout(Dialog);
		horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
		horizontalLayout_7->setSizeConstraint(QLayout::SetFixedSize);
		verticalLayout_3 = new QVBoxLayout();
		verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
		horizontalLayout = new QHBoxLayout();
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		label = new QLabel(Dialog);
		label->setObjectName(QStringLiteral("label"));

		horizontalLayout->addWidget(label);

		openlEdit = new QLineEdit(Dialog);
		openlEdit->setObjectName(QStringLiteral("openlEdit"));

		horizontalLayout->addWidget(openlEdit);

		openBtn = new QPushButton(Dialog);
		openBtn->setObjectName(QStringLiteral("openBtn"));

		horizontalLayout->addWidget(openBtn);


		verticalLayout_3->addLayout(horizontalLayout);

		groupBox = new QGroupBox(Dialog);
		groupBox->setObjectName(QStringLiteral("groupBox"));
		verticalLayout = new QVBoxLayout(groupBox);
		verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
		horizontalLayout_2 = new QHBoxLayout();
		horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
		label_2 = new QLabel(groupBox);
		label_2->setObjectName(QStringLiteral("label_2"));

		horizontalLayout_2->addWidget(label_2);

		gridWidth = new QLineEdit(groupBox);
		gridWidth->setObjectName(QStringLiteral("gridWidth"));

		horizontalLayout_2->addWidget(gridWidth);

		label_3 = new QLabel(groupBox);
		label_3->setObjectName(QStringLiteral("label_3"));

		horizontalLayout_2->addWidget(label_3);

		buLyd = new QLineEdit(groupBox);
		buLyd->setObjectName(QStringLiteral("buLyd"));

		horizontalLayout_2->addWidget(buLyd);


		verticalLayout->addLayout(horizontalLayout_2);

		horizontalLayout_3 = new QHBoxLayout();
		horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
		label_6 = new QLabel(groupBox);
		label_6->setObjectName(QStringLiteral("label_6"));

		horizontalLayout_3->addWidget(label_6);

		ddcs = new QLineEdit(groupBox);
		ddcs->setObjectName(QStringLiteral("ddcs"));

		horizontalLayout_3->addWidget(ddcs);

		label_5 = new QLabel(groupBox);
		label_5->setObjectName(QStringLiteral("label_5"));

		horizontalLayout_3->addWidget(label_5);

		flyz = new QLineEdit(groupBox);
		flyz->setObjectName(QStringLiteral("flyz"));

		horizontalLayout_3->addWidget(flyz);


		verticalLayout->addLayout(horizontalLayout_3);

		checkBox = new QCheckBox(groupBox);
		checkBox->setObjectName(QStringLiteral("checkBox"));

		verticalLayout->addWidget(checkBox);


		verticalLayout_3->addWidget(groupBox);

		groupBox_2 = new QGroupBox(Dialog);
		groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
		verticalLayout_2 = new QVBoxLayout(groupBox_2);
		verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
		horizontalLayout_4 = new QHBoxLayout();
		horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
		label_4 = new QLabel(groupBox_2);
		label_4->setObjectName(QStringLiteral("label_4"));

		horizontalLayout_4->addWidget(label_4);

		savlEdit = new QLineEdit(groupBox_2);
		savlEdit->setObjectName(QStringLiteral("savlEdit"));

		horizontalLayout_4->addWidget(savlEdit);

		savBtn = new QPushButton(groupBox_2);
		savBtn->setObjectName(QStringLiteral("savBtn"));

		horizontalLayout_4->addWidget(savBtn);


		verticalLayout_2->addLayout(horizontalLayout_4);

		horizontalLayout_5 = new QHBoxLayout();
		horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
		label_7 = new QLabel(groupBox_2);
		label_7->setObjectName(QStringLiteral("label_7"));

		horizontalLayout_5->addWidget(label_7);

		savlEdit_2 = new QLineEdit(groupBox_2);
		savlEdit_2->setObjectName(QStringLiteral("savlEdit_2"));
		horizontalLayout_5->addWidget(savlEdit_2);
		savBtn_2 = new QPushButton(groupBox_2);
		savBtn_2->setObjectName(QStringLiteral("savBtn_2"));
		horizontalLayout_5->addWidget(savBtn_2);
		verticalLayout_2->addLayout(horizontalLayout_5);
		verticalLayout_3->addWidget(groupBox_2);
		horizontalLayout_6 = new QHBoxLayout();
		horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
		horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

		horizontalLayout_6->addItem(horizontalSpacer);

		okBtn = new QPushButton(Dialog);
		okBtn->setObjectName(QStringLiteral("okBtn"));

		horizontalLayout_6->addWidget(okBtn);

		horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

		horizontalLayout_6->addItem(horizontalSpacer_2);

		canBtn = new QPushButton(Dialog);
		canBtn->setObjectName(QStringLiteral("canBtn"));

		horizontalLayout_6->addWidget(canBtn);

		helpBtn = new QPushButton(Dialog);
		helpBtn->setObjectName(QStringLiteral("helpBtn"));
		helpBtn->setCheckable(true);

		horizontalLayout_6->addWidget(helpBtn);


		verticalLayout_3->addLayout(horizontalLayout_6);


		horizontalLayout_7->addLayout(verticalLayout_3);

		helpGBox = new QGroupBox(Dialog);
		helpGBox->setObjectName(QStringLiteral("helpGBox"));
		gridLayout = new QGridLayout(helpGBox);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));
		gridLayout->setContentsMargins(2, 2, 2, 2);
		textEdit = new QTextEdit(helpGBox);
		textEdit->setObjectName(QStringLiteral("textEdit"));
		textEdit->setReadOnly(true);

		gridLayout->addWidget(textEdit, 0, 0, 1, 1);


		horizontalLayout_7->addWidget(helpGBox);


		retranslateUi(Dialog);

		QMetaObject::connectSlotsByName(Dialog);
	} // setupUi

	void retranslateUi(QDialog *Dialog)
	{
		Dialog->setWindowTitle(QApplication::translate("Dialog", "CSF\346\273\244\346\263\242", 0));
		label->setText(QApplication::translate("Dialog", "\350\276\223\345\205\245\347\202\271\344\272\221\346\226\207\344\273\266\357\274\232", 0));
		openBtn->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200", 0));
		groupBox->setTitle(QApplication::translate("Dialog", "\345\217\202\346\225\260\350\256\276\347\275\256", 0));
		label_2->setText(QApplication::translate("Dialog", "\346\240\274\347\275\221\345\244\247\345\260\217\357\274\232", 0));
		gridWidth->setText(QApplication::translate("Dialog", "0.5", 0));
		label_3->setText(QApplication::translate("Dialog", "\345\270\203\346\226\231\347\241\254\345\272\246\357\274\232", 0));
		buLyd->setText(QApplication::translate("Dialog", "2", 0));
		label_6->setText(QApplication::translate("Dialog", "\350\277\255\344\273\243\346\254\241\346\225\260\357\274\232", 0));
		ddcs->setText(QApplication::translate("Dialog", "200", 0));
		label_5->setText(QApplication::translate("Dialog", "\345\210\206\347\261\273\351\230\210\345\200\274\357\274\232", 0));
		flyz->setText(QApplication::translate("Dialog", "0.5", 0));
		checkBox->setText(QApplication::translate("Dialog", "\346\230\257\345\220\246\345\271\263\346\273\221\345\244\204\347\220\206", 0));
		groupBox_2->setTitle(QApplication::translate("Dialog", "\350\276\223\345\207\272\347\202\271\344\272\221", 0));
		label_4->setText(QApplication::translate("Dialog", "\345\234\260\351\235\242\347\202\271\357\274\232", 0));
		savBtn->setText(QApplication::translate("Dialog", "\344\277\235\345\255\230", 0));
		label_7->setText(QApplication::translate("Dialog", "\351\235\236\345\234\260\351\235\242\347\202\271\357\274\232", 0));
		savBtn_2->setText(QApplication::translate("Dialog", "\344\277\235\345\255\230", 0));
		okBtn->setText(QApplication::translate("Dialog", "\347\241\256\345\256\232", 0));
		canBtn->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));
		helpBtn->setText(QApplication::translate("Dialog", ">>", 0));
		helpGBox->setTitle(QApplication::translate("Dialog", "\345\267\245\345\205\267\345\270\256\345\212\251", 0));
		textEdit->setHtml(QApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
			"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
			"p, li { white-space: pre-wrap; }\n"
			"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\256\200\344\273\213\357\274\232CSF\346\273\244\346\263\242\347\256\227\346\263\225\345\274\225\347\224\250\350\207\252(&quot;W. Zhang, J. Qi, P. Wan,A. Wang, D. Xie, X. Wang, and G Yan, &quot;An Easy-to-Use Airborne LiDAR Data Filtering Method Based on Cloth Simulation,&quot; Remote Sens., vol. 8, no. 6, p. 501,2016)</p>\n"
			"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0"
			"px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\350\276\223\345\205\245\347\202\271\344\272\221\346\226\207\344\273\266\357\274\232</span>\350\276\223\345\205\245las\343\200\201txt\346\240\274\345\274\217\347\202\271\344\272\221\346\225\260\346\215\256</p>\n"
			"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\345\217\202\346\225\260\350\256\276\347\275\256\357\274\232</span></p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">         \346\240\274\347\275\221\345\244\247\345\260\217\357\274\232\347\202\271\344\272\221\347\275\221\346\240\274\345\214\226\347\232\204\350\276\271\351\225\277,\345\215\225\344\275\215\344\270\272m,\346\240\271\346\215"
			"\256\347\202\271\344\272\221\345\257\206\345\272\246\350\200\214\345\256\232,\344\270\200\350\210\254\351\273\230\350\256\244\345\215\263\345\217\257</p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">         \345\270\203\346\226\231\347\241\254\345\272\246:\345\234\260\345\275\242\350\266\212\345\271\263\345\235\246\357\274\214\350\257\245\350\266\212\345\244\247\357\274\214\345\217\226\345\200\274\350\214\203\345\233\264\345\273\272\350\256\256[[1,3];</p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">         \350\277\255\344\273\243\346\254\241\346\225\260:\346\240\271\346\215\256\345\244\204\347\220\206\346\225\260\346\215\256\347\232\204\345\244\247\345\260\217\350\277\233\350\241\214\351\200\211\346\213\251\357\274\214\351\273\230\350\256\244\350\256\276\347\275\256\344\270\272200;</p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0"
			"px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">         \345\210\206\347\261\273\351\230\210\345\200\274:\345\237\272\344\272\216\347\202\271\345\222\214\346\250\241\346\213\237\345\234\260\345\275\242\344\271\213\351\227\264\347\232\204\350\267\235\347\246\273\357\274\214\347\224\250\350\257\245\351\230\210\345\200\274\345\216\273\345\210\206\347\261\273\345\234\260\351\235\242\347\202\271\345\222\214\351\235\236\345\234\260\351\235\242\347\202\271\357\274\2140.5 \351\200\202\347\224\250\344\272\216\345\244\247\351\203\250\345\210\206\345\234\260\345\275\242;</p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">         \345\271\263\346\273\221\345\244\204\347\220\206\357\274\232\347\241\256\345\256\232\346\230\257\345\220\246\345\257\271\345\234\260\351\235\242\347\202\271\344\272\221\350\277\233\350\241\214\345\271\263\346\273\221\345\244\204\347\220\206</p>\n"
			"<p style=\"-qt-paragraph-type:empty; margin-top:0px; marg"
			"in-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\350\276\223\345\207\272\347\202\271\344\272\221\357\274\232</span>(\350\276\223\345\207\272\347\202\271\344\272\221\346\240\274\345\274\217\345\277\205\351\241\273\344\270\216\350\276\223\345\205\245\347\202\271\344\272\221\346\240\274\345\274\217\344\270\200\350\207\264)</p>\n"
			"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">         \345\210\206\345\210\253\350\276\223\345\207\272\345\234\260\351\235\242\347\202\271\344\272\221\345\217\212\351\235\236\345\234\260\351\235\242\347\202\271\344\272\221</p></body></html>", 0));
	} // retranslateUi

	private slots:
	void openFile();
	void saveFile();
	void saveFile2();
	void cfsLB();
	void setHelptext();
private:
	void lasLB();
	void txtLB();
};

