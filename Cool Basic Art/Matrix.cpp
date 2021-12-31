#include <iostream>
#include <windows.h>
#include <unistd.h>
#include <chrono>
#define M_PI 3.14159265358979323846
#include <bits/stdc++.h>

using namespace std;
 
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BLINK 128

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
inline
char getChar() {
    int x = rand() % 4;
    switch (x) {
        case 0: return (char)(48 + rand() % 10);
        case 1: return (char)(97 + rand() % 26);
        
        default: return (char)(65 + rand() % 26);
    }
}
//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 
struct Ball{
	int y, x, dirX, dirY;
};
int main()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret;
    /* get the width of the console */
    ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    constexpr int WIDTH = 1320,HEIGHT = 720;
    constexpr int dW=8,dH=16;
    auto drawPoint = [&](char platno[HEIGHT/dH][WIDTH/dW+1],int A,int B,char c)
    {
    	if(A<0||B<0||A>=WIDTH/dW||B>=HEIGHT/dH)	return;
		platno[B][A]=c;
	};
	auto plotLineLow  = [&](char platno[HEIGHT/dH][WIDTH/dW+1],int x0,int y0,int x1,int y1,char c)
	{
		int dx = x1 - x0, dy = y1 - y0, yi = 1;
	    if (dy < 0)
	    {
	        yi = -1;
	        dy = -dy;
		}
	    int D = 2*dy - dx;
	    int y = y0;
	
	    for (int x=x0;x<=x1;x++)
	    {
	        drawPoint(platno,x,y,c);
	        if( D > 0)
	        {
	            y += yi;
	            D -= 2*dx;
			}
	        D += 2*dy;
		}
	};
	auto gotoxy = [&]( short x, short y)
	{
		COORD coord = {x, y};
		SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
	};
	auto plotLineHigh = [&](char platno[HEIGHT/dH][WIDTH/dW+1],int x0,int y0,int x1,int y1,char c)
	{
		int dx = x1 - x0, dy = y1 - y0, xi = 1;
	    if (dx < 0)
	    {
	        xi = -1;
	        dx = -dx;
		}
	    int D = 2*dx - dy;
	    int x = x0;
	
	    for (int y=y0;y<=y1;y++)
	    {
	        drawPoint(platno,x,y,c);
			if( D > 0)
	        {
	            x += xi;
	            D -= 2*dy;
			}
	        D += 2*dx;
		}
	};
	auto drawLine = [&](char platno[HEIGHT/dH][WIDTH/dW+1],int A,int B,int C,int D,char c)
    {
    	if(A>C)
		{
			int t;
			t=A;
			A=C;
			C=t;
			t=B;
			B=D;
			D=t;
		}
		//algorithm
		if(B==D)
		{
			for(int i=A;i<=C;i++)
				drawPoint(platno,i,B,c);//platno[B][i]=c;
			return;
		}
		if(A==C)
		{
			int min=B,max=D;
			if(D<B)
			{
				min=D;
				max=B;
			}
			for(int i=min;i<=max;i++)
				drawPoint(platno,A,i,c);//platno[i][A]=c;
			return;
		}
		if(abs(D-B)<abs(C-A))
			plotLineLow(platno,A,B,C,D,c);
		else
		{
			if(B>D)	plotLineHigh(platno,C,D,A,B,c);
			else	plotLineHigh(platno,A,B,C,D,c);
		}
	};
    float 
	l1,l2,	//lengths
	m1,m2,	//masses
	O1,O2,	//angles
	w1,w2,	//angular velocities
	g=9.81f;
	
	l1=150.0f;
	l2=150.0f;
	m1=10.0f;
	m2=10.0f;
	O1=2.0f*M_PI/2.0f;
	O2=2.0f*M_PI/3.0f;
	w1=0.0f;
	w2=0.0f;

	const float fps=300.0f;
	const float dt=1.0f/fps;
	float accumulator = 0.0f;
	Timer tmr;
	float frameStart=tmr.elapsed();
	
	char platno[HEIGHT/dH][WIDTH/dW+1];
	for(int i=0;i<HEIGHT/dH-1;i++)	platno[i][WIDTH/dW]='\n';
	platno[HEIGHT/dH-1][WIDTH/dW]='\0';
	for(int i=0;i<HEIGHT/dH;i++)
	{
		for(int j=0;j<WIDTH/dW;j++)
		{
			platno[i][j]=' ';
		}
	}
	

	
	//main loop
	vector<Ball> pts;
	Ball st; st.x=WIDTH/(2*dW), st.y=HEIGHT/(2*dH), st.dirX=1, st.dirY=1;
//	cout<<st.y<<' '<<st.x<<endl;
	Ball v; v.x=WIDTH/(2*dW), v.y=HEIGHT/(2*dH), v.dirX=-1, v.dirY=1;
	pts.push_back(v);
	pts.push_back(st);
	st.dirY*=-1;
	pts.push_back(st);
	v.dirY*=-1;
	pts.push_back(v);
	while(true)
	{
		gotoxy(0,0);
		
		int sz = pts.size();
		for(int i=0; i<sz; i++)
		{
			Ball& z = pts[i];
			platno[z.y][z.x] = getChar();
			if(z.y==HEIGHT/dH-1 && z.x==WIDTH/dW-1)
			z.x-=5, z.y-=3;
			if(z.y==HEIGHT/dH-1 || z.y==0)
			{
				z.dirY*=-1;
				if(rng()%2 && i==0)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
				else if(i==0)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			}
			if(z.x==WIDTH/dW-1|| z.x==0)
			{
				z.dirX*=-1;
				if(rng()%2 && i==0)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
				else if(i==0)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			}
			z.y+=z.dirY;
			z.x+=z.dirX;
//			cout<<z.y<<' '<<z.x<<endl;
			platno[z.y][z.x] = '*';
		}
		
		usleep(2000);
		puts(platno[0]);
	}
	return 0;
}