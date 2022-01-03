#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct room
{
    char roomId[10];
    int rooms[10];
    int chest[10];
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
	int totalActions;
	int actions[10][3]; // Actions are a array with 3 elements [Damaging, blocking, healing]
	int intention[3];
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

void generate_rooms(Layer *l, int n)
{
    for(int i = 0; i < n; ++i)
    {
        l->room_list[i] = malloc(sizeof(Room));
        strcpy(l->room_list[i]->roomId, "hello");
        l->room_list[i]->rooms[i] = i;
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
        generate_rooms(temp, 3);
        temp = temp->next;
    }
}

int move(Player* p, int roadIndex)
{
	if (p->currentRoom->rooms[roadIndex] != 1 || roadIndex < 2)
		return 1;
	
	p->currentRoom = p->currentLayer->next->room_list[roadIndex];
	p->currentLayer = p->currentLayer->next;
	return 0;
}

int enemy_attack(Enemy* monster, Player* hero){
	
}

int generate_intention(Enemy* monster)
{
	int index;
	
	if (monster->totalActions == 0)
		return 1; // Cannot generate random action if monster does not have any actions
		
	srand(time(NULL)); // Sets the seed to the current time
	index = rand() % monster->totalActions;
	
	for (int i = 0; i < 3; i++) // Copies an action into the monsters intention
		monster->intention[i] = monster->actions[index][i]; 
	
	return 0;
}

int display_intention(Enemy *monster)
{
	printf("%s tÃ¤nker ", monster->name);
	if (monster->intention[0] != 0)
		printf("skada dig med %d", monster->intention[0]);
		
	if (monster->intention[1] != 0){
		if (monster->intention[0] != 0)
			printf("och ");
		
		printf("skydda sig med %d ", monster->intention[1]);
	}
	
	if (monster->intention[0] != 0 || monster->intention[1] != 0){
		if (monster->intention[0] != 0)
			printf("och ");
		
		printf("lÃ¤ka sig fÃ¶r %d ", monster->intention[1]);
	}
	
	printf("\n");
	return 0;
}

int combat(Enemy* monster, Player* hero)
{
	generate_intention(monster);
	display_intention(monster);
	
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

int main()
{
    Map *m = malloc(sizeof(Map));
    m->head = NULL;
    m->layerCount = 3;

    generate_map(m);
    printf("%s\n", m->head->room_list[1]->roomId);
    printf("%d", m->head->room_list[2]->rooms[1]);
    
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
}
