#include <stdlib.h>
#include <stdio.h>

static int daytab[][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},    // leap year
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}     // common year
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int leap, *pm;

    leap = (year % 4 == 0 && year % 100) || year % 400 == 0;
    for (pm = *(daytab+leap); pm - *(daytab+leap) < month; pm++)
        day += *pm;
    return day;
}


/* month_day: */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap, *pm;

    leap = (year % 4 == 0 && year % 100) || year % 400 == 0;
    for (pm = *(daytab+leap); yearday > *pm; pm++)
        yearday -= *pm;

    *pmonth = pm - *(daytab+leap);
    *pday = yearday;
}

char *month_name(int);

void show_help_msg(char *name) {
    printf("Usage:\n");
    printf("    %s (<year> <day-of-year> | <year> <month> <day>)\n", name);
    printf("\n");
    printf("    Options:\n");
    printf("        <year> <day-of-year>:\tshow the month and day for the given day-of-year\n");
    printf("        <year> <month> <day>:\tshow the day-of-year for the given month and day\n");
}

int main(int argc, char **argv) {
    if (argc == 3) {
        int month, day;

        month_day(atoi(argv[1]), atoi(argv[2]), &month, &day);
        printf("day %s of %s: %s %d\n", argv[2], argv[1], month_name(month), day);

        return EXIT_SUCCESS;
    }

    if (argc == 4 ) {
        int yearday;

        yearday = day_of_year(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
        printf("%s-%s-%s: %d of %s\n", argv[1], argv[2], argv[3], yearday, argv[1]);

        return EXIT_SUCCESS;
    }

    show_help_msg(argv[0]);
    return EXIT_SUCCESS;
}

/* month_name: return name of n-th month */
char *month_name(int n) {
    static char *name[] = {
        "Illegal month",
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    return (n < 1 || n > 12) ? name[0] : name[n];
}
