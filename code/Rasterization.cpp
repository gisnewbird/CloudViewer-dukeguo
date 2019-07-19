#include "Rasterization.h"
#include <iostream>
#include <queue>
using namespace std;
//Since all the particles in cloth are formed as a regular grid, 
//for each lidar point, its nearest Cloth point can be simply found by Rounding operation
//then record all the correspoinding lidar point for each cloth particle


double Rasterization::findHeightValByScanline(Particle *p, Cloth &cloth)
{
	int xpos = p->pos_x;
	int ypos = p->pos_y;
	//横向向右扫描
	for (int i = xpos + 1; i < cloth.num_particles_width; i++)
	{
		double crresHeight = cloth.getParticle(i, ypos).nearestPointHeight;
		if (crresHeight > MIN_INF)
			return crresHeight;
	}
	//横向向左扫描
	for (int i = xpos - 1; i >= 0; i--)
	{
		double crresHeight = cloth.getParticle(i, ypos).nearestPointHeight;
		if (crresHeight > MIN_INF)
			return crresHeight;
	}
	//纵向向上扫描
	for (int j = ypos - 1; j >= 0; j--)
	{
		double crresHeight = cloth.getParticle(xpos, j).nearestPointHeight;
		if (crresHeight > MIN_INF)
			return crresHeight;
	}
	//纵向向下扫描
	for (int j = ypos + 1; j < cloth.num_particles_height; j++)
	{
		double crresHeight = cloth.getParticle(xpos, j).nearestPointHeight;
		if (crresHeight > MIN_INF)
			return crresHeight;
	}

	return findHeightValByNeighbor(p, cloth);


}

double Rasterization::findHeightValByNeighbor(Particle *p, Cloth &cloth)
{
	queue<Particle*> nqueue;
	vector<Particle *> pbacklist;
	size_t neiborsize = p->neighborsList.size();
	for (size_t i = 0; i < neiborsize; i++)
	{
		p->isVisited = true;
		nqueue.push(p->neighborsList[i]);
	}

	//iterate over the nqueue
	while (!nqueue.empty())
	{
		Particle *pneighbor = nqueue.front();
		nqueue.pop();
		pbacklist.push_back(pneighbor);
		if (pneighbor->nearestPointHeight > MIN_INF)
		{
			for (int i = 0; i < pbacklist.size(); i++)
				pbacklist[i]->isVisited = false;
			while (!nqueue.empty())
			{
				Particle *pp = nqueue.front();
				pp->isVisited = false;
				nqueue.pop();
			}
			return pneighbor->nearestPointHeight;
		}
		else
		{
			size_t nsize = pneighbor->neighborsList.size();
			for (size_t i = 0; i < nsize; i++)
			{
				Particle *ptmp = pneighbor->neighborsList[i];
				if (!ptmp->isVisited)
				{
					ptmp->isVisited = true;
					nqueue.push(ptmp);
				}
			}

		}
	}
	return MIN_INF;
}

bool Rasterization::RasterTerrain(Cloth& cloth, const wl::PointCloud& pc, std::vector<double>& heightVal, unsigned KNN)
{
	try
	{
		//首先对每个lidar点找到在布料网格中对应的节点，并记录下来
		//find the nearest cloth particle for each lidar point by Rounding operation
		for (int i = 0; i < pc.size(); i++)
		{
			double pc_x = pc[i].x;
			double pc_z = pc[i].z;
			//将该坐标与布料的左上角坐标相减 minus the top-left corner of the cloth
			double deltaX = pc_x - cloth.origin_pos.x;
			double deltaZ = pc_z - cloth.origin_pos.z;
			int col = int(deltaX / cloth.step_x + 0.5);
			int row = int(deltaZ / cloth.step_y + 0.5);
			if (col >= 0 && row >= 0)
			{
				Particle& pt = cloth.getParticle(col, row);
				//Particle pt = cloth.getParticle(col, row); this give wrong results, since it made a copy
				pt.correspondingLidarPointList.push_back(i);
				double pc2particleDist = SQUARE_DIST(pc_x, pc_z, pt.pos.x, pt.pos.z);
				if (pc2particleDist < pt.tmpDist)
				{
					pt.tmpDist = pc2particleDist;
					pt.nearestPointHeight = pc[i].y;
					pt.nearestPointIndex = i;
				}
			}
		}


		heightVal.resize(cloth.getSize());
		//#pragma omp parallel for
		for (int i = 0; i < cloth.getSize(); i++)
		{
			Particle& pcur = cloth.getParticleByIndex(i);
			double nearestHeight = pcur.nearestPointHeight;

			if (nearestHeight > MIN_INF)
			{
				heightVal[i] = nearestHeight;
			}
			else
			{
				heightVal[i] = findHeightValByScanline(&pcur, cloth);
			}

		}
	}
	catch (const std::bad_alloc&)
	{
		//not enough memory
		return false;
	}

	return true;
}
