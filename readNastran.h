#ifndef _READ_NASTRAN_
#define _READ_NASTRAN_

#include "test.h"
std::vector<Face> narrowTriangle;
int getFormatNas(char *buffer, int &keySize)
{
	if(buffer[keySize] == '*'){ keySize++; return 2; }
	for(unsigned int i = 0; i < strlen(buffer); i++)
		if(buffer[i] == ',') return 0; 
	return 1;
}

double atofNas(char *str)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++){
		if(str[i] == 'E' || str[i] == 'e') {
			return atof(str);
		}
		else if(str[i] == 'D' || str[i] == 'd'){
			str[i] = 'E';
			return atof(str);
		}
	}
	char tmp[32];
	int j = 0, leading_minus = 1;
	for(int i = 0; i < len; i++){
		if(leading_minus && str[i] != ' '  && str[i] != '-') leading_minus = 0;
		if(!leading_minus && str[i] == '-') tmp[j++] = 'E';
		if(str[i] == '+') tmp[j++] = 'E';
		tmp[j++] = str[i];
	}
	tmp[j] = '\0';
	return atof(tmp);
}

bool emptyFieldNas(char *field, int length)
{
	for(int i = 0; i < length; i++)
		if(field[i] != '\0' && field[i] != ' ' && field[i] != '\n' && field[i] != '\r')
			return false;
	return true;
}

void readLineNas(char *buffer, int format, std::vector<char*> &fields)
{
	int cmax = (format == 2) ? 16 : 8;
	int nmax = (format == 2) ? 4 : 8;

	if(format == 0){
		for(unsigned int i = 0; i < strlen(buffer); i++){
			if(buffer[i] == ',') fields.push_back(&buffer[i + 1]);
		}
	}
	else{
		for(int i = 0; i < nmax + 1; i++){
			if(!emptyFieldNas(&buffer[8 + cmax * i], cmax))
				fields.push_back(&buffer[8 + cmax * i]);
		}
	}
}

int readVertexNas(FILE *fp, char *buffer, int keySize,
	int *num, double *x, double *y, double *z)
{
	char tmp[5][32];
	int j = keySize;

	switch(getFormatNas(buffer, keySize)){
	case 0:
		for(int i = 0; i < 5; i++){
			tmp[i][16] = '\0';
			strncpy(tmp[i], &buffer[j + 1], 16);
			for(int k = 0; k < 16; k++){ if(tmp[i][k] == ',') tmp[i][k] = '\0'; }
			j++;
			while(j < (int)strlen(buffer) && buffer[j] != ',') j++;
		}
		break;
	case 1:
		for(int i = 0; i < 5; i++) tmp[i][8] = '\0';
		strncpy(tmp[0], &buffer[8], 8);
		strncpy(tmp[2], &buffer[24], 8);
		strncpy(tmp[3], &buffer[32], 8);
		strncpy(tmp[4], &buffer[40], 8);
		break;
	case 2:
		for(int i = 0; i < 5; i++) tmp[i][16] = '\0';
		strncpy(tmp[0], &buffer[8], 16);
		strncpy(tmp[2], &buffer[40], 16);
		strncpy(tmp[3], &buffer[56], 16);
		char buffer2[256];
		for(unsigned int i = 0; i < sizeof(buffer2); i++) buffer2[i] = '\0';
		if(!fgets(buffer2, sizeof(buffer2), fp)) return 0;
		strncpy(tmp[4], &buffer2[8], 16);
		break;
	}

	*num = atoi(tmp[0]);
	*x = atofNas(tmp[2]);
	*y = atofNas(tmp[3]);
	*z = atofNas(tmp[4]);
	return 1;
}

