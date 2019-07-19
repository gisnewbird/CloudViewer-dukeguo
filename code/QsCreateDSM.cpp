#include "QsCreateDSM.h"


class DSMThread :public QThread
{
public:
	DSMThread(QString file1, QString file2, double grid, double size)
	{
		this->inFilename = file1;
		this->outFilename = file2;
		this->grid = grid;
		this->size = size;
		
	}
	~DSMThread()
	{

	}
private:
	QString inFilename;
	QString outFilename;
	QString fgroFilename;
	double grid;
	double size;
protected:
	void run()
	{
		double pixResoultion = this->grid;

		std::ifstream ifs;
		ifs.open(this->inFilename.toLocal8Bit().data(), std::ios::in | std::ios::binary);
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

		for (int i = 0; i < pn; i++)
		{
			padfx[i] = Xs.at(i);
			padfy[i] = Ys.at(i);
			padfz[i] = Zs.at(i);
		}

		//计算图像大小
		int nXsize = (maxX - minX) / pixResoultion;
		int nYsize = (maxY - minY) / pixResoultion;

		GDALAllRegister();
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//设置保证gdal支持中文
		float *pData = new float[nXsize*nYsize];
		//构造插值算法参数并设置插值参数值

		GDALGridNearestNeighborOptions *pOptions = new GDALGridNearestNeighborOptions();
		pOptions->dfRadius1 = this->size;
		pOptions->dfRadius2 = this->size;
		pOptions->dfNoDataValue = 0;

		GDALGridCreate(GGA_NearestNeighbor, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
		delete pOptions;

		for (int i = 0; i < nXsize; i++)
		{
			for (int j = 0; j < nYsize; j++)
			{
				if (pData[j*nXsize + i] == 0)
					pData[j*nXsize + i] = minZ;
			}
		}

		QByteArray ba = this->outFilename.toLocal8Bit();
		const char* psz = ba.data();
		//创建数据集
		GDALDriver *pDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
		GDALDataset *pDataset = pDriver->Create(psz, nXsize, nYsize, 1, GDT_Float32, NULL);
		double adfGeoTransform[6] = { minX, pixResoultion, 0, minY, 0, pixResoultion };
		pDataset->SetGeoTransform(adfGeoTransform);
		//写入影像
		pDataset->RasterIO(GF_Write, 0, 0, nXsize, nYsize, pData, nXsize, nYsize, GDT_Float32, 1, 0, 0, 0, 0);
		delete[]pData;
		GDALClose(pDataset);

	}

};

QsCreateDSM::QsCreateDSM()
{
	setupUi(this);

	progDlg = new QProgressDialog(this);
	timer = new QTimer;
	currentValue = 0;
	connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressDialog()));

	connect(openBtn, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(savBtn, SIGNAL(clicked()), this, SLOT(saveFile()));
	connect(okBtn, SIGNAL(clicked()), this, SLOT(createDsm()));
	connect(canBtn, SIGNAL(clicked()), this, SLOT(close()));
}


QsCreateDSM::~QsCreateDSM()
{
	delete progDlg;
	delete timer;
}

void QsCreateDSM::updateProgressDialog()
{
	currentValue++;
	if (currentValue == 100)
		currentValue = 0;
	progDlg->setValue(currentValue);
	QCoreApplication::processEvents();//避免界面冻结

}
void QsCreateDSM::stopProgress()
{
	progDlg->setValue(100);
	QCoreApplication::processEvents();//避免界面冻结
	timer->stop();
	progDlg->hide();

	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("DSM生成成功！"));
	this->close();

}

void QsCreateDSM::openFile()
{
	QString pcloudFile = QFileDialog::getOpenFileName(this, QStringLiteral("打开点云数据"),
		".", QStringLiteral("点云数据(*.las)"));
	if (!pcloudFile.isEmpty())
	{
		this->openlEdit->setText(pcloudFile);
	}
}



void QsCreateDSM::saveFile()
{
	QString demFile = QFileDialog::getSaveFileName(this, QStringLiteral("保存DSM"),
		".", QStringLiteral("(*.tif)"));
	if (!demFile.isEmpty())
	{
		this->savlEdit->setText(demFile);
	}
}

void QsCreateDSM::createDsm()
{
	QFileInfo *file = new QFileInfo(this->openlEdit->text());
	if (file->suffix() == "txt")//获取文件扩展名
	{
		txtDSM();	
	}
	if (file->suffix() == "las" || file->suffix() == "LAS")
	{
		
		//lasDSM();
		progDlg->setCancelButtonText(QStringLiteral("取消"));
		progDlg->setRange(0, 100);
		progDlg->show();
		progDlg->setValue(currentValue);
		timer->start(100);

		DSMThread *dsm = new DSMThread(this->openlEdit->text(), this->savlEdit->text(),
			this->lineEdit->text().toDouble(), this->lineEdit_2->text().toDouble());
		dsm->start();
		connect(dsm, SIGNAL(finished()), this, SLOT(stopProgress()));
	
	}
}


