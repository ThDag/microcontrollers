#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_bin8(uint8_t n) {
  for (int i = 7; i >= 0; i--) {
    putchar((n & (1 << i)) ? '1' : '0');
  }
  putchar('\n');
}

bool isAnagram(char *s, char *t) {

  int counts[26] = {0};
  // counts[2] = 542;

  if (strlen(s) != strlen(t)) {
    return 0;
  }

  for (int i = 0; i < strlen(s); i++) {
    // printf("%c - ", s[i]);
    // printf("%d - ", s[i] & 0b00011111);
    // printf("%d\n", counts[(s[i] & 0b00011111) - 1]);

    int letterid_s = (s[i] & 0b00011111) - 1;
    int letterid_t = (t[i] & 0b00011111) - 1;

    counts[letterid_s]++;
    counts[letterid_t]--;
  }

  for (int i = 0; i < 26; i++) {
    if (counts[i] != 0)
      return 0;
  }
  return 1;
}

int main() {

  char s[] = "abcdefghijklmnwxybdabdaz";
  char t[] = "abcdefghijklmnwxybdabdaz";

  bool result = isAnagram(s, t);
}
