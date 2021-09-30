#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Character {
    char* charName;
    struct Character* next;
    int num;
};
/* Constructor for struct Character*.
*  Paramters: charName, num, next
*  return: a pointer object of type Character*.
*/
struct Character* character(char* charName, int num, struct Character* next);

/* randomizes the num field of characters[i] between 0 to 8 so that it can be added to the room with corresponding num.
*  Paramater: array of characters in the game.
*/
void randomizeCharacterNum(struct Character* characters[5]);
