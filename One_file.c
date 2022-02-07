#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct Room
{
    int roomId;
    char brief[256];
    char full[256];
    char exits[10][10];
    int exit_count;
    char chest[12][12];
    int item_counter;
}Room;

typedef struct player{
	char name[20];
    int health;
    char inventory[10][30];
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


    int r = 0;
    while(!feof(world))
    {
        r++;
        //printf("går till rad %d\n",r);
        
        fgets(row, 256, world);
        if(!strncmp(row, "#ROOM_BEGIN", 11)) //Letar starttecken av rum i filen.
        {
            is_room = 1;
            continue;
        }
        
        if(!strncmp(row, "#ROOM_END", 9)) // Letar sluttecken av rum i filen.
        {
            rum[index].exit_count = exit_count;
            is_room = 0;
            exit_count = 0;
            index++;
           
            continue;
        }

        if(is_room)	//Kopierar alla information till structen. Om läsningen är i ett rum.
        {
            key = strtok(row, ":");
            value = strtok(NULL,  ":");
            
            
            if(key == NULL || value == NULL) continue;
            
            if(!strcmp(key, "id"))
                {
                rum[index].roomId = atoi(value);
                continue;
                }
            else if(!strcmp(key, "brief"))
            {
                strcpy(rum[index].brief, value);
                continue;
            }
            else if(!strcmp(key, "full"))
                {
                strcpy(rum[index].full, value);
                continue;
                }
            else if(!strcmp(key, "exit"))
            {
                strcpy(rum[index].exits[exit_count], value);
                exit_count++;
                continue;
            }
            else if(!strcmp(key, "item"))
            {
				rum[index].item_counter = 1;
				strcpy(rum[index].chest[0], value);
                printf("%s\n",rum[index].chest[0]);
                continue;
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
				if(!strcmp(a, r->chest[i]))
                    {
					    printf("\nDu kan ge dig iväg nu!\n\n");
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

int main()
{
	printf("test");
    char cmd[15]; // Lagrar input från spelaren
    FILE* world = fopen("world.txt","r"); // Filen som innehåller data för världen 

    Player *p = malloc(sizeof(Player));
    p->item_counter = 0; // Spelaren skapas och sätts till att inte ha några items

    int count = room_count(world); // Räknar antal rum för att kunna allokera rätt mängd minne
    printf("Rooms: %d\n", count);
    Room rum[count];
    startscreen(p);
 

    read_world(rum, count, world); // Läser in världen och använder count för att veta hur många rums som ska läsas in.
	p->currentRoom = &rum[0];
	int check = win_check(p, rum);
	
    while( check != 1)
    {
	    // Mainloopen skriver ut nödvändiga saker och läser sedan in användarens input och skickar med det till handle_commands
    	printf("%s \n", p->currentRoom->full);
        printf(">");
        scanf("%s",cmd);
        handle_commands(p, cmd, rum);
        printf("\n");
        check = win_check(p, rum);
    }
}
