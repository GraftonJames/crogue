
#ifndef WORLD_ACTION_H_
#define WORLD_ACTION_H_

#include "common.h"
#include "keymapper.h"
#include "mapper.h"

struct action_list {
	void (*action)(struct grid *);
	struct action_list* next;
};

struct wa_vtab {
	wint_t key;
	struct action_list *al;
};

int unpack_action_hashtable(
	int action_type,
	struct wa_vtab *wa,
	struct action_key *km
); 

struct action_list *w_action(wint_t key, struct wa_vtab *wam);
void (*wa_action(int code))(struct grid *g); 

#endif
