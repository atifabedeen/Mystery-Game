#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Room {
    char* name;
	char* description;
	struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;
    struct Character* characterList;
    int num;
    struct Item* itemList;
};

/* Constructor for struct Room*.
*  Paramters: description, north, south, east, west, num, name
*  return: a pointer object of type Room*.
*/
struct Room* room(char* description,struct Room* north, struct Room* south, struct Room* east, struct Room* west, int num, char* name);

/* Randomizes the num variable of room object between 0-8 to place on grid.
*  Parameter: Array of all room objects rooms[9].
*/

void randomizeRoomNum(struct Room* rooms[9]);

/* Finds and returns the room pointer object which has the same num as the digit passed into the function.
*  Parameters: Array of all room objects rooms[9], integer digit.
*  return: pointer to room object
           NULL if no room is found
*/

struct Room* findRoom(struct Room* rooms[9], int digit);

/* Links each of the room using North, south, East, West links of each room appropriately wherever each room is placed on the 3x3 grid.
*  Parameters: Array of all room objects rooms[9].
*/

void linkRooms(struct Room* rooms[9]);




