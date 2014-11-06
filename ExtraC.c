#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


/* Extra uppgift till C som man kan använda för att redovisa mål  */



struct vara_t {
  char namn[100];
  char beskrivning[1000];
  char plats_t[50];
  int pris;
  int antal;
  struct vara *next;
};

typedef struct db_t * DB;

struct db_t{
  struct vara_t *first;
  int antal;
};

// Kolla upp 
void add_to_db(DB db, struct vara_t * vara){
  vara->next=db->first;
  db->first=vara;
  db->antal++;
  printf("Info added to database\n");
}

// Lägg till


void print_item(struct vara_t *vara){
  printf("Namn: %s\nAntal: %d\nBeskrivning: %s\nPlats: %s\nPris: %d",
	 vara -> namn,
	 vara -> antal,
	 vara -> beskrivning,
	 vara -> plats_t,
	 vara -> pris);
}

char ask_char_question(char * q, char * a){
  printf("%s [%s]\n",q,a);
  while(true){
    char reply = tolower(getchar());
    while(getchar()!='\n');
    if(strchr(a,reply)){
      return (reply);
    }
    printf("Felaktigt svar, pröva [%s]\n",a);
  }
}

char ask_string_question(char * c){
  char b[500];  
  printf("Nämn %s: ", c);
  scanf("%[^\n]", b);
  while(getchar()!='\n');
}

void add_item(DB db){
  struct vara_t *vara = malloc(sizeof(struct vara_t));
  vara->namn = ask_string_question("Namn");
  vara->antal = ask_string_question("Antal");
  vara->beskrivning = ask_string_question("Beskrivning");
  vara->plats_t = ask_string_question("Plats");
  vara->pris = ask_string_question("Pris");
  print_item(vara);
  if(ask_char_question("\nSpara till Db?", "YyNn") == 'y'){
    add_to_db(db, vara);
  }else{
    free(vara);
  }
}



// Ta bort 

// Ångra vara 

// lagersaldo

// redigera vara 

// Avsluta




void print_main_menu(void){
  puts(" ____    ____       ");
  puts("/\\  _`\\ /\\  _`\\     ");
  puts("\\ \\ \\/\\ \\ \\ \\L\\ \\   ");
  puts(" \\ \\ \\ \\ \\ \\  _ <\\ ");
  puts("  \\ \\ \\_\\ \\ \\ \\L\\ \\ ");
  puts("   \\ \\____/\\ \\____/ ");
  puts("    \\/___/  \\/___/  ");
  puts("");
  puts("Please choose an operation");
  puts("");
  puts("A or a. Avsluta programet");
  puts("Z or z. Ångra vara (Ej implementerat");
  puts("L or l. Lägg till vara (Ej klart)");
  puts("T or t. Ta bort vara (Ej implementerat)");
  puts("R or r. Redigera vara (Ej implementerat)");
  puts("I or i. Skriv ut alla varor? (Ej implementerat)");
}

int main(){
  DB TEST = malloc(sizeof(struct db_t));
  TEST -> first = NULL;
  TEST -> antal = 0;
  while(true){
    print_main_menu();

    switch(ask_char_question("\nVad vill du göra idag?", "AaZzLlTtRrIi")){

      // case 'a': Avsluta
      // Vid ingång i case 6 så ska programet fråga, Vill du avsluta
      // programet? Om man inte vill det ska man då gå tillbaka till val
      //  av case. Annars så ska man då avsluta programet.
      
    case 'a':
      if(ask_char_question("Vill du avsluta programet?", "YyNn") == 'y'){
	return 0;
      }
      break;

      // case 3: Ångra vara 

    case 'z':
      printf("Du har inte implementerat Ångra\n");
      break;

      //  case 1: Lägg till vara 
      //  Be användaren att skriva vilken vara som ska läggas in.
      //  Om varan redan finns så berätta detta, annars så lägg till 
      //  varan, om det uppfyller alla kriterier.

    case 'l':
      //printf("Du har inte implementerat Lägg till\n");
      add_item(TEST);

      break;

      //  case 2: Ta bort vara
      //  kontrollera om varan existerar. Om den inte gör det, berätta 
      //  det för användaren annars ta bort sagd vara.

    case 't':
      printf("Du har inte implementerat Ta bort\n");
      break;

      //  case 5: Redigera vara 
      //  kontrollera om sagd vara existerar. Om den inte gör det, berätta
      //  det för användaren annars så finns möjlighet att redigera
      //  både varans namn och pris */

    case 'r':
      printf("Du har inte implementerat redigera\n");
      break;

      //  case 4: Printa lagersaldo (för specifik vara eller alla?) */

    case 'i':
      printf("du har inte implementerat listning av varor\n");
      break;
    }
      
      
  }
  return 0;
}
