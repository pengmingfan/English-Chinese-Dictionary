#include <stdio.h>
#include <string.h>

#include "file.h"

static void line_to_word_notes(const char *line, char *word, char *notes);

void file_to_hash(const char* filename, char (*word)[50], 
					char (*notes)[50], Hash *h)
{
	FILE *fp = fopen("Englishwords.txt", "r");

	char line[100];

	int i, j = 0, len;

	while (fgets(line, 100, fp) != NULL)
	{
		len = strlen(line);
		line[len - 1] = '\0';
		--len;
	
		for (i = 0; i < len && line[i] != '.'; ++i)
		{ 
		}

		if (i < len)
		{
			line_to_word_notes(line, word[j], notes[j]);
			insert_hash(h, word[j], notes[j]);
			++j;
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
	while (line[i] != '\0')
	{
		notes[j++] = line[i++];
	}	
}
