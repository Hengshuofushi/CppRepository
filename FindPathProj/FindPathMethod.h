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
	const int STRAIT_VALUE_PER_STEP = 10;
	const int ITA_VALUE_PER_STEP = 14;
private:
	
};