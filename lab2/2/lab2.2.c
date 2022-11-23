#include <stdio.h>
#include <stdlib.h>
int main(){
	int n;
	printf("Enter age: ");
	scanf("%d",&n);
	if ((n>0) && (n<=13))
		printf("Boy\n");
	else if ((n>=14) && (n<=20))
		printf("Young man\n");
	else if ((n>=21) && (n<=70))
		printf("Man\n");
	else if (n>70)
		printf("The elder\n");
	else 
		printf("Invalid value\n");
	system("pause");
	return 0;
} 