// DSItest1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"iostream"
#include <fstream>
#include <sstream>
#include"gmDSIinterp.h"
using namespace DSIInterpolate;

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

int main()
{
	double eps = 0.0001;//允许误差最大值
	dm_dsi_Interpolate dsi;//插值对象
	string filename, filename1;
	//文件路径 
	string path = "C:\\Users\\hp\\Desktop\\";
	filename = "modelA6.txt";
	filename1 = "new modelA6.txt";
	ifstream infile((path + filename).c_str());
	ofstream newfile((path + filename1).c_str());
	vector<DSI_3DOT>  srcDlist;
	string line;
	int text,j,k;
	int a = 0;
	j = k = 0;
	long int n,m, pass;
	n = 0;

	/////////////////////////////////////////
	//for (long int i = 0; i < 89978; i++)
	//{
	//	if (i <= 4)
	//	{
	//		continue;
	//	}
	//	if (i == 5)
	//	{
	//		infile >> n;
	//		continue;
	//	}
	//	if (i < 34549)
	//	{
	//		infile >> dsi.Nodes[i].Pnt.x >> dsi.Nodes[i].Pnt.y >> dsi.Nodes[i].Pnt.z >> a;
	//		continue;
	//	}
	//	if (i == 34549 || i == 34550)
	//	{
	//		continue;
	//	}
	//	if (i == 34551)
	//	{
	//		infile >> m;
	//		continue;
	//	}
	//	infile >> dsi.Tragles[a].NodeIDs[0]>> dsi.Tragles[a].NodeIDs[1]>> dsi.Tragles[a].NodeIDs[2]>>a ;
	//	
	//}

	/*ifstream infile1;
	long int i = 1;
	string x, y, z;
	infile1.open("modelA6.mesh");*/
	while (!infile.eof())            // 若未到文件结束一直循环
	{
		infile >> line;
		infile >> n;
		//infile1 >> dsi.Nodes[i-2].Pnt.x >> dsi.Nodes[i-2].Pnt.y >> dsi.Nodes[i-2].Pnt.z >> a;
		for (long int i = 0; i < n; i++)
		{
			infile >> line;
			dsi.Nodes[i].Pnt.x = stringToNum<double>(line);
			infile >> line;
			dsi.Nodes[i].Pnt.y = stringToNum<double>(line);
			infile >> line;
			dsi.Nodes[i].Pnt.z = stringToNum<double>(line);
			infile >> a;
		}
	}
	infile.close();   //关闭文件


	//while (true) {
	//	//从 modelA6.mesh 读入数据到 srcDlist 中
	//	//infile >> line;
	//	if (infile.eof())
	//		break;

	//	if (line == "Vertices")
	//	{
	//		infile >> pass;             //换行读取文件
	//		infile >> n;
	//		for (int i = 0; i < n; i++)
	//		{
	//			/*if (line != "0")
	//			{
	//				infile >> dsi.Nodes[i].Pnt.x >> dsi.Nodes[i].Pnt.y >> dsi.Nodes[i].Pnt.z >> a;
	//			}
	//			else
	//				continue;*/
	//			infile >> dsi.Nodes[i].Pnt.x >> dsi.Nodes[i].Pnt.y >> dsi.Nodes[i].Pnt.z >> a;
	//		}
	//	}
	//	if (line == "Triangles")
	//	{
	//		infile >> pass;             //换行读取文件
	//		infile >> m;
	//		dsi.Tragles.resize(m);
	//		for (int a = 0; a < m; a++)
	//		{   //储存三角网三角形的三个顶点
	//			if (line != "0")
	//			{
	//				infile >> dsi.Tragles[a].NodeIDs[0];
	//				infile >> dsi.Tragles[a].NodeIDs[1];
	//				infile >> dsi.Tragles[a].NodeIDs[2];
	//			}
	//			else
	//				continue;
	//		}
	//	}
	//}

	dsi.DiscreteSmoothInterpolation(srcDlist, eps);
	text = dsi.Nodes.size();
	newfile << "Vertices";
	newfile << text;
	while(j<text)
	{
			newfile << dsi.Nodes[j].Pnt.x << " ";
			newfile << dsi.Nodes[j].Pnt.y << " ";
			newfile << dsi.Nodes[j].Pnt.z << " ";
			newfile << 0;
			j++;
	}	
	text = dsi.Tragles.size();
	newfile << "Triangles";
	newfile << text;
	while (k < text)
	{
		newfile << dsi.Tragles[k].NodeIDs[0];
		newfile << dsi.Tragles[k].NodeIDs[1];
		newfile << dsi.Tragles[k].NodeIDs[2];
		k++;
	}
	newfile.close();
	return 0;
}


