#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct hospitalEmployee
{
    char surname[20];
    char name[20];
    char patronymic[20];
    int years;
    int months;
    int days;
    float paymentinOneDay;                                                                                                                                                        
}a[50];
struct users
{
    char login[30];
    char password[30];
    int role;
}a1[5];
void array_nulling(char *array, int *size)
{
    for (int i=0; i<*size; i++)
    {
        *(array+i)=0;
    }
}
void pass(int *k, struct users *a1, int *size)
{
    int n, stop, maxNumofLetters=30;
    char login[maxNumofLetters], password[maxNumofLetters];
    while (*k==0)
    {
        array_nulling(login, &maxNumofLetters);
        array_nulling(password, &maxNumofLetters);
        stop=0;
        printf("Login: ");
        scanf("%s", &login);
        printf("Password: ");
        scanf("%s", &password);
        for (int i=0; i<*size; i++)
        {
            if (memcmp((a1+i)->login, login, maxNumofLetters)==0 && memcmp((a1+i)->password, password, maxNumofLetters)==0)
            {
                if (a1[i].role==1)
                {
                    *k=1;
                    printf("Enter succesful!\nYou have entered as admin\n");
                    break;
                }
                else *k=2;
                printf("Enter succesful!\nYou have entered as user\n");
                break;
            }
        }
        if (*k==0) printf("\nWrong login or password\n");
        while ((*k==0) && stop!=1)
        {
            printf("1 - Try logging in again\n2 - Exit\n");
            scanf("%d", &n);
            switch(n)
            {
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
void outputInformationAboutHospitalEmployees(struct hospitalEmployee *a, int *size)
{
    for (int i=0; i<*size; i++)
    {
        printf("%d.|FIO: %2s %2s %2s | Year: %2d | Month: %2d | Number of days: %2d | Payment in one day: %2.3f|\n", i+1, (a+i)->surname, (a+i)->name, (a+i)->patronymic, (a+i)->years, (a+i)->months, (a+i)->days, (a+i)->paymentinOneDay);
    }
}
void editInformationAboutHospitalEmployees(struct hospitalEmployee *a, int *size)
{
    int n, m=0, n1=0, m1=0;
    while (m==0)
    {
        printf("Enter the employee's number(0-Exit): ");
        scanf("%d", &n1);
        m1=0;
        if ((n1<0) || (n1>*size))
        {
            printf("\nWrong number, please try again\n");
        }
        else if (n1==0)
        {
                m=1;     
        }
        else while (m1==0)
        {
            printf("\n1 - Edit surname\n2 - Edit name\n3 - Edit patronymic\n4 - Edit Number of years of absence due to illness");
            printf("\n5 - Edit number of month of absence due to illness\n6 - Edit number of days of absence due to illness\n7 - Edit payment in one day\n0 - Exit\n");
                scanf("%d", &n);
                switch (n)
                {
                    case 1:
                        printf("\nEnter new surname: ");
                        scanf("%s", &(a+n1-1)->surname);
                        break;
                    case 2:
                        printf("\nEnter new name: ");
                        scanf("%s", &(a+n1-1)->name);
                        break;
                    case 3:
                        printf("\nEnter new patronymic: ");
                        scanf("%s", &(a+n1-1)->patronymic);
                        break;
                    case 4:
                        printf("\nEnter new number of years of absence due to illness: ");
                        scanf("%d", &(a+n1-1)->years);
                        break;
                    case 5:
                        printf("\nEnter new number of month of absence due to illness: ");
                        scanf("%d", &(a+n1-1)->months);
                        break;
                    case 6:
                        printf("\nEnter new number of days of absence due to illness: ");
                        scanf("%d", &(a+n1-1)->days);
                        break;
                    case 7:
                        printf("\nEnter new payment in one day: ");
                        scanf("%f", &(a+n1-1)->paymentinOneDay);
                        break;
                    case 0:
                        m1=1;
                        break;
                    default:
                        printf("\nWrong number, please try again\n");
                        break;
                }
            }
        
    }
}
int main()
{
    int k=0, size1, n, size2, m=0;
    struct users a1[]={"admin", "admin", 1, "user", "user", 0};
    size1=sizeof(a1)/sizeof(a1[0]);
    struct hospitalEmployee a[]={"Kostroma", "Matvey", "Olegovich", 2018, 11, 5, 8.54};
    size2=sizeof(a)/sizeof(a[0]);
    pass(&k, a1, &size1);
    system("pause");
    if (k==2)
    {
        while (m==0){
            printf("1 - Display information about hospital employees\n2 - Exit\n");
            scanf("%d", &n);
            switch(n)
            {
                case 1:
                    outputInformationAboutHospitalEmployees(a, &size2);
                    system("pause");
                    break;
                case 2:
                    m=-1;
                    break;
                default:
                    printf("\nWrong number, please try again\n");
                    break;
            }
        }
    }
    if (k==1)
    {
        while (m==0)
        {
            printf("1 - Display information about hospital employees\n2 - Exit\n3 - Edit information about hospital employees\n");
            scanf("%d", &n);
            switch(n)
            {
                case 1:
                    outputInformationAboutHospitalEmployees(a, &size2);
                    system("pause");
                    break;
                case 2:
                    m=1;
                    break;
                case 3:
                    outputInformationAboutHospitalEmployees(a, &size2);
                    editInformationAboutHospitalEmployees(a, &size2);
                    break;
                default:
                    printf("\nWrong number, please try again\n");
                    break;
            }
        }
    }
    system("pause");
    return 0;
}