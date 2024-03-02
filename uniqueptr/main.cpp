#include <iostream>
#include "shaped_ptr.h"

int main() {
  int a = 1;
  int* pa = &a;
  int b = 2;
  int* pb = &b;
  std::swap(pa, pb);
  std::cout << *pb;
}