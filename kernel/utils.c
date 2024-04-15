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

  /* TODO: implement "reverse" */
}

void memory_copy(char *src, char *dst, int len) {
  int i;
  for (i = 0; i < len; i++) {
    *(dst + i) = *(src + i);
  }
}
