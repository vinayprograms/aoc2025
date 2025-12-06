#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include "program.h"

//***************************************
// Internal functions

static unsigned int turn_left(unsigned int* current, unsigned int distance) {
  unsigned int crossover_count = 0;

  if ( (*current) == 0)
    (*current) = 100; // Set it to the max value of the dial.

  while (distance > 0) {
    if ( distance < (*current) ) {
      (*current) = (*current) - distance;
      distance = 0;
    } else {
      distance = distance - (*current);
      (*current) = 100;
      crossover_count++;
    }
  }

  if ( (*current) == 100)
    (*current) = 0;

  return crossover_count;
}

static unsigned int turn_right(unsigned int* current, unsigned int distance) {
  unsigned int crossover_count = 0;
  while (distance > 0) {
    if ( distance < 100 - (*current) ) {
      (*current) = (*current) + distance;
      distance = 0;
    } else {
      distance = distance - 100 + (*current);
      (*current) = 0;
      crossover_count++;
    }
  }
  return crossover_count;
}

static unsigned int turn(unsigned int* current, char direction, unsigned int distance) {
  switch (direction) {
    case 'L': return turn_left(current, distance);
    case 'R': return turn_right(current, distance);
    default: printf("Unknown direction"); return 0;
  }
}

//***************************************
// Exported functions (see header file)

unsigned int first(unsigned int start_position, char **buffer, unsigned int line_count) {
  unsigned int password = 0;

  for (unsigned int i = 0; i < line_count; i++) {
    if (strcmp(buffer[i], "") == 0) { // Empty string
      printf("Empty line... skipping!");
      continue;
    }
    unsigned int len = strlen(buffer[i]);
    if (len < 2) {
      printf("Invalid line: '%s'", buffer[i]);
      continue;
    }
    char direction = buffer[i][0];
    errno = 0;
    unsigned int clicks = (unsigned int) strtoul(&buffer[i][1], NULL, 10);
    if (clicks == 0) // If invalid input or input said 'zero clicks', skip
      continue;
    if (clicks == UINT_MAX && errno == ERANGE) // If value overflows (we only expect UINT in input), skip
      continue;
    //printf("POS: %d, DIR: %c, CLICKS: %d\r\n", start_position, direction, clicks);
    turn(&start_position, direction, clicks);
    if (start_position == 0)
      password++;
  }
  return password;
}

unsigned int second(unsigned int start_position, char **buffer, unsigned int line_count) {
  unsigned int password = 0;

  for (unsigned int i = 0; i < line_count; i++) {
    if (strcmp(buffer[i], "") == 0) { // Empty string
      printf("Empty line... skipping!");
      continue;
    }
    unsigned int len = strlen(buffer[i]);
    if (len < 2) {
      printf("Invalid line: '%s'", buffer[i]);
      continue;
    }
    char direction = buffer[i][0];
    errno = 0;
    unsigned int clicks = strtoul(&buffer[i][1], NULL, 10);
    if (clicks == 0) // If invalid input or input said 'zero clicks', skip
      continue;
    if (clicks == UINT_MAX && errno == ERANGE) // If value overflows (we only expect UINT in input), skip
      continue;
    //printf("POS: %d, DIR: %c, CLICKS: %d\r\n", start_position, direction, clicks);
    password += turn(&start_position, direction, clicks);
  }
  return password;
}
