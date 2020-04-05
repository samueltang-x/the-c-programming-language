#include <stdio.h>

#define MAXLEN 1000
#define MAXREVERSE 10

int get_line(char s[], int lim);
void reverse_line(char s[], int len);

int main() {
  char line[MAXLEN];

  while ( get_line(line, MAXLEN) > 0 ) {
    reverse_line(line, MAXREVERSE); 
    printf("%s", line);
  }

  return 0;
}

int get_line(char s[], int lim) {
  int i, c;
  for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n')
    s[i++] = c;

  s[i] = '\0';
  return i;
}

void reverse_line(char s[], int lim) {
  int i = 0;
  char r[lim];
  int c;
  short has_newline = 0;

  while (i < lim && (r[i] = s[i]) != '\0') {
    ++i;
  }

  --i;

  int j = 0;
  while (i >=0) {
    c = r[i];
    if (c == '\n')
      has_newline = 1;
    else {
      s[j] = c;
      ++j;
    }
    --i;
  }

  if (has_newline) {
    s[j] = '\n';
    ++j;
  }

  s[j] = '\0';

}
