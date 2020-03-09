#pragma once
#include <vector>
using std::vector;
class FindPathMethod
{
public:
	FindPathMethod(){};
	virtual void FindPath(int start_x, int start_y, int end_x, int end_y) = 0;
	
protected:
	vector<vector<int> > map;
private:
	
};