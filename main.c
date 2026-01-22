#include <stdio.h>
#include "my_struct.h"

int main(){
	Matrix matr = {0, NULL};
	if(input(&matr) == 0){
		printf("%s\n", "End of file occured");
		erase(&matr);
		return 1;
	}
	output("Start matrix", matr);
	Matrix* res = func(&matr);
	output("Result matrix", *res);
	erase(&matr);
	erase(res);
	return 0;
}
