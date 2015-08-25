#include "test.h"
#include "readNastran.h"
#include "meshOperator.h"

//void triangleSd()
//{
//	std::vector<Vertex> grid;
//	std::vector<Face> ctria3;
//	std::vector<Quad> cquad4;
//	std::vector<Vertex> newgrid;
//	std::vector<Face> newctria3;
//	std::vector<Quad> newcquad4;
//	readNas("E:\\sphere\\40m_bymeshlabS5.nas", grid, ctria3, cquad4);
//	//rate_Tri_Face_Edge(grid, ctria3);
//	subdividSphere(40, 1, grid, ctria3, newgrid, newctria3);
//	//threePointsubdividSphere(140, 1, grid, ctria3, newgrid, newctria3);
//	rate_Tri_Face_Edge(newgrid, newctria3);
//	writeNas("E:\\sphere\\40m_bymeshlabS6.nas", newgrid, newctria3);
//}

int main()
{
	float testFloat = 6.2;
	int testInt = 0;
	testFloat *= 10;
	testInt = (int)testFloat;
	std::cout << testFloat << std::endl;
	std::cout << testInt << std::endl;

	std::vector<Vertex> grid;
	std::vector<Face> ctria3;
	std::vector<Quad> cquad4;
	std::vector<Vertex> newgrid;
	std::vector<Face> newctria3;
	std::vector<Quad> newcquad4;
	std::vector<Tet> ctetra;
	std::vector<Tet> newctetra;

	readNas("D:\\sphere.nas", grid, ctria3, cquad4, ctetra);
	rate_Tri_Face_Edge(grid, ctria3);
	//std::sort(&grid[0], &grid[0]+grid.size());
	//int count = 0;
	//for(int i = 0; i < grid.size()-1; ++i)
	//{
	//	if(fab	s(grid[i].x-grid[i+1].x)<1e-2 && fabs(grid[i].y-grid[i+1].y)<1e-2 && fabs(grid[i].z-grid[i+1].z)<1e-2)
	//		++count;
	//}
	//std::cout << count << std::endl;
	//writeNas("C:\\Users\\Administrator\\Desktop\\model\\B02_new.nas", grid, ctria3, cquad4, ctetra);
	//readNas("C:\\Users\\Administrator\\Desktop\\model\\1618_a3.nas", grid, ctria3, cquad4, ctetra);
	////tempFunc(grid, cquad4, newgrid, newcquad4);
	//for(int i = 0; i < grid.size(); ++i)
	//{
	//	grid[i].x = grid[i].x * (1.0/25.4);
	//	grid[i].y = grid[i].y * (1.0/25.4);
	//	grid[i].z = grid[i].z * (1.0/25.4);
	//}
	//writeNas("C:\\Users\\Administrator\\Desktop\\model\\1618_a4.nas", grid, ctria3, cquad4, ctetra);

	//readNas("E:\\sphere\\20m_quad.nas", grid, ctria3, cquad4, ctetra);
	//ScaleQuad(160, grid);
	//rate_Quad_Face_Edge(grid, cquad4);
	//writeNas("E:\\sphere\\160m_Quad.nas", grid, ctria3, cquad4, newctetra);

	/*readNas("E:\\sphere\\80m_Quad.nas", grid, ctria3, cquad4, ctetra);
	subdividSphereQuad(20, 1, grid, cquad4, newgrid, newcquad4);
	rate_Quad_Face_Edge(newgrid, newcquad4);
	writeNas("E:\\sphere\\160m_Quad.nas", newgrid, newctria3, newcquad4, ctetra);*/

	/*readNas("E:\\sphere\\20m_tet.nas", grid, ctria3, cquad4, ctetra);
	avgTet(grid, ctetra);
	sbudividSphereTet(20, 1, grid, ctria3, ctetra, newgrid, newctria3, newctetra);
	avgTet(newgrid, newctetra);
	writeNasL("E:\\sphere\\20m_tetL1.nas", newgrid, newctria3, newcquad4, newctetra);*/

	/*readNasL("E:\\sphere\\20m_tetL3.nas", grid, ctria3, cquad4, ctetra);
	avgTet(grid, ctetra);
	sbudividSphereTet(20, 1, grid, ctria3, ctetra, newgrid, newctria3, newctetra);
	avgTet(newgrid, newctetra);
	writeNasL("E:\\sphere\\20m_tetL4.nas", newgrid, newctria3, newcquad4, newctetra);*/


	//readNas("E:\\sphere\\a_bl_V2.nas", grid, ctria3, cquad4, ctetra);
	//avgTet(grid, ctetra);
	//sbudividSphereTet(20, 1, grid, ctria3, ctetra, newgrid, newctria3, newctetra);
	//ScaleQuad(2, grid);
	//avgTet(newgrid, newctetra);
	//writeNas("G:\\sphere\\40m_tet5.nas", newgrid, newctria3, newcquad4, newctetra);
	//std::cout << "WRITE END1" << std::endl;
	//grid.clear();
	//ctria3.clear();
	//cquad4.clear();
	//ctetra.clear();
	//sbudividSphereTet(40, 1,  newgrid, newctria3, newctetra, grid, ctria3, ctetra);
	//ScaleQuad(2, grid);
	//avgTet(grid, ctetra);
	//writeNas("G:\\sphere\\80m_tet6.nas", grid, ctria3, cquad4, ctetra);
	//std::cout << "WRITE END2" << std::endl;
	//newgrid.clear();
	//newctria3.clear();
	//newcquad4.clear();
	//newctetra.clear();
	//sbudividSphereTet(80, 1, grid, ctria3, ctetra, newgrid, newctria3, newctetra);
	//ScaleQuad(2, grid);
	//avgTet(grid, ctetra);
	//writeNas("G:\\sphere\\160m_tet6.nas", newgrid, newctria3, newcquad4, newctetra);
	//std::cout << "WRITE END3" << std::endl;


	std::cout << "WRITE END" << std::endl;
	getchar();
	return 0;
}