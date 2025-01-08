
#include "world_actions.h"

void protag_move_north(struct game_data *g); 
void protag_move_south(struct game_data *g);
void protag_move_east(struct game_data *g);
void protag_move_west(struct game_data *g);
void no_action(struct game_data *g);


void (*wa_action(int code))(struct grid *g) {
	switch (code) {
		case WA_PROTAG_MOVE_N:
			return protag_move_north;
			break;
		case WA_PROTAG_MOVE_S:
			return protag_move_south;
			break;
		case WA_PROTAG_MOVE_E:
			return protag_move_east;
			break;
		case WA_PROTAG_MOVE_W:
			return protag_move_west;
			break;
		default:
			return no_action;
			break;
	}
};

void protag_move_north(struct game_data *gd) {
	struct grid *g = gd->grid;
	for (int i = 0; i < g->width * g->height; i++) {
		if (g->items[i]->obj->def->id == OBJ_ID_PROTAG) {
			struct item_list *protag = g->items[i];
			protag->next = g->items[i - g->width];
			g->items[i - g->width] = protag;
			g->items[i] = g->items[i]->next;
			break;
		}
	}
}
void protag_move_south(struct game_data *gd) {
	for (int i = 0; i < g->width * g->height; i++) {
		if (g->items[i]->obj->def->id == OBJ_ID_PROTAG) {
			struct item_list *protag = g->items[i];
			protag->next = g->items[i + g->width];
			g->items[i + g->width] = protag;
			g->items[i] = g->items[i]->next;
			break;
		}
	}
}
void protag_move_east(struct game_data *gd) {
}
void protag_move_west(struct grid *g) {
}

