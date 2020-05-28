#ifndef _Functions_H_
#define  _Functions_H_
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>
#include<errno.h>
#include<string.h>
#include<windows.h>

struct memory
{
	int **matrix1;
	int Det1;
	int Size;
	struct memory *next;
};
typedef struct memory Memory;

void Add(Memory *head, int **Matr, int m, int d);
int Prov(int **matr, int **matr1, int m);
Memory* Proverka(Memory *head, int m, int **matr);


int ROW(FILE *I);
int COLUMN(FILE *J);
int SYMBOL(FILE *X);
int SPACE(FILE *X);
int LongNumber(FILE *X);
void PrintMatrix(int **matr, int m);
void getmatr(int **matri, int kolvo, int i, int j, int **pi);
int det(int **matrix, int count);
#endif
