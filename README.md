# dungeonGame
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
| `use <item>`           | Use an item from your inventory. The item effects will modify player stats.   |
| `attack`               | Attack creatures in the current room. Health and attack stats are updated.    |
| `inventory`            | List all items currently in the player's inventory.                          |
| `save <filepath>`      | Save the current game state to the specified file path.                       |
| `load <filepath>`      | Load a saved game state from the specified file path.                         |
| `list`                 | List all saved games in the `./saves` directory.                              |
| `exit`                 | Quit the game.                                                                |


##Project Structure
The game is modular and divided into several components, each handling a specific part of the game logic.

#1. main.c
Purpose:
The entry point of the game. It initializes the game, loads all data, and manages the game loop.

Key Responsibilities:

Loads game data (rooms, creatures, items) using file_parser.c.
Initializes the player and sets the starting room.
Accepts and processes user commands using process_command (from game.c).
Frees allocated memory at the end of the game.


