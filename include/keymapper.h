#ifndef KEYMAPPER_H_
#define KEYMAPPER_H_

#include "common.h"

#define ACTION_COUNT 7
#define STATE_MASK_BITS 8
#define MAX_KEYS_PER_ACTION 10
#define KEYBIND_HASH_MAP_BITWIDTH 8
#define KEYBIND_HASH_MAP_SIZE 256
#define ACTION_TYPE_MASK UINT_MAX << (sizeof(int)*8 - ACTION_TYPE_MASK_BITS)

enum action_types {
	ACTION_TYPE_UNDEFINED = 0,
	ACTION_TYPE_UI = 1,
	ACTION_TYPE_GAME = 2,
	ACTION_TYPE_WORLD = 3,
};

enum actions {
	ACTION_UNDEFINED = 0,
	UIA_MAINMENU_OPEN = (ACTION_TYPE_UI << (sizeof(int)*8 - STATE_MASK_BITS )),
	GA_SAVE_WORLD = (ACTION_TYPE_GAME << (sizeof(int)*8 - STATE_MASK_BITS)),
	WA_PROTAG_MOVE_N = (ACTION_TYPE_WORLD << (sizeof(int)*8 - STATE_MASK_BITS)),
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

