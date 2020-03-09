#include "Astar.h"

int main()
{
	vector<vector<int> > a = {
		{0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0},
		{0,0,0,1,0,0,0},
		{0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0}
	};
	FindPathMethod* method = new AstarMethod(a);
	method->FindPath(2, 1, 2, 5);

	//std::list<Node> ls =
	//{
	//	{ nullptr, 0, 0, 0,0,0 }
	//};
	//auto node = *(ls.begin());
	//ls.erase(ls.begin());
	//std::cout << node.F << std::endl;
}



