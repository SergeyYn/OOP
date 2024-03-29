#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "CFile.h"

using namespace std;
using std::vector;

CFile::CFile()
{
	name = NULL; ;
	size = 0;
	keywords = NULL;
	keywords_nmb = 0;
}

CFile::CFile(const CFile &src)
{
	if (src.name == NULL) this->name = NULL;
	else {
		this->name = new char[strlen(src.name)];
		strcpy(this->name, src.name);
	}
	this->size = src.size;
	if (src.keywords == NULL) this->keywords = NULL;
	else {
		this->keywords = new char[strlen(src.keywords)];
		strcpy(this->keywords, src.keywords);
	}
	this->keywords_nmb = src.keywords_nmb;
}

CFile::~CFile()
{
}

void CFile::SetDetails(const char *new_name, int new_size)
{
	name = new char[strlen(new_name)];
	strcpy(name, new_name);
	size = new_size;
}

void CFile::SetKeywords(const char *new_keywords)
{
	int count = 0;
	int size = strlen(new_keywords);
	for (int i = 0; i < size; i++) {
		if (new_keywords[i] == ';' && i < size)
			count++;
	}
	if(new_keywords[size-1]!=';')
		count++;
	keywords_nmb = count;
	keywords = new char[size];
	strcpy(keywords, new_keywords);
}

CFile & CFile::operator=(const CFile &temp)
{
	this->size = temp.size;
	if (temp.keywords == NULL) this->keywords = NULL;
	else {
		this->keywords = new char[strlen(temp.keywords)];
		strcpy(this->keywords, temp.keywords);
	}
	if (temp.name == NULL) this->name = NULL;
	else {
		this->name = new char[strlen(temp.name)];
		strcpy(this->name, temp.name);
	}
	this->keywords_nmb = temp.keywords_nmb;
	return *this;
}

bool CFile::operator<(const CFile &temp) const
{
	if (this->size < temp.size)
		return true;
	return false;
}

void CFile::SetSize(int new_size)
{
	size = new_size;
}

void CFile::Print() const
{
	if(name == NULL) cout << "\nEmpty object\nSize: 0\nNo keywords\nKeywords number: 0"<< endl;
	else {
		cout << "\nName: " << name << "\nSize: " << size << endl;
		cout << "Keywords: ";
		int j = 0;
		for (int i = 0; i < keywords_nmb; i++) {
			while (keywords[j] != ';' && j < strlen(keywords)) {
				cout << keywords[j];
				j++;
			}
			j++;
			cout << " ";
		}
		cout << "\nKeywords number: " << keywords_nmb << endl;
	}
}
void CFile::ListAll(const vector<CFile> &temp)
{
	for (int i = 0; i < temp.size(); i++) {
		temp[i].Print();
	}
}
void CFile::AddKeyword(vector<CFile>&temp, char *kwrd)
{
	if (kwrd == NULL) {
		cout << "No keyword set" << endl;
		return;
	}
	int size1, size2, size3;
	char* tc;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i].name == NULL) {
			cout << "\nCan't add keyword to empty object" << endl;
			continue;
		}
		size1 = strlen(temp[i].keywords);
		size2 = strlen(kwrd);
		size3 = size1 + size2 + 2;
		tc = new char[size3];
		strcpy(tc, temp[i].keywords);
		tc[size1] = ';';
		for (int j = size1 + 1; j < size3; j++) {
			tc[j] = kwrd[j - size1 - 1];
		}
		tc[size3 - 1] = '\0';
		temp[i].keywords = new char[size3];
		strcpy(temp[i].keywords, tc);
		temp[i].keywords_nmb++;
	}
}

void CFile::DelKeyword(vector<CFile>&temp, char *kwrd)
{
	if (kwrd == NULL)
		return;
	int length, k1, k2, count = 0;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i].keywords_nmb == 0)
			continue;
		char** t = new char*[temp[i].keywords_nmb];
		k1 = 0;
		for (int j = 0; j < temp[i].keywords_nmb; j++) {
			t[j] = new char[strlen(temp[i].keywords)];
			k2 = 0;
			while (temp[i].keywords[k1] != ';' && k1 < strlen(temp[i].keywords)) {
				t[j][k2] = temp[i].keywords[k1];
				k1++;
				k2++;
			}
			k1++;
			t[j][k2] = '\0';
			if (!(strcmp(t[j], kwrd))) {
				count++;
			}
		}
		if (count > 0) {
			int size = 0;
			for (int j = 0; j < temp[i].keywords_nmb; j++) {
				if (strcmp(t[j], kwrd)) {
					size += strlen(t[j]);
					size++;
				}
			}
			size--;
			temp[i].keywords = new char[size];
			int t_s = 0;
			for (int j = 0; j < temp[i].keywords_nmb; j++) {
				if (strcmp(t[j], kwrd)) {
					for (int k = 0; k < strlen(t[j]); k++) {
						temp[i].keywords[t_s] = t[j][k];
						t_s++;
					}
					if (j < temp[i].keywords_nmb - count) {
						temp[i].keywords[t_s] = ';';
						t_s++;
					}
				}
				delete t[j];
			}
			temp[i].keywords[t_s] = '\0';
			temp[i].keywords_nmb -= count;
		}
		count = 0;
		delete t;
	}
}

void CFile::DelKeywordByLen(vector<CFile>&temp, int len)
{
	if (len == 0)
		return;
	int length, k1, k2, count = 0;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i].keywords_nmb == 0)
			continue;
		char** t = new char*[temp[i].keywords_nmb];
		k1 = 0;
		for (int j = 0; j < temp[i].keywords_nmb; j++) {
			t[j] = new char[strlen(temp[i].keywords)];
			k2 = 0;
			while (temp[i].keywords[k1] != ';' && k1 < strlen(temp[i].keywords)) {
				t[j][k2] = temp[i].keywords[k1];
				k1++;
				k2++;
			}
			k1++;
			t[j][k2] = '\0';
			if ((strlen(t[j]))==len) {
				count++;
			}
		}
		if (count > 0) {
			int size = 0;
			for (int j = 0; j < temp[i].keywords_nmb; j++) {
				if ((strlen(t[j])) != len) {
					size += strlen(t[j]);
					size++;
				}
			}
			size--;
			temp[i].keywords = new char[size];
			int t_s = 0;
			for (int j = 0; j < temp[i].keywords_nmb; j++) {
				if ((strlen(t[j])) != len) {
					for (int k = 0; k < strlen(t[j]); k++) {
						temp[i].keywords[t_s] = t[j][k];
						t_s++;
					}
					if (j < temp[i].keywords_nmb - count) {
						temp[i].keywords[t_s] = ';';
						t_s++;
					}
				}
				delete t[j];
			}
			temp[i].keywords[t_s] = '\0';
			temp[i].keywords_nmb -= count;
		}
		count = 0;
		delete t;
	}
}

void CFile::SortBySize(vector<CFile>&temp)
{
	CFile buf;
	for (int i = 0; i < temp.size() - 1; i++) {
		for (int j = 0; j < temp.size() - i - 1; j++) {
			if(temp[j+1] < temp[j]) {
				buf = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = buf;
			}
		}
	}
}

void CFile::SortByKeywordsNumber(vector<CFile>&temp)
{
	CFile buf;
	for (int i = 0; i < temp.size()-1; i++) {
		for (int j = 0; j < temp.size()-i-1; j++){
			if (temp[j].keywords_nmb > temp[j+1].keywords_nmb) {
				buf = temp[j];
				temp[j] = temp[j+1];
				temp[j+1] = buf;
			}
		}
	}
}
