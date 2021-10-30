#define MAXLEN 1000

int getline(char *, int);
char *alloc(int);

/* readlines: read inpt lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p; line[MAXLEN];

    nlines = 0;
    while ( (len = getline(line, MAXLEN)) > 0 ) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        }
        else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output lines */
/*
void writelines(char *lineptr[], int nlines) {
    int i;
    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}
// */


/* writelines: write output lines, pointer version */
//*
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}
// */
