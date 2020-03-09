#include "Astar.h"
#include <iostream>
#include <cmath>
#include <windows.h>
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
bool AstarMethod::IsInOpenList(int x, int y)
{
	for (auto node : openlist)
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
	for (auto it=openlist.begin();it!=openlist.end();it++)
	{
		if (node->X == (*it)->X && node->Y == (*it)->Y) //������ڵ�����openlist��G��С�����
		{
			if (node->G < (*it)->G)
			{
				(*it)->parent = node->parent;
				(*it)->G = node->G;
				(*it)->F = (*it)->G + (*it)->H;
			}
			return;
		}
		else
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
	}
	openlist.push_back(node);
}

void AstarMethod::FindPath(int start_x, int start_y, int end_x, int end_y)
{
	int curH = (end_x - start_x + end_y - start_y) * STRAIT_VALUE_PER_STEP;
	Node startNode = { nullptr, start_x, start_y, curH, 0, curH };
	openlist.push_back(&startNode);
	Node* curNode = &startNode;
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
		cout << curNode->X << "," << curNode->Y << endl;
		//������ǰ�ڵ���Χ��8��
		for (int x = curNode->X - 1; x <= curNode->X + 1 && x >= 0 && x <= map.size()-1 && !isFind; x++)
		{
			for (int y = curNode->Y - 1; y <= curNode->Y + 1 && y >= 0 && y <= map[0].size()-1 && !isFind; y++)
			{
				if (x == end_x && y == end_y)
				{
					isFind = true;
				}
				bool t = IsInCloseList(x, y);
				if (map[x][y] > 0 || IsInCloseList(x, y)) //����б����ĵ㡢�ϰ���closelist�еĽڵ�
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
		Sleep(500);
	}
	cout << "route is:" << endl;
	cout << "2,5" << endl;
	while (true)
	{
		cout << "<-";
		cout << curNode->X << "," << curNode->Y << endl;
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
