#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct enemy
{
	char name[10];
	int health;
    int damage;
}Enemy;

typedef struct room
{
    int roomId;
    char brief[256];
    char full[256];
    char exits[10][10];
    int exit_count;
    int chest[10];
    Enemy* enemy;
} Room;

typedef struct layer
{
    int roomCount;
    struct layer *next;
    struct room *room_list[10];
} Layer;

typedef struct player{
	char name[20];
    int health;
    int inventory[10];
    int item_counter;
	Layer* currentLayer;
	Room* currentRoom;
}Player;
typedef struct map
{
    int layerCount;
    Layer *head;
} Map;

void push_layer(Map *m)
{
    Layer *temp = m->head;
    m->head = malloc(sizeof(Layer));
    m->head->next = temp;
}

// void generate_roads(Layer *l, int n)
// {
//     for(int i = 0; i < n; ++i)
//     {
//         l->room_list[i] = malloc(sizeof(Room));
//         l->room_list[i]->roomId = i;
//         l->room_list[i]->exits[i] = 1;
//         l->roomCount++;
//     }
// }

// void generate_map(Map *m)
// {
    
//     for(int i = 0; i < m->layerCount; ++i)
//     {
//         push_layer(m);
//     }

// 	Layer *temp = m->head;
//     while(temp != NULL)
//     {
//         generate_roads(temp, 3);
//         temp = temp->next;
//     }
// }

void combat(Enemy* monster, Player* p)
{
    while(monster->health > 0)
    {
        p->health -= monster->damage;
        monster->health -= 5;
        printf("You took %d damage!\n", monster->damage);
        printf("You dealt %d damage to the %s!\n", 5, monster->name);
        printf("You have %d health left!", p->health);

        if(p->health <= 0)
        {
            printf("You lose!");
            exit(-1);
        }
    }
}

int move(Player* p, int roadIndex)
{
	if (p->currentRoom->exits[roadIndex] != 1 && roadIndex > 3)
    {
        printf("Denna gång finns inte!");
        return 1;
    }
		
	
	p->currentRoom = p->currentLayer->next->room_list[roadIndex];
	p->currentLayer = p->currentLayer->next;
    printf("Awoopie");
    if(p->currentRoom->enemy != NULL)
        combat(p->currentRoom->enemy, p);
	return 0;
}

//LÃgger till item till spelarens inventory och tar bort den ifrÃ¥n positionen
void add_item(Player *L, Room *P, int ID)
{
    
    int length = sizeof(L->inventory)/sizeof(L->inventory[0]);
    
    if (L->item_counter == 10)
    {
        printf("Din ryggsÃ¤ck Ã¤r full. Du mÃ¥sta slÃ¤ppa nÃ¥got fÃ¶r att ta upp mer.\n");
        return;
    }
    
    for ( int i =1;i<length;++i)
    {
        if (L->inventory[i]==0)
        {
            L->inventory[i] = ID;
            P->chest[i] = 0;
            L->item_counter++;
            return;
        }
    }    
}

//Tar bort item ifrÃ¥n spelares inventory och lÃ¤gger den pÃ¥ positionen
void remove_item(Player *L, Room *P, int ID)
{

    if (L->item_counter == 0)
    {
        printf("Din ryggsÃ¤ck Ã¤r tom, du kan inte slÃ¤ppa nÃ¥got.\n");
        return;
    }

    for (int i = 0; i<10;++i)
    {
        if (L->inventory[i] == ID)
        {
            L->inventory[i] = 0;
            for ( int j =1;j<10;++j)
            {
                if (P->chest[j] == 0)
                {
                    P->chest[j] = ID;
                    L->item_counter--; 
                    return;
                }
            }
        }
    }

       
}

// Tar bort alla items i inventory (SÃ¤tter alla slots till 0)
void release_all(Player *L)
{
    for (int i = 0; i<10;++i)
    {
        L->inventory[i]=0;
    }
}

void clear_room(Room *P1)
{
    for (int i = 0; i<10;++i)
    {
        P1->chest[i]=0;
    }
}

int handle_combat(Player* p, char *str)
{
    return 0;
}

int handle_commands(Player* p, char *str)
{

    char *cmd = strtok(str, " ");
    char *item = strtok(NULL, " ");

    //TODO(Alex): Call for functions specific to the commands entered by the user
    if(!strcmp(cmd, "i"))
        printf("inventory");
    else if(!strcmp(cmd, "n"))
        find_connections()
    else if(!strcmp(cmd, "e"))
        printf("e");
    else if(!strcmp(cmd, "w"))
        printf("w");
    else if(!strcmp(cmd, "ta"))
        printf("ta");
    else if(!strcmp(cmd, "släpp"))
        printf("släpp");
    else
        return -1;
}

int find_connections(Player* p, char cmd)
{
    Room *current_room = p->currentRoom;
    char direction;
    int roomId;

    //TODO(Alex): If the player is in a room that is connected to the command they entered move them otherwise return and print not work
    for(int i = 0; i < current_room->exit_count; i++)
    {
        direction = strtok(current_room->exits[i], " ");
        roomId = atoi(strtok(NULL, " "));

        if(!strcmp(direction, cmd))
        {
            move(p, roomId);
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

void read_world(Room room[], int rooms, FILE* world)
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
            room[index].exit_count = exit_count;
            is_room = 0;
            exit_count = 0;
            index++;
        }

        if(is_room)
        {
            key = strtok(row, ":");
            value = strtok(NULL,  ":");

            if(!strcmp(key, "id"))
                room[index].roomId = atoi(value);
            else if(!strcmp(key, "brief"))
            {
                strcpy(room[index].brief, value);
            }
            else if(!strcmp(key, "full"))
                strcpy(room[index].full, value);
            else if(!strcmp(key, "exit"))
            {
                strcpy(room[index].exits[exit_count], value);
                exit_count++;
            }
        }
    }
}

int main()
{
    char cmd[15];

    FILE* world = fopen("world.txt","r");
    Room rum[15];

    Player L;
    L.item_counter = 0;

    int count = room_count(world);
    printf("Rooms: %d\n", count);
    Room room[count];

    read_world(room, count, world);

    while(1)
    {
        printf(">");
        gets(cmd);
        handle_commands(&L, cmd);
        printf("\n");
    }
}
