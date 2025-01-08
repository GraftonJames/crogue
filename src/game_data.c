
#include "game_data.h"

struct obj_def seed_protag_def();
struct obj_def seed_wall_def();
struct obj_def seed_floor_def();
int seed_object_def_table(struct obj_def *od); 

int seed_map(struct obj_def *def, struct grid *tm) {

	seed_object_def_table(def);

	tm->height = 25;
	tm->width = 50;

	tm->items = malloc(sizeof(struct item_list *) * tm->height * tm->width);
	for (int x = 0; x < tm->height * tm->width; x++) {
		tm->items[x] = malloc(sizeof(struct item_list));
		tm->items[x]->obj = malloc(sizeof(struct obj));
		if (
			x % tm->width == 0 ||
			x % tm->width == 1 ||
			x < tm->width ||
			x > tm->width * (tm->height - 1)
		) tm->items[x]->obj->def = def + 1;
		else tm->items[x]->obj->def = def + 2;
	}

	struct item_list* t = malloc(sizeof(struct item_list));
	t->obj = malloc(sizeof(struct obj));
	t->obj->def = def;
	t->next = tm->items[25*25 -1];
	tm->items[25*25-1] = t;

	return 0;
}


struct obj_def seed_protag_def() {
	struct obj_def o;
	o.id = OBJ_ID_PROTAG;
	o.paint = malloc(sizeof(cchar_t));
	setcchar(o.paint, L"@", WA_NORMAL, COLOR_PAIR(0), NULL);
	o.type = 0;
	o.flags = 0;
	o.prec = 0;
	return o;
}

struct obj_def seed_wall_def() {
	struct obj_def o;
	o.id = OBJ_ID_WALL;
	o.paint = malloc(sizeof(cchar_t));
	setcchar(o.paint, L"#", WA_NORMAL, COLOR_PAIR(0), NULL);
	o.type = 0;
	o.flags = 0;
	o.prec = 0;
	return o;
}

struct obj_def seed_floor_def() {
	struct obj_def o;
	o.id = OBJ_ID_FLOOR;
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
	return 1;
}


