#include "keymapper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>

#define CONFIG_DEFAULT_PATH "keymap.cfg"

const struct action_key default_keymap[ACTION_COUNT] = {
	{ACTION_UNDEFINED, {0,0,0,0,0,0,0,0,0,0}},
	{WA_PROTAG_MOVE_N, {'e',0,0,0,0,0,0,0,0,0}},
	{WA_PROTAG_MOVE_S, {'j',0,0,0,0,0,0,0,0,0}},
	{WA_PROTAG_MOVE_E, {'o',0,0,0,0,0,0,0,0,0}},
	{WA_PROTAG_MOVE_W, {'u',0,0,0,0,0,0,0,0,0}}
};

int fread_key_action_pairs(struct action_key* km, FILE *fd);
int keymap_save(struct action_key* keymap);
int keymap_add(struct action_key* keymap, int key, int action);
int keymap_remove(struct action_key* keymap, int key, int action);
char *get_config_path();
struct action_key *gen_keymap();


int
fread_key_action_pairs(struct action_key* km, FILE *fd)
{
	memset(km, 0, sizeof(struct action_key) * ACTION_COUNT);

	if (km == NULL)
		return 0;

	int res = fread(km, sizeof(struct action_key), ACTION_COUNT, fd);
	if (res != ACTION_COUNT)
		return 0;

	res = fclose(fd);
	if (res != 0)
		return 0;

	return 1;

	exit:
		err(EXIT_FAILURE, NULL);
}

int
init_key_action_pairs(struct action_key *km)
{
	char *keymap_file = get_config_path();
	FILE *fd = fopen(keymap_file, "rb");

	if (fd == NULL) {
		if (errno == ENOENT) {
			km = (struct action_key *) default_keymap;
			return 1;
		}
		else {
			err(EXIT_FAILURE, "%s", keymap_file);
			return 0;
		}
	}

	return fread_key_action_pairs(km, fd);
}



int
keymap_save(struct action_key *keymap)
{
	char *keymap_file = get_config_path();
	printf(keymap_file);
	FILE *fd = fopen(keymap_file, "wb");
	if (fd == NULL) {
		free(keymap);
		exit(EXIT_FAILURE);
	}

	int res = fwrite(keymap, sizeof(struct action_key), ACTION_COUNT, fd);
	if (res != ACTION_COUNT) {
		fclose(fd);
		exit(EXIT_FAILURE);
	}

	fclose(fd);
	if (fd != 0) {
		exit(EXIT_FAILURE);
	}

	return 1;
}

int
keymap_add(struct action_key *keymap, int key, int action)
{
	int i = 0;
	while (
		i < ACTION_COUNT &&
		keymap[i].action != ACTION_UNDEFINED &&
		keymap[i].action != action
	) i++;
	
	if (keymap[i].action == ACTION_UNDEFINED) {
		keymap[i].action = action;
		keymap[i].keys[0] = key;
		return 1;
	}

	int j = 0;
	while (
		j <= MAX_KEYS_PER_ACTION &&
		keymap[i].keys[j] != 0 &&
		keymap[i].keys[j] != key
	) j++;

	if (keymap[i].keys[j] == key) 
		return 1;

	if (j == MAX_KEYS_PER_ACTION)
		return -1;
	
	keymap[i].keys[j] = key;
	return 1;
}

int
keymap_remove(struct action_key *keymap, int key, int action)
{
	int i = 0;
	while (
		i <= ACTION_COUNT &&
		keymap[i].action != action
	) i++;

	if (i == ACTION_COUNT) 
		return -1;
	
	int j = 0;
	while (
		j <= MAX_KEYS_PER_ACTION &&
		keymap[i].keys[j] != 0 &&
		keymap[i].keys[j] != key
	) j++;

	if (keymap[i].keys[j] == 0 || j == MAX_KEYS_PER_ACTION) 
		return -1;

	while (
		j +1 < MAX_KEYS_PER_ACTION &&
		keymap[i].keys[j+1] != 0 
	) {
		keymap[i].keys[j] = keymap[i].keys[j+1];
		j++;
	}
	keymap[i].keys[j+1] = 0;

	return 1;
}

char*
get_config_path()
{
	return "keymaps.cfg";
}
