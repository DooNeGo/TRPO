#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
struct hospitalEmployee
{
    char surname[20];
    char name[20];
    char patronymic[20];
    int year;
    int month;
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
void nullingArray(char *array, int size)
{
    for (int i = 0; i < size; i++)
        *(array + i) = '\000';
}
void outputMessage(const char *msg)
{
    system("cls");
    fflush(stdin);
    printf("%s\n", msg);
    system("pause");
}
void logInAgain(int *stopmain)
{
    int n;
    while (1)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Log in again\n0 - Close program\n");
        n = 5;
        scanf("%d", &n);
        if (n == 1)
        {
            userNum = 0;
            return;
        }
        else if (n == 0)
        {
            userNum = -1;
            *stopmain = 1;
            return;
        }
        else
        outputMessage("Wrong number, please try again");
    }
}
void verification(char *login, char *password)
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
    char login[15], password[15];
    while (userNum == 0)
    {
        system("cls");
        role = 0;
        nullingArray(login, 15);
        nullingArray(password, 15);
        printf("Login: ");
        scanf("%s", &login);
        printf("Password: ");
        scanf("%s", &password);
        verification(login, password);
        if (userNum == 0)
        {
            outputMessage("Wrong number, please try again");
            logInAgain(stopmain);
        }
    }
    if (userNum != -1)
        system("pause");
}
void createDefaultAdmin()
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
        if (sizeUsers > 0)
        {
            for (int i = 0; i < sizeUsers; i++)
                fscanf(fileUsers, "%s %s %d\n", &users[i].login, &users[i].password, &users[i].role);
        }
        if (sizeEmployee > 0)
            fread(employees, sizeof(struct hospitalEmployee), sizeEmployee, fileEmployees);
        fclose(fileEmployees);
        fclose(fileUsers);
    }
    else
        createDefaultAdmin();
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
            fprintf(fileUsers, "%s %s %d\n", users[i].login, users[i].password, users[i].role);
    }
    if (sizeEmployee > 0)
        fwrite(employees, sizeof(struct hospitalEmployee), sizeEmployee, fileEmployees);
    fclose(fileEmployees);
    fclose(fileUsers);
}
void outputEmployees(struct hospitalEmployee *array, int *sizeEmployee)
{
    system("cls");
    fflush(stdin);
    if (*sizeEmployee > 0)
    {
        printf("A list of hospital employees:\n");
        for (int i = 0; i < *sizeEmployee; i++)
            printf("%2d. FIO: %-s %-s %-s  Year: %-4d  Month: %-2d  Number of days of absence due to illness: %-2d  Payment in one day: %-4.3f\n", i + 1, (array + i)->surname, (array + i)->name, (array + i)->patronymic, (array + i)->year, (array + i)->month, (array + i)->days, (array + i)->paymentinOneDay);
    }
    else
        outputMessage("There are no hospital employees in the database");
}
void outputSpecificHospitalEmployee(int *numOfEmployee)
{
    system("cls");
    printf("%d.|FIO: %s %s %s | Year: %d | Month: %d | Number of days of absence due to illness: %d | Payment in one day: %.3f|\n", *numOfEmployee, (employees + *numOfEmployee - 1)->surname, (employees + *numOfEmployee - 1)->name, (employees + *numOfEmployee - 1)->patronymic, (employees + *numOfEmployee - 1)->year, (employees + *numOfEmployee - 1)->month, (employees + *numOfEmployee - 1)->days, (employees + *numOfEmployee - 1)->paymentinOneDay);
}
int chooseEmployee(int *stopMenu)
{
    int n;
    while (1)
    {
        outputEmployees(employees, &sizeEmployee);
        if (sizeEmployee > 0)
        {
            printf("Enter the employee's number(0 - Return): ");
            scanf("%d", &n);
            if ((n < 0) || (n > sizeEmployee))
            outputMessage("Wrong number, please try again");
            else if (n == 0)
            {
                *stopMenu = 1;
                return n;
            }
            else
                return n;
        }
        else
        {
            system("pause");
            return 0;
        }
    }
}
void editSurname(int *n)
{
    char surname[20];
    nullingArray(surname, 20);
    system("cls");
    printf("Enter new surname(0 - Return): ");
    scanf("%s", &surname);
    if (surname[0] == '0')
        return;
    strcpy(employees[*n - 1].surname, surname);
    outputMessage("Surname has been changed");
}
void editName(int *n)
{
    char name[20];
    nullingArray(name, 20);
    system("cls");
    printf("Enter new name(0 - Return): ");
    scanf("%s", &name);
    if (name[0] == '0')
        return;
    strcpy(employees[*n - 1].name, name);
    outputMessage("Name has been changed");
}
void editPatronymic(int *n)
{
    char patronymic[20];
    nullingArray(patronymic, 20);
    system("cls");
    printf("Enter new patronymic(0 - Return): ");
    scanf("%s", &patronymic);
    if (patronymic[0] == '0')
        return;
    strcpy(employees[*n - 1].patronymic, patronymic);
    outputMessage("Patronymic has been changed");
}
void editYear(int *n)
{
    int year;
    system("cls");
    printf("Enter new year(0 - Return): ");
    scanf("%d", &year);
    if (year == 0)
        return;
    employees[*n - 1].year = year;
    outputMessage("Year has been changed");
}
void editMonth(int *n)
{
    int month;
    system("cls");
    printf("Enter new month(0 - Return): ");
    scanf("%d", &month);
    if (month == 0)
        return;
    employees[*n - 1].month = month;
    outputMessage("Month has been changed");
}
void editDays(int *n)
{
    int days;
    system("cls");
    printf("\nEnter new number of days of absence due to illness(-1 - Return): ");
    scanf("%d", &days);
    if (days == -1)
        return;
    employees[*n - 1].days = days;
    outputMessage("Number of days of absence due to illness has been changed");
}
void editPayment(int *n)
{
    float payment;
    system("cls");
    printf("Enter new payment in one day(0 - Return): ");
    scanf("%f", &payment);
    if (payment == 0)
        return;
    employees[*n - 1].paymentinOneDay = payment;
    outputMessage("Payment in one day has been changed");
}
void editEmployeesMenu()
{
    int stop = 0, n1, n, stop1 = 0;
    while (stop == 0)
    {
        stop1 = 0;
        n = chooseEmployee(&stop);
        if (n != 0)
        {
            while (stop1 == 0)
            {
                outputSpecificHospitalEmployee(&n);
                printf("1 - Edit surname\n2 - Edit name\n3 - Edit patronymic\n4 - Edit number of year\n");
                printf("5 - Edit number of month\n6 - Edit number of days of absence due to illness\n7 - Edit payment in one day\n0 - Return\n");
                n1 = 100;
                scanf("%d", &n1);
                if (n1 == 1)
                    editSurname(&n);
                else if (n1 == 2)
                    editName(&n);
                else if (n1 == 3)
                    editPatronymic(&n);
                else if (n1 == 4)
                    editYear(&n);
                else if (n1 == 5)
                    editMonth(&n);
                else if (n1 == 6)
                    editDays(&n);
                else if (n1 == 7)
                    editPayment(&n);
                else if (n1 == 0)
                    stop1 = 1;
                else
                    outputMessage("Wrong number, please try again");
            }
        }
    }
}
void deleteEmployee()
{
    int stop = 0, n, i;
    while (stop == 0)
    {
        n = chooseEmployee(&stop);
        if (n != 0)
        {
            for (i = n - 1; i < sizeEmployee - 1; i++)
            {
                strcpy((employees + i)->surname, (employees + i + 1)->surname);
                strcpy((employees + i)->name, (employees + i + 1)->name);
                strcpy((employees + i)->patronymic, (employees + i + 1)->patronymic);
                (employees + i)->year = (employees + i + 1)->year;
                (employees + i)->month = (employees + i + 1)->month;
                (employees + i)->days = (employees + i + 1)->days;
                (employees + i)->paymentinOneDay = (employees + i + 1)->paymentinOneDay;
            }
            sizeEmployee--;
            outputMessage("Delete hospital employee successfully");
        }
        else
            stop = 1;
    }
}
int checkRepetition()
{
    for (int i = 0; i < sizeUsers; i++)
    {
        if (strcmp(users[sizeUsers].login, users[i].login) == 0)
        {
            outputMessage("This login already exists");
            return 0;
        }
    }
    return 1;
}
void addUser()
{
    int stop = 0;
    while (stop == 0)
    {
        system("cls");
        fflush(stdin);
        printf("Enter Login (0 - Return): ");
        scanf("%s", &users[sizeUsers].login);
        if (users[sizeUsers].login[0] == '0')
            return;
        else
            stop = checkRepetition();
    }
    printf("Enter Password(0 - Return): ");
    scanf("%s", &users[sizeUsers].password);
    if (users[sizeUsers].password[0] == '0')
        return;
    while (1)
    {
        printf("Enter Role(1 - admin 2 - user 0 - Return): ");
        scanf("%d", &users[sizeUsers].role);
        if (users[sizeUsers].role == 1 || users[sizeUsers].role == 2)
        {
            outputMessage("New user was added");
            sizeUsers++;
            return;
        }
        else if (users[sizeUsers].role == 0)
            return;
        else
            outputMessage("Wrong number, please try again");
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
void addEmployee()
{
    system("cls");
    fflush(stdin);
    printf("Enter FIO(0 - Return): ");
    scanf("%s", &employees[sizeEmployee].surname);
    if (employees[sizeEmployee].surname[0] == '0')
        return;
    scanf("%s", &employees[sizeEmployee].name);
    if (employees[sizeEmployee].name[0] == '0')
        return;
    scanf("%s", &employees[sizeEmployee].patronymic);
    if (employees[sizeEmployee].patronymic[0] == '0')
        return;
    printf("Enter year(0 - Return): ");
    scanf("%d", &employees[sizeEmployee].year);
    if (employees[sizeEmployee].year == 0)
        return;
    printf("Enter month(0 - Return): ");
    scanf("%d", &employees[sizeEmployee].month);
    if (employees[sizeEmployee].month == 0)
        return;
    printf("Enter number of days of absence due to illness(-1 - Return): ");
    scanf("%d", &employees[sizeEmployee].days);
    if (employees[sizeEmployee].days == -1)
        return;
    printf("Enter payment in one day(0 - Return): ");
    scanf("%f", &employees[sizeEmployee].paymentinOneDay);
    if (employees[sizeEmployee].paymentinOneDay == 0)
        return;
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
int chooseUser(int *stopMenu)
{
    int n;
    while (1)
    {
        outputUsers();
        if (sizeUsers > 0)
        {
            printf("Enter the users's number(0 - Return): ");
            n = 101;
            scanf("%d", &n);
            if ((n < 0) || (n > sizeUsers))
                outputMessage("Wrong number, please try again");
            else if (n == 0)
            {
                *stopMenu = 1;
                return n;
            }
            else
                return n;
        }
        else
        {
            system("pause");
            return 0;
        }
    }
}
void editLogin(int *n)
{
    char login[15];
    nullingArray(login, 15);
    system("cls");
    printf("Enter new login(0 - Return): ");
    scanf("%s", &login);
    if (login[0] == '0')
        return;
    strcpy(users[*n - 1].login, login);
    outputMessage("Login has been changed");
}
void editPassword(int *n)
{
    char password[15];
    nullingArray(password, 15);
    system("cls");
    printf("Enter new password(0 - Return): ");
    scanf("%s", &password);
    if (password[0] == '0')
        return;
    strcpy(users[*n - 1].password, password);
    outputMessage("Password has been changed\n");
}
void editRole(int *n)
{
    int role;
    while (1)
    {
        fflush(stdin);
        system("cls");
        printf("Enter new role(1 - admin 2 - user 0 - Return): ");
        scanf("%d", &role);
        if (role == 0)
            return;
        else if (role == 1 || role == 2)
        {
            users[*n - 1].role = role;
            outputMessage("Role has been changed");
            return;
        }
        else
            outputMessage("Wrong number, please try again");
    }
}
void editUsers()
{
    int stop = 0, n, n1;
    while (stop == 0)
    {
        n = chooseUser(&stop);
        if (n != 0)
        {
            while (1)
            {
                outputSpecificUser(&n);
                printf("1 - Edit login\n2 - Edit password\n3 - Edit role\n0 - Return\n");
                scanf("%d", &n1);
                if (n1 == 1)
                    editLogin(&n);
                else if (n1 == 2)
                    editPassword(&n);
                else if (n1 == 3)
                    editRole(&n);
                else if (n1 == 0)
                    return;
                else
                    outputMessage("Wrong number, please try again");
            }
        }
    }
}
void deleteUser()
{
    int stop = 0, n, i;
    while (stop == 0)
    {
        n = chooseUser(&stop);
        if (n != 0 && n != userNum)
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
            outputMessage("Delete user successfully");
            system("pause");
        }
        else if (n == userNum)
            outputMessage("You can't delete an active user!!!");
    }
}
int enterYearMonth(int *year, int *month)
{
    system("cls");
    printf("Enter year(Example - 2022 | 0 - Return): ");
    scanf("%d", year);
    if (*year == 0)
        return 0;
    while (1)
    {
        system("cls");
        printf("Enter month(Example - 7 | 0 - Return): ");
        scanf("%d", month);
        if (*month == 0)
            return 0;
        else if (*month < 1 || *month > 12)
            outputMessage("Wrong number, please try again");
        else
            return 1;
    }
}
void outputAlistOfPayments()
{
    int year, month, i, monthPayment, counter = 0;
    if (enterYearMonth(&year, &month) == 1)
    {
        for (i = 0; i < sizeEmployee; i++)
        {
            if ((employees + i)->year == year && (employees + i)->month == month)
            {
                monthPayment = (30 - (employees + i)->days) * (employees + i)->paymentinOneDay;
                counter++;
                printf("%d. FIO: %s %s %s  Payment: %d\n", i + 1, employees[i].surname, employees[i].name, employees[i].patronymic, monthPayment);
            }
        }
        if (counter == 0)
            outputMessage("There is no information for this request");
        else
            system("pause");
    }
}
void outputTotalAmountofPayments()
{
    int year, month, i, totalMonthPayment = 0;
    if (enterYearMonth(&year, &month) == 1)
    {
        for (i = 0; i < sizeEmployee; i++)
        {
            if ((employees + i)->year == year && (employees + i)->month == month)
            {
                totalMonthPayment = totalMonthPayment + (30 - (employees + i)->days) * (employees + i)->paymentinOneDay;
            }
        }
        printf("Total month payment: %d\n", totalMonthPayment);
        system("pause");
    }
}
void writeArray(struct hospitalEmployee *array, int *numOfEmployee, int *counter)
{
    strcpy((array + *counter)->surname, (employees + *numOfEmployee)->surname);
    strcpy((array + *counter)->name, (employees + *numOfEmployee)->name);
    strcpy((array + *counter)->patronymic, (employees + *numOfEmployee)->patronymic);
    (array + *counter)->year = (employees + *numOfEmployee)->year;
    (array + *counter)->month = (employees + *numOfEmployee)->month;
    (array + *counter)->days = (employees + *numOfEmployee)->days;
    (array + *counter)->paymentinOneDay = (employees + *numOfEmployee)->paymentinOneDay;
}
void searchMatches(struct hospitalEmployee *array, char *FIO, int *n, int *ymd, float *payment)
{
    int counter = 0, numLetters;
    numLetters = strlen(FIO);
    for (int i = 0; i < sizeEmployee; i++)
    {
        if ((memcmp(employees[i].surname, FIO, numLetters) == 0 && *n == 1) || (memcmp(employees[i].name, FIO, numLetters) == 0 && *n == 2) || (memcmp(employees[i].patronymic, FIO, numLetters) == 0 && *n == 3) || (employees[i].year == *ymd && *n == 4) || (employees[i].month == *ymd && *n == 5) || (employees[i].days == *ymd && *n == 6) || (employees[i].paymentinOneDay == *payment && *n == 7))
        {
            writeArray(array, &i, &counter);
            counter++;
        }
    }
    if (counter > 0)
        outputEmployees(array, &counter);
    printf("Number of matches: %d\n", counter);
    system("pause");
}
void searchEngine(int *n)
{
    char FIO[20];
    struct hospitalEmployee array[100];
    int ymd, stop = 0, flag = 0;
    float payment;
    if (sizeEmployee == 0)
        outputMessage("There are no hospital employees in the database\n");
    else
    {
        while (stop == 0)
        {
            system("cls");
            fflush(stdin);
            if (*n == 1)
                printf("Enter surname for search(0 - Return): ");
            else if (*n == 2)
                printf("Enter name for search(0 - Return): ");
            else if (*n == 3)
                printf("Enter patronymic for search(0 - Return): ");
            else if (*n == 4)
                printf("Enter year for search(0 - Return): ");
            else if (*n == 5)
                printf("Enter month for search(0 - Return): ");
            else if (*n == 6)
                printf("Enter number of days of absence due to illness for search(0 - Return): ");
            else if (*n == 7)
                printf("Enter paymention in one day for search(0 - Return): ");
            if (*n > 0 && *n < 4)
                scanf("%s", &FIO);
            else if (*n > 3 && *n < 7)
                scanf("%d", &ymd);
            else if (*n == 7)
                scanf("%f", &payment);
            if ((*n > 0 && *n < 4 && FIO[0] == '0') || (*n > 3 && *n < 8 && ymd == 0))
            {
                flag = 1;
                return;
            }
            else if (*n == 5 && (ymd < 1 || ymd > 12) || (*n == 6 && (ymd < 1 || ymd > 31)))
                outputMessage("Wrong number, please try again");
            else
                stop = 1;
        }
        if (flag == 0)
            searchMatches(array, FIO, n, &ymd, &payment);
    }
}
void search()
{
    int n;
    while (1)
    {
        system("cls");
        printf("1 - Search by surname\n2 - Search by name\n3 - Search by patronymic\n4 - Search by year\n5 - Search by month\n6 - Search by number of days of absence due to illness\n7 - Search by payment in one day\n0 - Return\n");
        scanf("%d", &n);
        if (n > 0 && n < 8)
            searchEngine(&n);
        else if (n == 0)
            return;
        else
            outputMessage("Wrong number, please try again");
    }
}
void copyArray(struct hospitalEmployee *array)
{
    for (int i = 0; i < sizeEmployee; i++)
    {
        strcpy(array[i].surname, employees[i].surname);
        strcpy(array[i].name, employees[i].name);
        strcpy(array[i].patronymic, employees[i].patronymic);
        array[i].year = employees[i].year;
        array[i].month = employees[i].month;
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
    temp1 = (array + *i)->year;
    (array + *i)->year = (array + *num)->year;
    (array + *num)->year = temp1;
    temp1 = (array + *i)->month;
    (array + *i)->month = (array + *num)->month;
    (array + *num)->month = temp1;
    temp1 = (array + *i)->days;
    (array + *i)->days = (array + *num)->days;
    (array + *num)->days = temp1;
    temp1 = (array + *i)->paymentinOneDay;
    (array + *i)->paymentinOneDay = (array + *num)->paymentinOneDay;
    (array + *num)->paymentinOneDay = temp1;
}
void sortAscendingDescending(int *n)
{
    while (1)
    {
        fflush(stdin);
        system("cls");
        printf("1 - Ascending\n2 - Descending\n0 - Return\n");
        scanf("%d", n);
        if (*n == 1 || *n == 2 || *n == 0)
            return;
        else
            outputMessage("Wrong number, please try again");
    }
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
                else if (*n == 4 && (array + num)->year > (array + k)->year)
                    num = k;
                else if (*n == 5 && (array + num)->month > (array + k)->month)
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
                else if (*n == 4 && (array + num)->year < (array + k)->year)
                    num = k;
                else if (*n == 5 && (array + num)->month < (array + k)->month)
                    num = k;
                else if (*n == 6 && (array + num)->days < (array + k)->days)
                    num = k;
                else if (*n == 7 && (array + num)->paymentinOneDay < (array + k)->paymentinOneDay)
                    num = k;
            }
        }
        if (num != i)
            swap(array, &num, &i);
    }
}
void sortBy()
{
    int n, n1;
    struct hospitalEmployee array[100];
    copyArray(array);
    while (1)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Sort by surname\n2 - Sort by name\n3 - Sort by patronymic\n4 - Sort by year\n5 - Sort by month\n6 - Sort by number of days of absence due to illness\n7 - Sort by payment in one day\n0 - Return\n");
        scanf("%d", &n);
        if (n > 0 && n < 8)
        {
            sortAscendingDescending(&n1);
            if (n1 != 0)
            {
                sortEngine(&n, &n1, array);
                outputEmployees(array, &sizeEmployee);
                system("pause");
            }
        }
        else if (n == 0)
            return;
        else
            outputMessage("Wrong number, please try again");
    }
}
void userList()
{
    int n;
    while (1)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Add user\n2 - Edit user\n3 - Delete user\n4 - Display users\n0 - Return\n");
        scanf("%d", &n);
        if (n == 1)
            addUser();
        else if (n == 2)
            editUsers();
        else if (n == 3)
            deleteUser();
        else if (n == 4)
        {
            outputUsers();
            system("pause");
        }
        else if (n == 0)
            return;
        else
            outputMessage("Wrong number, please try again");
    }
}
void employeeList()
{
    int n;
    while (1)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Add hospital employee\n2 - Edit hospital employee\n3 - Delete hospital employee\n4 - Display hospital employees\n5 - Display a list of payments to hospital employees\n6 - Display the total amount of payments to hospital employees\n7 - Search\n8 - Sort by\n0 - Return\n");
        n = 20;
        scanf("%d", &n);
        if (n == 1)
            addEmployee();
        else if (n == 2)
            editEmployeesMenu();
        else if (n == 3)
            deleteEmployee();
        else if (n == 4)
        {
            outputEmployees(employees, &sizeEmployee);
            system("pause");
        }
        else if (n == 5)
            outputAlistOfPayments();
        else if (n == 6)
            outputTotalAmountofPayments();
        else if (n == 7)
            search();
        else if (n == 8)
            sortBy();
        else if (n == 0)
            return;
        else
            outputMessage("Wrong number, please try again");
    }
}
void userMenu()
{
    int n;
    while (1)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Display hospital employees\n2 - Display a list of payments to hospital employees\n3 - Display the total amount of payments to hospital employees\n4 - Search\n5 - Sort by\n0 - Log out\n");
        n = 10;
        scanf("%d", &n);
        if (n == 1)
        {
            outputEmployees(employees, &sizeEmployee);
            system("pause");
        }
        else if (n == 2)
            outputAlistOfPayments();
        else if (n == 3)
            outputTotalAmountofPayments();
        else if (n == 4)
            search();
        else if (n == 5)
            sortBy();
        else if (n == 0)
        {
            userNum = 0;
            return;
        }
        else
            outputMessage("Wrong number, please try again");
    }
}
void adminMenu()
{
    int stop = 0, n;
    while (1)
    {
        system("cls");
        fflush(stdin);
        printf("1 - Users\n2 - Hospital employees\n0 - Log out\n");
        n = 10;
        scanf("%d", &n);
        if (n == 1)
            userList();
        else if (n == 2)
            employeeList();
        else if (n == 0)
        {
            userNum = 0;
            return;
        }
        else
            outputMessage("Wrong number, please try again");
    }
}
int main()
{
    int stopmain = 0;
    if (load() == 0)
    {
        while (stopmain == 0)
        {
            pass(&stopmain);
            if (role == 2)
                userMenu();
            else if (role == 1)
                adminMenu();
            if (userNum == 0)
                logInAgain(&stopmain);
        }
        save();
    }
    return 0;
}