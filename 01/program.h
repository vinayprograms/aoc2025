#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "constants.h"

unsigned int first(unsigned int start_position, const char buffer[MAX_LINES][MAX_LINE_LENGTH], unsigned int line_count);
unsigned int second(unsigned int start_position, const char buffer[MAX_LINES][MAX_LINE_LENGTH], unsigned int line_count);

#endif
