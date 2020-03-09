/**
 * A* - Manhatton
 �������� open list ��
�ظ����¹��̣�
a. ���� open list ������ F ֵ��С�Ľڵ㣬������Ϊ��ǰҪ����Ľڵ㡣
b. ������ڵ��Ƶ� close list ��
c. �Ե�ǰ����� 8 �����ڷ����ÿһ������
�� ������ǲ��ɵִ�Ļ������� close list �У������������������²�����
�� ��������� open list �У��������� open list �����Ұѵ�ǰ��������Ϊ���ĸ��ף���¼�÷���� F �� G �� H ֵ��
�� ������Ѿ��� open list �У��������·�� ( �����ɵ�ǰ���񵽴������� ) �Ƿ���ã��� G ֵ���ο�����С�� G ֵ��ʾ���Ǹ��õ�·��������������������ĸ�������Ϊ��ǰ���񣬲����¼������� G �� F ֵ�������� open list �ǰ� F ֵ����Ļ����ı���������Ҫ��������
d. ֹͣ������
�� ���յ���뵽�� open list �У���ʱ·���Ѿ��ҵ��ˣ�����
�� �����յ�ʧ�ܣ����� open list �ǿյģ���ʱû��·����
3.����·�������յ㿪ʼ��ÿ���������Ÿ��ڵ��ƶ�ֱ����㣬��������·����
 */
#define  _ASTAR_
#ifdef _ASTAR_
#include <list>
#include "FindPathMethod.h"
#include <iostream>
class Node
{
public:
	Node* parent; // parent node
	int X; // x����
	int Y; // y����
	int F; // ��ʼ�㵽�յ�Ļ��� F = G+ H
	int G; // ��ʼ�㵽����Ļ���
	int H; // ���㵽�յ�Ļ���
protected:
private:
};

class AstarMethod : public FindPathMethod
{
public:
	AstarMethod(vector<vector<int> > map);
	void FindPath(int start_x, int start_y, int end_x, int end_y) override;
protected:
private:
	std::list<Node*> openlist;
	std::list<Node*> closelist;

	bool IsInCloseList(int x, int y);
	void PutOpenList(Node* node);
	

};


#endif
