
#include <stdio.h>
#include <math.h>

int main(){
	double x,y;
	
	printf("Enter x: ");
	scanf("%lf",&x);
	
	if(x > 1) 
		y=sqrt(tan(x*x-1));
		
	else if((x >= 0)&&(x <= 1))	
		y=(-2)*x;
		
	else if(x<0)
		y=exp(cos(x));
		
	printf_s("y:%0.6lf", y);
	return 0;
} 