#include "Laba_2_Head.h"
//доп функции сравнения для qsort
int compare_manufacturers(const void * a, const void * b)
{
	SCAN_INFO *A = (SCAN_INFO *)a;
	SCAN_INFO *B = (SCAN_INFO *)b;
	return strcmp(A->manufacturer, B->manufacturer);
}
int compare_models(const void * a, const void * b)
{
	SCAN_INFO *A = (SCAN_INFO *)a;
	SCAN_INFO *B = (SCAN_INFO *)b;
	return strcmp(A->model, B->model);
}
int compare_years(const void * a, const void * b)
{
	SCAN_INFO *A = (SCAN_INFO *)a;
	SCAN_INFO *B = (SCAN_INFO *)b;
	return A->year - B->year;
}
int compare_prices(const void * a, const void * b)
{
	SCAN_INFO *A = (SCAN_INFO *)a;
	SCAN_INFO *B = (SCAN_INFO *)b;
	if (A->price - B->price > 0) {
		return 1;
	}
	else if (A->price - B->price < 0) {
		return -1;
	}
	else 
		return 0;
}
int compare_x_sizes(const void * a, const void * b)
{
	SCAN_INFO *A = (SCAN_INFO *)a;
	SCAN_INFO *B = (SCAN_INFO *)b;
	return A->x_size - B->x_size;
}
int compare_y_sizes(const void * a, const void * b)
{
	SCAN_INFO *A = (SCAN_INFO *)a;
	SCAN_INFO *B = (SCAN_INFO *)b;
	return A->y_size - B->y_size;
}


void create_db(const char *csv, const char *db) {
	int count = 0;
	FILE *csv_file;
	FILE *db_file;
	if ((csv_file = fopen(csv, "r")) == NULL) {
		printf("Can't open the CSV file\n");
		exit(1);
	}
	char temp;
	int symbol_count = 0;
	while (!feof(csv_file)) {
		fscanf(csv_file, "%c", &temp);
		if (temp == ';') {
			symbol_count++;
		}
		if (feof(csv_file) && symbol_count == 5) {
			count++;
			break;
		}
		else if (temp == ';' && symbol_count == 6) {
			fscanf(csv_file, "%c", &temp);
			if (temp == '\n'){
				symbol_count = 0;
				count++;
			}
			else {
				printf("CSV database file is incorrect!\n");
				exit(1);
			}
		}
	}
	fclose(csv_file);
	if ((csv_file = fopen(csv, "r")) == NULL) {
		printf("Can't open the CSV file\n");
		exit(1);
	}
	SCAN_INFO *all_scanners;
	all_scanners = malloc(sizeof(SCAN_INFO)*count);
	for (int i = 0; i < count; i++) {
		all_scanners[i].id = i;
		fscanf(csv_file, "%[^;];%[^;];%d;%f;%d;%d;\n", &all_scanners[i].manufacturer, &all_scanners[i].model, &all_scanners[i].year, &all_scanners[i].price, &all_scanners[i].x_size, &all_scanners[i].y_size);
	}
	fclose(csv_file);
	for (int i = 0; i < count-1; i++) {//удаление одинаковых структур
		for (int j = i + 1; j < count; j++) {
			if (strcmp(all_scanners[i].manufacturer, all_scanners[j].manufacturer) == 0 && strcmp(all_scanners[i].model, all_scanners[j].model)==0 && all_scanners[i].year == all_scanners[j].year && all_scanners[i].price == all_scanners[j].price && all_scanners[i].x_size == all_scanners[j].x_size && all_scanners[i].y_size == all_scanners[j].y_size) {
				for (int k = j; k < count-1; k++) {
					int temp_id = all_scanners[k].id;
					all_scanners[k] = all_scanners[k + 1];
					all_scanners[k].id = temp_id;
				}
				count--;
				i = 0;
			}
		}
	}  
	all_scanners = realloc(all_scanners, sizeof(SCAN_INFO)*count);

	if ((db_file = fopen(db, "w")) == NULL) {
		printf("Can't create the DB file\n");
		exit(1);
	}
	fwrite(&count, sizeof(int), 1, db_file);
	for (int i = 0; i < count; i++) {
		fwrite(&all_scanners[i], sizeof(SCAN_INFO), 1, db_file);
	}
	free(all_scanners);
	fclose(db_file);
}

