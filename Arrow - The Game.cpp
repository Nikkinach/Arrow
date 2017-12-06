#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

void clreol()
{
	cout << '\r';
	for (int i = 0; i < 40; ++i)
		cout << ' ';
	cout << '\r';
}

void gotoxy(int x, int y)		// function is defined below after main
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition);
}

const int size = 20;																					  //global variables
const int value = 25;
char map[size][value];
int ch = 0;
int opt = 0;
int hintcount=0;

struct windo
{
	char dir[10];
	int wspeed;
}wid;

int boards()                                                                                            //function to ask user for level
{
	cout << "Choose the level you wish to play:\n";
	int menu_item=0, run, x=7;
	bool running = true;

	gotoxy(18,5); cout << "Levels";
	gotoxy(18,7); cout << "->";

	while(running)
	{
        gotoxy(20,7);  cout << "1) Level 1";
		gotoxy(20,8);  cout << "2) Level 2";
		gotoxy(20,9);  cout << "3) Level 3";
		gotoxy(20,10); cout << "4) Level 4";
		gotoxy(20,11); cout << "5) Level 5";
		gotoxy(20,12); cout << "6) Level 6";

		system("pause>nul"); // the >nul bit causes it the print no message

		if(GetAsyncKeyState(VK_DOWN) && x != 13) //down button pressed
			{
				gotoxy(18,x); cout << "  ";
				if (x == 12)
					{
					x = 7;
					menu_item = 0;
					}
				else 
					{
					x++;
					menu_item++;
					}
				gotoxy(18,x); cout << "->";
				continue;
			}

		if(GetAsyncKeyState(VK_UP) && x != 6) //up button pressed
			{
				gotoxy(18,x); cout << "  ";\
				if (x == 7)
					{
					x = 12;
					menu_item = 5;
					}
				else
					{
					x--;
					menu_item--;
					}
				gotoxy(18,x); cout << "->";
				continue;
			}

		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed

			switch(menu_item){

				case 0: {
					return 1;		  
					break;
				}


				case 1: {
					return 2;
					break;
				}

				case 2: {
					return 3;
					break;
				}

				case 3: {
					return 4;
					break;
				}
				
				case 4: {
					return 5;
					break;
				}
				
				case 5: {
					return 6;
					break;
				}

			}
		}
	}
	system("cls");
}

class Map
{
	char bmap[11][25];
	int m;
	int l;
	int check;

	public:
	int x;
	int z;
	int counter;
	Map()
	{
		m = 0;
		l = 0;
		x = 1;
		z = 24;
		counter = 0;
		check = 1;
	}
	void target(int i, int j, char ar[][25], char k);
	void goal(int i, int l, int j, char ar[][25], char k);
	void babydisplay();
	void display();
	void showmap() ;
}game;

void Map:: target(int i, int j, char ar[][25], char k)
{
	if (ch == 1)
	{
		for (int m=i;m<20-fabs(i);m++)
		{
			ar[m][j] = k;
		}
	}

	else if (ch == 2)
	{
		for (int m = i + 9; m < 18 - fabs(i);m++)
			ar[m][j] = k;
		for (int m = i; m < 9 - fabs(i);m++)
			ar[m][j] = k;
	}
	else if (ch == 5)
	{
		for (int m = fabs(i+9); m < 19 - fabs(i);m++)
			ar[m][j] = k;
		for (int m = fabs(i); m < 10 - fabs(i);m++)
			ar[m][j] = k;
	}
	else if(ch == 3 || ch == 4 || ch == 6)
	{
		for (int m=fabs(i);m<20-fabs(i);m++)
			ar[m][j] = k;
	}
}

void Map :: goal(int i, int l, int j, char ar[][25], char k)                                                   //function to assign values for the moving target
{
	for (int m = i; m <= l;m++)
	{
		ar[m][j] = k;
	}
}

