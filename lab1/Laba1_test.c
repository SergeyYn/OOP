/************************************************************************
* file: Laba1_test.c
* purpose: testing functions declared in Laba1.h and defined in Laba1.c
* author : Yershykhin
* ***********************************************************************/
#include "Laba1.h"
int main() {
	char *const string = "SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";
	char *argz;
	size_t argz_len;
	char *entry = "usr=monty";
	char *const str = "monty";
	char *const with = "sergey";

	//creates argz vector
	argz_create_sep(string, 58, &argz, &argz_len);
	argz_print(argz, argz_len);

	//print number of '\0' symbols
	printf("\ncount = %d\n", argz_count(argz, argz_len));

	//adds "str" string to argz vector modifying argz and argz_len accordingly
	argz_add(&argz, &argz_len, str);
	argz_print(argz, argz_len);

	//deletes "entry" string from argz vector modifying argz and argz_len accordingly
	argz_delete(&argz, &argz_len, entry);
	argz_print(argz, argz_len);

	//replaces "str" tring with "with" string modifying argz and argz_len accordingly
	argz_replace(&argz, &argz_len, str, with);
	argz_print(argz, argz_len);

	//inserts "entry" string before "before" before string, or at the end if "before" == NULL modifying argz and argz_len accordingly
	entry = "TEST_INSERT";
	char *before = "PWD=/bin/sergey";
	argz_insert(&argz, &argz_len, before, entry);
	argz_print(argz, argz_len);

	//tests search of next element function
	entry = NULL;
	while(entry = argz_next(argz, &argz_len, entry)){//outputs first letter of each element after entry
		printf("%c ", entry[0]);
		printf("\n");
	}
	return 0;
}