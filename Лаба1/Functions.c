#include<stdio.h>
#include<stdlib.h>

//Эта структура запоминает матрицы
struct memory
{
	int **matrix1;
	int Det1;
	int Size;
	struct memory *next;
};
typedef struct memory Memory;



//Эта функция запоминает матрицы и определитель
void Add(Memory *head, int **Matr, int m, int d)
{
	int i, j;
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->Size = m;
	head->Det1 = d;
	head->matrix1 = (int**)malloc(m * sizeof(int*));
	for (i = 0; i < m; i = i + 1)
	{
		head->matrix1[i] = (int*)malloc(m * sizeof(int));
	}
	for (i = 0; i < m; i = i + 1)
	{
		for (j = 0; j < m; j = j + 1)
		{
			head->matrix1[i][j] = Matr[i][j];
		}
	}
	head->next = (Memory*)malloc(sizeof(Memory));
	head->next->next = NULL;
	head->next->Size = 0;
}





int Prov(int **matr, int **matr1, int m)
{
	int i, j, n = 1;
	for (i = 0; i < m; i = i + 1)
	{
		for (j = 0; j < m; j = j + 1)
		{
			if (matr[i][j] != matr1[i][j])
			{
				n = 0;
				break;
			}
		}
		if (n == 0)
			break;
	}
	return n;
}



//Эти функции проверяют если такие матрицы
Memory* Proverka(Memory *head, int m, int **matr)
{
	Memory *n = NULL;
	int p;
	while (head != NULL)
	{
		if (head->Size == 0)
		{
			n = NULL;
			break;
		}
		if (head->Size == m)
		{
			p = Prov(head->matrix1, matr, m);
			if (p != 0)
			{
				n = head;
				break;
			}
		}
		head = head->next;
	}
	return n;
}






//Эта функция считает колличество строк
int ROW(FILE *I)
{
	int m = 1;
	char tmp;
	while (!feof(I)) {
		if (fscanf_s(I, "%c", &tmp, 1) == 1)
		{
			if (tmp == 10)
			{
				m++;
			}
		}
		else
		{
			break;
		}
	}
	fseek(I, 0, SEEK_SET);
	return m;
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
	int pr = 0;
	while (!feof(X))
	{
		fscanf_s(X, "%c", &symbol, 1);
		if ((pr == 32) || (pr == 0) || (pr == 13))
		{
			if (!((symbol == 32) || (symbol == 45) || ((symbol >= 48) && (symbol <= 57))))
			{
				printf("Некорректные символы или файл пуст.\n");
				system("pause");
				exit(1);
			}
		}
		if ((pr >= 48) && (pr <= 57))
		{
			if (!((symbol == 32) || (symbol == 10) || ((symbol >= 48) && (symbol <= 57))))
			{
				printf("Некорректные символы или файл пуст\n");
				system("pause");
				exit(1);
			}
		}
		if (pr == 45) {
			if (!((symbol >= 48) && (symbol <= 57))) {
				printf("Некорректные символы или файл пуст\n");
				system("pause");
				exit(1);
			}
		}
		pr = symbol;
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
	char t = 0;
	int k = 0;
	while (!feof(X))
	{
		while ((t != 32) && (!feof(X)) && (t != 10) && (t != 13))
		{
			fscanf_s(X, "%c", &t, 1);
			k++;
			if (k > 4)
			{
				printf("Число слишком длинное.\n");
				system("pause");
				exit(1);
			}
		}
		k = 0;
		t = 0;
	}
	fseek(X, 0, SEEK_SET);
	return 0;
}



//Эта функция выводит матрицы
void PrintMatrix(int **matr, int m)
{
	int i, j;
	for (i = 0; i < m; i = i + 1)
	{
		for (j = 0; j < m; j = j + 1)
		{
			printf("%3d ", matr[i][j]);
		}
		printf("\n");
	}
}



//Эта функция вычеркивания строки и столбца
void getmatr(int **matri, int kolvo, int i, int j, int **pi)
{
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < kolvo - 1; ki++)
	{
		if (ki == i)
		{
			di = 1;
		}
		dj = 0;
		for (kj = 0; kj < kolvo - 1; kj++)
		{
			if (kj == j)
			{
				dj = 1;
			}
			pi[ki][kj] = matri[ki + di][kj + dj];
		}
	}
}
//функция вычисления определителя(матрица,размерность)
long long int det(int **matrix, int count)
{
	int i, j = 0;
	long long int temp = 0;
	int k = 1;	//степень
	if (count == 1)
	{
		temp = matrix[0][0];
	}
	if (count == 2)
	{
		temp = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
	}
	if (count > 2)
	{
		int **p, n;
		n = count - 1;
		p = (int**)malloc(n * sizeof(int*));
		for (int i1 = 0; i1 < n; i1 = i1 + 1)
		{
			p[i1] = (int*)malloc(n * sizeof(int));
		}
		for (i = 0; i < count; i++)
		{
			getmatr(matrix, count, i, j, p);
			//printf("%d\n", matrix[i][j]);
			//PrintMatrix(p, count-1);
			temp = temp + k * matrix[i][0] * det(p, count - 1);
			k = -k;
		}
		for (int i1 = 0; i1 < n; i1 = i1 + 1)
		{
			free(p[i1]);
		}
		free(p);
	}
	return temp;
}
