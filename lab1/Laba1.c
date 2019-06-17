/************************************************************************
* file: Laba1.c
* synopsis : The argz functions use malloc / realloc to allocate / grow argz vectors, and so any argz
* vector creating using these functions may be freed by using free; conversely, any argz
* function that may grow a string expects that string to have been allocated using malloc
* (those argz functions that only examine their arguments or modify them in place will work
* on any sort of memory).All argz functions that do memory allocation have a return type
* of error_t, and return 0 for success, and ERROR if an allocation error occurs.
* These functions are declared in the include file "argz.h".
* related files : none
* author : Yershykhin 
* ***********************************************************************/

#include "Laba1.h"

error_t argz_create_sep(const char * string, int sep, char ** argz, size_t * argz_len){
	if (string==NULL) {
		return ERROR;
	}
	*argz_len = strlen(string);
	*argz = malloc((*argz_len) + 1);
	while (*string) {
		if (*string == sep) {
			**argz = '\0';
		}
		else {
			**argz = *string;
		}
		++(*argz);
		++string;
	}
	**argz = '\0';
	*argz  -= *argz_len;
	return OK;
	}

size_t argz_count(const char * argz, size_t argz_len)
{
	size_t count = 0;
	for (int i = 0; i < argz_len; i++) {
		if (*(argz + i) == '\0') {
			count++;
		}
	}
	return count;
}

error_t argz_add(char ** argz, size_t * argz_len, const char * str)
{
	if (str == NULL) {
		return ERROR;
	}
	size_t len_str = strlen(str);
	*argz_len += len_str + 1;
	*argz = realloc(*argz, *argz_len);
	(*argz) += *argz_len - len_str - 1;
	**argz = '\0';
	++(*argz);
	while (*str) {
		**argz = *str;
		++(*argz);
		++str;
	}
	**argz = '\0';
	*argz -= *argz_len;
	return OK;
}

void argz_delete(char **argz, size_t *argz_len, char *entry)
{
	if (entry == NULL) {
		return;
	}
	size_t entry_len = strlen(entry);
	int count = 0;
	for (int i = 0; i < *argz_len; i++) {
		if ( *(*argz + i) == entry[count]) {
			count++;
			if (count == entry_len && *(*argz + i + 1) == '\0') {
				for (int j = i+1; j < *argz_len; j++) {
					*(*argz + j - entry_len - 1) = *(*argz + j);
				}
				*argz_len -= entry_len + 1;
				count = 0;
			}
		}
		else {
			count = 0;
		}
	}
}

error_t argz_insert(char ** argz, size_t * argz_len, char * before, const char * entry)
{
	if (entry == NULL) {
		return ERROR;
	}
	if (before == NULL) {
		char *const entry_add = entry;
		argz_add(argz, argz_len, entry_add);
		return OK;
	}
	int entry_len = strlen(entry);
	int size = 0;
	int zero_size_flag = 0;
	for (int i = 0; i < *argz_len; i++) {
		if (*(*argz + i) == before[0]) {
			size = i;
			if (size == 0) {
				size = entry_len;
				zero_size_flag = 1;
			}
			break;
		}
	}
	*argz_len += entry_len + 1;
	*argz = realloc(*argz, *argz_len);
	for (int i = *argz_len; i > size; i--) {
		*(*argz + i) = *(*argz + i - entry_len - 1);
	}
	*(*argz + size) = '\0';
	if (1 == zero_size_flag) {
			size = 0;
	}
	for (int i = size; i < size + entry_len; i++) {
		*(*argz + i) = entry[i - size];
	}
	return OK;
}

char * argz_next(char *argz, size_t *argz_len, const char *entry) {
	int count = 0;
	if (entry == NULL) {
		return argz;
	}
	size_t entry_len = strlen(entry);
	for (int i = 0; i < *argz_len; i++) {
		if (*(argz + i) == entry[count]) {
			count++;
			if (count == entry_len && *(argz + i + 1) == '\0'&& *(argz + i - entry_len) == '\0') {
				if (i + 2 > *argz_len) {
					return NULL;
				}
				return argz + i + 2;
			}
		}
		else {
			count = 0;
		}
	}
	return NULL;
}

error_t argz_replace(char ** argz, size_t * argz_len, const char * str, const char * with)
{
	if (str == NULL || with == NULL) {
		return ERROR;
	}
	int str_len = strlen(str);
	int with_len = strlen(with);
	int count = 0;
	if (str_len - with_len >= 0) {
		for (int i = 0; i < *argz_len; i++) {
			if (*(*argz + i) == str[count]) {
				count++;
				if (count == str_len) {
					int k = i - str_len + 1;
					for (int j = k; j < k + with_len; j++) {
						*(*argz + j) = with[j - k];
					}
					for (int j = k + with_len; j < *argz_len; j++) {
						*(*argz + j) = *(*argz + j + str_len - with_len);
					}
					count = 0;
					*argz_len -= str_len - with_len;
				}
			}
			else {
				count = 0;
			}
		}
		*argz = realloc(*argz, *argz_len);
	}
	else if (str_len - with_len < 0) {
		size_t dif = with_len - str_len;
		for (int i = 0; i < *argz_len; i++) {
			if (*(*argz + i) == str[count]) {
				count++;
				if (count == str_len) {
					*argz_len += dif;
					*argz = realloc(*argz, *argz_len);
					int k = i - str_len + 1;
					for (int j = *argz_len; j > i + 1; j--) {
						*(*argz + j) = *(*argz + j - dif);
					}
					for (int j = k; j < k + with_len; j++) {
						*(*argz + j) = with[j - k];
					}
					count = 0;
				}
			}
			else {
				count = 0;
			}
		}
	}
	return OK;
}

void argz_print(const char *argz, size_t argz_len) {
	printf("\n\n");
	for (int i = 0; i < argz_len; i++) {
		printf("%c", *(argz + i));
	}
	printf("\n\n");
}