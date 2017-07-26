//will contain all the declarations
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void tablecheck(char * tablefile);
int* encryption(int bin_key[64], int input_bin_t[64], int df,int flag_print_rl,int turn);
void read_encryption(FILE * fp, char * key, const char *input_f, int method);
void test_table_encrypt(FILE * fp);
