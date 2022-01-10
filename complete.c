#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct room
{
    int roomId;
    char brief[256];
    char full[256];
    char exits[10][10];
    int exit_count;
    char chest[10][10];
    int item_counter;
} Room;

typedef struct player{
	char name[20];
    int health;
    char inventory[10][10];
    int item_counter;
	Room* currentRoom;
}Player;

// Flyttar items från spelarens iventory till rummet
int drop_item(Player *p, Room* r){
	char item[10];
	printf("Vilket item vill du släppa?\n");
	scanf("%s",item);
	
	for (int i = 0; i < p->item_counter; i++){
			if (!strcmp(p->inventory[i], item)){
				if (r->item_counter + 1 >= 10){
					printf("Du kan inte slänga några föremål här\n");
					return 1;
				}
			else{
				strcpy(r->chest[r->item_counter], item);
				printf("Du släppte %s", item);
				r->item_counter++;
				return 0;
			}
			}
		}
	printf("Du har inte %s i ditt inventory\n", item);
	return 1;
}

// Flyttar items från rummet till spelaren
int pick_up(Player* p, Room* r){
	char item[10];
	printf("Vilket item vill du ta upp?\n");
	scanf("%s",item);
	
	for (int i = 0; i < r->item_counter; i++){
			if (!strncmp(r->chest[i], item, strlen(item))){
				if (p->item_counter + 1 >= 10){
					printf("Du kan inte ta upp fler föremål\n");
					return 1;
				}
			else{
				strcpy(p->inventory[p->item_counter], item);
				p->item_counter++;
				printf("Du plockade upp %s \n", item);
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
	if (p->item_counter <= 0){
		printf("Du har inte några föremål i din väska \n");
		return 1;
	}
	
	printf("I din väska finns: \n");
	for (int i = 0; i < p->item_counter; i++){
		printf("%s ", p->inventory[i]);
	}
	printf("\n");
	return 0;
}

// Lägger till items i ett rum, skicka med en pekare till rummet och en sträng som är itemet.
int add_item(Room* r, char item[]){
	printf("%s \n", item);
	if (r->item_counter + 1 >= 10){
		printf("Kan inte lägga till fler föremål \n");
		return 1;
	}
	
	else{
		strcpy(r->chest[r->item_counter], item);
		r->item_counter++;
		
	}
	return 0;
}

// Skriver ut alla föremål som finns i rummet till spelaren
int look(Room* r){
	if (r->item_counter <= 0){
		printf("Du leter, men hittar ingenting i rummet \n");
		return 1;
	}
	
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

int room_count(FILE* world)
{
    int count;
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


int handle_commands(Player* p, char *str, Room rooms[])
{

    char *cmd = strtok(str, " ");
    //char *item = strtok(NULL, " ");

    //TODO(Alex): Call for functions specific to the commands entered by the user
    if(!strcmp(cmd, "i"))
        invent(p);
    else if(!strcmp(cmd, "n"))
        find_connections(p, cmd, rooms);
    else if(!strcmp(cmd, "e"))
        find_connections(p, cmd, rooms);
    else if(!strcmp(cmd, "w"))
        find_connections(p, cmd, rooms);
    else if(!strcmp(cmd, "s"))
		find_connections(p, cmd, rooms);
    else if(!strcmp(cmd, "ta"))
        pick_up(p, p->currentRoom);
    else if(!strcmp(cmd, "släpp"))
        drop_item(p, p->currentRoom);
    else if(!strcmp(cmd, "leta"))
		look(p->currentRoom);
	else if(!strcmp(cmd, "t"))
		printf("%s\n", rooms[1].exits[1]);
    else
        return -1;
    return 0;
}


void win_check(Player* p){
	if (p->currentRoom->roomId == 1){
		for(int i = 0; i < p->item_counter; i++){
			if(!strcmp(p->inventory[i], "Bilnyckel")){
				printf("Du kan nu ge dig iväg!");
				exit(0);
			}
		}
	}
}


int main()
{
    char cmd[15];

    FILE* world = fopen("world.txt","r");

    Player p;
    p.item_counter = 0;

    int count = room_count(world);
    printf("Rooms: %d\n", count);
    Room rum[count];

    read_world(rum, count, world);
	p.currentRoom = &rum[0];
	
    while(1)
    {
		printf("%s \n", p.currentRoom->full);
        printf(">");
        scanf("%s",cmd);
        handle_commands(&p, cmd, rum);
        printf("\n");
        win_check(&p);
    }
}