int make_index(const char * db, const char * field_name)
{
	FILE* index;
	FILE *db_file;
	char filename[100];
	sprintf(filename, "%s.idx", field_name);
	if ((index = fopen(filename, "w")) == NULL) {
		printf("Can't create INDEX file\n");
		return 1;
	}
	if ((db_file = fopen(db, "r")) == NULL) {
		printf("Can't open the DB file\n");
		return 1;
	}
	int count = 0;
	fread(&count, sizeof(int),1, db_file);
	SCAN_INFO *temp = malloc(sizeof(SCAN_INFO)*count);
	for (int i = 0; i < count; i++) {
		fread(&(temp[i]), sizeof(SCAN_INFO), 1, db_file);
	}
	if (strcmp(field_name, "manufacturer") == 0)
		qsort(temp, count, sizeof(SCAN_INFO), compare_manufacturers);
	else if (strcmp(field_name, "model") == 0)
		qsort(temp, count, sizeof(SCAN_INFO), compare_models);
	else if (strcmp(field_name, "year") == 0)
		qsort(temp, count, sizeof(SCAN_INFO), compare_years);
	else if (strcmp(field_name, "price") == 0)
		qsort(temp, count, sizeof(SCAN_INFO), compare_prices);
	else if (strcmp(field_name, "x_size") == 0)
		qsort(temp, count, sizeof(SCAN_INFO), compare_x_sizes);
	else if (strcmp(field_name, "y_size") == 0)
		qsort(temp, count, sizeof(SCAN_INFO), compare_y_sizes);
	else {
		printf("Field name is not correct!\n");
		return 1;
	}
	for (int i = 0; i < count; i++) {
		fprintf(index, "%d ", temp[i].id);
	}
	free(temp);
	fclose(db_file);
	fclose(index);
	return 0;
}

RECORD_SET * get_recs_by_index(const char * db, char * index_field)
{
	FILE *db_file;
	FILE *index;
	char filename[127];
	RECORD_SET *record = malloc(sizeof(RECORD_SET));
	int temp_id = 0;
	sprintf(filename, "%s.idx", index_field);
	if ((index = fopen(filename, "r")) == NULL) {
		printf("Can't open the INDEX file\n");
		exit(1);
	}
	if ((db_file = fopen(db, "r")) == NULL) {
		printf("Can't open the DB file\n");
		exit(1);
	}
	fread(&record->rec_nmb, sizeof(int), 1, db_file);
	SCAN_INFO *temp_struct = malloc(sizeof(SCAN_INFO)*record->rec_nmb);
	record->recs = malloc(sizeof(SCAN_INFO)*(record->rec_nmb));
	for (int i = 0; i < record->rec_nmb; i++) {
		fread(&temp_struct[i], sizeof(SCAN_INFO), 1, db_file);
	}
	for (int i = 0; i < record->rec_nmb; i++) {
		fscanf(index, "%d", &temp_id);
		for (int j = 0; j < record->rec_nmb;j++) {
			if (temp_struct[j].id == temp_id) {
				record->recs[i] = temp_struct[j];
			}
		}
	}
	free(temp_struct);
	fclose(index);
	fclose(db_file);
	return record;
}

void reindex(const char * db)
{
	make_index(db, "manufacturer");
	make_index(db, "model");
	make_index(db, "year");
	make_index(db, "price");
	make_index(db, "x_size");
	make_index(db, "y_size");
}

