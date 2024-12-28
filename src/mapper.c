
#include <ncursesw/ncurses.h>
#include "mapper.h"
#include "object.h"


cchar_t get_tile_paint(tile *t) {
	if (tile.o != NULL)
		return title.o.paint;

	return 0;
}

int seed_map(tile_map *tm) {

	tm 
}


struct obj_def seed_protag_def() {
	struct obj_def o;
	setchar(&(o.paint), L"@", WA_NORMAL, COLOR_PAIR(0), NULL);
	o.type = 0;
	o.flags = 0;
	o.prec = 0;
	return o;
}

struct obj_def seed_wall_def() {
	struct obj_def o;
	setchar(&(o.paint), L"#", WA_NORMAL, COLOR_PAIR(0), NULL);
	o.type = 0;
	o.flags = 0;
	o.prec = 0;
	return o;
}

struct obj_def seed_floor_def() {
	struct obj_def o;
	setchar(&(o.paint), L".", WA_NORMAL, COLOR_PAIR(0), NULL);
	o.type = 0;
	o.flags = 0;
	o.prec = 0;
	return o;
}

int seed_object_def_table(obj_def *od) {
	*od = seed_protag_def();
	*(od + 1) = seed_wall_def();
	*(od + 2) = seed_floor_def();
}


