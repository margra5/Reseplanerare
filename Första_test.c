#include <stdlib.h>

struct node {
  int x;
  struct node *next;
};

int main()
{
    /* Det här kommer att vara den orörliga första noden */
    struct node *root;      

    /* Nu pekar root till en node struct */
    root = (struct node *) malloc( sizeof(struct node) ); 

    /* noden roots har sin nästa pekare lika med en null pekare */
    root->next = 0;  

    /* Genom att använda operatorn ->, can man modifiera vad noden,
       en pekare, pekar mot */
    root->x = 5;     
}
