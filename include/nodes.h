
typedef struct _player
{
int xPosition;
int yPosition;
short health;
short mana;
short strength;
short intelligence;
}player;

typedef struct _monster
{ 
  int xPosition;
  int yPosition;
  char* name;
  short health;
  short mana;
  char** description;

}monster;

typedef struct _item
{
  short type;
    
}item;

