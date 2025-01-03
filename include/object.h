#ifndef OBJECT_H_
#define OBJECT_H_

#include "common.h"

#define MAX_OBJ_DEF 10

enum obj_prec {
	OBJ_PREC_UNDEF = 0,
	OBJ_PREC_PROTAG = 1
};

enum obj_type {
	OBJ_TYPE_UNDEF = 0,
	OBJ_TYPE_PROTAG = 1
};

struct obj_def {
	cchar_t *paint;
	char type;
	char flags;
	char prec;
};

struct obj {
	struct obj_def *def;
};


int init_obj_defs(struct obj_def *defs);

#endif
