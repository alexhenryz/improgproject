#include <stdio.h>
#include <stdlib.h>


typedef struct 
{
    char name[20];
    int position;
    int inventory[10];
    int item_counter;

}player;

// EN struct för varje plats.
typedef struct
{
    int chest[10];
    int position;
}plats;


//LÄgger till item till spelarens inventory och tar bort den ifrån positionen
void add_item(player *L,plats *P, int ID)
{
    
    int lenght = sizeof(L->inventory)/sizeof(L->inventory[0]);
    
    if (L->item_counter == 10)
    {
        printf("Din ryggsäck är full. Du måsta släppa något för att ta upp mer.\n");
        return;
    }
    
    for ( int i =1;i<10;++i)
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

//Tar bort item ifrån spelares inventory och lägger den på positionen
void remove_item(player *L, plats *P, int ID)
{

    if (L->item_counter == 0)
    {
        printf("Din ryggsäck är tom, du kan inte släppa något.\n");
        return;
    }

    for (int i = 0; i<10;++i)
    {
        if (L->inventory[i] == ID)
        {
            L->inventory[i] = 0;
            for ( int j =1;j<10;++j)
            {
                if (P->chest[j] ==0)
                {
                    P->chest[j] = ID;
                    L->item_counter--; 
                    return;
                }
            }
        }
    }

       
}

// Tar bort alla items i inventory (Sätter alla slots till 0)
void release_all(player *L)
{
    for (int i = 0; i<10;++i)
    {
        L->inventory[i]=0;
    }
}

void rensa_plats(plats *P1)
{
    for (int i = 0; i<10;++i)
    {
        P1->chest[i]=0;
    }
}

//ÖNÖDIG
void items_i_ryggsäck(player *L)
{
    printf("Du har: ");
        for (int i = 1; i < 10; ++i)
        {
            if (L->inventory[i] != 0)
            {
                printf("%d ",L->inventory[i]);
    
            }
        }   
    printf("\n");
}

//ÖNDÖDIG dvs testfunktion konstruerad till test.
void item_i_chest(plats *P)
{
    printf("I kistan finns: ");
        for (int i = 1; i < 10; ++i)
        {
            if (P->chest[i] != 0)
            {
                printf("%d ",P->chest[i]);
    
            }
        } 
    printf("\n");  
}

int main()
{
    player L;
    plats P1;
    int lenght = sizeof(L.inventory)/sizeof(L.inventory[0]);
    L.item_counter =0;
    

    release_all(&L);
    // Bara så att alla slots på plats 1 är 0. Annars onödig funktion.
    rensa_plats(&P1);
    P1.chest[1] = 5;

    

    for (int i = 0; i<10;++i)
    {
        add_item(&L,&P1,i);
    }
    remove_item(&L,&P1,4);
    remove_item(&L,&P1,2);

    items_i_ryggsäck(&L);
    item_i_chest(&P1);

    //for (int j = 0; j<10;++j)   { 
    //printf("Inventory: %d\n",L.inventory[j]);
    //printf("Kistplats:  %d\n",P1.chest[j]);
    //}
    return 0;
} 
