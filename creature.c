#include "creature.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Creature *create_creature(const char *name, int health, int attack, Room *room, Item *drop) {
    Creature *creature = malloc(sizeof(Creature));
    if (!creature) {
        perror("Failed to allocate memory for creature");
        exit(EXIT_FAILURE);
    }

    strncpy(creature->name, name, sizeof(creature->name) - 1);
    creature->name[sizeof(creature->name) - 1] = '\0';
    creature->health = health;
    creature->attack = attack;
    creature->room = room;
    creature->drop = drop;

    return creature;
}


void free_creature(Creature *creature) {
    if (creature) {
        if (creature->drop) {
            free_item(creature->drop);
        }
        free(creature);
    }
}
