#ifndef CREATURE_H
#define CREATURE_H

#include "room.h"
#include "item.h"

typedef struct Creature {
    char name[256];
    int health;
    int attack;
    Room *room;
    Item *drop;
} Creature;

Creature *create_creature(const char *name, int health, int attack, Room *room, Item *drop);
void describe_creature(const Creature *creature);
void creature_attack(Creature *creature, int *player_health);
void free_creature(Creature *creature);

#endif
