#include "QsPCloudIO.h"


QsPCloudIO::QsPCloudIO(QString filename)
{
	this->fileName = filename;
	this->Separator = " ";
}


QsPCloudIO::~QsPCloudIO()
{

}

int QsPCloudIO::AnalysisFile()
{
	QFileInfo finfo = QFileInfo(this->fileName);//��ȡ�ļ���Ϣ
	this->fName = finfo.fileName();//��ȡ�ļ���
	this->filePath = finfo.absolutePath();//��ȡ�ļ�·��
	this->extendFileName = finfo.suffix();//��ȡ�ļ���չ��
	if (extendFileName == "txt" || extendFileName == "xyz" || extendFileName == "qsc")
	{
		QFile *file = new QFile(this->fileName);

		if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
			return 0;
		QByteArray line0 = file->readLine();
		QString str0(QString::fromLocal8Bit(line0));
		file->close();

		if (str0.contains(","))
		{
			Separator = ",";
		}
		else if (str0.contains(" "))
		{
			Separator = " ";
		}
		else if (str0.contains("	"))
		{
			Separator = "	";
		}
		else
		{
			return 0;
		}
	}

	return 1;

}



