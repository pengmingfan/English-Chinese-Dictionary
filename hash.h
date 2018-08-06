#ifndef HASH_H
#define HASH_H

typedef struct translate_t
{
	char *word;
	char *notes;
	struct translate_t *next;
} Translate;

typedef struct hash_node_t
{
	Translate *head;
} Hash;

Hash* create_hash(int capacity);
void insert_hash(Hash *h, const char *word, const char *notes);
const char* word_to_notes(const Hash *h, const char* word);
void destroy_hash(Hash **p_h);
double conflict_rate();
int size_hash();

#endif