void del_scanner(const char * db, int id)
{
	FILE *db_file;
	int initial_number = 0;
	int final_number = 0;
	if ((db_file = fopen(db, "r")) == NULL) {
		printf("Can't open the DB file\n");
		exit(1);
	}
	fread(&initial_number, sizeof(int), 1, db_file);
	SCAN_INFO *temp_struct = malloc(sizeof(SCAN_INFO)*initial_number);
	for (int i = 0; i < initial_number; i++) {
		fread(&(temp_struct[i]), sizeof(SCAN_INFO), 1, db_file);
	}
	fclose(db_file);
	if ((db_file = fopen(db, "w")) == NULL) {
		printf("Can't re-create the DB file\n");
		exit(1);
	}
	int struct_count = 0;
	final_number = initial_number;
	fseek(db_file, sizeof(int), SEEK_SET);
	for (int i = 0; i < initial_number; i++) {
		if (temp_struct[i].id != id) {
			fwrite(&temp_struct[i], sizeof(SCAN_INFO), 1, db_file);
		}
		else
			final_number--;
	}
	fseek(db_file, 0, SEEK_SET);
	fwrite(&final_number, sizeof(int), 1, db_file);
	free(temp_struct);
	fclose(db_file);
	reindex(db);
}

void add_scanner(const char * db, const char * scanner_str)
{
	FILE *db_file;
	int temp;
	SCAN_INFO temp_struct;
	SCAN_INFO *db_temp_struct;
	char temp_buf[127];
	if ((db_file = fopen(db, "r+")) == NULL) {
		printf("Can't open the DB file\n");
		exit(1);
	}
	if (strcmp(scanner_str, "") == 0) {
		printf("String is incorrect\n");
		exit(1);
	}
	int symbol_count = 0;
	for (int k = 0; k < 127;k++)
	{
		if (scanner_str[k] == ';')
			symbol_count++;
	}
	if (symbol_count != 5) {
		printf("String is incorrect!\n");
		exit(1);
	}
	memset(temp_buf, 0, sizeof(temp_buf));
	int j = 0;
	int count = 0;
	for (int i = 0; i < 5; i++) {
		while (scanner_str[count] != ';' ) {
			temp_buf[j] = scanner_str[count];
			j++;
			count++;
		}
		temp_buf[j] = '\0';
		count++;
		j = 0;
		switch (i) {
			case 0:
				strcpy(temp_struct.manufacturer, temp_buf);
				break;
			case 1:
				strcpy(temp_struct.model, temp_buf);
				break;
			case 2:
				temp_struct.year = strtol(temp_buf, NULL, 10);
				break;
			case 3:
				temp_struct.price = strtof(temp_buf, NULL);
				break;
			case 4:
				temp_struct.x_size = strtol(temp_buf, NULL, 10);
				break;
		}
	}
	while (scanner_str[count]) {
		temp_buf[j] = scanner_str[count];
		j++;
		count++;
	}
	temp_buf[j] = '\0';
	temp_struct.y_size = strtol(temp_buf, NULL, 10);

	fread(&temp, sizeof(int), 1, db_file);
	db_temp_struct = malloc(sizeof(SCAN_INFO)*temp);
	int same_flag = 0;
	for (int i = 0; i < temp; i++) {
		fread(&db_temp_struct[i], sizeof(SCAN_INFO), 1, db_file);
		if (strcmp(temp_struct.manufacturer, db_temp_struct[i].manufacturer) == 0 && strcmp(temp_struct.model, db_temp_struct[i].model) == 0 && temp_struct.year == db_temp_struct[i].year && temp_struct.price == db_temp_struct[i].price && temp_struct.x_size == db_temp_struct[i].x_size && temp_struct.y_size == db_temp_struct[i].y_size) {
			same_flag = 1;
			break;
		}
	}
	if (same_flag != 1) {
		temp++;
		fseek(db_file, 0, SEEK_SET);
		fwrite(&temp, sizeof(int), 1, db_file);
		fseek(db_file, sizeof(int) + sizeof(SCAN_INFO)*(temp - 2), SEEK_SET);
		fread(&temp_struct.id, sizeof(int), 1, db_file);
		temp_struct.id++;
		fseek(db_file, sizeof(int) + sizeof(SCAN_INFO)*(temp - 1), SEEK_SET);
		fwrite(&temp_struct, sizeof(SCAN_INFO), 1, db_file);
	}
	free(db_temp_struct);
	fclose(db_file);
	reindex(db);
}

