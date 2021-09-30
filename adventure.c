#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "rooms.h"
#include "items.h"
#include "characters.h"

struct Avatar {
    struct Room* room;
    struct Item* inventory;
};

struct Avatar player; //object for user

/* Adds an item to the rooms' linkedlist of items.
*  Paramters: pointer to a room object, pointer to an item object.
*/

void addItemToRoom(struct Room* room, struct Item* item) {
    struct Item* ptr = (struct Item* ) malloc(sizeof(struct Item));
    if(room->itemList == NULL) {
        room->itemList = item;
        return;
    }
    ptr = room->itemList;
    while(ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = item;
    free(ptr);
}

/* Adds a character to the rooms' linkedlist of characters.
*  Paramters: pointer to a room object, pointer to a character object.
*/

void addCharacterToRoom(struct Room* room, struct Character* character) {
    struct Character* ptr = (struct Character* ) malloc(sizeof(struct Character));
    if(room->characterList == NULL) {
        room->characterList = character;
        return;
    }
    ptr = room->characterList;
    while(ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = character;
    free(ptr);
}

/* Removes an item from the rooms' linkedlist of items.
*  Paramters: pointer to an item object.
*  returns: returns the item removed.
*           NULL if unsuccessful
*/

struct Item* removeRoomItem(char* item) {
    struct Item* ptr = (struct Item*) malloc(sizeof(struct Item));
    ptr = player.room->itemList;
    int found = 0;
    while(ptr != NULL) {
        if(strcasecmp(ptr->itemName, item) == 0) {
            found = 1;
            break;
        }
        ptr = ptr->next;
    }
    if(found == 0) {
        printf("Item not found. Try again.\n");
        return NULL;
    }

    ptr = player.room->itemList;
    struct Item* prevPtr = (struct Item*) malloc(sizeof(struct Item));
    struct Item* node = (struct Item*) malloc(sizeof(struct Item));
    prevPtr = player.room->itemList;

    if(strcasecmp(ptr->itemName, item) == 0) {
        if(ptr->next == NULL) {
            node = ptr;
            player.room->itemList = NULL;
            return node;
        }
        else {
            node = ptr;
            player.room->itemList = player.room->itemList->next;
            ptr->next = NULL;
            return node;
        }
    }

    ptr = ptr->next;

    while(ptr != NULL) {
       if(strcasecmp(ptr->itemName, item) == 0) {
           if(ptr->next == NULL) {
               prevPtr->next = NULL;
               node = ptr;
               return node;
           }
       }

       if(strcasecmp(ptr->itemName, item) == 0){
	        node = ptr;
	        prevPtr->next = ptr->next;
	        ptr->next = NULL;
	        return node;
        }
        ptr = ptr->next;
        prevPtr = prevPtr->next;
    }
    free(ptr);
    free(prevPtr);
    free(node);
    return NULL;
 }

/*Displays the room name, description, items in the room, characters present in
* the room, and the rooms that are linked to this room in different directions.
* Parameter: pointer to room object.
*/
void displayRoom(struct Room* room) {
    printf("You are in the %s. \n", room->name);
    printf("%s \n",room->description);
    struct Item* ptr1 = (struct Item*) malloc(sizeof(struct Item));
    ptr1 = room->itemList;
    while(ptr1 != NULL) {
        printf("There is a %s in the room.\n", ptr1->itemName);
        ptr1 = ptr1->next;
    }

    struct Character* ptr2 = (struct Character* ) malloc(sizeof(struct Character));
    ptr2 = room->characterList;
    while(ptr2 != NULL) {
        printf("There is %s in the room.\n", ptr2->charName);
        ptr2 = ptr2->next;
    }

    if(room->north != NULL) {
        printf("There is the %s to the north \n", room->north->name);
    }

    if(room->south != NULL) {
        printf("There is the %s to the south \n", room->south->name);
    }

    if(room->east != NULL) {
        printf("There is the %s to the east \n", room->east->name);
    }

    if(room->west != NULL) {
        printf("There is the %s to the west \n", room->west->name);
    }
    free(ptr1);
    free(ptr2);
}

/* Displays all the different commands available to the user.
*/

void help() {
    printf("\nThe following commands can be used: \n");
    printf("Take: Take the items available in the room and add them to your inventory\n");
    printf("Drop: Drop any item from your inventory in the room you are currently in.\n");
    printf("Go: Go to a different room which is connected to the current room by specifying direction (North, South, East, West).\n");
    printf("List: Shows the list of rooms, characters and items in the game.\n");
    printf("Look: Shows the details about the room you are currently in including the items, characters and the different conected rooms in each direction.\n");
    printf("Inventory: Shows the items that you have currently in your inventory\n");
    printf("Clue: use clue CHARACTER to make a guess in a room and it will tell you if there is room match, character match and/or item match.\n");
}

/* Moves the player to a different room that is linkd to the room the player is currently in.
*  Parameter: string for direction in which the player wants to move.
*  returns : 1 if successfully moved.
*           -1 if invalid.
*/

int movePlayer(char* dir) {
    if((strcasecmp(dir, "north") == 0) && (player.room->north != NULL)) {
        player.room = player.room->north;
        return 1;
    }

    if((strcasecmp(dir, "south") == 0) && (player.room->south != NULL)) {
        player.room = player.room->south;
        return 1;
    }

    if((strcasecmp(dir, "east") == 0) && (player.room->east != NULL)) {
        player.room = player.room->east;
        return 1;
    }

    if((strcasecmp(dir, "west") == 0) && (player.room->west != NULL)) {
        player.room = player.room->west;
        return 1;
    }

    printf("Inavlid direction or there is no room in that direction. Try again. \n");
    return -1;

}

/* Shows the list of all characters, items and rooms in the game.
 * Parameters: array of Room* objects, Character* objects, Item* Objects
 */

void listCommand(struct Room* rooms[9], struct Character* characters[5], struct Item* items[6]) {
    printf("These are the characters in the game:\n");
    for(int i = 0; i < 5; ++i) {
        printf("%s", characters[i]->charName);
        if(i != 4) {
            printf(", ");
        }
    }
    printf("\nThese are the items in the game:\n");
    for(int i = 0; i < 6; ++i) {
        printf("%s ", items[i]->itemName);
        if(i != 5) {
            printf(", ");
        }
    }
    printf("\nThese are the rooms in the game:\n");
    for(int i = 0; i < 9; ++i) {
        printf("%s ", rooms[i]->name);
        if(i != 8) {
            printf(", ");
        }
    }
}

// Displays all the items in the inventory of the player.
void seeInventory() {
    struct Item* ptr = (struct Item*) malloc(sizeof(struct Item));
    if(player.inventory->next == NULL) {
        printf("Inventory is empty. \n");
    }
    ptr = player.inventory->next;
    while(ptr != NULL) {
        printf("%s ", ptr->itemName);
        ptr = ptr->next;
    }

    printf("\n");
    free(ptr);
}

/* Checks if the command input is valid.
 * parameter: input from user stored in char array.
 * returns : 1 for help()
 *           2 for take item command.
 *           3 for drop item command.
 *           4 for go DIRECTION command.
 *           5 for listCommand() command.
 *           6 for display the room command.
 *           7 for show inventory command.
 *           8 for clue command.
 *           -1 for invalid.
 */
int whichCommand(char command[10]) {

    if(strcasecmp(command, "help") == 0) {
        return 1;
    }
    else if(strcasecmp(command, "take") == 0) {
        return 2;
    }
    else if(strcasecmp(command, "drop") == 0) {
        return 3;
    }
    else if(strcasecmp(command, "go") == 0) {
        return 4;
    }
    else if(strcasecmp(command, "list") == 0) {
        return 5;
    }
    else if(strcasecmp(command, "look") == 0) {
        return 6;
    }
    else if(strcasecmp(command, "inventory") == 0) {
        return 7;
    }
    else if(strcasecmp(command, "clue") == 0) {
        return 8;
    }
    else {
        printf("\nInvalid command. Try again. \n");
        return -1;
    }
    return -1;
}

/* finds the characters' room and removes him/her from that room.
 * parameter : object - character name string, characters in the game array, rooms in the game array
 * returns: 1 if successfully removed or character is already in the room
 *         -1 if unsuccessful.
 */

int moveCharacter(char* object, struct Character* characters[5], struct Room* rooms[9]) {
    int found = 0;
    struct Room* charRoom = (struct Room*) malloc(sizeof(struct Room));
    for(int i = 0; i < 5; ++i) {
        if(strcasecmp(object, characters[i]->charName) == 0) {
            found = 1;
            if(characters[i]->num == player.room->num) {
                return 1;
            }
            else {
            charRoom = findRoom(rooms,characters[i]->num);
            }
            break;
        }
    }
    if(found == 0) {
      printf("Invalid Character. Try again.\n");
      return -1;
    }
    struct Character* ptr = (struct Character*) malloc(sizeof(struct Character));
    ptr = charRoom->characterList;
    struct Character* prevPtr = (struct Character*) malloc(sizeof(struct Character));
    struct Character* node = (struct Character*) malloc(sizeof(struct Character));
    prevPtr = charRoom->characterList;

    if(strcasecmp(ptr->charName, object) == 0) {
        if(ptr->next == NULL) {
            node = ptr;
            charRoom->characterList = NULL;
            addCharacterToRoom(player.room,node);
            return 1;
        }
        else {
            node = ptr;
            charRoom->characterList = charRoom->characterList->next;
            ptr->next = NULL;
            addCharacterToRoom(player.room,node);
            return 1;
        }
    }

    ptr = ptr->next;

    while(ptr != NULL) {
       if(strcasecmp(ptr->charName, object) == 0) {
           if(ptr->next == NULL) {
               prevPtr->next = NULL;
               node = ptr;
               addCharacterToRoom(player.room,node);
               return 1;
           }
       }

       if(strcasecmp(ptr->charName, object) == 0){
	        node = ptr;
	        prevPtr->next = ptr->next;
	        ptr->next = NULL;
	        addCharacterToRoom(player.room,node);
	        return 1;
        }
        ptr = ptr->next;
        prevPtr = prevPtr->next;
    }
    free(ptr);
    free(prevPtr);
   // free(node);
   // free(charRoom);
    return -1;

}
/* checks for character match, room match, and item match.
*  parameter: the array which contains the answers to room, item, character.
*  returns: 1 if all 3 matches found
*           -1 if 3 matches not found
*/

int clue(char* answer[3]) {
    int matches = 0;
    if(strcasecmp(player.room->name,answer[0]) == 0) {
        printf("Room Match. \n");
        matches++;
    }
    struct Character* ptr = (struct Character*) malloc(sizeof(struct Character));
    ptr = player.room->characterList;
    while(ptr != NULL) {
        if(strcasecmp(answer[2], ptr->charName) == 0) {
            printf("Character Match. \n");
            matches++;
            break;
        }
        ptr = ptr->next;
    }
    struct Item* ptr2 = (struct Item*) malloc(sizeof(struct Item));
    ptr2 = player.room->itemList;
    while(ptr2 != NULL) {
        if(strcasecmp(answer[1], ptr2->itemName) == 0) {
            printf("Item Match. \n");
            matches++;
            break;
        }
        ptr2 = ptr2->next;
    }

    struct Item* ptr3 = (struct Item*) malloc(sizeof(struct Item));
    ptr3 = player.inventory;
    while(ptr3 != NULL) {
        if(strcasecmp(answer[1], ptr3->itemName) == 0) {
            printf("Item Match. \n");
            matches++;
            break;
        }
        ptr3 = ptr3->next;
    }

    if(matches == 3) {
        printf("Congratualtions you have figured out the Murder Mystery! \n");
        return 1;
    }
    else {
        return -1;
    }
   // free(ptr);
    //free(ptr2);
    //free(ptr3);
}

int main() {
    time_t t;
    srand((unsigned) time(&t)); //Randomly generating seed based on time

    extern char* roomName1;
    extern char* roomName2;
    extern char* roomName3;
    extern char* roomName4;
    extern char* roomName5;
    extern char* roomName6;
    extern char* roomName7;
    extern char* roomName8;
    extern char* roomName9;
    extern char* roomDesc1;
    extern char* roomDesc2;
    extern char* roomDesc3;
    extern char* roomDesc4;
    extern char* roomDesc5;
    extern char* roomDesc6;
    extern char* roomDesc7;
    extern char* roomDesc8;
    extern char* roomDesc9;

    struct Room* rooms[9];
    rooms[0] = room(roomDesc1, NULL, NULL, NULL, NULL, 0, roomName1);
    rooms[1] = room(roomDesc2, NULL, NULL, NULL, NULL, 0, roomName2);
    rooms[2] = room(roomDesc3, NULL, NULL, NULL, NULL, 0, roomName3);
    rooms[3] = room(roomDesc4, NULL, NULL, NULL, NULL, 0, roomName4);
    rooms[4] = room(roomDesc5, NULL, NULL, NULL, NULL, 0, roomName5);
    rooms[5] = room(roomDesc6, NULL, NULL, NULL, NULL, 0, roomName6);
    rooms[6] = room(roomDesc7, NULL, NULL, NULL, NULL, 0, roomName7);
    rooms[7] = room(roomDesc8, NULL, NULL, NULL, NULL, 0, roomName8);
    rooms[8] = room(roomDesc9, NULL, NULL, NULL, NULL, 0, roomName9);

    randomizeRoomNum(rooms);
    linkRooms(rooms);

    extern char* itemName1;
    extern char* itemName2;
    extern char* itemName3;
    extern char* itemName4;
    extern char* itemName5;
    extern char* itemName6;

    struct Item* items[6];
    items[0] = item(itemName1, 0, NULL);
    items[1] = item(itemName2, 0, NULL);
    items[2] = item(itemName3, 0, NULL);
    items[3] = item(itemName4, 0, NULL);
    items[4] = item(itemName5, 0, NULL);
    items[5] = item(itemName6, 0, NULL);

    randomizeItemNum(items);
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 6; ++j) {
            if(rooms[i]->num == items[j]->num) {
                addItemToRoom(rooms[i], items[j]);
            }
        }
    }

    extern char* characterName1;
    extern char* characterName2;
    extern char* characterName3;
    extern char* characterName4;
    extern char* characterName5;

    struct Character* characters[5];
    characters[0] = character(characterName1, 0, NULL);
    characters[1] = character(characterName2, 0, NULL);
    characters[2] = character(characterName3, 0, NULL);
    characters[3] = character(characterName4, 0, NULL);
    characters[4] = character(characterName5, 0, NULL);

    randomizeCharacterNum(characters);
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 5; ++j) {
            if(rooms[i]->num == characters[j]->num) {
                addCharacterToRoom(rooms[i], characters[j]);
            }
        }
    }

    player.room = rooms[0];
    player.inventory = item("dummy",0,NULL); //Dummy variable for making inventory not NULL
    int valid = 1;

    char* answer[3];
    answer[0] = rooms[rand() % 9]->name;
    answer[1] = items[rand() % 6]->itemName;
    answer[2] = characters[rand() % 5]->charName; // randomly generated answers from each array
    int clueNum = 0; // number of guesses made


    printf("A murder has occured in Barnsely Hotel, an old bickered hotel located at the outskirts of the town.\n");
    printf("You, a police detective have been asked to investigate the murder. \n");
    printf("Your objective is to explore each of the rooms in the hotel and figure out who was the murderer, what murder weapon did they use and which room the murder occured. \n\n");
    printf("To know the list of commands available to use while playing the game, type in help \n\n");
    printf("You arrive at the entrance of the hotel. You are immediately disgusted by the nasty odor lingering in the air. \n");
    printf("Nevertheless, you enter the hotel. \n\n");
    printf("You are in the %s", player.room->name);
    while(true) {
        char input[30];
        valid = 1;

        printf("\n\nwhat do you want to do? \n");

        fgets(input, sizeof(input), stdin);

        char* command = strtok(input," \n");
        char* object = strtok(NULL, " \n");

        valid = whichCommand(command);
        if(valid == -1) {
            continue;
        }

        if(valid == 1) {
            help();
        }

        else if(valid == 2) {
            struct Item* roomItem = (struct Item*) malloc(sizeof(struct Item));
            roomItem = removeRoomItem(object);

            if(roomItem == NULL) {
                continue;
            }

           takeItem(player.inventory, roomItem);
        }

        else if(valid == 3) {
            struct Item* inventItem = (struct Item*) malloc(sizeof(struct Item));
            inventItem = dropItem(player.inventory, object);

            if(inventItem == NULL) {
                continue;
            }

            addItemToRoom(player.room, inventItem);
            printf("Item dropped\n");
        }

        else if(valid == 4) {

            if(object == NULL) {
                printf("Invalid. \n");
                continue;
            }

            if(movePlayer(object) == -1) {
                continue;
            }

            printf("You are in the %s", player.room->name);
        }

        else if(valid == 5) {
            listCommand(rooms, characters, items);
        }

        else if(valid == 6) {
            displayRoom(player.room);
        }

        else if(valid == 7) {
            seeInventory();
        }

        else if(valid == 8) {
            int gameOver = 0; // to cehck game over
            int check = 0;   // check valid input

            if(object == NULL) {
                printf("Invalid. Try again. \n");
                continue;
            }

            check = moveCharacter(object,characters,rooms);

            if(check == -1) {
                continue;
            }

            gameOver = clue(answer);

            if(gameOver == 1) {
                break;
            }

            clueNum++;
            printf("You have %i guess left.\n", 10-clueNum);

            if(clueNum == 10) {
                printf("Sorry you are out of guesses. Game Over. \n");
                break;
            }
        }

    }

    for(int i = 0; i < 9;++i) {
        free(rooms[i]);
    }
   for(int i = 0; i < 6;++i) {
        free(items[i]);
    }
    for(int i = 0; i < 9;++i) {
        free(characters[i]);
    }
}