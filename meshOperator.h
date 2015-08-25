#ifndef _MESH_OPERATOR_H_
#define _MESH_OPERATOR_H_
#include "test.h"

double lengthOfCBar(Line a, const const std::vector<Vertex>& grid)
{
	double length = (grid[a.v1-1].x - grid[a.v2-1].x) * (grid[a.v1-1].x - grid[a.v2-1].x) +
		(grid[a.v1-1].y - grid[a.v2-1].y) * (grid[a.v1-1].y - grid[a.v2-1].y) + 
		(grid[a.v1-1].z - grid[a.v2-1].z) * (grid[a.v1-1].z - grid[a.v2-1].z);
	return sqrt(length);
}

void subdividSphere(double radius, int subLevel, const std::vector<Vertex>& grid, 
	const std::vector<Face>& ctria3, std::vector<Vertex>& newgrid, std::vector<Face>& newctria3)
{
	newgrid.assign(grid.begin(), grid.end());
	std::map<Line, int> cbarTest;
	double lengthMax = std::numeric_limits<double>::min();
	double lengthMin = std::numeric_limits<double>::max();
	double tempLength;
	double avgLength = 0.0;
	std::cout << "begin to subdibidSphere function" << std::endl;
	std::cout << "origin grid size is " << grid.size() << std::endl;
	std::cout << "origin ctria3 size is " << ctria3.size() << std::endl;
	Line tempLine;
	std::map<Line, int>::iterator pos;
	for(size_t i = 0; i < ctria3.size(); ++i)
	{
		Vertex midV1, midV2, midV3;
		//int midV1No, midV2No, midV3No;
		/////////////////////////////////////////////////////////////////////////////////////
		//first edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v2);
		tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v2);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV1.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV1.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV1.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			tempLength = sqrt(midV1.x*midV1.x + midV1.y*midV1.y + midV1.z*midV1.z);
			midV1.x *= radius / tempLength;
			midV1.y *= radius / tempLength;
			midV1.z *= radius / tempLength;
			newgrid.push_back(midV1);
			midV1.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			tempLength = lengthOfCBar(tempLine, grid) / 2;
			avgLength += tempLength*2;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);
		}
		else
		{
			midV1.x = newgrid[pos->second-1].x;
			midV1.y = newgrid[pos->second-1].y;
			midV1.z = newgrid[pos->second-1].z;
			midV1.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//second edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v2, ctria3[i].v3);
		tempLine.v2 = std::max(ctria3[i].v2, ctria3[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV2.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV2.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV2.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			tempLength = sqrt(midV2.x*midV2.x + midV2.y*midV2.y + midV2.z*midV2.z);
			midV2.x *= radius / tempLength;
			midV2.y *= radius / tempLength;
			midV2.z *= radius / tempLength;
			newgrid.push_back(midV2);
			midV2.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			tempLength = lengthOfCBar(tempLine, grid) / 2;
			avgLength += tempLength*2;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);
		}
		else
		{
			midV2.x = newgrid[pos->second-1].x;
			midV2.y = newgrid[pos->second-1].y;
			midV2.z = newgrid[pos->second-1].z;
			midV2.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//third edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v3);
		tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV3.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV3.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV3.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			tempLength = sqrt(midV3.x*midV3.x + midV3.y*midV3.y + midV3.z*midV3.z);
			midV3.x *= radius / tempLength;
			midV3.y *= radius / tempLength;
			midV3.z *= radius / tempLength;
			newgrid.push_back(midV3);
			midV3.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			tempLength = lengthOfCBar(tempLine, grid) / 2.0;
			avgLength += tempLength*2;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);
		}
		else
		{
			midV3.x = newgrid[pos->second-1].x;
			midV3.y = newgrid[pos->second-1].y;
			midV3.z = newgrid[pos->second-1].z;
			midV3.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//construct new triangle
		/////////////////////////////////////////////////////////////////////////////////////
		Face tempFace;
		tempFace.v1 = ctria3[i].v1;
		tempFace.v2 = midV1.No;
		tempFace.v3 = midV3.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = midV1.No;
		tempFace.v2 = ctria3[i].v2;
		tempFace.v3 = midV2.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = midV1.No;
		tempFace.v2 = midV2.No;
		tempFace.v3 = midV3.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = midV3.No;
		tempFace.v2 = midV2.No;
		tempFace.v3 = ctria3[i].v3;
		newctria3.push_back(tempFace);
	}
	avgLength /= (cbarTest.size()*2);
	std::cout << "length Max = " << lengthMax << std::endl;
	std::cout << "length Min = " << lengthMin << std::endl;
	std::cout << "avg length = " << avgLength << std::endl;
	std::cout << "new grid size = " << newgrid.size() << std::endl;
	std::cout << "new ctria size = " << newctria3.size() << std::endl;
	std::cout << "end of subdibidSphere function" << std::endl;
}

