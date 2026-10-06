#include <stdio.h>

int main() {
  int a = 45;
  int *p = &a;
  printf("pointer; %p\n", p);
  printf("int; %i\n", *p);
  printf("int; %i\n", a);
  printf("int; %i\n", 421);
}
