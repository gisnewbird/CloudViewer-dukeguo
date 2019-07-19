#include "QsCSFLvBo.h"


QsCSFLvBo::QsCSFLvBo()
{
	setupUi(this);
	this->helpGBox->hide();
	connect(helpBtn, SIGNAL(toggled(bool)), helpGBox, SLOT(setVisible(bool)));
	connect(helpBtn, SIGNAL(clicked()), this, SLOT(setHelptext()));
	connect(openBtn, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(savBtn, SIGNAL(clicked()), this, SLOT(saveFile()));
	connect(savBtn_2, SIGNAL(clicked()), this, SLOT(saveFile2()));
	connect(okBtn, SIGNAL(clicked()), this, SLOT(cfsLB()));
	connect(canBtn, SIGNAL(clicked()), this, SLOT(close()));
}


QsCSFLvBo::~QsCSFLvBo()
{

}

void QsCSFLvBo::setHelptext()
{
	if (this->helpGBox->isVisible())
	{
		this->helpBtn->setText("<<");
	}
	else
	{
		this->helpBtn->setText(">>");
	}
}

void QsCSFLvBo::openFile()
{
	QString pcloudFile = QFileDialog::getOpenFileName(this, QStringLiteral("打开点云数据"),
		".", QStringLiteral("点云数据(*.las *.txt *.xyz)"));
	if (!pcloudFile.isEmpty())
	{
		this->openlEdit->setText(pcloudFile);
	}
}



void QsCSFLvBo::saveFile()
{
	QString groFile = QFileDialog::getSaveFileName(this, QStringLiteral("保存地面点云"),
		".", QStringLiteral("las文件(*.las);;文本文件(*.txt)"));
	if (!groFile.isEmpty())
	{
		this->savlEdit->setText(groFile);
	}
}

void QsCSFLvBo::saveFile2()
{
	QString fgroFile = QFileDialog::getSaveFileName(this, QStringLiteral("保存非地面点云"),
		".", QStringLiteral("las文件(*.las);;文本文件(*.txt)"));
	if (!fgroFile.isEmpty())
	{
		this->savlEdit_2->setText(fgroFile);
	}
}

void QsCSFLvBo::cfsLB()
{
	QFileInfo *file = new QFileInfo(this->openlEdit->text());
	if (file->suffix() == "txt")//获取文件扩展名
	{

		txtLB();
	}
	if (file->suffix() == "las" || file->suffix() == "LAS")
	{

		lasLB();
	}
}

void QsCSFLvBo::txtLB()
{

	wl::PointCloud myPointCloud;
	CSF *csf = new CSF(myPointCloud);
	if (!csf->readPointsFromFile(this->openlEdit->text().toLocal8Bit().data()))//CSF原始默认从txt文本读取
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("读取点云文件出错！"));
		return;
	}
	//设置CSF滤波参数 可以使用默认参数
	csf->params.k_nearest_points = 1;
	csf->params.time_step = 0.7;//这两个参数使用默认即可


	csf->params.class_threshold = this->flyz->text().toDouble();//分类阈值
	csf->params.cloth_resolution = this->gridWidth->text().toDouble();//格网大小
	csf->params.rigidness = this->buLyd->text().toDouble();
	csf->params.iterations = this->ddcs->text().toInt();//迭代次数
	if (this->checkBox->isChecked())
		csf->params.bSloopSmooth = true;
	else
		csf->params.bSloopSmooth = false;//是否滤波后平滑处理
										 //
	std::vector<int> groundIndexes; //保存地面点的序号
	std::vector<int> offGroundIndexes;//保存非地面点的序号

	if (!csf->do_filtering(groundIndexes, offGroundIndexes, false, this))
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("CSF滤波失败！"));
		return;
	}
	csf->saveGroundPoints(groundIndexes, this->savlEdit->text().toLocal8Bit().data());
	csf->saveOffGroundPoints(offGroundIndexes, this->savlEdit_2->text().toLocal8Bit().data());

	myPointCloud.clear();
	delete csf;
	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("CSF滤波成功！"));
	this->close();
}

void QsCSFLvBo::lasLB()
{

	std::ifstream ifs;
	ifs.open(this->openlEdit->text().toLocal8Bit().data(), std::ios::in | std::ios::binary);
	if (!ifs)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("打开文件出错！"));
		return;
	}

	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);
	liblas::Header const& header = reader.GetHeader();

	wl::PointCloud myPointCloud;

	while (reader.ReadNextPoint())
	{
		wl::Point p;

		liblas::Point const& laspoint = reader.GetPoint();
		p.x = laspoint.GetX();
		p.y = -laspoint.GetZ();
		p.z = laspoint.GetY();

		myPointCloud.push_back(p);
	}
	ifs.close();

	CSF *csf = new CSF(myPointCloud);
	//设置CSF滤波参数 可以使用默认参数
	csf->params.k_nearest_points = 1;
	csf->params.time_step = 0.7;//这两个参数使用默认即可


	csf->params.class_threshold = this->flyz->text().toDouble();//分类阈值
	csf->params.cloth_resolution = this->gridWidth->text().toDouble();//格网大小
	csf->params.rigidness = this->buLyd->text().toDouble();
	csf->params.iterations = this->ddcs->text().toInt();//迭代次数
	if (this->checkBox->isChecked())
		csf->params.bSloopSmooth = true;
	else
		csf->params.bSloopSmooth = false;//是否滤波后平滑处理
										 //
	std::vector<int> groundIndexes; //保存地面点的序号
	std::vector<int> offGroundIndexes;//保存非地面点的序号

	if (!csf->do_filtering(groundIndexes, offGroundIndexes, false, this))
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("CSF滤波失败！"));
		return;
	}

	//输出地面点
	QByteArray ba = this->savlEdit->text().toLocal8Bit();
	const char* psz = ba.data();
	std::ofstream ofs;
	ofs.open(psz, std::ios::out | std::ios::binary);
	//输出非地面点
	QByteArray ba2 = this->savlEdit_2->text().toLocal8Bit();
	const char* psz2 = ba2.data();
	std::ofstream ofs2;
	ofs2.open(psz2, std::ios::out | std::ios::binary);

	if (!ofs || !ofs2)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("保存文件出错！"));
		return;
	}


	liblas::Writer writer(ofs, header); liblas::Writer writer2(ofs2, header);

	for (size_t i = 0; i < groundIndexes.size(); i++)
	{
		liblas::Point * laspoint = new liblas::Point(&header);
		laspoint->SetX(myPointCloud[groundIndexes[i]].x);
		laspoint->SetY(myPointCloud[groundIndexes[i]].z);
		laspoint->SetZ(-myPointCloud[groundIndexes[i]].y);
		writer.WritePoint(*laspoint);
	}

	for (size_t i = 0; i < offGroundIndexes.size(); i++)
	{
		liblas::Point * laspoint = new liblas::Point(&header);
		laspoint->SetX(myPointCloud[offGroundIndexes[i]].x);
		laspoint->SetY(myPointCloud[offGroundIndexes[i]].z);
		laspoint->SetZ(-myPointCloud[offGroundIndexes[i]].y);
		writer2.WritePoint(*laspoint);
	}
	ofs.close();
	ofs2.close();

	groundIndexes.clear();
	offGroundIndexes.clear();
	myPointCloud.clear();
	delete csf;

	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("CSF滤波成功！"));
	this->close();
}
