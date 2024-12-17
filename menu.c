#include "menu.h"
#include <stdio.h>

void display_help() {
    printf("Available commands:\n");
    printf("  look          - Look around the current room.\n");
    printf("  move <dir>    - Move to another room (directions: up, down, left, right).\n");
    printf("  inventory     - Show your inventory.\n");
    printf("  use <item>    - Use an item on the inventory.\n");
    printf("  pickup <item> - Pick up an item from the current room.\n");
    printf("  drop <item>   - Drop an item from the inventory.\n");
    printf("  attack        - Attack a creature in the current room.\n");
    printf("  help          - Show this list of commands.\n");
    printf("  list          - List the saved games.\n");
    printf("  save <path>   - Save the current state in to the given file.\n");
    printf("  load <path>   - Load the state from the given file\n");
    printf("  exit          - Quit the game.\n");
}
