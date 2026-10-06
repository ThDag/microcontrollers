
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

// int compare(const void *a, const void *b) {
//   uint8_t x = *(const uint8_t *)a;
//   uint8_t y = *(const uint8_t *)b;
//
//   if (x < y) {
//     return -1;
//   }
//   if (x > y) {
//     return 1;
//   }
//   return 0;
// }

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

// bool isAnagram(char *s, char *t) {
//
//   if (strlen(s) != strlen(t))
//     return 0;
//
//   for (int i = 0; i < strlen(t); i++) {
//     bool foundFlag = false;
//     for (int j = 0; j < strlen(s); j++) {
//       if (t[i] == s[j]) {
//
//         s[j] = 127; // 0x7F is ascii DEL which we use for a non character
//         value.
//                     // no specific reason to be DEL
//         foundFlag = true;
//         break;
//       }
//     }
//     if (!foundFlag) {
//       return 0;
//     }
//   }
//   return 1;
// }
//
//
// bool isAnagram(char *s, char *t) {
//
//   if (strlen(s) != strlen(t))
//     return 0;
//
//   qsort(s, strlen(s), sizeof(char), compare);
//   qsort(t, strlen(t), sizeof(char), compare);
//
//   for (int i = 0; i < strlen(s); i++) {
//     if (s[i] != t[i])
//       return 0;
//   }
//   return 1;
// }
