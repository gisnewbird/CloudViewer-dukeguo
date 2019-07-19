#include "cloudviewer.h"

CloudViewer::CloudViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/***** Slots connection of QMenuBar and QToolBar *****/
	// File (connect)
	QObject::connect(ui.openAction, &QAction::triggered, this, &CloudViewer::open);
	QObject::connect(ui.addAction, &QAction::triggered, this, &CloudViewer::add);
	QObject::connect(ui.clearAction, &QAction::triggered, this, &CloudViewer::clear);
	QObject::connect(ui.saveAction, &QAction::triggered, this, &CloudViewer::save);
	QObject::connect(ui.saveBinaryAction, &QAction::triggered, this, &CloudViewer::saveBinary);
	QObject::connect(ui.changeAction, &QAction::triggered, this, &CloudViewer::change);
	QObject::connect(ui.exitAction, &QAction::triggered, this, &CloudViewer::exit);
	// Display (connect)
	QObject::connect(ui.pointcolorAction, &QAction::triggered, this, &CloudViewer::pointcolorChanged);
	QObject::connect(ui.bgcolorAction, &QAction::triggered, this, &CloudViewer::bgcolorChanged);
	QObject::connect(ui.mainviewAction, &QAction::triggered, this, &CloudViewer::mainview);
	QObject::connect(ui.leftviewAction, &QAction::triggered, this, &CloudViewer::leftview);
	QObject::connect(ui.topviewAction, &QAction::triggered, this, &CloudViewer::topview);
	// View (connect)
	QObject::connect(ui.dataAction, &QAction::triggered, this, &CloudViewer::data);
	QObject::connect(ui.propertyAction, &QAction::triggered, this, &CloudViewer::properties);
	QObject::connect(ui.consoleAction, &QAction::triggered, this, &CloudViewer::console);
	QObject::connect(ui.RGBAction, &QAction::triggered, this, &CloudViewer::rgbDock);
	// Generate (connect)
	QObject::connect(ui.cubeAction, &QAction::triggered, this, &CloudViewer::cube);
	QObject::connect(ui.sphereAction, &QAction::triggered, this, &CloudViewer::createSphere);
	QObject::connect(ui.cylinderAction, &QAction::triggered, this, &CloudViewer::createCylinder);
	// Process (connect)
	QObject::connect(ui.meshsurfaceAction, &QAction::triggered, this, &CloudViewer::convertSurface);
	QObject::connect(ui.wireframeAction, &QAction::triggered, this, &CloudViewer::convertWireframe);
	// Option (connect)
	QObject::connect(ui.windowsThemeAction, &QAction::triggered, this, &CloudViewer::windowsTheme);
	QObject::connect(ui.darculaThemeAction, &QAction::triggered, this, &CloudViewer::darculaTheme);
	QObject::connect(ui.englishAction, &QAction::triggered, this, &CloudViewer::langEnglish);
	QObject::connect(ui.chineseAction, &QAction::triggered, this, &CloudViewer::langChinese);
	// About (connect)
	QObject::connect(ui.aboutAction, &QAction::triggered, this, &CloudViewer::about);
	QObject::connect(ui.helpAction, &QAction::triggered, this, &CloudViewer::help);

	/***** Slots connection of RGB widget *****/
	// Random color (connect)
	connect(ui.colorBtn, SIGNAL(clicked()), this, SLOT(colorBtnPressed()));
	// Connection between RGB slider and RGB value (connect)
	connect(ui.rSlider, SIGNAL(valueChanged(int)), this, SLOT(rSliderChanged(int)));
	connect(ui.gSlider, SIGNAL(valueChanged(int)), this, SLOT(gSliderChanged(int)));
	connect(ui.bSlider, SIGNAL(valueChanged(int)), this, SLOT(bSliderChanged(int)));
	// RGB slider released (connect)
	connect(ui.rSlider, SIGNAL(sliderReleased()), this, SLOT(RGBsliderReleased()));
	connect(ui.gSlider, SIGNAL(sliderReleased()), this, SLOT(RGBsliderReleased()));
	connect(ui.bSlider, SIGNAL(sliderReleased()), this, SLOT(RGBsliderReleased()));
	// Change size of cloud (connect)
	connect(ui.pSlider, SIGNAL(valueChanged(int)), this, SLOT(pSliderChanged(int)));
	connect(ui.pSlider, SIGNAL(sliderReleased()), this, SLOT(psliderReleased()));
	// Checkbox for coordinate and background color (connect)
	connect(ui.cooCbx, SIGNAL(stateChanged(int)), this, SLOT(cooCbxChecked(int)));
	connect(ui.bgcCbx, SIGNAL(stateChanged(int)), this, SLOT(bgcCbxChecked(int)));

	/***** Slots connection of dataTree(QTreeWidget) widget *****/
	// Item in dataTree is left-clicked (connect)
	connect(ui.dataTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(itemSelected(QTreeWidgetItem*, int)));
	// Item in dataTree is right-clicked
	connect(ui.dataTree, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(popMenu(const QPoint&)));

	connect(ui.consoleTable, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(popMenuInConsole(const QPoint&)));
	
	//"CSF"�����˲�
	connect(ui.actionCSF_lvB, SIGNAL(triggered()), this, SLOT(csfLvBo()));
	//��̬ѧ�˲�
	connect(ui.actionlvbo, SIGNAL(triggered()), this, SLOT(Fenge()));
	//las->pcd
	connect(ui.actionlas_pcd, SIGNAL(triggered()), this, SLOT(las2pcd()));
	//���ƹ�һ��
	connect(ui.actionNpCloud, SIGNAL(triggered()), this, SLOT(norPcloud()));
	//����ģ������
	connect(ui.action_DEM, SIGNAL(triggered()), this, SLOT(createDEM()));
	connect(ui.action_DSM, SIGNAL(triggered()), this, SLOT(createDSM()));
	connect(ui.action_CHM, SIGNAL(triggered()), this, SLOT(createCHM()));
	//�ؾ����
	connect(ui.actionyuannihe, SIGNAL(triggered()), this, SLOT(yuannihe()));
	//
	connect(ui.actionJGJL, SIGNAL(triggered()), this, SLOT(showTreesInfo()));
	// Initialization
	initial();
}

CloudViewer::~CloudViewer()
{

}

// Open point cloud
void CloudViewer::open()
{
	QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Open point cloud file"), QString::fromLocal8Bit(mycloud.dirname.c_str()), tr("Point cloud data(*.pcd *.ply *.obj);;All file(*.*)"));
	//Return if filenames is empty
	if (filenames.isEmpty())
		return;

	// Clear cache
	mycloud_vec.clear();
	total_points = 0;
	ui.dataTree->clear();
	viewer->removeAllPointClouds();

	// Open point cloud one by one
	for (int i = 0; i != filenames.size(); i++){
		// time start
		timeStart();
		mycloud.cloud.reset(new PointCloudT); // Reset cloud
		filename = filenames[i];
		std::string file_name = filename.toStdString();
		std::string subname = getFileName(file_name);  //��ȡȫ·���е��ļ���������׺��

		//����״̬��
		ui.statusBar->showMessage(QString::fromLocal8Bit(subname.c_str()) + ": " + QString::number(i) + "/" + QString::number(filenames.size()) + " point cloud loading...");

		int status = -1;
		if (filename.endsWith(".pcd", Qt::CaseInsensitive))
		{
			status = pcl::io::loadPCDFile(file_name, *(mycloud.cloud));
			if (mycloud.cloud->points[0].r == 0 && mycloud.cloud->points[0].g == 0 && mycloud.cloud->points[0].b == 0)
			{
				setCloudColor(255, 255, 255);
			}
		}
		else if (filename.endsWith(".ply", Qt::CaseInsensitive))
		{
			status = pcl::io::loadPLYFile(file_name, *(mycloud.cloud));
			if (mycloud.cloud->points[0].r == 0 && mycloud.cloud->points[0].g == 0 && mycloud.cloud->points[0].b == 0)
			{
				setCloudColor(255, 255, 255);
			}
		}
		else if (filename.endsWith(".obj", Qt::CaseInsensitive))
		{
			status = pcl::io::loadOBJFile(file_name, *(mycloud.cloud));
			if (mycloud.cloud->points[0].r == 0 && mycloud.cloud->points[0].g == 0 && mycloud.cloud->points[0].b == 0)
			{
				setCloudColor(255, 255, 255);
			}
		}
		else
		{
			//��ʾ���޷���ȡ����.ply .pcd .obj������ļ�
			QMessageBox::information(this, tr("File format error"),
				tr("Can't open files except .ply .pcd .obj"));
			return;
		}
		//��ʾ����׺û���⣬���ļ������޷���ȡ
		if (status != 0)
		{
			QMessageBox::critical(this, tr("Reading file error"), tr("We can not open the file"));
			return;
		}
		setA(255);  //���õ���Ϊ��͸��
		// �����ĵ��Ƶ���Ϣ
		mycloud.filename = file_name;
		mycloud.subname = subname;
		mycloud.dirname = file_name.substr(0, file_name.size() - subname.size());
		mycloud_vec.push_back(mycloud);  //�����Ƶ����������

		
		// time off
		time_cost = timeOff();
		// �������
		consoleLog("Open", QString::fromLocal8Bit(mycloud.subname.c_str()), QString::fromLocal8Bit(mycloud.filename.c_str()), "Time cost: " + time_cost + " s, Points: " + QString::number(mycloud.cloud->points.size()));

		//������Դ������
		QTreeWidgetItem *cloudName = new QTreeWidgetItem(QStringList()
			<< QString::fromLocal8Bit(subname.c_str()));
		cloudName->setIcon(0, QIcon(":/Resources/images/icon.png"));
		ui.dataTree->addTopLevelItem(cloudName);

		//setWindowTitle(filename + " - CloudViewer"); //���±���

		total_points += mycloud.cloud->points.size();
	}
	ui.statusBar->showMessage("");
	showPointcloudAdd();  //������ͼ����
	setPropertyTable();

}

