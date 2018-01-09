#include "move.cpp"
#include "server.cpp"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#define N 80
#define M 60
int32_t change[1000];
int change_ct = 0;
int FOO = 5;
#define CPU 1
int size=16;
int w = size*N;
int h = size*M;
int win[M][N] = {0};
int counter = 1;


struct food f[100], dead[1000];
int food_ct = 0;
int dead_ct = 0;

int main(){
	Texture t[3];
	int input[2]={0};
	Sprite sprite[3];
	t[0].loadFromFile("images/green.png");
	t[1].loadFromFile("images/white.png");
	t[2].loadFromFile("images/red.png");
	for(int i = 0; i<3; i++)
		sprite[i].setTexture(t[i]);
	//con();
	srand(time(0));
	for(int i=0;i<FOO;i++){
		f[i].x = rand()%N;
		f[i].y = rand()%M;
		if(win[f[i].y][f[i].x] > 0)
			i--;
		else
			win[f[i].y][f[i].x] = -1;
	} 
	cpu *s[CPU];
	for(int i = 0; i<CPU; i++)
		s[i] = new cpu();
	user *s1 = new user;
	con();
	//RenderWindow window(VideoMode(w, h), "Snake Game!");
	//while (window.isOpen()){
	while(true){
		usleep(50000);
		change_ct = 0;
		/*Event e;
		while (window.pollEvent(e)){
		    if (e.type == Event::Closed)      
			window.close();
		}
		window.clear();*/
		cout << "recieve_Enter" << endl;
		recieve_sig(input);
		cout << "recieve_exit" << endl;
		for(int i = 0; i<CPU; i++){
			cout << "m1" << endl;
			cout << s[i]->num << endl;
			s[i]->run_cpu();
		}
		
		for(int i = 0; i<CPU; i++){
			if(s[i]->state == false){
				delete(s[i]);
				s[i] = new cpu();
			}
		}
		if(s1->state == false){
			delete(s1);
			s1 = new user();	
		}
		
		s1->run_user(input);
		
		cout << "m2" << endl;
		
		dead_ct = 0;
		//DRRW
		for (int i=0; i<N; i++) {
		  	for (int j=0; j<M ; j++) {
		  		if(win[j][i] == -1){
		  			dead[dead_ct].x = i;
		  			dead[dead_ct].y = j;
		  			dead_ct++;
		  		}
		  	}
		}
		usleep(50000);
		cout << "send_Enter" << endl;
		send_ct(change_ct);
		cout << "send _exit" << endl;
		//input[0] = 0;
		//input[1] = 0;
		//cout << input[0] << " " << input[1] << endl;
		//cout << s1->dir << endl;
		//s2->run_user(input);
		//usleep(10000);
		send_sig(change, change_ct);
		/*int col;
		for (int i=0; i<N; i++){
			for (int j=0; j<M ; j++) {
				col = win[j][i];
				if(col > 1)
				col = 1;
				//cout << col << endl;
		  		sprite[col+1].setPosition(i*size, j*size);
		  		window.draw(sprite[col+1]);
		  	}
		}
		for(int i = 0; i < FOO; i++){
			sprite[0].setPosition(f[i].x*size, f[i].y*size);
			window.draw(sprite[0]);
		}
		window.display();*/
	}
	return 0;
	
}

	
