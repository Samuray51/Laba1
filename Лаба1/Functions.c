#include<stdio.h>
#include<stdlib.h>

//Эта структура запоминает матрицы
struct memory
{
	int **matrix1;
	int Determinant1;
	int Size;
	struct memory *next;
};
typedef struct memory Memory;



//Эта функция запоминает матрицы и определитель
void MemoryDeterminant(Memory *head, int **Matrix, int size, int determinant)
{
	int i, j;
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->Size = size;
	head->Determinant1 = determinant;
	head->matrix1 = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i = i + 1)
	{
		head->matrix1[i] = (int*)malloc(size * sizeof(int));
	}
	for (i = 0; i < size; i = i + 1)
	{
		for (j = 0; j < size; j = j + 1)
		{
			head->matrix1[i][j] = Matrix[i][j];
		}
	}
	head->next = (Memory*)malloc(sizeof(Memory));
	head->next->next = NULL;
	head->next->Size = 0;
}




//Эта функция сравнивает матрицы
int CheckMatrix(int **matrix, int **matrix1_, int size)
{
	int i, j, temp = 1;
	for (i = 0; i < size; i = i + 1)
	{
		for (j = 0; j < size; j = j + 1)
		{
			if (matrix[i][j] != matrix1_[i][j])
			{
				temp = 0;
				break;
			}
		}
		if (temp == 0)
			break;
	}
	return temp;
}



//Эти функции проверяют если такие матрицы
Memory* SearchMatrix(Memory *head, int size, int **matrix)
{
	Memory *P = NULL;
	int Temporary;
	while (head != NULL)
	{
		if (head->Size == 0)
		{
			P = NULL;
			break;
		}
		if (head->Size == size)
		{
			Temporary = CheckMatrix(head->matrix1, matrix, size);
			if (Temporary != 0)
			{
				P = head;
				break;
			}
		}
		head = head->next;
	}
	return P;
}






//Эта функция считает колличество строк
int ROW(FILE *I)
{
	int size = 1;
	char tmp;
	while (!feof(I)) {
		if (fscanf_s(I, "%c", &tmp, 1) == 1)
		{
			if (tmp == 10)
			{
				size++;
			}
		}
		else
		{
			break;
		}
	}
	fseek(I, 0, SEEK_SET);
	return size;
}



//Эта функция считает колличество столбцов
int COLUMN(FILE *J)
{
	int k = 0, number, numberDijits = 0, s = 0;
	char tmp = 0;
	while (!feof(J))
	{
		while ((tmp != 10) && (!feof(J)))
		{
			fscanf_s(J, "%d", &number);
			k++;
			fscanf_s(J, "%c", &tmp, 1);
			if ((tmp != 10) && (!feof(J)))
			{
				fseek(J, ftell(J) - (sizeof(char)), SEEK_SET);
			}
		}
		if ((s > 0) && (k != numberDijits))
		{
			printf("Строки разной длины.");
			system("pause");
			exit(-1);
		}
		numberDijits = k;
		k = 0;
		tmp = 0;
		s++;
	}
	fseek(J, 0, SEEK_SET);
	return numberDijits;
}


//Эта фунеция проверяет на символы
int SYMBOL(FILE *X)
{
	char symbol;
	int possition = 0;
	while (!feof(X))
	{
		fscanf_s(X, "%c", &symbol, 1);
		if ((possition == 32) || (possition == 0) || (possition == 13))
		{
			if (!((symbol == 32) || (symbol == 45) || ((symbol >= 48) && (symbol <= 57))))
			{
				printf("Некорректные символы или файл пуст.\n");
				system("pause");
				exit(1);
			}
		}
		if ((possition >= 48) && (possition <= 57))
		{
			if (!((symbol == 32) || (symbol == 10) || ((symbol >= 48) && (symbol <= 57))))
			{
				printf("Некорректные символы или файл пуст\n");
				system("pause");
				exit(1);
			}
		}
		if (possition == 45) {
			if (!((symbol >= 48) && (symbol <= 57))) {
				printf("Некорректные символы или файл пуст\n");
				system("pause");
				exit(1);
			}
		}
		possition = symbol;
	}
	fseek(X, 0, SEEK_SET);
	return 0;
}


//Эта функцмя проверяет на пробелы
int SPACE(FILE *X)
{
	char t;
	char p = 0;
	while (!feof(X)) {
		fscanf_s(X, "%c", &t, 1);
		if (((t == 10) || (feof(X))) && (p == 32)) {
			printf("Ненужный пробел в конце строки или столбца.\n");
			system("pause");
			exit(1);
		}
		p = t;
	}
	fseek(X, 0, SEEK_SET);
	return 0;
}


//Эта функция проверяет длину числа
int LongNumber(FILE *X)
{
	char tmp = 0;
	int count = 0;
	while (!feof(X))
	{
		while ((tmp != 32) && (!feof(X)) && (tmp != 10) && (tmp != 13))
		{
			fscanf_s(X, "%c", &tmp, 1);
			count++;
			if (count > 4)
			{
				printf("Число слишком длинное.\n");
				system("pause");
				exit(1);
			}
		}
		count = 0;
		tmp = 0;
	}
	fseek(X, 0, SEEK_SET);
	return 0;
}



//Эта функция выводит матрицы
void PrintMatrix(int **matrix, int m)
{
	int i, j;
	for (i = 0; i < m; i = i + 1)
	{
		for (j = 0; j < m; j = j + 1)
		{
			printf("%3d ", matrix[i][j]);
		}
		printf("\n");
	}
}



//Эта функция вычеркивания строки и столбца
void GetMatrix(int **matrix, int count, int i, int j, int **TemporaryMatrix)
{
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < count - 1; ki++)
	{
		if (ki == i)
		{
			di = 1;
		}
		dj = 0;
		for (kj = 0; kj < count - 1; kj++)
		{
			if (kj == j)
			{
				dj = 1;
			}
			TemporaryMatrix[ki][kj] = matrix[ki + di][kj + dj];
		}
	}
}
//функция вычисления определителя(матрица,размерность)
long long int GetDeterminant(int **matrix, int count)
{
	int i, j = 0;
	long long int determinant = 0;
	int k = 1;	//степень
	if (count == 1)
	{
		determinant = matrix[0][0];
	}
	if (count == 2)
	{
		determinant = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
	}
	if (count > 2)
	{
		int **TemporaryMatrix, size;
		size = count - 1;
		TemporaryMatrix = (int**)malloc(size * sizeof(int*));
		for (int i1 = 0; i1 < size; i1 = i1 + 1)
		{
			TemporaryMatrix[i1] = (int*)malloc(size * sizeof(int));
		}
		for (i = 0; i < count; i++)
		{
			GetMatrix(matrix, count, i, j, TemporaryMatrix);
			//printf("%d\n", matrix[i][j]);
			//PrintMatrix(p, count-1);
			determinant = determinant + k * matrix[i][0] * GetDeterminant(TemporaryMatrix, count - 1);
			k = -k;
		}
		for (int i1 = 0; i1 < size; i1 = i1 + 1)
		{
			free(TemporaryMatrix[i1]);
		}
		free(TemporaryMatrix);
	}
	return determinant;
}
