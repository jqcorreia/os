int strlen(char *str) {
  int a = 0;

  while (*(str++) != '\0') {
    a++;
  }
  return a;
}

/* K&R */
void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
  int i, sign;
  if ((sign = n) < 0)
    n = -n;
  i = 0;
  do {
    str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0)
    str[i++] = '-';
  str[i] = '\0';

  reverse(str);
}

void memory_copy(char *src, char *dst, int len) {
  int i;
  for (i = 0; i < len; i++) {
    *(dst + i) = *(src + i);
  }
}