void rate_Tri_Face_Edge(const std::vector<Vertex>& grid, const std::vector<Face>& ctria3)
{
	static int commonLine = 0;
	//Vertex maxXV, maxYV, maxZV;
	std::map<Line, int> cbarTest;
	std::map<Line, int> commonLineTest;
	double lengthMax = std::numeric_limits<double>::min();
	double lengthMin = std::numeric_limits<double>::max();
	double tempLength;
	double avgLength = 0.0;
	std::cout << "BEGIN:" << std::endl;
	//readNas("D:\\model\\y80_01.nas");
	std::cout << "grid size is " << grid.size() << std::endl;
	std::cout << "ctria3 size is " << ctria3.size() << std::endl;
	Line tempLine;
	std::map<Line, int>::iterator pos;
	for(int i = 0; i < ctria3.size(); ++i)
	{
		
		tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v2);
		tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v2);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			cbarTest.insert(std::make_pair(tempLine, i+1));
			tempLength = lengthOfCBar(tempLine, grid);
			avgLength += tempLength;
			if(tempLength > lengthMax)
				lengthMax = tempLength;
			if(tempLength < lengthMin)
				lengthMin = tempLength;
		}
		else
		{
			commonLineTest.insert(std::make_pair(tempLine, i+1));
			++commonLine;
		}
		
		///////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v2, ctria3[i].v3);
		tempLine.v2 = std::max(ctria3[i].v2, ctria3[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			cbarTest.insert(std::make_pair(tempLine, i+1));
			tempLength = lengthOfCBar(tempLine, grid);
			if(tempLength > lengthMax)
				lengthMax = tempLength;
			if(tempLength < lengthMin)
				lengthMin = tempLength;
			avgLength += tempLength;
		}
		else
		{
			commonLineTest.insert(std::make_pair(tempLine, i+1));
			++commonLine;
		}
		////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v3, ctria3[i].v1);
		tempLine.v2 = std::max(ctria3[i].v3, ctria3[i].v1);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			cbarTest.insert(std::make_pair(tempLine, i+1));
			tempLength = lengthOfCBar(tempLine, grid);
			if(tempLength > lengthMax)
				lengthMax = tempLength;
			if(tempLength < lengthMin)
				lengthMin = tempLength;
			avgLength += tempLength;
		}
		else
		{
			commonLineTest.insert(std::make_pair(tempLine, i+1));
			++commonLine;
		}
	}
	std::vector<Vertex> newgrid;
	std::vector<Face> newctria3;
	std::vector<Quad> newcquad4;
	std::vector<Tet> newctetra;
	for(std::map<Line, int>::iterator it = cbarTest.begin(); it != cbarTest.end(); ++it)
	{
		pos = commonLineTest.find(it->first);
		if(pos==commonLineTest.end())
		{
			int iV1 = it->first.v1;
			int iV2 = it->first.v2;
			std::cout << iV1 << "\t" << iV2 << std::endl;
			std::cout << grid[iV1-1].x << "\t" << grid[iV1-1].y << "\t" << grid[iV1-1].z << std::endl;
			std::cout << grid[iV2-1].x << "\t" << grid[iV2-1].y << "\t" << grid[iV2-1].z << std::endl << std::endl;
			Face tempFace;
			tempFace = ctria3[it->second-1];
			newctria3.push_back(tempFace);
		}
	}
	//writeNas("C:\\Users\\Administrator\\Desktop\\model\\errface.nas", grid, newctria3, newcquad4, newctetra);
	avgLength /= cbarTest.size();
	std::cout << "commonLine is " << commonLine << std::endl;
	std::cout << "cbar size is " << cbarTest.size() << std::endl;
	std::cout << "avgLength = " << avgLength << std::endl;
	std::cout << "length Max = " << lengthMax << std::endl;
	std::cout << "length Min = " << lengthMin << std::endl;
	std::cout << "cbar / ctria3 = " << (cbarTest.size() * 1.0) / (ctria3.size()*1.0) << std::endl;
	std::cout << "END;" << std::endl;
}

