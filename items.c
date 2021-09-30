#include "items.h"
#include <string.h>

struct Item* item(char* itemName,int num, struct Item* next)  {
    struct Item*  node;
    node  =  (struct Item*) malloc(sizeof(struct Item));
    node->itemName = itemName;
    node->next = next;
    node->num = num;
    return node;
}

void takeItem(struct Item* inventory, struct Item* roomItem) {
        struct Item* ptr = (struct Item*) malloc(sizeof(struct Item));
        ptr = inventory;
        while(ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = roomItem;

    printf("Item taken.\n");
    //free(ptr);
}

struct Item* dropItem(struct Item* inventory, char* object) {
    struct Item* ptr = (struct Item*) malloc(sizeof(struct Item));
    ptr = inventory->next;
    int found = 0;
    while(ptr != NULL) {
        if(strcasecmp(ptr->itemName, object) == 0) {
            found = 1;
            break;
        }
        ptr = ptr->next;
    }
    if(found == 0) {
        printf("Item not found. Try again.\n");
        return NULL;
    }

    ptr = inventory->next;
    struct Item* prevPtr = (struct Item*) malloc(sizeof(struct Item));
    struct Item* node = (struct Item*) malloc(sizeof(struct Item));
    prevPtr = inventory;

    while(ptr != NULL) {
       if(strcasecmp(ptr->itemName, object) == 0) {
           if(ptr->next == NULL) {
               prevPtr->next = NULL;
               node = ptr;
               return node;
           }
       }

       if(strcasecmp(ptr->itemName, object) == 0){
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
    return NULL;

}

void randomizeItemNum(struct Item* items[6]) {
    int numList[6] = {-1, -1, -1, -1, -1, -1};
    int  j = 0;
    int found = 0;
    for(int i = 0; i < 6; ++i) {
        found = 0;
        items[i]->num = (rand() % 9);
        for(int k = 0; k < 6; ++k) {
            if(numList[k] == items[i]->num) {
                found = 1;
            }
        }
        if(found == 0){
                numList[j] = items[i]->num;
                ++j;
        }
        else {
            --i;
        }
    }
}

char* itemName1 = "Handgun";
char* itemName2 = "RayGun";
char* itemName3 = "Knife";
char* itemName4 = "crowbar";
char* itemName5 = "Taser";
char* itemName6 = "Chainsaw";
