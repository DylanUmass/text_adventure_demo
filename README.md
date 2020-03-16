# Text Adventure Demo
Text-Based Adventure

Max Walker
Dylan Nelson

Our submission was a text based adventure game centered around escaping a laboratory. To do this, the player must traverse the rooms in the lab and use items they find to unlock paths and ultimately escape. The game uses an array based inventory system to store items on the player and in rooms. The items and rooms themselves are structs with fields for discriptions and in the case of rooms also pointers to other adjecent rooms. Some of them also have a linked list of events triggered by items to unlock paths to new rooms.

Requirements:
1. The game has nine rooms, one of which is a placeholder "Exit" room which triggers the end of the game when the player is in it.
2. Each room has an inventory which has an array that can store item structs. Each item has a name and discription.
3. The game has a struct which represents a player. This struct also has a field for the aforementioned inventory type.
4. Typing in the command "look" will print a description of the player's current room and also a list of the items within it.
5. The game allows the player to traverse rooms by typing 'go <DIRECTION'. Each direction is used at least once.
6. The player can take items from a room and put them in their inventory by typing 'take <ITEM>'.
7. The game allows the player to open paths to new rooms with a specific item in certain cases by typing 'use <ITEM>'.
8. There are five instances in the game where using an item in a room will open a new path.
9. The player can drop an item with 'drop <ITEM>'. This adds it to their current room's inventory.
10. The game is won when the player uses the exit lift in the atrium to escape the laboratory.
  
Puzzle Solutions:
1. Use the bat (located in the beaker storage) to break down the beaker storage's South door.
2. Use the pliers (located in the breaker room) to cut the lock to the Main Basement's stairs (up direction).
3. Use the acid (located in the beaker storage) to burn a hole in the break room's East wall.
4. Use the notes (located in the chemical laboratory) to open the password protected South door of the atrium.
5. Use the lift key (located in the Hadron Collider room) to unlock the escape lift in the Atrium (up direction).
