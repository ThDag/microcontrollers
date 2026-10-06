#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPalindrome(int x) {

  if (x < 0) {
    return false;
  }

  // convert int to string
  char *buf = malloc(12);
  sprintf(buf, "%d", x);

  for (int i = 0; i < strlen(buf) / 2; i++) {
    if (!(buf[i] == buf[strlen(buf) - 1 - i])) {
      return false;
    }
    // printf("%d - %lu\n", i, strlen(buf) - 1 - i);
    // printf("%c - %c\n", buf[i], buf[strlen(buf) - 1 - i]);
  }

  return true;
}

int main() {

  int x = 987606789;

  bool result = isPalindrome(x);

  printf("%d", result);
}
