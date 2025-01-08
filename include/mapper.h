#ifndef MAPPER_H_
#define MAPPER_H_

#include "common.h"
#include "object.h"

#define TILE_MAP_MAX_HEIGHT 50
#define TILE_MAP_MAX_WIDTH 50

struct item_list {
	struct obj *obj;
	struct item_list *next;
};

struct grid {
	short height;
	short width;
	struct item_list **items;
};

int seed_map(struct obj_def *def, struct grid *tm); 

#endif