void threePointsubdividSphere(double radius, int subLevel, std::vector<Vertex>& grid, 
	std::vector<Face>& ctria3, std::vector<Vertex>& newgrid, std::vector<Face>& newctria3)
{
	newgrid.assign(grid.begin(), grid.end());
	std::map<Line, int> cbarTest;
	double lengthMax = std::numeric_limits<double>::min();
	double lengthMin = std::numeric_limits<double>::max();
	double tempLength;
	double avgLength = 0.0;
	std::cout << "begin to subdibidSphere function" << std::endl;
	std::cout << "origin grid size is " << grid.size() << std::endl;
	std::cout << "origin ctria3 size is " << ctria3.size() << std::endl;
	Line tempLine;
	std::map<Line, int>::iterator pos;
	for(size_t i = 0; i < ctria3.size(); ++i)
	{
		//std::vector<int> v;
		//v.push_back(ctria3[i].v1);
		//v.push_back(ctria3[i].v2);
		//v.push_back(ctria3[i].v3);
		//std::sort(v.begin(), v.end());
		//ctria3[i].v1 = v[0];
		//ctria3[i].v2 = v[1];
		//ctria3[i].v3 = v[2];

		Vertex triV1, triV2, triV3, triV4, triV5, triV6, inV1;
		//int midV1No, midV2No, midV3No;
		/////////////////////////////////////////////////////////////////////////////////////
		//first edge triV1, triV2
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v2);
		tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v2);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			tempLine.v1 = ctria3[i].v1;
			tempLine.v2 = ctria3[i].v2;
			triV1.x = (grid[tempLine.v2-1].x - grid[tempLine.v1-1].x) / 3.0 + grid[tempLine.v1-1].x;
			triV1.y = (grid[tempLine.v2-1].y - grid[tempLine.v1-1].y) / 3.0 + grid[tempLine.v1-1].y;
			triV1.z = (grid[tempLine.v2-1].z - grid[tempLine.v1-1].z) / 3.0 + grid[tempLine.v1-1].z;
			triV2.x = (grid[tempLine.v2-1].x - grid[tempLine.v1-1].x) * 2 / 3.0 + grid[tempLine.v1-1].x;
			triV2.y = (grid[tempLine.v2-1].y - grid[tempLine.v1-1].y) * 2 / 3.0 + grid[tempLine.v1-1].y;
			triV2.z = (grid[tempLine.v2-1].z - grid[tempLine.v1-1].z) * 2 / 3.0 + grid[tempLine.v1-1].z;


			tempLength = sqrt(triV1.x*triV1.x + triV1.y*triV1.y + triV1.z*triV1.z);
			triV1.x *= radius / tempLength;
			triV1.y *= radius / tempLength;
			triV1.z *= radius / tempLength;
			newgrid.push_back(triV1);
			triV1.No = newgrid.size();

			tempLength = sqrt(triV2.x*triV2.x + triV2.y*triV2.y + triV2.z*triV2.z);
			triV2.x *= radius / tempLength;
			triV2.y *= radius / tempLength;
			triV2.z *= radius / tempLength;
			newgrid.push_back(triV2);
			triV2.No = newgrid.size();

			tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v2);
			tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v2);
			int newSize;
			if(tempLine.v1 == ctria3[i].v1)
				newSize = newgrid.size();
			else
				newSize = -1 * newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newSize));
			tempLength = lengthOfCBar(tempLine, grid) / 3;
			//avgLength += tempLength * 3;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);
		}
		else
		{
			int second; 
			if(pos->second < 0)
				second = pos->second * (-1);
			else 
				second = pos->second;
			triV2.x = newgrid[second-2].x;
			triV2.y = newgrid[second-2].y;
			triV2.z = newgrid[second-2].z;
			triV2.No = second-1;
			triV1.x = newgrid[second-1].x;
			triV1.y = newgrid[second-1].y;
			triV1.z = newgrid[second-1].z;
			triV1.No = second;
			//if(ctria3[i].v1 < ctria3[i].v2 && pos->second > 0
			//	||
			//	ctria3[i].v1 > ctria3[i].v2 && pos->second < 0)
			//{
			//	/*int second;
			//	if(pos->second < 0)
			//		second = (pos->second) * (-1);
			//	else 
			//		second = pos->second;
			//	triV1.x = newgrid[second-2].x;
			//	triV1.y = newgrid[second-2].y;
			//	triV1.z = newgrid[second-2].z;
			//	triV1.No = second-1;
			//	triV2.x = newgrid[second-1].x;
			//	triV2.y = newgrid[second-1].y;
			//	triV2.z = newgrid[second-1].z;
			//	triV2.No = second;*/
			//	int second; 
			//	if(pos->second < 0)
			//		second = pos->second * (-1);
			//	else 
			//		second = pos->second;
			//	triV2.x = newgrid[second-2].x;
			//	triV2.y = newgrid[second-2].y;
			//	triV2.z = newgrid[second-2].z;
			//	triV2.No = second-1;
			//	triV1.x = newgrid[second-1].x;
			//	triV1.y = newgrid[second-1].y;
			//	triV1.z = newgrid[second-1].z;
			//	triV1.No = second;
			//}
			//else if(ctria3[i].v1 > ctria3[i].v2 && pos->second > 0
			//		||
			//	ctria3[i].v1 < ctria3[i].v2 && pos->second < 0
			//	)
			//{
			//	//continue;
			//	int second; 
			//	if(pos->second < 0)
			//		second = pos->second * (-1);
			//	else 
			//		second = pos->second;
			//	triV2.x = newgrid[second-2].x;
			//	triV2.y = newgrid[second-2].y;
			//	triV2.z = newgrid[second-2].z;
			//	triV2.No = second-1;
			//	triV1.x = newgrid[second-1].x;
			//	triV1.y = newgrid[second-1].y;
			//	triV1.z = newgrid[second-1].z;
			//	triV1.No = second;
			//}
			//else
			//{
			//	std::cout << "error1" << std::endl; 
			//	continue;
			//}
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//second edge triV3, triV4
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v2, ctria3[i].v3);
		tempLine.v2 = std::max(ctria3[i].v2, ctria3[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			tempLine.v1 = ctria3[i].v2;
			tempLine.v2 = ctria3[i].v3;
			triV3.x = (grid[tempLine.v2-1].x - grid[tempLine.v1-1].x) / 3.0 + grid[tempLine.v1-1].x;
			triV3.y = (grid[tempLine.v2-1].y - grid[tempLine.v1-1].y) / 3.0 + grid[tempLine.v1-1].y;
			triV3.z = (grid[tempLine.v2-1].z - grid[tempLine.v1-1].z) / 3.0 + grid[tempLine.v1-1].z;
			triV4.x = (grid[tempLine.v2-1].x - grid[tempLine.v1-1].x) * 2 / 3.0 + grid[tempLine.v1-1].x;
			triV4.y = (grid[tempLine.v2-1].y - grid[tempLine.v1-1].y) * 2 / 3.0 + grid[tempLine.v1-1].y;
			triV4.z = (grid[tempLine.v2-1].z - grid[tempLine.v1-1].z) * 2 / 3.0 + grid[tempLine.v1-1].z;


			tempLength = sqrt(triV3.x*triV3.x + triV3.y*triV3.y + triV3.z*triV3.z);
			triV3.x *= radius / tempLength;
			triV3.y *= radius / tempLength;
			triV3.z *= radius / tempLength;
			newgrid.push_back(triV3);
			triV3.No = newgrid.size();

			tempLength = sqrt(triV4.x*triV4.x + triV4.y*triV4.y + triV4.z*triV4.z);
			triV4.x *= radius / tempLength;
			triV4.y *= radius / tempLength;
			triV4.z *= radius / tempLength;
			newgrid.push_back(triV4);
			triV4.No = newgrid.size();

			tempLine.v1 = std::min(ctria3[i].v2, ctria3[i].v3);
			tempLine.v2 = std::max(ctria3[i].v2, ctria3[i].v3);
			int newSize;
			if(tempLine.v1 == ctria3[i].v2)
				newSize = newgrid.size();
			else
				newSize = -1 * newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newSize));
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			tempLength = lengthOfCBar(tempLine, grid) / 3;
			//avgLength += tempLength * 3;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);
		}
		else
		{
			int second; 
			if(pos->second < 0)
				second = pos->second * (-1);
			else 
				second = pos->second;
			triV4.x = newgrid[second-2].x;
			triV4.y = newgrid[second-2].y;
			triV4.z = newgrid[second-2].z;
			triV4.No = second-1;
			triV3.x = newgrid[second-1].x;
			triV3.y = newgrid[second-1].y;
			triV3.z = newgrid[second-1].z;
			triV3.No = second;
			//if(ctria3[i].v2 < ctria3[i].v3 && pos->second > 0
			//   ||
			//   ctria3[i].v2 > ctria3[i].v3 && pos->second < 0)
			//{
			//	/*int second;
			//	if(pos->second < 0)
			//	second = (pos->second) * (-1);
			//	else 
			//	second = pos->second;
			//	triV3.x = newgrid[second-2].x;
			//	triV3.y = newgrid[second-2].y;
			//	triV3.z = newgrid[second-2].z;
			//	triV3.No = second-1;
			//	triV4.x = newgrid[second-1].x;
			//	triV4.y = newgrid[second-1].y;
			//	triV4.z = newgrid[second-1].z;
			//	triV4.No = second;*/
			//	//continue;
			//	int second; 
			//	if(pos->second < 0)
			//		second = pos->second * (-1);
			//	else 
			//		second = pos->second;
			//	triV4.x = newgrid[second-2].x;
			//	triV4.y = newgrid[second-2].y;
			//	triV4.z = newgrid[second-2].z;
			//	triV4.No = second-1;
			//	triV3.x = newgrid[second-1].x;
			//	triV3.y = newgrid[second-1].y;
			//	triV3.z = newgrid[second-1].z;
			//	triV3.No = second;
			//}
			//else if(ctria3[i].v2 < ctria3[i].v3 && pos->second < 0
			//	||
			//	ctria3[i].v2 > ctria3[i].v3 && pos->second > 0
			//	)
			//{
			//	//continue;
			//	int second; 
			//	if(pos->second < 0)
			//		second = pos->second * (-1);
			//	else 
			//		second = pos->second;
			//	triV4.x = newgrid[second-2].x;
			//	triV4.y = newgrid[second-2].y;
			//	triV4.z = newgrid[second-2].z;
			//	triV4.No = second-1;
			//	triV3.x = newgrid[second-1].x;
			//	triV3.y = newgrid[second-1].y;
			//	triV3.z = newgrid[second-1].z;
			//	triV3.No = second;
			//}
			//else
			//{
			//	std::cout << "error2" << std::endl; 
			//	continue;
			//}

		}
		/////////////////////////////////////////////////////////////////////////////////////
		//third edge triV5, triV6
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v3);
		tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			tempLine.v1 = ctria3[i].v1;
			tempLine.v2 = ctria3[i].v3;
			triV6.x = (grid[tempLine.v2-1].x - grid[tempLine.v1-1].x) / 3.0 + grid[tempLine.v1-1].x;
			triV6.y = (grid[tempLine.v2-1].y - grid[tempLine.v1-1].y) / 3.0 + grid[tempLine.v1-1].y;
			triV6.z = (grid[tempLine.v2-1].z - grid[tempLine.v1-1].z) / 3.0 + grid[tempLine.v1-1].z;
			triV5.x = (grid[tempLine.v2-1].x - grid[tempLine.v1-1].x) * 2 / 3.0 + grid[tempLine.v1-1].x;
			triV5.y = (grid[tempLine.v2-1].y - grid[tempLine.v1-1].y) * 2 / 3.0 + grid[tempLine.v1-1].y;
			triV5.z = (grid[tempLine.v2-1].z - grid[tempLine.v1-1].z) * 2 / 3.0 + grid[tempLine.v1-1].z;


			tempLength = sqrt(triV5.x*triV5.x + triV5.y*triV5.y + triV5.z*triV5.z);
			triV5.x *= radius / tempLength;
			triV5.y *= radius / tempLength;
			triV5.z *= radius / tempLength;
			newgrid.push_back(triV5);
			triV5.No = newgrid.size();

			tempLength = sqrt(triV6.x*triV6.x + triV6.y*triV6.y + triV6.z*triV6.z);
			triV6.x *= radius / tempLength;
			triV6.y *= radius / tempLength;
			triV6.z *= radius / tempLength;
			newgrid.push_back(triV6);
			triV6.No = newgrid.size();

			tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v3);
			tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v3);
			int newSize;
			if(tempLine.v1 == ctria3[i].v1)
				newSize = newgrid.size();
			else
				newSize = -1 * newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newSize));
			tempLength = lengthOfCBar(tempLine, grid) / 3;
			//avgLength += tempLength * 3;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);
		}
		else
		{
			int second; 
			if(pos->second < 0)
				second = pos->second * (-1);
			else 
				second = pos->second;
			triV6.x = newgrid[second-2].x;
			triV6.y = newgrid[second-2].y;
			triV6.z = newgrid[second-2].z;
			triV6.No = second-1;
			triV5.x = newgrid[second-1].x;
			triV5.y = newgrid[second-1].y;
			triV5.z = newgrid[second-1].z;
			triV5.No = second;
			//if(ctria3[i].v1 < ctria3[i].v3 && pos->second > 0
			//	||
			//	ctria3[i].v1 > ctria3[i].v3 && pos->second < 0)
			//{
			//	/*int second;
			//	if(pos->second < 0)
			//		second = (pos->second) * (-1);
			//	else 
			//		second = pos->second;
			//	triV5.x = newgrid[second-2].x;
			//	triV5.y = newgrid[second-2].y;
			//	triV5.z = newgrid[second-2].z;
			//	triV5.No = second-1;
			//	triV6.x = newgrid[second-1].x;
			//	triV6.y = newgrid[second-1].y;
			//	triV6.z = newgrid[second-1].z;
			//	triV6.No = second;*/
			//	int second; 
			//	if(pos->second < 0)
			//		second = pos->second * (-1);
			//	else 
			//		second = pos->second;
			//	triV6.x = newgrid[second-2].x;
			//	triV6.y = newgrid[second-2].y;
			//	triV6.z = newgrid[second-2].z;
			//	triV6.No = second-1;
			//	triV5.x = newgrid[second-1].x;
			//	triV5.y = newgrid[second-1].y;
			//	triV5.z = newgrid[second-1].z;
			//	triV5.No = second;
			//}
			//else if(ctria3[i].v1 < ctria3[i].v3 && pos->second < 0
			//	||
			//	ctria3[i].v1 > ctria3[i].v3 && pos->second > 0
			//	)
			//{
			//	//continue;
			//	int second; 
			//	if(pos->second < 0)
			//		second = pos->second * (-1);
			//	else 
			//		second = pos->second;
			//	triV6.x = newgrid[second-2].x;
			//	triV6.y = newgrid[second-2].y;
			//	triV6.z = newgrid[second-2].z;
			//	triV6.No = second-1;
			//	triV5.x = newgrid[second-1].x;
			//	triV5.y = newgrid[second-1].y;
			//	triV5.z = newgrid[second-1].z;
			//	triV5.No = second;
			//}
			//else
			//{
			//	std::cout << "error3" << std::endl;
			//	continue;
			//}
		}

		/////////////////////////////////////////////////////////////////////////////////////
		//create interior point
		/////////////////////////////////////////////////////////////////////////////////////
		inV1.x = (grid[ctria3[i].v1-1].x + grid[ctria3[i].v2-1].x + grid[ctria3[i].v3-1].x) / 3.0; 
		inV1.y = (grid[ctria3[i].v1-1].y + grid[ctria3[i].v2-1].y + grid[ctria3[i].v3-1].y) / 3.0; 
		inV1.z = (grid[ctria3[i].v1-1].z + grid[ctria3[i].v2-1].z + grid[ctria3[i].v3-1].z) / 3.0;
		tempLength = sqrt(inV1.x*inV1.x + inV1.y*inV1.y + inV1.z*inV1.z);
		inV1.x *= (radius / tempLength);
		inV1.y *= (radius / tempLength);
		inV1.z *= (radius / tempLength);
		newgrid.push_back(inV1);
		inV1.No = newgrid.size();

		/////////////////////////////////////////////////////////////////////////////////////
		//construct new triangle
		/////////////////////////////////////////////////////////////////////////////////////
		Face tempFace;
		tempFace.v1 = ctria3[i].v1;
		tempFace.v2 = triV1.No;
		tempFace.v3 = triV6.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = triV1.No;
		tempFace.v2 = triV2.No;
		tempFace.v3 = inV1.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = triV1.No;
		tempFace.v2 = inV1.No;
		tempFace.v3 = triV6.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = triV6.No;
		tempFace.v2 = inV1.No;
		tempFace.v3 = triV5.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = triV2.No;
		tempFace.v2 = ctria3[i].v2;
		tempFace.v3 = triV3.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = triV2.No;
		tempFace.v2 = triV3.No;
		tempFace.v3 = inV1.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = inV1.No;
		tempFace.v2 = triV3.No;
		tempFace.v3 = triV4.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = inV1.No;
		tempFace.v2 = triV4.No;
		tempFace.v3 = triV5.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = triV5.No;
		tempFace.v2 = triV4.No;
		tempFace.v3 = ctria3[i].v3;
		newctria3.push_back(tempFace);
	}

	//avgLength /= (cbarTest.size()*2);
	std::cout << "length Max = " << lengthMax << std::endl;
	std::cout << "length Min = " << lengthMin << std::endl;
	//std::cout << "avg length = " << avgLength << std::endl;
	std::cout << "new grid size = " << newgrid.size() << std::endl;
	std::cout << "new ctria size = " << newctria3.size() << std::endl;
	std::cout << "end of subdibidSphere function" << std::endl;
}


