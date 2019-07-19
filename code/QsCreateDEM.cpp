#include "QsCreateDEM.h"

class DEMThread :public QThread
{
public:
	DEMThread(QString file1, QString file2, int select,double grid, double size)
	{
		this->inFilename = file1;
		this->outFilename = file2;
		this->select = select;
		this->grid = grid;
		this->size = size;

	}
	~DEMThread()
	{

	}
private:
	QString inFilename;
	QString outFilename;
	QString fgroFilename;
	int select;
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

		//����ͼ���С
		int nXsize = (maxX - minX) / pixResoultion;
		int nYsize = (maxY - minY) / pixResoultion;

		GDALAllRegister();
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//���ñ�֤gdal֧������
		float *pData = new float[nXsize*nYsize];
		//�����ֵ�㷨���������ò�ֵ����ֵ
		if (this->select==1)//������Ȩ�ز�ֵ
		{
			GDALGridInverseDistanceToAPowerOptions *pOptions = new GDALGridInverseDistanceToAPowerOptions();
			pOptions->dfPower = 2;
			pOptions->dfRadius1 = this->size;
			pOptions->dfRadius2 = this->size;
			pOptions->dfNoDataValue = 0;

			GDALGridCreate(GGA_InverseDistanceToAPower, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
			delete pOptions;
		}
		if (this->select == 2)//�ƶ�ƽ����ֵ
		{
			GDALGridMovingAverageOptions *pOptions = new GDALGridMovingAverageOptions();
			pOptions->dfRadius1 = this->size;
			pOptions->dfRadius2 = this->size;
			pOptions->dfNoDataValue = 0;

			GDALGridCreate(GGA_MovingAverage, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
			delete pOptions;
		}
		if (this->select == 3)//���ڽ���ֵ
		{
			GDALGridNearestNeighborOptions *pOptions = new GDALGridNearestNeighborOptions();
			pOptions->dfRadius1 = this->size;
			pOptions->dfRadius2 = this->size;
			pOptions->dfNoDataValue = 0;

			GDALGridCreate(GGA_NearestNeighbor, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
			delete pOptions;
		}
		
		for (int i = 0; i < nXsize;i++)
		{
			for (int j = 0; j < nYsize;j++)
			{
				if (pData[j*nXsize + i] == 0)
					pData[j*nXsize + i] = minZ;
			}
		}

		QByteArray ba = this->outFilename.toLocal8Bit();
		const char* psz = ba.data();

		//�������ݼ�
		GDALDriver *pDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
		GDALDataset *pDataset = pDriver->Create(psz, nXsize, nYsize, 1, GDT_Float32, NULL);
		double adfGeoTransform[6] = { minX, pixResoultion, 0, minY, 0, pixResoultion };
		pDataset->SetGeoTransform(adfGeoTransform);
		//д��Ӱ��
		pDataset->RasterIO(GF_Write, 0, 0, nXsize, nYsize, pData, nXsize, nYsize, GDT_Float32, 1, 0, 0, 0, 0);
		delete[]pData;
		GDALClose(pDataset);

	}

};


QsCreateDEM::QsCreateDEM()
{
	setupUi(this);

	progDlg = new QProgressDialog(this);
	timer = new QTimer;
	currentValue = 0;
	connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressDialog()));

	connect(openBtn, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(savBtn, SIGNAL(clicked()), this, SLOT(saveFile()));
	connect(okBtn, SIGNAL(clicked()), this, SLOT(createDem()));
	connect(canBtn, SIGNAL(clicked()), this, SLOT(close()));
}


QsCreateDEM::~QsCreateDEM()
{
	delete progDlg;
	delete timer;
}

void QsCreateDEM::updateProgressDialog()
{
	currentValue++;
	if (currentValue == 100)
		currentValue = 0;
	progDlg->setValue(currentValue);
	QCoreApplication::processEvents();//������涳��

}

void QsCreateDEM::stopProgress()
{
	progDlg->setValue(100);
	QCoreApplication::processEvents();//������涳��
	timer->stop();
	progDlg->hide();

	QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("DEM���ɳɹ���"));
	this->close();

}


