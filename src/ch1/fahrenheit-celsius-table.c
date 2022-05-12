#include <stdio.h>
#include <stdlib.h>

int main() {
    /* print Fahrenheit-CelSius table
     *   for fahr = 0, 20, ..., 300 */

    int fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = lower;
    printf("Fahr  CelS\n");
    printf("----  ----\n");
    while (fahr <= upper) {
        celsius = (fahr - 32) * 5 / 9;
        printf("%4d%6d\n", fahr, celsius);
        fahr += step;
    }

    return EXIT_SUCCESS;
}
