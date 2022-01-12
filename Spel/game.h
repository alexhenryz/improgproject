typedef struct Room
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


int drop_item(Player *p, Room* r);

int pick_up(Player* p, Room* r);

int invent(Player* p);

int add_item(Room* r, char item[]);

int look(Room* r);

int move(Player* p, int ID, Room rooms[]);

int handle_commands(Player* p, char *str, Room rooms[]);

int room_count(FILE* world);

int find_connections(Player* p, char cmd[], Room rooms[]);

void read_world(Room rum[], int rooms, FILE* world);

int win_check(Player* p, Room* r);

void startscreen(Player *p);
