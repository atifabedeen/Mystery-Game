#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Item {
char* itemName;
struct Item* next;
int num;
};

/* Constructor for struct Item*.
*  Paramters: itemName, num, next
*  return: a pointer object of type Item*.
*/
struct Item* item(char* itemName,int num, struct Item* next);

/* Takes the item from the current room the player is in and adds it to the the players' inventory.
*  Parameters: inventory - Linked list of players' inventory.
*              item - pointer object that is to be added to the inventory from the room.
*/

void takeItem(struct Item* inventory, struct Item* item);

/* removes the item from the players' inventory and returns it so that it can be added to the current rooms' linked list
*  Parameters: inventory - Linked list of players' inventory.
*              object - string name of the item we want to remove from the inventory.
*
*  return: item node that is removed
*          NULL if no item with object name is found in the inventory.
*/

struct Item* dropItem(struct Item* inventory, char* object);

/* randomizes the num field of items[i] between 0 to 8 so that it can be added to the room with corresponding num.
*  Paramater: array of items in the game.
*/

void randomizeItemNum(struct Item* items[6]);