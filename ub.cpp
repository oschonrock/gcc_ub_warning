#include "fmt/core.h"

int main(int argc, [[may_unused]] char* argv[]) {
  fmt::println("%d", argc);
}  
