#define _CRT_SECURE_NO_WARNINGS
#include "CFile.h"
#include <vector>
#include <iostream>
using std::vector;
using namespace std;

vector <CFile> group;

void File_Input(){
	FILE *f;
	char temp_name[50];
	char temp_size[50];
	char temp_kwd[255];
	char temp;
	CFile obj;
	int nmb=0;
	int j = 0;
	if ((f = fopen("lab.csv", "r")) == NULL) {
		printf("Can't open the CSV file\n");
		exit(1);
	}
	fscanf(f, "%c", &temp);
	while (temp != '\n' && !feof(f)) {
		j = 0;
		while (temp != ';' && !feof(f)) {
			temp_name[j] = temp;
			j++;
			fscanf(f, "%c", &temp);
		}
		temp_name[j] = '\0';
		fscanf(f, "%c", &temp);
		j = 0;
		while (temp != ';' && !feof(f)) {
			temp_size[j] = temp;
			j++;
			fscanf(f, "%c", &temp);
		}
		temp_size[j] = '\0';
		j = 0;
		fscanf(f, "%c", &temp);
		while (temp != '\n' && !feof(f)) {
			temp_kwd[j] = temp;
			j++;
			fscanf(f, "%c", &temp);
		}
		temp_kwd[j] = '\0';
		obj.SetDetails(temp_name, atoi(temp_size));
		obj.SetKeywords(temp_kwd);
		group.push_back(obj);
		fscanf(f, "%c", &temp);
	}
}

int main() {
	File_Input();
	CFile::ListAll(group);
	char* add = new char[7];
	strcpy(add, "kwAdd");
	cout << endl << "Added word: " << add << endl;
	CFile::AddKeyword(group, add);
	CFile::ListAll(group);
	cout << endl << "Sorted by keywords nmb" << endl;
	CFile::SortByKeywordsNumber(group);
	CFile::ListAll(group);
	cout << endl << "Sorted by size" << endl;
	CFile::SortBySize(group);
	CFile::ListAll(group);
	char* del = new char[5];
	strcpy(del, "kw22");
	cout << endl << "Deleted word: " << del << endl;
	CFile::DelKeyword(group, del);
	CFile::ListAll(group);
	int len = 5;
	cout << endl << "Deleted words with length: " << len << endl;
	CFile::DelKeywordByLen(group, len);
	CFile::ListAll(group);
	return 0;
}