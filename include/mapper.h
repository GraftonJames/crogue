#ifndef MAPPER_H_
#define MAPPER_H_

#include "common.h"

#include "object.h"

#define TILE_MAP_MAX_HEIGHT 50
#define TILE_MAP_MAX_WIDTH 50

struct tile_link {
	struct obj *obj;
	struct tile_link *next;
};

struct tile_map {
	short height;
	short width;
	struct tile_link *tiles;
};

int seed_map(struct obj_def *def, struct tile_map *tm); 

#endif
