# Dungeon Game
# Report Link
https://docs.google.com/document/d/1juRgZQsSf9gZKnoYwztOBmqj5XLkd7FaBsP17rkaicE/edit?usp=sharing
# Command-Line Adventure Game
A text-based adventure game developed in C for exploring a dungeon, battling creatures, collecting items, and saving/loading game progress.
## Description
This project is a command-line based adventure game where players navigate through a dungeon, battle creatures, collect useful items, and manage their health and inventory. The game is built in **C programming language** and includes features like:
- Moving between interconnected rooms.
- Picking up and dropping the items and using to affect the player's stats.
- Battling creatures with attack mechanics.
- Encountering traps that reduce the player's health.
- Saving and loading game progress from files.
- Listing available saved games.

The game is modular and scalable, making it easy to add new rooms, creatures, and items.

## How to Play
Once you start the game, you can enter commands to interact with the game world. The available commands are:

| **Command**           | **Description**                                                                 |
|------------------------|-------------------------------------------------------------------------------|
| `move <direction>`     | Move to a connected room. Directions: `up`, `down`, `left`, `right`.          |
| `look`                 | Display the description of the current room, creatures, and items.            |
| `pickup <item>`        | Pick up an item from the current room and add it to your inventory.           |
| `drop <item>`          | Drop an item from the inventory.                                              |
| `use <item>`           | Use an item from your inventory. The item effects will modify player stats.   |
| `attack`               | Attack creatures in the current room. Health and attack stats are updated.    |
| `inventory`            | List all items currently in the player's inventory.                           |
| `save <filepath>`      | Save the current game state to the specified file path.                       |
| `load <filepath>`      | Load a saved game state from the specified file path.                         |
| `list`                 | List all saved games in the `./saves` directory.                              |
| `exit`                 | Quit the game.                                                                |


# Project Structure
The game is modular and divided into several components, each handling a specific part of the game logic.

## 1-main.c
Purpose:
The entry point of the game. It initializes the game, loads all data, and manages the game loop.

 Key Responsibilities:

- Loads game data (rooms, creatures, items) using `file_parser.c`.
- Initializes the player and sets the starting room.
- Accepts and processes user commands using `process_command` (from `game.c`).
- Frees allocated memory at the end of the game.

## 2-player.c / player.h
Purpose:
 Manages the player's attributes, inventory, and interactions.

Key Features:

- Player Attributes: Stores player's health, strength, and inventory.
- Inventory Management:
    - add_to_inventory: Adds items to the inventory.
    - remove_from_inventory: Removes items from the inventory.
    - display_inventory: Lists all items in the player's inventory.
- Item Effects:
    - use_item: Applies effects of items such as restoring health or increasing strength.
- Functions:
    - create_player: Initializes a player with a given name.
    - free_player: Frees memory allocated to the player.

## 3-room.c / room.h
Purpose:
 Manages room structures, descriptions, and connections.

Key Features:

- Room Navigation: Rooms are connected in four directions: up, down, left, right.
- Trap Management:
  - Some rooms have traps that reduce the player's health.
- Room Description: Provides details about the current room.
- Functions:

  - create_room: Creates a new room with its description and trap status.
  - describe_room: Displays the room's description and any warnings about traps.
  - free_room: Frees memory allocated to the room.

## 4-creature.c / creature.h
Purpose:
  Manages creatures and their interactions with the player.

Key Features:

- Creature Attributes: Creatures have health, attack, and a room location.
- Combat:
    - attack_creature: Handles the player attacking a creature.
    - creature_attack: Allows creatures to retaliate during combat.
- Item Drops:
    - Creatures drop specific items when defeated, which are automatically added to the player's inventory.
-Functions:

  - create_creature: Initializes a new creature with attributes.
  - describe_creature: Displays creature details.
  - free_creature: Frees memory allocated to the creature.
  
## 5-item.c / item.h
Purpose:
  Manages item attributes and effects.

Key Features:

- Item Effects: Items can restore health, increase strength, or apply harmful effects.
    - Items are picked up from rooms or dropped by creatures upon defeat.
- Functions:

    - create_item: Initializes a new item with its name and effect.
    - free_item: Frees memory allocated to an item.

## 6-file_parser.c / file_parser.h
Purpose:
  Handles loading game data (rooms, creatures, and items) from external files.

Key Features:

- Data Loading:
  - Reads rooms.txt to create rooms and their connections.
  - Reads creatures.txt to load creatures and their attributes.
  - Reads items.txt to load items and their effects.
  - Supports modular game design, making it easy to add or modify game data.
- Functions:

  - load_rooms: Loads room data from rooms.txt.
  - load_creatures: Loads creature data from creatures.txt.
  - load_items: Loads item data from items.txt.
## 7-game.c / game.h
Purpose:
  Processes user commands and manages game events.

Key Features:

-Command Processing:
  - move <direction>: Move to an adjacent room.
  - look: Describe the current room.
  - pickup <item>: Add an item to the player's inventory.
  - use <item>: Use an item from the inventory.
  - attack: Engage in combat with creatures.
  - save <filepath>: Save the current game state.
  - load <filepath>: Load a previously saved game state.
  - list: List all saved games.
-Trap Logic:
  - Rooms with traps reduce the player's health dynamically.
-State Management:
  - Ensures the game state can be saved and reloaded.
-Functions:

  - process_command: Processes all user commands.
  - check_trap: Checks for traps when entering a room.

## 8-Makefile
Purpose:
  Automates the compilation of the game.

Usage:

  - make: Compiles the game.
  - make clean: Removes compiled object files.



# Files:
- The game uses external files to load data dynamically:

##record.txt: 
- saved file example

## rooms.txt:

- Defines room descriptions, connections, and trap status.
- Format: RoomID,Description,Up,Down,Left,Right,Trap
  
## creatures.txt:

- Defines creatures' attributes and dropped items.
- Format: RoomID,CreatureName,Health,Attack,DropItem

## items.txt:

- Defines item effects.
- Format: RoomID,ItemName,Effect

# Technical Details
- Language: C (ANSI C standard, compiled with GCC).
- Memory Management:
Dynamic allocation using malloc and free.
 All resources are freed at the end of the game.
- Data Handling:
 Modular data loading from external text files.
 Save/load functionality to store the game state in files.


# Conclusion
The Dungeon Adventure Game is a text-based adventure game developed in C language. The player navigates through interconnected rooms, battles creatures, collects items, and encounters traps. Additionally, the game allows saving and loading progress dynamically.
This project demonstrates a modular and dynamic game design in C, showcasing key concepts like:

- Structured programming.
- File I/O operations.
- Memory management.
- Command parsing.
- This design allows easy expansion of the game with additional rooms, creatures, and items.

## Enjoy your adventure in the dungeon!
