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
    int n;
    bool stop;
    char login[15], password[15];
    struct users a1[]={"admin", "admin", 1, "user", "user", 0};
    while (*k==0){
        stop=false;
        printf("Login: ");
        scanf("%s", &login);
        printf("Password: ");
        scanf("%s", &password);
        if ((a1[0].login==login) && (a1[0].password==password)){
            *k=1;
            printf("Enter succesful!");
        }
        for (int i=0; i<2; i++){
            if ((a1[i].login==login) && (a1[i].password==password)){
                if (i==0){
                    *k=1;
                    break;
                }
                else *k=2;
                printf("Enter succesful!");
            }
        }
        while ((*k==0) && !stop){
            printf("Wrong login or password\n1 - Try again\n2 - Exit\n");
            scanf("%d", &n);
            switch (n){
                case 1:
                    stop=true;
                    break;
                case 2:
                    *k=-1;
                    break;
                default:
                    printf("Wrong number");
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