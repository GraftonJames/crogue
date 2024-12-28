#ifndef MAPPER_H_
#define MAPPER_H_

#include "object.h"

struct tile {
	obj *o;
	tile *next;
};

struct tile_map {
	short h;
	short w;
	tile *t;
}

#endif MAPPER_H_