int readElementNas(FILE *fp, char *buffer, int keySize, int numVertices,
	int &num, int &region, Face &vertices,
	std::vector<Vertex> &vertexMap)
{
	static int count = 0;
	++count;
	char buffer2[256], buffer3[256];
	std::vector<char*> fields;
	int format = getFormatNas(buffer, keySize);

	for(unsigned int i = 0; i < sizeof(buffer2); i++) 
		buffer2[i] = buffer3[i] = '\0';

	readLineNas(buffer, format, fields);

	if(((int)fields.size() - 2 < abs(numVertices)) ||
		(numVertices < 0 && (fields.size() == 9))){
			if(fields.size() == 9) fields.pop_back();
			if(!fgets(buffer2, sizeof(buffer2), fp)) return 0;
			readLineNas(buffer2, format, fields);
	}

	if(((int)fields.size() - 2 < abs(numVertices)) ||
		(numVertices < 0 && (fields.size() == 17))){
			if(fields.size() == 17) fields.pop_back();
			if(!fgets(buffer3, sizeof(buffer3), fp)) return 0;
			readLineNas(buffer3, format, fields);
	}

	if((int)fields.size() - 2 < abs(numVertices)){
		std::cout << "Wrong number of vertices" << fields.size() - 2  << std::endl;
		return 0;
	}

	int n[30], cmax = (format == 2) ? 16 : 8;
	char tmp[32];
	tmp[cmax] = '\0';
	strncpy(tmp, fields[0], cmax); 
	num = atoi(tmp);
	strncpy(tmp, fields[1], cmax); 
	region = atoi(tmp);
	for(unsigned int i = 2; i < fields.size(); i++)
	{
		strncpy(tmp, fields[i], cmax); n[i - 2] = atoi(tmp);
	}

	int numCheck = (numVertices > 0) ? numVertices : fields.size() - 2;

	if(numCheck == 3 && n[0] <= vertexMap.size() && n[1] <= vertexMap.size() && n[2] <= vertexMap.size())
	{
	vertices.v1 = n[0];
	vertices.v2 = n[1];
	vertices.v3 = n[2];
	}
	//if(numCheck == 4 && n[0] <= vertexMap.size() && n[1] <= vertexMap.size() && n[2] <= vertexMap.size() && n[3] <= vertexMap.size())
	//{
	//	vertices.v1 = n[0];
	//	vertices.v2 = n[1];
	//	vertices.v3 = n[2];
	//	vertices.v4 = n[3];
	//}
	//else
	//{
	//	std::cout << "n[0] = " << n[0] << std::endl;
	//	std::cout << "n[1] = " << n[1] << std::endl;
	//	std::cout << "n[2] = " << n[2] << std::endl;
	//	std::cout << "num = " << num << std::endl;
	//	std::cout << "regeion = " << region << std::endl;
	//	std::cout << "Wrong vertex index " << count << std::endl;
	//	return 0;
	//}
	return 1;
}

int readElementNasQuad(FILE *fp, char *buffer, int keySize, int numVertices,
	int &num, int &region, Quad &vertices,
	std::vector<Vertex> &vertexMap)
{
	static int count = 0;
	++count;
	char buffer2[256], buffer3[256];
	std::vector<char*> fields;
	int format = getFormatNas(buffer, keySize);

	for(unsigned int i = 0; i < sizeof(buffer2); i++) 
		buffer2[i] = buffer3[i] = '\0';

	readLineNas(buffer, format, fields);

	if(((int)fields.size() - 2 < abs(numVertices)) ||
		(numVertices < 0 && (fields.size() == 9))){
			if(fields.size() == 9) fields.pop_back();
			if(!fgets(buffer2, sizeof(buffer2), fp)) return 0;
			readLineNas(buffer2, format, fields);
	}

	if(((int)fields.size() - 2 < abs(numVertices)) ||
		(numVertices < 0 && (fields.size() == 17))){
			if(fields.size() == 17) fields.pop_back();
			if(!fgets(buffer3, sizeof(buffer3), fp)) return 0;
			readLineNas(buffer3, format, fields);
	}

	if((int)fields.size() - 2 < abs(numVertices)){
		std::cout << "Wrong number of vertices" << fields.size() - 2  << std::endl;
		return 0;
	}

	int n[30], cmax = (format == 2) ? 16 : 8;
	char tmp[32];
	tmp[cmax] = '\0';
	strncpy(tmp, fields[0], cmax); 
	num = atoi(tmp);
	strncpy(tmp, fields[1], cmax); 
	region = atoi(tmp);
	for(unsigned int i = 2; i < fields.size(); i++)
	{
		strncpy(tmp, fields[i], cmax); n[i - 2] = atoi(tmp);
	}

	int numCheck = (numVertices > 0) ? numVertices : fields.size() - 2;

	//if(numCheck == 3 && n[0] <= vertexMap.size() && n[1] <= vertexMap.size() && n[2] <= vertexMap.size())
	//{
	//	vertices.v1 = n[0];
	//	vertices.v2 = n[1];
	//	vertices.v3 = n[2];
	//}
	if(numCheck == 4 && n[0] <= vertexMap.size() && n[1] <= vertexMap.size() && n[2] <= vertexMap.size() && n[3] <= vertexMap.size())
	{
		vertices.v1 = n[0];
		vertices.v2 = n[1];
		vertices.v3 = n[2];
		vertices.v4 = n[3];
	}
	else
	{
		std::cout << "n[0] = " << n[0] << std::endl;
		std::cout << "n[1] = " << n[1] << std::endl;
		std::cout << "n[2] = " << n[2] << std::endl;
		std::cout << "num = " << num << std::endl;
		std::cout << "regeion = " << region << std::endl;
		std::cout << "Wrong vertex index " << count << std::endl;
		return 0;
	}
	return 1;
}


