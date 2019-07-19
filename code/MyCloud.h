#pragma once

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <string>

using namespace std;

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

class MyCloud
{
public:
	MyCloud();
	~MyCloud();

	PointCloudT::Ptr cloud;  //����ָ��
	string filename;  //���Ƶ�ȫ·���ļ���
	string subname;  //���Ƶ��ļ���
	string dirname = "E:\\Date\\PointCloud\\";
	bool visible = true;  //������ viewer ���Ƿ�ɼ�


};

