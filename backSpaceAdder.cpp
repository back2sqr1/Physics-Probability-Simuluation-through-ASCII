#include <iostream>
#include "draw.h"
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include <bits/stdc++.h>
using namespace std;
int main(){
	cout<<"How many lines?"<<endl;
	int n; cin>>n;
	string emp;
	getline(cin,emp);
	while(n--)
	{
		string s;
		getline(cin, s);
		cout<<endl;
		for(int i=0; i<s.length(); i++)
		{
			cout<<s[i];
			if(s[i]==92)
			cout<<"\\";
		}
		cout<<endl;
	}
}
//can elp add other escape keys
