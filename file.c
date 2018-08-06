#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file.h"

static void line_to_word_notes(const char *line, char *word, char *notes);

void file_to_hash(const char* filename, char *word, char *notes, Hash *h)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror(filename);
		exit(0);
	}
	
	char line[100];
	while (fgets(line, 100, fp) != NULL)
	{
		if (strchr(line, '\n') != NULL)
		{
			line[strlen(line) - 1] = '\0';
		}
	
		if (strchr(line, '.') != NULL)
		{
			line_to_word_notes(line, word, notes);
			insert_hash(h, word, notes);
		}
	}

	fclose(fp);
}

void line_to_word_notes(const char *line, char *word, char *notes)
{
	int i = 0, j = 0;

	while (line[i] == ' ')
	{
		++i;
	}

	while (line[i] != ' ')
	{
		word[j++] = line[i++];
	}
	word[j] = '\0';
	
	while (line[i] == ' ')
	{
		++i;
	}

	j = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		notes[j++] = line[i++];
	}	
	notes[j] = '\0';
}
