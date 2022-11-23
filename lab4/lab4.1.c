#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main (){
    int v, i, j, n, prod, k1=0, k2=0, sum=0, tmp=0;
    printf("Enter dimension of the array: ");
    scanf("%d", &n);
    int a[n];
    srand(time(0));
    printf("Generated array: \n");
    for (i=0; i<n; i++){
        a[i]=rand()%15+(-5);
        printf("%3d ",a[i]);
    }
    prod=a[1];
    for (i=3; i<n; i=i+2) prod=prod*a[i];
    printf("\nThe product of even numbers: %d\n", prod);
    for (i=0; i<n; i++){
        if (a[i]==0){
            k1=i;
            break;
        }
    }
    for (i=n-1; i>=0; i--){
        if (a[i]==0){
            k2=i;
            break;
        }
    }
    if (k1!=k2){
        for (i=k1+1; i<k2; i++)
            sum=sum+a[i];
        printf("The sum of the array elements located between the first and the last zero elements: %d\n", sum);
    }
    else printf("\nERROR k1=k2 or there are no zero elements in the array \n\n");
    for (i=0; i<n-1; i++){
        v=i;
        for (j=i+1; j<n; j++){
            if (a[v]<a[j]) v=j;
        }
        tmp=a[i];
        a[i]=a[v];
        a[v]=tmp;
    }
    printf("Sorted array: \n");
    for (i=0; i<n; i++)
        printf("%3d", a[i]);
    printf("\n");
    system("pause");
    return 0;
}
