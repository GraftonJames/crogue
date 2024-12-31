#ifndef KEYMAPPER_H_
#define KEYMAPPER_H_

#include "common.h"

#define ACTION_COUNT 4
#define ACTION_TYPE_MASK_BITS 8
#define MAX_KEYS_PER_ACTION 10

enum action_types {
	ACTION_TYPE_UNDEFINED = 0,
	ACTION_TYPE_UI = 1,
	ACTION_TYPE_GAME = 2,
	ACTION_TYPE_WORLD = 3,
};

enum actions {
	ACTION_UNDEFINED = 0,
	UIA_MAINMENU_OPEN = (ACTION_TYPE_UI << (sizeof(int)*8 - ACTION_TYPE_MASK_BITS)),
	GA_SAVE_WORLD = (ACTION_TYPE_GAME << (sizeof(int)*8 - ACTION_TYPE_MASK_BITS)),
	WA_MOVE_N = (ACTION_TYPE_WORLD << (sizeof(int)*8 - ACTION_TYPE_MASK_BITS)),
};

struct action_key {
	int action;
	wint_t keys[MAX_KEYS_PER_ACTION];
};

struct action_key get_keys_for_action();
struct action_key *init_key_action_pairs();

#endif 