void Map :: babydisplay()                                                                                        //function to show a small map during input
{
	int i = 0 , j = 0;
	for (i=0 ; i<11 ; i++)
	{
		for (j=0 ; j<20 ; j++)
		{
			bmap[i][j] = ' ';
		}
	}
	cout << "+############################################################+" << endl;
	goal(1,9,19,bmap,'|');
	goal(2,8,18,bmap,'+');
	goal(3,7,17,bmap,'+');
	goal(4,6,17,bmap,'*');
	goal(5,5,17,bmap,'<');
	for (i=0 ; i<11 ; i++)
	{
		cout << '|';
		for (j=0 ; j<20 ; j++)
		{
			cout << ' ' << bmap[i][j] << ' ';
		}
		cout << '|';
		cout << endl;
	}
	cout << "+############################################################+" << endl;
	gotoxy(50,16);
	cout << "@";
	gotoxy(0,20);
	cout << "The '@' shows where the projectile will land with angle = 45 and speed = 100. ";
}

void Map :: display()                                                                                          //function to display the various types of board depending on level
{
	for (long int d=0;d<22222222;d++);
	if (ch == 1)
	{
		system("cls");
		cout << "+###########################################################################+" << endl;
		int i = 0 , j = 0;
		target(1,24,map,'|');
		target(2,23,map,'+');
		target(4,22,map,'+');
		target(5,22,map,'*');
		target(9,22,map,'<');
		for (i=0 ; i<size ; i++)
		{
			cout << '|';
			for (j=0 ; j<value ; j++)
			{
				cout << ' ' << map[i][j] << ' ';
			}
			cout << '|';
			cout << endl;
		}
		cout << "+###########################################################################+" << endl;
	}
	else if(ch == 2)
	{
		system("cls");
		cout << "+###########################################################################+" << endl;
		int i = 0 , j = 0;
		target(1,24,map,'|');
		target(2,23,map,'+');
		target(3,22,map,'*');
		target(4,22,map,'<');
		for (i=0 ; i<size ; i++)
		{
			cout << '|';
			for (j=0 ; j<value ; j++)
			{
				cout << ' ' << map[i][j] << ' ';
			}
			cout << '|';
			cout << endl;
		}
		cout << "+###########################################################################+" << endl;
	}
	else if (ch == 3)
	{
		system("cls");
		cout << "+###########################################################################+" << endl;
		int i = 0 , j = 0;
		for (i=0 ; i < size ; i++)
		{
			for (j=0 ; j < value ; j++)
			{
				if (map[i][j] != '-' && map[i][j] != '`')
					map[i][j] = ' ';
			}
		}

		const char ar[50] = {'<','|','+','*','0'};                                   //to generate random values
		srand (time(NULL));
		int rand1 = rand() % 5;
		int rand2 = rand() % 5;
		int rand3 = rand() % 5;
		int rand4 = rand() % 5;
		int rand5 = rand() % 5;

		target(x,z,map,ar[rand1]);
		target(x+1,z-1,map,ar[rand2]);
		target(x+3,z-2,map,ar[rand3]);
		target(x+4,z-2,map,ar[rand4]);
		target(x+5,z-2,map,ar[rand5]);

		z--;

		for (i=0 ; i<size ; i++)
		{
			cout << '|';
			for (j=0 ; j<value ; j++)
			{
				cout << ' ' << map[i][j] << ' ';
			}
			cout << '|';
			cout << endl;
		}
		cout << "+###########################################################################+" << endl;
	}
	else if (ch == 4)
	{
		system("cls");
		cout << "+###########################################################################+" << endl;
		int i = 0 , j = 0;
		for (i=0 ; i < size ; i++)
		{for (j=0 ; j < value ; j++)
			{
				if (map[i][j] != '-' && map[i][j] != '`')
					map[i][j] = ' ';
			}
		}

		const char ar[50] = {'<','|','+','*','0'};                                   //to generate random values
		srand (time(NULL));
		int rand1 = rand() % 5;
		int rand2 = rand() % 5;
		int rand3 = rand() % 5;
		int rand4 = rand() % 5;
		int rand5 = rand() % 5;

		target(x,z,map,ar[rand1]);
		target(x+1,z-1,map,ar[rand2]);
		target(x+3,z-2,map,ar[rand3]);
		target(x+4,z-2,map,ar[rand4]);
		target(x+5,z-2,map,ar[rand5]);

		counter++;
		if (counter <7)
			x++;

		for (i=0 ; i<size ; i++)
		{
			cout << '|';
			for (j=0 ; j<value ; j++)
			{
				cout << ' ' << map[i][j] << ' ';
			}
			cout << '|';
			cout << endl;
		}
		cout << "+###########################################################################+" << endl;
	}
	else if (ch == 5)
	{
		system("cls");
		cout << "+###########################################################################+" << endl;
		int i = 0 , j = 0;
		for (i=0 ; i < size ; i++)
		{
			for (j=0 ; j < value ; j++)
			{
				if (map[i][j] != '-' && map[i][j] != '`')
					map[i][j] = ' ';
			}
		}

		const char ar[50] = {'<','|','+','*','0'};                                   //to generate random values
		srand (time(NULL));
		int rand1 = rand() % 5;
		int rand2 = rand() % 5;
		int rand3 = rand() % 5;
		int rand4 = rand() % 5;
		int rand5 = rand() % 5;

		target(x,z,map,ar[rand1]);
		target(x+1,z-1,map,ar[rand2]);
		target(x+3,z-2,map,ar[rand3]);
		target(x+4,z-2,map,ar[rand4]);
		target(x+5,z-2,map,ar[rand5]);

		if (z > 2)
			z--;
		else
			x++;

		counter++;
		if (counter < 1)
			x++;

		for (i=0 ; i<size ; i++)
		{
			cout << '|';
			for (j=0 ; j<value ; j++)
			{
				cout << ' ' << map[i][j] << ' ';
			}
			cout << '|';
			cout << endl;
		}
		cout << "+###########################################################################+" << endl;
	}
	else if (ch == 6)
	{
		system("cls");
		cout << "+###########################################################################+" << endl;
		int i = 0, j = 0;
		for (i = 0; i<size ; i++)
		{for (j=22 ; j<value ; j++)
			{
				if (map[i][j] != '-' && map[i][j] != '`' )
					map[i][j] = ' ';
			}
		}
		goal(l,l+6,24,map,'*');
		goal(l+1,l+5,23,map,'|');                                                                   //for movement of board
		goal(l+2,l+4,22,map,'+');
		goal(l+3,l+3,22,map,'<');
		if(check == 1)
			l++;
		if (l == 14)
			check = 0;
		if (check == 0)
			l--;
		if (l == 0)
			check = 1;

		for (i=0 ; i<size ; i++)
		{
			cout << '|';
			for (j=0 ; j<value ; j++)
			{
				cout << ' ' << map[i][j] << ' ';
			}
			cout << '|';
			cout << endl;
		}
		cout << "+###########################################################################+" << endl;
	}
}

