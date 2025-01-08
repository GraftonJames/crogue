#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "common.h"
#include "game_data.h"
#include "keymapper.h"

struct action_list;
struct action_vtab;
struct state;
struct state_machine;

struct action_list {
	void (*action)(struct state *, struct game_data *);
	struct action_list* next;
};

struct action_vtab {
	wint_t min_key;
	wint_t max_key;
	struct action_list *vtab;
	struct action_list *no_action;
};

struct state {
	struct state_machine *parent;
	void (*print_fn)(struct state *, struct game_data *);
	void (*(*get_action_fn)(enum actions))(struct state *, struct game_data *);
	struct action_vtab a_vtab;
};

#define STATE_TYPE_COUNT 1
struct state_machine {
	enum state_names cur_name;
	struct state *cur;
	struct state states[STATE_TYPE_COUNT];
	struct action_list no_action;
};



int init_statemachine(struct state_machine *s, struct action_key *km);

#endif 

