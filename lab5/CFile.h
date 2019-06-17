#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
using std::vector;
class CFile {
public:
	//default constructor
	CFile();
	//copy constructor
	CFile(const CFile &temp);
	//destructor
	~CFile();
	void SetDetails(const char *nname, int nsize);
	void SetKeywords(const char* nkwrds);
	//overloaded assignment
	CFile & operator=(const CFile &temp);
	bool operator<(const CFile &temp)const;
	int GetSize()const { return size; };
	void SetSize(int nsize);
	void Print()const;
	static void ListAll(const vector<CFile>&);
	static void AddKeyword(vector <CFile> &temp, char *kwrd);
	static void DelKeyword(vector <CFile> &temp, char *kwrd);
	static void DelKeywordByLen(vector <CFile> &temp, int len);
	static void SortBySize(vector <CFile> &temp);
	static void SortByKeywordsNumber(vector <CFile> &temp);

private:
	char *name;//file name
	int size;//file length
	char *keywords;//set of keywords
	int keywords_nmb;//keywords number
};
