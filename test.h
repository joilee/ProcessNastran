#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
struct Vertex
{
	double x;
	double y;
	double z;
	int No;
	bool operator < (const Vertex& v) const
	{
		if(z < v.z)
			return true;
		else
		{
			if(z == v.z && x < v.x)
				return true;
			else
			{
				if(z == v.z && x == v.x && y < v.y)
					return true;
			}
		}
		return false;
	}
};

struct Line
{
	size_t v1;
	size_t v2;
	bool operator < (const Line& b) const
	{
		if(v1 < b.v1)
			return true;
		else
		{
			if(v1 == b.v1  && v2 < b.v2)
				return true;
			else
				return false;
		}
	}
};

struct Face
{
	size_t v1;
	size_t v2;
	size_t v3;
};

struct Quad
{
	size_t v1;
	size_t v2;
	size_t v3;
	size_t v4;
};

struct Tet
{
	size_t v1;
	size_t v2;
	size_t v3;
	size_t v4;
};

const double ZERO = 1e-16;
//std::map<Line, int> cbarTest;
//std::vector<Vertex> grid;
//std::vector<Face> ctria3;
//std::vector<Quad> cquad4;




/*
void writeJson(FILE *fp)
{
	int _index = 1;
	int _tag = 0;
	for(unsigned int i = 0; i < grid.size(); ++i)
	{
		if(i != grid.size()-1)
			fprintf(fp, "%.2lf ", grid[i].x);
		else
			fprintf(fp, "%.2lf\n", grid[i].x);
	}
	for(unsigned int i = 0; i < grid.size(); ++i)
	{
		if(i != grid.size()-1)
			fprintf(fp, "%.2lf ", grid[i].y);
		else
			fprintf(fp, "%.2lf\n", grid[i].y);
	}
	for(unsigned int i = 0; i < grid.size(); ++i)
	{
		if(i != grid.size()-1)
			fprintf(fp, "%.2lf ", grid[i].z);
		else
			fprintf(fp, "%.2lf\n", grid[i].z);
	}
}
*/
/*
bool Scale(double sx, double sy, double sz)
{
	for(int i = 0; i < grid.size(); ++i)
	{
		grid[i].x *= sx;
		grid[i].y *= sy;
		grid[i].z *= sz;
	}
	return true;
}

bool Move(double mx, double my, double mz)
{
	for(int i = 0; i < grid.size(); ++i)
	{
		grid[i].x += mx;
		grid[i].y += my;
		grid[i].z += mz;
	}
	return 0;
}

bool Translation(double tx, double ty, double tz)
{
	for(int i = 0; i < grid.size(); ++i)
	{
		grid[i].x += tx;
		grid[i].y += ty;
		grid[i].z += tz;
	}
	return true;
}
*/
//void toQuad()
//{
//	std::cout << "BEGIN:" << std::endl;
//	readNas("C:\\Users\\Administrator\\Desktop\\model\\t1.nas");
//	std::cout << "grid size is " << grid.size() << std::endl;
//	std::cout << "ctria3 size is " << ctria3.size() << std::endl;
//
//	Vertex tempVertex1;
//	Vertex tempVertex2;
//	Vertex tempVertex3;
//	Vertex tempVertex4;
//	Vertex tempVertex5;
//	Vertex tempVertex6;
//	Vertex tempVertex7;
//	Quad tempQuad;
//	int vertexIndex = grid.size();
//	int vertexIndex1;
//	int vertexIndex2;
//	int vertexIndex3;
//	int vertexIndex4;
//	int vertexIndex5;
//	int vertexIndex6;
//	int vertexIndex7;
//	Line tempLine;
//	for(int i = 0; i < ctria3.size(); ++i)
//	{
//		tempVertex7.x =(grid[ctria3[i].v1-1].x + grid[ctria3[i].v2-1].x + grid[ctria3[i].v3-1].x) / 3.0;
//		tempVertex7.y =(grid[ctria3[i].v1-1].y + grid[ctria3[i].v2-1].y + grid[ctria3[i].v3-1].y) / 3.0;
//		tempVertex7.z =(grid[ctria3[i].v1-1].z + grid[ctria3[i].v2-1].z + grid[ctria3[i].v3-1].z) / 3.0;
//		grid.push_back(tempVertex7);
//		++vertexIndex;
//		vertexIndex7 = vertexIndex;
//		
//		//////////////////////////////////////////////////////////////////////////////////////
//		std::map<Line, int>::iterator pos;
//		tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v2);
//		tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v2);
//		pos = cbarTest.find(tempLine);
//		if(pos != cbarTest.end())
//		{
//			tempVertex4.x = grid[pos->second-1].x;
//			tempVertex4.y = grid[pos->second-1].y;
//			tempVertex4.z = grid[pos->second-1].z;
//			vertexIndex4 = pos->second;
//		}
//		else
//		{
//			tempVertex4.x = (grid[ctria3[i].v1-1].x + grid[ctria3[i].v2-1].x) / 2.0;
//			tempVertex4.y = (grid[ctria3[i].v1-1].y + grid[ctria3[i].v2-1].y) / 2.0;
//			tempVertex4.z = (grid[ctria3[i].v1-1].z + grid[ctria3[i].v2-1].z) / 2.0;
//			grid.push_back(tempVertex4);
//			++vertexIndex;
//			vertexIndex4 = vertexIndex;
//			cbarTest.insert(std::make_pair(tempLine, vertexIndex4));
//		}
//		///////////////////////////////////////////////////////////////////////////////////////
//		tempLine.v1 = std::min(ctria3[i].v3, ctria3[i].v2);
//		tempLine.v2 = std::max(ctria3[i].v3, ctria3[i].v2);
//		pos = cbarTest.find(tempLine);
//		if(pos != cbarTest.end())
//		{
//			tempVertex5.x = grid[pos->second-1].x;
//			tempVertex5.y = grid[pos->second-1].y;
//			tempVertex5.z = grid[pos->second-1].z;
//			vertexIndex5 = pos->second;
//		}
//		else
//		{
//			tempVertex5.x = (grid[ctria3[i].v3-1].x + grid[ctria3[i].v2-1].x) / 2.0;
//			tempVertex5.y = (grid[ctria3[i].v3-1].y + grid[ctria3[i].v2-1].y) / 2.0;
//			tempVertex5.z = (grid[ctria3[i].v3-1].z + grid[ctria3[i].v2-1].z) / 2.0;
//			grid.push_back(tempVertex5);
//			++vertexIndex;
//			vertexIndex5 = vertexIndex;
//			cbarTest.insert(std::make_pair(tempLine, vertexIndex5));
//		}
//		///////////////////////////////////////////////////////////////////////////////////////
//		tempLine.v1 = std::min(ctria3[i].v3, ctria3[i].v1);
//		tempLine.v2 = std::max(ctria3[i].v3, ctria3[i].v1);
//		pos = cbarTest.find(tempLine);
//		if(pos != cbarTest.end())
//		{
//			tempVertex6.x = grid[pos->second-1].x;
//			tempVertex6.y = grid[pos->second-1].y;
//			tempVertex6.z = grid[pos->second-1].z;
//			vertexIndex6 = pos->second;
//		}
//		else
//		{
//			tempVertex6.x = (grid[ctria3[i].v3-1].x + grid[ctria3[i].v1-1].x) / 2.0;
//			tempVertex6.y = (grid[ctria3[i].v3-1].y + grid[ctria3[i].v1-1].y) / 2.0;
//			tempVertex6.z = (grid[ctria3[i].v3-1].z + grid[ctria3[i].v1-1].z) / 2.0;
//			grid.push_back(tempVertex6);
//			++vertexIndex;
//			vertexIndex6 = vertexIndex;
//			cbarTest.insert(std::make_pair(tempLine, vertexIndex6));
//		}
//		///////////////////////////////////////////////////////////////////////////////////////
//
//		///////////////////////////////////////////////////////////////////////////////////////
//		tempQuad.v1 = ctria3[i].v1;
//		tempQuad.v2 = vertexIndex4;
//		tempQuad.v3 = vertexIndex7;
//		tempQuad.v4 = vertexIndex6;
//		cquad4.push_back(tempQuad);
//		tempQuad.v1 = vertexIndex4;
//		tempQuad.v2 = ctria3[i].v2;
//		tempQuad.v3 = vertexIndex5;
//		tempQuad.v4 = vertexIndex7;
//		cquad4.push_back(tempQuad);
//		tempQuad.v1 = vertexIndex6;
//		tempQuad.v2 = vertexIndex7;
//		tempQuad.v3 = vertexIndex5;
//		tempQuad.v4 = ctria3[i].v3;
//		cquad4.push_back(tempQuad);
//	}
//	ctria3.clear();
//
//	FILE *fp = fopen("C:\\Users\\Administrator\\Desktop\\model\\y8_0_05_new.nas", "w");
//	if(!fp)
//	{
//		std::cout << "Unable to open file" << std::endl;
//		return ;
//	}
//	writeNas(fp);
//	fclose(fp);
//	std::cout << "quad size is " << cquad4.size() << std::endl;
//	std::cout << "END;" << std::endl;
//	getchar();
//}