void QsCreateDSM::lasDSM()
{
	// char* pszDst = this->savlEdit->text().toLatin1().data();


	//const char* pszDst = "C:\\Users\\GIS\\Desktop\\dsm.tif";

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

	for (int i = 0; i < pn; i++)
	{
		padfx[i] = Xs.at(i);
		padfy[i] = Ys.at(i);
		padfz[i] = Zs.at(i);
	}

	//计算图像大小
	int nXsize = (maxX - minX) / pixResoultion;
	int nYsize = (maxY - minY) / pixResoultion;

	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//设置保证gdal支持中文
	float *pData = new float[nXsize*nYsize];
	//构造插值算法参数并设置插值参数值
	
		GDALGridNearestNeighborOptions *pOptions = new GDALGridNearestNeighborOptions();
		pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
		pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();

		GDALGridCreate(GGA_NearestNeighbor, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
		delete pOptions;
	
		QByteArray ba = this->savlEdit->text().toLocal8Bit();
		const char* psz = ba.data();
	//创建数据集
	GDALDriver *pDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
	GDALDataset *pDataset = pDriver->Create(psz, nXsize, nYsize, 1, GDT_Float32, NULL);
	double adfGeoTransform[6] = { minX, pixResoultion, 0, minY, 0, pixResoultion };
	pDataset->SetGeoTransform(adfGeoTransform);
	//写入影像
	pDataset->RasterIO(GF_Write, 0, 0, nXsize, nYsize, pData, nXsize, nYsize, GDT_Float32, 1, 0, 0, 0, 0);
	delete[]pData;
	GDALClose(pDataset);

	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("DSM生成成功！"));
	this->close();
}

void QsCreateDSM::txtDSM()
{
	//const char* pszPoints = this->openlEdit->text().toLocal8Bit().data();
	// char* pszDst = this->savlEdit->text().toLatin1().data();


	//const char* pszDst = "C:\\Users\\GIS\\Desktop\\dsm.tif";

	double pixResoultion = this->lineEdit->text().toDouble();

	QFile *file = new QFile(this->openlEdit->text());

	if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("DSM生成失败！"));
		return;
	}

	double arr[3];
	double minX = DBL_MAX;
	double maxX = DBL_MIN;
	double minY = DBL_MAX;
	double maxY = DBL_MIN;
	double minZ = DBL_MAX;
	double maxZ = DBL_MIN;

	QList<double> Xs; QList<double> Ys; QList<double> Zs;
	int pn = 0;
	QsPCloudIO *pclio = new QsPCloudIO(this->openlEdit->text());
	if (!pclio->AnalysisFile())
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("DSM生成失败！"));
		return;
	}

	while (!file->atEnd())
	{
		QByteArray line = file->readLine();
		QString str(QString::fromLocal8Bit(line));
		QStringList strlist = str.split(pclio->Separator);
		if (strlist.length() < 3)//判断是否分割为3部分，如果否直接返回
		{
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("DSM生成失败！"));
			return;
		}
		bool ok;
		arr[0] = strlist.at(0).toDouble(&ok);//ok判断是否转换成功
		if (!ok)  {
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("DSM生成失败！"));
			return;
		}
		arr[1] = strlist.at(1).toDouble(&ok);
		if (!ok)  {
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("DSM生成失败！"));
			return;
		}
		arr[2] = strlist.at(2).toDouble(&ok);
		if (!ok)  {
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("DSM生成失败！"));
			return;
		}

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
	file->close();

	double *padfx = new double[pn];
	double *padfy = new double[pn];
	double *padfz = new double[pn];

	for (int i = 0; i < pn; i++)
	{
		padfx[i] = Xs.at(i);
		padfy[i] = Ys.at(i);
		padfz[i] = Zs.at(i);
	}

	//计算图像大小
	int nXsize = (maxX - minX) / pixResoultion;
	int nYsize = (maxY - minY) / pixResoultion;

	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//设置保证gdal支持中文
	float *pData = new float[nXsize*nYsize];
	//构造插值算法参数并设置插值参数值

	GDALGridNearestNeighborOptions *pOptions = new GDALGridNearestNeighborOptions();
	pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
	pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();

	GDALGridCreate(GGA_NearestNeighbor, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
	delete pOptions;

	QByteArray ba = this->savlEdit->text().toLocal8Bit();
	const char* psz = ba.data();
	//创建数据集
	GDALDriver *pDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
	GDALDataset *pDataset = pDriver->Create(psz, nXsize, nYsize, 1, GDT_Float32, NULL);
	double adfGeoTransform[6] = { minX, pixResoultion, 0, minY, 0, pixResoultion };
	pDataset->SetGeoTransform(adfGeoTransform);
	//写入影像
	pDataset->RasterIO(GF_Write, 0, 0, nXsize, nYsize, pData, nXsize, nYsize, GDT_Float32, 1, 0, 0, 0, 0);
	delete[]pData;
	GDALClose(pDataset);


	
	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("DSM生成成功！"));
	this->close();
}