#ifndef TEXT_H
#define TEXT_H
#include <stdio.h>
#include <string.h>

#define MAX_STR_LENGTH 300

size_t num_of_symbols(const char* name_of_file);
char* text_reader(FILE* file, const char* name_of_file);
int stricmp(const char* source1, const char* source2);

#endif
