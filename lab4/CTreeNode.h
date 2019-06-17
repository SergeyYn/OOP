#pragma once
class CTreeNode
{
public:
	int m_Trainnumber;
	char m_Destination[30];
	char m_DepartureTime[20];
	CTreeNode *left;
	CTreeNode *right;

	CTreeNode();
	~CTreeNode();
};

