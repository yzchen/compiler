#include <stdio.h>

int globalint;

double globalfloat;

void printint(){
	printf("globalint : %d \n", globalint);
}

void printfloat(){
	printf("globalfloat : %f \n", globalfloat);
}

void printa(int num){
	printf("num : %d \n", num);
}