void QsCreateDEM::openFile()
{
	QString pcloudFile = QFileDialog::getOpenFileName(this, QStringLiteral("�򿪵����������"),
		".", QStringLiteral("��������(*.las)"));
	if (!pcloudFile.isEmpty())
	{
		this->openlEdit->setText(pcloudFile);
	}
}



void QsCreateDEM::saveFile()
{
	QString demFile = QFileDialog::getSaveFileName(this, QStringLiteral("����DEM"),
		".", QStringLiteral("(*.tif)"));
	if (!demFile.isEmpty())
	{
		this->savlEdit->setText(demFile);
	}
}

void QsCreateDEM::createDem()
{
	QFileInfo *file = new QFileInfo(this->openlEdit->text());
	if (file->suffix() == "txt")//��ȡ�ļ���չ��
	{
		
		txtDEM();
		
	}
	if (file->suffix() == "las" || file->suffix() == "LAS")
	{
		
		//lasDEM();
		progDlg->setCancelButtonText(QStringLiteral("ȡ��"));
		progDlg->setRange(0, 100);
		progDlg->show();
		progDlg->setValue(currentValue);
		timer->start(100);
		int caseSelect = 0;
		if (this->rBtn1->isChecked()) caseSelect = 1;
		if (this->rBtn2->isChecked()) caseSelect = 2;
		if (this->rBtn3->isChecked()) caseSelect = 3;

		DEMThread *dem = new DEMThread(this->openlEdit->text(), this->savlEdit->text(),caseSelect,
			this->lineEdit->text().toDouble(), this->lineEdit_2->text().toDouble());
		dem->start();
		connect(dem, SIGNAL(finished()), this, SLOT(stopProgress()));
	
	}
}


