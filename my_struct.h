#include <stdio.h>
#include <malloc.h>

typedef struct Line{
	int n; //кол-во элементов в строке
	int* a; //массив эл-тов
}Line;

typedef struct Matrix{
	int lines; //кол-во строк матрицы
	Line *matr; //массив строк матрицы
}Matrix;

int getInt(int *);
int get_el(int *);
int input(Matrix *a);
void output(const char *msg, Matrix a);
Matrix change(Matrix *);
void erase(Matrix *a);
int positive(Line);
int negative(Line);
Matrix* func(Matrix* matrix);
