#include"Functions.h"



int main()
{
	setlocale(LC_ALL, "RUS");
	int i = 0, j = 0, m1, m=0, n = 0;
	long long int d;
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
		if (scanf_s("%d", &m) == 0)
		{
			printf("Некорректный ввод\n");
			system("pause");
			exit(1);
		}
		if (m == 1)
		{
			printf("Введите размер матрицы: ");
			if (scanf_s("%d", &m) == 0)
			{
				printf("Некорректный ввод\n");
				system("pause");
				exit(1);
			}
			if (m < 1)
			{
				printf("Определитель вычислить невозможно!\n");
				system("pause");
				exit(1);
			}
			if (m > 12)
			{
				printf("Большой размер матрицы!\n");
				system("pause");
				exit(1);
			}
			Mas.matrix = (int**)malloc(m * sizeof(int*));
			for (i = 0; i < m; i = i + 1)
			{
				Mas.matrix[i] = (int*)malloc(m * sizeof(int));
			}
			for (i = 0; i < m; i = i + 1)
			{
				for (j = 0; j < m; j = j + 1)
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
			PrintMatrix(Mas.matrix, m);
			printf("Вычесление определителя матрицы способом разложения по первому столбцу:\n");

			P = Proverka(head, m, Mas.matrix);
			if (P == NULL)
			{
				start = clock();
				d = det(Mas.matrix, m);
				end = clock();
				if (head->next == NULL)
				{
					head->Det1 = d;
					head->Size = m;
					head->matrix1 = (int**)malloc(m * sizeof(int*));
					for (i = 0; i < m; i = i + 1)
					{
						head->matrix1[i] = (int*)malloc(m * sizeof(int));
					}
					for (i = 0; i < m; i = i + 1)
					{
						for (j = 0; j < m; j = j + 1)
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
					Add(head, Mas.matrix, m, d);
				}
			}
			else
			{
				start = clock();
				d = P->Det1;
				end = clock();
			}



			printf("Определитель матрицы равен: %lld\n", d);
			printf("Время вычисления определителя: %f секунд\n", ((float)end - start) / (float)CLOCKS_PER_SEC);
			for (i = 0; i < m; i = i + 1)
			{
				free(Mas.matrix[i]);
			}
			free(Mas.matrix);
		}
		else if (m == 2)
		{
			FILE *in;
			err = fopen_s(&in, "input.txt", "r");
			if (err == NULL)
			{
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
				m = ROW(in);
				m1 = COLUMN(in);
				if (m == m1)
				{
					if (m > 12)
					{
						printf("Большой размер матрицы!\n");
						system("pause");
						exit(1);
					}
					Mas.matrix = (int**)malloc(m * sizeof(int*));
					for (i = 0; i < m; i = i + 1)
					{
						Mas.matrix[i] = (int*)malloc(m * sizeof(int));
					}
					printf("Размер матрицы: %d\n", m);
					for (i = 0; i < m; i = i + 1)
					{
						for (j = 0; j < m; j = j + 1)
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
					PrintMatrix(Mas.matrix, m);
					printf("Вычесление определителя матрицы способом разложения по первому столбцу:\n");




					P = Proverka(head, m, Mas.matrix);
					if (P == NULL)
					{
						start = clock();
						d = det(Mas.matrix, m);
						end = clock();
						if (head->next == NULL)
						{
							head->Det1 = d;
							head->Size = m;
							head->matrix1 = (int**)malloc(m * sizeof(int*));
							for (i = 0; i < m; i = i + 1)
							{
								head->matrix1[i] = (int*)malloc(m * sizeof(int));
							}
							for (i = 0; i < m; i = i + 1)
							{
								for (j = 0; j < m; j = j + 1)
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
							Add(head, Mas.matrix, m, d);
						}
					}
					else
					{
						start = clock();
						d = P->Det1;
						end = clock();
					}




					printf("Определитель матрицы равен: %lld\n", d);
					printf("Время вычисления определителя: %f секунд\n", ((float)end - start) / (float)CLOCKS_PER_SEC);
					for (i = 0; i < m; i = i + 1)
					{
						free(Mas.matrix[i]);
					}
					free(Mas.matrix);
				}
				else
				{
					printf("Матрица не квадратная.\n");
					system("pause");
					exit(1);
				}
			}
			else if (err != NULL)
			{
				printf("Файл: input.txt\nКод ошибки: %d\n", err);
				perror("Описание ошибки");
			}
		}
		else if (m == 3)
		{
			srand((int)time(0));
			printf("Введите размер матрицы: ");
			if (scanf_s("%d", &m) == 0)
			{
				printf("Некорректный ввод\n");
				system("pause");
				exit(1);
			}
			if (m < 1)
			{
				printf("Определитель вычислить невозможно!\n");
				system("pause");
				exit(1);
			}
			if (m > 12)
			{
				printf("Большой размер матрицы!\n");
				system("pause");
				exit(1);
			}
			Mas.matrix = (int**)malloc(m * sizeof(int*));
			for (i = 0; i < m; i = i + 1)
			{
				Mas.matrix[i] = (int*)malloc(m * sizeof(int));
			}
			printf("Размер матрицы: %d\n", m);
			for (i = 0; i < m; i = i + 1)
			{
				for (j = 0; j < m; j = j + 1)
				{
					Mas.matrix[i][j] = -9 + rand() % 19;
				}
			}
			printf("Рандомная матрица:\n");
			PrintMatrix(Mas.matrix, m);
			printf("Вычесление определителя матрицы способом разложения по первому столбцу:\n");




			P = Proverka(head, m, Mas.matrix);
			if (P == NULL)
			{
				start = clock();
				d = det(Mas.matrix, m);
				end = clock();
				if (head->next == NULL)
				{
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
							head->matrix1[i][j] = Mas.matrix[i][j];
						}
					}
					head->next = (Memory*)malloc(sizeof(Memory));
					head->next->next = NULL;
					head->next->Size = 0;
				}
				else
				{
					Add(head, Mas.matrix, m, d);
				}
			}
			else
			{
				start = clock();
				d = P->Det1;
				end = clock();
			}



			printf("Определитель матрицы равен: %lld\n", d);
			printf("Время вычисления определителя: %f секунд\n", ((float)end - start) / (float)CLOCKS_PER_SEC);
			for (i = 0; i < m; i = i + 1)
			{
				free(Mas.matrix[i]);
			}
			free(Mas.matrix);
		}
		else if(m == 4)
		{
			system("pause");
			exit(1);
		}
		else
		{
			printf("Некорректный ввод\n");
			system("pause");
			exit(1);
		}
		system("pause");
		system("cls");
	}
	system("pause");
	return 0;
}