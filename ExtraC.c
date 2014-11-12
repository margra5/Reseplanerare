#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


/* Extra uppgift till C som man kan använda för att redovisa mål  */



struct vara_t {
  char *namn;
  char *beskrivning;
  char *plats_t;
  int pris;
  int antal_1;
  struct vara_t *next;
};

typedef struct db_t * DB;

struct db_t{
  struct vara_t *first;
  int antal_2;
  char last_used;
};


// Lägg till


void add_to_db(DB db, struct vara_t * vara){
  vara -> next = db -> first;
  db -> first = vara;
  db -> antal_2++;
  db -> last_used = 'l';
  printf("Info added to database\n");
}

void print_item(struct vara_t *vara){
  printf("          ========================================\n");
  printf("           %s\n           %d\n           %s\n           %s\n           %d\n",
	 vara -> namn,
	 vara -> antal_1,
	 vara -> beskrivning,
	 vara -> plats_t,
	 vara -> pris);
  printf("          ========================================\n");
};

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

char * ask_string_question(char * c){
  char* b = malloc(sizeof(char) * 500);
  printf("Nämn %s: ", c);
  scanf("%[^\n]", b);
  while(getchar()!='\n');
  return b;
}

void add_item(DB db){
  struct vara_t *vara = malloc(sizeof(struct vara_t));
  vara -> next = NULL;
  vara -> namn = ask_string_question("Namn");
  vara -> antal_1 = atoi(ask_string_question("Antal"));
  vara -> beskrivning = ask_string_question("Beskrivning");
  vara -> plats_t = ask_string_question("Plats");
  vara -> pris = atoi(ask_string_question("Pris"));
  print_item(vara);
  if(ask_char_question("\nSpara till Db?", "YyNn") == 'y'){
    add_to_db(db, vara);
  }else{
    free(vara);
  }
}

// Ta bort 

// Ångra vara

void undo(DB db_1, DB db_2){
  if (db_1 -> last_used == 'l'){
    printf("Senaste tilllagda varan har ångrats\n");
    db_1 -> first = db_1 -> first -> next;
    db_1 -> antal_2--;
    db_1 -> last_used = 'o';
  }
  /*
    else if(db_1 -> last_used == 'm'){
    printf("Ångra att du tog bort senast tillagd vara\n");
    db_2 -> first = db_1 -> first;
    db_1 -> antal_2++;
    db_1 -> last_used = 'l';
    }
  */
  else if (db_1 -> last_used == 'r'){
    printf("Senaste redigerade varan har ångrats\n");
    db_1 -> last_used = 'o';
  }
  else if (db_1 -> last_used == 't'){
    printf("Senaste borttagna varan har ångrats\n");
    db_1 -> last_used = 'o';
  } 
  else if (db_1 -> last_used == 'o'){
    printf("Det finns inget att ångra\n");
  }
  else {
    printf("last_used är satt till en odef char");
  } 
}


// lagersaldo

void print_all(DB db){
  int i;
  struct vara_t *vara = db -> first;
  if (db -> first == NULL){
    printf("Du har inga varor i databasen\n");
  }else{
    for(i = 0; i < db -> antal_2; i++){
      print_item(vara);
      vara = vara -> next;
    }
  }
}

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
  puts("Z or z. Ångra vara (Inte helt klar)");
  puts("L or l. Lägg till vara");
  puts("T or t. Ta bort vara (Ej implementerat)");
  puts("R or r. Redigera vara (Ej implementerat)");
  puts("I or i. Skriv ut alla varor?");
}

int main(){
  //vara_t vara = malloc(sizeof(struct vara_t));
  DB TEST = malloc(sizeof(struct db_t));
  DB Undo_db = malloc(sizeof(struct db_t));
  TEST -> first = NULL;
  TEST -> antal_2 = 0;
  TEST -> last_used = 'o';

  while(true){
    print_main_menu();

    switch(ask_char_question("\nVad vill du göra idag?", "AaZzLlTtRrIiQq")){

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
      undo(TEST, Undo_db);
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
      print_all(TEST);
      break;

    }   
  }
  return 0;
}
