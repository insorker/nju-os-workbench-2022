#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  perror(argv[0]);
  exit(EXIT_FAILURE);
}