void Map:: showmap()                                                                                          //function to show the map before putting values of angle and speed
{
	system("cls");
	gotoxy(0,1);
	display();
	gotoxy(0,23);
	cout << "This is your map. The '>' shows where your arrow is. \n";
	gotoxy(2,20);
	cout << ">";
	gotoxy(0,25);
	cout << "Press enter to proceed.";
	getch();
}

int showagain();                                                                                          //function to show the map after putting values of angle and speed

class Player
{
	int score;
	public:
	int life;
	int points;
	int ang;
	int spd;
	Player()
	{
		points = 0;
		score = 0;
		ang = 45;
		spd = 100;
		life = 3;
	}
	int returnscore()
	{
		return score;
	}
	void assignscore(int t)
	{
		score = t;
	}
	void moves(int speed,int angle) ;
	void angle();
	void speed();
}obj;

void gethints();

void Player :: moves(int speed,int angle)				//function to move the arrow according to formula of projectile motion
{
	float range, height;
	int i=0,j=0;
	int flag = 1;

	float angl = angle * 0.0174533;					//convert to radians
	height = (pow(speed,2) * pow(sin(angl),2))/19.6;                                               //get real height and range values
	range = (pow(speed,2) * sin(2*angl))/9.8;
	height /= 30.25;
	range /= 42.5;																				   						//scale down height and range according to board
	height = 19.0 - height;      //since we start from the bottom
	if (ch > 2)
	{
		if(strcmp(wid.dir,"north") == 0)
		{
			height -= wid.wspeed;
		}
		else if(strcmp(wid.dir,"south") == 0)
		{
			height += wid.wspeed;
		}
		else if(strcmp(wid.dir,"east") == 0)
		{
			range += wid.wspeed;
		}
		else if(strcmp(wid.dir,"west") == 0)
		{
			range -= wid.wspeed;
		}
	}
	i = 19, j = 0;
	do{
		while(i >= height && j <= range/2)														  						//loop to move to its maximum height and midrange
		{																					      							//always end the game when hitting the target
			map[i][j] = '>';
			game.display();
			map[i][j] = '-';
			if (i==0)
			{
				flag = 0;
			}
			if (map[i-1][j+1] == '<')
			{points += 10;
				if (map[i-1][j] == '<' || map[i-1][j] == '+' || map[i-1][j] == '*' || map[i-1][j] == '|')
				{map[i][j] = '>';
				}
				else
					map[i-1][j] = '>';
				flag = 0;
				break;
			}
			if (map[i-1][j+1] == '*')
			{points += 5;
				if (map[i-1][j] == '<' || map[i-1][j] == '+' || map[i-1][j] == '*' || map[i-1][j] == '|')
				{map[i][j] = '>';
				}
				else
					map[i-1][j] = '>';
				flag = 0;
				break;
			}
			if (map[i-1][j+1] == '+')
			{points += 3;
				if (map[i-1][j] == '<' || map[i-1][j] == '+' || map[i-1][j] == '*' || map[i-1][j] == '|')
				{map[i][j] = '>';
				}
				else
					map[i-1][j] = '>';
				flag = 0;
				break;
			}
			if (map[i-1][j+1] == '|')
			{points += 1;
				if (map[i-1][j] == '<' || map[i-1][j] == '+' || map[i-1][j] == '*' || map[i-1][j] == '|')
				{map[i][j] = '>';
				}
				else
					map[i-1][j] = '>';
				flag = 0;
				break;
			}
			if (map[i-1][j+1] == '0')
			{points += 0;
				if (map[i-1][j] == '<' || map[i-1][j] == '+' || map[i-1][j] == '*' || map[i-1][j] == '|')
				{map[i][j] = '>';
				}
				else
					map[i-1][j] = '>';
				flag = 0;
				break;
			}
			if (j == 24)
			{
				if (map[i + 1][j] == ' ')
					map[i][j+1] = '>';
				flag = 0;
				break;
			}
			i--;
			j++;
		}

		if (flag == 0)
			break;

		if (j <(range/2))																				//if it reaches its maximum height before reaching midrange
		{
			i++;
			for ( ;j<= range/2;j++)
			{
				map[i][j] = '`';
				game.display();
				if (map[i][j+1] == '<')
				{points += 10;
					map[i][j] = '>';
					flag = 0;
					break;
				}
				if (map[i][j+1] == '*')
				{points += 5;
					map[i][j] = '>';
					flag = 0;
					break;
				}
				if (map[i][j+1] == '+')
				{points += 3;
					map[i][j] = '>';
					flag = 0;
					break;
				}
				if (map[i][j+1] == '|')
				{points += 1;
					map[i][j] = '>';
					flag = 0;
					break;
				}
				if (map[i][j+1] == '0')
				{points += 0;
					map[i][j] = '>';
					flag = 0;
					break;
				}
				if (j == 24)
				{
					if (map[i + 1][j] == ' ')
						map[i][j+1] = '>';
					flag = 0;
					break;
				}
			}
		}
		if (flag == 0)
			break;

		if (i < height)
		{
			i = height;
		}

		while(i <= 19 && j <= 25)																		//to reach down after reaching maximum height and midrange
		{
			map[i][j] = '>';
			game.display();
			map[i][j] = '-';
			if (map[i+1][j+1] == '<')
			{
				points += 10;
				if (map[i+1][j] == '<' || map[i+1][j] == '+' || map[i+1][j] == '*' || map[i+1][j] == '|')
				{map[i][j] = '>';
				}
				else
					map[i+1][j] = '>';
				flag = 0;
				break;
			}
			if (map[i+1][j+1] == '*')
			{
				points += 5;
				if (map[i+1][j] == '<' || map[i+1][j] == '+' || map[i+1][j] == '*' || map[i+1][j] == '|')
				{map[i][j] = '>';
				}
				else
					map[i+1][j] = '>';
				flag = 0;
				break;
			}
			if (map[i+1][j+1] == '+')
			{
				points += 3;
				if (map[i+1][j] == '<' || map[i+1][j] == '+' || map[i+1][j] == '*' || map[i+1][j] == '|')
				{map[i][j] = '>';
				}
				else
					map[i+1][j] = '>';
				flag = 0;
				break;
			}
			if (map[i+1][j+1] == '|')
			{
				points += 1;
				if (map[i+1][j] == '<' || map[i+1][j] == '+' || map[i+1][j] == '*' || map[i+1][j] == '|')
				{map[i][j] = '>';
				}
				else
					map[i+1][j] = '>';
				flag = 0;
				break;
			}
			if (map[i+1][j+1] == '0')
			{
				points += 0;
				if (map[i+1][j] == '<' || map[i+1][j] == '+' || map[i+1][j] == '*' || map[i+1][j] == '|')
				{map[i][j] = '>';
				}
				else
					map[i+1][j] = '>';
				flag = 0;
				break;
			}
			if (j == 24)
			{
				if (map[i + 1][j] == ' ')
					map[i + 1][j + 1] = '>';
				flag = 0;
				break;
			}
			i++;
			j++;
		}
		if (flag == 0)
			break;

		if(i == 19)
			break;

	}while(j <= 25 && i >= 0 && i <= 19);																	//to always stay in the board
	game.display();
	getch();
	system("cls");
	cout << "You got " << points << " points. Press enter to go to your next attempt.\n \n";
	gethints();
	getch();
	score += points;
}

