#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;
void project();
char initdisplayboard(char t[][10]);
char printanyboard(char y[][10]);
char initrealboard(char y[][10]);
void minegenerator(char t[][10]);
void player_input(int x,int y,char rea[][10],char disp[][10],int scr);
void revealwhen0(int x,int y,char rea[][10],char disp[][10]);
void flagbox(int x,int y,char rea[][10],char disp[][10]);
void unflagthebox(int x,int y,char rea[][10],char disp[][10]);
void flagcounter(char disp[][10],char rea[][10]);
char revealmine(char dis[][10],char rea[][10]);
int wincondition(char rea[][10],char disp[][10]);
int lostcondition(char rea[][10],char disp[][10]);
//void playerinfo(char t[],int size);
int scorecalc(int x,char rea[][10],char disp[][10]);

void writeToFile(char disp[][10]) {
    ofstream outputFile;
    outputFile.open("minesweeper_data.txt");

    // Write displayboard to the file
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            outputFile << disp[i][j] << " ";
        }
        outputFile << endl;
    }

    /*// Write realboard to the file
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            outputFile << rea[i][j] << " ";
        }
        outputFile << endl;
    }*/

    outputFile.close();
}


int main()
{
	string filename = "minesweeper_data.txt";

	start:
	char displayboard[10][10];
	char realboard[10][10];




	int xaxis,yaxis;
	bool y=true;
	int win=10;
	int lost=0;
	int score=0;
	int size=40;
	char name[size];
	   	project();
   	system("cls");
   //	playerinfo(name,size);
   	system("cls");
    initdisplayboard(displayboard);
     initrealboard(realboard);
   minegenerator(realboard);
   while(y)
   {
   	system("cls");
   	lost=lostcondition(realboard,displayboard);
   	flagcounter(displayboard,realboard);

     printanyboard(displayboard);
     ofstream outputFile;
outputFile.open(filename);

// ???????? displayboard ? ????
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
        outputFile << displayboard[i][j] << " ";
    }
    outputFile << endl;
}

// ???????? realboard ? ????
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
        outputFile << realboard[i][j] << " ";
    }
    outputFile << endl;
}