int readElementNasTet(FILE *fp, char *buffer, int keySize, int numVertices,
	int &num, int &region, Tet &vertices,
	std::vector<Vertex> &vertexMap)
{
	static int count = 0;
	++count;
	char buffer2[256], buffer3[256];
	std::vector<char*> fields;
	int format = getFormatNas(buffer, keySize);

	for(unsigned int i = 0; i < sizeof(buffer2); i++) 
		buffer2[i] = buffer3[i] = '\0';

	readLineNas(buffer, format, fields);

	if(((int)fields.size() - 2 < abs(numVertices)) ||
		(numVertices < 0 && (fields.size() == 9))){
			if(fields.size() == 9) fields.pop_back();
			if(!fgets(buffer2, sizeof(buffer2), fp)) return 0;
			readLineNas(buffer2, format, fields);
	}

	if(((int)fields.size() - 2 < abs(numVertices)) ||
		(numVertices < 0 && (fields.size() == 17))){
			if(fields.size() == 17) fields.pop_back();
			if(!fgets(buffer3, sizeof(buffer3), fp)) return 0;
			readLineNas(buffer3, format, fields);
	}

	if((int)fields.size() - 2 < abs(numVertices)){
		std::cout << "Wrong number of vertices" << fields.size() - 2  << std::endl;
		return 0;
	}

	int n[30], cmax = (format == 2) ? 16 : 8;
	char tmp[32];
	tmp[cmax] = '\0';
	strncpy(tmp, fields[0], cmax); 
	num = atoi(tmp);
	strncpy(tmp, fields[1], cmax); 
	region = atoi(tmp);
	for(unsigned int i = 2; i < fields.size(); i++)
	{
		strncpy(tmp, fields[i], cmax); n[i - 2] = atoi(tmp);
	}

	int numCheck = (numVertices > 0) ? numVertices : fields.size() - 2;

	//if(numCheck == 3 && n[0] <= vertexMap.size() && n[1] <= vertexMap.size() && n[2] <= vertexMap.size())
	//{
	//	vertices.v1 = n[0];
	//	vertices.v2 = n[1];
	//	vertices.v3 = n[2];
	//}
	if(numCheck == 4 && n[0] <= vertexMap.size() && n[1] <= vertexMap.size() && n[2] <= vertexMap.size() && n[3] <= vertexMap.size())
	{
		vertices.v1 = n[0];
		vertices.v2 = n[1];
		vertices.v3 = n[2];
		vertices.v4 = n[3];
	}
	else
	{
		std::cout << "n[0] = " << n[0] << std::endl;
		std::cout << "n[1] = " << n[1] << std::endl;
		std::cout << "n[2] = " << n[2] << std::endl;
		std::cout << "num = " << num << std::endl;
		std::cout << "regeion = " << region << std::endl;
		std::cout << "Wrong vertex index " << count << std::endl;
		return 0;
	}
	return 1;
}

