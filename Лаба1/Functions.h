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
	int Determinant1;
	int Size;
	struct memory *next;
};
typedef struct memory Memory;

void MemoryDeterminant(Memory *head, int **Matrix, int size, int determinant);
int CheckMatrix(int **matrix, int **matrix1_, int size);
Memory* SearchMatrix(Memory *head, int size, int **matrix);


int ROW(FILE *I);
int COLUMN(FILE *J);
int SYMBOL(FILE *X);
int SPACE(FILE *X);
int LongNumber(FILE *X);
void PrintMatrix(int **matrix, int m);
void GetMatrix(int **matrix, int count, int i, int j, int **TemporaryMatrix);
long long int GetDeterminant(int **matrix, int count);
#endif
