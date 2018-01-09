#define N 80
#define M 60
#include <stdint.h>
extern int FOO;
extern int CPU;
extern int size;
extern int w ;
extern int h ;
extern int win[M][N];
extern int counter;
extern int food_ct;
extern int dead_ct;
extern int change_ct;
extern int32_t change[1000];
struct food{
	int x;
	int y;
};
