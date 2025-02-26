
#include "game_data.h"

struct obj_def seed_protag_def();
struct obj_def seed_wall_def();
struct obj_def seed_floor_def();
int seed_object_def_table(struct obj_def *od); 

int seed_map(struct game_data *gd) {

	gd->defs = malloc(sizeof(struct obj_def) * 3);
	seed_object_def_table(gd->defs);

	struct grid *grid = &gd->grid;
	struct obj_def *def = gd->defs;

	grid->height = 25;
	grid->width = 50;

	grid->items = malloc(sizeof(struct item_list *) * grid->height * grid->width);
	for (int x = 0; x < grid->height * grid->width; x++) {
		grid->items[x] = malloc(sizeof(struct item_list));
		grid->items[x]->obj = malloc(sizeof(struct obj));
		if (
			x % grid->width == 0 ||
			x % grid->width == 1 ||
			x < grid->width ||
			x > grid->width * (grid->height - 1)
		) grid->items[x]->obj->def = def + 1;
		else grid->items[x]->obj->def = def + 2;
	}

	struct item_list* t = malloc(sizeof(struct item_list));
	t->obj = malloc(sizeof(struct obj));
	t->obj->def = def;
	t->next = grid->items[25*25 -1];
	grid->items[25*25-1] = t;

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


