#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "hash.h"
#include "file.h"

#define SIZE 6000

static void query_word(const Hash *h);

int main()
{
	char *word = (char*)malloc(sizeof(char) * 50);
	char *notes = (char*)malloc(sizeof(char) * 100);

	Hash *h = create_hash(SIZE);

	file_to_hash("Englishwords.txt", word, notes, h);

	free(word);
	free(notes);

	printf("单词总数 : %d\n单词哈希值冲突率: %.2f%%\n", 
		 size_hash(), 100 * conflict_rate());

	query_word(h);

	destroy_hash(&h);


	return 0;
}

void query_word(const Hash *h)
{
	char *buf = (char*)malloc(sizeof(char) * 50);

	do {
		printf("\n请输入要查询的单词, 按回车结束 : ");

		fgets(buf, 50, stdin);
		buf[strlen(buf) - 1] = '\0';

		const char *p_notes = word_to_notes(h, buf);

		if (p_notes != NULL)
		{
			printf("\n单词: %s\n注释: %s\n", buf, p_notes);
		}
		else
		{
			printf("未找到所查询的单词 \"%s\"\n", buf);
		}

		printf("\n输入q加回车退出, 按回车继续查询单词: ");	
	} 
	while (strcmp(fgets(buf, 50, stdin), "q\n") != 0);

	free(buf);
}
