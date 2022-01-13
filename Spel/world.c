#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "game.h"


// Läser igenom filen rad för rad och räknar hur många gånger raden "#ROOM_BEGIN" finns med för att se hur många rum som finns
int room_count(FILE* world)
{
    int count;
    char row[256]; // Lagrar raden som läses in
    while(!feof(world))
    {
        fgets(row, 256, world); // Läser 256 karaktärer på raden från filen world
        if(!strncmp(row, "#ROOM_BEGIN", 11))
            count++;
    }
    rewind(world); // Skickar tillbaka läsaren till toppen av filen
    return count; // Returnerar hur många rum som finns i filen
}


int find_connections(Player* p, char cmd[], Room rooms[])
{
    Room *current_room = p->currentRoom;
    char direction;
    int roomId;
	
    //TODO(Alex): If the player is in a room that is connected to the command they entered move them otherwise return and print not work
    for(int i = 0; i < current_room->exit_count; i++)
    {
        direction = current_room->exits[i][0];
        roomId = atoi(&current_room->exits[i][2]);
        
		
        if(direction == cmd[0])
        {
            move(p, roomId, rooms);
            return 1;
        }
    }

    printf("No room connected!!!!!!!!!!!!");
    return 0;
}


void read_world(Room rum[], int rooms, FILE* world)
{
    char row[256];
    int is_room = 0;
    char *key;
    char *value;
    int index = 0;
    int exit_count = 0;

    while(!feof(world))
    {
        fgets(row, 256, world);
        if(!strncmp(row, "#ROOM_BEGIN", 11))
        {
            is_room = 1;
        }
        
        if(!strncmp(row, "#ROOM_END", 9))
        {
            rum[index].exit_count = exit_count;
            is_room = 0;
            exit_count = 0;
            index++;
        }

        if(is_room)
        {
            key = strtok(row, ":");
            value = strtok(NULL,  ":");

            if(!strcmp(key, "id"))
                rum[index].roomId = atoi(value);
            else if(!strcmp(key, "brief"))
            {
                strcpy(rum[index].brief, value);
            }
            else if(!strcmp(key, "full"))
                strcpy(rum[index].full, value);
            else if(!strcmp(key, "exit"))
            {
                strcpy(rum[index].exits[exit_count], value);
                exit_count++;
            }
            else if(!strcmp(key, "item"))
            {
				rum[index].item_counter = 1;
				strcpy(rum[index].chest[0], value);
			}
        }
    }
}

int win_check(Player* p, Room* r){
	char a[] = {"Bilnyckel"};
	if (p->currentRoom->roomId == 1){
		if (r->item_counter >=1){
			for(int i = 0; i <= r->item_counter; i++){
				if(!strcmp(a, r->chest[i])){
					printf("\nDu kan ge dig iväg nu!\n");
					return 1;
					}
				}
			}
		}
	
	return 0;
}

void startscreen(Player *p){
    system("clear");
    printf("\t================================\n\t=====   SPELET HAR BÖRJAT  =====\n\t================================\n");
    printf("\nHej!\nVad heter du? ");
    scanf("%s",p->name);

    for (int i = 3; i>=0;--i){
        system("clear");
        printf("\n Välkommen, %s.\n\nSpelet börjar om %d!\n",p->name,i);
        sleep(1);
        system("clear");
    }
    system("clear");
    printf("Du är sen till tentan, du skyndar ut till bilen men inser att du har glömt bilnyckeln.\nDu förstår att du måste skynda dig in igen för att hitta bilnyckeln, men\ndu har glömt bort vart du har lagt den!\n\n");
    printf("Hitta bilnyckeln och ta med den tillbaka!!!\n\n");

}

