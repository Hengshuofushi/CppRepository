#include "Astar.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using std::cout;
using std::endl;
using std::abs;

const int STRAIT_VALUE_PER_STEP = 10;
const int ITA_VALUE_PER_STEP = 14;

AstarMethod::AstarMethod(vector<vector<int> > map)
{
	this->map.assign(map.begin(), map.end());
}
bool AstarMethod::IsInCloseList(int x, int y)
{
	for (auto node : closelist)
	{
		if (node->X == x && node->Y == y)
		{
			return true;
		}
	}
	return false;
}

void AstarMethod::PutOpenList(Node* node) //openlist��F��С��������
{
	auto it = std::find_if(std::begin(openlist), std::end(openlist), [node](Node* on) {
		return on->X == node->X && on->Y == node->Y;
		}
	);
	if (it != std::end(openlist))
	{
		if (node->G < (*it)->G)
		{
			(*it)->parent = node->parent;
			(*it)->G = node->G;
			(*it)->F = node->G + node->H;
		}
		return;
	}

	for (auto it = openlist.begin(); it != openlist.end(); it++)
	{
		if (node->F < (*it)->F) //FֵС�ķ�ǰ��
		{
			openlist.insert(it, node);
			return;
		}
		else if (node->F == (*it)->F && node->H <= (*it)->H) //Fֵ��ȣ���HֵС�ķ�ǰ��
		{
			openlist.insert(it, node);
			return;
		}
	}
	openlist.push_back(node);
}

void AstarMethod::FindPath(int start_x, int start_y, int end_x, int end_y)
{
	int curH = (end_x - start_x + end_y - start_y) * STRAIT_VALUE_PER_STEP;
	Node* startNode = new Node;
	startNode->parent = nullptr;
	startNode->X = start_x;
	startNode->Y = start_y;
	startNode->G = 0;
	startNode->H = curH;
	startNode->F = curH;
	openlist.push_back(startNode);
	Node* curNode = startNode;
	bool isFind = false;
	while (!isFind)
	{
		//����СF�Ľڵ��openlistȡ��������closelist����������ڵ㵱����ǰ�ڵ�
		auto it = openlist.begin(); //��СFֵ�ڵ��ڵ�һ��

		if (it != openlist.end())
		{
			curNode = *it;
			closelist.push_back(*it);
			openlist.erase(it);
		}
		else
		{
			break;
		}
		cout << curNode->X << "," << curNode->Y << endl;
		//������ǰ�ڵ���Χ��8��
		for (int x = curNode->X - 1; x <= curNode->X + 1 && !isFind; x++)
		{
			for (int y = curNode->Y - 1; y <= curNode->Y + 1 && !isFind; y++)
			{
				if (x <0 || x>=map.size() || y<0 || y>= map[0].size())
				{
					continue;
				}
				if (x == end_x && y == end_y)
				{
					isFind = true;
				}
				bool t = IsInCloseList(x, y);
				if (map[x][y] > 0 || IsInCloseList(x, y)) //�����ϰ���closelist�еĽڵ�
				{
					continue;
				}

				int tH = (std::abs(end_x - x) + std::abs(end_y - y)) * STRAIT_VALUE_PER_STEP;
				int tG = curNode->G;
				if (abs(x - curNode->X) + abs(y - curNode->Y) > 1) //б���ϵ�
				{
					tG += ITA_VALUE_PER_STEP;
				}
				else //ֱ���ϵ�
				{
					tG += STRAIT_VALUE_PER_STEP;
				}
				Node* tNode = new Node;
				tNode->parent = curNode;
				tNode->X = x;
				tNode->Y = y;
				tNode->G = tG;
				tNode->H = tH;
				tNode->F = tG + tH;
				PutOpenList(tNode);
			}
		}
	}
	if (!isFind)
	{
		cout << "Finished: path not found" << endl;
		return;
	}
	cout << "route is:" << endl;
	cout << "(2,5)";
	while (true)
	{
		cout << " <- ";
		cout << "(" << curNode->X << "," << curNode->Y << ")";
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