void Player :: angle()																						   	 //function to input the angle
{
	system("cls");
	char key;
	gotoxy(0,0);
	cout << "Level-" << ch << "\tLives-" << life;
	gotoxy(0,25);
	cout << "Use the arrow keys to change your angle.";
	gotoxy(0,5);
	Map().babydisplay();
	gotoxy(0,18);
	if (ch > 2)
	{
		gotoxy(0,22);
		cout << "*The wind is moving towards ";
		puts(wid.dir);
		cout << " at a speed of " << wid.wspeed <<".*";
	}
	gotoxy(0,2);
	cout << "Please enter your angle: " << ang;

	do{
		key = getch();

		if (GetAsyncKeyState(VK_UP) && (ang <= 84)) {
			++ang;
			getch();
			cout << '\r';
			cout << "Please enter your angle: " << ang;
		}

		else if (GetAsyncKeyState(VK_DOWN) && (ang >= 21)){
			--ang;
			getch();

			cout << '\r';

			cout << "Please enter your angle: " << ang;
		}
	}while(key != '\r');
}

void Player :: speed()																						    //function to input the speed
{
	char key;
	gotoxy(0,0);
	cout << "Level-" << ch << "\tLives-" << life;
	gotoxy(0,5);
	Map().babydisplay();
	gotoxy(0,18);
	if (ch > 2)
	{
		gotoxy(0,22);
		cout << "*The wind is moving towards ";
		puts(wid.dir);
		cout <<" at a speed of " << wid.wspeed << ".*";
	}
	gotoxy(0,24);
	clreol();
	cout << "Use the arrow keys to change your speed.";
	gotoxy(0,25);
	clreol();
	cout << "Press backspace to return to changing your angle.";
	gotoxy(0,3);
	cout << "Please enter your speed: " << spd;

	do{
		key = getch();

		if (GetAsyncKeyState(VK_UP) && (spd <= 149)) {
			spd++;
			getch();
			gotoxy(0,3);
			clreol();

			cout << "Please enter your speed: " << spd;
		}

		else if (GetAsyncKeyState(VK_DOWN) && (spd >= 51))
		{
			spd--;
			getch();
			gotoxy(0,3);
			clreol();
			cout << "Please enter your speed: " << spd;
		}
		if(spd == 99)																							//to remove the 0 from the unit's place
		{
			clreol();
			gotoxy(0,0);
			cout << "Level-" << ch << "\tLives-" << life;
			gotoxy(0,5);
			Map().babydisplay();
			gotoxy(0,24);
			clreol();
			cout << "Press the 'w' key to increase your speed and 's' key to change your speed.";
			if (ch > 2)
			{
				gotoxy(0,22);
				cout << "*The wind is moving towards ";
				puts(wid.dir);
				cout <<" at a speed of " << wid.wspeed << ".*";
			}
			gotoxy(0,25);
			clreol();
			cout << "Press backspace to return to changing your angle.";
			gotoxy(0,3);
			clreol();
			cout << "Please enter your speed: " << spd << "\n";
		}
		if(key == '\b')
		{
			angle();
			gotoxy(0,3);
			clreol();
			cout << "Please enter your speed: " << spd << "\n";
		}

	}while(key != '\r');
	showagain();
}

