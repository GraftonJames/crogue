
#include "local_grid_state.h"

int split_states_km(struct action_key *km, struct action_key **spl_km);

void get_min_max_keycodes(struct action_key *km, wint_t *min, wint_t *max);
void no_action(struct state *s, struct game_data *gd) {}

int init_statemachine(struct state_machine *sm, struct action_key *km)
{	
	struct action_key **states_km;
	if (split_states_km(km, states_km) == -1)
		return -1;

	for (int i = 0; i < STATE_COUNT; i++)
		attach_km(sm->states[i], i, states_km[i]);
	

	sm->cur_name = LOCAL_GRID;
	sm->cur = &sm->states[LOCAL_GRID];

	sm->states[LOCAL_GRID].parent = sm;
	sm->states[LOCAL_GRID].print_fn = LOCAL_GRID_print; 
	sm->states[LOCAL_GRID].a_vtab = 

	return 1;
}

int
split_states_km(
	struct action_key *km,
	struct action_key **spl_km
) {
	spl_km = malloc(STATE_COUNT * sizeof(struct action_key *));
	
	for (int i=0; i < STATE_COUNT; i++)
		spl_km[i] = calloc(ACTION_COUNT, sizeof(struct action_key));

	int ins_index[STATE_COUNT] = {0};
	for (int i = 0; i < ACTION_COUNT; i++) {
		enum state_names sn = km[i].action >> (sizeof(int)*8 - STATE_MASK_BITS);	
		int j = ins_index[sn]++;
		if (j == ACTION_COUNT)
			return -1;
		spl_km[sn][j] = km[i];
	}

	return 1;
}

int 
attach_km(struct state *s, enum state_names sn, struct action_key *km)
{
	wint_t *min = &s->a_vtab.min_key;
	wint_t *max = &s->a_vtab.max_key;
	get_min_max_keycodes(km, min, max);
	
	struct action_list al = s->get_action;

}

void
get_min_max_keycodes(struct action_key *km, wint_t *min, wint_t *max)
{
	for (int i = 0; i < ACTION_COUNT; i++) {
		for (
			int j = 0;
			j < MAX_KEYS_PER_ACTION && km[i].keys[j] != 0;
			j++
		) {
			*min = *min < km[i].keys[j] ? *min : km[i].keys[j];	
			*max = *max > km[i].keys[j] ? *max : km[i].keys[j];	
		}


	}
}

int init_state_branch(
	enum state_names st,
	struct state *s,
	struct action_key (*km)[STATE_COUNT]
) {
	switch (st) {
		case LOCAL_GRID:
			LOCAL_GRID_state_init(s, km[LOCAL_GRID]);
			return 1;
		default:
			return -1;
	}
}

struct action_list
*get_state_action(struct state *s, wint_t key)
{
	struct action_vtab *a_vtab = &s->a_vtab;
	if (key < a_vtab->min_key || key > a_vtab->max_key)
		return a_vtab->no_action;
	
	size_t offset = key - a_vtab->min_key;
	return &(a_vtab->vtab[key]);
}

int
unpack_action_tables(
	struct state_machine *st,
	struct action_key *km
) {
	return 1;
}
