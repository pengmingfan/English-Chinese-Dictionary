#include <stdio.h>
#include <string.h>

#include "hash.h"
#include "file.h"

#define SIZE 6000

static void query_word(const Hash *h);

int main()
{
	char word[SIZE][50], notes[SIZE][50], buf[50];

	Hash *h = create_hash(SIZE);

	file_to_hash("Englishwords.txt", word, notes, h);	

	printf("单词总数 : %d\n单词哈希值冲突率: %.2f%%\n", 
		 size_hash(), 100 * conflict_rate());

	query_word(h);

	destroy_hash(&h);

	return 0;
}

void query_word(const Hash *h)
{
	char buf[50];
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
}
