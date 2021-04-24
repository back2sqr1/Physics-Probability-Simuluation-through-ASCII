#include <iostream>
#include "draw.h"
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include <random>
#include <bits/stdc++.h>
using namespace std;
class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    float elapsed() const { 
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<float, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};
constexpr int LENGTH=10;
char platno[HEIGHT/dH][WIDTH/dW+1];
class Walker{
	public:
		int x, y;
		int pX[LENGTH]={0}, pY[LENGTH]={0};
		Walker()
		{
			y=HEIGHT/dH/2;
			x=WIDTH/(dW)/2+1;
		}
		void walk(int a, int b){
			x+=a;
			y+=b;
			if(x<0 || y>=HEIGHT/dH || y<0 || x>=WIDTH/dW+1)
			{
				x=WIDTH/(dW)/2;
				y=HEIGHT/dH/2;
			}
		}
		
		void display()
		{
			drawPoint(platno, x, y, 'x');
			drawPoint(platno, pX[0], pY[0],' ' );
			for(int i=0; i<LENGTH-1; i++)
			{
				pX[i]=pX[i+1];
				pY[i]=pY[i+1];
			}
			pX[LENGTH-1]=x;
			pY[LENGTH-1]=y;
		}
};
void RandomWalker(int L, int R, int D)
{
	for(int i=0;i<HEIGHT/dH-1;i++)	platno[i][WIDTH/dW]='\n';
	platno[HEIGHT/dH-1][WIDTH/dW]='\0';
	for(int i=0;i<HEIGHT/dH;i++)
	{
		for(int j=0;j<WIDTH/dW;j++)
		{
			platno[i][j]=' ';
		}
	}
	Walker w;
   srand (time(NULL));
   while(true)
   {
   		gotoxy(0,0);
   		int dir=rand()%100+1;
   		if(dir<=L)
   		w.walk(-1, 0);
   		else if(dir<=R)
   		w.walk(1,0);
   		else if(dir<=D)
   		w.walk(0,1);
   		else
   		w.walk(0,-1);
   		
   		w.display();
   		puts(platno[0]);
   		cout<<w.x<<' '<<w.y<<' '<<dir<<' '<<endl;
   }
}
int main(){
	cout<<"What probabilities do you want? (Make sure they are less than 100 and add up to 100)"<<endl;
	int L, R, D, U;
	printf("Left: ");
	scanf("%i", &L);
	printf("Right: ");
	scanf("%i", &R);
	printf("Down: ");
	scanf("%i", &D);
	printf("Up: ");
	scanf("%i", &U);
	R+=L; D+=R; 
	RandomWalker(L, R, D);
}