outputFile.close();

    player_input(xaxis,yaxis,realboard,displayboard,score);
    lost=lostcondition(realboard,displayboard);
     if(win==wincondition(realboard,displayboard)||lost==2)
     {
     	y=false;
	 }

 }
 if(win==wincondition(realboard,displayboard))
 {
 	cout<<"YOU "<<name<<" WON THE GAME CONGRATULATIONS !!!!"<<endl;
 	cout<<"YOUR SCORE : "<<scorecalc(score,realboard,displayboard)<<endl;
 }
 cout<<"WANNA PLAY AGAIN  !!!!"<<endl;
 cout<<"ENTER YOUR CHOICE (Y/N):"<<endl;
 char choice;
 cin>>choice;
 switch(choice)
 {
 	case 'Y':
 		goto start;
 	case'N':
	 {
	 	cout<<"THANK YOU FOR PLAYING !!!!"<<endl;
	 	exit(0);
		 }
	default:
	cout<<"INVALID ENTRY !!!!"<<endl;
	break;
 }
}
char initrealboard(char y[][10])
{
		for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
		{
			y[i][j]='0';
		}
	}
}
char initdisplayboard(char t[][10])
{
		for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
		{
			t[i][j]='B';
		}
	}
}
char printanyboard(char y[][10])
{

	cout<<endl;
	for(int i=0;i<1;i++)
	{
		cout<<setw(34);
		for(int j=0;j<10;j++)
		{
			cout<<j<<"     ";
		}
	}
	cout<<endl;
	cout<<setw(34);
	for(int i=0;i<30;i++)
	{
		cout<<"__";
	}
	cout<<endl<<endl;
	for(int i=0;i<=9;i++)
	{
		cout<<setw(30)<<i<<" | ";
		for(int j=0;j<=9;j++)
		{
			cout<<"("<<y[i][j]<<")"<<"   ";
		}
		cout<<"| "<<endl<<endl;
	}
}
void hints(int x,int y,char arr[][10])
{
	if(arr[x][y]!='X' && x>=0&&y>=0&&x<=9&&y<=9)
	arr[x][y]=arr[x][y]+1;
}
void minegenerator(char t[][10])
{
	int counter=0;
	int a,b,y=0;
	int p=0;
	int arr[20];
	for(int i=0;i<20;i++)
	{
		arr[i]=19;
	}
	srand(time(0));
	while(counter<=9&&y<20)
	{
		strt:
		a=rand()%10;
		b=rand()%10;
		if(p>0)
		{
			for(int i=0;i<20;i+=2) // to check that if the previous coordinates are not repeated
			{
				if(a==arr[i]&&b==arr[i+1])
				{
					goto strt;
				}
			}
		}
		arr[y]=a;
		arr[y+1]=b;
		t[a][b]='X';
		hints(a,b+1,t);
		hints(a,b-1,t);
		hints(a-1,b,t);
		hints(a-1,b+1,t);
		hints(a-1,b-1,t);
		hints(a+1,b,t);
		hints(a+1,b+1,t);
		hints(a+1,b-1,t);
		counter++;
		y+=2;
		p++;
	}
}
void revealwhen0(int x,int y,char rea[][10],char disp[][10])
{
	if(rea[x][y]!='X'&&disp[x][y]=='B'&&x>=0&&y>=0&&x<=9&&y<=9)
	{
		disp[x][y]=rea[x][y];
		if(rea[x][y]=='0')
		{
			disp[x][y]='-';
			revealwhen0(x,y+1,rea,disp);
			revealwhen0(x,y-1,rea,disp);
			revealwhen0(x-1,y+1,rea,disp);
			revealwhen0(x-1,y,rea,disp);
			revealwhen0(x-1,y-1,rea,disp);
			revealwhen0(x+1,y,rea,disp);
			revealwhen0(x+1,y+1,rea,disp);
			revealwhen0(x+1,y-1,rea,disp);
		}
	}
}
void openbox(int x,int y,char rea[][10],char disp[][10],int score)
{
	str:
	cout<<"ENTER THE ROW NUMBER : ";
	cin>>x;
	cout<<"ENTER THE COLUMN NUMBER : ";
	cin>>y;
	if(rea[x][y]!='0'&&disp[x][y]!='F'&&rea[x][y]!='X'&&disp[x][y]=='B'&&x>=0&&y>=0&&x<=9&&y<=9)
	{

		disp[x][y]=rea[x][y];
	}
	else{
		if(rea[x][y]=='0'&&disp[x][y]=='B'&&x>=0&&y>=0&&x<=9&&y<=9)
		{

			revealwhen0(x,y,rea,disp);
		}else{
			if(rea[x][y]=='X'&&disp[x][y]=='B'&&x>=0&&y>=0&&x<=9&&y<=9)
			{
				scorecalc(score,rea,disp);
	            	revealmine(disp,rea);
				cout<<endl<<"you hit mine !!"<<endl;
				cout<<"your score : "<<score<<endl;
                lostcondition(rea,disp);
			}
			else{
				if(disp[x][y]!='B'&&disp[x][y]!='F'&&x>=0&&y>=0&&x<=9&&y<=9)
				{
					cout<<"THE BOX IS ALREADY OPENED !!"<<endl;
					goto str;
				}else{
					if(x<0||y<0||x>9||y>9)
					{
						cout<<"LOCATION ENTERED IS OUT OF THE SCOPE OF THE BOARD !"<<endl;
						goto str;
					}
					else{
						if(disp[x][y]=='F'&&x>=0&&y>=0&&x<=9&&y<=9)
						{
							cout<<"THE BOX IS ALREADY FLAGGED SO CAN'T OPEN THIS BOX !!"<<endl;
							goto str;
						}
					}
				}
			}
		}
	}
}
void flagbox(int x,int y,char rea[][10],char disp[][10])
{
	str:
		cout<<"ENTER THE ROW NUMBER : ";
	cin>>x;
	cout<<"ENTER THE COLUMN NUMBER : ";
	cin>>y;
	if(disp[x][y]=='B'&&x>=0&&y>=0&&x<=9&&y<=9)
	{
		disp[x][y]='F';
	}else{
		if(disp[x][y]=='F'&&x>=0&&y>=0&&x<=9&&y<=9)
		{
			cout<<"THIS BOX IS ALREADY FLAGGED !!!"<<endl;
			goto str;
		}else{
			if(x<0||y<0||x>9||y>9)
					{
						cout<<"LOCATION ENTERED IS OUT OF THE SCOPE OF THE BOARD !"<<endl;
						goto str;
					}else{
						if(disp[x][y]!='F'&&disp[x][y]!='B'&&x>=0&&y>=0&&x<=9&&y<=9)
						{
							cout<<"THE BOX IS ALREADY OPENED !!"<<endl;
							goto str;
						}
					}
		}
	}
}
void unflagthebox(int x,int y,char rea[][10],char disp[][10])
{
	st:
		cout<<"ENTER THE ROW NUMBER : ";
	cin>>x;
	cout<<"ENTER THE COLUMN NUMBER : ";
	cin>>y;
	if(disp[x][y]=='F'&&x>=0&&y>=0&&x<=9&&y<=9)
	{
		disp[x][y]='B';
	}else{
		if(disp[x][y]!='F'&&x>=0&&y>=0&&x<=9&&y<=9)
		{
			cout<<"SORRY THE BOX IS NOT FLAGGED !!!"<<endl;
			goto st;
		}else{
			if(x<0||y<0||x>9||y>9)
					{
						cout<<"LOCATIO ENTERED IS OUT OF THE SCOPE OF THE BOARD !"<<endl;
						goto st;
					}
		}
	}
}
void player_input(int x,int y,char rea[][10],char disp[][10],int scr)
{
	str:
	cout<<endl<<"PRESS 1 TO OPEN THE BOX PRESS 2 TO FLAG THE BOX PRESS 3 TO UNFLAG THE BOX"<<endl;
	char choice;
	cout<<"YOUR CHOICE : ";
	cin>>choice;
    switch(choice)
    {
    	case '1':
    		openbox(x,y,rea,disp,scr);
    		break;
    	case '2':
		    flagbox(x,y,rea,disp);
		    break;
		case '3':
		   unflagthebox(x,y,rea,disp);
		   break;
		   default:
		   	cout<<"INVALID ENTRY !!!"<<endl;
		   	goto str;
	}
	writeToFile(disp);
}
void flagcounter(char disp[][10],char rea[][10])
{
	int flag=0;
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(rea[i][j]=='X')
			{
				flag++;
			}
		}
	}
	cout<<"TOTAL NUMBER OF FLAGS : "<<flag<<endl;
	cout<<"TOTAL NUMBER OF MINES : "<<flag<<endl;
	int flgrem=0;
	flgrem=flag;
		for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(disp[i][j]=='F')
			{
				flgrem--;
			}
		}
	}

	cout<<"NUMBER OF FLAGS LEFT : "<<flgrem<<endl;
	cout<<"NUMBER OF MINES LEFT : "<<flgrem<<endl;
}
char revealmine(char disp[][10],char rea[][10])
{

	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(rea[i][j]=='X')
			{
			disp[i][j]=rea[i][j];
			}
		}
	}
	printanyboard(disp);
}
int wincondition(char rea[][10],char disp[][10])
{
	int counter=0;
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(disp[i][j]=='F'&&rea[i][j]=='X')
			{
				counter++;
			}
		}
	}
	if(counter==10);
	{
		return counter;
	}
}
int lostcondition(char rea[][10], char dis[][10])
{
	int y;
	for(int i=0;i<=9;i++)
	{
		for(int j=0;j<=9;j++)
	{
	if( dis[i][j]=='X')
	{
		return 2;
	}
	else{
		y=1;
	}
}
}
}
void project()
{
	for(int i=0;i<49;i++)
	{
		cout<<"$$";
	}
	cout<<endl;
	for(int i=0;i<5;i++)
	cout<<"**"<<setw(96)<<"**"<<endl;
		for(int i=0;i<49;i++)
	{
		cout<<"$$";
	}

	for(int i=0;i<49;i++)
	{
		cout<<"$$";
	}
	cout<<endl;
	for(int i=0;i<5;i++)
	cout<<"**"<<setw(96)<<"**"<<endl;
		for(int i=0;i<49;i++)
	{
		cout<<"$$";
	}
	cout<<endl;
//	system("PAUSE");
}
void playerinfo(char t[],int size)
{
	cout<<setw(50)<<"WELCOME TO MINESWEEPER !!!"<<endl;
	cout<<setw(30)<<"PLAYER'S INFORMATION "<<endl;
	cout<<setw(25)<<"ENTER YOUR NAME : ";
	cin.getline(t,size-1);
}
int scorecalc(int x,char rea[][10],char disp[][10])
{
	x=0;
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(rea[i][j]=='X'&&disp[i][j]=='X')
			{
				x+=10;
			}
		}
	}
	return x;
}

//by Viktoriia Dziadukh 2023