void QsCreateDEM::lasDEM()
{
	// char* pszDst = this->savlEdit->text().toLatin1().data();


	//const char* pszDst = "C:\\Users\\GIS\\Desktop\\dem.tif";

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

	//����ͼ���С
	int nXsize = (maxX - minX) / pixResoultion;
	int nYsize = (maxY - minY) / pixResoultion;

	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//���ñ�֤gdal֧������
	float *pData = new float[nXsize*nYsize];
	//�����ֵ�㷨���������ò�ֵ����ֵ
	if (this->rBtn1->isChecked())//������Ȩ�ز�ֵ
	{
		GDALGridInverseDistanceToAPowerOptions *pOptions = new GDALGridInverseDistanceToAPowerOptions();
		pOptions->dfPower = 2;
		pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
		pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();


		GDALGridCreate(GGA_InverseDistanceToAPower, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
		delete pOptions;
	}
	if (this->rBtn2->isChecked())//�ƶ�ƽ����ֵ
	{
		GDALGridMovingAverageOptions *pOptions = new GDALGridMovingAverageOptions();
		pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
		pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();

		GDALGridCreate(GGA_MovingAverage, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
		delete pOptions;
	}
	if (this->rBtn3->isChecked())//���ڽ���ֵ
	{
		GDALGridNearestNeighborOptions *pOptions = new GDALGridNearestNeighborOptions();
		pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
		pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();

		GDALGridCreate(GGA_NearestNeighbor, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
		delete pOptions;
	}

	QByteArray ba = this->savlEdit->text().toLocal8Bit();
	const char* psz = ba.data();

	//�������ݼ�
	GDALDriver *pDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
	GDALDataset *pDataset = pDriver->Create(psz, nXsize, nYsize, 1, GDT_Float32, NULL);
	double adfGeoTransform[6] = { minX, pixResoultion, 0, minY, 0, pixResoultion };
	pDataset->SetGeoTransform(adfGeoTransform);
	//д��Ӱ��
	pDataset->RasterIO(GF_Write, 0, 0, nXsize, nYsize, pData, nXsize, nYsize, GDT_Float32, 1, 0, 0, 0, 0);
	delete[]pData;
	GDALClose(pDataset);

	QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("DEM���ɳɹ���"));
	this->close();
}

void QsCreateDEM::txtDEM()
{
	//const char* pszPoints = this->openlEdit->text().toLocal8Bit().data();
	// char* pszDst = this->savlEdit->text().toLocal8Bit().data();
	

	//const char* pszDst = "C:\\Users\\GIS\\Desktop\\dem.tif";
	

	double pixResoultion = this->lineEdit->text().toDouble();

	QFile *file = new QFile(this->openlEdit->text());

	if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("DEM����ʧ�ܣ�"));
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
		QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("DEM����ʧ�ܣ�"));
		return;
	}

	while (!file->atEnd())
	{
		QByteArray line = file->readLine();
		QString str(QString::fromLocal8Bit(line));
		QStringList strlist = str.split(pclio->Separator);
		if (strlist.length() < 3)//�ж��Ƿ�ָ�Ϊ3���֣������ֱ�ӷ���
		{
			QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("DEM����ʧ�ܣ�"));
			return;
		}
		bool ok;
		arr[0] = strlist.at(0).toDouble(&ok);//ok�ж��Ƿ�ת���ɹ�
		if (!ok)  {
			QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("DEM����ʧ�ܣ�"));
			return;
		}
		arr[1] = strlist.at(1).toDouble(&ok);
		if (!ok)  {
			QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("DEM����ʧ�ܣ�"));
			return;
		}
		arr[2] = strlist.at(2).toDouble(&ok);
		if (!ok)  {
			QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("DEM����ʧ�ܣ�"));
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

	//����ͼ���С
	int nXsize = (maxX - minX) / pixResoultion ;
	int nYsize = (maxY - minY) / pixResoultion ;

	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//���ñ�֤gdal֧������
	float *pData = new float[nXsize*nYsize];
	//�����ֵ�㷨���������ò�ֵ����ֵ
	if (this->rBtn1->isChecked())//������Ȩ�ز�ֵ
	{
		GDALGridInverseDistanceToAPowerOptions *pOptions = new GDALGridInverseDistanceToAPowerOptions();
		pOptions->dfPower = 2;
		pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
		pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();


		GDALGridCreate(GGA_InverseDistanceToAPower, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
		delete pOptions;
	}
	if (this->rBtn2->isChecked())//�ƶ�ƽ����ֵ
	{
		GDALGridMovingAverageOptions *pOptions = new GDALGridMovingAverageOptions();
		pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
		pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();

		GDALGridCreate(GGA_MovingAverage, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
		delete pOptions;
	}
	if (this->rBtn3->isChecked())//���ڽ���ֵ
	{
		GDALGridNearestNeighborOptions *pOptions = new GDALGridNearestNeighborOptions();
		pOptions->dfRadius1 = this->lineEdit_2->text().toDouble();
		pOptions->dfRadius2 = this->lineEdit_2->text().toDouble();

		GDALGridCreate(GGA_NearestNeighbor, pOptions, pn, padfx, padfy, padfz, minX, maxX, minY, maxY, nXsize, nYsize, GDT_Float32, pData, NULL, NULL);
		delete pOptions;
	}

	//char *sss = this->savlEdit->text().toLocal8Bit().data();
	QByteArray ba = this->savlEdit->text().toLocal8Bit();
	const char* psz = ba.data();
	//�������ݼ�
	GDALDriver *pDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
	GDALDataset *pDataset = pDriver->Create(psz, nXsize, nYsize, 1, GDT_Float32, NULL);
	double adfGeoTransform[6] = { minX, pixResoultion, 0, minY, 0, pixResoultion };
	pDataset->SetGeoTransform(adfGeoTransform);
	//д��Ӱ��
	pDataset->RasterIO(GF_Write, 0, 0, nXsize, nYsize, pData, nXsize, nYsize, GDT_Float32, 1, 0, 0, 0, 0);
	delete[]pData;
	GDALClose(pDataset);
	
	QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("DEM���ɳɹ���"));
	this->close();
}