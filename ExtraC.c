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

typedef struct db_2 * DB_2;

struct db_t{
  struct vara_t *first;
  int antal_2;
  char last_used;
};

struct db_2{
  struct vara_t *first;
  int antal_3;
};

int duplicate(DB db, char* c){
  struct vara_t *vara;
  for(vara = db->first; vara != NULL; vara = vara -> next){
    if(strcmp(vara->namn,c) == 0){
      printf("Du försöker skapa en duplicate\n");
      return 1;
    }else{
      return 0;
    }
  }
}

void add_to_db(DB db, struct vara_t * vara){
  vara -> next = db -> first;
  db -> first = vara;
  db -> antal_2++;
  db -> last_used = 'l';
  printf("Info added to database\n");
}


void add_to_db_2(DB_2 db_2, struct vara_t * vara){
  vara -> next = db_2 -> first;
  db_2 -> first = vara;
  db_2 -> antal_3++;
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
  if(duplicate(db, vara -> namn) == 0){
    if(ask_char_question("\nSpara till Db?", "YyNn") == 'y'){
      add_to_db(db, vara);
    }else{
      free(vara);
    }
  }
}



int djup(DB db){
  return db -> antal_2;
}

struct vara_t * search(DB db){
  int a = djup(db);
  struct vara_t *vara = db -> first;
  char *input = ask_string_question("DERP");
  for(int i = 0; i < a; i++){
    if(strcmp(input,db->first->namn)==0){
      return vara;
    }else{
      vara = db -> first -> next;
    }
  }
  return NULL;
}


void redigera_db(DB db_1, DB db_2){
  char* b = malloc(sizeof(char) * 500);
  if (db_1 -> first == NULL){
    printf("Du har inga varor i databasen\n");
  }else{
    struct vara_t *vara;
    printf("Varunamn: \n");
    scanf("%[^\n]",b);
    while(getchar() != '\n');
    for(vara = db_1->first;
	vara != NULL; 
	vara = vara -> next
	){
      if(strcmp(vara->namn,b) == 1){
	printf("Varan finns inte \n");
	break;
      }else{
	char q = ask_char_question("Vad vill du redigera", "NnBbAaPpSs");
	if(q == 'n'){
	  char* c = ask_string_question("Namn");
	  if(duplicate(db_1, c) == 0){
	    vara -> namn = c;
	    db_1 -> last_used = 'r';
	    printf("Varans namn har redigerats\n");
	    return;
	  }
	}
	else if(q == 'b'){
	  vara -> beskrivning = ask_string_question("Beskrivning");
	  db_1 -> last_used = 'r';
	  printf("Beskrivingen av varan har redigerats\n");
	  return;
	}
	else if(q == 'a'){
	  vara -> antal_1 = atoi(ask_string_question("Antal"));
	  db_1 -> last_used = 'r';
	  printf("Antalet varor har redigerats\n");
	  return;
	}
	else if(q == 'p'){
	  char* c = ask_string_question("Plats");
	  if(duplicate(db_1, c) == 0){
	    vara -> plats_t = c;
	    db_1 -> last_used = 'r';
	    printf("Varans plats har redigerats\n");
	    return;
	  }
	}
	else if(q == 's'){
	  vara -> pris = atoi(ask_string_question("Pris"));
	  db_1 -> last_used = 'r';
	  printf("Varans pris har redigerats\n");
	  return;
	}   
      }
    }
  }
}
// Lägg till


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
    printf("Inte Klart\n");
    //printf("Senaste redigerade varan har ångrats\n");
    db_1 -> last_used = 'o';
  }
  else if (db_1 -> last_used == 't'){
    printf("Inte implementerat\n");
    // printf("Senaste borttagna varan har ångrats\n");
    db_1 -> last_used = 'o';
  } 
  else if (db_1 -> last_used == 'o'){
    printf("Det finns inget att ångra\n");
  }
  else {
    printf("last_used är satt till en odef char");
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
  puts("R or r. Redigera vara");
  puts("I or i. Skriv ut alla varor?");
}

int main(){
  //vara_t vara = malloc(sizeof(struct vara_t));
  DB TEST = malloc(sizeof(struct db_t));
  DB Undo_db = malloc(sizeof(struct db_2));
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
      //      ta_bort(TEST);
      break;

      //  case 5: Redigera vara 
      //  kontrollera om sagd vara existerar. Om den inte gör det, berätta
      //  det för användaren annars så finns möjlighet att redigera
      //  både varans namn och pris */

    case 'r':

      redigera_db(TEST, Undo_db);
      break;
      
      //  case 4: Printa lagersaldo (för specifik vara eller alla?) */
      
    case 'i':
      print_all(TEST);
      printf("\n_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n");
      print_all(Undo_db);
      break;
    }   
  }
  return 0;
}
