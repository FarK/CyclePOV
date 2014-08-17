#include "parser.h"

#include "animation.h"
#include "assert.h"
#include <string.h>
#include <stdlib.h>

//AUX PRIVATE FUNCTIONS
/* Parse the line and fill the "frame" structure */
void parseLine(TCHAR* line, BMP_Frame* frame);

/* Read until reaches EOL or EOF
 * Returns:
 * 	- the number of character of the line
 * 	- -1 if EOF is reached
 */
int readLine(FIL* file, TCHAR* line);

/* Parse file and fill "animation" structure */
void parseIndex(FIL* file){
	TCHAR line[MAX_LINE_LENGTH];
	int lineSize;
	unsigned int i = 0;

	lineSize = readLine(file, &line[0]);
	while(lineSize != -1){
		if(line[0] != COMMENT && lineSize > 0){
			ASSERT(i < MAX_FRAMES);
			parseLine(&line[0], &animation.frames[i++]);
		}
		lineSize = readLine(file, &line[0]);
	}

	animation.nFrames = i;
}

void parseLine(TCHAR* line, BMP_Frame* frame){
	TCHAR* token;

	token = strtok(&line[0], DELIM);
	ASSERT(token);
	frame->times = atoi(token);
	ASSERT(frame->times);

	token = strtok(NULL, DELIM);
	ASSERT(token);
	strcpy(frame->path, token);
}

int readLine(FIL* file, TCHAR* line){
	TCHAR character = EOL;
	UINT read = 0;
	unsigned int i = 0;

	//Read character by character until reaches EOL or EOF
	//CHECK_ERROR(f_read(file, &character, sizeof(character), &read));
	f_read(file, &character, sizeof(character), &read);
	while(read > 0 && character != EOL){
		ASSERT(i < MAX_LINE_LENGTH - 1);
		line[i++] = character;
		CHECK_ERROR(f_read(file, &character, sizeof(character), &read));
	}

	//Set end of string
	line[i] = '\0';

	//Returns -1 if EOF is reached
	return !read? -1 : i;
}
