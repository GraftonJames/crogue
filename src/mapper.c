#include "mapper.h"

cchar_t* get_tile_paint(struct obj *o); 
struct obj_def seed_protag_def();
struct obj_def seed_wall_def();
struct obj_def seed_floor_def();
int seed_object_def_table(struct obj_def *od); 

cchar_t* get_tile_paint(struct obj *o) {
	return o->def->paint;
}

int seed_map(struct obj_def *def, struct tile_map *tm) {

	printf("entered seed_map");
	seed_object_def_table(def);

	printf("done");
	tm->height = 50;
	tm->width = 50;
	tm->tiles = malloc(sizeof(struct tile_link) * tm->height * tm->width);
	for (int x = 0; x < tm->height * tm->width; x++) {
		tm->tiles[x].obj = malloc(sizeof(struct obj));
		if (
			x % tm->width == 0 ||
			x % tm->width == 1 ||
			x < tm->width ||
			x > tm->width * (tm->height -1)
		) tm->tiles[x].obj->def = def + 1;
		else tm->tiles[x].obj->def = def + 2;
	}

	tm->tiles[25*25-1].next = malloc(sizeof(struct tile_link));
	tm->tiles[25*25-1].next->obj = malloc(sizeof(struct obj));
	tm->tiles[25*25-1].next->obj->def = def;

	return 0;
}


struct obj_def seed_protag_def() {
	struct obj_def o;
	o.paint = malloc(sizeof(cchar_t));
	setcchar(o.paint, L"@", WA_NORMAL, COLOR_PAIR(0), NULL);
	o.type = 0;
	o.flags = 0;
	o.prec = 0;
	return o;
}

struct obj_def seed_wall_def() {
	struct obj_def o;
	o.paint = malloc(sizeof(cchar_t));
	setcchar(o.paint, L"#", WA_NORMAL, COLOR_PAIR(0), NULL);
	o.type = 0;
	o.flags = 0;
	o.prec = 0;
	return o;
}

struct obj_def seed_floor_def() {
	struct obj_def o;
	o.paint = malloc(sizeof(cchar_t));
	setcchar(o.paint, L".", WA_NORMAL, COLOR_PAIR(0), NULL);
	o.type = 0;
	o.flags = 0;
	o.prec = 0;
	return o;
}

int seed_object_def_table(struct obj_def *od) {
	*od = seed_protag_def();
	*(od + 1) = seed_wall_def();
	*(od + 2) = seed_floor_def();
}


