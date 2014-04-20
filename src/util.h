#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "stdint.h"
#include "limits.h"


FILE* openFile(char *fileName);
int optionCheck(char *option, char *check);
char *substr(char *s, int position, int length);
long strToLong(char num[]);
void arrayCopy(unsigned char a[], char b[], int len);
int is_number(char a[], int len);
