#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Player *create_player(char *name) {
    Player *player = (Player *)malloc(sizeof(Player));
    if (!player) {
        perror("Failed to allocate memory for player");
        exit(EXIT_FAILURE);
    }
    player->name = strdup(name);
    player->health = 100;
    player->strength = 10;
    player->inventory_count = 0;
    return player;
}

void display_inventory(Player *player) {
    printf("Your Inventory:\n");
    if (player->inventory_count == 0) {
        printf(" - Inventory is empty.\n");
    } else {
        for (int i = 0; i < player->inventory_count; i++) {
            printf(" - %s\n", player->inventory[i]);
        }
    }
}

bool remove_from_inventory(Player *player, const char *item) {
    for (int i = 0; i < player->inventory_count; i++) {
        if (strcmp(player->inventory[i], item) == 0) {
            free(player->inventory[i]);
            for (int j = i; j < player->inventory_count - 1; j++) {
                player->inventory[j] = player->inventory[j + 1];
            }
            player->inventory_count--;
            return true;
        }
    }
    return false;
}
void attack_creature(Player *player, Creature *creature) {
    if (!creature || creature->health <= 0) {
        printf("There is no active creature to attack.\n");
        return;
    }

    creature->health -= player->strength;
    printf("You attacked %s! Its health is now %d.\n", creature->name, creature->health);

    if (creature->health <= 0) {
        printf("You have defeated the %s!\n", creature->name);
        exit(1);
    }

    player->health -= ((creature->attack) - (player->defense)*(creature->attack)*0.01) ;

    printf("%s attacked you! Your health is now %d.\n", creature->name, player->health);

    if (player->health <= 0) {
        printf("You have been defeated by the %s. Game Over!\n", creature->name);
    }
}

bool add_to_inventory(Player *player, const char *item) {
    if (player->inventory_count >= MAX_INVENTORY_SIZE) {
        printf("Inventory is full!\n");
        return false;
    }
    player->inventory[player->inventory_count++] = strdup(item);
    return true;
}

void free_player(Player *player) {
    free(player->name);
    for (int i = 0; i < player->inventory_count; i++) {
        free(player->inventory[i]);
    }
    free(player);
}
void add_dropped_item_to_inventory(Player *player, Creature *creature) {
    if (creature->drop) {
        if (add_to_inventory(player, creature->drop->name)) {
            printf("You picked up %s dropped by the %s.\n", creature->drop->name, creature->name);
            free_item(creature->drop);
            creature->drop = NULL;
        } else {
            printf("Your inventory is full! You cannot pick up %s.\n", creature->drop->name);
        }
    }
}

void use_item(Player *player, const char *item_name, Item **items, int item_count) {

    for (int i = 0; i < player->inventory_count; i++) {
        if (strcmp(player->inventory[i], item_name) == 0) {

            for (int j = 0; j < item_count; j++) {
                if (strcmp(items[j]->name, item_name) == 0) {

                    if (strstr(items[j]->effect, "Restore") && strstr(items[j]->effect, "Health")) {
                        int value = atoi(strrchr(items[j]->effect, ' ') + 1);
                        player->health += value;
                        printf("You used %s. Health restored by %d. Current health: %d\n", item_name, value, player->health);
                    }else if (strstr(items[j]->effect, "Decrease") && strstr(items[j]->effect, "Health")) {
                        int value = atoi(strrchr(items[j]->effect, ' ') + 1);
                        player->health -= value;
                        printf("You used %s. Health decreased by %d. Current health: %d\n", item_name, value, player->health);
                    }else if (strstr(items[j]->effect, "Increase") && strstr(items[j]->effect, "Strength")) {
                        int value = atoi(strrchr(items[j]->effect, ' ') + 1);
                        player->strength += value;
                        printf("You used %s. Strength increased by %d. Current strength: %d\n", item_name, value, player->strength);
                    }else if (strstr(items[j]->effect, "Decrease") && strstr(items[j]->effect, "Strength")) {
                        int value = atoi(strrchr(items[j]->effect, ' ') + 1);
                        player->strength -= value;
                        printf("You used %s. Strength decreased by %d. Current strength: %d\n", item_name, value, player->strength);
                    }else if (strstr(items[j]->effect, "Increase") && strstr(items[j]->effect, "Defense")) {
                        int value = atoi(strrchr(items[j]->effect, ' ') + 1);
                        player->defense += value;
                        printf("You used %s. Defense increased by %d. Current defense: %d\n",item_name, value, player->defense);
                    }else if (strstr(items[j]->effect, "Decrease") && strstr(items[j]->effect, "Defense")) {
                        int value = atoi(strrchr(items[j]->effect, ' ') + 1);
                        printf("You used %s. Defense decreased by %d.\n", item_name, value);
                    } else {
                        printf("The item has no usable effect.\n");
                    }
                    free(player->inventory[i]);
                    for (int k = i; k < player->inventory_count - 1; k++) {
                        player->inventory[k] = player->inventory[k + 1];
                    }
                    player->inventory_count--;
                    return;
                }
            }
            printf("Item '%s' not found in item database.\n", item_name);
            return;
        }
    }
    printf("You do not have '%s' in your inventory.\n", item_name);
}
