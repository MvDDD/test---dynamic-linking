#include <stdint.h>

typedef struct {
	void *item;
	uint32_t hash;
} hitem_t;

typedef struct {
	hitem_t *items;
	uint32_t size;
	uint32_t usedItems;
	void (*add)(hashtable_t,hitem_t);
	 (*remove)(hashtable_t,hitem_t);
	int (*has)(hashtable_t,hitem_t);
	hitem_t *(*get)(hashtable_t,hitem_t);
} hashtable_t;

hashtable_t createHashTable();