// Add Point Cloud
void CloudViewer::add()
{
	QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Open point cloud file"), QString::fromLocal8Bit(mycloud.dirname.c_str()), tr("Point cloud data(*.pcd *.ply *.obj);;All file(*.*)"));
	if (filenames.isEmpty())
		return;
	for (int i = 0; i != filenames.size(); i++){
		// time start
		timeStart();
		mycloud.cloud.reset(new PointCloudT);
		filename = filenames[i];
		std::string file_name = filename.toStdString();
		std::string subname = getFileName(file_name);

		// ����״̬��
		ui.statusBar->showMessage(QString::fromLocal8Bit(subname.c_str()) + ": " + QString::number(i) + "/" + QString::number(filenames.size()) + " point cloud loading...");

		int status = -1;
		if (filename.endsWith(".pcd", Qt::CaseInsensitive))
		{
			status = pcl::io::loadPCDFile(file_name, *(mycloud.cloud));
			if (mycloud.cloud->points[0].r == 0 && mycloud.cloud->points[0].g == 0 && mycloud.cloud->points[0].b == 0)
			{
				setCloudColor(255, 255, 255);
			}
		}
		else if (filename.endsWith(".ply", Qt::CaseInsensitive))
		{
			status = pcl::io::loadPLYFile(file_name, *(mycloud.cloud));
			if (mycloud.cloud->points[0].r == 0 && mycloud.cloud->points[0].g == 0 && mycloud.cloud->points[0].b == 0)
			{
				setCloudColor(255, 255, 255);
			}
		}
		else if (filename.endsWith(".obj", Qt::CaseInsensitive))
		{
			status = pcl::io::loadOBJFile(file_name, *(mycloud.cloud));
			if (mycloud.cloud->points[0].r == 0 && mycloud.cloud->points[0].g == 0 && mycloud.cloud->points[0].b == 0)
			{
				setCloudColor(255, 255, 255);
			}
		}
		else
		{
			//��ʾ���޷���ȡ����.ply .pcd .obj������ļ�
			QMessageBox::information(this, tr("File format error"), tr("Can't open files except .ply .pcd .obj"));
			return;
		}
		//��ʾ����׺û���⣬���ļ������޷���ȡ
		if (status != 0)
		{
			QMessageBox::critical(this, tr("Reading file error"), tr("We can not open the file"));
			return;
		}
		setA(255);  //���õ���Ϊ��͸��
		mycloud.filename = file_name;
		mycloud.subname = subname;
		mycloud.dirname = file_name.substr(0, file_name.size() - subname.size());
		mycloud_vec.push_back(mycloud);  //�����Ƶ����������

		// time of
		time_cost = timeOff();
		//�������
		consoleLog("Add", QString::fromLocal8Bit(mycloud.subname.c_str()), QString::fromLocal8Bit(mycloud.filename.c_str()), "Time cost: " + time_cost + " s, Points: " + QString::number(mycloud.cloud->points.size()));

		//������Դ������
		QTreeWidgetItem *cloudName = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit(subname.c_str()));
		cloudName->setIcon(0, QIcon(":/Resources/images/icon.png"));
		ui.dataTree->addTopLevelItem(cloudName);

		//setWindowTitle("CloudViewer");
		total_points += mycloud.cloud->points.size();
	}
	ui.statusBar->showMessage("");
	showPointcloudAdd();
	setPropertyTable();

}

// Clear all point clouds
void CloudViewer::clear()
{
	mycloud_vec.clear();  //�ӵ����������Ƴ����е���
	viewer->removeAllPointClouds();  //��viewer���Ƴ����е���
	viewer->removeAllShapes(); //���remove������
	ui.dataTree->clear();  //��dataTree���

	ui.propertyTable->clear();  //������Դ���propertyTable
	QStringList header;
	header << "Property" << "Value";
	ui.propertyTable->setHorizontalHeaderLabels(header);

	//�������
	consoleLog("Clear", "All point clouds", "", "");

	setWindowTitle("CloudViewer");  //���´��ڱ���
	showPointcloud();  //������ʾ
}


// Save point cloud
void CloudViewer::save()
{
	save_filename = QFileDialog::getSaveFileName(this, tr("Save point cloud"),
		QString::fromLocal8Bit(mycloud.dirname.c_str()), tr("Point cloud data(*.pcd *.ply);;Allfile(*.*)"));
	std::string file_name = save_filename.toStdString();
	std::string subname = getFileName(file_name);
	//�ļ���Ϊ��ֱ�ӷ���
	if (save_filename.isEmpty())
		return;

	if (mycloud_vec.size() > 1)
	{
		savemulti();
		return;
	}

	int status = -1;
	if (save_filename.endsWith(".pcd", Qt::CaseInsensitive))
	{
		status = pcl::io::savePCDFile(file_name, *(mycloud.cloud));
	}
	else if (save_filename.endsWith(".ply", Qt::CaseInsensitive))
	{
		status = pcl::io::savePLYFile(file_name, *(mycloud.cloud));
	}
	else //��ʾ���޷�����Ϊ����.ply .pcd������ļ�
	{
		QMessageBox::information(this, tr("File format error"),
			tr("Can't save files except .ply .pcd"));
		return;
	}
	//��ʾ����׺û���⣬�����޷�����
	if (status != 0)
	{
		QMessageBox::critical(this, tr("Saving file error"),
			tr("We can not save the file"));
		return;
	}

	//�������
	consoleLog("Save", QString::fromLocal8Bit(subname.c_str()), save_filename, "Single save");

	setWindowTitle(save_filename + " - CloudViewer");
	QMessageBox::information(this, tr("save point cloud file"),
		QString::fromLocal8Bit(("Save " + subname + " successfully!").c_str()));
}

// Save point cloud as binary file
void CloudViewer::saveBinary()
{
	save_filename = QFileDialog::getSaveFileName(this, tr("Save point cloud as binary file"),
		QString::fromLocal8Bit(mycloud.dirname.c_str()), tr("Point cloud data(*.pcd *.ply);;Allfile(*.*)"));
	std::string file_name = save_filename.toStdString();
	std::string subname = getFileName(file_name);
	//�ļ���Ϊ��ֱ�ӷ���
	if (save_filename.isEmpty())
		return;

	if (mycloud_vec.size() > 1)
	{
		savemulti();
		return;
	}

	int status = -1;
	if (save_filename.endsWith(".pcd", Qt::CaseInsensitive))
	{
		status = pcl::io::savePCDFileBinary(file_name, *(mycloud.cloud));
	}
	else if (save_filename.endsWith(".ply", Qt::CaseInsensitive))
	{
		status = pcl::io::savePLYFileBinary(file_name, *(mycloud.cloud));
	}
	else //��ʾ���޷�����Ϊ����.ply .pcd������ļ�
	{
		QMessageBox::information(this, tr("File format error"),
			tr("Can't save files except .ply .pcd"));
		return;
	}
	//��ʾ����׺û���⣬�����޷�����
	if (status != 0)
	{
		QMessageBox::critical(this, tr("Saving file error"),
			tr("We can not save the file"));
		return;
	}

	//�������
	consoleLog("Save as binary", QString::fromLocal8Bit(subname.c_str()), save_filename, "Single save (binary)");

	setWindowTitle(save_filename + " - CloudViewer");
	QMessageBox::information(this, tr("save point cloud file"),
		QString::fromLocal8Bit(("Save " + subname + " successfully!").c_str()));
}


