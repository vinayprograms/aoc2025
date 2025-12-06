#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "utils.h"
#include "program.h"

#define START_POS 50

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage - first [INPUT FILE]\n");
    return -1;
  }

  unsigned int line_count = 0;

  char** buffer = read_input(argv[1], &line_count);
  if (buffer == NULL) {
    perror("Error in reading from input file");
    return -1;
  }

  if (line_count == 0) {
    errno = EINVAL;
    perror("Error reading file contents");
    return -1;
  }

  printf("ROUND 1: %d\r\n", first(START_POS, buffer, line_count));
  printf("ROUND 2: %d\r\n", second(START_POS, buffer, line_count));

  cleanup(buffer, line_count);

  return 0;
}
