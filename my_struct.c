#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "my_struct.h"

int getInt(int *a){
	int n;
	do{
		n = scanf("%d", a);
		if(n<0){
			return 0;
		}
		if(n==0){
			printf("%s\n", "Ошибка! Повторите ввод");
			scanf("%*[^\n]");
			scanf("%*c");	
			
		}
	}while(n==0);
	return 1;
}
// todo remove
int get_el(int *a){
	int n;
	do{
		n = scanf("%d", a);
		if(n<0){
			return 0;
		}
		if(n==0){
			printf("%s\n", "Ошибка! Повторите ввод");
			scanf("%*[^\n]");
		}
	}while(n==0);
	return 1;
}

int input(Matrix *rm){
	const char *pr = "";
	int m; //кол-во строк матрицы
	int i;
	int j;
	do{
		printf("%s\n", pr);
		printf("Enter number of lines: -->");
		pr = "Error, repeat";
		if(getInt(&m)==0){
			return 0;
		}
	} while(m < 1);
	rm->lines = m;
	rm->matr = (Line *)malloc(m*sizeof(Line));
	for(i = 0; i< rm->lines; i++){
		rm->matr[i].n = 0;
	}
	for(i = 0; i< rm->lines; i++){
		pr ="";
		do{
			printf("%s\n", pr);
			printf("Enter number of elements %d: -->", i+1);
			pr = "Error, repeat";
			if (getInt(&m) == 0){
				return 0;
			}
		}while(m<1);
		rm->matr[i].n = m;
		rm->matr[i].a = (int *)malloc(sizeof(int) * m);

		printf("Enter line #%d:\n", i+1);
		for (j=0; j<m; j++){
			if(get_el(&rm->matr[i].a[j])==0){
				return 0;
			}
		}
		
	}
	return 1;
}

void output(const char *msg, Matrix a){
	int i, j;
	printf("%s: \n", msg);
	for (i=0; i < a.lines; i++){
		for (j = 0; j < a.matr[i].n; j++){
			printf("%d ", a.matr[i].a[j]);
		}
		printf("\n");
	}
}

void erase(Matrix *a){
	int i;
	for (i=0; i< a->lines; ++i){
		if (a->matr[i].n != 0){
			free(a->matr[i].a);
		}
		
	}
	free(a->matr);
	a->matr = NULL;
}

Matrix change(Matrix *structure){
	Matrix res = {0, NULL};
	int m = structure -> lines;
	res.lines = 0;
	res.matr = (Line *)malloc(m*sizeof(Line));
	
	for (int i = 0; i < m; i++){
		int el = structure -> matr[i].n;
		res.matr[res.lines].n = el; 
		res.matr[res.lines].a = (int*)malloc(sizeof(int) *el);

		int pos = positive(structure->matr[i]);
		int neg = negative(structure->matr[i]);
		if (pos != -1 && neg != -1){
			if(neg > pos){
				int p = 1;
				for (int k = 0; k<(neg - pos - 1); k++){
					res.matr[res.lines].a[k] = structure->matr[i].a[pos+p];
					p++;
				}				
				res.matr[res.lines].a = realloc(res.matr[res.lines].a, (neg - pos - 1)*sizeof(int));
				res.matr[res.lines].n = neg - pos - 1;
			}

			if(neg < pos){
				free(res.matr[res.lines].a);
				continue;
			}
		}
		
		if (pos != -1 && neg == -1){
			int p = 1;
			for (int l = 0; l < el - pos - 1; l++){
				res.matr[res.lines].a[l] = structure->matr[i].a[pos+p];
				p++;
			}
			res.matr[res.lines].a = realloc(res.matr[res.lines].a, (el - pos - 1)*sizeof(int));
			res.matr[res.lines].n = el - pos - 1;
		}

		if (pos == -1 && neg != -1){
			for (int u = 0; u<neg; u++){
				res.matr[res.lines].a[u] = structure->matr[i].a[u];
			}
			res.matr[res.lines].a = realloc(res.matr[res.lines].a, neg * sizeof(int));
			res.matr[res.lines].n = neg;
		}

		if(pos == -1 && neg == -1){
			free(res.matr[res.lines].a);
			continue;
		}
		
		res.lines++;
		
	}
	res.matr = realloc(res.matr, res.lines*sizeof(Line));
	return res;
	
}

int positive(Line str){
	int k = -1;
	int len = str.n;
	for (int i = 0; i<len; i++){
		if((str.a[i]) > 0){
			k = i;
			return k;
		}
		
	}
	return k;
}

int negative(Line str){
	int k = -1;
	int len = str.n;
	for (int i = 0; i<len; i++){
		if((str.a[i]) < 0){
			k = i;
			return k;
		}
			
	}
	return k;
}


Matrix* func(Matrix* matrix){
    Matrix* matrix_copy = (Matrix *) calloc(1, sizeof(Matrix));
    matrix_copy->lines = matrix->lines;
    matrix_copy->matr = calloc(matrix_copy->lines, sizeof(Line));
    for (int i = 0; i<matrix_copy->lines; i++){
        matrix_copy->matr[i].n = matrix->matr[i].n;
        matrix_copy->matr[i].a = calloc(matrix_copy->matr[i].n, sizeof(int));
        int max = 0;
        int idx_max;
        int min = 1000000000;
        int idx_min;
        for (int j = 0; j<matrix_copy->matr[i].n; j++){
            matrix_copy->matr[i].a[j] = matrix->matr[i].a[j];
            if (matrix_copy->matr[i].a[j] > max){
                max = matrix_copy->matr[i].a[j];
                idx_max = j;
            }

            if (matrix_copy->matr[i].a[j] < min){
                min = matrix_copy->matr[i].a[j];
                idx_min = j;
            }

        }
        matrix_copy->matr[i].a[idx_max] = min;
        matrix_copy->matr[i].a[idx_min] = max;
    }
    return(matrix_copy);
}

