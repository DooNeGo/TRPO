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
};
struct users
{
    char login[30];
    char password[30];
    int role;
};
void array_nulling(char *array, int *size)
{
    for (int i = 0; i < *size; i++)
    {
        *(array + i) = 0;
    }
}
void pass(int *role, struct users *a1, int *sizeUsers, int *stopmain, int *userNum)
{
    int n, stop, maxNumofLetters = 30;
    char login[maxNumofLetters], password[maxNumofLetters];
    *userNum = 0;
    while (*userNum == 0)
    {
        stop = 0;
        array_nulling(login, &maxNumofLetters);
        array_nulling(password, &maxNumofLetters);
        printf("Login: ");
        scanf("%s", &login);
        printf("Password: ");
        scanf("%s", &password);
        for (int i = 0; i < *sizeUsers; i++)
        {
            if (strcmp((a1 + i)->login, login) == 0 && strcmp((a1 + i)->password, password) == 0)
            {
                *userNum = i + 1;
                if ((a1 + i)->role == 1)
                {
                    *role = 1;
                    printf("Enter successful! Hello %s\n", (a1 + i)->login);
                }
                else
                {
                    *role = 2;
                    printf("Enter successful! Hello %s\n", (a1 + i)->login);
                }
            }
        }
        if (*userNum == 0)
            printf("\nWrong login or password\n");
        while ((*userNum == 0) && stop != 1)
        {
            printf("1 - Try log in again\n2 - Close program\n");
            scanf("%d", &n);
            switch (n)
            {
            case 1:
                stop = 1;
                break;
            case 2:
                *userNum = -1;
                *stopmain = 1;
                break;
            default:
                printf("\nWrong number, please try again\n");
            }
        }
    }
    if (*userNum != -1)
        system("pause");
}
void outputHospitalEmployees(struct hospitalEmployee *a, int *sizeEmployee)
{
    if (*sizeEmployee > 0)
    {
        for (int i = 0; i < *sizeEmployee; i++)
        {
            printf("%d.|FIO: %2s %2s %2s | Year: %2d | Month: %2d | Number of days: %2d | Payment in one day: %2.3f|\n", i + 1, (a + i)->surname, (a + i)->name, (a + i)->patronymic, (a + i)->years, (a + i)->months, (a + i)->days, (a + i)->paymentinOneDay);
        }
    }
    else
        printf("\nThere are no hospital employees in the database\n");
}
void editHospitalEmployees(struct hospitalEmployee *a, int *sizeEmployee)
{
    int n, stop = 0, n1, stop1 = 0;
    while (stop == 0)
    {
        outputHospitalEmployees(a, sizeEmployee);
        if (*sizeEmployee > 0)
        {
            printf("Enter the employee's number(0-Exit): ");
            scanf("%d", &n1);
            stop1 = 0;
            if ((n1 < 0) || (n1 > *sizeEmployee))
                printf("\nWrong number, please try again\n");
            else if (n1 == 0)
                stop = 1;
            else
                while (stop1 == 0)
                {
                    printf("1 - Edit surname\n2 - Edit name\n3 - Edit patronymic\n4 - Edit Number of years of absence due to illness");
                    printf("\n5 - Edit number of month of absence due to illness\n6 - Edit number of days of absence due to illness\n7 - Edit payment in one day\n0 - Exit\n");
                    scanf("%d", &n);
                    switch (n)
                    {
                    case 1:
                        printf("\nEnter new surname: ");
                        scanf("%s", &(a + n1 - 1)->surname);
                        printf("Surname has been changed\n");
                        break;
                    case 2:
                        printf("\nEnter new name: ");
                        scanf("%s", &(a + n1 - 1)->name);
                        printf("Name has been changed\n");
                        break;
                    case 3:
                        printf("\nEnter new patronymic: ");
                        scanf("%s", &(a + n1 - 1)->patronymic);
                        printf("Patronymic has been changed\n");
                        break;
                    case 4:
                        printf("\nEnter new number of years of absence due to illness: ");
                        scanf("%d", &(a + n1 - 1)->years);
                        printf("Number of years of absence due to illness has been changed\n");
                        break;
                    case 5:
                        printf("\nEnter new number of months of absence due to illness: ");
                        scanf("%d", &(a + n1 - 1)->months);
                        printf("Number of months of absence due to illness has been changed\n");
                        break;
                    case 6:
                        printf("\nEnter new number of days of absence due to illness: ");
                        scanf("%d", &(a + n1 - 1)->days);
                        printf("Number of days of absence due to illness has been changed\n");
                        break;
                    case 7:
                        printf("\nEnter new payment in one day: ");
                        scanf("%f", &(a + n1 - 1)->paymentinOneDay);
                        printf("Payment in one day has been changed\n");
                        break;
                    case 0:
                        stop1 = 1;
                        break;
                    default:
                        printf("\nWrong number, please try again\n");
                        break;
                    }
                }
        }
        else
            stop = 1;
    }
    system("pause");
}
void deleteHospitalEmployee(struct hospitalEmployee *a, int *sizeEmployee)
{
    int stop = 0, n, i;
    while (stop == 0)
    {
        outputHospitalEmployees(a, sizeEmployee);
        if (*sizeEmployee > 0)
        {
            printf("Enter the employee's number(0-Exit): ");
            scanf("%d", &n);
            if ((n < 0) || (n > *sizeEmployee))
                printf("\nWrong number, please try again\n");
            else if (n == 0)
                stop = 1;
            else if (n == *sizeEmployee)
            {
                printf("Delete hospital employee successfully\n");
                (*sizeEmployee)--;
                system("pause");
            }
            else
            {
                for (i = n - 1; i < *sizeEmployee - 1; i++)
                {
                    strcpy((a + i)->surname, (a + i + 1)->surname);
                    strcpy((a + i)->name, (a + i + 1)->name);
                    strcpy((a + i)->patronymic, (a + i + 1)->patronymic);
                    (a + i)->years = (a + i + 1)->years;
                    (a + i)->months = (a + i + 1)->months;
                    (a + i)->days = (a + i + 1)->days;
                    (a + i)->paymentinOneDay = (a + i + 1)->paymentinOneDay;
                }
                (*sizeEmployee)--;
                printf("Delete hospital employee successfully\n");
            }
        }
        else
            stop = 1;
    }
    system("pause");
}
void addNewUser(struct users *a1, int *sizeUsers)
{
    int i, stop = 0;
    while (stop == 0)
    {
        stop = 1;
        printf("Enter Login (Q(q)-Exit): ");
        scanf("%s", &((a1 + *sizeUsers)->login));
        if (memcmp((a1 + *sizeUsers)->login, "Q", 2) == 0 || memcmp((a1 + *sizeUsers)->login, "q", 2) == 0)
            stop = 2;
        else
            for (i = 0; i < *sizeUsers; i++)
            {
                if (strcmp((a1 + *sizeUsers)->login, (a1 + i)->login) == 0)
                {
                    printf("This login already exists\n");
                    stop = 0;
                    break;
                }
            }
    }
    if (stop == 1)
    {
        printf("Enter Password: ");
        scanf("%s", &((a1 + *sizeUsers)->password));
        while (stop == 1)
        {
            printf("Enter Role(1-admin or 2-user): ");
            scanf("%d", &((a1 + *sizeUsers)->role));
            if ((a1 + *sizeUsers)->role == 1 || (a1 + *sizeUsers)->role == 2)
            {
                printf("New user was added\n");
                (*sizeUsers)++;
                stop = 0;
            }
            else
                printf("\nWrong number of role, please try again\n");
        }
    }
    system("pause");
}
void outputUsers(struct users *a1, int *sizeUsers)
{
    printf("\n");
    for (int i = 0; i < *sizeUsers; i++)
        printf("%d.Login: %s  Password: %s  Role: %d\n", i + 1, (a1 + i)->login, (a1 + i)->password, (a1 + i)->role);
}
void addNewHospitalEmployee(struct hospitalEmployee *a, int *size)
{
    printf("Enter FIO: ");
    scanf("%s %s %s", &(a + *size)->surname, &(a + *size)->name, &(a + *size)->patronymic);
    printf("Enter number of years of absence due to illness: ");
    scanf("%d", &((a + *size)->years));
    printf("Enter number of months of absence due to illness: ");
    scanf("%d", &((a + *size)->months));
    printf("Enter number of days of absence due to illness: ");
    scanf("%d", &((a + *size)->days));
    printf("Enter payment in one day: ");
    scanf("%f", &((a + *size)->paymentinOneDay));
    printf("New hospital employee was added\n");
    (*size)++;
    system("pause");
}
void editUsers(struct users *a1, int *size, int *userNum)
{
    int stop = 0, n, stop1 = 0, n1, stop2 = 0;
    while (stop == 0)
    {
        outputUsers(a1, size);
        printf("Enter the user's number(0-Exit): ");
        scanf("%d", &n);
        if ((n < 0) || (n > *size))
            printf("\nWrong number, please try again\n");
        else if (n == 0)
            stop = 1;
        else if (n == *userNum)
        {
            printf("You can't edit an active user!!!\n");
            system("pause");
        }
        else
            while (stop1 == 0)
            {
                printf("1 - Edit login\n2 - Edit password\n3 - Edit role\n0 - Exit\n");
                scanf("%d", &n1);
                switch (n1)
                {
                case 1:
                    printf("Enter new login: ");
                    scanf("%s", &(a1 + n - 1)->login);
                    printf("Login has been changed\n");
                    break;
                case 2:
                    printf("Enter new password: ");
                    scanf("%s", &(a1 + n - 1)->password);
                    printf("Password has been changed\n");
                    break;
                case 3:
                    while (stop2 == 0)
                    {
                        printf("Enter new role(1-admin or 2-user): ");
                        scanf("%d", &(a1 + n - 1)->role);
                        if ((a1 + n - 1)->role == 1 || (a1 + n - 1)->role == 2)
                            stop2 = 1;
                        else
                            printf("\nWrong number, please try again\n");
                    }
                    printf("Role has been changed\n");
                    break;
                case 0:
                    stop1 = 1;
                    break;
                default:
                    printf("\nWrong number, please try again\n");
                    break;
                }
            }
    }
}
void deleteUser(struct users *a1, int *sizeUsers, int *userNum)
{
    int stop = 0, n, i, k;
    while (stop == 0)
    {
        outputUsers(a1, sizeUsers);
        printf("Enter the user's number(0-Exit): ");
        scanf("%d", &n);
        if ((n < 0) || (n > *sizeUsers))
            printf("\nWrong number, please try again\n");
        else if (n == 0)
            stop = 1;
        else if (n == *userNum)
        {
            printf("You can't delete an active user!!!\n");
            system("pause");
        }
        else if (n == *sizeUsers)
        {
            printf("Delete user successfully\n");
            (*sizeUsers)--;
            system("pause");
        }
        else
        {
            for (i = n - 1; i < *sizeUsers - 1; i++)
            {
                strcpy((a1 + i)->login, (a1 + i + 1)->login);
                strcpy((a1 + i)->password, (a1 + i + 1)->password);
                (a1 + i)->role = (a1 + i + 1)->role;
            }
            (*sizeUsers)--;
            if (*userNum > n)
                (*userNum)--;
            printf("Delete user successfully\n");
            system("pause");
        }
    }
}
void usercapabilities(struct hospitalEmployee *a, int *sizeEmployee)
{
    int stop = 0, n;
    while (stop == 0)
    {
        printf("1 - Display information about hospital employees\n0 - Log out\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            outputHospitalEmployees(a, sizeEmployee);
            system("pause");
            break;
        case 0:
            stop = 1;
            break;
        default:
            printf("Wrong number, please try again\n");
            break;
        }
    }
}
void admincapabilities(struct hospitalEmployee *a, struct users *a1, int *sizeEmployee, int *sizeUsers, int *userNum)
{
    int stop = 0, n;
    while (stop == 0)
    {
        printf("1 - Display information about hospital employees\n2 - Edit information about hospital employees\n3 - Add new user\n4 - Display all users\n5 - Add new hospital employee\n6 - Edit users\n7 - Delete user\n8 - Delete hospital employee\n0 - Log out\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            outputHospitalEmployees(a, sizeEmployee);
            system("pause");
            break;
        case 2:
            editHospitalEmployees(a, sizeEmployee);
            break;
        case 3:
            addNewUser(a1, sizeUsers);
            break;
        case 4:
            outputUsers(a1, sizeUsers);
            system("pause");
            break;
        case 5:
            addNewHospitalEmployee(a, sizeEmployee);
            break;
        case 6:
            editUsers(a1, sizeUsers, userNum);
            break;
        case 7:
            deleteUser(a1, sizeUsers, userNum);
            break;
        case 8:
            deleteHospitalEmployee(a, sizeEmployee);
            break;
        case 0:
            stop = 1;
            break;
        default:
            printf("\nWrong number, please try again\n");
            break;
        }
    }
}
int main()
{
    int role, sizeUsers = 3, n, sizeEmployee = 1, n1, stopmain = 0, userNum = 0;
    struct users a1[10] = {"admin", "admin", 1, "user", "user", 2, "DooNeGo", "DooNeGo", 1};
    struct hospitalEmployee a[15] = {"Kostroma", "Matvey", "Olegovich", 2018, 11, 5, 8.54};
    while (stopmain == 0)
    {
        pass(&role, a1, &sizeUsers, &stopmain, &userNum);
        if (role == 2)
            usercapabilities(a, &sizeEmployee);
        if (role == 1)
            admincapabilities(a, a1, &sizeEmployee, &sizeUsers, &userNum);
        while (userNum != -1)
        {
            printf("1 - Log in\n0 - Close program\n");
            scanf("%d", &n1);
            switch (n1)
            {
            case 1:
                userNum = -1;
                break;
            case 0:
                userNum = -1;
                stopmain = 1;
                break;
            default:
                printf("\nWrong number, please try again\n");
                break;
            }
        }
    }
    return 0;
}