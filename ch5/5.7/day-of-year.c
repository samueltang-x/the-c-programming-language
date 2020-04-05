#include <stdlib.h>
#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int leap, i;

    leap = (year % 4 == 0 && year % 100) || year % 400 == 0;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}


/* month_day: */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap, i;

    leap = (year % 4 == 0 && year % 100) || year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;
}

char *month_name(int);

int main(int argc, char **argv) {
    if (argc == 3) {
        int month, day;

        month_day(atoi(argv[1]), atoi(argv[2]), &month, &day);
        printf("day %s of %s: %s %d\n", argv[2], argv[1], month_name(month), day);        
    }

    if (argc == 4 ) {
        int yearday;

        yearday = day_of_year(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
        printf("%s-%s-%s: %d of %s\n", argv[1], argv[2], argv[3], yearday, argv[1]);
    }
}

/* month_name: return name of n-th month */
char *month_name(int n) {
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };

    return (n < 1 || n > 12) ? name[0] : name[n];
}
