# dungeonGame
# Command-Line Adventure Game
A text-based adventure game developed in C for exploring a dungeon, battling creatures, collecting items, and saving/loading game progress.
## Description
This project is a command-line based adventure game where players navigate through a dungeon, battle creatures, collect useful items, and manage their health and inventory. The game is built in **C programming language** and includes features like:
- Moving between interconnected rooms.
- Picking up and using items to affect the player's stats.
- Battling creatures with attack mechanics.
- Encountering traps that reduce the player's health.
- Saving and loading game progress from files.
- Listing available saved games.

The game is modular and scalable, making it easy to add new rooms, creatures, and items.

## How to Play
Once you start the game, you can enter commands to interact with the game world. The available commands are:

### Basic Commands:
- `move <direction>`: Move to another room. Valid directions are `up`, `down`, `left`, `right`.
- `look`: Display the description of the current room, including creatures and items.
- `pickup <item>`: Pick up an item in the room and add it to your inventory.
- `use <item>`: Use an item in your inventory to gain its effects.
- `attack`: Attack creatures in the current room.
- `inventory`: Display the items in your inventory.

### Save and Load Commands:
- `save <filepath>`: Save the current game state to a file.
- `load <filepath>`: Load a saved game state from a file.
- `list`: List all saved games in the `./saves` directory.

### Exit:
- `exit`: Quit the game.



