
#include "local_grid_state.h"

void protag_move_north(struct state *s, struct game_data *g); 
void protag_move_south(struct state *s, struct game_data *g);
void protag_move_east(struct state *s, struct game_data *g);
void protag_move_west(struct state *s, struct game_data *g);
void no_action(struct state *s, struct game_data *g);

void LOCAL_GRID_state_init(struct state *s, struct action_key *km)
{
	s->print_fn = LOCAL_GRID_print;
	s->a_vtab.no_action->action = no_action; 
	s->a_vtab.no_action->next = NULL; 
}

void LOCAL_GRID_print(struct state *s, struct game_data *gd)
{
}

void LOCAL_GRID_attach_actions(struct action_vtab *t, struct action_key *state_km) {	
	
}

void (*LOCAL_GRID_get_action(int code))(struct state *s, struct game_data *gd) {
	switch (code) {
		case WA_PROTAG_MOVE_N:
			return protag_move_north;
		case WA_PROTAG_MOVE_S:
			return protag_move_south;
		case WA_PROTAG_MOVE_E:
			return protag_move_east;
		case WA_PROTAG_MOVE_W:
			return protag_move_west;
		default:
			return no_action;
	}
};

void protag_move_north(struct state *s, struct game_data *gd) {
	struct grid *g = &gd->grid;
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
void protag_move_south(struct state *s, struct game_data *gd) {
	struct grid *g = &gd->grid;
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
void protag_move_east(struct state *s, struct game_data *gd) {
}
void protag_move_west(struct state *s, struct game_data *gd) {
}