int readElementNasTetL(FILE *fp, char *buffer, int keySize, int numVertices,
	int &num, int &region,Tet &vertices, 
	std::vector<Vertex> &vertexMap)
{
	char tmp[6][32];
	int j = keySize;

	switch(getFormatNas(buffer, keySize)){
	case 2:
		for(int i = 0; i < 5; i++) tmp[i][16] = '\0';
		strncpy(tmp[0], &buffer[8], 16);
		strncpy(tmp[1], &buffer[24], 16);
		strncpy(tmp[2], &buffer[40], 16);
		strncpy(tmp[3], &buffer[56], 16);
		char buffer2[256];
		for(unsigned int i = 0; i < sizeof(buffer2); i++) buffer2[i] = '\0';
		if(!fgets(buffer2, sizeof(buffer2), fp)) return 0;
		strncpy(tmp[4], &buffer2[8], 16);
		strncpy(tmp[5], &buffer2[24], 16);
		break;
	}
	num = strtoul(tmp[0], 0, 10);
	region = strtoul(tmp[1], 0, 10);
	vertices.v1 = strtoul(tmp[2], 0, 10);
	vertices.v2 = strtoul(tmp[3], 0, 10);
	vertices.v3 = strtoul(tmp[4], 0, 10);
	vertices.v4 = strtoul(tmp[5], 0, 10);
	return 1;
}




int readNasL(const std::string &filename, std::vector<Vertex>& grid, std::vector<Face>& ctria3, std::vector<Quad>& cquad4, std::vector<Tet>& ctetra)
{
	int pre = 0;
	int cur;
	Vertex tempVertex;
	Face tempFace;
	Quad tempQuad;
	Tet tempTet;
	FILE *fp = fopen(filename.c_str(), "r");
	if(!fp)
	{
		std::cout << "Unable to open file " << filename.c_str() << std::endl;
		return 0;
	}
	char buffer[256];

	int count = 0;
	while(!feof(fp))
	{
		for(unsigned int i = 0; i < sizeof(buffer); ++i)
			buffer[i] = '\0';
		if(!fgets(buffer, sizeof(buffer), fp)) 
			break;
		if(!strncmp(buffer, "ENDDATA", 7))
			break;
		if(buffer[0] != '$')
		{
			if(!strncmp(buffer, "GRID", 4))
			{
				int num;
				double x, y, z;
				if(!readVertexNas(fp, buffer, 4, &num, &x, &y, &z)) 
					break;
				/*cur = num;
				if((cur - pre) != 1)
					std::cout << "error grid" << std::endl;
				pre = cur;*/
				tempVertex.x = x;
				tempVertex.y = y;
				tempVertex.z = z;
				tempVertex.No = num;
				if(num != grid.size()+1)
					int d = 1;
				grid.push_back(tempVertex);
			}
		}
	}
	rewind(fp);
	count = 0;
	pre = 0;
	while(!feof(fp))
	{
		for(unsigned int i = 0; i < sizeof(buffer); ++i)
			buffer[i] = '\0';
		if(!fgets(buffer, sizeof(buffer), fp)) break;
		if(buffer[0] != '$')
		{
			int num, region;
			if(!strncmp(buffer, "CTRIA3", 6))
			{
				readElementNas(fp, buffer, 6, 3, num, region, tempFace, grid);
			
				ctria3.push_back(tempFace);
			}
			else if(!strncmp(buffer, "CQUAD4", 6))
			{
				readElementNasQuad(fp, buffer, 6, 4, num, region, tempQuad, grid);
				cquad4.push_back(tempQuad);
			}
			else if(!strncmp(buffer, "CTETRA", 6))
			{
				if(readElementNasTetL(fp, buffer, 6, -4, num, region, tempTet, grid))
				{
					ctetra.push_back(tempTet);
				}
				else
					std::cout << "error" << std::endl;

			}
		}
	}
	fclose(fp);
	return 1;
}

