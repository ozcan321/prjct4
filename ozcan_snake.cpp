

#include <iostream>
#include <windows.h>
#include <vector>
#include <conio.h>
using namespace std;
#define black 0
#define white 7
typedef struct snakee{
	char c;
	COORD pos;
}snake;
void updateSnakePos(HANDLE, COORD [], vector<snake>, char);
bool hit(HANDLE, vector<snake>);
int main()
{	
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<snake> s(8);
	int i, j;

	SetConsoleTextAttribute(screen, 79);
	cout<<"The game is played with number characters: 8, 4, 5, 6";
	SetConsoleTextAttribute(screen, 13);
	for(i=0; i<8; i++)
	{	
		COORD posOfElements={18+i, 20};
		s[i].c='*';
		(s[i].pos)=posOfElements;
	}
	COORD positions[8];
	for(i=0; i<8; i++)
		positions[i]=s[i].pos;

	COORD positionOfWall={15,10};
	COORD positionOfUpWall={15,9};
	char wall[20][20];
	for(i=0; i<20; i++)
	{
		wall[i][0]='+';
		wall[i][19]='+';
		wall[0][i]='+';
		wall[19][i]='+';
	}
	SetConsoleCursorPosition(screen, positionOfUpWall);
	for(i=0; i<20; i++)
		cout<<'+';
	for(i=1; i<19; i++)
		for(j=1; j<19; j++)
			wall[i][j]=' ';
	SetConsoleCursorPosition(screen, positionOfWall);

	for(i=0; i<20; i++)	
		for(j=0; j<20; j++)
		{	
			cout<<wall[i][j];
			if(j==19)
			{
				cout<<"\n";
				COORD positionOfWall={15, 10+i};
				SetConsoleCursorPosition(screen, positionOfWall);
			}
		}

	SetConsoleCursorPosition(screen, (s[0].pos));
	for(i=0; i<8; i++)																//yılanın ilk konumu
		cout<<s[i].c;
	
	int level=0, score=0, speed=0;
	char direction='6', nextdirection='0';

	while(1){
		if(score==0)
			Sleep(2000);
		updateSnakePos(screen, positions, s, direction);
		for(i=0; i<8; i++)															//yılanın yerinde saymaması için
			s[i].pos=positions[i];
									
		if(level>4 && level<7)
			speed=200;																//yılanın gittikçe hızlanması için
		else if(level>7 && level<10)
			speed=300;
		else if(level>10 && level<14)
			speed=400;
		else if(level>14 && level<18)
			speed=475;
		else if(level>18 && level<24)
			speed=550;
		else if(level>24 && level<30)
			speed=600;
		else if(level>30 && level<37)
			speed=650;
		else if(level>37 && level<48)
			speed=675;
		else if(level>48 && level<57)
			speed=690;
		else if(level>57 && level<68)
			speed=710;
		else if(level>68 && level<90)
			speed=720;
		else if(level>90 && level<120)
			speed=740;
		else if(level>120 && level<160)
			speed=750;
		else
			speed=765;

		Sleep(800-speed);
		if(hit(screen, s))
			break;
		if(kbhit()){
			nextdirection=_getch();
			if(nextdirection=='q'||nextdirection=='Q')
			{
				cout<<"\n\n\n     ☺ Goodbye ☺"<<endl;
				break;
			}
			else if((nextdirection=='4' && direction=='8')||(nextdirection=='4' && direction=='5')||(nextdirection=='5' && direction=='4')||(nextdirection=='5' && direction=='6')||(nextdirection=='6' && direction=='5')||(nextdirection=='6' && direction=='8')||(nextdirection=='8' && direction=='4')||(nextdirection=='8' && direction=='6'))
				direction=nextdirection;
			else if((nextdirection=='4' && direction=='6')||(nextdirection=='6' && direction=='4')||(nextdirection=='8' && direction=='5')||(nextdirection=='5' && direction=='8'))
			{
				int errormsg=0;
				COORD newpos={15, 39};
				
				while(errormsg<3)
				{	
					SetConsoleCursorPosition(screen, newpos);
					SetConsoleTextAttribute(screen, 10);
					cout<<"! ILLOGICAL DIRECTIVE !";				//yılanın gittiği yönün tersi yönüne basıldığında oluşan geçici bir error mesajı
					Sleep(200);
					SetConsoleCursorPosition(screen, newpos);
					SetConsoleTextAttribute(screen, black);	
					cout<<"! ILLOGICAL DIRECTIVE !";
					Sleep(200);
					errormsg++;
				}
			}
		}
		level++;
		score++;
	}
	SetConsoleTextAttribute(screen, 14);
	cout<<"\n\n YOUR SCORE: "<<score<<"\n GOODBYE...\n";
	SetConsoleTextAttribute(screen, white);

return 0;
}
void updateSnakePos(HANDLE screen, COORD positions[], vector<snake> s, char direction)
{
	int i;
	SetConsoleCursorPosition(screen, (s[0].pos));				//yılanın kuyruğu bir kademe kısalıyor
	SetConsoleTextAttribute(screen, black);
	cout<<"*";
	
	if(direction=='6')											//kuyruk yok olduktan sonra direction yönünde '*' ekleniyor
	{
		COORD headOfSnake={(s[7].pos).X+1, (s[7].pos).Y};
		SetConsoleCursorPosition(screen, headOfSnake);
		SetConsoleTextAttribute(screen, white);
		cout<<"*";
		for(i=0; i<8; i++)
		{
			if(i==7)
			{
				s[i].pos=headOfSnake;
				positions[i]=s[i].pos;
			}
			else
			{	
				(s[i].pos)=s[i+1].pos;
				positions[i]=s[i].pos;	
			}
		}
	}
	else if(direction=='8')
	{
		COORD headOfSnake={(s[7].pos).X, (s[7].pos).Y-1};
		SetConsoleCursorPosition(screen, headOfSnake);
		SetConsoleTextAttribute(screen, white);
		cout<<"*";
		for(i=0; i<8; i++)
		{
			if(i==7)
			{
				s[i].pos=headOfSnake;
				positions[i]=s[i].pos;
			}
			else
			{	
				(s[i].pos)=s[i+1].pos;
				positions[i]=s[i].pos;	
			}
		}
	}
	else if(direction=='4')
	{
		COORD headOfSnake={(s[7].pos).X-1, (s[7].pos).Y};
		SetConsoleCursorPosition(screen, headOfSnake);
		SetConsoleTextAttribute(screen, white);
		cout<<"*";
		for(i=0; i<8; i++)
		{
			if(i==7)
			{
				s[i].pos=headOfSnake;
				positions[i]=s[i].pos;
			}
			else
			{	
				(s[i].pos)=s[i+1].pos;
				positions[i]=s[i].pos;	
			}
		}
	}	
	else if(direction=='5')
	{
		COORD headOfSnake={(s[7].pos).X, (s[7].pos).Y+1};
		SetConsoleCursorPosition(screen, headOfSnake);
		SetConsoleTextAttribute(screen, white);
		cout<<"*";
		for(i=0; i<8; i++)
		{
			if(i==7)
			{
				s[i].pos=headOfSnake;
				positions[i]=s[i].pos;
			}
			else
			{	
				(s[i].pos)=s[i+1].pos;
				positions[i]=s[i].pos;	
			}
		}
	}
}
bool hit(HANDLE screen, vector<snake> s)
{
	int i, j;
	COORD wall[78];
	for(i=0; i<20; i++)
	{
		wall[i].X=15+i;
		wall[i].Y=9;
	}
	for(i=20; i<38; i++)
	{
		wall[i].X=15;
		wall[i].Y=11+i-20;
	}
	for(i=38; i<57; i++)
	{
		wall[i].X=34;
		wall[i].Y=11+i-38;
	}
	for(i=57; i<78; i++)
	{
		wall[i].X=15+i-57;
		wall[i].Y=28;
	}
	for(j=0; j<78; j++)
		if((s[7].pos).X==wall[j].X && (s[7].pos).Y==wall[j].Y)
		{	
			COORD p={0,3};
			SetConsoleCursorPosition(screen, p);
			SetConsoleTextAttribute(screen, 28);
			cout<<"!!!!!!!!!!!!SNAKE HITS THE WALL!!!!!!!!!!";
			SetConsoleTextAttribute(screen, white);
			return true;
		}

	for(i=0; i<7; i++)
		if((s[i].pos).X==(s[7].pos).X && (s[i].pos).Y==(s[7].pos).Y)
		{
			COORD p={0,3};
			SetConsoleCursorPosition(screen, p);
			SetConsoleTextAttribute(screen, 28);
			cout<<"!!!!!!!!!!!!SNAKE HITS ITSELF!!!!!!!!!!!";
			SetConsoleTextAttribute(screen, white);
			return true;
		}
return false;
}
