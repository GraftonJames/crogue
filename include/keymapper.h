#ifndef KEYMAPPER_H_
#define KEYMAPPER_H_

#include "common.h"

#define ACTION_COUNT 4
#define STATE_MASK_BITS 8
#define MAX_KEYS_PER_ACTION 10
#define STATE_MASK UINT_MAX << (sizeof(int)*8 - STATE_MASK_BITS)

#define STATE_COUNT 1
enum state_names {
	LOCAL_GRID,
}; 

enum actions {
	ACTION_UNDEFINED = 0,
	WA_PROTAG_MOVE_N = (LOCAL_GRID << (sizeof(int)*8 - STATE_MASK_BITS)),
	WA_PROTAG_MOVE_S,
	WA_PROTAG_MOVE_E,
	WA_PROTAG_MOVE_W,
};

struct action_key {
	enum actions action;
	wint_t keys[MAX_KEYS_PER_ACTION];
};

struct action_code_list {
	enum actions action;
	struct action_code_list *next;
};

struct action_code_tab {
	wint_t key;
	struct action_code_list *list;
};


int init_key_action_pairs(struct action_key* km);

#endif 