int writeNas(const std::string &filename, const std::vector<Vertex>& grid, const std::vector<Face>& ctria3, const std::vector<Quad>& cquad4,
	const std::vector<Tet>& ctetra)
{
	FILE *fp = fopen(filename.c_str(), "w");
	if(!fp)
	{
		std::cout << "Unable to open file " << filename.c_str() << std::endl;
		return 0;
	}

	int _index = 1;
	int _tag = 0;
	for(unsigned int i = 0; i < grid.size(); ++i)
	{
		
		fprintf(fp, "GRID*   %-16d%-16d%-16.9G%-16.9G%-8s\n", _index, 0, grid[i].x, grid[i].y, "*");
		fprintf(fp, "%-8s%-16.9G\n", "*", grid[i].z);
		++_index;
	}
	_index = 1;

	for(unsigned int i = 0; i < ctria3.size(); ++i)
	{
	/*	if(i == 1755861 || i == 1755862)
			continue;*/
		fprintf(fp, "%-8s%-8d%-8d", "CTRIA3", _index, _tag);
		fprintf(fp, "%-8d%-8d%-8d\n", ctria3[i].v1, ctria3[i].v2, ctria3[i].v3 );
		++_index;
		//std::cout << _index << std::endl;
	}
	_index = 1;
	for(unsigned int i = 0; i < cquad4.size(); ++i)
	{
		fprintf(fp, "%-8s%-8d%-8d", "CQUAD4", _index, _tag);
		fprintf(fp, "%-8d%-8d%-8d%-8d\n", cquad4[i].v1, cquad4[i].v2, cquad4[i].v3, cquad4[i].v4 );
		++_index;
	}
	_index = 1;
	for(unsigned int i = 0; i < ctetra.size(); ++i)
	{
		fprintf(fp, "%-8s%-8d%-8d", "CTETRA", _index, _tag);
		fprintf(fp, "%-8d%-8d%-8d%-8d\n", ctetra[i].v1, ctetra[i].v2, ctetra[i].v3, ctetra[i].v4 );
		++_index;
	}
	fclose(fp);
	return 1;
}

int writeNasL(const std::string &filename, const std::vector<Vertex>& grid, const std::vector<Face>& ctria3, const std::vector<Quad>& cquad4,
	const std::vector<Tet>& ctetra)
{
	FILE *fp = fopen(filename.c_str(), "w");
	if(!fp)
	{
		std::cout << "Unable to open file " << filename.c_str() << std::endl;
		return 0;
	}

	size_t _index = 1;
	size_t _tag = 0;
	for(size_t i = 0; i < grid.size(); ++i)
	{

		fprintf(fp, "GRID*   %-16d%-16d%-16.9G%-16.9G%-8s\n", _index, 0, grid[i].x, grid[i].y, "*");
		fprintf(fp, "%-8s%-16.9G\n", "*", grid[i].z);
		++_index;
	}
	_index = 1;

	for(size_t i = 0; i < ctria3.size(); ++i)
	{
		fprintf(fp, "%-8s%-8d%-8d", "CTRIA3", _index, _tag);
		fprintf(fp, "%-8d%-8d%-8d\n", ctria3[i].v1, ctria3[i].v2, ctria3[i].v3 );
		++_index;
		//std::cout << _index << std::endl;
	}
	_index = 1;
	for(size_t i = 0; i < cquad4.size(); ++i)
	{
		fprintf(fp, "%-8s%-8d%-8d", "CQUAD4", _index, _tag);
		fprintf(fp, "%-8d%-8d%-8d%-8d\n", cquad4[i].v1, cquad4[i].v2, cquad4[i].v3, cquad4[i].v4 );
		++_index;
	}
	_index = 1;
	for(size_t i = 0; i < ctetra.size(); ++i)
	{
		fprintf(fp, "CTETRA* %-16d%-16d%-16d%-16d%-8s\n", _index, 0, ctetra[i].v1, ctetra[i].v2, "*");
		fprintf(fp, "%-8s%-16d%-16d\n", "*", ctetra[i].v3, ctetra[i].v4);
		++_index;
	}
	fclose(fp);
	return 1;
}

