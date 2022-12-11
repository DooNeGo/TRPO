#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void array_output(int *array, int *size){
    for (int i=0; i<*size; i++){
        printf("%3d", *(array+i));
    }
}
void prod_evenNum(int *array, int *size, int *prod){
    *prod=1;
    for (int i=1; i<*size; i+=2){
        *prod=*prod**(array+i);
    }
}
void findFirst_zeroElem(int *array, int *size, int *num1_zeroElem){
    for (int i=0; i<*size; i++){
        if (*(array+i)==0){
            *num1_zeroElem=i;
            break;
        }
    }
}
void findLast_zeroElem(int *array, int *size, int *num2_zeroElem){
    for (int i=*size-1; i>=0; i--){
        if (*(array+i)==0){
            *num2_zeroElem=i;
            break;
        }
    }
}
void array_generate(int *array, int *size, int *num1_zeroElem, int *num2_zeroElem, int *prod){
	srand(time(0));
    while ((*num1_zeroElem==-1 || *num2_zeroElem==-1) || (*num1_zeroElem==*num2_zeroElem) || (*prod==0)){
	    for(int i=0; i<*size; i++){
		    *(array+i)=rand()%10;
        }
        *prod=1;
        *num1_zeroElem=-1;
        *num2_zeroElem=-2;
        prod_evenNum(array, size, prod);
        findFirst_zeroElem(array, size, num1_zeroElem);
        findLast_zeroElem(array, size, num2_zeroElem);
	}
}
void sum_arrayElem_firstNlast_zeroElem(int *array, int *size, int *num1_zeroElem, int *num2_zeroElem){
    int sum=0, i;
        for (i=*num1_zeroElem+1; i<*num2_zeroElem; i++){
            sum=sum+*(array+i);
        }
        printf("The sum of the array elements located between the first and the last zero elements: %d\n", sum);
}
void selectionSort(int *array, int *size){
    int i, min=*array, j, tmp;
    for (i=0; i<*size-1; i++){
        min=i;
        for (j=i+1; j<*size; j++){
            if (*(array+min)<*(array+j)){
                min=j;
            }
        }
        tmp=*(array+i);
        *(array+i)=*(array+min);
        *(array+min)=tmp;
    }
}
int main(){
    int n, num1_zeroElem=-1, num2_zeroElem=-1, prod=1;
    printf("Enter dimension of the array: ");
    scanf("%d", &n);
    int *array=(int*)calloc(n, sizeof(int));
    printf("Generated array: \n");
    array_generate(array, &n, &num1_zeroElem, &num2_zeroElem, &prod);
    array_output(array, &n);
    printf("\nThe product of even numbers: %d\n", prod);
    sum_arrayElem_firstNlast_zeroElem(array, &n, &num1_zeroElem, &num2_zeroElem);
    selectionSort(array, &n);
    printf("Sorted array: \n");
    array_output(array, &n);
    printf("\n");
    system("pause");
    return 0;
}