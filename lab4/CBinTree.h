#pragma once
#include "CTreeNode.h"
class CBinTree
{
	CTreeNode *root;
public:
	CBinTree();
	~CBinTree();
	bool create_from_file(const char *file_name);
	void write_tree();
	void get_info_by_number(int train_number);
	void find_station(const char *station_name);
	void delete_train_pub(int train_number);
	void menu();
private:
	CTreeNode* delete_train(int train_number, CTreeNode *root);
	CTreeNode* add(int number, char *desination, char *time, CTreeNode *node);
	void write(CTreeNode *node);
	CTreeNode* get_number(int num, CTreeNode *node);
	bool write_station(CTreeNode *node, const char *station);
	void clear(CTreeNode *node);
};