int readNas(const std::string &filename, std::vector<Vertex>& grid, std::vector<Face>& ctria3, std::vector<Quad>& cquad4, std::vector<Tet>& ctetra)
{
	int pre = 0;
	int cur;
	Vertex tempVertex;
	Face tempFace;
	Quad tempQuad;
	Tet tempTet;
	FILE *fp = fopen(filename.c_str(), "r");
	if(!fp)
	{
		std::cout << "Unable to open file " << filename.c_str() << std::endl;
		return 0;
	}
	char buffer[256];

	int count = 0;
	while(!feof(fp))
	{
		for(unsigned int i = 0; i < sizeof(buffer); ++i)
			buffer[i] = '\0';
		if(!fgets(buffer, sizeof(buffer), fp)) 
			break;
		if(!strncmp(buffer, "ENDDATA", 7))
			break;
		if(buffer[0] != '$')
		{
			if(!strncmp(buffer, "GRID", 4))
			{
				int num;
				double x, y, z;
				if(!readVertexNas(fp, buffer, 4, &num, &x, &y, &z)) 
					break;
				/*cur = num;
				if((cur - pre) != 1)
					std::cout << "error grid" << std::endl;
				pre = cur;*/
				tempVertex.x = x;
				tempVertex.y = y;
				tempVertex.z = z;
				tempVertex.No = num;
				if(num != grid.size()+1)
					int d = 1;
				grid.push_back(tempVertex);
			}
		}
	}
	rewind(fp);
	count = 0;
	pre = 0;
	while(!feof(fp))
	{
		for(unsigned int i = 0; i < sizeof(buffer); ++i)
			buffer[i] = '\0';
		if(!fgets(buffer, sizeof(buffer), fp)) break;
		if(buffer[0] != '$')
		{
			int num, region;
			if(!strncmp(buffer, "CTRIA3", 6))
			{
				readElementNas(fp, buffer, 6, 3, num, region, tempFace, grid);
				double l1 = sqrt( (grid[tempFace.v1-1].x-grid[tempFace.v2-1].x)*(grid[tempFace.v1-1].x-grid[tempFace.v2-1].x)
					+ (grid[tempFace.v1-1].y-grid[tempFace.v2-1].y)*(grid[tempFace.v1-1].y-grid[tempFace.v2-1].y)
					+ (grid[tempFace.v1-1].z-grid[tempFace.v2-1].z)*(grid[tempFace.v1-1].z-grid[tempFace.v2-1].z) );
				double l2 = sqrt( (grid[tempFace.v1-1].x-grid[tempFace.v3-1].x)*(grid[tempFace.v1-1].x-grid[tempFace.v3-1].x)
					+ (grid[tempFace.v1-1].y-grid[tempFace.v3-1].y)*(grid[tempFace.v1-1].y-grid[tempFace.v3-1].y)
					+ (grid[tempFace.v1-1].z-grid[tempFace.v3-1].z)*(grid[tempFace.v1-1].z-grid[tempFace.v3-1].z) );
				double l3 = sqrt( (grid[tempFace.v3-1].x-grid[tempFace.v2-1].x)*(grid[tempFace.v3-1].x-grid[tempFace.v2-1].x)
					+ (grid[tempFace.v3-1].y-grid[tempFace.v2-1].y)*(grid[tempFace.v3-1].y-grid[tempFace.v2-1].y)
					+ (grid[tempFace.v3-1].z-grid[tempFace.v2-1].z)*(grid[tempFace.v3-1].z-grid[tempFace.v2-1].z) );
				double p = (l1+l2+l3)/2;
				double S = (p*(p-l1)*(p-l2)*(p-l3));
				double maxl = std::max(std::max(l1,l2),l3);
				double minl = std::min(std::min(l1,l2),l3);
				
				if(l1<1e-15 || l2<1e-15 || l3<1e-15 ||S<1e-15)
				{
					std::cout << "index is " << ctria3.size()+1 << std::endl;
					std::cout << "v1 is " << tempFace.v1+1 << std::endl;
					std::cout << "v2 is " << tempFace.v2+1 << std::endl;
					std::cout << "v3 is " << tempFace.v3+1 << std::endl;
					std::cout << "p is " << p << std::endl;
					std::cout << "l1 is " << l1 << std::endl;
					std::cout << "l2 is " << l2 << std::endl;
					std::cout << "l3 is " << l3 << std::endl;
					std::cout <<"S is  " << S << std::endl; 
					std::cout << "error111" << std::endl;
				}
				else
				{
					if(maxl / minl > 100)
					{
						narrowTriangle.push_back(tempFace);
					}
					ctria3.push_back(tempFace);
				}
			}
			else if(!strncmp(buffer, "CQUAD4", 6))
			{
				readElementNasQuad(fp, buffer, 6, 4, num, region, tempQuad, grid);
				cquad4.push_back(tempQuad);
			}
			else if(!strncmp(buffer, "CTETRA", 6))
			{
				if(readElementNasTet(fp, buffer, 6, -4, num, region, tempTet, grid))
				{
					ctetra.push_back(tempTet);
				}
				else
					std::cout << "error" << std::endl;

			}
		}
	}
	std::vector<Quad> newcquad4;
	std::vector<Tet> newctetra;
	//writeNas("C:\\Users\\Administrator\\Desktop\\model\\narrowface.nas", grid, narrowTriangle, newcquad4, newctetra);
	fclose(fp);
	return 1;
}

#endif