#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define ADDITIONAL_LINES_CAPACITY 2
#define MAX_LINE_LENGTH 256

void cleanup(char** buffer, unsigned int count) {
  if (buffer == NULL)
    return;
  for (unsigned int i = 0; i < count; i++) {
    free(buffer[i]);
  }
  free(buffer);
}

char** read_input(char* file, unsigned int* line_count) {
  size_t lines_capacity = 0;
  FILE *fileptr;
  char** buffer = NULL;
  char temp[MAX_LINE_LENGTH];

  (*line_count) = 0;

  fileptr = fopen(file, "r");
  if (fileptr == NULL) {
    perror("Error opening file");
    return NULL;
  }

  // NOTE: This implementation uses multiple temporary buffers - `temp` and
  // `copy`. The primary intent is to aggressively optimize memory such that
  // only the required space is used before it is copied into `buffer`.
  while (fgets(temp, sizeof(temp), fileptr)) { // read till end of line or max length
    // If we read content from file, expand 'buffer'
    if ((*line_count) >= lines_capacity) {
      lines_capacity = (lines_capacity) ? (lines_capacity + (2 * ADDITIONAL_LINES_CAPACITY)) : ADDITIONAL_LINES_CAPACITY;
      char** new_buf = realloc (buffer, lines_capacity * sizeof(char*));
      if (new_buf == NULL) {
        perror("Something went wrong!");
        fclose(fileptr);
        cleanup(buffer, *line_count);
        return NULL;
      }
      buffer = new_buf;
    }
    size_t len = strcspn(temp, "\n");
    char* copy = malloc(len + 1);
    if (copy == NULL) {
      perror("Something went wrong with malloc");
      fclose(fileptr);
      cleanup(buffer, *line_count);
      return NULL;
    }
    memcpy(copy, temp, len);
    copy[len] = '\0';
    buffer[(*line_count)++] = copy;
  }

  fclose(fileptr);

  return buffer;
}

