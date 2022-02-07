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
    char inventory[10][30];
    int item_counter;
	Room* currentRoom;
}Player;


int drop_item(Player *p, Room* r);	//funktion för att spelaren ska kunna droppa item

int pick_up(Player* p, Room* r);	// Flyttar items från rummet till spelaren

int invent(Player* p);		// Skriver ut alla föremål som spelaren har på sig

int look(Room* r);		// Skriver ut alla föremål som finns i rummet till spelaren

int move(Player* p, int ID, Room rooms[]);	// Tries to move the player to the given room id, returns 0 succsession

int handle_commands(Player* p, char *str, Room rooms[]);	//funktion för commandon inmatat av spelaren

int room_count(FILE* world);		// Räknar antalet rum som finns i filen. Returnerar sedan antalet rum.

int find_connections(Player* p, char cmd[], Room rooms[]);	// Kollar om om det är en möjlig förflyttning av spelaren. Om så är fallet flyttar spelaren dit.

void read_world(Room rum[], int rooms, FILE* world);		// Läser igenom world. Skapar structar till varje rum, lägger dom i en lista.

int win_check(Player* p, Room* r);		// Kollar om Bilnyckeln ligger i hallen. Returnerar 1 om så är fallet. 

void startscreen(Player *p);		// Frågar efter namn av spelaren. Skriver sedan ut instruktionerna för spelet.
