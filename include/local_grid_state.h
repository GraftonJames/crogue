
#ifndef LOCAL_GRID_STATE_H_
#define LOCAL_GRID_STATE_H_

#include "common.h"
#include "statemachine.h"

void LOCAL_GRID_print(struct state *, struct game_data *);
void LOCAL_GRID_state_init(struct state *, struct action_key *);

#endif
