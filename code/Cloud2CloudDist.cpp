#include "Cloud2CloudDist.h"

//system
#include <cmath>


// For each lidar point, we find its neibors in cloth particles by  Rounding operation.
//use for neighbor particles to do bilinear interpolation.

bool Cloud2CloudDist::Compute(const Cloth& cloth,
	const wl::PointCloud& pc,
	double class_threshold,
	std::vector<int>& groundIndexes,
	std::vector<int>& offGroundIndexes,
	unsigned N/*=3*/)
{

	try
	{
		//�ҵ�ÿ�������״�㵽����ֱ�ӵľ��룬�øþ�����ֵ���Ե��ƽ��з���
		//˫���Բ�ֵ
		// for each lidar point, find the projection in the cloth grid, and the sub grid which contains it.
		//use the four corner of the subgrid to do bilinear interpolation;
		for (int i = 0; i < pc.size(); i++)
		{
			double pc_x = pc[i].x;
			double pc_z = pc[i].z;
			//���������벼�ϵ����Ͻ��������
			double deltaX = pc_x - cloth.origin_pos.x;
			double deltaZ = pc_z - cloth.origin_pos.z;
			//�õ���������ڲ���С�������Ͻǵ����� �����ĸ��ǵ�ֱ�Ϊ0 1 2 3 ˳ʱ����
			int col0 = int(deltaX / cloth.step_x);
			int row0 = int(deltaZ / cloth.step_y);
			int col1 = col0 + 1;
			int row1 = row0;
			int col2 = col0 + 1;
			int row2 = row0 + 1;
			int col3 = col0;
			int row3 = row0 + 1;
			//�����������Ͻǽ�������ϵ���������һ����[0,1]
			double subdeltaX = (deltaX - col0*cloth.step_x) / cloth.step_x;
			double subdeltaZ = (deltaZ - row0*cloth.step_y) / cloth.step_y;
			//cout << subdeltaX << " " << subdeltaZ << endl;
			//˫���Բ�ֵ bilinear interpolation;
			//f(x,y)=f(0,0)(1-x)(1-y)+f(0,1)(1-x)y+f(1,1)xy+f(1,0)x(1-y)
			double fxy = cloth.getParticle(col0, row0).pos.y * (1 - subdeltaX)*(1 - subdeltaZ)
				+ cloth.getParticle(col3, row3).pos.y * (1 - subdeltaX)*subdeltaZ
				+ cloth.getParticle(col2, row2).pos.y * subdeltaX*subdeltaZ
				+ cloth.getParticle(col1, row1).pos.y * subdeltaX*(1 - subdeltaZ);
			double height_var = fxy - pc[i].y;
			if (std::fabs(height_var) < class_threshold)
			{
				groundIndexes.push_back(i);
			}
			else
			{
				offGroundIndexes.push_back(i);
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


