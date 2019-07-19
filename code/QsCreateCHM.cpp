#include "QsCreateCHM.h"


QsCreateCHM::QsCreateCHM()
{
	setupUi(this);

	connect(dsmBtn, SIGNAL(clicked()), this, SLOT(openDSM()));
	connect(demBtn, SIGNAL(clicked()), this, SLOT(openDEM()));
	connect(savBtn, SIGNAL(clicked()), this, SLOT(saveCHM()));
	connect(okBtn, SIGNAL(clicked()), this, SLOT(createCHM()));
	connect(calBtn, SIGNAL(clicked()), this, SLOT(close()));
}


QsCreateCHM::~QsCreateCHM()
{
}

void QsCreateCHM::openDSM()
{
	QString dsmFile = QFileDialog::getOpenFileName(this, QStringLiteral("��DSM"),
		".", QStringLiteral("DSM(*.tif)"));
	if (!dsmFile.isEmpty())
	{
		this->dsmLE->setText(dsmFile);
	}
}

void QsCreateCHM::openDEM()
{
	QString demFile = QFileDialog::getOpenFileName(this, QStringLiteral("��DEM"),
		".", QStringLiteral("DEM(*.tif)"));
	if (!demFile.isEmpty())
	{
		this->demLE->setText(demFile);
	}
}



void QsCreateCHM::saveCHM()
{
	QString chmFile = QFileDialog::getSaveFileName(this, QStringLiteral("����CHM"),
		".", QStringLiteral("(*.tif)"));
	if (!chmFile.isEmpty())
	{
		this->chmLE->setText(chmFile);
	}
}


void QsCreateCHM::createCHM()
{
	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//���ñ�֤gdal֧������
	GDALDataset *dsmDataset;   //GDAL���ݼ�  
	GDALDataset *demDataset;   //GDAL���ݼ�  
	QByteArray ba1 = this->dsmLE->text().toLocal8Bit();
	const char *str1 = ba1.data();
	QByteArray ba2 = this->demLE->text().toLocal8Bit();
	const char *str2 = ba2.data();
	dsmDataset = (GDALDataset*)GDALOpen(str1, GA_ReadOnly);
	demDataset = (GDALDataset*)GDALOpen(str2, GA_ReadOnly);//����������ݼ�

	double adfGeoTransform[6];
	double pixResoultion = dsmDataset->GetGeoTransform(adfGeoTransform);
	int srcWidth = dsmDataset->GetRasterXSize();//Ĭ�϶���  �����θ߳�ͼ
	int srcHeight = dsmDataset->GetRasterYSize();//��ȡͼ���Ⱥ͸߶�

	float *dataArray1 = new float[srcWidth * srcHeight];
	float *dataArray2 = new float[srcWidth * srcHeight];
	float *newArray = new float[srcWidth * srcHeight];

	dsmDataset->RasterIO(GF_Read, 0, 0, srcWidth, srcHeight, dataArray1, srcWidth, srcHeight, GDT_Float32, 1, 0, 0, 0, 0);
	demDataset->RasterIO(GF_Read, 0, 0, srcWidth, srcHeight, dataArray2, srcWidth, srcHeight, GDT_Float32, 1, 0, 0, 0, 0);
	for (int i = 0; i < srcHeight; i++)
	{
		for (int j = 0; j < srcWidth; j++)
		{
			newArray[i * srcWidth + j] = dataArray1[i * srcWidth + j] - dataArray2[i * srcWidth + j];
		}
	}

	QByteArray ba = this->chmLE->text().toLocal8Bit();
	const char* psz = ba.data();
	//�������ݼ�
	GDALDriver *pDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
	GDALDataset *pDataset = pDriver->Create(psz, srcWidth, srcHeight, 1, GDT_Float32, NULL);
	
	pDataset->SetGeoTransform(adfGeoTransform);
	//д��Ӱ��
	pDataset->RasterIO(GF_Write, 0, 0, srcWidth, srcHeight, newArray, srcWidth, srcHeight, GDT_Float32, 1, 0, 0, 0, 0);
	
	delete[] dataArray1;
	delete[] dataArray2;
	delete[]newArray;
	GDALClose(dsmDataset);
	GDALClose(demDataset);
	GDALClose(pDataset);

	QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("CHM���ɳɹ���"));
	this->close();
	
}