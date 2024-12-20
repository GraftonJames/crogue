#ifndef KEYMAPPER_H_
#define KEYMAPPER_H_

#include <stdio.h>
#include "gamestate.h"

#define ACTION_TYPE_MASK_BITS 4

enum action_types = {
	ACTION_TYPE_UI,
	ACTION_TYPE_GAME,
	ACTION_TYPE_WORLD,
};

enum actions = {
	UIA_MAINMENU_OPEN = ACTION_TYPE_UI << (sizeof(int) - ACTION_TYPE_MASK_BITS),
	GA_SAVE_WORLD = ACTION_TYPE_GAME << (sizeof(int) - ACTION_TYPE_MASK_BITS),
	WA_MOVE_N = ACTION_TYPE_WORLD << (sizeof(int) - ACTION_TYPE_MASK_BITS),
};

struct key_action {
	int key;
	action_link *action;
}; 

struct action_link {
	int action;
	action_link *link;
};


int get_action(int keycode);

int get_keybindings();


#endif 

