#pragma once
#ifndef _RASTERIZATION_H_
#define _RASTERIZATION_H_

#include "Cloth.h"
#include "PointCloud.h"

#define SQUARE_DIST(x1,y1,x2,y2) (((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2)))

class Rasterization
{
public:

	//for a cloth particle, if no corresponding lidar point are found. 
	//the heightval are set as its neighbor's
	double static findHeightValByNeighbor(Particle *p, Cloth &cloth);
	double static findHeightValByScanline(Particle *p, Cloth &cloth);

	//�Ե��ƽ������ٽ�������Ѱ����Χ�����N����  ����������
	static bool RasterTerrain(Cloth& cloth, const wl::PointCloud& pc, std::vector<double>& heightVal, unsigned KNN = 1);

};

#endif //_RASTERIZATION_H_
