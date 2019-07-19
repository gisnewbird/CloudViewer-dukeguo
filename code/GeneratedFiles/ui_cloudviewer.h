/********************************************************************************
** Form generated from reading UI file 'cloudviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOUDVIEWER_H
#define UI_CLOUDVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CloudViewerClass
{
public:
    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;
    QAction *cubeAction;
    QAction *helpAction;
    QAction *aboutAction;
    QAction *changeAction;
    QAction *exitAction;
    QAction *pointcolorAction;
    QAction *bgcolorAction;
    QAction *mainviewAction;
    QAction *leftviewAction;
    QAction *topviewAction;
    QAction *dataAction;
    QAction *propertyAction;
    QAction *consoleAction;
    QAction *RGBAction;
    QAction *clearAction;
    QAction *addAction;
    QAction *sphereAction;
    QAction *cylinderAction;
    QAction *meshsurfaceAction;
    QAction *wireframeAction;
    QAction *windowsThemeAction;
    QAction *darculaThemeAction;
    QAction *englishAction;
    QAction *chineseAction;
    QAction *saveBinaryAction;
    QAction *actionCSF_lvB;
    QAction *actionlvbo;
    QAction *actionlas_pcd;
    QAction *actionNpCloud;
    QAction *action_DEM;
    QAction *action_DSM;
    QAction *action_CHM;
    QAction *actionyuannihe;
    QAction *actionJGJL;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_5;
    QVTKWidget *screen;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuGenerate;
    QMenu *menuBasic_shapes;
    QMenu *menuAbout;
    QMenu *menuOption;
    QMenu *themeAction;
    QMenu *langAction;
    QMenu *menuView;
    QMenu *menuAngle_view;
    QMenu *menuView_2;
    QMenu *menuProcess;
    QMenu *menuDignalModel;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *RGBDock;
    QWidget *dockWidgetContents_4;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_1;
    QLCDNumber *rLCD;
    QSlider *rSlider;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLCDNumber *gLCD;
    QSlider *gSlider;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLCDNumber *bLCD;
    QSlider *bSlider;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLCDNumber *sizeLCD;
    QSlider *pSlider;
    QPushButton *colorBtn;
    QCheckBox *cooCbx;
    QCheckBox *bgcCbx;
    QDockWidget *dataDock;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *dataTree;
    QDockWidget *propertyDock;
    QWidget *dockWidgetContents_6;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *propertyTable;
    QDockWidget *consoleDock;
    QWidget *dockWidgetContents_7;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *consoleTable;

    void setupUi(QMainWindow *CloudViewerClass)
    {
        if (CloudViewerClass->objectName().isEmpty())
            CloudViewerClass->setObjectName(QStringLiteral("CloudViewerClass"));
        CloudViewerClass->resize(1246, 749);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(85);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CloudViewerClass->sizePolicy().hasHeightForWidth());
        CloudViewerClass->setSizePolicy(sizePolicy);
        CloudViewerClass->setMinimumSize(QSize(900, 650));
        CloudViewerClass->setMaximumSize(QSize(16777215, 16777215));
        CloudViewerClass->setStyleSheet(QStringLiteral(""));
        CloudViewerClass->setAnimated(true);
        CloudViewerClass->setTabShape(QTabWidget::Rounded);
        CloudViewerClass->setDockNestingEnabled(false);
        openAction = new QAction(CloudViewerClass);
        openAction->setObjectName(QStringLiteral("openAction"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        openAction->setIcon(icon);
        saveAction = new QAction(CloudViewerClass);
        saveAction->setObjectName(QStringLiteral("saveAction"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Resources/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveAction->setIcon(icon1);
        saveasAction = new QAction(CloudViewerClass);
        saveasAction->setObjectName(QStringLiteral("saveasAction"));
        cubeAction = new QAction(CloudViewerClass);
        cubeAction->setObjectName(QStringLiteral("cubeAction"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Resources/images/cube.png"), QSize(), QIcon::Normal, QIcon::Off);
        cubeAction->setIcon(icon2);
        helpAction = new QAction(CloudViewerClass);
        helpAction->setObjectName(QStringLiteral("helpAction"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Resources/images/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        helpAction->setIcon(icon3);
        aboutAction = new QAction(CloudViewerClass);
        aboutAction->setObjectName(QStringLiteral("aboutAction"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Resources/images/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        aboutAction->setIcon(icon4);
        changeAction = new QAction(CloudViewerClass);
        changeAction->setObjectName(QStringLiteral("changeAction"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Resources/images/change.png"), QSize(), QIcon::Normal, QIcon::Off);
        changeAction->setIcon(icon5);
        exitAction = new QAction(CloudViewerClass);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Resources/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        exitAction->setIcon(icon6);
        pointcolorAction = new QAction(CloudViewerClass);
        pointcolorAction->setObjectName(QStringLiteral("pointcolorAction"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Resources/images/pointcolor.png"), QSize(), QIcon::Normal, QIcon::Off);
        pointcolorAction->setIcon(icon7);
        bgcolorAction = new QAction(CloudViewerClass);
        bgcolorAction->setObjectName(QStringLiteral("bgcolorAction"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Resources/images/bgcolor.png"), QSize(), QIcon::Normal, QIcon::Off);
        bgcolorAction->setIcon(icon8);
        mainviewAction = new QAction(CloudViewerClass);
        mainviewAction->setObjectName(QStringLiteral("mainviewAction"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/Resources/images/zhengshi.png"), QSize(), QIcon::Normal, QIcon::Off);
        mainviewAction->setIcon(icon9);
        leftviewAction = new QAction(CloudViewerClass);
        leftviewAction->setObjectName(QStringLiteral("leftviewAction"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/Resources/images/zuoshi.png"), QSize(), QIcon::Normal, QIcon::Off);
        leftviewAction->setIcon(icon10);
        topviewAction = new QAction(CloudViewerClass);
        topviewAction->setObjectName(QStringLiteral("topviewAction"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/Resources/images/fushi.png"), QSize(), QIcon::Normal, QIcon::Off);
        topviewAction->setIcon(icon11);
        dataAction = new QAction(CloudViewerClass);
        dataAction->setObjectName(QStringLiteral("dataAction"));
        dataAction->setCheckable(true);
        dataAction->setChecked(true);
        propertyAction = new QAction(CloudViewerClass);
        propertyAction->setObjectName(QStringLiteral("propertyAction"));
        propertyAction->setCheckable(true);
        propertyAction->setChecked(true);
        consoleAction = new QAction(CloudViewerClass);
        consoleAction->setObjectName(QStringLiteral("consoleAction"));
        consoleAction->setCheckable(true);
        consoleAction->setChecked(true);
        RGBAction = new QAction(CloudViewerClass);
        RGBAction->setObjectName(QStringLiteral("RGBAction"));
        RGBAction->setCheckable(true);
        RGBAction->setChecked(true);
        clearAction = new QAction(CloudViewerClass);
        clearAction->setObjectName(QStringLiteral("clearAction"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/Resources/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearAction->setIcon(icon12);
        addAction = new QAction(CloudViewerClass);
        addAction->setObjectName(QStringLiteral("addAction"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/Resources/images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addAction->setIcon(icon13);
        sphereAction = new QAction(CloudViewerClass);
        sphereAction->setObjectName(QStringLiteral("sphereAction"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/Resources/images/sphere.png"), QSize(), QIcon::Normal, QIcon::Off);
        sphereAction->setIcon(icon14);
        cylinderAction = new QAction(CloudViewerClass);
        cylinderAction->setObjectName(QStringLiteral("cylinderAction"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/Resources/images/cylinder.png"), QSize(), QIcon::Normal, QIcon::Off);
        cylinderAction->setIcon(icon15);
        meshsurfaceAction = new QAction(CloudViewerClass);
        meshsurfaceAction->setObjectName(QStringLiteral("meshsurfaceAction"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/Resources/images/mesh.png"), QSize(), QIcon::Normal, QIcon::Off);
        meshsurfaceAction->setIcon(icon16);
        wireframeAction = new QAction(CloudViewerClass);
        wireframeAction->setObjectName(QStringLiteral("wireframeAction"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/Resources/images/frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        wireframeAction->setIcon(icon17);
        windowsThemeAction = new QAction(CloudViewerClass);
        windowsThemeAction->setObjectName(QStringLiteral("windowsThemeAction"));
        darculaThemeAction = new QAction(CloudViewerClass);
        darculaThemeAction->setObjectName(QStringLiteral("darculaThemeAction"));
        englishAction = new QAction(CloudViewerClass);
        englishAction->setObjectName(QStringLiteral("englishAction"));
        chineseAction = new QAction(CloudViewerClass);
        chineseAction->setObjectName(QStringLiteral("chineseAction"));
        saveBinaryAction = new QAction(CloudViewerClass);
        saveBinaryAction->setObjectName(QStringLiteral("saveBinaryAction"));
        saveBinaryAction->setEnabled(false);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/Resources/images/saveBinary.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveBinaryAction->setIcon(icon18);
        actionCSF_lvB = new QAction(CloudViewerClass);
        actionCSF_lvB->setObjectName(QStringLiteral("actionCSF_lvB"));
        actionlvbo = new QAction(CloudViewerClass);
        actionlvbo->setObjectName(QStringLiteral("actionlvbo"));
        actionlas_pcd = new QAction(CloudViewerClass);
        actionlas_pcd->setObjectName(QStringLiteral("actionlas_pcd"));
        actionNpCloud = new QAction(CloudViewerClass);
        actionNpCloud->setObjectName(QStringLiteral("actionNpCloud"));
        action_DEM = new QAction(CloudViewerClass);
        action_DEM->setObjectName(QStringLiteral("action_DEM"));
        action_DSM = new QAction(CloudViewerClass);
        action_DSM->setObjectName(QStringLiteral("action_DSM"));
        action_CHM = new QAction(CloudViewerClass);
        action_CHM->setObjectName(QStringLiteral("action_CHM"));
        actionyuannihe = new QAction(CloudViewerClass);
        actionyuannihe->setObjectName(QStringLiteral("actionyuannihe"));
        actionJGJL = new QAction(CloudViewerClass);
        actionJGJL->setObjectName(QStringLiteral("actionJGJL"));
        centralWidget = new QWidget(CloudViewerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        horizontalLayout_5 = new QHBoxLayout(centralWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        screen = new QVTKWidget(centralWidget);
        screen->setObjectName(QStringLiteral("screen"));
        screen->setMinimumSize(QSize(600, 400));

        horizontalLayout_5->addWidget(screen);

        CloudViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CloudViewerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1246, 26));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        menuBar->setFont(font);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuGenerate = new QMenu(menuBar);
        menuGenerate->setObjectName(QStringLiteral("menuGenerate"));
        menuBasic_shapes = new QMenu(menuGenerate);
        menuBasic_shapes->setObjectName(QStringLiteral("menuBasic_shapes"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/Resources/images/shape.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuBasic_shapes->setIcon(icon19);
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QStringLiteral("menuOption"));
        themeAction = new QMenu(menuOption);
        themeAction->setObjectName(QStringLiteral("themeAction"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/Resources/images/theme.png"), QSize(), QIcon::Normal, QIcon::Off);
        themeAction->setIcon(icon20);
        langAction = new QMenu(menuOption);
        langAction->setObjectName(QStringLiteral("langAction"));
        langAction->setEnabled(false);
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/Resources/images/language.png"), QSize(), QIcon::Normal, QIcon::Off);
        langAction->setIcon(icon21);
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuAngle_view = new QMenu(menuView);
        menuAngle_view->setObjectName(QStringLiteral("menuAngle_view"));
        menuView_2 = new QMenu(menuBar);
        menuView_2->setObjectName(QStringLiteral("menuView_2"));
        menuProcess = new QMenu(menuBar);
        menuProcess->setObjectName(QStringLiteral("menuProcess"));
        menuDignalModel = new QMenu(menuProcess);
        menuDignalModel->setObjectName(QStringLiteral("menuDignalModel"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        CloudViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CloudViewerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CloudViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CloudViewerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CloudViewerClass->setStatusBar(statusBar);
        RGBDock = new QDockWidget(CloudViewerClass);
        RGBDock->setObjectName(QStringLiteral("RGBDock"));
        RGBDock->setMinimumSize(QSize(245, 400));
        RGBDock->setMaximumSize(QSize(300, 524287));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_1 = new QLabel(dockWidgetContents_4);
        label_1->setObjectName(QStringLiteral("label_1"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_1->sizePolicy().hasHeightForWidth());
        label_1->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        label_1->setFont(font1);

        horizontalLayout->addWidget(label_1);

        rLCD = new QLCDNumber(dockWidgetContents_4);
        rLCD->setObjectName(QStringLiteral("rLCD"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(rLCD->sizePolicy().hasHeightForWidth());
        rLCD->setSizePolicy(sizePolicy3);
        rLCD->setAutoFillBackground(false);
        rLCD->setInputMethodHints(Qt::ImhNone);
        rLCD->setFrameShape(QFrame::Panel);
        rLCD->setFrameShadow(QFrame::Raised);
        rLCD->setLineWidth(1);
        rLCD->setSmallDecimalPoint(false);
        rLCD->setDigitCount(3);
        rLCD->setMode(QLCDNumber::Dec);
        rLCD->setProperty("value", QVariant(255));
        rLCD->setProperty("intValue", QVariant(255));

        horizontalLayout->addWidget(rLCD);


        verticalLayout->addLayout(horizontalLayout);

        rSlider = new QSlider(dockWidgetContents_4);
        rSlider->setObjectName(QStringLiteral("rSlider"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(rSlider->sizePolicy().hasHeightForWidth());
        rSlider->setSizePolicy(sizePolicy4);
        rSlider->setMinimumSize(QSize(132, 0));
        rSlider->setMaximum(255);
        rSlider->setSliderPosition(255);
        rSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(rSlider);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(dockWidgetContents_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        gLCD = new QLCDNumber(dockWidgetContents_4);
        gLCD->setObjectName(QStringLiteral("gLCD"));
        sizePolicy3.setHeightForWidth(gLCD->sizePolicy().hasHeightForWidth());
        gLCD->setSizePolicy(sizePolicy3);
        gLCD->setFrameShape(QFrame::Panel);
        gLCD->setDigitCount(3);
        gLCD->setProperty("intValue", QVariant(255));

        horizontalLayout_2->addWidget(gLCD);


        verticalLayout->addLayout(horizontalLayout_2);

        gSlider = new QSlider(dockWidgetContents_4);
        gSlider->setObjectName(QStringLiteral("gSlider"));
        sizePolicy4.setHeightForWidth(gSlider->sizePolicy().hasHeightForWidth());
        gSlider->setSizePolicy(sizePolicy4);
        gSlider->setMinimumSize(QSize(132, 0));
        gSlider->setMaximum(255);
        gSlider->setSliderPosition(255);
        gSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(gSlider);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(dockWidgetContents_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        bLCD = new QLCDNumber(dockWidgetContents_4);
        bLCD->setObjectName(QStringLiteral("bLCD"));
        sizePolicy3.setHeightForWidth(bLCD->sizePolicy().hasHeightForWidth());
        bLCD->setSizePolicy(sizePolicy3);
        bLCD->setFrameShape(QFrame::Panel);
        bLCD->setDigitCount(3);
        bLCD->setProperty("intValue", QVariant(255));

        horizontalLayout_3->addWidget(bLCD);


        verticalLayout->addLayout(horizontalLayout_3);

        bSlider = new QSlider(dockWidgetContents_4);
        bSlider->setObjectName(QStringLiteral("bSlider"));
        sizePolicy4.setHeightForWidth(bSlider->sizePolicy().hasHeightForWidth());
        bSlider->setSizePolicy(sizePolicy4);
        bSlider->setMinimumSize(QSize(132, 0));
        bSlider->setMaximum(255);
        bSlider->setSliderPosition(255);
        bSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(bSlider);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(dockWidgetContents_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setFont(font1);

        horizontalLayout_4->addWidget(label_4);

        sizeLCD = new QLCDNumber(dockWidgetContents_4);
        sizeLCD->setObjectName(QStringLiteral("sizeLCD"));
        sizePolicy3.setHeightForWidth(sizeLCD->sizePolicy().hasHeightForWidth());
        sizeLCD->setSizePolicy(sizePolicy3);
        sizeLCD->setDigitCount(1);
        sizeLCD->setSegmentStyle(QLCDNumber::Filled);
        sizeLCD->setProperty("intValue", QVariant(1));

        horizontalLayout_4->addWidget(sizeLCD);


        verticalLayout->addLayout(horizontalLayout_4);

        pSlider = new QSlider(dockWidgetContents_4);
        pSlider->setObjectName(QStringLiteral("pSlider"));
        sizePolicy4.setHeightForWidth(pSlider->sizePolicy().hasHeightForWidth());
        pSlider->setSizePolicy(sizePolicy4);
        pSlider->setMinimumSize(QSize(132, 0));
        pSlider->setMinimum(1);
        pSlider->setMaximum(10);
        pSlider->setSliderPosition(1);
        pSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(pSlider);

        colorBtn = new QPushButton(dockWidgetContents_4);
        colorBtn->setObjectName(QStringLiteral("colorBtn"));
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(11);
        colorBtn->setFont(font2);
        colorBtn->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(colorBtn);


        verticalLayout_2->addLayout(verticalLayout);

        cooCbx = new QCheckBox(dockWidgetContents_4);
        cooCbx->setObjectName(QStringLiteral("cooCbx"));
        cooCbx->setFont(font1);

        verticalLayout_2->addWidget(cooCbx);

        bgcCbx = new QCheckBox(dockWidgetContents_4);
        bgcCbx->setObjectName(QStringLiteral("bgcCbx"));
        bgcCbx->setFont(font1);

        verticalLayout_2->addWidget(bgcCbx);

        RGBDock->setWidget(dockWidgetContents_4);
        CloudViewerClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), RGBDock);
        dataDock = new QDockWidget(CloudViewerClass);
        dataDock->setObjectName(QStringLiteral("dataDock"));
        dataDock->setMinimumSize(QSize(250, 235));
        dataDock->setMaximumSize(QSize(300, 524287));
        dataDock->setFont(font1);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QStringLiteral("dockWidgetContents_5"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        dataTree = new QTreeWidget(dockWidgetContents_5);
        dataTree->setObjectName(QStringLiteral("dataTree"));
        dataTree->setMinimumSize(QSize(0, 180));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(9);
        dataTree->setFont(font3);
        dataTree->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_3->addWidget(dataTree);

        dataDock->setWidget(dockWidgetContents_5);
        CloudViewerClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dataDock);
        propertyDock = new QDockWidget(CloudViewerClass);
        propertyDock->setObjectName(QStringLiteral("propertyDock"));
        propertyDock->setMinimumSize(QSize(250, 235));
        propertyDock->setFont(font1);
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QStringLiteral("dockWidgetContents_6"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents_6);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        propertyTable = new QTableWidget(dockWidgetContents_6);
        if (propertyTable->columnCount() < 2)
            propertyTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        propertyTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        propertyTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (propertyTable->rowCount() < 4)
            propertyTable->setRowCount(4);
        propertyTable->setObjectName(QStringLiteral("propertyTable"));
        propertyTable->setMinimumSize(QSize(0, 180));
        QFont font4;
        font4.setPointSize(9);
        propertyTable->setFont(font4);
        propertyTable->setFrameShadow(QFrame::Sunken);
        propertyTable->setMidLineWidth(0);
        propertyTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        propertyTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        propertyTable->setAutoScroll(true);
        propertyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        propertyTable->setTabKeyNavigation(true);
        propertyTable->setProperty("showDropIndicator", QVariant(true));
        propertyTable->setDragDropOverwriteMode(true);
        propertyTable->setAlternatingRowColors(false);
        propertyTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
        propertyTable->setTextElideMode(Qt::ElideLeft);
        propertyTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        propertyTable->setShowGrid(false);
        propertyTable->setWordWrap(true);
        propertyTable->setCornerButtonEnabled(true);
        propertyTable->setRowCount(4);
        propertyTable->setColumnCount(2);
        propertyTable->horizontalHeader()->setCascadingSectionResizes(false);
        propertyTable->horizontalHeader()->setDefaultSectionSize(100);
        propertyTable->horizontalHeader()->setHighlightSections(true);
        propertyTable->horizontalHeader()->setMinimumSectionSize(25);
        propertyTable->horizontalHeader()->setStretchLastSection(true);
        propertyTable->verticalHeader()->setVisible(false);
        propertyTable->verticalHeader()->setCascadingSectionResizes(false);

        verticalLayout_4->addWidget(propertyTable);

        propertyDock->setWidget(dockWidgetContents_6);
        CloudViewerClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), propertyDock);
        consoleDock = new QDockWidget(CloudViewerClass);
        consoleDock->setObjectName(QStringLiteral("consoleDock"));
        consoleDock->setMinimumSize(QSize(200, 140));
        consoleDock->setMaximumSize(QSize(524287, 220));
        dockWidgetContents_7 = new QWidget();
        dockWidgetContents_7->setObjectName(QStringLiteral("dockWidgetContents_7"));
        verticalLayout_5 = new QVBoxLayout(dockWidgetContents_7);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        consoleTable = new QTableWidget(dockWidgetContents_7);
        if (consoleTable->columnCount() < 5)
            consoleTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        consoleTable->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        consoleTable->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        consoleTable->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        consoleTable->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        consoleTable->setHorizontalHeaderItem(4, __qtablewidgetitem6);
        consoleTable->setObjectName(QStringLiteral("consoleTable"));
        consoleTable->setShowGrid(false);
        consoleTable->setGridStyle(Qt::SolidLine);
        consoleTable->setRowCount(0);
        consoleTable->setColumnCount(5);
        consoleTable->horizontalHeader()->setVisible(true);
        consoleTable->horizontalHeader()->setDefaultSectionSize(200);
        consoleTable->horizontalHeader()->setStretchLastSection(true);
        consoleTable->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(consoleTable);

        consoleDock->setWidget(dockWidgetContents_7);
        CloudViewerClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), consoleDock);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuView_2->menuAction());
        menuBar->addAction(menuGenerate->menuAction());
        menuBar->addAction(menuProcess->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuBar->addAction(menuOption->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuFile->addAction(openAction);
        menuFile->addAction(addAction);
        menuFile->addAction(clearAction);
        menuFile->addAction(saveAction);
        menuFile->addAction(saveBinaryAction);
        menuFile->addAction(changeAction);
        menuFile->addAction(exitAction);
        menuGenerate->addAction(cubeAction);
        menuGenerate->addAction(menuBasic_shapes->menuAction());
        menuBasic_shapes->addAction(sphereAction);
        menuBasic_shapes->addAction(cylinderAction);
        menuAbout->addAction(helpAction);
        menuAbout->addAction(aboutAction);
        menuOption->addAction(themeAction->menuAction());
        menuOption->addAction(langAction->menuAction());
        themeAction->addAction(windowsThemeAction);
        themeAction->addAction(darculaThemeAction);
        langAction->addAction(englishAction);
        langAction->addAction(chineseAction);
        menuView->addAction(pointcolorAction);
        menuView->addAction(bgcolorAction);
        menuView->addAction(menuAngle_view->menuAction());
        menuAngle_view->addAction(mainviewAction);
        menuAngle_view->addAction(leftviewAction);
        menuAngle_view->addAction(topviewAction);
        menuView_2->addAction(dataAction);
        menuView_2->addAction(propertyAction);
        menuView_2->addAction(consoleAction);
        menuView_2->addAction(RGBAction);
        menuProcess->addAction(meshsurfaceAction);
        menuProcess->addAction(wireframeAction);
        menuProcess->addSeparator();
        menuProcess->addAction(actionCSF_lvB);
        menuProcess->addAction(actionlvbo);
        menuProcess->addSeparator();
        menuProcess->addAction(actionlas_pcd);
        menuProcess->addSeparator();
        menuProcess->addAction(actionNpCloud);
        menuProcess->addAction(menuDignalModel->menuAction());
        menuDignalModel->addAction(action_DEM);
        menuDignalModel->addAction(action_DSM);
        menuDignalModel->addAction(action_CHM);
        menu->addAction(actionyuannihe);
        menu_2->addAction(actionJGJL);
        mainToolBar->addAction(openAction);
        mainToolBar->addAction(addAction);
        mainToolBar->addAction(clearAction);
        mainToolBar->addAction(saveAction);
        mainToolBar->addAction(saveBinaryAction);
        mainToolBar->addAction(changeAction);
        mainToolBar->addSeparator();
        mainToolBar->addAction(pointcolorAction);
        mainToolBar->addAction(bgcolorAction);
        mainToolBar->addSeparator();
        mainToolBar->addAction(mainviewAction);
        mainToolBar->addAction(leftviewAction);
        mainToolBar->addAction(topviewAction);
        mainToolBar->addSeparator();
        mainToolBar->addAction(cubeAction);
        mainToolBar->addSeparator();
        mainToolBar->addAction(meshsurfaceAction);
        mainToolBar->addAction(wireframeAction);
        mainToolBar->addSeparator();
        mainToolBar->addAction(helpAction);
        mainToolBar->addAction(aboutAction);

        retranslateUi(CloudViewerClass);

        QMetaObject::connectSlotsByName(CloudViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *CloudViewerClass)
    {
        CloudViewerClass->setWindowTitle(QApplication::translate("CloudViewerClass", "\345\215\225\346\234\250\347\202\271\344\272\221\346\217\220\345\217\226\347\263\273\347\273\237", nullptr));
        openAction->setText(QApplication::translate("CloudViewerClass", "\346\211\223\345\274\200", nullptr));
#ifndef QT_NO_STATUSTIP
        openAction->setStatusTip(QApplication::translate("CloudViewerClass", "open a exsting file", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        openAction->setShortcut(QApplication::translate("CloudViewerClass", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        saveAction->setText(QApplication::translate("CloudViewerClass", "\344\277\235\345\255\230", nullptr));
#ifndef QT_NO_STATUSTIP
        saveAction->setStatusTip(QApplication::translate("CloudViewerClass", "save the file", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        saveAction->setShortcut(QApplication::translate("CloudViewerClass", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        saveasAction->setText(QApplication::translate("CloudViewerClass", "Save as...", nullptr));
        cubeAction->setText(QApplication::translate("CloudViewerClass", "\347\253\213\346\226\271\344\275\223", nullptr));
#ifndef QT_NO_STATUSTIP
        cubeAction->setStatusTip(QApplication::translate("CloudViewerClass", "generate a cube point cloud", nullptr));
#endif // QT_NO_STATUSTIP
        helpAction->setText(QApplication::translate("CloudViewerClass", "\345\270\256\345\212\251", nullptr));
#ifndef QT_NO_STATUSTIP
        helpAction->setStatusTip(QApplication::translate("CloudViewerClass", "show help information", nullptr));
#endif // QT_NO_STATUSTIP
        aboutAction->setText(QApplication::translate("CloudViewerClass", "\345\205\263\344\272\216", nullptr));
#ifndef QT_NO_STATUSTIP
        aboutAction->setStatusTip(QApplication::translate("CloudViewerClass", "show some information of the software", nullptr));
#endif // QT_NO_STATUSTIP
        changeAction->setText(QApplication::translate("CloudViewerClass", "Change", nullptr));
#ifndef QT_NO_STATUSTIP
        changeAction->setStatusTip(QApplication::translate("CloudViewerClass", "change the format of the file", nullptr));
#endif // QT_NO_STATUSTIP
        exitAction->setText(QApplication::translate("CloudViewerClass", "\351\200\200\345\207\272", nullptr));
#ifndef QT_NO_SHORTCUT
        exitAction->setShortcut(QApplication::translate("CloudViewerClass", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        pointcolorAction->setText(QApplication::translate("CloudViewerClass", "\347\202\271\344\272\221\351\242\234\350\211\262", nullptr));
        bgcolorAction->setText(QApplication::translate("CloudViewerClass", "\350\203\214\346\231\257\350\211\262", nullptr));
        mainviewAction->setText(QApplication::translate("CloudViewerClass", "\346\255\243\350\247\206\345\233\276", nullptr));
        leftviewAction->setText(QApplication::translate("CloudViewerClass", "\345\267\246\350\247\206\345\233\276", nullptr));
        topviewAction->setText(QApplication::translate("CloudViewerClass", "\344\277\257\350\247\206\345\233\276", nullptr));
        dataAction->setText(QApplication::translate("CloudViewerClass", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        propertyAction->setText(QApplication::translate("CloudViewerClass", "\345\261\236\346\200\247\347\256\241\347\220\206", nullptr));
        consoleAction->setText(QApplication::translate("CloudViewerClass", "\345\221\275\344\273\244\350\241\214", nullptr));
        RGBAction->setText(QApplication::translate("CloudViewerClass", "\351\242\234\350\211\262\347\256\241\347\220\206", nullptr));
        clearAction->setText(QApplication::translate("CloudViewerClass", "\346\270\205\351\231\244", nullptr));
        addAction->setText(QApplication::translate("CloudViewerClass", "\345\212\240\350\275\275", nullptr));
        sphereAction->setText(QApplication::translate("CloudViewerClass", "Sphere", nullptr));
        cylinderAction->setText(QApplication::translate("CloudViewerClass", "Cylinder", nullptr));
        meshsurfaceAction->setText(QApplication::translate("CloudViewerClass", "Surface", nullptr));
        wireframeAction->setText(QApplication::translate("CloudViewerClass", "Wireframe", nullptr));
        windowsThemeAction->setText(QApplication::translate("CloudViewerClass", "Windows", nullptr));
        darculaThemeAction->setText(QApplication::translate("CloudViewerClass", "Darcula", nullptr));
        englishAction->setText(QApplication::translate("CloudViewerClass", "English", nullptr));
        chineseAction->setText(QApplication::translate("CloudViewerClass", "Chinese", nullptr));
        saveBinaryAction->setText(QApplication::translate("CloudViewerClass", "\344\272\214\350\277\233\345\210\266\344\277\235\345\255\230", nullptr));
#ifndef QT_NO_STATUSTIP
        saveBinaryAction->setStatusTip(QApplication::translate("CloudViewerClass", "Save point cloud as binary file", nullptr));
#endif // QT_NO_STATUSTIP
        actionCSF_lvB->setText(QApplication::translate("CloudViewerClass", "CSF\346\273\244\346\263\242", nullptr));
        actionlvbo->setText(QApplication::translate("CloudViewerClass", "\345\275\242\346\200\201\345\255\246\346\273\244\346\263\242", nullptr));
        actionlas_pcd->setText(QApplication::translate("CloudViewerClass", "las->pcd", nullptr));
        actionNpCloud->setText(QApplication::translate("CloudViewerClass", "\347\202\271\344\272\221\345\275\222\344\270\200\345\214\226", nullptr));
        action_DEM->setText(QApplication::translate("CloudViewerClass", "DEM", nullptr));
        action_DSM->setText(QApplication::translate("CloudViewerClass", "DSM", nullptr));
        action_CHM->setText(QApplication::translate("CloudViewerClass", "CHM", nullptr));
        actionyuannihe->setText(QApplication::translate("CloudViewerClass", "\350\203\270\345\276\204\346\213\237\345\220\210", nullptr));
        actionJGJL->setText(QApplication::translate("CloudViewerClass", "julu", nullptr));
        menuFile->setTitle(QApplication::translate("CloudViewerClass", "\346\226\207\344\273\266", nullptr));
        menuGenerate->setTitle(QApplication::translate("CloudViewerClass", "\346\236\204\345\273\272", nullptr));
        menuBasic_shapes->setTitle(QApplication::translate("CloudViewerClass", "Basic shapes", nullptr));
        menuAbout->setTitle(QApplication::translate("CloudViewerClass", "\345\205\263\344\272\216", nullptr));
        menuOption->setTitle(QApplication::translate("CloudViewerClass", "\351\200\211\351\241\271", nullptr));
        themeAction->setTitle(QApplication::translate("CloudViewerClass", "\344\270\273\351\242\230", nullptr));
        langAction->setTitle(QApplication::translate("CloudViewerClass", "\350\257\255\350\250\200", nullptr));
        menuView->setTitle(QApplication::translate("CloudViewerClass", "\346\230\276\347\244\272", nullptr));
        menuAngle_view->setTitle(QApplication::translate("CloudViewerClass", "\350\247\206\350\247\222", nullptr));
        menuView_2->setTitle(QApplication::translate("CloudViewerClass", "\350\247\206\345\233\276", nullptr));
        menuProcess->setTitle(QApplication::translate("CloudViewerClass", "\350\277\220\350\241\214", nullptr));
        menuDignalModel->setTitle(QApplication::translate("CloudViewerClass", "\346\225\260\345\255\227\346\250\241\345\236\213\347\224\237\346\210\220", nullptr));
        menu->setTitle(QApplication::translate("CloudViewerClass", "\345\217\202\346\225\260\346\217\220\345\217\226", nullptr));
        menu_2->setTitle(QApplication::translate("CloudViewerClass", "\345\217\202\346\225\260\350\256\260\345\275\225", nullptr));
        RGBDock->setWindowTitle(QApplication::translate("CloudViewerClass", "RGB", nullptr));
        label_1->setText(QApplication::translate("CloudViewerClass", "Red", nullptr));
        label_2->setText(QApplication::translate("CloudViewerClass", "Green", nullptr));
        label_3->setText(QApplication::translate("CloudViewerClass", "Blue", nullptr));
        label_4->setText(QApplication::translate("CloudViewerClass", "Point Size", nullptr));
        colorBtn->setText(QApplication::translate("CloudViewerClass", "\351\242\234\350\211\262", nullptr));
        cooCbx->setText(QApplication::translate("CloudViewerClass", "\345\235\220\346\240\207\347\263\273", nullptr));
        bgcCbx->setText(QApplication::translate("CloudViewerClass", "\350\203\214\346\231\257:\351\273\221/\347\231\275", nullptr));
        dataDock->setWindowTitle(QApplication::translate("CloudViewerClass", "\346\225\260\346\215\256", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = dataTree->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("CloudViewerClass", "Point Cloud File", nullptr));
        propertyDock->setWindowTitle(QApplication::translate("CloudViewerClass", "\345\261\236\346\200\247", nullptr));
        QTableWidgetItem *___qtablewidgetitem = propertyTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CloudViewerClass", "Property", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = propertyTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CloudViewerClass", "Value", nullptr));
        consoleDock->setWindowTitle(QApplication::translate("CloudViewerClass", "\345\221\275\344\273\244\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = consoleTable->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("CloudViewerClass", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = consoleTable->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("CloudViewerClass", "Operation", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = consoleTable->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("CloudViewerClass", "Operation obeject", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = consoleTable->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("CloudViewerClass", "\347\273\206\350\212\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = consoleTable->horizontalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("CloudViewerClass", "\345\244\207\346\263\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CloudViewerClass: public Ui_CloudViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOUDVIEWER_H
