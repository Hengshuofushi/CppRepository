#pragma once
/**
 * Dijstra算法
 * openlist: 存放下一步需要遍历的点
 * closelist： 已经确认的点放进去，即最短路径上的点
 * Dijstra算法在这种情况下（路径代价相同）相当于广域搜索，其应该主要用于路径具有不同代价的有向图。
 */

#include <list>
#include <string>
#include "FindPathMethod.h"
using NodeM = struct NodeM //路径代价不同
{
	NodeM(std::string name) : name(name){};
	std::string name;
	std::list<NodeM*> children;
	NodeM* parent;
	int val;
};
class DijstraMethod : public FindPathMethod
{
	using Node = struct Node //路径代价相同
	{
		Node* parent;
		int val; //起始节点到本节点的最小代价
		int x, y;
	};
	
public:
	DijstraMethod(std::vector<vector<int> > a);
	
	virtual void FindPath(int start_x, int start_y, int end_x, int end_y);
	
protected:
private:
	std::list<Node*> openlist;
	std::list<Node*> closelist;
	

	bool IsInCloseList(int x, int y);
	void PutOpenList(Node* node);
};
class DijkstraMethod2
{
public:
	DijkstraMethod2(std::list<NodeM*> n);
	void FindPath(NodeM* start, NodeM* end);
protected:
private:
	std::list<NodeM*> openlist;
	std::list<NodeM*> closelist;
	std::list<NodeM*> nodem_list;

	void PutIntoOpenlist(NodeM* node);
};
