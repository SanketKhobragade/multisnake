#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include "global.cpp"
using namespace sf;
using namespace std;
extern struct food f[100];
extern struct food dead[1000];
void add(int,int,int);
class snake{
	public:
		int dir;
		int prev_dir;
		int num;
		int id;
		Clock clk;
		float timer,delay;
		food *target;
		int speedup;
		bool state;
		int x[1000],y[1000],arr[4] = {0};
		bool player;
		snake(){

			speedup = 1;
			state = true;
			id = counter++;
			target = NULL;
			dir = rand()%4;
			prev_dir = dir;
			timer = 0.0;
			delay = 0.08;
			x[0] = rand()%N;
			y[0] = rand()%M;
			num = rand()%10 + 1;
			for(int i = 1; i<num; i++){
				if (dir==3){ y[i]= (y[i-1]+1)%M;      x[i] = x[i-1];}
				if (dir==2) {x[i]=((x[i-1]-1)+N)%N;       y[i] = y[i-1];}
				if (dir==1) {x[i]=(x[i-1]+1)%N;       y[i] = y[i-1];}
				if (dir==0) {y[i]=((y[i-1]-1)+M)%M; 	  x[i]  =x[i-1];}
				if(win[y[i]][x[i]] > 0)
					state = false;
			}
			if(state == true){
				for(int i = 0; i<num; i++){
					win[y[i]][x[i]] = id;
					add(y[i],x[i],id);
				}
					
			}
 		}
	
	public:
		void Tick();
};
void snake::Tick(){
	if(state == false)
		return;
	
	if(dir == 3-prev_dir){
		dir = prev_dir;
	}	
	win[y[num-1]][x[num-1]] = 0;
	add(y[num-1],x[num-1],0);
	
	for (int i=num-1;i>0;--i){
		x[i]=x[i-1];
	 	y[i]=y[i-1];
	 }

	if (dir==0) y[0] = (y[0]+1)%M;      
	if (dir==1) x[0] = ((x[0]-1)+N)%N;        
	if (dir==2) x[0] = (x[0]+1)%N;         
	if (dir==3) y[0] = ((y[0]-1)+M)%M; 
	
	add(y[0],x[0],id); 
	
	if(win[y[0]][x[0]] > 0 && win[y[0]][x[0]] != id){
		state = false;
		for(int i = 0; i < num; i++){
			win[y[i]][x[i]] = -1;
			add(y[i],x[i],-1);
			
		}
		return;
	}

	for(int i = 0 ; i<FOO; i++){
		if (((x[0]==f[i].x) && (y[0]==f[i].y))){ 
			if (dir==3) {y[num]=y[num-1]+1;	x[num] = x[num-1];}
			if (dir==2) {x[num]=x[num-1]-1;	y[num] = y[num-1];}
			if (dir==1) {x[num]=x[num-1]+1;	y[num] = y[num-1];}
			if (dir==0) {y[num]=y[num-1]-1;	x[num]  =x[num-1];}
		    	f[i].x=rand() % N;
			f[i].y=rand() % M;
			while(win[f[i].y][f[i].x] > 0){
				f[i].x=rand() % N;
				f[i].y=rand() % M;	
			}
			win[f[i].y][f[i].x] = -1; 
			add(f[i].y, f[i].x, -1);
		}
	}
	if(win[y[0]][x[0]] == -1){
		if (dir==3) {y[num]=y[num-1]+1;	x[num] = x[num-1];}
		if (dir==2) {x[num]=x[num-1]-1;	y[num] = y[num-1];}
		if (dir==1) {x[num]=x[num-1]+1;	y[num] = y[num-1];}
		if (dir==0) {y[num]=y[num-1]-1;	x[num] = x[num-1];}
		num++;
	}	
	for(int i = 0; i<num; i++)
		win[y[i]][x[i]]=id;
	add(y[num-1],x[num-1],id);
}
void add(int x, int y, int v){
	int a[2];
	int b[2];
	int c[2];
	a[0] = x/10;
	a[1] = x%10;
	b[0] = y/10;
	b[1] = y%10;
	c[0] = v >= 0 ? 1 : 0;
	c[1] = v >= 0 ? v : -v;
	int32_t f = a[0]*100000 + a[1]*10000 + b[0]*1000 + b[1]*100 + c[0]*10 + c[1]*1;
	change[change_ct++] = f;
}
