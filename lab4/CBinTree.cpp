#include "CBinTree.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

CBinTree::CBinTree()
{
	root = NULL;
}

CBinTree::~CBinTree()
{
	clear(root);
}

bool CBinTree::create_from_file(const char *file_name)
{
	FILE *csv_file;
	if ((csv_file = fopen(file_name, "r")) == NULL) {
		printf("Can't open the CSV file\n");
		return false;
	}
	int count = 0;
	char temp;
	int symbol_count = 0;
	while (!feof(csv_file)) {
		fscanf(csv_file, "%c", &temp);
		if (temp == ';') {
			symbol_count++;
		}
		if (feof(csv_file) && symbol_count == 2) {
			count++;
			break;
		}
		else if (temp == '\n' && symbol_count == 2) {
			symbol_count = 0;
			count++;
		}
		else if (temp == '\n' && symbol_count != 2){
			cout << "CSV database file is incorrect!\n";
			return false;
		}
	}
	fclose(csv_file);
	if ((csv_file = fopen(file_name, "r")) == NULL) {
		cout <<"Can't open the CSV file\n";
		return false;
	}
	CTreeNode *TempArray = new CTreeNode[count];
	for (int i = 0; i < count; i++) {
		fscanf(csv_file, "%d;%[^;];%[^\n]\n", &TempArray[i].m_Trainnumber, &TempArray[i].m_Destination, &TempArray[i].m_DepartureTime);
		root = add(TempArray[i].m_Trainnumber, TempArray[i].m_Destination, TempArray[i].m_DepartureTime, root);
	}

	for (int i = 0; i < count - 1; i++) {//удаление одинаковых структур
		for (int j = i + 1; j < count; j++) {
			if (TempArray[i].m_Trainnumber == TempArray[j].m_Trainnumber) {
				cout << "CSV database file is incorrect!\n";
				return false;
			}
		}
	}

	delete[] TempArray;
	return true;
}

void CBinTree::write_tree()
{
	write(root);
}

void CBinTree::get_info_by_number(int train_number)
{
	CTreeNode *p = NULL;
	p = get_number(train_number, root);
	if (p == NULL)
		cout << "No train with this number in database" << endl;
	else
		cout << p->m_Trainnumber << " " << p->m_Destination << " " << p->m_DepartureTime << endl;
}

CTreeNode* CBinTree::delete_train(int train_number, CTreeNode *node)
{
	CTreeNode* P, *v;
	if (node == NULL)
		cout << "No train with such number!\n";
	else if (train_number < node->m_Trainnumber)
		node->left = delete_train(train_number, node->left);
	else if (train_number > node->m_Trainnumber)
		node->right = delete_train(train_number, node->right);
	else
	{
		P = node;
		if (node->right == NULL)
			node = node->left;
		else if (node->left == NULL)
			node = node->right;
		else
		{
			v = node->left;
			if (v->right)
			{
				while (v->right->right) {
					v = v->right;
				}
				node->m_Trainnumber = v->right->m_Trainnumber;
				strcpy(node->m_DepartureTime,v->right->m_DepartureTime);
				strcpy(node->m_Destination,v->right->m_Destination);
				P = v->right;
				v->right = v->right->left;
			}
			else
			{
				node->m_Trainnumber = v->m_Trainnumber;
				strcpy(node->m_DepartureTime, v->m_DepartureTime);
				strcpy(node->m_Destination, v->m_Destination);
				P = v;
				node->left = node->left->left;
			}
		}
		delete P;
	}
	return node;
}

void CBinTree::delete_train_pub(int train_number) {
	root = delete_train(train_number, root);
}

CTreeNode* CBinTree::add(int number, char *destination, char *time, CTreeNode *node)
{
	if (node == NULL){
		node = new CTreeNode;
		node->m_Trainnumber = number;
		strcpy(node->m_Destination, destination);
		strcpy(node->m_DepartureTime, time);
	}
	else{
		if (number < node->m_Trainnumber)
			node->left = add(number, destination, time, node->left);
		else
			node->right = add(number, destination, time, node->right);
	}
	return node;
}

void CBinTree::write(CTreeNode * node)
{
	if (node != NULL){
		write(node->left);
		cout << node->m_Trainnumber << " " << node->m_Destination << " " << node->m_DepartureTime << "\n";
		write(node->right);
	}
}

CTreeNode * CBinTree::get_number(int number, CTreeNode * node)
{
	if (node == NULL) {
		return NULL;
	}
	else if (node->m_Trainnumber == number) {
		return node;
	}
	else if (node->m_Trainnumber > number){
		return get_number(number, node->left);
	}
	else { 
		return get_number(number, node->right);
	}
}

bool CBinTree::write_station(CTreeNode * node, const char * station)
{
	bool flag = false;
	if (node != NULL){
		if (strcmp(station, node->m_Destination) == 0) {
			cout << node->m_Trainnumber << " " << node->m_Destination << " " << node->m_DepartureTime << "\n";
			flag = true;
		}
		flag+=write_station(node->left, station);
		flag+=write_station(node->right, station);
	}
	return flag;

}

void CBinTree::find_station(const char * station_name)
{
	if (station_name == NULL)
		cout << "Invalid destination name\n";
	else if (!write_station(root, station_name))
		cout << "There are no trains going to this station\n";
}

void CBinTree::clear(CTreeNode * node)
{
	if (node != NULL)
	{
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

void CBinTree::menu() {
	int temp;
	if (create_from_file("trains.csv") == false) {
		exit (1);
	}
	while (true) {
		system("cls");
		cout << "Select menu:\n";
		cout << "1 to output info about all trains\n";
		cout << "2 to delete train from database\n";
		cout << "3 to search for all trains to one destination\n";
		cout << "4 to search for info about train by number\n";
		cout << "5 to exit\n";
		cin >> temp;
		if (temp == 1) {
			write_tree();
		}
		else if (temp == 2) {
			cout << "Insert train number:\n";
			cin >> temp;
			delete_train_pub(temp);
		}
		else if (temp == 3) {
			cout << "Insert destination:\n";
			char temp_ch[50];
			cin >> temp_ch;
			find_station(temp_ch);
		}
		else if (temp == 4) {
			cout << "Insert train number:\n";
			cin >> temp;
			get_info_by_number(temp);
		}
		else if (temp == 5) {
			break;
		}
		else {
			cout << "Incorect input\n";
		}
		system("pause");
	}
}

