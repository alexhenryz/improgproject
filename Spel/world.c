#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../game.h"


// Räknar antalet rum som finns i filen. Returnerar sedan antalet rum.
int room_count(FILE* world)
{
    int count = 0;
    char row[256];
    while(!feof(world))
    {
        fgets(row, 256, world);
        if(!strncmp(row, "#ROOM_BEGIN", 11))
            count++;
    }
    rewind(world);
    return count;
}

// Kollar om om det är en möjlig förflyttning av spelaren. Om så är fallet flyttar spelaren dit.
int find_connections(Player* p, char cmd[], Room rooms[])
{
	Room *current_room = p->currentRoom;
    char direction;
    int roomId;
	
    
    for(int i = 0; i < current_room->exit_count; i++)
    {
        direction = current_room->exits[i][0];
        roomId = atoi(&current_room->exits[i][2]);
        
		
        if(direction == cmd[0])
        {
            move(p, roomId, rooms); // Om rummen har en passage mellan sig förflyttas spelaren det rummet och returner sedan 1.
            return 1;
        }
    }

    printf("Finns inget rum i den riktningen"); // Om rummen inte har en passage returneras 0.
    return 0;
}

// Läser igenom world. Skapar structar till varje rum, lägger dom i en lista.
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
        if(!strncmp(row, "#ROOM_BEGIN", 11)) //Letar starttecken av rum i filen.
        {
            is_room = 1;
        }
        
        if(!strncmp(row, "#ROOM_END", 9)) // Letar sluttecken av rum i filen.
        {
            rum[index].exit_count = exit_count;
            is_room = 0;
            exit_count = 0;
            index++;
        }

        if(is_room)	//Kopierar alla information till structen. Om läsningen är i ett rum.
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

// Kollar om Bilnyckeln ligger i hallen. Returnerar 1 om så är fallet. 
int win_check(Player* p, Room* r){  
	char a[] = {"Bilnyckel"};
	if (p->currentRoom->roomId == 1){
		if (r->item_counter >=1){
			for(int i = 0; i <= r->item_counter; i++){
                printf("buh");
				if(!strcmp(a, r->chest[i]))
                    {
					    printf("\nDu kan ge dig iväg nu!\n");
					    return 1;
					}
				}
			}
		}
	
	return 0; // Returnerar 0 om bilnyckeln inte är i hallen.
}

// Frågar efter namn av spelaren. Skriver sedan ut instruktionerna för spelet.
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

