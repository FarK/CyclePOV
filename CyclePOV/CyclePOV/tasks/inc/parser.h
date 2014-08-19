#ifndef PARSER_H_
#define PARSER_H_

#include "ff.h"
#include "defines.h"

#define MAX_LINE_LENGTH MAX_PATH_LENGTH + 3 + 10
#define EOL	'\n'
#define DELIM "\t"
#define COMMENT '#'

void parseIndex(FIL* file);

#endif /* PARSER_H_ */
