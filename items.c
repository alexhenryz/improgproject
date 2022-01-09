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
