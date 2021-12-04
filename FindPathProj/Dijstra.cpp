#include "Dijstra.h"
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

DijstraMethod::DijstraMethod(std::vector<vector<int>> a)
{
	map.assign(a.begin(), a.end());
}

bool DijstraMethod::IsInCloseList(int x, int y)
{
	for (auto node : closelist)
	{
		if (node->x == x && node->y == y)
		{
			return true;
		}
	}
	return false;
}
void DijstraMethod::PutOpenList(Node* node) //openlist按F从小到大排列
{
	auto it = std::find_if(std::begin(openlist), std::end(openlist), [node](Node* on) {
		return on->x == node->x && on->y == node->y;
		}
	);
	if (it != std::end(openlist))
	{
		if (node->val < (*it)->val)
		{
			(*it)->parent = node->parent;
			(*it)->val = node->val;
		}
		return;
	}

	for (auto it = openlist.begin(); it != openlist.end(); it++)
	{
		if (node->val < (*it)->val)
		{
			openlist.insert(it, node);
			return;
		}
	}
	openlist.push_back(node);
}
void DijstraMethod::FindPath(int start_x, int start_y, int end_x, int end_y)
{
	Node* node_start = new Node;
	node_start->val = 0;
	node_start->x = start_x;
	node_start->y = start_y;
	node_start->parent = nullptr;
	openlist.push_back(node_start);
	bool isFound = false;
	Node* curNode = nullptr;
	while (isFound)
	{
		auto it = openlist.begin();
		if (it != openlist.end())
		{
			curNode = *it;
			closelist.push_back(*it);
			openlist.erase(it);
		}
		else
		{
			break; //算法结束，没找到
		}
		for (int x = curNode->x-1; x<= curNode->x + 1 || isFound;x++)
		{
			for (int y = curNode->y -1; y<= curNode->y+1 && isFound;y++)
			{
				if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size())
				{
					continue;
				}
				if (map[x][y] > 0 || IsInCloseList(x, y)) //忽略障碍和closelist中的节点
				{
					continue;
				}
				if (x == end_x && y == end_y)
				{
					isFound = true;
				}
				Node* tmp = new Node;
				tmp->x = x;
				tmp->y = y;
				tmp->parent = curNode;
				if (abs(x - curNode->x) + abs(y - curNode->y) > 1) //斜角上的
				{
					tmp->val = curNode->val + ITA_VALUE_PER_STEP;
				}
				else //直线上的
				{
					tmp->val = curNode->val + STRAIT_VALUE_PER_STEP;
				}
				PutOpenList(tmp);
			}
		}
	}
	if (!isFound)
	{
		cout << "Finished: path not found" << endl;
		return;
	}
	cout << "route is:" << endl;
	cout << "(2,5)";
	while (true)
	{
		cout << " <- ";
		cout << "(" << curNode->x << "," << curNode->y << ")";
		if (curNode->parent != nullptr)
		{
			curNode = curNode->parent;
		}
		else
		{
			break;
		}
	}
}

DijkstraMethod2::DijkstraMethod2(std::list<NodeM*> n)
{
	nodem_list.assign(n.begin(), n.end());
}

void DijkstraMethod2::FindPath(NodeM* start, NodeM* end)
{
	NodeM* curNode = start;
	while (true)
	{
		auto it = openlist.begin();
		if (it != openlist.end())
		{
			curNode = *it;
			closelist.push_back(*it);
			openlist.erase(it);
		}
		else
		{
			break; //openlist为空则结束
		}
		
		for (auto it = curNode->children.begin(); it != curNode->children.end();it++)
		{
			PutIntoOpenlist(*it);
		}
	}
	cout << "path:" << endl;
	cout << end->name;
	while (end->parent)
	{
		end = end->parent;
		cout << " <- " << end->name;
	}
}

void DijkstraMethod2::PutIntoOpenlist(NodeM* node)
{
	auto it = std::find_if(openlist.begin(), openlist.end(), [=](NodeM* n) {
		return node->name == n->name;
		});
	if (it != std::end(openlist)) //已存在则更新
	{
		if ((*it)->val > node->val)
		{
			(*it)->parent = node->parent;
			(*it)->val = node->val;
		}
		return;
	}
	//不存在则插入，最小val值在最前
	for (auto it = openlist.begin(); it != openlist.end(); it++)
	{
		if ((*it)->val < node->val)
		{
			openlist.insert(it, node);
			return;
		}
	}
	openlist.push_back(node);
}