void print_db(const char * db)
{
	FILE* text_info;
	FILE *db_file;
	char filename[100];
	int count = 0;
	sprintf(filename, "%s.txt", db);
	if ((text_info = fopen(filename, "w")) == NULL) {
		printf("Can't create TEXT file\n");
		exit (1);
	}
	if ((db_file = fopen(db, "r")) == NULL) {
		printf("Can't open the DB file\n");
		exit(1);
	}
	fread(&count, sizeof(int), 1, db_file);
	SCAN_INFO *temp = malloc(sizeof(SCAN_INFO)*count);
	fprintf(text_info, "Database file contains %d scanners.\nEach row contains scanner's id manufacturer, model, year, price, x and y sizes in this exact order.\n", count);
	for (int i = 0; i < count; i++) {
		fread(&(temp[i]), sizeof(SCAN_INFO), 1, db_file);
		fprintf(text_info, "%d, %s, %s, %d, %.2f, %d, %d\n", (temp[i]).id, (temp[i]).manufacturer, (temp[i]).model, (temp[i]).year, (temp[i]).price, (temp[i]).x_size, (temp[i]).y_size);
	}
	fclose(db_file);
	fclose(text_info);
	free(temp);
}

RECORD_SET * select(const char * db, const char * field, const char * value)
{
	FILE *db_file;
	RECORD_SET *record = malloc(sizeof(RECORD_SET));
	int flag = 0;
	if ((db_file = fopen(db, "r")) == NULL) {
		printf("Can't open the DB file\n");
		exit(1);
	}
	fread(&record->rec_nmb, sizeof(int), 1, db_file);
	record->recs = malloc(sizeof(SCAN_INFO)*(record->rec_nmb));
	for (int i = 0; i < record->rec_nmb; i++) {
		fseek(db_file, sizeof(int) + sizeof(SCAN_INFO)*i, SEEK_SET);
		fread(&record->recs[i], sizeof(SCAN_INFO), 1, db_file);
	}

	for (int i = 0; i < record->rec_nmb; i++) {
		if (strcmp(field, "manufacturer") == 0) {
			if (strcmp(record->recs[i].manufacturer, value) != 0) {
				flag = 1;
			}
		}
		else if (strcmp(field, "model") == 0) {
			if (strcmp(record->recs[i].model, value) != 0) {
				flag = 1;
			}
		}
		else if (strcmp(field, "year") == 0) {
			if (record->recs[i].year != strtol(value,NULL,10)) {
				flag = 1;
			}
		}
		else if (strcmp(field, "price") == 0) {
			if (record->recs[i].price != strtof(value, NULL)) {
				flag = 1;
			}
		}
		else if (strcmp(field, "x_size") == 0) {
			if (record->recs[i].x_size != strtol(value, NULL, 10)) {
				flag = 1;
			}
		}
		else if (strcmp(field, "y_size") == 0) {
			if (record->recs[i].y_size != strtol(value, NULL, 10)) {
				flag = 1;
			}
		}
		else {
			printf("No such field in database!\n");
			exit(1);
		}
		if(flag == 1){
			for (int j = i; j < record->rec_nmb - 1; j++) {
				record->recs[j] = record->recs[j + 1];
			}
			record->rec_nmb--;
			i--;
			flag = 0;
		}
	}
	record->recs = realloc(record->recs, sizeof(SCAN_INFO)*record->rec_nmb);
	fclose(db_file);
	return record;
}

void print_rec_set(RECORD_SET * rs)
{
	printf("Records in RECORD_set order:\n");
	for (int i = 0; i < rs->rec_nmb; i++) {
		printf("id = %d; %s,%s,%d,%0.2f,%d,%d\n", rs->recs[i].id, rs->recs[i].manufacturer, rs->recs[i].model, rs->recs[i].year, rs->recs[i].price, rs->recs[i].x_size, rs->recs[i].y_size);
	}
}