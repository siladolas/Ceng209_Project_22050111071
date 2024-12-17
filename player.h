#ifndef PLAYER_H
#define PLAYER_H
#include "creature.h"

#include <stdbool.h>

#define MAX_INVENTORY_SIZE 10

typedef struct {
    char *name;
    int health;
    int strength;
    char *inventory[MAX_INVENTORY_SIZE];
    int inventory_count;
    int defense;
} Player;

Player *create_player(char *name);
void display_inventory(Player *player);
bool add_to_inventory(Player *player, const char *item);
void free_player(Player *player);
bool remove_from_inventory(Player *player, const char *item);
void attack_creature(Player *player, Creature *creature);
void add_dropped_item_to_inventory(Player *player, Creature *creature); 
void use_item(Player *player, const char *item_name, Item **items, int item_count);

#endif