int showagain()
{
	char go = '\r';
	gotoxy(0,1);
	game.display();
	if (ch > 2)
	{
		gotoxy(2,3);
		cout << "   N  \n";
		cout << "  W--|--E\n";
		cout << "     S   \n";
	}
	gotoxy(0,23);
	cout << "This is your map. The '>' shows where your arrow is. \n";
	gotoxy(2,20);
	cout << ">";
	if (ch >= 3)
	{
		gotoxy(0,24);
		cout << "Beware! Your target is moving.";
	}
	gotoxy(0,25);
	cout << "Press 'backspace' to change your speed and angle or 'enter' to proceed.";
	go = getch();

	if(go == '\b')
	{
		obj.angle();
		obj.speed();
	}
	else
		return 0;
}

void gethints()				 																									 	//function to display hints for getting better shots
{
	ifstream ifile ("Hint.txt");																									//already exists on the comp
	char ar[50];
	if(!ifile)
	{
		cout << "There was an error loading the hints :( \n";
	}
	else
	{
		cout << "Hint: ";
		int i = 0;
		while (ifile)
		{
			ifile.getline(ar,50,'\n');
			if(i == hintcount)
			{
				cout << ar;
				break;
			}
			++i;
		}
		if(i == 20)
		{
			i = 0;
			hintcount = 0;
		}
	}
	hintcount++;
	ifile.close();

}

