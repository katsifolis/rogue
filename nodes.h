
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
  char* name;
  short health;
  short mana;

}monster;

typedef struct Item
{
  short type;
    
}item;

#define CMWC_CYCLE 4096
#define CMWC_C_MAX 809430660

struct cmwc_state{
  unsigned int Q[CMWC_CYCLE];
  unsigned int c; // Must be limited from cmwcmax
  unsigned i;
};
