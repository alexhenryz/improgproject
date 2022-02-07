#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../game.h"



//funktion för att spelaren ska kunna droppa item
int drop_item(Player *p, Room* r){ 
	char item[25];
	printf("Vilket item vill du släppa?\n");
	scanf("%s",item);
	
	for (int i = 0; i <= p->item_counter; i++){ //for loop som körs om spelaren har något item på sig
			if (!strcmp(p->inventory[i], item)){ //if sats som kollar om föremålet användaren skriver in finns i inventory
				if (r->item_counter + 1 >= 10){ //if sats som kollar om du kan släppa item på just den platsen
					printf("Du kan inte slänga några föremål här\n");
					return 1;
				}
			else{ //om det går körs detta
				strcpy(r->chest[r->item_counter], item); //item kopieras in till rummets chest 
				printf("Du släppte %s", item);
				r->item_counter++; //rummets item counter adderas med 1
				return 0;
			}
			}
		}
	printf("Du har inte %s i ditt inventory\n", item);
	return 1;
}

// Flyttar items från rummet till spelaren
int pick_up(Player* p, Room* r){
	char item[25];
	printf("Vilket item vill du ta upp?\n");
	scanf("%s",item);
	
	for (int i = 0; i <= r->item_counter; i++){//samma princip som drop_item funktionen men nu från rummet till spelaren 
			if (!strncmp(r->chest[i], item, strlen(item))){//kollar om item som vill plockas upp finns i rummet
				if (p->item_counter + 1 >= 10){ //if sats som kollar att spelarens inventory inte är full
					printf("Du kan inte ta upp fler föremål\n");
					return 1;
				}
			else{//om inventory inte full körs detta
				strcpy(p->inventory[p->item_counter], item);//item kopieras och läggs in i spelarens inventory
				p->item_counter++;
				printf("Du plockade upp %s \n", item);
				r->item_counter--;
				return 0;
			}
			}
		}
	printf("%s \n", r->chest[0]);
	printf("%s finns inte i rummet\n", item);
	return 1;
}

// Skriver ut alla föremål som spelaren har på sig
int invent(Player* p){
	if (p->item_counter <= 0){ //if sats som kollar om spelaren har något i inventory 
		printf("Du har inte några föremål i din väska \n");//om inget finns printas detta
		return 1;
	}
	//annars körs detta
	printf("I din väska finns: \n");
	for (int i = 0; i < p->item_counter; i++){//for loop som loopar antalet items spelaren har i inventory
		printf("%s ", p->inventory[i]);//printar ut varje item 
	}
	printf("\n");
	return 0;
}



// Skriver ut alla föremål som finns i rummet till spelaren
int look(Room* r){
	if (r->item_counter <= 0){ 
		printf("Du letar, men hittar ingenting i rummet \n");
		return 1;
	}
	//identisk funktion som invent funktionen men här är det rummets items som skrivs ut
	printf("Du letar i rummet och hittar: ");
	for (int i = 0; i < r->item_counter; i++){ 
		printf("%s ", r->chest[i]);
	}
	printf("\n");
	return 0;
}

// Tries to move the player to the given room id, returns 0 succsession
int move(Player* p, int ID, Room rooms[]){
	p->currentRoom = &rooms[ID-1];
	printf("Du går in i %s", p->currentRoom->brief);
	return 0;
}

//funktion för commandon inmatat av spelaren
int handle_commands(Player* p, char *str, Room rooms[])
{

    char *cmd = strtok(str, " ");
    //char *item = strtok(NULL, " ");

  
    if(!strcmp(cmd, "i")) //if sats för alla de olika kommandon i spelet 
        invent(p);
    else if(!strcmp(cmd, "n")) //n,e,w,s är rörelse kommandon som callar find_connections funktionen 
        find_connections(p, cmd, rooms);
    else if(!strcmp(cmd, "e"))
        find_connections(p, cmd, rooms);
    else if(!strcmp(cmd, "w"))
        find_connections(p, cmd, rooms);
    else if(!strcmp(cmd, "s"))
		find_connections(p, cmd, rooms);
    else if(!strcmp(cmd, "ta")) //för att plocka upp items, callar på pick_up funktionen 
        pick_up(p, p->currentRoom);
    else if(!strcmp(cmd, "släpp"))//för att släppa items, callar på drop_item funktionen
        drop_item(p, p->currentRoom);
    else if(!strcmp(cmd, "leta"))//för att leta i rummet och se vad för item som finns där, callar på look funktionen 
		look(p->currentRoom);
    else
        return -1;
    return 0;
}
