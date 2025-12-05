#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "program.h"

unsigned int read_input(char* file, char buffer[MAX_LINES][MAX_LINE_LENGTH]) {
  unsigned int line_count = 0;
  FILE *fileptr;

  fileptr = fopen(file, "r");
  if (fileptr == NULL) {
    perror("Error opening file");
    return 0;
  }

  while (line_count < MAX_LINES && fgets(buffer[line_count], MAX_LINE_LENGTH, fileptr) != NULL) {
    buffer[line_count][strcspn(buffer[line_count], "\n")] = 0; // clear out trailing newlines
    line_count++;
  }

  fclose(fileptr);

  return line_count;
}

int main(int argc, char** argv) {
  char buffer[MAX_LINES][MAX_LINE_LENGTH];

  if (argc != 2) {
    printf("Usage - first [INPUT FILE]\n");
    return -1;
  }

  unsigned int line_count = read_input(argv[1], buffer);

  if (line_count <= 0) {
    errno = EINVAL;
    perror("Error reading file contents");
    return -1;
  }

  printf("ROUND 1: %d\r\n", first(START_POS, buffer, line_count));
  printf("ROUND 2: %d\r\n", second(START_POS, buffer, line_count));

  return 0;
}
