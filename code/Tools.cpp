#include "Tools.h"

QTime time;

Tools::Tools()
{
}


Tools::~Tools()
{
}

//��ȡȫ·���е��ļ���������׺��
std::string getFileName(std::string file_name)
{
	std::string subname;
	for (auto i = file_name.end() - 1; *i != '/'; i--)
	{
		subname.insert(subname.begin(), *i);
	}
	return subname;
}

//��ʱ��ʼ
void timeStart()
{
	time.start();
}

//��ʱ����
QString timeOff()
{
	int timediff = time.elapsed();   //���ش��ϴ�start()��restart()��ʼ������ʱ����λms
	float f = timediff / 1000.0;
	QString tr_timediff = QString("%1").arg(f);  //float->QString
	return tr_timediff;
}