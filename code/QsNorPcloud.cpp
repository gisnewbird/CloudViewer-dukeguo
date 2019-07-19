
#include "QsNorPcloud.h"
#include <gdal_alg.h>
#include <gdal_priv.h>

struct Point
{
	double x, y, z;

};

class NorPcloud :public QThread
{
public:
	NorPcloud(QString file1, QString file2, QString file3, double grid, double size)
	{

		this->groFilename = file1;
		this->fgroFilename = file2;
		this->gyhFilename = file3;
		this->grid = grid;
		this->size = size;

	}
	~NorPcloud()
	{

	}
private:
	QString groFilename;
	QString fgroFilename;
	QString gyhFilename;

	double grid;
	double size;

protected:
	void run()
	{
		double pixResoultion = this->grid;

		std::ifstream ifs;
		ifs.open(this->groFilename.toLocal8Bit().data(), std::ios::in | std::ios::binary);
		if (!ifs)
		{
			return;
		}

		liblas::ReaderFactory f;
		liblas::Reader reader = f.CreateWithStream(ifs);



		double arr[3];
		double minX = DBL_MAX;
		double maxX = DBL_MIN;
		double minY = DBL_MAX;
		double maxY = DBL_MIN;
		double minZ = DBL_MAX;
		double maxZ = DBL_MIN;

		QList<double> Xs; QList<double> Ys; QList<double> Zs;
		int pn = 0;

		while (reader.ReadNextPoint())
		{

			liblas::Point const& laspoint = reader.GetPoint();
			arr[0] = laspoint.GetX();
			arr[1] = laspoint.GetY();
			arr[2] = laspoint.GetZ();

			Xs.append(arr[0]);
			Ys.append(arr[1]);
			Zs.append(arr[2]);

			if (arr[0] < minX)
				minX = arr[0];
			if (arr[0] > maxX)
				maxX = arr[0];
			if (arr[1] < minY)
				minY = arr[1];
			if (arr[1] > maxY)
				maxY = arr[1];
			if (arr[2] < minZ)
				minZ = arr[2];
			if (arr[2] > maxZ)
				maxZ = arr[2];
			pn++;
		}
		ifs.close();

		double *padfx = new double[pn];
		double *padfy = new double[pn];
		double *padfz = new double[pn];
#pragma omp parallel for
		for (int i = 0; i < pn; i++)
		{
			padfx[i] = Xs.at(i);
			padfy[i] = Ys.at(i);
			padfz[i] = Zs.at(i);
		}



		//计算行列
		int nXsize = (maxX - minX) / pixResoultion;
		int nYsize = (maxY - minY) / pixResoultion;

		GDALAllRegister();
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//设置保证gdal支持中文
		float *pData = new float[nXsize*nYsize];
		//构造插值算法参数并设置插值参数值

		/*GDALGridInverseDistanceToAPowerOptions *pOptions = new GDALGridInverseDistanceToAPowerOptions();
		pOptions->dfPower = 2;
		pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
		pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();
		GDALGridCreate(GGA_InverseDistanceToAPower, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
		delete pOptions; pOptions = NULL;*/
		//最近邻插值
		
		GDALGridNearestNeighborOptions *pOptions = new GDALGridNearestNeighborOptions();
		
		pOptions->dfRadius1 = this->size;
		pOptions->dfRadius2 = this->size;

		GDALGridCreate(GGA_NearestNeighbor, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
		delete pOptions;


		//读取非地面点云
		QVector<Point> data;
		std::ifstream ifs1;
		ifs1.open(this->fgroFilename.toLocal8Bit().data(), std::ios::in | std::ios::binary);
		if (!ifs1)
		{
			return;
		}

		liblas::ReaderFactory f1;
		liblas::Reader reader1 = f1.CreateWithStream(ifs1);
		liblas::Header const& header = reader1.GetHeader();

		while (reader1.ReadNextPoint())
		{

			liblas::Point const& laspoint = reader1.GetPoint();
			Point p;
			p.x = laspoint.GetX();
			p.y = laspoint.GetY();
			p.z = laspoint.GetZ();
			data.push_back(p);
		}
		ifs1.close();


		//输出归一化点云
		QByteArray ba = this->gyhFilename.toLocal8Bit();
		const char* psz = ba.data();
		std::ofstream ofs;
		ofs.open(psz, std::ios::out | std::ios::binary);

		liblas::Writer writer(ofs, header);
#pragma omp parallel for
		for (int i = 0; i < data.size(); i++)//遍历每一个点
		{
			int col = (int)((data[i].x - minX) / pixResoultion);
			int row = (int)((data[i].y - minY) / pixResoultion);
			//避免非地面点超出地面插值范围  将超出范围的点所属地面网格归为其最近网格高程
			if (col >= nXsize)
				col = nXsize - 1;
			if (row >= nYsize)
				row = nYsize - 1;
			if (col < 0)
				col = 0;
			if (row < 0)
				row = 0;
			double zz = data[i].z - pData[row*nXsize + col];

			liblas::Point * laspoint = new liblas::Point(&header);
			laspoint->SetX(data[i].x);
			laspoint->SetY(data[i].y);
			laspoint->SetZ(zz);
			writer.WritePoint(*laspoint);
		}
		ofs.close();

		delete[] pData; pData = NULL;
		delete[] padfx; padfx = NULL;
		delete[] padfy; padfy = NULL;
		delete[] padfz; padfz = NULL;

	}

};


QsNorPcloud::QsNorPcloud()
{
	setupUi(this);
	progDlg = new QProgressDialog(this);
	timer = new QTimer;
	currentValue = 0;


	connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressDialog()));


	connect(openBtn, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(openBtn_2, SIGNAL(clicked()), this, SLOT(openFile2()));
	connect(savBtn, SIGNAL(clicked()), this, SLOT(saveFile()));
	connect(okBtn, SIGNAL(clicked()), this, SLOT(norPcloud()));
	connect(canBtn, SIGNAL(clicked()), this, SLOT(close()));
}


