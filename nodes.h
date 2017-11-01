
typedef struct Player
{
int xPosition;
int yPosition;
short health;
short mana;
short strength;
short intelligence;
}player;

typedef struct Monster
{ 
  int xPosition;
  int yPosition;
  char* name;
  short health;
  short mana;
  char** description;

}monster;

typedef struct Item
{
  short type;
    
}item;

