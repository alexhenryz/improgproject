#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "game.h"

int main()
{
    char cmd[15]; // Lagrar input från spelaren
    FILE* world = fopen("world.txt","r"); // Filen som innehåller data för världen 

    Player p;
    p.item_counter = 0; // Spelaren skapas och sätts till att inte ha några items

    int count = room_count(world); // Räknar antal rum för att kunna allokera rätt mängd minne
    printf("Rooms: %d\n", count);
    Room rum[count];
    startscreen(&p);
 

    read_world(rum, count, world); // Läser in världen och använder count för att veta hur många rums som ska läsas in.
	p.currentRoom = &rum[0];
	int check = win_check(&p, rum);
	
    while( check != 1)
    {
	// Mainloopen skriver ut nödvändiga saker och läser sedan in användarens input och skickar med det till handle_commands
	printf("%s \n", p.currentRoom->full);
        printf(">");
        scanf("%s",cmd);
        handle_commands(&p, cmd, rum);
        printf("\n");
        check= win_check(&p, rum);
    }

}
