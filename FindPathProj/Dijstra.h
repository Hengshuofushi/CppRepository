#pragma once
/**
 * Dijstra�㷨
 * openlist: �����һ����Ҫ�����ĵ�
 * closelist�� �Ѿ�ȷ�ϵĵ�Ž�ȥ�������·���ϵĵ�
 * Dijstra�㷨����������£�·��������ͬ���൱�ڹ�����������Ӧ����Ҫ����·�����в�ͬ���۵�����ͼ��
 */

#include <list>
#include <string>
#include "FindPathMethod.h"
using NodeM = struct NodeM //·�����۲�ͬ
{
	NodeM(std::string name) : name(name){};
	std::string name;
	std::list<NodeM*> children;
	NodeM* parent;
	int val;
};
class DijstraMethod : public FindPathMethod
{
	using Node = struct Node //·��������ͬ
	{
		Node* parent;
		int val; //��ʼ�ڵ㵽���ڵ����С����
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