void logo()                                                                                              //function to print the name at start of game
{
	cout << endl << endl ;
	ifstream ifile("logo.txt");
	char c;
	if(!ifile)
	{
		cout << "File open error";
		getch();
	}
	while(ifile.get(c))
	{
		cout << c;
	}
	cout << "\n\t \t \t            The Game.                                  \n ";
	cout << "______________________________________________________________________________  \n ";
	getch();
	system("cls");
}

void loading()																					    //to make it look like an actual game
{
	int i=0;

	for(long int num=0;num<2;num++)
	{
		system("cls");
		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t LOADING.";
		for(long int mn=0;mn<222221056;mn++)
		{}
		system("cls");
		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t LOADING..";
		for(long int ln=0;ln<222221056;ln++)
		{}
		system("cls");
		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t LOADING...";
		for(long int d=0;d<222221056;d++)
		{}
	}system("cls");
	cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t LOADED ";
}

void rules()																						    //to output the rules of the game
{
	system("cls");
	cout << "Lets begin your quest. Your aim is to hit the target and get the maximum score\npossible. \n\n";
	cout<<"\n";
	getch();
	cout << "To fire the angle towards the target, you have to choose your angle and speed. \n";
	cout<<"\n";
	getch();
	cout << "The minimum angle is 20 and maximum is 80. \n";
	cout << "The minimum speed is 50 and maximum is 150. \n";
	cout<<"\n";
	getch();
	cout << "After you choose your angle and speed, the arrow will fly towards the target. \n";
	cout<<"\n";
	getch();
	cout << "Based on which symbol the arrow hits on the target, the scoring is as follows: \n";
	cout << " \t '<' = 10 \n";
	cout << " \t '*' = 5 \n";
	cout << " \t '+' = 3 \n";
	cout << " \t '|' = 1 \n";
	cout << " \t '0' = 0 \n";
	cout << " \t ' ' = 0 \n";
	cout<<"\n";
	getch();
	cout << "You have 3 lives to clear all 6 levels. If you score less than 3 on a level,\nyou lose a life. \n";
	cout<<"\n";
	getch();
	cout << "At the end of the game, you can input your score on our very own Leaderboard!   Only the top ten scorers are displayed.\n";
	cout<<"\n";
	getch();
	cout << "All the best! \n";
	getch();
}

