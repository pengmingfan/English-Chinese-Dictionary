#ifndef FILE_H
#define FILE_H

#include "hash.h"

void file_to_hash(const char* filename, char (*word)[50], 
	char (*notes)[50], Hash *h);

#endif
