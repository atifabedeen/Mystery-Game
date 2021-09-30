This is the implementation of a text adventure game in C programming language. 

The 9 rooms are randomly placed on a 3 x 3 grid using randomizeRoomNum() which randomizes the number associated to the num variable of a room object. Then all rooms are linked using linkRooms(). 
All items and characters are randomised and placed into different rooms using   randomizeItemNum() and randomizeCharacterNum().
Random answers are generated in main() using rand() to get random index of each array of rooms, items and characters and stores it in an char* array. 
Each room has a linked list of items called itemList. 
The player has an inventory which is a linked list of items.
help() - shows list of commands
listCommand() - shows list of all items, characters and rooms in the game.
movePlayer() - helps the player move their desired direction
takeItem() and dropItem() help the player take or drop an item from their inventory respectivey.
clue() - checks if there is a room match, character match and/or item match. 
moveCharacter() moves the given charater to the current players' room. 
memory is dynamically allocated and freed after its' use.


video link:
https://youtu.be/oPdbby_7fkg