// Save multi point cloud
void CloudViewer::savemulti()
{
	std::string subname = getFileName(save_filename.toStdString());
	PointCloudT::Ptr multi_cloud;
	multi_cloud.reset(new PointCloudT);
	multi_cloud->height = 1;
	int sum = 0;
	for (auto c : mycloud_vec)
	{
		sum += c.cloud->points.size();
	}
	multi_cloud->width = sum;
	multi_cloud->resize(multi_cloud->height * multi_cloud->width);
	int k = 0;
	for (int i = 0; i != mycloud_vec.size(); i++)
	{
		for (int j = 0; j != mycloud_vec[i].cloud->points.size(); j++)          //ע��cloudvec[i]->points.size()��cloudvec[i]->size()������
		{
			multi_cloud->points[k].x = mycloud_vec[i].cloud->points[j].x;
			multi_cloud->points[k].y = mycloud_vec[i].cloud->points[j].y;
			multi_cloud->points[k].z = mycloud_vec[i].cloud->points[j].z;
			multi_cloud->points[k].r = mycloud_vec[i].cloud->points[j].r;
			multi_cloud->points[k].g = mycloud_vec[i].cloud->points[j].g;
			multi_cloud->points[k].b = mycloud_vec[i].cloud->points[j].b;
			k++;
		}
	}
	//����multi_cloud
	int status = -1;
	if (save_filename.endsWith(".pcd", Qt::CaseInsensitive))
	{
		if (save_as_binary){
			status = pcl::io::savePCDFileBinary(save_filename.toStdString(), *multi_cloud);
		}
		else{
			status = pcl::io::savePCDFile(save_filename.toStdString(), *multi_cloud);
		}
		
	}
	else if (save_filename.endsWith(".ply", Qt::CaseInsensitive))
	{
		if (save_as_binary){
			status = pcl::io::savePLYFileBinary(save_filename.toStdString(), *multi_cloud);
		}
		else{
			status = pcl::io::savePLYFile(save_filename.toStdString(), *multi_cloud);
		}
	}
	else //��ʾ���޷�����Ϊ����.ply .pcd������ļ�
	{
		QMessageBox::information(this, tr("File format error"), tr("Can't save files except .ply .pcd"));
		return;
	}
	
	//��ʾ����׺û���⣬�����޷�����
	if (status != 0)
	{
		QMessageBox::critical(this, tr("Saving file error"), tr("We can not save the file"));
		return;
	}

	// �������
	if (save_as_binary){
		consoleLog("Save as binary", QString::fromLocal8Bit(subname.c_str()), save_filename, "Multi save (binary)");
	}
	else{
		consoleLog("Save", QString::fromLocal8Bit(subname.c_str()), save_filename, "Multi save");
	}
	

	save_as_binary = false;
	//�������� multi_cloud ����Ϊ��ǰ mycloud,�Ա㱣��֮��ֱ�ӽ��в���
	mycloud.cloud = multi_cloud;
	mycloud.filename = save_filename.toStdString();
	mycloud.subname = subname;

	setWindowTitle(save_filename + " - CloudViewer");
	QMessageBox::information(this, tr("save point cloud file"), QString::fromLocal8Bit(("Save " + subname + " successfully!").c_str()));
}




//��ʽת��
void CloudViewer::change()
{

}

//�˳�����
void CloudViewer::exit()
{
	this->close();
}

// Generate cube
void CloudViewer::cube()
{
	mycloud.cloud.reset(new PointCloudT);
	total_points = 0;
	ui.dataTree->clear();  //�����Դ��������item
	viewer->removeAllPointClouds();  //��viewer���Ƴ����е���
	mycloud_vec.clear();  //��յ�������

	mycloud.cloud->width = 50000;         // ���õ��ƿ�
	mycloud.cloud->height = 1;            // ���õ��Ƹߣ���Ϊ1��˵��Ϊ����֯����
	mycloud.cloud->is_dense = false;
	mycloud.cloud->resize(mycloud.cloud->width * mycloud.cloud->height);     // ���õ��ƴ�С
	for (size_t i = 0; i != mycloud.cloud->size(); ++i)
	{
		mycloud.cloud->points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
		mycloud.cloud->points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
		mycloud.cloud->points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
		mycloud.cloud->points[i].r = red;
		mycloud.cloud->points[i].g = green;
		mycloud.cloud->points[i].b = blue;
	}
	//������Դ������
	QTreeWidgetItem *cloudName = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("cube"));
	cloudName->setIcon(0, QIcon(":/Resources/images/icon.png"));
	ui.dataTree->addTopLevelItem(cloudName);

	// �������
	consoleLog("Generate cube", "cube", "cube", "");

	mycloud_vec.push_back(mycloud);
	showPointcloudAdd();
}

//��ʼ��
void CloudViewer::initial()
{
	//�����ʼ��
	setWindowIcon(QIcon(tr(":/Resources/images/icon.png")));
	setWindowTitle(tr("CloudViewer"));

	//���Ƴ�ʼ��
	mycloud.cloud.reset(new PointCloudT);
	mycloud.cloud->resize(1);
	viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
	//viewer->addPointCloud(cloud, "cloud");

	ui.screen->SetRenderWindow(viewer->getRenderWindow());
	viewer->setupInteractor(ui.screen->GetInteractor(), ui.screen->GetRenderWindow());
	ui.screen->update();

	ui.propertyTable->setSelectionMode(QAbstractItemView::NoSelection); // ��ֹ������Թ������� item
	ui.consoleTable->setSelectionMode(QAbstractItemView::NoSelection);  // ��ֹ���������ڵ� item
	ui.dataTree->setSelectionMode(QAbstractItemView::ExtendedSelection); // ���� dataTree ���ж�ѡ

	// ����Ĭ������
	QString qss = darcula_qss;
	qApp->setStyleSheet(qss);

	setPropertyTable();
	setConsoleTable();

	// �������
	consoleLog("Software start", "CloudViewer", "Welcome to use CloudViewer", "Nightn");


	// ���ñ�����ɫΪ dark
	viewer->setBackgroundColor(30 / 255.0, 30 / 255.0, 30 / 255.0);

}

//��ʾ���ƣ�����������Ƕ�
void CloudViewer::showPointcloud()
{
	for (int i = 0; i != mycloud_vec.size(); i++)
	{
		viewer->updatePointCloud(mycloud_vec[i].cloud, "cloud" + QString::number(i).toStdString());
	}
	//viewer->resetCamera();
	ui.screen->update();
}

//��ӵ��Ƶ�viewer,����ʾ����
void CloudViewer::showPointcloudAdd()
{
	for (int i = 0; i != mycloud_vec.size(); i++)
	{
		viewer->addPointCloud(mycloud_vec[i].cloud, "cloud" + QString::number(i).toStdString());
		viewer->updatePointCloud(mycloud_vec[i].cloud, "cloud" + QString::number(i).toStdString());
	}
	viewer->resetCamera();
	ui.screen->update();
}

void CloudViewer::setCloudColor(unsigned int r, unsigned int g, unsigned int b)
{
	// Set the new color
	for (size_t i = 0; i < mycloud.cloud->size(); i++)
	{
		mycloud.cloud->points[i].r = r;
		mycloud.cloud->points[i].g = g;
		mycloud.cloud->points[i].b = b;
		mycloud.cloud->points[i].a = 255;
	}
}

void CloudViewer::setA(unsigned int a)
{
	for (size_t i = 0; i < mycloud.cloud->size(); i++)
	{
		mycloud.cloud->points[i].a = a;
	}
}

//����
void CloudViewer::about()
{
	AboutWin *aboutwin = new AboutWin(this);
	aboutwin->setModal(true);
	aboutwin->show();

	// �������
	consoleLog("About", "DukeGuo", "https://github.com/gisnewbird", "Welcome to my Github!");
}