/*
void rate_Quad_Face_Edge()
{
	double lengthMax = std::numeric_limits<double>::min();
	double lengthMin = std::numeric_limits<double>::max();
	double tempLength;
	double sumLength = 0.0;
	std::cout << "BEGIN:" << std::endl;
	readNas("C:\\Users\\Administrator\\Desktop\\model\\y8(changed)_de_quad_0_1.nas");
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
			tempLength = lengthOfCBar(tempLine);
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
			tempLength = lengthOfCBar(tempLine);
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
			tempLength = lengthOfCBar(tempLine);
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
			tempLength = lengthOfCBar(tempLine);
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


//void antenna1618()
//{
//	Vertex v1, v2;
//	v1.x = 17.5;
//	v1.y = 6.5;
//	v1.z = 1.0;
//	v2.x = 17.5;
//	v2.y = 7.5;
//	v2.z = 1.0;
//	Vertex tempV1, tempV2;
//	for(int i = 0; i < 18; ++i)
//	{
//		for(int j = 0; j < 16; ++j)
//		{
//			tempV1.x = v1.x + j * 46;
//			tempV1.y = v1.y + i * 65;
//			tempV1.z = v1.z;
//			tempV2.x = v2.x + j * 46;
//			tempV2.y = v2.y + i * 65;
//			tempV2.z = v2.z;
//			grid.push_back(tempV1);
//			grid.push_back(tempV2);
//		}
//	}
//	FILE *fp = fopen("C:\\Users\\Administrator\\Desktop\\model\\Point1618.nas", "w");
//	if(!fp)
//	{
//		std::cout << "Unable to open file" << std::endl;
//		return ;
//	}
//	writeNas(fp);
//	fclose(fp);
//	std::cout << "grid size is " << grid.size() << std::endl;
//	std::cout << "END;" << std::endl;
//	getchar();
//}

bool gridCompare(const Vertex& a, const Vertex& b)
{
	if(a.x > b.x)
		return true;
	else if (a.x == b.x)
	{
		if(a.y > b.y)
			return true;
		else if(a.y == b.y)
		{
			if(a.z > b.z)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

void removeRepeatVertex()
{

}

void removeRepeatFace()
{

}

void zy2014_12_15()
{
	readNas("C:\\Users\\Administrator\\Desktop\\model\\full.nas");
	double minZ = std::numeric_limits<double>::max();
	double minZ1 = 0., minZ2 = 0., minZ3 = 0.;
	for(int i = 0;i < ctria3.size(); ++i)
	{
		double z1 = grid[ctria3[i].v1-1].z;
		double z2 = grid[ctria3[i].v2-1].z;
		double z3 = grid[ctria3[i].v3-1].z;

		if((z1 >= -1.0 && z1 <= 0.0) || (z2 >= -1.0 && z2 <= 0.0) || (z3 >= -1.0 && z3 <= 0.0))
		{
			if(minZ > (z1+z2+z3))
			{
				minZ = z1 + z2 + z3;
				minZ1 = z1;
				minZ2 = z2;
				minZ3 = z3;
			}
			int temp = ctria3[i].v1;
			ctria3[i].v1 = ctria3[i].v3;
			ctria3[i].v3 = temp;
		}
	}
	std::cout << minZ1 << std::endl;
	std::cout << minZ2 << std::endl;
	std::cout << minZ3 << std::endl;
	writeNas("C:\\Users\\Administrator\\Desktop\\model\\1618_a1.nas");
}

void zy2014_12_16()
{
	std::vector<Vertex> tempV;
	Vertex maxXV, maxYV, maxZV;
	double lengthMax = std::numeric_limits<double>::min();
	double lengthMin = std::numeric_limits<double>::max();
	double tempLength;
	std::cout << "BEGIN:" << std::endl;
	readNas("C:\\Users\\Administrator\\Desktop\\model\\1618_a1.nas");
	Line tempLine;
	for(int i = 0; i < ctria3.size(); ++i)
	{
		std::map<Line, int>::iterator pos;
		tempLine.v1 = std::min(ctria3[i].v1, ctria3[i].v2);
		tempLine.v2 = std::max(ctria3[i].v1, ctria3[i].v2);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			cbarTest.insert(std::make_pair(tempLine, 0));
			if(grid[tempLine.v1-1].z == 1 && grid[tempLine.v2-1].z ==1)
			{
				tempV.push_back(grid[tempLine.v1-1]);
				tempV.push_back(grid[tempLine.v2-1]);
			}
		}
		///////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v2, ctria3[i].v3);
		tempLine.v2 = std::max(ctria3[i].v2, ctria3[i].v3);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			cbarTest.insert(std::make_pair(tempLine, 0));
			if(grid[tempLine.v1-1].z == 1 && grid[tempLine.v2-1].z ==1)
			{
				tempV.push_back(grid[tempLine.v1-1]);
				tempV.push_back(grid[tempLine.v2-1]);
			}
		}
		////////////////////////////////////////////////////////////////////////
		tempLine.v1 = std::min(ctria3[i].v3, ctria3[i].v1);
		tempLine.v2 = std::max(ctria3[i].v3, ctria3[i].v1);
		pos = cbarTest.find(tempLine);
		if(pos == cbarTest.end())
		{
			cbarTest.insert(std::make_pair(tempLine, 0));
			if(grid[tempLine.v1-1].z == 1 && grid[tempLine.v2-1].z ==1)
			{
				tempV.push_back(grid[tempLine.v1-1]);
				tempV.push_back(grid[tempLine.v2-1]);
			}
		}
	}
	std::cout << tempV.size() << std::endl;
	
	FILE *fp = fopen("C:\\Users\\Administrator\\Desktop\\model\\1618.txt", "w");
	if(!fp)
	{
		std::cout << "Unable to open file "  << std::endl;
		return;
	}
	for(unsigned int i = 0; i < tempV.size(); ++i)
	{
		if(i != tempV.size()-1)
			fprintf(fp, "%.2lf ", tempV[i].x);
		else
			fprintf(fp, "%.2lf\n", tempV[i].x);
	}
	for(unsigned int i = 0; i < tempV.size(); ++i)
	{
		if(i != tempV.size()-1)
			fprintf(fp, "%.2lf ", tempV[i].y);
		else
			fprintf(fp, "%.2lf\n", tempV[i].y);
	}
	for(unsigned int i = 0; i < tempV.size(); ++i)
	{
		if(i != tempV.size()-1)
			fprintf(fp, "%.2lf ", tempV[i].z);
		else
			fprintf(fp, "%.2lf\n", tempV[i].z);
	}
	fclose(fp);
}
*/
#endif

