#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char *monsters[] = {"Ogre", "Elf", "Goblin", "Slime", };
typedef struct room
{
    int roomId;
    char brief[254];
    char full[254];
    int exits[10];
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

typedef struct enemy
{
	char name[10];
	int health;
    int damage;
}Enemy;

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

void generate_roads(Layer *l, int n)
{
    for(int i = 0; i < n; ++i)
    {
        l->room_list[i] = malloc(sizeof(Room));
        l->room_list[i]->roomId = i;
        l->room_list[i]->exits[i] = 1;
        l->roomCount++;
    }
}

void generate_map(Map *m)
{
    
    for(int i = 0; i < m->layerCount; ++i)
    {
        push_layer(m);
    }

	Layer *temp = m->head;
    while(temp != NULL)
    {
        generate_roads(temp, 3);
        temp = temp->next;
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

    if(!strcmp(cmd, "i"))
        printf("inventory");
    else if(!strcmp(cmd, "n"))
        move(p, 0);
    else if(!strcmp(cmd, "e"))
        move(p, 1);
    else if(!strcmp(cmd, "w"))
        move(p, 2);
    else if(!strcmp(cmd, "ta"))
        return 1;
    else if(!strcmp(cmd, "släpp"))
        return 1;
    else
        return -1;
}



void read_world(Room rum[])
{
    FILE*file = fopen( "world.txt","r");

    char row[254];
    int is_room = 0;
    char *key;
    char *value;
    int counter = 0;

    while (!feof(file))
    {

        fgets(row,254,file);
        if(!strcmp(row,"#ROOM_BEGIN\n")){
            is_room = 1;

        }

        if(!strcmp(row,"#ROOM_END\n")){
            is_room = 0;
            continue;
        }

        if (is_room == 1){
            key = strtok(row,":");
            value = strtok(NULL,":");

            if(!strcmp(key,"ID"))
                strcpy(rum->roomId,value);
            if(!strcmp(key,"brief"))
                strcpy(rum->brief,value);
            if(!strcmp(key,"full"))
                strcpy(rum->full,value);
            if(!strcmp(key,"exit"))
                strcpy(rum->exits,value);

        } 
    ++counter;
    }
}

int main()
{
    char cmd[15];
    Map *m = malloc(sizeof(Map));
    m->head = NULL;
    m->layerCount = 3;

    generate_map(m);
    // printf("%d\n", m->head->room_list[1]->roomId);
    // printf("%d", m->head->room_list[2]->roads[1]);
    
    Player L;
    L.item_counter =0;
    

    release_all(&L);
    // Bara sÃ¥ att alla slots pÃ¥ plats 1 Ã¤r 0. Annars onÃ¶dig funktion.
    clear_room(m->head->room_list[0]);
    m->head->room_list[0]->chest[1] = 5;

    for (int i = 0; i<10;++i)
    {
        add_item(&L,m->head->room_list[0],i);
    }
    remove_item(&L,m->head->room_list[0],4);
    remove_item(&L,m->head->room_list[0],2);

	printf("%d ",m->head->room_list[0]->chest[1]);

    L.currentLayer = m->head;
    L.currentRoom = m->head->room_list[1];
    // printf("%p\n", L.currentRoom);
    while(1)
    {
        printf(">");
        gets(cmd);
        handle_commands(&L, cmd);
        printf("\n");
    }
}
