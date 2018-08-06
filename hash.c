#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "hash.h"

static int HASH_CAPACITY = 0;
static int HASH_SIZE = 0;
static int HASH_CONFLICT = 0;

static int DJB_hash(const char *str);

Hash* create_hash(int capacity)
{
	Hash *h = (Hash*)malloc(sizeof(Hash) * capacity);
	assert(h != NULL);

	for (int i = 0; i < capacity; ++i)
	{
		(h + i)->head = NULL;
	}
	
	HASH_CAPACITY = capacity;
	
	return h;
}

static int DJB_hash(const char *str)
{
	int hash = 5381; 

    for(int i = 0; i < strlen(str); ++i)  
    {  
       hash = ((hash << 5) + hash) + str[i];  
	}  
    
	return hash;  
}

void insert_hash(Hash *h, const char *word, const char *notes)
{
	int index = abs(DJB_hash(word) % HASH_CAPACITY);
	
	Translate *p = (Translate*)malloc(sizeof(Translate));
	assert(p != NULL);

	p->word = word;
	p->notes = notes;
	p->next = NULL;

	if ((h + index)->head == NULL)
	{
		(h + index)->head = p;
	}
	else
	{
		p->next = (h + index)->head;
		(h + index)->head = p;

		++HASH_CONFLICT;
	}
	
	++HASH_SIZE;
}

const char* word_to_notes(const Hash *h, const char* word)
{
	int index = abs(DJB_hash(word) % HASH_CAPACITY);

	Translate *p = (h + index)->head;
	while (p != NULL && strcmp(p->word, word) != 0)
	{
		p = p->next;
	}

	if (p == NULL)
	{
		return NULL;
	}
	else
	{
		return p->notes;
	}
}

void destroy_hash(Hash **p_h)
{
    for(int i = 0; i < HASH_CAPACITY; ++i)  
    {  
		Translate *p = (*p_h + i)->head;
		Translate *q;
		while (p != NULL)
		{
			q = p->next;
			free(p);
			p = q;
		}
	}  	

	free(*p_h);
	*p_h = NULL;
}

double conflict_rate()
{
	return (double)HASH_CONFLICT / (double)HASH_SIZE;
}

int size_hash()
{
	return HASH_SIZE;
}
