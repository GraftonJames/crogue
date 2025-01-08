
#include "statemachine.h"

#define STATE_TYPE_COUNT 1

int hm_insert(wint_t key, enum actions action, struct wa_vtab *ac_tab);

void no_action(struct game_data *gd) {}

int init_statemachine(struct state_machine *sm)
{
	sm->type = LOCAL_GRID;

	sm->states[LOCAL_GRID].parent = sm;
	sm->states[LOCAL_GRID].print_fn = lg_print; 
	sm->states[LOCAL_GRID].no_action->action = no_action; 
	sm->states[LOCAL_GRID].no_action->next = NULL; 



	return 1;
}

struct action_list
*get_state_action(struct state *s, wint_t key)
{
	if (key < s->min_key || key > s->max_key)
		return s->no_action;
	
	size_t offset = key - s->min_key;
	return &(s->action_vtab[key]);
}

int
unpack_action_tables(
	struct state_machine *st,
	struct action_key *km
) {
	return 1;
}
