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
} employees[100];
struct user
{
    char login[15];
    char password[15];
    int role;
} users[50];
int sizeUsers = 0, sizeEmployee = 0, userNum = 0, role = 0;
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
void userVerification(char *login, char *password)
{
    for (int i = 0; i < sizeUsers; i++)
    {
        if (strcmp(users[i].login, login) == 0 && strcmp(users[i].password, password) == 0)
        {
            userNum = i + 1;
            role = users[i].role;
            printf("Enter successful! Hello %s\n", users[i].login);
        }
    }
}
void pass(int *stopmain)
{
    int n, maxNumofLetters = 15;
    char login[maxNumofLetters], password[maxNumofLetters];
    while (userNum == 0)
    {
        system("cls");
        fflush(stdin);
        role = 0;
        array_nulling(login, &maxNumofLetters);
        array_nulling(password, &maxNumofLetters);
        printf("Login: ");
        scanf("%s", &login);
        printf("Password: ");
        scanf("%s", &password);
        userVerification(login, password);
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
    strcpy(users[0].login, "admin");
    strcpy(users[0].password, "admin");
    users[0].role = 1;
    printf("Admin account was created\nLogin: admin\nPassword: admin\n");
    system("pause");
}
int load()
{
    FILE *fileEmployees = fopen("database.dat", "rb");
    FILE *fileUsers = fopen("users.txt", "r");
    if (fileUsers)
    {
        fscanf(fileUsers, "%d", &sizeUsers);
        fread(&sizeEmployee, sizeof(int), 1, fileEmployees);
        if (sizeUsers > 50)
        {
            printf("The users file is damaged\n");
            system("pause");
            return 1;
        }
        if (sizeEmployee > 100)
        {
            printf("The database is damaged\n");
            system("pause");
            return 1;
        }
        else
        {
            if (sizeUsers > 0)
            {
                for (int i = 0; i < sizeUsers; i++)
                    fscanf(fileUsers, "%s %s %d\n", &users[i].login, &users[i].password, &users[i].role);
            }
            if (sizeEmployee > 0)
                fread(employees, sizeof(struct hospitalEmployee), sizeEmployee, fileEmployees);
        }
        fclose(fileEmployees);
        fclose(fileUsers);
    }
    else
        createAdmin();
    return 0;
}
void save()
{
    FILE *fileEmployees = fopen("database.dat", "wb");
    FILE *fileUsers = fopen("users.txt", "w");
    fprintf(fileUsers, "%d\n", sizeUsers);
    fwrite(&sizeEmployee, sizeof(int), 1, fileEmployees);
    if (sizeUsers > 0)
    {
        for (int i = 0; i < sizeUsers; i++)
        {
            fprintf(fileUsers, "%s %s %d\n", users[i].login, users[i].password, users[i].role);
        }
    }
    if (sizeEmployee > 0)
    {
        fwrite(employees, sizeof(struct hospitalEmployee), sizeEmployee, fileEmployees);
    }
    fclose(fileEmployees);
    fclose(fileUsers);
}
void outputHospitalEmployees(struct hospitalEmployee *array, int *sizeEmployee)
{
    system("cls");
    fflush(stdin);
    if (*sizeEmployee > 0)
    {
        printf("A list of hospital employees:\n");
        for (int i = 0; i < *sizeEmployee; i++)
            printf("%2d. FIO: %-s %-s %-s  Year: %-4d  Month: %-2d  Number of days of absence due to illness: %-2d  Payment in one day: %-4.3f\n", i + 1, (array + i)->surname, (array + i)->name, (array + i)->patronymic, (array + i)->years, (array + i)->months, (array + i)->days, (array + i)->paymentinOneDay);
    }
    else
        printf("There are no hospital employees in the database\n");
}
void outputSpecificHospitalEmployee(int *numOfEmployee)
{
    system("cls");
    fflush(stdin);
    printf("%d.|FIO: %s %s %s | Year: %d | Month: %d | Number of days of absence due to illness: %d | Payment in one day: %.3f|\n", *numOfEmployee, (employees + *numOfEmployee - 1)->surname, (employees + *numOfEmployee - 1)->name, (employees + *numOfEmployee - 1)->patronymic, (employees + *numOfEmployee - 1)->years, (employees + *numOfEmployee - 1)->months, (employees + *numOfEmployee - 1)->days, (employees + *numOfEmployee - 1)->paymentinOneDay);
}
void editHospitalEmployees()
{
    int n, stop = 0, n1, stop1;
    while (stop == 0)
    {
        outputHospitalEmployees(employees, &sizeEmployee);
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
                    outputSpecificHospitalEmployee(&n1);
                    printf("1 - Edit surname\n2 - Edit name\n3 - Edit patronymic\n4 - Edit Number of years of absence due to illness");
                    printf("\n5 - Edit number of month of absence due to illness\n6 - Edit number of days of absence due to illness\n7 - Edit payment in one day\n0 - Exit\n");
                    scanf("%d", &n);
                    switch (n)
                    {
                    case 1:
                        printf("\nEnter new surname: ");
                        scanf("%s", &(employees + n1 - 1)->surname);
                        printf("Surname has been changed\n");
                        break;
                    case 2:
                        printf("\nEnter new name: ");
                        scanf("%s", &(employees + n1 - 1)->name);
                        printf("Name has been changed\n");
                        break;
                    case 3:
                        printf("\nEnter new patronymic: ");
                        scanf("%s", &(employees + n1 - 1)->patronymic);
                        printf("Patronymic has been changed\n");
                        break;
                    case 4:
                        printf("\nEnter new number of years of absence due to illness: ");
                        scanf("%d", &(employees + n1 - 1)->years);
                        printf("Number of years of absence due to illness has been changed\n");
                        break;
                    case 5:
                        printf("\nEnter new number of months of absence due to illness: ");
                        scanf("%d", &(employees + n1 - 1)->months);
                        printf("Number of months of absence due to illness has been changed\n");
                        break;
                    case 6:
                        printf("\nEnter new number of days of absence due to illness: ");
                        scanf("%d", &(employees + n1 - 1)->days);
                        printf("Number of days of absence due to illness has been changed\n");
                        break;
                    case 7:
                        printf("\nEnter new payment in one day: ");
                        scanf("%f", &(employees + n1 - 1)->paymentinOneDay);
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
        outputHospitalEmployees(employees, &sizeEmployee);
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
                    strcpy((employees + i)->surname, (employees + i + 1)->surname);
                    strcpy((employees + i)->name, (employees + i + 1)->name);
                    strcpy((employees + i)->patronymic, (employees + i + 1)->patronymic);
                    (employees + i)->years = (employees + i + 1)->years;
                    (employees + i)->months = (employees + i + 1)->months;
                    (employees + i)->days = (employees + i + 1)->days;
                    (employees + i)->paymentinOneDay = (employees + i + 1)->paymentinOneDay;
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
        scanf("%s", &((users + sizeUsers)->login));
        if (memcmp((users + sizeUsers)->login, "Q", 2) == 0 || memcmp((users + sizeUsers)->login, "q", 2) == 0)
            stop = 2;
        else
            for (i = 0; i < sizeUsers; i++)
            {
                if (strcmp((users + sizeUsers)->login, (users + i)->login) == 0)
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
            scanf("%s", &((users + sizeUsers)->password));
        while (stop == 1)
        {
            printf("Enter Role(1-admin or 2-user): ");
            scanf("%d", &((users + sizeUsers)->role));
            if ((users + sizeUsers)->role == 1 || (users + sizeUsers)->role == 2)
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
        printf("%2d. Login: %-15.15s  Password: %-15.15s  Role: %d\n", i + 1, (users + i)->login, (users + i)->password, (users + i)->role);
}
void addNewHospitalEmployee()
{
    system("cls");
    fflush(stdin);
    printf("Enter FIO: ");
    scanf("%s %s %s", &(employees + sizeEmployee)->surname, &(employees + sizeEmployee)->name, &(employees + sizeEmployee)->patronymic);
    printf("Enter year: ");
    scanf("%d", &((employees + sizeEmployee)->years));
    printf("Enter month: ");
    scanf("%d", &((employees + sizeEmployee)->months));
    printf("Enter number of days of absence due to illness: ");
    scanf("%d", &((employees + sizeEmployee)->days));
    printf("Enter payment in one day: ");
    scanf("%f", &((employees + sizeEmployee)->paymentinOneDay));
    printf("New hospital employee was added\n");
    sizeEmployee++;
    system("pause");
}
void outputSpecificUser(int *numOfUser)
{
    system("cls");
    fflush(stdin);
    printf("%d. Login: %s  Password: %s  Role: %d\n", *numOfUser, (users + *numOfUser - 1)->login, (users + *numOfUser - 1)->password, (users + *numOfUser - 1)->role);
}
void editUsers()
{
    int stop = 0, n, stop1, n1, stop2;
    while (stop == 0)
    {
        outputUsers();
        stop1 = 0;
        stop2 = 0;
        printf("Enter the user's number for edit(0-Exit): ");
        scanf("%d", &n);
        if ((n < 0) || (n > sizeUsers))
            printf("Wrong number, please try again\n");
        else if (n == 0)
            stop = 1;
        else
            while (stop1 == 0)
            {
                outputSpecificUser(&n);
                printf("1 - Edit login\n2 - Edit password\n3 - Edit role\n0 - Exit\n");
                scanf("%d", &n1);
                switch (n1)
                {
                case 1:
                    system("cls");
                    fflush(stdin);
                    printf("Enter new login: ");
                    scanf("%s", &(users + n - 1)->login);
                    printf("Login has been changed\n");
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    fflush(stdin);
                    printf("Enter new password: ");
                    scanf("%s", &(users + n - 1)->password);
                    printf("Password has been changed\n");
                    system("pause");
                    break;
                case 3:
                    while (stop2 == 0)
                    {
                        system("cls");
                        fflush(stdin);
                        printf("Enter new role(1-admin or 2-user): ");
                        scanf("%d", &(users + n - 1)->role);
                        if ((users + n - 1)->role == 1 || (users + n - 1)->role == 2)
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
        else
        {
            for (i = n - 1; i < sizeUsers - 1; i++)
            {
                strcpy((users + i)->login, (users + i + 1)->login);
                strcpy((users + i)->password, (users + i + 1)->password);
                (users + i)->role = (users + i + 1)->role;
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
        if ((employees + i)->years == year && (employees + i)->months == month)
        {
            monthPayment = (30 - (employees + i)->days) * (employees + i)->paymentinOneDay;
            printf("%d. FIO: %s %s %s  Payment: %d\n", i + 1, employees[i].surname, employees[i].name, employees[i].patronymic, monthPayment);
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
        if ((employees + i)->years == year && (employees + i)->months == month)
        {
            totalMonthPayment = totalMonthPayment + (30 - (employees + i)->days) * (employees + i)->paymentinOneDay;
        }
    }
    printf("Total payment: %d\n", totalMonthPayment);
    system("pause");
}
void writeArray(struct hospitalEmployee *array, int *numOfEmployee, int *counter)
{
    strcpy((array + *counter)->surname, (employees + *numOfEmployee)->surname);
    strcpy((array + *counter)->name, (employees + *numOfEmployee)->name);
    strcpy((array + *counter)->patronymic, (employees + *numOfEmployee)->patronymic);
    (array + *counter)->years = (employees + *numOfEmployee)->years;
    (array + *counter)->months = (employees + *numOfEmployee)->months;
    (array + *counter)->days = (employees + *numOfEmployee)->days;
    (array + *counter)->paymentinOneDay = (employees + *numOfEmployee)->paymentinOneDay;
}
void searchEngine(int *n)
{
    char FIO[20];
    struct hospitalEmployee array[100];
    int ymd, numFind, stop = 0, counter = 0;
    float payment;
    system("cls");
    if (sizeEmployee == 0)
        printf("There are no hospital employees in the database\n");
    else if (*n == 1)
    {
        printf("Enter surname for search: ");
        numFind = scanf("%c", &FIO);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (memcmp(employees[i].surname, FIO, numFind) == 0)
            {
                writeArray(array, &i, &counter);
                counter++;
            }
        }
    }
    else if (*n == 2)
    {
        printf("Enter name for search: ");
        numFind = scanf("%s", &FIO);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (memcmp(employees[i].name, FIO, numFind) == 0)
            {
                writeArray(array, &i, &counter);
                counter++;
            }
        }
    }
    else if (*n == 3)
    {
        printf("Enter patronymic for search: ");
        numFind = scanf("%s", &FIO);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (memcmp(employees[i].patronymic, FIO, numFind) == 0)
            {
                writeArray(array, &i, &counter);
                counter++;
            }
        }
    }
    else if (*n == 4)
    {
        printf("Enter year for search: ");
        scanf("%d", &ymd);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (employees[i].years == ymd)
            {
                writeArray(array, &i, &counter);
                counter++;
            }
        }
    }
    else if (*n == 5)
    {
        while (stop == 0)
        {
            printf("Enter month for search: ");
            scanf("%d", &ymd);
            if (ymd < 1 || ymd > 12)
                printf("Wrong number, please try again");
            else
                for (int i = 0; i < sizeEmployee; i++)
                {
                    if (employees[i].months == ymd)
                    {
                        writeArray(array, &i, &counter);
                        counter++;
                    }
                }
            stop = 1;
        }
    }
    else if (*n == 6)
    {
        printf("Enter number of days of absence due to illness for search: ");
        scanf("%d", &ymd);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (employees[i].days == ymd)
            {
                writeArray(array, &i, &counter);
                counter++;
            }
        }
    }
    else if (*n == 7)
    {
        printf("Enter paymention in one day for search: ");
        scanf("%f", &payment);
        for (int i = 0; i < sizeEmployee; i++)
        {
            if (employees[i].paymentinOneDay == payment)
            {
                writeArray(array, &i, &counter);
                counter++;
            }
        }
    }
    if (counter > 0)
        outputHospitalEmployees(array, &counter);
    printf("Number of matches: %d\n", counter);
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
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            searchEngine(&n);
            break;
        case 0:
            stop = 1;
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
void arrayCopy(struct hospitalEmployee *array)
{
    for (int i = 0; i < sizeEmployee; i++)
    {
        strcpy(array[i].surname, employees[i].surname);
        strcpy(array[i].name, employees[i].name);
        strcpy(array[i].patronymic, employees[i].patronymic);
        array[i].years = employees[i].years;
        array[i].months = employees[i].months;
        array[i].days = employees[i].days;
        array[i].paymentinOneDay = employees[i].paymentinOneDay;
    }
}
void swap(struct hospitalEmployee *array, int *num, int *i)
{
    char temp[20];
    int temp1;
    strcpy(temp, (array + *i)->surname);
    strcpy((array + *i)->surname, (array + *num)->surname);
    strcpy((array + *num)->surname, temp);
    strcpy(temp, (array + *i)->name);
    strcpy((array + *i)->name, (array + *num)->name);
    strcpy((array + *num)->name, temp);
    strcpy(temp, (array + *i)->patronymic);
    strcpy((array + *i)->patronymic, (array + *num)->patronymic);
    strcpy((array + *num)->patronymic, temp);
    temp1 = (array + *i)->years;
    (array + *i)->years = (array + *num)->years;
    (array + *num)->years = temp1;
    temp1 = (array + *i)->months;
    (array + *i)->months = (array + *num)->months;
    (array + *num)->months = temp1;
    temp1 = (array + *i)->days;
    (array + *i)->days = (array + *num)->days;
    (array + *num)->days = temp1;
    temp1 = (array + *i)->paymentinOneDay;
    (array + *i)->paymentinOneDay = (array + *num)->paymentinOneDay;
    (array + *num)->paymentinOneDay = temp1;
}
void sortEngine(int *n, int *n1, struct hospitalEmployee *array)
{
    int i, k, num;
    for (i = 0; i < sizeEmployee - 1; i++)
    {
        num = i;
        for (k = i + 1; k < sizeEmployee; k++)
        {
            if (*n1 == 1)
            {
                if (*n == 1 && memcmp((array + num)->surname, (array + k)->surname, 1) < 0)
                    num = k;
                else if (*n == 2 && memcmp((array + num)->name, (array + k)->name, 1) < 0)
                    num = k;
                else if (*n == 3 && memcmp((array + num)->patronymic, (array + k)->patronymic, 1) < 0)
                    num = k;
                else if (*n == 4 && (array + num)->years > (array + k)->years)
                    num = k;
                else if (*n == 5 && (array + num)->months > (array + k)->months)
                    num = k;
                else if (*n == 6 && (array + num)->days > (array + k)->days)
                    num = k;
                else if (*n == 7 && (array + num)->paymentinOneDay > (array + k)->paymentinOneDay)
                    num = k;
            }
            else if (*n1 == 2)
            {
                if (*n == 1 && memcmp((array + num)->surname, (array + k)->surname, 1) > 0)
                    num = k;
                else if (*n == 2 && memcmp((array + num)->name, (array + k)->name, 1) > 0)
                    num = k;
                else if (*n == 3 && memcmp((array + num)->patronymic, (array + k)->patronymic, 1) > 0)
                    num = k;
                else if (*n == 4 && (array + num)->years < (array + k)->years)
                    num = k;
                else if (*n == 5 && (array + num)->months < (array + k)->months)
                    num = k;
                else if (*n == 6 && (array + num)->days < (array + k)->days)
                    num = k;
                else if (*n == 7 && (array + num)->paymentinOneDay < (array + k)->paymentinOneDay)
                    num = k;
            }
            if (num != i)
                swap(array, &num, &i);
        }
    }
}
void sortBy()
{
    int stop = 0, n, n1, stop1 = 0;
    struct hospitalEmployee array[100];
    arrayCopy(array);
    while (stop == 0)
    {
        stop1 = 0;
        system("cls");
        printf("1 - Sort by surname\n2 - Sort by name\n3 - Sort by patronymic\n4 - Sort by year\n5 - Sort by month\n6 - Sort by number of days of absence due to illness\n7 - Sort by paymention in one day\n0 - Exit\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            while (stop1 == 0)
            {
                system("cls");
                printf("1 - Ascending\n2 - Descending\n");
                scanf("%d", &n1);
                if (n1 == 1 || n1 == 2)
                    stop1 = 1;
                else
                    printf("Wrong number, please try again");
            }
            sortEngine(&n, &n1, array);
            outputHospitalEmployees(array, &sizeEmployee);
            system("pause");
            break;
        case 0:
            stop = 1;
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
void userList()
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
            editUsers();
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
        printf("1 - Add hospital employee\n2 - Edit hospital employee\n3 - Delete hospital employee\n4 - Display hospital employees\n5 - Display a list of payments to hospital employees\n6 - Display the total amount of payments to hospital employees\n7 - Search\n8 - Sort by\n0 - Exit\n");
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
            outputHospitalEmployees(employees, &sizeEmployee);
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
        case 8:
            sortBy();
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
        printf("1 - Display hospital employees\n2 - Display a list of payments to hospital employees\n3 - Display the total amount of payments to hospital employees\n4 - Search\n0 - Log out\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            outputHospitalEmployees(employees, &sizeEmployee);
            system("pause");
            break;
        case 2:
            outputAlistOfPayments();
            break;
        case 3:
            outputTotalAmountofPayments();
            break;
        case 4:
            search();
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
            userList();
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
    int stopmain = 0;
    if (load() == 0)
    {
        while (stopmain == 0)
        {
            system("cls");
            fflush(stdin);
            pass(&stopmain);
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