void tempFunc(std::vector<Vertex>& grid, std::vector<Quad>& cquad4,
	std::vector<Vertex>& newgrid, std::vector<Quad>& newcquad4)
{
	std::map<int, int> p2p;
	std::map<int, int>::iterator pos;
	newgrid.assign(grid.begin(), grid.end());
	newcquad4.assign(cquad4.begin(), cquad4.end());
	for(int i = 0; i < grid.size(); ++i)
	{
		if(fabs(grid[i].y) > ZERO)
		{
			Vertex tempV;
			tempV.x = grid[i].x;
			tempV.y = -grid[i].y;
			tempV.z = grid[i].z;
			newgrid.push_back(tempV);
			p2p.insert(std::make_pair(i+1, newgrid.size()));
		}
	}
	for(int i = 0; i < cquad4.size(); ++i)
	{
		Quad tempQ;
		//first point
		pos = p2p.find(cquad4[i].v1);
		if(pos != p2p.end())
		{
			tempQ.v1 = pos->second;
		}
		else if(pos == p2p.end() && grid[cquad4[i].v1-1].y < ZERO)
		{
			tempQ.v1 = cquad4[i].v1;
		}
		else
		{
			std::cout << "error!!!" << std::endl; 
			break;
		}
		//second point
		pos = p2p.find(cquad4[i].v2);
		if(pos != p2p.end())
		{
			tempQ.v2 = pos->second;
		}
		else if(pos == p2p.end() && grid[cquad4[i].v2-1].y < ZERO)
		{
			tempQ.v2 = cquad4[i].v2;
		}
		else
		{
			std::cout << "error!!!" << std::endl; 
			break;
		}
		//third point
		pos = p2p.find(cquad4[i].v3);
		if(pos != p2p.end())
		{
			tempQ.v3 = pos->second;
		}
		else if(pos == p2p.end() && grid[cquad4[i].v3-1].y < ZERO)
		{
			tempQ.v3 = cquad4[i].v3;
		}
		else
		{
			std::cout << "error!!!" << std::endl; 
			break;
		}
		//fourth point
		pos = p2p.find(cquad4[i].v4);
		if(pos != p2p.end())
		{
			tempQ.v4 = pos->second;
		}
		else if(pos == p2p.end() && grid[cquad4[i].v4-1].y < ZERO)
		{
			tempQ.v4 = cquad4[i].v4;
		}
		else
		{
			std::cout << "error!!!" << std::endl; 
			break;
		}
		//end
		newcquad4.push_back(tempQ);
	}
}