windo wind()                                                                                           //function to get direction and speed of wind
{
	windo wid;
	wid.wspeed = 0;
	const char windd[4][10] = {"north","east","west","south"};
	//randomize();
	srand (time(NULL));
	int rand1 = rand() % 4;
	const int wspd[6] = {1,1,1,2,2,3};
	int rand2 = rand() % 6;
	strcpy(wid.dir,windd[rand1]);
	wid.wspeed = wspd[rand2];
	return wid;
}

class Score
{
	int highscore;
	char name[100];

	public:
	Score()
	{
		highscore = 0;
		strcpy(name,"Player");
	}
	void display()
	{
		cout << "\t" << name << "\t\t\t" << highscore;
		cout << "\n";
	}
	void assignValues(int scoreo, char *nm)
	{
		highscore = scoreo;
		strcpy(name,nm);
	}
	int returnsscore()
	{
		return highscore;
	}
};

void createFile(Player &temp)
{
	ifstream ifile ("Scores.dat" , ios::binary);
	ofstream ofile ("temp.dat", ios::binary);
	//Creating object of class
	char nm[50];
	system("cls");
	cout << "Please enter your username: \n";
	cin.ignore(10, '\n');
	cin.getline(nm, 50);
	int flagnew = 1;
	Score obj, mini;
	cout << "YAY";
	//Putting data into the object
	obj.assignValues(temp.returnscore(),nm);

	//Writing into file in descending order
	if (!ifile)
		cout << "FOE";
	while (ifile.read((char*) &mini, sizeof(mini)))
	{
		if(obj.returnsscore() <= mini.returnsscore())
		{
			ofile.write((char*) &mini, sizeof(mini));
		}
		else
		{
			flagnew = 0;
			ofile.write((char*) &obj, sizeof(obj));
			ofile.write((char*) &mini, sizeof(mini));
			break;
		}
	}

	if (flagnew == 1)
		ofile.write((char*) &obj, sizeof(obj));
	else
	{while (ifile.read((char*) &mini, sizeof(mini)))
		{
			ofile.write((char*) &mini, sizeof(mini));
		}
	}

	ifile.close();
	ofile.close();
	remove("Scores.dat");
	rename("temp.dat","Scores.dat");
}

void displayFile()
{
	int check = 0;
	ifstream ifile ("Scores.dat" , ios::binary);
	if (!ifile)
	{
		cout << "File open error.";
		getch();
	}
	Score obj;
	//Reading the files or a score
	system("cls");
	cout << "\t\t The Leaderboards ! \n";
	cout << "\n";

	cout << "\t Username" << "\t\t" << "Highscore" << "\n\n";
	ifile.seekg(0,ios::end);
	check = ifile.tellg() / sizeof(obj);
	ifile.seekg(0,ios::beg);
	for(int i = 0; i < (check<10?check:10); ++i)
	{
		ifile.read((char*) &obj, sizeof(obj));
		cout << ifile.tellg() / sizeof(obj) << "). ";
		obj.display();
	}
	ifile.close();
}

