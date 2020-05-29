#include"Functions.h"



int main()
{
	setlocale(LC_ALL, "RUS");
	int i = 0, j = 0, size = 0, size1, number;
	long long int determinant;
	errno_t err;
	clock_t start, end;
	struct mas
	{
		int **matrix;
	};
	struct mas Mas;

	Memory *head = (Memory*)malloc(sizeof(Memory)), *P;
	head->next = NULL;
	head->Size = 0;

	while (1)
	{
		printf("Введите 1, чтобы ввести матрицу с клавиатуры.\nВведите 2, чтобы взять матрицу из файла.\nВведите 3, чтобы посчитать рандомную матрицу.\nНажмите 4, чтобы выйти из программы.\n");
		if (scanf_s("%d", &number) == 0)
		{
			printf("Некорректный ввод\n");
			system("pause");
			exit(1);
		}
		if (number == 1)
		{
			printf("Введите размер матрицы: ");
			if (scanf_s("%d", &size) == 0)
			{
				printf("Некорректный ввод\n");
				system("pause");
				exit(1);
			}
			if (size < 1)
			{
				printf("Определитель вычислить невозможно!\n");
				system("pause");
				exit(1);
			}
			if (size > 12)
			{
				printf("Большой размер матрицы!\n");
				system("pause");
				exit(1);
			}
			Mas.matrix = (int**)malloc(size * sizeof(int*));
			for (i = 0; i < size; i = i + 1)
			{
				Mas.matrix[i] = (int*)malloc(size * sizeof(int));
			}
			for (i = 0; i < size; i = i + 1)
			{
				for (j = 0; j < size; j = j + 1)
				{
					printf("Матрица[%d][%d]= ", i, j);
					if (scanf_s("%d", &Mas.matrix[i][j]) == 0)
					{
						printf("Некорректный ввод\n");
						system("pause");
						exit(1);
					}
					if (Mas.matrix[i][j] < -99 || Mas.matrix[i][j]>99)
					{
						printf("Число слишком длинное!\n");
						system("pause");
						exit(1);
					}
				}
			}
			printf("Исходная матрица:\n");
		}
		else if (number == 2)
		{
			FILE *in;
			err = fopen_s(&in, "input.txt", "r");
			if (err != NULL)
			{
				printf("Файл: input.txt\nКод ошибки: %d\n", err);
				perror("Описание ошибки");
				system("pause");
				exit(1);
			}
			if (SYMBOL(in) == 1) {
				system("pause");
				exit(1);
			}
			if (SPACE(in) == 1) {
				system("pause");
				exit(1);
			}
			if (LongNumber(in) == 1) {
				system("pause");
				exit(1);
			}
			size = ROW(in);
			size1 = COLUMN(in);
			if (size == size1)
			{
				if (size > 12)
				{
					printf("Большой размер матрицы!\n");
					system("pause");
					exit(1);
				}
				Mas.matrix = (int**)malloc(size * sizeof(int*));
				for (i = 0; i < size; i = i + 1)
				{
					Mas.matrix[i] = (int*)malloc(size * sizeof(int));
				}
				printf("Размер матрицы: %d\n", size);
				for (i = 0; i < size; i = i + 1)
				{
					for (j = 0; j < size; j = j + 1)
					{
						fscanf_s(in, "%d", &Mas.matrix[i][j]);
						if (Mas.matrix[i][j] > 99)
						{
							printf("Большое число!\n");
							system("pause");
							exit(1);
						}
					}
				}
				printf("Матрица из файла:\n");
			}
			else
			{
				printf("Матрица не квадратная.\n");
				system("pause");
				exit(1);
			}
		}
		else if (number == 3)
		{
			srand((int)time(0));
			printf("Введите размер матрицы: ");
			if (scanf_s("%d", &size) == 0)
			{
				printf("Некорректный ввод\n");
				system("pause");
				exit(1);
			}
			if (size < 1)
			{
				printf("Определитель вычислить невозможно!\n");
				system("pause");
				exit(1);
			}
			if (size > 12)
			{
				printf("Большой размер матрицы!\n");
				system("pause");
				exit(1);
			}
			Mas.matrix = (int**)malloc(size * sizeof(int*));
			for (i = 0; i < size; i = i + 1)
			{
				Mas.matrix[i] = (int*)malloc(size * sizeof(int));
			}
			printf("Размер матрицы: %d\n", size);
			for (i = 0; i < size; i = i + 1)
			{
				for (j = 0; j < size; j = j + 1)
				{
					Mas.matrix[i][j] = -9 + rand() % 19;
				}
			}
			printf("Рандомная матрица:\n");
		}
		else if(number == 4)
		{
			exit(1);
		}
		else
		{
			printf("Некорректный ввод\n");
			system("pause");
			exit(1);
		}
		PrintMatrix(Mas.matrix, size);
		printf("Вычесление определителя матрицы способом разложения по первому столбцу:\n");
		P = SearchMatrix(head, size, Mas.matrix);
		if (P == NULL)
		{
			start = clock();
			determinant = GetDeterminant(Mas.matrix, size);
			end = clock();
			if (head->next == NULL)
			{
				head->Determinant1 = determinant;
				head->Size = size;
				head->matrix1 = (int**)malloc(size * sizeof(int*));
				for (i = 0; i < size; i = i + 1)
				{
					head->matrix1[i] = (int*)malloc(size * sizeof(int));
				}
				for (i = 0; i < size; i = i + 1)
				{
					for (j = 0; j < size; j = j + 1)
					{
						head->matrix1[i][j] = Mas.matrix[i][j];
					}
				}
				head->next = (Memory*)malloc(sizeof(Memory));
				head->next->next = NULL;
				head->next->Size = 0;
			}
			else
			{
				MemoryDeterminant(head, Mas.matrix, size, determinant);
			}
		}
		else
		{
			start = clock();
			determinant = P->Determinant1;
			end = clock();
		}
		printf("Определитель матрицы равен: %lld\n", determinant);
		printf("Время вычисления определителя: %f секунд\n", ((float)end - start) / (float)CLOCKS_PER_SEC);
		for (i = 0; i < size; i = i + 1)
		{
			free(Mas.matrix[i]);
		}
		free(Mas.matrix);
		system("pause");
		system("cls");
	}
	system("pause");
	return 0;
}