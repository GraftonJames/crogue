#include "keymapper.h"
#include "gamestate.h"
#include "err_handler.h"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>


#define ACTION_COUNT 1
#define ACTION_COUNT_BITS 1
#define ACTION_TYPE_MASK INT_MAX << (sizeof(int) - ACTION_TYPE_MASK_BITS)
#define CONFIG_DEFAULT_PATH "keymap.cfg"

const keymap_defaults keyaction[ACTION_COUNT] = {

}

keyaction* load_keymap_pairs(FILE *fd);
keyaction* init_keymap_pairs();
int key_hash(int c);
int keymap_insert(keyaction[] hashmap, keyaction ka);

struct keyaction_pair {
	int key;
	int action;
}

int get_action(gamestate *gs, int keycode)
{
	return keymap_fetch(*gs.keybinds, keycode);
}

keyaction[] init_keybinds()
{
	keyaction[ACTION_COUNT] pairs = init_keymap_pairs();
	keyaction[ACTION_COUNT] h = malloc(ACTION_COUNT * sizeof(keyaction));

	for (int i = 0; i < ACTION_COUNT; i++) {
		keymap_insert(h, pairs[i]);
	}
	
	free(pairs);
	return h;
}

keyaction_pair* 
load_keymap_pairs(FILE *fd)
{

	keyaction[ACTION_COUNT] ret = malloc(ACTION_COUNT * sizeof(keyaction));
	if (ret == NULL)
		goto exit;

	ret = fread(sizeof(keyaction), ACTION_COUNT, ptr);
	if (ret != ACTION_COUNT)
		goto clean_ret;

	int res = fclose(ptr);
	if (res != 0)
		goto clean_ret;

	return return

	clean_ret:
		free(ret);
	exit:
		err(EXIT_FAILURE, NULL);
}

keyaction_pair*
init_keymap_pairs()
{
	char *keymap_file = get_config_path();
	char *ptr = fopen(keymap_file, "rb");

	if (ptr == NULL) {
		if (errno == ENOENT) {
			return gen_keymap();
		}
		else {
			err(EXIT_FAILURE, "%s", file_name);
		}
	}

	keyaction[] km = load_keymap(ptr);

	return km;
}

int 
key_hash(int c)
{
	long h = 0x243f6 * 2 ^ sizeof(int);
	h = c * h;
	h = h >> (sizeof(long) - ACTION_COUNT_BITS);
	h = h % ACTION_COUNT;
	return (int) h;
}

int 
keymap_insert(keyaction[] hashmap, keyaction_pair pair)
{
	int kh = key_hash(pair->key);
	action_link *ptr;
	keyaction *ka; 

	while (hashmap[kh] != NULL || hashmap[kh].key != pair.key)
		kh = (kh + 1) % ACTION_COUNT;

	if (hashmap[kh] == NULL)
		hashmap[kh].key = pair.key;

	ptr = hashmap[kh].action;
	while (ptr != NULL)
		ptr = ptr.link;

	ptr.action = pair.action;

	return 1;
}

keyaction 
keymap_fetch(keyaction[] hashmap, key k)
{
	int kh = key_hash(k);
	while (hashmap[kh]->key != k)
		kh = (kh + 1) % ACTION_COUNT;

	return hashmap[kh];
}

int
keymap_edit(keyaction* hashmap, keyaction ka)
{
	
}

int
keymap_save(keyaction* hashmap)
{
	
}

bool
get_action_type(int target_type, int action)
{
	return action >> (sizeof(int) - ACTION_TYPE_MASK_BITS);
}

char*
get_config_path()
{
}

keyaction*
gen_keymap()
{
	return keymap_defaults;
}
