
#include "world_actions.h"

void protag_move_north(struct grid *g); 
void protag_move_south(struct grid *g);
void protag_move_east(struct grid *g);
void protag_move_west(struct grid *g);
void no_action(struct grid *g);

int hm_insert(wint_t key, enum actions action, struct wa_vtab *ac_tab);

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

void no_action(struct grid *g) {}
void protag_move_north(struct grid *g) {
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
void protag_move_south(struct grid *g) {
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
void protag_move_east(struct grid *g) {
}
void protag_move_west(struct grid *g) {
}

size_t
hash_wint(wint_t key) {
	size_t h = 0x243f6 * 2 ^ sizeof(int);
	h = key * h;
	h = h >> (sizeof(size_t) - KEYBIND_HASH_MAP_BITWIDTH);
	h = h % KEYBIND_HASH_MAP_SIZE;
	return (size_t) h;
}

struct action_list
*w_action(wint_t key, struct wa_vtab *wam)
{
	int kh = hash_wint(key);
	int start = kh;

	while (wam[kh].key != key) {
		kh = (kh + 1) % KEYBIND_HASH_MAP_SIZE;
		if (kh == start)
			return NULL;
	}

	return wam[kh].al;
}

int
unpack_action_hashtable(
	int action_type,
	struct wa_vtab *wa,
	struct action_key *km
) {
	int type_cmp = action_type << (sizeof(int)*8 - ACTION_TYPE_MASK_BITS);

	
	int res = 0;
	for (int i = 0; i < ACTION_COUNT; i++) {
		if (type_cmp != (ACTION_TYPE_MASK & km[i].action))
			 continue;

		for (wint_t *k = &km[i].keys[0]; *k != 0; k++) {
			res = hm_insert(*k, km[i].action, wa);
			if (res < 0)
				return res;
		}
	}

	return 1;
}

int
hm_insert (
	wint_t key,
	enum actions code,
	struct wa_vtab *wa
) {
	int kh = hash_wint(key);

	while (wa[kh].key != (wint_t) 0 && wa[kh].key != key)
		kh = (kh + 1) % KEYBIND_HASH_MAP_SIZE;

	if (wa[kh].key == 0)
		wa[kh].key = key;

	struct action_list **ptr = &(wa[kh].al);
	while (*ptr != NULL)
		ptr = &((*ptr)->next);

	*ptr = malloc(sizeof(struct action_list));

	if (*ptr == NULL)
		return -1;

	(*ptr)->action = wa_action(code);

	return 1;
}
