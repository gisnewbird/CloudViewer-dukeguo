#include "QsConvertFormat.h"


QsConvertFormat::QsConvertFormat()
{
	setupUi(this);
	connect(openBtn, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(savBtn, SIGNAL(clicked()), this, SLOT(saveFile()));
	connect(okBtn, SIGNAL(clicked()), this, SLOT(las2pcd()));
	connect(cancleBtn, SIGNAL(clicked()), this, SLOT(close()));
}


QsConvertFormat::~QsConvertFormat()
{
}


void QsConvertFormat::openFile()
{
	QString lasFile = QFileDialog::getOpenFileName(this, QStringLiteral("打开点云数据"),
		".", QStringLiteral("(*.las)"));
	if (!lasFile.isEmpty())
	{
		this->openEdit->setText(lasFile);
	}
}

void QsConvertFormat::saveFile()
{
	QString pcdFile = QFileDialog::getSaveFileName(this, QStringLiteral("转换点云数据"),
		".", QStringLiteral("(*.pcd)"));
	if (!pcdFile.isEmpty())
	{
		this->saveEdit->setText(pcdFile);
	}
}

int QsConvertFormat::las2pcd()
{
	try
	{
		//确定las文件输入路径以及pcd文件输出路径
	//string name = filename.toStdString();
		//const char* lasfile = "C:\\Users\\duke\\Desktop\\all.las";
		//const char* pcdfile = "123.pcd";
		std::ifstream ifs;
		ifs.open(this->openEdit->text().toLocal8Bit().data(), std::ios::in | std::ios::binary);
		if (!ifs)
		{
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("点云转换失败！"));
			return 0;
		}

		liblas::ReaderFactory f;
		liblas::Reader reader = f.CreateWithStream(ifs);
		liblas::Header const& header = reader.GetHeader();
		QByteArray subpcd = this->saveEdit->text().toLatin1();
		const char* pcdfile = subpcd.data();
		//QFile data(this->saveEdit->text());
		if (!pcdfile==NULL)
		{
			pcl::PointCloud<pcl::PointXYZ>::Ptr pointCloudPtr(new pcl::PointCloud<pcl::PointXYZ>);
			int count = header.GetPointRecordsCount();
			pointCloudPtr->resize(count);
			pointCloudPtr->width = 1;
			pointCloudPtr->height = count;
			pointCloudPtr->is_dense = false;

			int i = 0;
			liblas::Point const& p = reader.GetPoint();
			int x_weight = (int)p.GetX();
			int y_weight = (int)p.GetY();
			pointCloudPtr->points[10].z = p.GetZ();
			int z_weight = (int)pointCloudPtr->points[10].z;
			while (reader.ReadNextPoint())
			{
				liblas::Point const& p = reader.GetPoint();
				pointCloudPtr->points[i].x = p.GetX();
				pointCloudPtr->points[i].y = p.GetY();
				pointCloudPtr->points[i].z = p.GetZ();
				if (pointCloudPtr->points[i].x > 0 & pointCloudPtr->points[i].y > 0 & pointCloudPtr->points[i].z > 0)
				{
					pointCloudPtr->points[i].x = pointCloudPtr->points[i].x - x_weight;
					pointCloudPtr->points[i].y = pointCloudPtr->points[i].y - y_weight;
					pointCloudPtr->points[i].z = pointCloudPtr->points[i].z - z_weight;
				}
				++i;
			}
			pcl::io::savePCDFileASCII(pcdfile, *pointCloudPtr);
		}
		else
		{
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("点云转换失败！"));
			return 0;
		}

		ifs.close();

		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("点云转换完成！"));
		this->close();
		return 1;
			
	}
	catch (QException ex)
	{
		QErrorMessage msgbox(this);
		msgbox.setWindowTitle(QStringLiteral("错误消息框"));
		msgbox.showMessage(ex.what());
		msgbox.exec();
		//QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("点云转换失败！") + ex.what());
		return 0;
	}

}