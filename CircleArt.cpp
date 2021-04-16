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
constexpr double pi= 2*acos(0.0);
int main(){
	for(int i=0;i<HEIGHT/dH-1;i++)	platno[i][WIDTH/dW]='\n';
	platno[HEIGHT/dH-1][WIDTH/dW]='\0';
	for(int i=0;i<HEIGHT/dH;i++)
	{
		for(int j=0;j<WIDTH/dW;j++)
		{
			platno[i][j]=' ';
		}
	}
	double step= 2*pi/20;
	int h=50, k=25, r=15;
	drawPoint(platno, h, k, '*');
	int pX=h+r*cos(0), pY=k-r*sin(0);
	int a=h+r*cos(0), b= k+r*sin(0);
	for(double theta=step; theta<2*pi; theta+=step)
	{
		gotoxy(0,0);
		int x= h+r*cos(theta);
		int y=k-r*sin(theta);
		drawLine(platno, pX, pY, x, y, 'X');
		//drawLine(platno, h, k, x, y, 'X');
		pX=x;
		pY=y;
		puts(platno[0]);
		cout<<pX<<' '<<pY<<' '<<x<<' '<<y<<endl;
	}
	gotoxy(0,0);
	drawLine(platno, a, b, pX, pY, 'X');
	//drawLine(platno, h, k, a, b, 'X');
	puts(platno[0]);
	
}

