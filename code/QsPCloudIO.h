

#pragma once
/************************************************************************/
/*                �����ļ�������
*/
/************************************************************************/
#include<QString>
#include<QFileInfo>
#include <QFile>

class QsPCloudIO
{
public:
	//���캯��  
	//�������  �����ļ�ȫ·����
	QsPCloudIO(QString filename);
	~QsPCloudIO();
public:
	QString fileName;//�ļ�ȫ·����
	QString filePath;//�ļ�·��(�������ļ���)
	QString fName;//�ļ���
	QString extendFileName;//�ļ���չ��
	QString Separator;//�����Txt�ļ� ��������ָ��

public:
	int AnalysisFile();//�����ļ�


};

