#include "characters.h"
#include <string.h>

struct Character* character(char* charName, int num, struct Character* next) {
    struct Character* node;
     node = (struct Character*) malloc(sizeof(struct Character));
     node->charName = charName;
     node->num = num;
     node->next = next;
     return node;
}




void randomizeCharacterNum(struct Character* characters[5]) {
    int numList[5] = {-1, -1, -1, -1, -1};
    int  j = 0;
    int found = 0;
    for(int i = 0; i < 5; ++i) {
        found = 0;
        characters[i]->num = (rand() % 9);
        for(int k = 0; k < 5; ++k) {
            if(numList[k] == characters[i]->num) {
                found = 1;
            }

        }
        if(found == 0){
                numList[j] = characters[i]->num;
                ++j;
        }
        else {
            --i;
        }
    }
}

char* characterName1 = "Booker";
char* characterName2 = "Alex";
char* characterName3 = "Andrew";
char* characterName4 = "Comstock";
char* characterName5 = "Anabelle";

