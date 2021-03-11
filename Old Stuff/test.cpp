//You may delet everything from here, but not me!
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<iostream>
#include<list>
#include <string.h> 
#include <bits/stdc++.h> 

vector<enemy_ship> enemies;
vector<enemy_ship>::iterator it;

int main ()
{
	for(int t = 2; t <=20; t++){
  	int num = rand() % t;
		printf("%i\n",t);
	}
  return 0;
}