//����
void CloudViewer::help()
{
	//QDesktopServices::openUrl(QUrl(QLatin1String("http://nightn.com/cloudviewer")));

	//// �������
	//consoleLog("Help", "Cloudviewer help", "http://nightn.com/cloudviewer", "");

	QMessageBox::information(this, "Help", "we are building help widget...");
}


//����ͣ�����ڵ���ʾ������
void CloudViewer::data()
{
	if (ui.dataAction->isChecked())
	{
		ui.dataDock->setVisible(true);
	}
	else
	{
		ui.dataDock->setVisible(false);
	}
}
void CloudViewer::properties()
{
	if (ui.propertyAction->isChecked())
	{
		ui.propertyDock->setVisible(true);
	}
	else
	{
		ui.propertyDock->setVisible(false);
	}
}
void CloudViewer::console()
{
	if (ui.consoleAction->isChecked())
	{
		ui.consoleDock->setVisible(true);
	}
	else
	{
		ui.consoleDock->setVisible(false);
	}
}
void CloudViewer::rgbDock()
{
	if (ui.RGBAction->isChecked())
	{
		ui.RGBDock->setVisible(true);
	}
	else
	{
		ui.RGBDock->setVisible(false);
	}
}

//���ƻ���ͼ��
void CloudViewer::createSphere()
{
	mycloud.cloud.reset(new PointCloudT);
	ui.dataTree->clear();  //�����Դ��������item
	viewer->removeAllShapes();
	mycloud_vec.clear();  //��յ�������

	pcl::PointXYZ p;
	p.x = 0; p.y = 0; p.z = 0;
	viewer->addSphere(p, 100, "sphere1");

	viewer->resetCamera();
	ui.screen->update();

	// �������
	consoleLog("Create sphere", "Sphere", "", "Succeeded");
}
void CloudViewer::createCylinder()
{
	mycloud.cloud.reset(new PointCloudT);
	ui.dataTree->clear();  //�����Դ��������item
	viewer->removeAllShapes();
	mycloud_vec.clear();  //��յ�������

	viewer->addCylinder(*(new pcl::ModelCoefficients()), "cylinder");

	viewer->resetCamera();
	ui.screen->update();

	// �������
	consoleLog("Create cylinder", "Cylinder", "", "Failed");

}

// Change theme: Windows/Darcula
void CloudViewer::windowsTheme(){
	/*
	QFile qssFile("Resources/qss/Windows.qss"); //��Դ�ļ�":/Darcula.qss"
	qssFile.open(QFile::ReadOnly);
	if (qssFile.isOpen())
	{
	QString qss = QLatin1String(qssFile.readAll());
	//consoleLog("", "", "", qss);
	qApp->setStyleSheet(qss);
	qssFile.close();
	}
	*/
	QString qss = windows_qss;
	qApp->setStyleSheet(qss);

	//�ı� dataTree ������ɫ������Ӧ����ı��취
	QColor light_color(241, 241, 241, 255);
	QColor dark_color(0, 0, 0, 255);
	for (int i = 0; i != mycloud_vec.size(); i++){
		if (ui.dataTree->topLevelItem(i)->textColor(0) == light_color){
			ui.dataTree->topLevelItem(i)->setTextColor(0, dark_color);
		}
	}

	// �������
	consoleLog("Change theme", "Windows theme", "", "");

	theme_id = 0;
}
void CloudViewer::darculaTheme(){
	/*
	QFile qssFile("Resources/qss/Darcula.qss"); //��Դ�ļ�":/Darcula.qss"
	qssFile.open(QFile::ReadOnly);
	if (qssFile.isOpen())
	{
	QString qss = QLatin1String(qssFile.readAll());
	//cout << qss.toStdString();
	consoleLog("", "", "", qss);
	qApp->setStyleSheet(qss);
	qssFile.close();
	}
	*/

	QString qss = darcula_qss;
	qApp->setStyleSheet(qss);

	//�ı� dataTree ������ɫ������Ӧ����ı��취
	QColor light_color(241, 241, 241, 255);
	QColor dark_color(0, 0, 0, 255);
	for (int i = 0; i != mycloud_vec.size(); i++){
		if (ui.dataTree->topLevelItem(i)->textColor(0) == dark_color){
			ui.dataTree->topLevelItem(i)->setTextColor(0, light_color);
		}
	}

	// �������
	consoleLog("Change theme", "Darcula theme", "", "");

	theme_id = 1;
}
// Change language: English/Chinese
void CloudViewer::langEnglish(){
	// �������
	consoleLog("Change language", "English", "", "");
}
void CloudViewer::langChinese(){
	// �������
	consoleLog("Change language", "Chinese", "Doesn't support Chinese temporarily", "");
}



/*********************************************/
/*****************����ۺ���*****************/
/********************************************/
void CloudViewer::colorBtnPressed()
{
	QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
	int selected_item_count = ui.dataTree->selectedItems().size();
	// ���δѡ���κε��ƣ������ͼ�����е����е��ƽ�����ɫ
	if (selected_item_count == 0){
		for (int i = 0; i != mycloud_vec.size(); i++){
			for (int j = 0; j != mycloud_vec[i].cloud->points.size(); j++){
				mycloud_vec[i].cloud->points[j].r = 255 * (1024 * rand() / (RAND_MAX + 1.0f));
				mycloud_vec[i].cloud->points[j].g = 255 * (1024 * rand() / (RAND_MAX + 1.0f));
				mycloud_vec[i].cloud->points[j].b = 255 * (1024 * rand() / (RAND_MAX + 1.0f));
			}
		}

		// �������
		consoleLog("Random color", "All point clous", "", "");

	}
	else{
		for (int i = 0; i != selected_item_count; i++){
			int cloud_id = ui.dataTree->indexOfTopLevelItem(itemList[i]);
			for (int j = 0; j != mycloud_vec[cloud_id].cloud->size(); j++){
				mycloud_vec[cloud_id].cloud->points[j].r = red;
				mycloud_vec[cloud_id].cloud->points[j].g = 255 * (1024 * rand() / (RAND_MAX + 1.0f));
				mycloud_vec[cloud_id].cloud->points[j].b = 255 * (1024 * rand() / (RAND_MAX + 1.0f));
			}
		}

		// �������
		consoleLog("Random color", "Point clouds selected", "", "");
	}
	showPointcloud();
}

void CloudViewer::RGBsliderReleased()
{
	QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
	int selected_item_count = ui.dataTree->selectedItems().size();
	// ���δѡ���κε��ƣ������ͼ�����е����е��ƽ�����ɫ
	if (selected_item_count == 0){
		for (int i = 0; i != mycloud_vec.size(); i++){
			for (int j = 0; j != mycloud_vec[i].cloud->points.size(); j++){
				mycloud_vec[i].cloud->points[j].r = red;
				mycloud_vec[i].cloud->points[j].g = green;
				mycloud_vec[i].cloud->points[j].b = blue;
			}
		}

		// �������
		consoleLog("Change cloud color", "All point clouds", QString::number(red) + " " + QString::number(green) + " " + QString::number(blue), "");
	}
	else{
		for (int i = 0; i != selected_item_count; i++){
			int cloud_id = ui.dataTree->indexOfTopLevelItem(itemList[i]);
			for (int j = 0; j != mycloud_vec[cloud_id].cloud->size(); j++){
				mycloud_vec[cloud_id].cloud->points[j].r = red;
				mycloud_vec[cloud_id].cloud->points[j].g = green;
				mycloud_vec[cloud_id].cloud->points[j].b = blue;
			}
		}
		// �������
		consoleLog("Change cloud color", "Point clouds selected", QString::number(red) + " " + QString::number(green) + " " + QString::number(blue), "");
	}
	showPointcloud();
}

//�������е��Ƶĳߴ�
void CloudViewer::psliderReleased()
{
	QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
	int selected_item_count = ui.dataTree->selectedItems().size();
	if (selected_item_count == 0){
		for (int i = 0; i != mycloud_vec.size(); i++){
			viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,
				p, "cloud" + QString::number(i).toStdString());
		}
		// �������
		consoleLog("Change cloud size", "All point clouds", "Size: " + QString::number(p), "");
	}
	else{
		for (int i = 0; i != selected_item_count; i++){
			int cloud_id = ui.dataTree->indexOfTopLevelItem(itemList[i]);
			viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,
				p, "cloud" + QString::number(cloud_id).toStdString());
		}
		// �������
		consoleLog("Change cloud size", "Point clouds selected", "Size: " + QString::number(p), "");
	}
	ui.screen->update();
}
void CloudViewer::pSliderChanged(int value)
{
	p = value;
	ui.sizeLCD->display(value);

}
void CloudViewer::rSliderChanged(int value)
{
	red = value;
	ui.rLCD->display(value);
}
void CloudViewer::gSliderChanged(int value)
{
	green = value;
	ui.gLCD->display(value);
}
void CloudViewer::bSliderChanged(int value)
{
	blue = value;
	ui.bLCD->display(value);
}

