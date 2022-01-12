#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "game.h"

int main()
{
    char cmd[15];

    FILE* world = fopen("world.txt","r");


    Player p;
    p.item_counter = 0;

    int count = room_count(world);
    printf("Rooms: %d\n", count);
    Room rum[count];
    startscreen(&p);
 

    read_world(rum, count, world);
	p.currentRoom = &rum[0];
	int check = win_check(&p, rum);
    while( check != 1)
    {
		printf("%s \n", p.currentRoom->full);
        printf(">");
        scanf("%s",cmd);
        handle_commands(&p, cmd, rum);
        printf("\n");
        check= win_check(&p, rum);
    }

}