int main()
{
	int i, opt, m;
	char a;

	ifstream fr;

	opt = 1;

	while(true){
		do{
			switch(opt){
				case 1:
					system("cls");
					fr.open("maintemplate1.0.in");
					while(!fr.eof()){
						fr.get(a);
						cout<<a;
					}
					fr.close();
					break;

				case 2:
					system("cls");
					fr.open("maintemplate2.0.in");
					while(!fr.eof()){
						fr.get(a);
						cout<<a;
					}
					fr.close();
					break;

				case 3:
					system("cls");
					fr.open("maintemplate3.0.in");
					while(!fr.eof()){
						fr.get(a);
						cout<<a;
					}
					fr.close();
					break;

				case 4:
					system("cls");
					fr.open("maintemplate4.0.in");
					while(!fr.eof()){
						fr.get(a);
						cout<<a;
					}
					fr.close();
					break;

				case 5:
					system("cls");
					fr.open("maintemplate5.0.in");
					while(!fr.eof()){
						fr.get(a);
						cout<<a;
					}
					fr.close();
					break;
			}

			a = getch();

			if(GetAsyncKeyState(VK_UP))
				{
				if(opt == 1)
					{
					opt = 5;
					}
				else
					{
					opt--;
					}
				}
			else if(GetAsyncKeyState(VK_DOWN))
				{
				if(opt == 5)
					{
					opt = 1;
					}
				else
					{
					opt++;
					}
				}

		}while(a != '\r');

		if(opt == 1){
			int i = 0, j = 0, back;
			char op[5] = "yes";
			char oplead[3];
			char yno[3];
			cout << endl;
			system("cls");
			logo();
			loading();
			system("cls");
			cout << "Welcome to Arrow: The Game \n";
			cout << "Completely new game conceptualised by Aaditya, Nikita, Avinash and Rahul. \n";
			cout << "Enter your angle and speed to hit the target, maximise your score to beat your \nfriends. \n \n";
			gotoxy(0,25);
			cout << "Press enter to continue.";
			gotoxy(0, 30);
			cout << "Press backspace to return to main menu.";
			back = getch();
			if (back == '\b')
				continue;				
			loading();
			system("cls");
			ch = 1;
			while (obj.life > 0 && ch < 7)
			{
				game.showmap();
				wid = wind();
				obj.angle();
				obj.speed();
				cout << endl;
				obj.moves(obj.spd,obj.ang);
				for(i = 0; i < size; i++)
				{for(j = 0; j < value; j++)
					{
						map[i][j] = ' ';
					}
				}
				game.x = 1;
				game.z = 24;
				if (obj.points < 3)
				{
					obj.life--;
				}
				obj.points = 0;
				game.counter = 0;
				if (ch <= 6)
					ch++;
				else
				{
					cout << "Game over.";
					break;
				}
			}
			system("cls");
			cout << "Your total score is: " << obj.returnscore() << "\n";
			cout << "Would you like to enter the scoreboard? (Y/N) \n";
			cin >> oplead;
			if(strcmp(oplead, "Y") == 0 || strcmp(oplead, "Yes") == 0 || strcmp(oplead, "yes") == 0 || strcmp(oplead, "y") == 0)
			{
				createFile(obj);
				system("cls");
				displayFile();
				getch();
				system("cls");
				cout << "Do you wish to continue playing? (Y/N) \n";
				obj.life = 3;
				ch = 1;
				cin >> op;
				obj.assignscore(0);
				system("cls");
			}
			else
			{
				cout << "Do you wish to continue playing? (Y/N) \n";
				obj.life = 3;
				ch = 1;
				cin >> op;
				obj.assignscore(0);
				system("cls");
			}
		}

		if(opt == 2){
			int i = 0, j = 0, back;
			loading();
			system("cls");
			cout << "\t\t\t\t\t\n\n Welcome to the Practise Arena, where you learn how to play Arrow:The Game ! \n";
			gotoxy(0, 30);
			cout << "Press backspace to return to main menu.";
			back = getch();
			if (back == '\b')
				continue;
			system("cls");
			ch = boards();
			game.showmap();
			m = 0;

			cout << "\n\nHow many times would you like to practise this level ? \n";
			cin >> m;
			do{
				wid = wind();
				obj.angle();
				obj.speed();
				cout << endl;
				obj.moves(obj.spd,obj.ang);
				for(i = 0; i < size; i++)
				{for(j = 0; j < value; j++)
					{
						map[i][j] = ' ';
					}
				}
				game.x = 1;
				game.z = 24;
				obj.points = 0;
				game.counter = 0;
				m--;
			}while(m!=0);
			system("cls");
			cout << "Your total score is: " << obj.returnscore() << "\n";
		}

		if(opt == 3){
			displayFile();
		}

		if(opt == 4){
			rules();
		}

		if(opt == 5){
			cout << "Thank you for playing!";
			exit(0);
		}
		getch();
	}
	return 0;
}