void CloudViewer::cooCbxChecked(int value)
{
	switch (value)
	{
	case 0:
		viewer->removeCoordinateSystem();  //�Ƴ�����ϵ
		// �������
		consoleLog("Remove coordinate system", "Remove", "", "");
		break;
	case 2:
		viewer->addCoordinateSystem();  //�������ϵ
		// �������
		consoleLog("Add coordinate system", "Add", "", "");
		break;
	}
	//viewer->updatePointCloud(cloud, "cloud");
	ui.screen->update();
}
void CloudViewer::bgcCbxChecked(int value)
{
	switch (value)
	{
	case 0:
		viewer->setBackgroundColor(30 / 255.0, 30 / 255.0, 30 / 255.0);
		// �������
		consoleLog("Change bg color", "Background", "30 30 30", "");
		break;
	case 2:
		//��ע�⣺setBackgroundColor()���յ���0-1��double�Ͳ���
		viewer->setBackgroundColor(240 / 255.0, 240 / 255.0, 240 / 255.0);
		// �������
		consoleLog("Change bg color", "Background", "240 240 240", "");
		break;
	}
	//viewer->updatePointCloud(cloud, "cloud");
	ui.screen->update();
}


//ͨ����ɫ�Ի���ı������ɫ
void CloudViewer::pointcolorChanged()
{
	QColor color = QColorDialog::getColor(Qt::white, this, "Select color for point cloud");

	if (color.isValid()) //�ж���ѡ����ɫ�Ƿ���Ч
	{
		//QAction* action = dynamic_cast<QAction*>(sender());
		//if (action != ui.pointcolorAction) //�ı���ɫ���ź������� dataTree
		QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
		int selected_item_count = ui.dataTree->selectedItems().size();
		if (selected_item_count == 0){
			for (int i = 0; i != mycloud_vec.size(); i++){
				for (int j = 0; j != mycloud_vec[i].cloud->points.size(); j++){
					mycloud_vec[i].cloud->points[j].r = color.red();
					mycloud_vec[i].cloud->points[j].g = color.green();
					mycloud_vec[i].cloud->points[j].b = color.blue();
				}
			}
			// �������
			consoleLog("Change cloud color", "All point clouds", QString::number(color.red()) + " " + QString::number(color.green()) + " " + QString::number(color.blue()), "");
		}
		else{
			for (int i = 0; i != selected_item_count; i++){
				int cloud_id = ui.dataTree->indexOfTopLevelItem(itemList[i]);
				for (int j = 0; j != mycloud_vec[cloud_id].cloud->size(); j++){
					mycloud_vec[cloud_id].cloud->points[j].r = color.red();
					mycloud_vec[cloud_id].cloud->points[j].g = color.green();
					mycloud_vec[cloud_id].cloud->points[j].b = color.blue();
				}
			}
			// �������
			consoleLog("Change cloud color", "Point clouds selected", QString::number(color.red()) + " " + QString::number(color.green()) + " " + QString::number(color.blue()), "");
		}
		//��ɫ�ĸı�ͬ����RGBͣ������
		ui.rSlider->setValue(color.red());
		ui.gSlider->setValue(color.green());
		ui.bSlider->setValue(color.blue());

		showPointcloud();
	}
}

//ͨ����ɫ�Ի���ı䱳����ɫ
void CloudViewer::bgcolorChanged()
{
	QColor color = QColorDialog::getColor(Qt::white, this,
		"Select color for point cloud");
	if (color.isValid())
	{
		viewer->setBackgroundColor(color.red() / 255.0,
			color.green() / 255.0, color.blue() / 255.0);
		// �������
		consoleLog("Change bg color", "Background", QString::number(color.red()) + " " + QString::number(color.green()) + " " + QString::number(color.blue()), "");
		showPointcloud();
	}
}

//����ͼ
void CloudViewer::mainview()
{
	viewer->setCameraPosition(0, -1, 0, 0.5, 0.5, 0.5, 0, 0, 1);
	ui.screen->update();
}
void CloudViewer::leftview()
{
	viewer->setCameraPosition(-1, 0, 0, 0, 0, 0, 0, 0, 1);
	ui.screen->update();
}
void CloudViewer::topview()
{
	viewer->setCameraPosition(0, 0, 1, 0, 0, 0, 0, 1, 0);
	ui.screen->update();
}

//�������Թ�����
void CloudViewer::setPropertyTable(){

	QStringList header;
	header << "Property" << "Value";
	ui.propertyTable->setHorizontalHeaderLabels(header);
	ui.propertyTable->setItem(0, 0, new QTableWidgetItem("Clouds"));
	ui.propertyTable->setItem(1, 0, new QTableWidgetItem("Points"));
	ui.propertyTable->setItem(2, 0, new QTableWidgetItem("Total points"));
	ui.propertyTable->setItem(3, 0, new QTableWidgetItem("RGB"));


	ui.propertyTable->setItem(0, 1, new QTableWidgetItem(QString::number(mycloud_vec.size())));
	ui.propertyTable->setItem(1, 1, new QTableWidgetItem(""));
	ui.propertyTable->setItem(2, 1, new QTableWidgetItem(QString::number(total_points)));
	ui.propertyTable->setItem(4, 1, new QTableWidgetItem(""));

}

void CloudViewer::setConsoleTable(){
	// �����������
	QStringList header2;
	header2 << "Time" << "Operation" << "Operation obeject" << "Details" << "Note";
	ui.consoleTable->setHorizontalHeaderLabels(header2);
	ui.consoleTable->setColumnWidth(0, 150);
	ui.consoleTable->setColumnWidth(1, 200);
	ui.consoleTable->setColumnWidth(2, 200);
	ui.consoleTable->setColumnWidth(3, 300);

	//ui.consoleTable->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ò��ɱ༭
	ui.consoleTable->verticalHeader()->setDefaultSectionSize(22); //�����о�

	ui.consoleTable->setContextMenuPolicy(Qt::CustomContextMenu);

}

//
void CloudViewer::consoleLog(QString operation, QString subname, QString filename, QString note)
{
	if (enable_console == false){
		return;
	}
	int rows = ui.consoleTable->rowCount();
	ui.consoleTable->setRowCount(++rows);
	QDateTime time = QDateTime::currentDateTime();//��ȡϵͳ���ڵ�ʱ��
	QString time_str = time.toString("MM-dd hh:mm:ss"); //������ʾ��ʽ
	ui.consoleTable->setItem(rows - 1, 0, new QTableWidgetItem(time_str));
	ui.consoleTable->setItem(rows - 1, 1, new QTableWidgetItem(operation));
	ui.consoleTable->setItem(rows - 1, 2, new QTableWidgetItem(subname));
	ui.consoleTable->setItem(rows - 1, 3, new QTableWidgetItem(filename));
	ui.consoleTable->setItem(rows - 1, 4, new QTableWidgetItem(note));

	ui.consoleTable->scrollToBottom(); // �����Զ�������ײ�
}


//QTreeWidget��item�ĵ����Ӧ����
void CloudViewer::itemSelected(QTreeWidgetItem* item, int count)
{
	count = ui.dataTree->indexOfTopLevelItem(item);  //��ȡitem���к�

	for (int i = 0; i != mycloud_vec.size(); i++)
	{
		viewer->updatePointCloud(mycloud_vec[i].cloud, "cloud" + QString::number(i).toStdString());
		viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud" + QString::number(i).toStdString());
	}

	//��ȡ��ǰ���Ƶ�RGB,������������Ϣ
	int cloud_size = mycloud_vec[count].cloud->points.size();
	unsigned int cloud_r = mycloud_vec[count].cloud->points[0].r;
	unsigned int cloud_g = mycloud_vec[count].cloud->points[0].g;
	unsigned int cloud_b = mycloud_vec[count].cloud->points[0].b;
	bool multi_color = true;
	if (mycloud_vec[count].cloud->points.begin()->r == (mycloud_vec[count].cloud->points.end() - 1)->r) //�жϵ��Ƶ�ɫ��ɫ�����������Ǻ��Ͻ���
		multi_color = false;

	ui.propertyTable->setItem(0, 1, new QTableWidgetItem(QString::number(mycloud_vec.size())));
	ui.propertyTable->setItem(1, 1, new QTableWidgetItem(QString::number(cloud_size)));
	ui.propertyTable->setItem(2, 1, new QTableWidgetItem(QString::number(total_points)));
	ui.propertyTable->setItem(3, 1, new QTableWidgetItem(multi_color ? "Multi Color" : (QString::number(cloud_r) + " " + QString::number(cloud_g) + " " + QString::number(cloud_b))));

	//ѡ��item����Ӧ�ĵ��Ƴߴ���
	QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
	int selected_item_count = ui.dataTree->selectedItems().size();
	for (int i = 0; i != selected_item_count; i++){
		int cloud_id = ui.dataTree->indexOfTopLevelItem(itemList[i]);
		viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,
			2, "cloud" + QString::number(cloud_id).toStdString());
	}
	//mycloud = mycloud_vec[count];
	ui.screen->update();
}

