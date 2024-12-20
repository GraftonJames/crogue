#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "common.h"

struct state {
	enum statetype {
		LOCAL_GRID,
		MAIN_MENU
	} type;

	void *state;
	void (*print_fn)();
	void (*key_handle)(wint_t);
};

#endif 

