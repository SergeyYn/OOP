#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;//���������� �������������
	char manufacturer[127];// ������������
	char model[127];// ������������ �����
	int year;	 // �� ������������
	float price;// ����
	int x_size;// �������������� ����� ������ ����������
	int y_size;// ������������ ����� ������ ����������
} SCAN_INFO;

typedef struct {
	int rec_nmb;//number of records
	SCAN_INFO *recs;//records 
}RECORD_SET;

void create_db(const char *csv, const char *db);
int make_index(const char *db, const char *field_name);
RECORD_SET * get_recs_by_index(const char *db, char *inde3x_field);
void reindex(const char *db);
void del_scanner(const char *db, int id);
void add_scanner(const char *db, const char* scanner_str);
void print_db(const char *db);
RECORD_SET* select(const char *db, const char *field, const char *value);
void print_rec_set(RECORD_SET *rs);
