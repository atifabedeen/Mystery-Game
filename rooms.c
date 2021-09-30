#include "rooms.h"
struct Room* room(char* description,struct Room* north, struct Room* south, struct Room* east, struct Room* west,int num, char* name) {
	struct Room* node;
    node  =  (struct Room*) malloc(sizeof(struct Room));
	node->description =  description;
    node->itemList = NULL;
    node->north = north;
    node->south = south;
    node->east = east;
    node->west = west;
    node->name = name;
    node->characterList = NULL;
    node->num = num;
    return node;
}


void randomizeRoomNum(struct Room* rooms[9]) {
    int numList[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int  j = 0;
    int found = 0;
    for(int i = 0; i < 9; ++i) {
        found = 0;
        rooms[i]->num = (rand() % 9);
        for(int k = 0; k < 9; ++k) {
            if(numList[k] == rooms[i]->num) {
                found = 1;
            }
        }
        if(found == 0){
                numList[j] = rooms[i]->num;
                ++j;
        }
        else {
            --i;
        }
    }
}


struct Room* findRoom(struct Room* rooms[9], int digit) {
   for(int i = 0; i < 9; ++i) {
       if(rooms[i]->num == digit){
           return rooms[i];
       }
   }
    return NULL;
}

void linkRooms(struct Room* rooms[9]) {
    int digit = 0;
    for(int i = 0; i < 9; ++i) {
        digit = rooms[i]->num;
        switch(digit) {
            case 0 : rooms[i]->east = findRoom(rooms, 1);
                     rooms[i]->south = findRoom(rooms, 3);
                     break;

            case 1 : rooms[i]->west = findRoom(rooms, 0);
                     rooms[i]->east = findRoom(rooms, 2);
                     rooms[i]->south = findRoom(rooms, 4);
                     break;

            case 2 : rooms[i]->west = findRoom(rooms, 1);
                     rooms[i]->south = findRoom(rooms, 5);
                     break;

            case 3 : rooms[i]->north = findRoom(rooms, 0);
                     rooms[i]->east = findRoom(rooms, 4);
                     rooms[i]->south = findRoom(rooms, 6);
                     break;

            case 4 : rooms[i]->north = findRoom(rooms, 1);
                     rooms[i]->south = findRoom(rooms, 7);
                     rooms[i]->east = findRoom(rooms, 5);
                     rooms[i]->west = findRoom(rooms, 3);
                     break;

            case 5 : rooms[i]->north = findRoom(rooms, 2);
                     rooms[i]->west = findRoom(rooms, 4);
                     rooms[i]->south = findRoom(rooms, 8);
                     break;

            case 6 : rooms[i]->north = findRoom(rooms, 3);
                     rooms[i]->east = findRoom(rooms, 7);
                     break;

            case 7 : rooms[i]->north = findRoom(rooms, 4);
                     rooms[i]->east = findRoom(rooms, 8);
                     rooms[i]->west = findRoom(rooms, 6);
                     break;

            case 8 : rooms[i]->north = findRoom(rooms, 5);
                     rooms[i]->west = findRoom(rooms, 7);
                     break;
        }
    }
}




char* roomName1 = "Hotel Lobby";
char* roomName2 = "Storage room";
char* roomName3 = "BallRoom";
char* roomName4 = "Kitchen";
char* roomName5 = "Public Washroom ";
char* roomName6 = "Room number 666";
char* roomName7 = "Hotel Bar";
char* roomName8 = "Library";
char* roomName9 = "Indoor swimming pool";

char* roomDesc1 = "The disgusting smell persists and it gets worse once you enter the lobby. You cover your mouth to stop yourself from gagging. The wallpaper of the walls are peeling off.\n";
char* roomDesc2 = "There's just one dull yellow lightbulb in the middle of the room. You find it difficult to navigate around the room. You feel like you probably stepped on squishy... a dead rat maybe?? You don't want to find out.\n ";
char* roomDesc3 = "A huge room with tables and chairs hugging the walls and a wide open space in between. You want to turn up the music and dance in the middle of the room but you're afraid someone will see you.\n";
char* roomDesc4 = "Whatever was cooking here, you're glad the food is over. As you are walking around the room you hear a lot of squeaking coming from the pots and pans stored. \n";
char* roomDesc5 = "What on earth were you thinking entering the washroom...you wonder how can people be so bad at aiming as you look for clues among a lot of brown stuff on the floor.. and the walls. \n";
char* roomDesc6 = "Seriously? of all the rooms in the hotel, why this one? Thankfully nothing spooky has happened in the room (till now). \n";
char* roomDesc7 = "You've got a sudden urge to drink after seeing the bottles lined up perfectly, but then you remember you are on a case.\n";
char* roomDesc8 = "Peaceful. As every library should be. Bookshelves are as high as the ceiling and all the books are lined up so nicely. You wonder if your favourite Conan Doyle books are here.\n";
char* roomDesc9 = "One look at the colour of the pool tells you no one has attempted swimming in the pool for YEARS(or tried cleaning it). It's so bad that the water is orange in colour...\n";

