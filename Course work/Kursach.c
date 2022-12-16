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
} a[100];
struct users
{
    char login[30];
    char password[30];
    int role;
} a1[50];
int sizeUsers = 0, sizeEmployee = 0, userNum = 0;
void array_nulling(char *array, int *size)
{
    for (int i = 0; i < *size; i++)
    {
        *(array + i) = '\000';
    }
}
void logInAgain(int *stopmain)
{
    int n, stop = 0;
    while (stop == 0)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Log in again\n0 - Close program\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            userNum = 0;
            stop = 1;
            break;
        case 0:
            userNum = -1;
            stop = 1;
            *stopmain = 1;
            break;
        default:
            system("cls");
            fflush(stdin);
            printf("Wrong number, please try again\n");
            system("pause");
            break;
        }
    }
}
void userVerification(char *login, char *password, int *role)
{
    for (int i = 0; i < sizeUsers; i++)
    {
        if (strcmp(a1[i].login, login) == 0 && strcmp(a1[i].password, password) == 0)
        {
            userNum = i + 1;
            *role = a1[i].role;
            printf("Enter successful! Hello %s\n", a1[i].login);
        }
    }
}
void pass(int *role, int *stopmain)
{
    int n, stop, maxNumofLetters = 30;
    char login[maxNumofLetters], password[maxNumofLetters];
    while (userNum == 0)
    {
        system("cls");
        fflush(stdin);
        stop = 0;
        *role = 0;
        array_nulling(login, &maxNumofLetters);
        array_nulling(password, &maxNumofLetters);
        printf("Login: ");
        scanf("%s", &login);
        printf("Password: ");
        scanf("%s", &password);
        userVerification(login, password, role);
        if (userNum == 0)
        {
            system("cls");
            fflush(stdin);
            printf("Wrong login or password\n");
            system("pause");
            logInAgain(stopmain);
        }
    }
    if (userNum != -1)
        system("pause");
}
void createAdmin()
{
    sizeUsers++;
    strcpy(a1[0].login, "admin");
    strcpy(a1[0].password, "admin");
    a1[0].role = 1;
    printf("Admin account was created\nLogin: admin\nPassword: admin\n");
    system("pause");
}
int load()
{
    FILE *file = fopen("database.dat", "rb");
    if (file)
    {
        fread(&sizeUsers, sizeof(int), 1, file);
        fread(&sizeEmployee, sizeof(int), 1, file);
        if (sizeUsers > 50 || sizeEmployee > 100)
        {
            printf("The database is damaged\n");
            system("pause");
            return 1;
        }
        else
        {
            if (sizeUsers > 0)
            {
                fread(a1, sizeof(struct users), sizeUsers, file);
            }
            if (sizeEmployee > 0)
            {
                fread(a, sizeof(struct hospitalEmployee), sizeEmployee, file);
            }
        }
        fclose(file);
    }
    else
        createAdmin();
    return 0;
}
void save()
{
    FILE *file = fopen("database.dat", "wb");
    fwrite(&sizeUsers, sizeof(int), 1, file);
    fwrite(&sizeEmployee, sizeof(int), 1, file);
    if (sizeUsers > 0)
    {
        fwrite(a1, sizeof(struct users), sizeUsers, file);
    }
    if (sizeEmployee > 0)
    {
        fwrite(a, sizeof(struct hospitalEmployee), sizeEmployee, file);
    }
    fclose(file);
}
void outputHospitalEmployees()
{
    system("cls");
    fflush(stdin);
    if (sizeEmployee > 0)
    {
        printf("A list of hospital employees:\n");
        for (int i = 0; i < sizeEmployee; i++)
            printf("%d.|FIO: %2s %2s %2s | Year: %2d | Month: %2d | Number of days of absence due to illness: %2d | Payment in one day: %2.3f|\n", i + 1, (a + i)->surname, (a + i)->name, (a + i)->patronymic, (a + i)->years, (a + i)->months, (a + i)->days, (a + i)->paymentinOneDay);
    }
    else
        printf("There are no hospital employees in the database\n");
}
void editHospitalEmployees()
{
    int n, stop = 0, n1, stop1 = 0;
    while (stop == 0)
    {
        outputHospitalEmployees();
        if (sizeEmployee > 0)
        {
            printf("Enter the employee's number(0-Exit): ");
            scanf("%d", &n1);
            stop1 = 0;
            if ((n1 < 0) || (n1 > sizeEmployee))
                printf("Wrong number, please try again\n");
            else if (n1 == 0)
                stop = 1;
            else
                while (stop1 == 0)
                {
                    system("cls");
                    fflush(stdin);
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
                        printf("Wrong number, please try again\n");
                        break;
                    }
                }
        }
        else
        {
            stop = 1;
            system("pause");
        }
    }
}
void deleteHospitalEmployee()
{
    int stop = 0, n, i;
    while (stop == 0)
    {
        outputHospitalEmployees();
        if (sizeEmployee > 0)
        {
            printf("Enter the employee's number(0-Exit): ");
            scanf("%d", &n);
            if ((n < 0) || (n > sizeEmployee))
                printf("Wrong number, please try again\n");
            else if (n == 0)
                stop = 1;
            else if (n == sizeEmployee)
            {
                printf("Delete hospital employee successfully\n");
                sizeEmployee--;
                system("pause");
            }
            else
            {
                for (i = n - 1; i < sizeEmployee - 1; i++)
                {
                    strcpy((a + i)->surname, (a + i + 1)->surname);
                    strcpy((a + i)->name, (a + i + 1)->name);
                    strcpy((a + i)->patronymic, (a + i + 1)->patronymic);
                    (a + i)->years = (a + i + 1)->years;
                    (a + i)->months = (a + i + 1)->months;
                    (a + i)->days = (a + i + 1)->days;
                    (a + i)->paymentinOneDay = (a + i + 1)->paymentinOneDay;
                }
                sizeEmployee--;
                printf("Delete hospital employee successfully\n");
            }
        }
        else
        {
            stop = 1;
            system("pause");
        }
    }
}
void addNewUser()
{
    int i, stop = 0;
    while (stop == 0)
    {
        system("cls");
        fflush(stdin);
        stop = 1;
        printf("Enter Login (Q(q)-Exit): ");
        scanf("%s", &((a1 + sizeUsers)->login));
        if (memcmp((a1 + sizeUsers)->login, "Q", 2) == 0 || memcmp((a1 + sizeUsers)->login, "q", 2) == 0)
            stop = 2;
        else
            for (i = 0; i < sizeUsers; i++)
            {
                if (strcmp((a1 + sizeUsers)->login, (a1 + i)->login) == 0)
                {
                    printf("This login already exists\n");
                    stop = 0;
                    system("pause");
                    break;
                }
            }
    }
    if (stop == 1)
    {
        printf("Enter Password: ");
        scanf("%s", &((a1 + sizeUsers)->password));
        while (stop == 1)
        {
            printf("Enter Role(1-admin or 2-user): ");
            scanf("%d", &((a1 + sizeUsers)->role));
            if ((a1 + sizeUsers)->role == 1 || (a1 + sizeUsers)->role == 2)
            {
                printf("New user was added\n");
                sizeUsers++;
                stop = 0;
                system("pause");
            }
            else
            {
                printf("Wrong number of role, please try again\n");
                system("pause");
            }
        }
    }
}
void outputUsers()
{
    system("cls");
    fflush(stdin);
    printf("A list of users:\n");
    for (int i = 0; i < sizeUsers; i++)
        printf("%d.Login: %s  Password: %s  Role: %d\n", i + 1, (a1 + i)->login, (a1 + i)->password, (a1 + i)->role);
}
void addNewHospitalEmployee()
{
    system("cls");
    fflush(stdin);
    printf("Enter FIO: ");
    scanf("%s %s %s", &(a + sizeEmployee)->surname, &(a + sizeEmployee)->name, &(a + sizeEmployee)->patronymic);
    printf("Enter year: ");
    scanf("%d", &((a + sizeEmployee)->years));
    printf("Enter month: ");
    scanf("%d", &((a + sizeEmployee)->months));
    printf("Enter number of days of absence due to illness: ");
    scanf("%d", &((a + sizeEmployee)->days));
    printf("Enter payment in one day: ");
    scanf("%f", &((a + sizeEmployee)->paymentinOneDay));
    printf("New hospital employee was added\n");
    sizeEmployee++;
    system("pause");
}
void editUsers(int *stopAdmin, int *stopUserList)
{
    int stop = 0, n, stop1 = 0, n1, stop2 = 0;
    while (stop == 0)
    {
        outputUsers();
        printf("Enter the user's number for edit(0-Exit): ");
        scanf("%d", &n);
        if ((n < 0) || (n > sizeUsers))
            printf("Wrong number, please try again\n");
        else if (n == 0)
            stop = 1;
        else
            while (stop1 == 0)
            {
                system("cls");
                fflush(stdin);
                printf("1 - Edit login\n2 - Edit password\n3 - Edit role\n0 - Exit\n");
                scanf("%d", &n1);
                switch (n1)
                {
                case 1:
                    system("cls");
                    fflush(stdin);
                    printf("Enter new login: ");
                    scanf("%s", &(a1 + n - 1)->login);
                    printf("Login has been changed\n");
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    fflush(stdin);
                    printf("Enter new password: ");
                    scanf("%s", &(a1 + n - 1)->password);
                    printf("Password has been changed\n");
                    system("pause");
                    break;
                case 3:
                    while (stop2 == 0)
                    {
                        system("cls");
                        fflush(stdin);
                        printf("Enter new role(1-admin or 2-user): ");
                        scanf("%d", &(a1 + n - 1)->role);
                        if ((a1 + n - 1)->role == 1 || (a1 + n - 1)->role == 2)
                            stop2 = 1;
                        else
                            printf("Wrong number, please try again\n");
                    }
                    printf("Role has been changed\n");
                    system("pause");
                    break;
                case 0:
                    stop1 = 1;
                    break;
                default:
                    system("cls");
                    fflush(stdin);
                    printf("Wrong number, please try again\n");
                    system("pause");
                    break;
                }
            }
        if (n == userNum)
        {
            printf("You have changed the current user, please re-login\n");
            stop = 1;
            stop1 = 1;
            *stopAdmin = 1;
            *stopUserList = 1;
            userNum = -1;
            system("pause");
        }
    }
}
void deleteUser()
{
    int stop = 0, n, i;
    while (stop == 0)
    {
        system("cls");
        fflush(stdin);
        outputUsers();
        printf("Enter the user's number(0-Exit): ");
        scanf("%d", &n);
        if ((n < 0) || (n > sizeUsers))
            printf("Wrong number, please try again\n");
        else if (n == 0)
            stop = 1;
        else if (n == userNum)
        {
            printf("You can't delete an active user!!!\n");
            system("pause");
        }
        else if (n == sizeUsers)
        {
            printf("Delete user successfully\n");
            sizeUsers--;
            system("pause");
        }
        else
        {
            for (i = n - 1; i < sizeUsers - 1; i++)
            {
                strcpy((a1 + i)->login, (a1 + i + 1)->login);
                strcpy((a1 + i)->password, (a1 + i + 1)->password);
                (a1 + i)->role = (a1 + i + 1)->role;
            }
            sizeUsers--;
            if (userNum > n)
                userNum--;
            printf("Delete user successfully\n");
            system("pause");
        }
    }
}
void outputAlistOfPayments()
{
    int year, month, i, monthPayment;
    system("cls");
    fflush(stdin);
    printf("Enter year(Example - 2022): ");
    scanf("%d", &year);
    printf("Enter month(Exmple - 7): ");
    scanf("%d", &month);
    for (i = 0; i < sizeEmployee; i++)
    {
        if ((a + i)->years == year && (a + i)->months == month)
        {
            monthPayment = (30 - (a + i)->days) * (a + i)->paymentinOneDay;
            printf("%d. FIO: %s %s %s  Payment: %d\n", i + 1, a[i].surname, a[i].name, a[i].patronymic, monthPayment);
        }
    }
    system("pause");
}
void outputTotalAmountofPayments()
{
    int year, month, i, totalMonthPayment = 0;
    system("cls");
    fflush(stdin);
    printf("Enter year(Example - 2022): ");
    scanf("%d", &year);
    printf("Enter month(Exmple - 7): ");
    scanf("%d", &month);
    for (i = 0; i < sizeEmployee; i++)
    {
        if ((a + i)->years == year && (a + i)->months == month)
        {
            totalMonthPayment = totalMonthPayment + (30 - (a + i)->days) * (a + i)->paymentinOneDay;
        }
    }
    printf("Total payment: %d\n", totalMonthPayment);
    system("pause");
}
void searchBySurname()
{
    char surname[20];
    system("cls");
    if (sizeEmployee == 0)
        printf("There are no hospital employees in the database\n");
    else
    {
        printf("Enter surname for search: ");
        scanf("%s", &surname);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (strcmp(a[i].surname, surname) == 0)
            {
                printf("%d.|FIO: %2s %2s %2s | Year: %2d | Month: %2d | Number of days of absence due to illness: %2d | Payment in one day: %2.3f|\n", i + 1, (a + i)->surname, (a + i)->name, (a + i)->patronymic, (a + i)->years, (a + i)->months, (a + i)->days, (a + i)->paymentinOneDay);
            }
        }
    }
    system("pause");
}
void searchByName()
{
    char name[20];
    system("cls");
    if (sizeEmployee == 0)
        printf("There are no hospital employees in the database\n");
    else
    {
        printf("Enter name for search: ");
        scanf("%s", &name);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (strcmp(a[i].name, name) == 0)
            {
                printf("%d.|FIO: %2s %2s %2s | Year: %2d | Month: %2d | Number of days of absence due to illness: %2d | Payment in one day: %2.3f|\n", i + 1, (a + i)->surname, (a + i)->name, (a + i)->patronymic, (a + i)->years, (a + i)->months, (a + i)->days, (a + i)->paymentinOneDay);
            }
        }
    }
    system("pause");
}
void searchByPatronymic()
{
    char patronymic[20];
    system("cls");
    if (sizeEmployee == 0)
        printf("There are no hospital employees in the database\n");
    else
    {
        printf("Enter patronymic for search: ");
        scanf("%s", &patronymic);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (strcmp(a[i].patronymic, patronymic) == 0)
            {
                printf("%d.|FIO: %2s %2s %2s | Year: %2d | Month: %2d | Number of days of absence due to illness: %2d | Payment in one day: %2.3f|\n", i + 1, (a + i)->surname, (a + i)->name, (a + i)->patronymic, (a + i)->years, (a + i)->months, (a + i)->days, (a + i)->paymentinOneDay);
            }
        }
    }
    system("pause");
}
void searchByYear()
{
    int year;
    system("cls");
    if (sizeEmployee == 0)
        printf("There are no hospital employees in the database\n");
    else
    {
        printf("Enter year for search: ");
        scanf("%d", &year);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (a[i].years == year)
            {
                printf("%d.|FIO: %2s %2s %2s | Year: %2d | Month: %2d | Number of days of absence due to illness: %2d | Payment in one day: %2.3f|\n", i + 1, (a + i)->surname, (a + i)->name, (a + i)->patronymic, (a + i)->years, (a + i)->months, (a + i)->days, (a + i)->paymentinOneDay);
            }
        }
    }
    system("pause");
}
void searchByMonth()
{
    int month;
    system("cls");
    if (sizeEmployee == 0)
        printf("There are no hospital employees in the database\n");
    else
    {
        printf("Enter month for search: ");
        scanf("%d", &month);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (a[i].months == month)
            {
                printf("%d.|FIO: %2s %2s %2s | Year: %2d | Month: %2d | Number of days of absence due to illness: %2d | Payment in one day: %2.3f|\n", i + 1, (a + i)->surname, (a + i)->name, (a + i)->patronymic, (a + i)->years, (a + i)->months, (a + i)->days, (a + i)->paymentinOneDay);
            }
        }
    }
    system("pause");
}
void searchByDays()
{
    int days;
    system("cls");
    if (sizeEmployee == 0)
        printf("There are no hospital employees in the database\n");
    else
    {
        printf("Enter number of days of absence due to illness for search: ");
        scanf("%d", &days);

        for (int i = 0; i < sizeEmployee; i++)
        {
            if (a[i].days == days)
            {
                printf("%d.|FIO: %2s %2s %2s | Year: %2d | Month: %2d | Number of days of absence due to illness: %2d | Payment in one day: %2.3f|\n", i + 1, (a + i)->surname, (a + i)->name, (a + i)->patronymic, (a + i)->years, (a + i)->months, (a + i)->days, (a + i)->paymentinOneDay);
            }
        }
    }
    system("pause");
}
void searchByPayment()
{
    float payment;
    system("cls");
    if (sizeEmployee == 0)
        printf("There are no hospital employees in the database\n");
    else
    {
        printf("Enter number of days of absence due to illness for search: ");
        scanf("%f", &payment);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (a[i].paymentinOneDay == payment)
            {
                printf("%d.|FIO: %2s %2s %2s | Year: %2d | Month: %2d | Number of days of absence due to illness: %2d | Payment in one day: %2.3f|\n", i + 1, (a + i)->surname, (a + i)->name, (a + i)->patronymic, (a + i)->years, (a + i)->months, (a + i)->days, (a + i)->paymentinOneDay);
            }
        }
    }
    system("pause");
}
void search()
{
    int stop = 0, n, i;
    while (stop == 0)
    {
        system("cls");
        printf("1 - Search by surname\n2 - Search by name\n3 - Search by patronymic\n4 - Search by year\n5 - Search by month\n6 - Search by number of days of absence due to illness\n7 - Search by payment in one day\n0 - Exit\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            searchBySurname();
            break;
        case 2:
            searchByName();
            break;
        case 3:
            searchByPatronymic();
            break;
        case 4:
            searchByYear();
            break;
        case 5:
            searchByMonth();
            break;
        case 6:
            searchByDays();
            break;
        case 7:
            searchByPayment();
            break;
        case 0:
            stop = 1;
            break;
        default:
            printf("Wrong number, please try again\n");
            system("pause");
            break;
        }
    }
}
void userList(int *stopAdmin)
{
    int stop = 0, n;
    while (stop == 0)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Add user\n2 - Edit user\n3 - Delete user\n4 - Display users\n0 - Exit\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            addNewUser();
            break;
        case 2:
            editUsers(stopAdmin, &stop);
            break;
        case 3:
            deleteUser();
            break;
        case 4:
            outputUsers();
            system("pause");
            break;
        case 0:
            stop = 1;
            break;
        default:
            printf("Wrong number, please try again\n");
            system("pause");
            break;
        }
    }
}
void employeeList()
{
    int stop = 0, n;
    while (stop == 0)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Add hospital employee\n2 - Edit hospital employee\n3 - Delete hospital employee\n4 - Display hospital employees\n5 - Display a list of payments to hospital employees\n6 - Display the total amount of payments to hospital employees\n7 - Search\n0 - Exit\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            addNewHospitalEmployee();
            break;
        case 2:
            editHospitalEmployees();
            break;
        case 3:
            deleteHospitalEmployee();
            break;
        case 4:
            outputHospitalEmployees();
            system("pause");
            break;
        case 5:
            outputAlistOfPayments();
            break;
        case 6:
            outputTotalAmountofPayments();
            break;
        case 7:
            search();
            break;
        case 0:
            stop = 1;
            break;
        default:
            printf("Wrong number, please try again\n");
            system("pause");
            break;
        }
    }
}
void usercapabilities()
{
    int stop = 0, n;
    while (stop == 0)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Display hospital employees\n2 - Display a list of payments to hospital employees\n3 - Display the total amount of payments to hospital employees\n0 - Log out\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            outputHospitalEmployees();
            system("pause");
            break;
        case 2:
            outputAlistOfPayments();
            break;
        case 3:
            outputTotalAmountofPayments();
            break;
        case 0:
            stop = 1;
            userNum = 0;
            break;
        default:
            printf("Wrong number, please try again\n");
            break;
        }
    }
}
void admincapabilities()
{
    int stop = 0, n;
    while (stop == 0)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Users\n2 - Hospital employees\n0 - Log out\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            userList(&stop);
            break;
        case 2:
            employeeList();
            break;
        case 0:
            stop = 1;
            userNum = 0;
            break;
        default:
            printf("Wrong number, please try again\n");
            system("pause");
            break;
        }
    }
}
int main()
{
    int role, stopmain = 0;
    if (load() == 0)
    {
        while (stopmain == 0)
        {
            system("cls");
            fflush(stdin);
            pass(&role, &stopmain);
            if (role == 2)
                usercapabilities();
            else if (role == 1)
                admincapabilities();
            if (userNum == 0)
                logInAgain(&stopmain);
        }
        save();
    }
    return 0;
}