QsNorPcloud::~QsNorPcloud()
{
	delete timer;
	delete progDlg;
}

void QsNorPcloud::updateProgressDialog()
{
	currentValue++;
	if (currentValue == 100)
		currentValue = 0;
	progDlg->setValue(currentValue);
	QCoreApplication::processEvents();//避免界面冻结

}
void QsNorPcloud::stopProgress()
{
	progDlg->setValue(100);
	QCoreApplication::processEvents();//避免界面冻结
	timer->stop();
	progDlg->hide();

	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("点云归一化完成！"));
	this->close();

}

void QsNorPcloud::openFile()
{
	QString pcloudFile = QFileDialog::getOpenFileName(this, QStringLiteral("打开地面点云数据"),
		".", QStringLiteral("点云数据(*.las)"));
	if (!pcloudFile.isEmpty())
	{
		this->openlEdit->setText(pcloudFile);
	}
}

void QsNorPcloud::openFile2()
{
	QString pcloudFile = QFileDialog::getOpenFileName(this, QStringLiteral("打开非地面点云数据"),
		".", QStringLiteral("点云数据(*.las)"));
	if (!pcloudFile.isEmpty())
	{
		this->openlEdit_2->setText(pcloudFile);
	}
}



void QsNorPcloud::saveFile()
{
	QString lasFile = QFileDialog::getSaveFileName(this, QStringLiteral("保存归一化点云"),
		".", QStringLiteral("(*.las)"));
	if (!lasFile.isEmpty())
	{
		this->savlEdit->setText(lasFile);
	}
}

void QsNorPcloud::norPcloud()
{
	QFileInfo *file = new QFileInfo(this->openlEdit->text());
	if (file->suffix() == "txt")//获取文件扩展名
	{

		txtNorPcloud();

	}
	if (file->suffix() == "las" || file->suffix() == "LAS")
	{

		//lasNorPcloud();
		progDlg->setCancelButtonText(QStringLiteral("取消"));
		progDlg->setRange(0, 100);
		progDlg->show();
		progDlg->setValue(currentValue);
		timer->start(100);

		NorPcloud *lvb = new NorPcloud(this->openlEdit->text(), this->openlEdit_2->text(), this->savlEdit->text(),
			this->lineEdit->text().toDouble(),
			this->lineEdit_2->text().toDouble());
		lvb->start();
		connect(lvb, SIGNAL(finished()), this, SLOT(stopProgress()));

	}
}


