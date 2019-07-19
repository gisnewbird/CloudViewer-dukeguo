

#pragma once
/************************************************************************/
/*                点云文件解析类
*/
/************************************************************************/
#include<QString>
#include<QFileInfo>
#include <QFile>

class QsPCloudIO
{
public:
	//构造函数  
	//输入参数  点云文件全路径名
	QsPCloudIO(QString filename);
	~QsPCloudIO();
public:
	QString fileName;//文件全路径名
	QString filePath;//文件路径(不包含文件名)
	QString fName;//文件名
	QString extendFileName;//文件扩展名
	QString Separator;//如果是Txt文件 ，其坐标分割符

public:
	int AnalysisFile();//解析文件


};

