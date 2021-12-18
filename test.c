#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct room
{
    char roomId[10];
    int rooms[10];
} Room;

typedef struct layer
{
    int roomCount;
    struct layer *next;
    struct room *room_list[10];
} Layer;

// -----------------
typedef struct player{
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
// -----------------

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

// -------------------
int move(Player* p, int roadIndex)
{
	if (p->currentRoom->rooms[roadIndex] != 1 || roadIndex < 2)
		return 1;
	
	p->currentRoom = p->currentLayer->next->room_list[roadIndex];
	p->currentLayer = p->currentLayer->next;
	return 0;
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
	printf("%s tänker ", monster->name);
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
		
		printf("läka sig för %d ", monster->intention[1]);
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
// -------------------

int main()
{
    Map *m = malloc(sizeof(Map));
    m->head = NULL;
    m->layerCount = 3;

    generate_map(m);
    printf("%s\n", m->head->room_list[1]->roomId);
    printf("%d", m->head->room_list[2]->rooms[1]);
}