// consoleTable �һ���Ӧ�¼�
void CloudViewer::popMenuInConsole(const QPoint&){
	QAction clearConsoleAction("Clear console", this);
	QAction enableConsoleAction("Enable console", this);
	QAction disableConsoleAction("Disable console", this);

	connect(&clearConsoleAction, &QAction::triggered, this, &CloudViewer::clearConsole);
	connect(&enableConsoleAction, &QAction::triggered, this, &CloudViewer::enableConsole);
	connect(&disableConsoleAction, &QAction::triggered, this, &CloudViewer::disableConsole);

	QPoint pos;
	QMenu menu(ui.dataTree);
	menu.addAction(&clearConsoleAction);
	menu.addAction(&enableConsoleAction);
	menu.addAction(&disableConsoleAction);

	if (enable_console == true){
		menu.actions()[1]->setVisible(false);
		menu.actions()[2]->setVisible(true);
	}
	else{
		menu.actions()[1]->setVisible(true);
		menu.actions()[2]->setVisible(false);
	}

	menu.exec(QCursor::pos()); //�ڵ�ǰ���λ����ʾ
}
// ��� consoleTable
void CloudViewer::clearConsole(){
	ui.consoleTable->clearContents();
	ui.consoleTable->setRowCount(0);
}
// ����ʹ�� consoleTable
void CloudViewer::enableConsole(){
	enable_console = true;
}
// ���� consoleTable
void CloudViewer::disableConsole(){
	clearConsole();
	enable_console = false;

}

//QTreeWidget��item���һ���Ӧ����
void CloudViewer::popMenu(const QPoint&)
{
	QTreeWidgetItem* curItem = ui.dataTree->currentItem(); //��ȡ��ǰ������Ľڵ�
	if (curItem == NULL)return;           //����������Ҽ���λ�ò���treeItem�ķ�Χ�ڣ����ڿհ�λ���һ�
	QString name = curItem->text(0);
	int id = ui.dataTree->indexOfTopLevelItem(curItem);
	string cloud_id = "cloud" + QString::number(id).toStdString();

	QAction hideItemAction("Hide", this);
	QAction showItemAction("Show", this);
	QAction deleteItemAction("Delete", this);
	QAction changeColorAction("Change color", this);

	connect(&hideItemAction, &QAction::triggered, this, &CloudViewer::hideItem);
	connect(&showItemAction, &QAction::triggered, this, &CloudViewer::showItem);
	connect(&deleteItemAction, &QAction::triggered, this, &CloudViewer::deleteItem);
	connect(&changeColorAction, &QAction::triggered, this, &CloudViewer::pointcolorChanged);

	QPoint pos;
	QMenu menu(ui.dataTree);
	menu.addAction(&hideItemAction);
	menu.addAction(&showItemAction);
	menu.addAction(&deleteItemAction);
	menu.addAction(&changeColorAction);

	if (mycloud_vec[id].visible == true){
		menu.actions()[1]->setVisible(false);
		menu.actions()[0]->setVisible(true);
	}
	else{
		menu.actions()[1]->setVisible(true);
		menu.actions()[0]->setVisible(false);
	}


	menu.exec(QCursor::pos()); //�ڵ�ǰ���λ����ʾ
}
void CloudViewer::hideItem()
{
	QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
	for (int i = 0; i != ui.dataTree->selectedItems().size(); i++){
		//TODO hide֮��item��ɻ�ɫ���ٴ��һ�itemʱ����hideItem�� ѡ���� ��showItem��
		//QTreeWidgetItem* curItem = ui.dataTree->currentItem();
		QTreeWidgetItem* curItem = itemList[i];
		QString name = curItem->text(0);
		int id = ui.dataTree->indexOfTopLevelItem(curItem);
		string cloud_id = "cloud" + QString::number(id).toStdString();
		//QMessageBox::information(this, "cloud_id", QString::fromLocal8Bit(cloud_id.c_str()));
		// ��cloud_id����Ӧ�ĵ������ó�͸��
		viewer->setPointCloudRenderingProperties(pcl::visualization::RenderingProperties::PCL_VISUALIZER_OPACITY, 0.0, cloud_id, 0);
		QColor item_color = QColor(112, 122, 132, 255);
		curItem->setTextColor(0, item_color);
		mycloud_vec[id].visible = false;
	}

	// �������
	consoleLog("Hide point clouds", "Point clouds selected", "", "");

	ui.screen->update(); //ˢ����ͼ���ڣ�����ʡ��
}

void CloudViewer::showItem()
{
	QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
	for (int i = 0; i != ui.dataTree->selectedItems().size(); i++){
		//QTreeWidgetItem* curItem = ui.dataTree->currentItem();
		QTreeWidgetItem* curItem = itemList[i];
		QString name = curItem->text(0);
		int id = ui.dataTree->indexOfTopLevelItem(curItem);
		string cloud_id = "cloud" + QString::number(id).toStdString();
		// ��cloud_id����Ӧ�ĵ������ó�͸��
		viewer->setPointCloudRenderingProperties(pcl::visualization::RenderingProperties::PCL_VISUALIZER_OPACITY, 1.0, cloud_id, 0);
		QColor item_color;
		if (theme_id == 0){
			item_color = QColor(0, 0, 0, 255);
		}
		else{
			item_color = QColor(241, 241, 241, 255);
		}
		curItem->setTextColor(0, item_color);
		mycloud_vec[id].visible = true;
	}

	// �������
	consoleLog("Show point clouds", "Point clouds selected", "", "");

	ui.screen->update(); //ˢ����ͼ���ڣ�����ʡ��

}

void CloudViewer::deleteItem()
{
	QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
	// ui.dataTree->selectedItems().size() ���ŵ����������ı䣬���ѭ������Ҫ����Ϊ�̶���С�� selected_item_count
	int selected_item_count = ui.dataTree->selectedItems().size();
	for (int i = 0; i != selected_item_count; i++){
		//QTreeWidgetItem* curItem = ui.dataTree->currentItem();
		//QMessageBox::information(this, "itemList's size", QString::number(ui.dataTree->selectedItems().size()));
		QTreeWidgetItem* curItem = itemList[i];
		QString name = curItem->text(0);
		int id = ui.dataTree->indexOfTopLevelItem(curItem);
		//QMessageBox::information(this, "information", "curItem: " + name + " " + QString::number(id));
		auto it = mycloud_vec.begin() + ui.dataTree->indexOfTopLevelItem(curItem);
		// ɾ������֮ǰ����������Ŀ����
		int delete_points = (*it).cloud->points.size();
		it = mycloud_vec.erase(it);
		//QMessageBox::information(this, "information", QString::number(delete_points) + " " + QString::number(mycloud_vec.size()));

		total_points -= delete_points;
		setPropertyTable();

		ui.dataTree->takeTopLevelItem(ui.dataTree->indexOfTopLevelItem(curItem));
	}

	// �Ƴ�֮������ӣ����� id ����Դ�������кŲ�һ�µ����
	viewer->removeAllPointClouds();
	for (int i = 0; i != mycloud_vec.size(); i++)
	{
		viewer->addPointCloud(mycloud_vec[i].cloud, "cloud" + QString::number(i).toStdString());
		viewer->updatePointCloud(mycloud_vec[i].cloud, "cloud" + QString::number(i).toStdString());
	}

	// �������
	consoleLog("Delete point clouds", "Point clouds selected", "", "");

	ui.screen->update();
}