void QsNorPcloud::lasNorPcloud()
{
	double pixResoultion = this->lineEdit->text().toDouble();

	std::ifstream ifs;
	ifs.open(this->openlEdit->text().toLocal8Bit().data(), std::ios::in | std::ios::binary);
	if (!ifs)
	{
		return;
	}

	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);



	double arr[3];
	double minX = DBL_MAX;
	double maxX = DBL_MIN;
	double minY = DBL_MAX;
	double maxY = DBL_MIN;
	double minZ = DBL_MAX;
	double maxZ = DBL_MIN;

	QList<double> Xs; QList<double> Ys; QList<double> Zs;
	int pn = 0;

	while (reader.ReadNextPoint())
	{

		liblas::Point const& laspoint = reader.GetPoint();
		arr[0] = laspoint.GetX();
		arr[1] = laspoint.GetY();
		arr[2] = laspoint.GetZ();

		Xs.append(arr[0]);
		Ys.append(arr[1]);
		Zs.append(arr[2]);

		if (arr[0] < minX)
			minX = arr[0];
		if (arr[0] > maxX)
			maxX = arr[0];
		if (arr[1] < minY)
			minY = arr[1];
		if (arr[1] > maxY)
			maxY = arr[1];
		if (arr[2] < minZ)
			minZ = arr[2];
		if (arr[2] > maxZ)
			maxZ = arr[2];
		pn++;
	}
	ifs.close();

	double *padfx = new double[pn];
	double *padfy = new double[pn];
	double *padfz = new double[pn];
#pragma omp parallel for
	for (int i = 0; i < pn; i++)
	{
		padfx[i] = Xs.at(i);
		padfy[i] = Ys.at(i);
		padfz[i] = Zs.at(i);
	}



	//计算行列
	int nXsize = (maxX - minX) / pixResoultion;
	int nYsize = (maxY - minY) / pixResoultion;

	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//设置保证gdal支持中文
	float *pData = new float[nXsize*nYsize];
	//构造插值算法参数并设置插值参数值

	/*GDALGridInverseDistanceToAPowerOptions *pOptions = new GDALGridInverseDistanceToAPowerOptions();
	pOptions->dfPower = 2;
	pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
	pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();
	GDALGridCreate(GGA_InverseDistanceToAPower, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
	delete pOptions; pOptions = NULL;*/
	//最近邻插值
	GDALGridNearestNeighborOptions *pOptions = new GDALGridNearestNeighborOptions();
	pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
	pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();

	GDALGridCreate(GGA_NearestNeighbor, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
	delete pOptions;


	//读取非地面点云
	QVector<Point> data;
	std::ifstream ifs1;
	ifs1.open(this->openlEdit_2->text().toLocal8Bit().data(), std::ios::in | std::ios::binary);
	if (!ifs1)
	{
		return;
	}

	liblas::ReaderFactory f1;
	liblas::Reader reader1 = f1.CreateWithStream(ifs1);
	liblas::Header const& header = reader1.GetHeader();

	while (reader1.ReadNextPoint())
	{

		liblas::Point const& laspoint = reader1.GetPoint();
		Point p;
		p.x = laspoint.GetX();
		p.y = laspoint.GetY();
		p.z = laspoint.GetZ();
		data.push_back(p);
	}
	ifs1.close();


	//输出归一化点云
	QByteArray ba = this->savlEdit->text().toLocal8Bit();
	const char* psz = ba.data();
	std::ofstream ofs;
	ofs.open(psz, std::ios::out | std::ios::binary);
	if (!ofs)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("保存文件出错！"));
		return;
	}
	liblas::Writer writer(ofs, header);

	for (int i = 0; i < data.size(); i++)//遍历每一个点
	{
		int col = (int)((data[i].x - minX) / pixResoultion);
		int row = (int)((data[i].y - minY) / pixResoultion);
		//避免非地面点超出地面插值范围  将超出范围的点所属地面网格归为其最近网格高程
		if (col >= nXsize)
			col = nXsize - 1;
		if (row >= nYsize)
			row = nYsize - 1;
		if (col < 0)
			col = 0;
		if (row < 0)
			row = 0;
		double zz = data[i].z - pData[row*nXsize + col];

		liblas::Point * laspoint = new liblas::Point(&header);
		laspoint->SetX(data[i].x);
		laspoint->SetY(data[i].y);
		laspoint->SetZ(zz);
		writer.WritePoint(*laspoint);
	}
	ofs.close();

	delete[] pData; pData = NULL;
	delete[] padfx; padfx = NULL;
	delete[] padfy; padfy = NULL;
	delete[] padfz; padfz = NULL;

	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("点云归一化完成！"));
	this->close();
}


void QsNorPcloud::txtNorPcloud()
{

}
