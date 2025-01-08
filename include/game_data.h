#ifndef GAME_DATA_H_
#define GAME_DATA_H_

#include "common.h"

#define TILE_MAP_MAX_HEIGHT 50
#define TILE_MAP_MAX_WIDTH 50

enum obj_prec {
	OBJ_PREC_UNDEF = 0,
	OBJ_PREC_PROTAG = 1
};

enum obj_type {
	OBJ_TYPE_UNDEF = 0,
	OBJ_TYPE_PROTAG = 1
};

enum object_id {
	OBJ_ID_PROTAG,
	OBJ_ID_WALL,
	OBJ_ID_FLOOR,
};

struct obj_def {
	unsigned int id;
	cchar_t *paint;
	char type;
	char flags;
	char prec;
};

struct obj {
	int id;
	struct obj_def *def;
};

struct item_list {
	struct obj *obj;
	struct item_list *next;
};

struct grid {
	short height;
	short width;
	struct item_list **items;
};

struct game_data {
	struct obj_def od;
	struct grid grid;
};

int seed_map(struct obj_def *def, struct grid *tm); 

#endif