//���߹��ơ������ؽ���������Ƭ��ʾ
int CloudViewer::convertSurface()
{
	/* ����
	����÷���ֻ�ܴ���PointXYZ�ĵ��ƣ���PointXZYRGBA�ĵ��Ʊ���ᱨ��
	����boost::this_thread::sleep����Ҳ��������
	*/
	pcl::PointXYZ point;
	cloud_xyz.reset(new pcl::PointCloud<pcl::PointXYZ>);
	for (size_t i = 0; i < mycloud.cloud->size(); i++)
	{
		point.x = mycloud.cloud->points[i].x;
		point.y = mycloud.cloud->points[i].y;
		point.z = mycloud.cloud->points[i].z;
		cloud_xyz->push_back(point);
	}
	if (!cloud_xyz)
	{
		return -1;
	}

	/****** �������ģ�� ******/
	//�������߹��ƶ��� n
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	//������������ָ�� normals
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	//���� kdtree ���ڷ������ʱ��������
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud_xyz); //Ϊ kdtree �������
	n.setInputCloud(cloud_xyz); //Ϊ������ƶ����������
	n.setSearchMethod(tree);  //���÷������ʱ����ȡ��������ʽΪkdtree
	n.setKSearch(20); //���÷������ʱ��k���������ĵ���
	n.compute(*normals); //���з������

	QMessageBox::information(this, "information", "Normal estimation finished");

	/****** ���������뷨������ƴ�� ******/
	//����֮���������

	//����ͬʱ������ͷ��ߵ����ݽṹ��ָ��
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);

	//���ѻ�õĵ����ݺͷ�������ƴ��
	pcl::concatenateFields(*cloud_xyz, *normals, *cloud_with_normals); //������������cloud�������йأ��ĳ�PointXYZ�ĵ��ƾ�û�б�����

	//������һ��kdtree�����ؽ�
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
	//Ϊkdtree����������ݣ��õ�����������Ϊ��ͷ���
	tree2->setInputCloud(cloud_with_normals);

	/****** �����ؽ�ģ�� ******/
	//����̰��������ͶӰ�ؽ�����
	pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
	//���������������������洢�ؽ����
	pcl::PolygonMesh triangles;
	//���ò���
	gp3.setSearchRadius(25); //�������ӵ�֮�������룬����ȷ��k���ڵ���뾶
	gp3.setMu(2.5); //��������ھ���ĳ��ӣ��Եõ�ÿ��������������뾶
	gp3.setMaximumNearestNeighbors(100); //��������������ڵ���������
	gp3.setMaximumSurfaceAngle(M_PI / 2); //45�� ���ƽ���
	gp3.setMinimumAngle(M_PI / 18); //10�� ÿ�����ǵ����Ƕȣ�
	gp3.setMaximumAngle(2 * M_PI / 3); //120��
	gp3.setNormalConsistency(false); //��������һ�£���Ϊtrue
	//���õ������ݺ�������ʽ
	gp3.setInputCloud(cloud_with_normals);
	gp3.setSearchMethod(tree2);
	// ��ʼ�ؽ�
	gp3.reconstruct(triangles);
	QMessageBox::information(this, "informaiton", "Reconstruction finished");

	//���ؽ�������浽Ӳ���ļ��У��ؽ������VTK��ʽ�洢
	pcl::io::saveVTKFile("mymesh.vtk", triangles);

	/*
	//Additional vertex information
	std::vector<int> parts = gp3.getPartIDs();
	std::vector<int> states = gp3.getPointStates();
	fstream fs;
	fs.open("partsID.txt", ios::out);
	if (!fs)
	{
	return -2;
	}
	fs << "number of point clouds:" << parts.size() << "\n";
	for (int i = 0; i < parts.size(); i++)
	{
	if (parts[i] != 0)
	{
	fs << parts[i] << "\n";
	}
	}
	*/

	/****** ͼ����ʾģ�� ******/
	QMessageBox::information(this, "informaiton", "Start to show");
	viewer->addPolygonMesh(triangles, "my"); //����Ҫ��ʾ���������
	//��������ģ����ʾģʽ
	viewer->setRepresentationToSurfaceForAllActors(); //����ģ������Ƭ��ʽ��ʾ
	//viewer->setRepresentationToPointsForAllActors(); //����ģ���Ե���ʽ��ʾ
	//viewer->setRepresentationToWireframeForAllActors(); //����ģ�����߿�ͼģʽ��ʾ

	// �������
	consoleLog("Convert surface", "", "", "");

	viewer->removeAllShapes();
	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		//boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	return 0;

}

int CloudViewer::convertWireframe()
{
	/* ����
	����÷���ֻ�ܴ���PointXYZ�ĵ��ƣ���PointXZYRGBA�ĵ��Ʊ���ᱨ��
	����boost::this_thread::sleep����Ҳ��������
	*/
	pcl::PointXYZ point;
	cloud_xyz.reset(new pcl::PointCloud<pcl::PointXYZ>);
	for (size_t i = 0; i < mycloud.cloud->size(); i++)
	{
		point.x = mycloud.cloud->points[i].x;
		point.y = mycloud.cloud->points[i].y;
		point.z = mycloud.cloud->points[i].z;
		cloud_xyz->push_back(point);
	}
	if (!cloud_xyz)
	{
		return -1;
	}


	/****** �������ģ�� ******/
	//�������߹��ƶ��� n
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	//������������ָ�� normals
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	//���� kdtree ���ڷ������ʱ��������
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud_xyz); //Ϊ kdtree �������
	n.setInputCloud(cloud_xyz); //Ϊ������ƶ����������
	n.setSearchMethod(tree);  //���÷������ʱ����ȡ��������ʽΪkdtree
	n.setKSearch(20); //���÷������ʱ��k���������ĵ���
	n.compute(*normals); //���з������

	QMessageBox::information(this, "information", "Normal estimation finished");

	/****** ���������뷨������ƴ�� ******/
	//����֮���������

	//����ͬʱ������ͷ��ߵ����ݽṹ��ָ��
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);

	//���ѻ�õĵ����ݺͷ�������ƴ��
	pcl::concatenateFields(*cloud_xyz, *normals, *cloud_with_normals); //������������cloud�������йأ��ĳ�PointXYZ�ĵ��ƾ�û�б�����

	//������һ��kdtree�����ؽ�
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
	//Ϊkdtree����������ݣ��õ�����������Ϊ��ͷ���
	tree2->setInputCloud(cloud_with_normals);



	/****** �����ؽ�ģ�� ******/
	//����̰��������ͶӰ�ؽ�����
	pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
	//���������������������洢�ؽ����
	pcl::PolygonMesh triangles;
	//���ò���
	gp3.setSearchRadius(25); //�������ӵ�֮�������룬����ȷ��k���ڵ���뾶
	gp3.setMu(2.5); //��������ھ���ĳ��ӣ��Եõ�ÿ��������������뾶
	gp3.setMaximumNearestNeighbors(100); //��������������ڵ���������
	gp3.setMaximumSurfaceAngle(M_PI / 2); //45�� ���ƽ���
	gp3.setMinimumAngle(M_PI / 18); //10�� ÿ�����ǵ����Ƕȣ�
	gp3.setMaximumAngle(2 * M_PI / 3); //120��
	gp3.setNormalConsistency(false); //��������һ�£���Ϊtrue
	//���õ������ݺ�������ʽ
	gp3.setInputCloud(cloud_with_normals);
	gp3.setSearchMethod(tree2);
	// ��ʼ�ؽ�
	gp3.reconstruct(triangles);
	QMessageBox::information(this, "informaiton", "Reconstruction finished");

	//���ؽ�������浽Ӳ���ļ��У��ؽ������VTK��ʽ�洢
	pcl::io::saveVTKFile("mymesh.vtk", triangles);

	/*
	//Additional vertex information
	std::vector<int> parts = gp3.getPartIDs();
	std::vector<int> states = gp3.getPointStates();
	fstream fs;
	fs.open("partsID.txt", ios::out);
	if (!fs)
	{
	return -2;
	}
	fs << "number of point clouds:" << parts.size() << "\n";
	for (int i = 0; i < parts.size(); i++)
	{
	if (parts[i] != 0)
	{
	fs << parts[i] << "\n";
	}
	}
	*/

	/****** ͼ����ʾģ�� ******/
	QMessageBox::information(this, "informaiton", "Start to show");
	viewer->addPolygonMesh(triangles, "my"); //����Ҫ��ʾ���������
	//��������ģ����ʾģʽ
	//viewer->setRepresentationToSurfaceForAllActors(); //����ģ������Ƭ��ʽ��ʾ
	//viewer->setRepresentationToPointsForAllActors(); //����ģ���Ե���ʽ��ʾ
	viewer->setRepresentationToWireframeForAllActors(); //����ģ�����߿�ͼģʽ��ʾ

	// �������
	consoleLog("Convert wireframe", "", "", "");

	viewer->removeAllShapes();
	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		//boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	return 0;

}

