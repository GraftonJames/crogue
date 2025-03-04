
#include "local_grid_state.h"

int split_states_km(struct action_key *km, struct action_key **spl_km);

void get_min_max_keycodes(struct action_key *km, wint_t *min, wint_t *max);
int attach_km(struct state *s, enum state_names sn, struct action_key *km);

void no_action(struct state *s, struct game_data *gd) {}

int
init_statemachine(struct state_machine *sm, struct action_key *km)
{	
	sm->cur_name = LOCAL_GRID;
	sm->states = calloc(STATE_COUNT, sizeof(struct state));
	sm->cur = &sm->states[LOCAL_GRID];

	sm->states[LOCAL_GRID].parent = sm;
	sm->states[LOCAL_GRID].print_fn = LOCAL_GRID_print;
	sm->states[LOCAL_GRID].get_action_fn = LOCAL_GRID_get_action;

	struct action_key **states_km = calloc(STATE_COUNT, sizeof(struct action_key *));
	if (split_states_km(km, states_km) == -1)
		return -1;

	for (int i = 0; i < STATE_COUNT; i++)
		attach_km(&sm->states[i], i, states_km[i]);

	return 1;
}

int
split_states_km(
	struct action_key *km,
	struct action_key **spl_km
) {
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
attach_action_to_keys(
	void (*action)(struct state *, struct game_data *),
	wint_t keys[MAX_KEYS_PER_ACTION],
	struct state *s
) {
	wint_t min = s->a_vtab.min_key;
	wint_t max = s->a_vtab.max_key;
	struct action_list **vt = s->a_vtab.vtab;

	for (int i = 0; i < MAX_KEYS_PER_ACTION && keys[i] != 0; i++) {
		printf("attaching action to key %c index %i\n" , (char) keys[i], keys[i] - min);
		struct action_list **ptr = &vt[keys[i] - min];
		while (*ptr != NULL)
			ptr = &(*ptr)->next;
		
		*ptr = malloc(sizeof(struct action_list));
		(*ptr)->action = action;
		(*ptr)->next = NULL;
	}
	return 1;
}

int 
attach_km(struct state *s, enum state_names sn, struct action_key *km)
{
	wint_t *min = &s->a_vtab.min_key;
	*min = WINT_MAX;
	wint_t *max = &s->a_vtab.max_key;
	*max = 0;
	get_min_max_keycodes(km, min, max);

	s->a_vtab.vtab = calloc(*max - *min, sizeof(struct action_list *));

	for (int i = 0; i < ACTION_COUNT; i++) {
		printf("getting action code %i with key %c\n", km[i].action, (char) km[i].keys[0]);
		void (*action)(struct state *, struct game_data *) = s->get_action_fn(km[i].action);
		attach_action_to_keys(action, km[i].keys, s);
	}

	return 1;
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

struct action_list
*get_state_action(struct state *s, wint_t key)
{
	printf("getting action for %c\n", (char) key);
	struct action_vtab *a_vtab = &(s->a_vtab);
	if (key < a_vtab->min_key || key > a_vtab->max_key)
		return NULL;
	
	size_t offset = key - a_vtab->min_key;
	return a_vtab->vtab[offset];
}

int
unpack_action_tables(
	struct state_machine *st,
	struct action_key *km
) {
	return 1;
}

void
printf_state_machine_debug(struct state_machine *sm)
{
	struct action_vtab vt; 
	for (int i = 0; i < STATE_COUNT; i++) {

		vt = sm->states[i].a_vtab;
		printf("actions for state %d\n", i);

		for (int j = 0; j <=  vt.max_key - vt.min_key; j++) {
			if (vt.vtab[j] == NULL ) {
				printf("NO ACTION FOR KEY %c\n", (char) j + vt.min_key);
			} else {
				printf("ACTIONS FOR KEY %c\n", (char) j + vt.min_key);
			}
		}
		
	}

}
