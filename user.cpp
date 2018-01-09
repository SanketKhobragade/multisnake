#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "client.cpp"

using namespace std;
using namespace sf;
#define N 80
#define M 60

// Define all colours ->> Sprite sp[10];

int size=16;
int w = size*N;
int h = size*M;
int dir = rand()%4;
int **win=new int*[M];


Texture t[3];
Sprite sp[3];



void move(){
	int speedup = 0;
	dir = 1;
	/*if (Keyboard::isKeyPressed(Keyboard::Left)) dir=1;   
	if (Keyboard::isKeyPressed(Keyboard::Right))  dir=2;    
	if (Keyboard::isKeyPressed(Keyboard::Up)) dir=3;
	if (Keyboard::isKeyPressed(Keyboard::Down)) dir=0;
	if (Keyboard::isKeyPressed(Keyboard::Space)) speedup = 1;
	else	speedup = 0;*/
	//cout << "E1" << endl;
	send_sig(dir,speedup);
}

int main(){
	for(int i=0;i<M;i++){
		win[i]=new int[N];
	}
	
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++)
			win[i][j] = 0;
			
					
	char *ip = new char[20];
	int port;
	cout << "Enter ip and port :" ;
	cin >> ip >> port;
	con(ip,port);
	RenderWindow window(VideoMode(w, h), "Snake Game!");
	t[0].loadFromFile("images/green.png");
	t[1].loadFromFile("images/white.png");
	t[2].loadFromFile("images/red.png");
	for(int i = 0; i<3; i++)
		sp[i].setTexture(t[i]);
	while (window.isOpen()){
	//while(true){
		usleep(20000);
		Event e;
		while (window.pollEvent(e)){
		    if (e.type == Event::Closed)      
			window.close();
		}
		window.clear();
		
		move();
		usleep(20000);
		int ct = recieve_ct();
		recieve_sig(ct);	
		/*for (int i=0; i<N; i++){
			for (int j=0; j<M ; j++) {
		  		int col = win[j][i];
				if(col > 1 || col < -1)
					col = 1;
		  		sp[col+1].setPosition(i*size, j*size);
		  		window.draw(sp[col+1]);
		  	}
		}*/
	//	window.display();
	}
	return 0;
}
	
	 
		  		
		
	