void ScaleQuad(double ra, std::vector<Vertex>& grid)
{
	for(int i = 0; i < grid.size(); ++i)
	{
		double tempLength;
		tempLength = sqrt(grid[i].x*grid[i].x + grid[i].y*grid[i].y + grid[i].z*grid[i].z);
		grid[i].x *= (ra / tempLength);
		grid[i].y *= (ra / tempLength);
		grid[i].z *= (ra / tempLength);
	}
}


void subdividSphereQuad(double radius, int subLevel, const std::vector<Vertex>& grid, 
	const std::vector<Quad>& cquad4, std::vector<Vertex>& newgrid, std::vector<Quad>& newcquad4)
{
	newgrid.assign(grid.begin(), grid.end());
	std::map<Line, int> cbarTest;
	double lengthMax = std::numeric_limits<double>::min();
	double lengthMin = std::numeric_limits<double>::max();
	double tempLength;
	double avgLength = 0.0;
	std::cout << "begin to subdibidSphere function" << std::endl;
	std::cout << "origin grid size is " << grid.size() << std::endl;
	std::cout << "origin cquad4 size is " << cquad4.size() << std::endl;
	Line tempLine;
	std::map<Line, int>::iterator pos;
	for(size_t i = 0; i < cquad4.size(); ++i)
	{
		Vertex midV1, midV2, midV3, midV4, inV1;

		//int midV1No, midV2No, midV3No;
		/////////////////////////////////////////////////////////////////////////////////////
		//first edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(cquad4[i].v1, cquad4[i].v2);
		tempLine.v2 = std::max(cquad4[i].v1, cquad4[i].v2);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV1.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV1.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV1.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			tempLength = sqrt(midV1.x*midV1.x + midV1.y*midV1.y + midV1.z*midV1.z);
			midV1.x *= radius / tempLength;
			midV1.y *= radius / tempLength;
			midV1.z *= radius / tempLength;
			newgrid.push_back(midV1);
			midV1.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			/*tempLength = lengthOfCBar(tempLine, grid) / 2;
			avgLength += tempLength*2;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);*/
		}
		else
		{
			midV1.x = newgrid[pos->second-1].x;
			midV1.y = newgrid[pos->second-1].y;
			midV1.z = newgrid[pos->second-1].z;
			midV1.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//second edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(cquad4[i].v2, cquad4[i].v3);
		tempLine.v2 = std::max(cquad4[i].v2, cquad4[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV2.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV2.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV2.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			tempLength = sqrt(midV2.x*midV2.x + midV2.y*midV2.y + midV2.z*midV2.z);
			midV2.x *= radius / tempLength;
			midV2.y *= radius / tempLength;
			midV2.z *= radius / tempLength;
			newgrid.push_back(midV2);
			midV2.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			/*tempLength = lengthOfCBar(tempLine, grid) / 2;
			avgLength += tempLength*2;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);*/
		}
		else
		{
			midV2.x = newgrid[pos->second-1].x;
			midV2.y = newgrid[pos->second-1].y;
			midV2.z = newgrid[pos->second-1].z;
			midV2.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//third edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(cquad4[i].v3, cquad4[i].v4);
		tempLine.v2 = std::max(cquad4[i].v3, cquad4[i].v4);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV3.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV3.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV3.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			tempLength = sqrt(midV3.x*midV3.x + midV3.y*midV3.y + midV3.z*midV3.z);
			midV3.x *= radius / tempLength;
			midV3.y *= radius / tempLength;
			midV3.z *= radius / tempLength;
			newgrid.push_back(midV3);
			midV3.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			/*tempLength = lengthOfCBar(tempLine, grid) / 2.0;
			avgLength += tempLength*2;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);*/
		}
		else
		{
			midV3.x = newgrid[pos->second-1].x;
			midV3.y = newgrid[pos->second-1].y;
			midV3.z = newgrid[pos->second-1].z;
			midV3.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//fourth edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(cquad4[i].v4, cquad4[i].v1);
		tempLine.v2 = std::max(cquad4[i].v4, cquad4[i].v1);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV4.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV4.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV4.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			tempLength = sqrt(midV4.x*midV4.x + midV4.y*midV4.y + midV4.z*midV4.z);
			midV4.x *= radius / tempLength;
			midV4.y *= radius / tempLength;
			midV4.z *= radius / tempLength;
			newgrid.push_back(midV4);
			midV4.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			/*tempLength = lengthOfCBar(tempLine, grid) / 2.0;
			avgLength += tempLength*2;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);*/
		}
		else
		{
			midV4.x = newgrid[pos->second-1].x;
			midV4.y = newgrid[pos->second-1].y;
			midV4.z = newgrid[pos->second-1].z;
			midV4.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//construct new triangle
		/////////////////////////////////////////////////////////////////////////////////////
		inV1.x = (grid[cquad4[i].v1-1].x + grid[cquad4[i].v2-1].x + grid[cquad4[i].v3-1].x + grid[cquad4[i].v4-1].x) / 4.0;
		inV1.y = (grid[cquad4[i].v1-1].y + grid[cquad4[i].v2-1].y + grid[cquad4[i].v3-1].y + grid[cquad4[i].v4-1].y) / 4.0;
		inV1.z = (grid[cquad4[i].v1-1].z + grid[cquad4[i].v2-1].z + grid[cquad4[i].v3-1].z + grid[cquad4[i].v4-1].z) / 4.0;
		tempLength = sqrt(inV1.x*inV1.x + inV1.y*inV1.y + inV1.z*inV1.z);
		inV1.x *= radius / tempLength;
		inV1.y *= radius / tempLength;
		inV1.z *= radius / tempLength;
		newgrid.push_back(inV1);
		inV1.No = newgrid.size();

		Quad tempQuad;
		tempQuad.v1 = cquad4[i].v1;
		tempQuad.v2 = midV1.No;
		tempQuad.v3 = inV1.No;
		tempQuad.v4 = midV4.No;
		newcquad4.push_back(tempQuad);
		tempQuad.v1 = midV1.No;
		tempQuad.v2 = cquad4[i].v2;
		tempQuad.v3 = midV2.No;
		tempQuad.v4 = inV1.No;
		newcquad4.push_back(tempQuad);
		tempQuad.v1 = midV4.No;
		tempQuad.v2 = inV1.No;
		tempQuad.v3 = midV3.No;
		tempQuad.v4 = cquad4[i].v4;
		newcquad4.push_back(tempQuad);
		tempQuad.v1 = inV1.No;
		tempQuad.v2 = midV2.No;
		tempQuad.v3 = cquad4[i].v3;
		tempQuad.v4 = midV3.No;
		newcquad4.push_back(tempQuad);	
	}
	std::cout << "length Max = " << lengthMax << std::endl;
	std::cout << "length Min = " << lengthMin << std::endl;
	std::cout << "new grid size = " << newgrid.size() << std::endl;
	std::cout << "new cquad4 size = " << newcquad4.size() << std::endl;
	std::cout << "end of subdibidSphere function" << std::endl;
}


void rate_Quad_Face_Edge(const std::vector<Vertex>& grid, const std::vector<Quad>& cquad4)
{
	double lengthMax = std::numeric_limits<double>::min();
	double lengthMin = std::numeric_limits<double>::max();
	double tempLength;
	double sumLength = 0.0;
	std::cout << "BEGIN:" << std::endl;
	std::map<Line, int> cbarTest;
	std::cout << "grid size is " << grid.size() << std::endl;
	std::cout << "cquad4 size is " << cquad4.size() << std::endl;
	Line tempLine;
	for(int i = 0; i < cquad4.size(); ++i)
	{
		std::map<Line, int>::iterator pos;
		tempLine.v1 = std::min(cquad4[i].v1, cquad4[i].v2);
		tempLine.v2 = std::max(cquad4[i].v1, cquad4[i].v2);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			cbarTest.insert(std::make_pair(tempLine, 0));
			tempLength = lengthOfCBar(tempLine, grid);
			sumLength += tempLength;
			if(tempLength > lengthMax)
				lengthMax = tempLength;
			if(tempLength < lengthMin)
				lengthMin = tempLength;
		}
		///////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(cquad4[i].v2, cquad4[i].v3);
		tempLine.v2 = std::max(cquad4[i].v2, cquad4[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			cbarTest.insert(std::make_pair(tempLine, 0));
			tempLength = lengthOfCBar(tempLine, grid);
			sumLength += tempLength;
			if(tempLength > lengthMax)
				lengthMax = tempLength;
			if(tempLength < lengthMin)
				lengthMin = tempLength;
		}
		////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(cquad4[i].v3, cquad4[i].v4);
		tempLine.v2 = std::max(cquad4[i].v3, cquad4[i].v4);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			cbarTest.insert(std::make_pair(tempLine, 0));
			tempLength = lengthOfCBar(tempLine, grid);
			sumLength += tempLength;
			if(tempLength > lengthMax)
				lengthMax = tempLength;
			if(tempLength < lengthMin)
				lengthMin = tempLength;
		}
		///////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(cquad4[i].v1, cquad4[i].v4);
		tempLine.v2 = std::max(cquad4[i].v1, cquad4[i].v4);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			cbarTest.insert(std::make_pair(tempLine, 0));
			tempLength = lengthOfCBar(tempLine, grid);
			sumLength += tempLength;
			if(tempLength > lengthMax)
				lengthMax = tempLength;
			if(tempLength < lengthMin)
				lengthMin = tempLength;
		}
	}
	std::cout << "cbar size is " << cbarTest.size() << std::endl;
	std::cout << "length Max = " << lengthMax << std::endl;
	std::cout << "length Min = " << lengthMin << std::endl;
	std::cout << "cbar / cquad = " << (cbarTest.size()*1.0) / (cquad4.size()*1.0) << std::endl;
	std::cout << "sumLength / cbar = " << sumLength / cbarTest.size() << std::endl;
}

