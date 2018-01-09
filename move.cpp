#include <time.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Snake.cpp"
using namespace std;
using namespace sf;
class cpu : public snake{
	public:
		void run_cpu();
		void move();
		void set_food();
		void eat_food();
		bool Check_food(int);
		int dodge();
		bool Check_danger(int);
};
void cpu :: run_cpu(){
	float time = clk.getElapsedTime().asSeconds();
	clk.restart();	
	timer += time;
	move();
	if(timer > delay){
		timer = 0.0;
		Tick();
		prev_dir = dir;	
	}	
}
void cpu::move(){
	set_food();
	eat_food();
	dir = dodge();
}
void cpu :: set_food(){
	int min = 99999999;
	int min_index=0;
	if(dead_ct > 0){
		for(int i=0;i<dead_ct;i++){
			if(((x[0]-dead[i].x)*(x[0]-dead[i].x) + (y[0]-dead[i].y)*(y[0]-dead[i].y)) < min){
				min_index = i;
				min = ((x[0]-dead[i].x)*(x[0]-dead[i].x) + (y[0]-dead[i].y)*(y[0]-dead[i].y));
			}
		}
		target = &dead[min_index];	
	}
	else{
		for(int i=0;i<food_ct;i++){
			if(((x[0]-f[i].x)*(x[0]-f[i].x) + (y[0]-f[i].y)*(y[0]-f[i].y)) < min){
				min_index = i;
				min = ((x[0]-f[i].x)*(x[0]-f[i].x) + (y[0]-f[i].y)*(y[0]-f[i].y));
			}
		}
		target = &f[min_index];
	}
}

void cpu::eat_food(){
	int i;
	int beg = 0, end = 2; 
	if(Check_food(prev_dir) == true){
		arr[0] = prev_dir;
		beg = 1;
	}
	else{
		arr[1]=prev_dir;
		beg = 0;
	}
	for(i=0; i<4;i++){
		if(i == 3 - prev_dir)
			arr[3] = i;
		else if(Check_food(i) == false && i!=prev_dir && i!=3-prev_dir && end==2)
				arr[end--] = i;
		else if(i!=prev_dir)
				arr[beg] = i;
	}
	
}

bool cpu::Check_food(int direct){
	if(direct == 0  && target->y > y[0])
		return true;
	if(direct == 1  && target->x < x[0])
		return true;
	if(direct == 2  && target->x > x[0])
		return true;
	if(direct == 3  && target->y < y[0])
		return true;
	return false;
}

int cpu::dodge(){
	bool b1 = Check_danger(arr[0]);
	bool b2 = Check_danger(arr[1]);
	bool b3 = Check_danger(arr[2]);
	if(b1 == false)
		return arr[0];
	else if(b2 == false)
		return arr[1];
	else
		return arr[2];
}
bool cpu::Check_danger(int direction){
	bool b1, b2, b3;
	int i = rand() % 100;
	if(direction == 0)
		for(int j = 1; j <= 3; j++)
			 if(win[(y[0]+j+M)%M][x[0]] > 0 && win[(y[0]+j+M)%M][x[0]] != id)
			 	return i < 60 ? true: false;
	if(direction == 1)
		for(int j = 1; j <= 3; j++)
			 if(win[y[0]][(x[0]-j+N)%N] > 0 && win[y[0]][(N+x[0]-j)%N] != id)
			 	return i < 60 ? true: false;
	if(direction == 2)
		for(int j = 1; j <= 3; j++)
			 if(win[y[0]][(N+x[0]+j)%N] > 0 && win[y[0]][(N+x[0]+j)%N] != id)
			 	return i < 60 ? true: false;
	if(direction == 3)
		for(int j = 1; j <= 3; j++)
			 if(win[(M+y[0]-j)%M][x[0]] > 0 && win[(M+y[0]-j)%M][x[0]] != id)
			 	return i < 60 ? true: false;
	return false;
}


class user : public snake{
	public:
		int arr[2];
	public:
		void run_user(int * input);
		void speed();
		void move();
};

void user:: speed(){
	if(delay - 0.04 < 0.0001){
		speedup++;
	}
	if(speedup%20 == 0 && num > 1){
		num--;
		win[y[num]][x[num]] = 0;
		speedup = 1;
	}
}
void user:: move(){
	dir = arr[0];
	delay = arr[1] == 0 ? 0.08 : 0.04;
}
void user :: run_user(int * input){
	arr[0] = input[0];
	arr[1] = input[1];
	float time = clk.getElapsedTime().asSeconds();
	clk.restart();	
	timer += time;
	move();
	if(timer > delay){
		speed();
		timer = 0.0;
		Tick();
		prev_dir = dir;	
	}	
}
