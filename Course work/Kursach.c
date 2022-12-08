#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct hospitalEmployee{
    char FIO[50];
    int year;
    int month;
    int numberofDays;
    int daysMissedDuetoIllness;
    float paymentinOneDay;                                                                                                                                                        
}a[100];

struct users{
    char login[15];
    char password[15];
    int role;
}a1[2];
// Вход
void pass(int *k){
    int n, stop;
    char login[15], password[15];
    struct users a1[]={"admin", "admin", 1, "user", "user", 0};
    while (*k==0){
        stop=0;
        printf("Login: ");
        scanf("%s", &login);
        printf("Password: ");
        scanf("%s", &password);
        for (int i=0; i<2; i++){
            if ((a1[i].login==login) && (a1[i].password==password)){
                if (i==0){
                    *k=1;
                    printf("Enter succesful!");
                    break;
                }
                else *k=2;
                printf("Enter succesful!");
                break;
            }
        }
        if (*k==0) printf("\nWrong login or password\n");
        while ((*k==0) && stop!=1){
            printf("1 - Try logging in again\n2 - Exit\n");
            scanf("%d", &n);
            switch (n){
                case 1:
                    stop=1;
                    break;
                case 2:
                    *k=-1;
                    break;
                default:
                    printf("\nWrong number, please try again\n");
            }
        }
    }
}
int main(){
    int k=0;
    pass(&k);
    system("pause");
    return 0;
}