void sbudividSphereTet(double radius, int subLevel, std::vector<Vertex>& grid, std::vector<Face>& ctria3, std::vector<Tet>& ctetra,
	std::vector<Vertex>& newgrid, std::vector<Face>& newctria3, std::vector<Tet>& newctetra)
{
	newgrid.assign(grid.begin(), grid.end());
	std::map<Line, size_t> cbarTest;
	double lengthMax = std::numeric_limits<double>::min();
	double lengthMin = std::numeric_limits<double>::max();
	double tempLength;
	double avgLength = 0.0;
	std::cout << "begin to subdibidSphere function" << std::endl;
	std::cout << "origin grid size is " << grid.size() << std::endl;
	std::cout << "origin ctria3 size is " << ctria3.size() << std::endl;
	std::cout << "origin ctetra size is" << ctetra.size() << std::endl;
	Line tempLine;
	std::map<Line, size_t>::iterator pos;
	for(size_t i = 0; i < ctria3.size(); ++i)
	{
		Vertex midV1, midV2, midV3;
		//int midV1No, midV2No, midV3No;
		/////////////////////////////////////////////////////////////////////////////////////
		//first edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v2);
		tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v2);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV1.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV1.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV1.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			tempLength = sqrt(midV1.x*midV1.x + midV1.y*midV1.y + midV1.z*midV1.z);
			midV1.x *= radius / tempLength;
			midV1.y *= radius / tempLength;
			midV1.z *= radius / tempLength;
			newgrid.push_back(midV1);
			midV1.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			tempLength = lengthOfCBar(tempLine, grid) / 2;
			avgLength += tempLength*2;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);
		}
		else
		{
			midV1.x = newgrid[pos->second-1].x;
			midV1.y = newgrid[pos->second-1].y;
			midV1.z = newgrid[pos->second-1].z;
			midV1.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//second edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v2, ctria3[i].v3);
		tempLine.v2 = std::max(ctria3[i].v2, ctria3[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV2.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV2.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV2.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			tempLength = sqrt(midV2.x*midV2.x + midV2.y*midV2.y + midV2.z*midV2.z);
			midV2.x *= radius / tempLength;
			midV2.y *= radius / tempLength;
			midV2.z *= radius / tempLength;
			newgrid.push_back(midV2);
			midV2.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			tempLength = lengthOfCBar(tempLine, grid) / 2;
			avgLength += tempLength*2;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);
		}
		else
		{
			midV2.x = newgrid[pos->second-1].x;
			midV2.y = newgrid[pos->second-1].y;
			midV2.z = newgrid[pos->second-1].z;
			midV2.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//third edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v3);
		tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV3.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV3.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV3.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			tempLength = sqrt(midV3.x*midV3.x + midV3.y*midV3.y + midV3.z*midV3.z);
			midV3.x *= radius / tempLength;
			midV3.y *= radius / tempLength;
			midV3.z *= radius / tempLength;
			newgrid.push_back(midV3);
			midV3.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
			tempLength = lengthOfCBar(tempLine, grid) / 2.0;
			avgLength += tempLength*2;
			lengthMax = std::max(tempLength, lengthMax);
			lengthMin = std::min(tempLength, lengthMin);
		}
		else
		{
			midV3.x = newgrid[pos->second-1].x;
			midV3.y = newgrid[pos->second-1].y;
			midV3.z = newgrid[pos->second-1].z;
			midV3.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//construct new triangle
		/////////////////////////////////////////////////////////////////////////////////////
		Face tempFace;
		tempFace.v1 = ctria3[i].v1;
		tempFace.v2 = midV1.No;
		tempFace.v3 = midV3.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = midV1.No;
		tempFace.v2 = ctria3[i].v2;
		tempFace.v3 = midV2.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = midV1.No;
		tempFace.v2 = midV2.No;
		tempFace.v3 = midV3.No;
		newctria3.push_back(tempFace);
		tempFace.v1 = midV3.No;
		tempFace.v2 = midV2.No;
		tempFace.v3 = ctria3[i].v3;
		newctria3.push_back(tempFace);
	}

	for(size_t i = 0; i < ctetra.size(); ++i)
	{
		Vertex midV1, midV2, midV3, midV4, midV5, midV6;
		/////////////////////////////////////////////////////////////////////////////////////
		//first edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctetra[i].v1, ctetra[i].v2);
		tempLine.v2 = std::max(ctetra[i].v1, ctetra[i].v2);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV1.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV1.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV1.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			newgrid.push_back(midV1);
			midV1.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
		}
		else
		{
			midV1.x = newgrid[pos->second-1].x;
			midV1.y = newgrid[pos->second-1].y;
			midV1.z = newgrid[pos->second-1].z;
			midV1.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//second edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctetra[i].v1, ctetra[i].v3);
		tempLine.v2 = std::max(ctetra[i].v1, ctetra[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV2.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV2.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV2.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			newgrid.push_back(midV2);
			midV2.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
		}
		else
		{
			midV2.x = newgrid[pos->second-1].x;
			midV2.y = newgrid[pos->second-1].y;
			midV2.z = newgrid[pos->second-1].z;
			midV2.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//third edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctetra[i].v1, ctetra[i].v4);
		tempLine.v2 = std::max(ctetra[i].v1, ctetra[i].v4);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV3.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV3.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV3.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			newgrid.push_back(midV3);
			midV3.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
		}
		else
		{
			midV3.x = newgrid[pos->second-1].x;
			midV3.y = newgrid[pos->second-1].y;
			midV3.z = newgrid[pos->second-1].z;
			midV3.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//fourth edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctetra[i].v2, ctetra[i].v3);
		tempLine.v2 = std::max(ctetra[i].v2, ctetra[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV4.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV4.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV4.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			newgrid.push_back(midV4);
			midV4.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
		}
		else
		{
			midV4.x = newgrid[pos->second-1].x;
			midV4.y = newgrid[pos->second-1].y;
			midV4.z = newgrid[pos->second-1].z;
			midV4.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//fifth edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctetra[i].v2, ctetra[i].v4);
		tempLine.v2 = std::max(ctetra[i].v2, ctetra[i].v4);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV5.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV5.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV5.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			newgrid.push_back(midV5);
			midV5.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
		}
		else
		{
			midV5.x = newgrid[pos->second-1].x;
			midV5.y = newgrid[pos->second-1].y;
			midV5.z = newgrid[pos->second-1].z;
			midV5.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//sixth edge
		/////////////////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctetra[i].v3, ctetra[i].v4);
		tempLine.v2 = std::max(ctetra[i].v3, ctetra[i].v4);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			midV6.x = (grid[tempLine.v1-1].x + grid[tempLine.v2-1].x) / 2.0;
			midV6.y = (grid[tempLine.v1-1].y + grid[tempLine.v2-1].y) / 2.0;
			midV6.z = (grid[tempLine.v1-1].z + grid[tempLine.v2-1].z) / 2.0;
			newgrid.push_back(midV6);
			midV6.No = newgrid.size();
			cbarTest.insert(std::make_pair(tempLine, newgrid.size()));
		}
		else
		{
			midV6.x = newgrid[pos->second-1].x;
			midV6.y = newgrid[pos->second-1].y;
			midV6.z = newgrid[pos->second-1].z;
			midV6.No = pos->second;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		//construct new eight tet
		/////////////////////////////////////////////////////////////////////////////////////
		Tet tempTet;
		//first tet
		tempTet.v1 = ctetra[i].v1;
		tempTet.v2 = midV1.No;
		tempTet.v3 = midV2.No;
		tempTet.v4 = midV3.No;
		newctetra.push_back(tempTet);
		//second tet
		tempTet.v1 = ctetra[i].v2;
		tempTet.v2 = midV4.No;
		tempTet.v3 = midV1.No;
		tempTet.v4 = midV5.No;
		newctetra.push_back(tempTet);
		//third tet
		tempTet.v1 = ctetra[i].v3;
		tempTet.v2 = midV4.No;
		tempTet.v3 = midV6.No;
		tempTet.v4 = midV2.No;
		newctetra.push_back(tempTet);
		//fourth tet
		tempTet.v1 = ctetra[i].v4;
		tempTet.v2 = midV3.No;
		tempTet.v3 = midV6.No;
		tempTet.v4 = midV5.No;
		newctetra.push_back(tempTet);
		//fifth tet
		tempTet.v1 = midV2.No;
		tempTet.v2 = midV4.No;
		tempTet.v3 = midV6.No;
		tempTet.v4 = midV1.No;
		newctetra.push_back(tempTet);
		//sixth tet
		tempTet.v1 = midV2.No;
		tempTet.v2 = midV1.No;
		tempTet.v3 = midV6.No;
		tempTet.v4 = midV3.No;
		newctetra.push_back(tempTet);
		//seven tet
		tempTet.v1 = midV5.No;
		tempTet.v2 = midV4.No;
		tempTet.v3 = midV1.No;
		tempTet.v4 = midV6.No;
		newctetra.push_back(tempTet);
		//eight tet
		tempTet.v1 = midV5.No;
		tempTet.v2 = midV1.No;
		tempTet.v3 = midV3.No;
		tempTet.v4 = midV6.No;
		newctetra.push_back(tempTet);
	}

	std::cout << "length Max = " << lengthMax << std::endl;
	std::cout << "length Min = " << lengthMin << std::endl;
	std::cout << "new grid size = " << newgrid.size() << std::endl;
	std::cout << "new ctria size = " << newctria3.size() << std::endl;
	std::cout << "new ctetra size = " << newctetra.size() << std::endl;
	std::cout << "end of subdibidSphere function" << std::endl;
}

void avgTet(const std::vector<Vertex>& grid, const std::vector<Tet>& ctetra)
{
	double avg = 0.0;
	double lengthMax = std::numeric_limits<double>::min();
	double lengthMin = std::numeric_limits<double>::max();
	for(size_t i = 0; i < ctetra.size(); ++i)
	{
		Line tempLine;
		double l;
		tempLine.v1 = ctetra[i].v1;
		tempLine.v2 = ctetra[i].v2;
		l = lengthOfCBar(tempLine, grid);
		/*if(l < ZERO)
			int tt = 1;*/
		lengthMax = std::max(l, lengthMax);
		lengthMin = std::min(l, lengthMin);
		avg += l;
		tempLine.v2 = ctetra[i].v3;
		l = lengthOfCBar(tempLine, grid);
		/*if(l < ZERO)
			int tt = 1;*/
		lengthMax = std::max(l, lengthMax);
		lengthMin = std::min(l, lengthMin);
		avg += l;
		tempLine.v2 = ctetra[i].v4;
		l = lengthOfCBar(tempLine, grid);
		/*if(l < ZERO)
			int tt = 1;*/
		lengthMax = std::max(l, lengthMax);
		lengthMin = std::min(l, lengthMin);
		avg += l;
		tempLine.v1 = ctetra[i].v2;
		tempLine.v2 = ctetra[i].v3;
		l = lengthOfCBar(tempLine, grid);
		/*if(l < ZERO)
			int tt = 1;*/
		lengthMax = std::max(l, lengthMax);
		lengthMin = std::min(l, lengthMin);
		avg += l;
		tempLine.v2 = ctetra[i].v4;
		l = lengthOfCBar(tempLine, grid);
		/*if(l < ZERO)
			int tt = 1;*/
		lengthMax = std::max(l, lengthMax);
		lengthMin = std::min(l, lengthMin);
		avg += l;
		tempLine.v1 = ctetra[i].v3;
		tempLine.v2 = ctetra[i].v4;
		l = lengthOfCBar(tempLine, grid);
		/*if(l < ZERO)
			int tt = 1;*/
		lengthMax = std::max(l, lengthMax);
		lengthMin = std::min(l, lengthMin);
		avg += l;
	}
	avg /= (6 * ctetra.size());
	std::cout << "max tet edge length = " << lengthMax << std::endl;
	std::cout << "min tet edge length = " << lengthMin << std::endl;
	std::cout << "avg tet length = " << avg  << std::endl;

}
#endif