//�����˲�
void CloudViewer::csfLvBo()
{
	QsCSFLvBo *csf = new QsCSFLvBo;
	csf->exec();
}
//��̬ѧ�˲�
void CloudViewer::Fenge()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointIndicesPtr ground(new pcl::PointIndices);
	//������PCD
	//pcl::PCDReader reader;
	//reader.read<pcl::PointXYZ>("C:\\Users\\duke\\Desktop\\123.pcd", *cloud);
	pcl::PLYReader reader;
	reader.read<pcl::PointXYZ>(filename.toStdString(), *cloud);

	std::cerr << "Cloud before filtering: " << std::endl;
	std::cerr << *cloud << std::endl;

	// ������̬ѧ�˲�������
	pcl::ProgressiveMorphologicalFilter<pcl::PointXYZ> pmf;
	pmf.setInputCloud(cloud);

	// ���ù��˵����Ĵ��ڳߴ�
	pmf.setMaxWindowSize(20);

	// ���ü���߶���ֵ��б��ֵ
	pmf.setSlope(1.0f);

	// ���ó�ʼ�߶Ȳ�������Ϊ�ǵ����
	pmf.setInitialDistance(0.5f);

	// ���ñ���Ϊ�ǵ��������߶�
	pmf.setMaxDistance(2.0f);
	pmf.extract(ground->indices);

	// Create the filtering object
	pcl::ExtractIndices<pcl::PointXYZ> extract;
	extract.setInputCloud(cloud);
	extract.setIndices(ground);
	extract.filter(*cloud_filtered);

	std::cerr << "Ground cloud after filtering: " << std::endl;
	std::cerr << *cloud_filtered << std::endl;

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered_RGB(new pcl::PointCloud<pcl::PointXYZRGB>);
	cloud_filtered_RGB->resize(cloud_filtered->size());
	cloud_filtered_RGB->is_dense = FALSE;

	for (size_t i = 0; i < cloud_filtered->points.size(); ++i)
	{
		cloud_filtered_RGB->points[i].x = cloud_filtered->points[i].x;
		cloud_filtered_RGB->points[i].y = cloud_filtered->points[i].y;
		cloud_filtered_RGB->points[i].z = cloud_filtered->points[i].z;

		cloud_filtered_RGB->points[i].r = 0;
		cloud_filtered_RGB->points[i].g = 255;
		cloud_filtered_RGB->points[i].b = 0;
	}

	//pcl::io::savePCDFileBinary("C:\\Users\\duke\\Desktop\\cloud_groud.pcd", *cloud_filtered_RGB);
	pcl::io::savePLYFileBinary("C:\\Users\\duke\\Desktop\\testascii_cloud_groud.ply", *cloud_filtered_RGB);
	// ��ȡ�ǵ����
	extract.setNegative(true);
	extract.filter(*cloud_filtered);

	std::cerr << "Object cloud after filtering: " << std::endl;
	std::cerr << *cloud_filtered << std::endl;

	//pcl::io::savePCDFileBinary("C:\\Users\\duke\\Desktop\\No_groud.pcd", *cloud_filtered);
	pcl::io::savePLYFileBinary("C:\\Users\\duke\\Desktop\\testascii_No_groud.ply", *cloud_filtered);
	
	QMessageBox::information(this, u8"���", u8"�˲����");
}
//las��ʽתpcd
void CloudViewer::las2pcd()
{
	QsConvertFormat *cF = new QsConvertFormat;
	cF->exec();
}
//��һ��
void CloudViewer::norPcloud()
{
	QsNorPcloud* np = new QsNorPcloud;
	np->exec();
}
//����DEM
void CloudViewer::createDEM()
{
	QsCreateDEM* cDem = new QsCreateDEM;
	cDem->exec();
}
//����DSM
void CloudViewer::createDSM()
{
	QsCreateDSM* cDsm = new QsCreateDSM;
	cDsm->exec();
}
//����CHM
void CloudViewer::createCHM()
{
	QsCreateCHM* cChm = new QsCreateCHM;
	cChm->exec();
}

//#include "pch.h"
#include <iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/point_cloud.h>
#include<pcl/segmentation/sac_segmentation.h>
#include<pcl/search/search.h>
#include<pcl/search/kdtree.h>
#include<pcl/features/normal_3d.h>
#include<pcl/common/common.h>


// use ransanc to fit cylinder
void fitCylinder(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud_out) {
	// Create segmentation object for cylinder segmentation and set all the parameters
	pcl::ModelCoefficients::Ptr coeffients_cylinder(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr inliers_cylinder(new pcl::PointIndices);

	//  Normals
	pcl::search::Search<pcl::PointXYZ>::Ptr tree = boost::shared_ptr<pcl::search::Search<pcl::PointXYZ>>(new pcl::search::KdTree<pcl::PointXYZ>);
	pcl::PointCloud<pcl::Normal>::Ptr normalsFilter(new pcl::PointCloud<pcl::Normal>);
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimator;
	normalEstimator.setSearchMethod(tree);
	normalEstimator.setInputCloud(cloud_in);
	normalEstimator.setKSearch(30);
	normalEstimator.compute(*normalsFilter);

	pcl::SACSegmentationFromNormals<pcl::PointXYZ, pcl::Normal> seg;
	seg.setOptimizeCoefficients(true);
	seg.setModelType(pcl::SACMODEL_CYLINDER);
	seg.setMethodType(pcl::SAC_RANSAC);
	//seg.setNormalDistanceWeight(0.1);
	seg.setNormalDistanceWeight(0.2);		// for coarse data
	seg.setMaxIterations(1000);
	seg.setDistanceThreshold(0.3);
	seg.setRadiusLimits(0, 6);				// radius is within 8 centimeters
	seg.setInputCloud(cloud_in);
	seg.setInputNormals(normalsFilter);

	// Perform segment
	seg.segment(*inliers_cylinder, *coeffients_cylinder);
	std::cerr << "Cylinder coefficient: " << *coeffients_cylinder << std::endl;

	// Ouput extracted cylinder
	pcl::ExtractIndices<pcl::PointXYZ> extract;
	extract.setInputCloud(cloud_in);
	extract.setIndices(inliers_cylinder);
	extract.filter(*cloud_out);
	pcl::PCDWriter wr;
	wr.write("Extract_Cylinder.pcd", *cloud_out);

	float sum_D = 0.0;
	float sum_Ave = 0.0;
	float x0 = coeffients_cylinder->values[0];
	float y0 = coeffients_cylinder->values[1];
	float z0 = coeffients_cylinder->values[2];
	float l = coeffients_cylinder->values[3];
	float m = coeffients_cylinder->values[4];
	float n = coeffients_cylinder->values[5];
	float r0 = coeffients_cylinder->values[6];
	for (int i = 0; i < cloud_out->points.size(); i++) {
		float x = cloud_out->points[i].x;
		float y = cloud_out->points[i].y;
		float z = cloud_out->points[i].z;
		// D=part1+part2
		float part1 = pow(x - x0, 2) + pow(y - y0, 2) + pow(z - z0, 2) - pow(r0, 2);
		float part2 = -pow(l*(x - x0) + m * (y - y0) + n * (z - z0), 2) / (l*l + m * m + n * n);
		sum_D += pow(part1 + part2, 2);
		sum_Ave += fabs(part1 + part2);
	}
	std::cerr << "The average difference is " << sum_Ave / cloud_out->points.size() << std::endl;;
	std::cerr << "The Difference of average difference is " << sum_D / cloud_out->points.size() << std::endl;;
	// evaluate the cylinder quation

}
void CloudViewer::yuannihe()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PLYReader reader;
	reader.read<pcl::PointXYZ>(filename.toStdString(), *cloud_in);
	fitCylinder(cloud_in, cloud_out);
	pcl::io::savePCDFile("C:\\Users\\duke\\Desktop\\cloud_out.pcd", *cloud_out);
}

void CloudViewer::showTreesInfo()
{
	//QsTreeShow* treeShow = new QsTreeShow(this->myTrees);
	//treeShow->exec();
}