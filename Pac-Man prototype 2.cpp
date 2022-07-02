#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;
char tmp_map[18][32];

char map[18][32] = {
	"+#############################+",
	"|                             |",
	"|                             |",
	"|## ########### ##   #########|",
	"|   |                         |",
	"| | |### |  |           |     |",
	"| |      |  | |###  |   |  |  |",
	"| | #####|  | |      ## |     |",
	"| |           |###  |      |  |",
	"| |##### ###         ##       |",
	"|          ######  ####### ###|",
	"|                             |",
	"|# ### ####      ###   #######|",
	"|                             |",
	"|                             |",
	"|                             |",
	"|                             |",
	"+#############################+"
	};

void ShowMap()
{
	for(int i = 0; i < 18; i++) {
		cout<<map[i]<<endl;
	}
}

void gotoxy( short x, short y )
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = { x, y } ;

    SetConsoleCursorPosition( hStdout, position ) ;
}

struct walk {
	short walk_count;
	short x;
	short y;
	short back;
};

struct target {
	short x;
	short y;
};

vector<target> walk_queue;

vector<walk> BFSArray;

void AddArray(int x, int y, int wc , int back){
	if( tmp_map[y][x] == ' ' || tmp_map[y][x] == '.' ){
		tmp_map[y][x] = '#';
		walk tmp;
		tmp.x = x;
		tmp.y = y;
		tmp.walk_count = wc;
		tmp.back = back;
		BFSArray.push_back( tmp );
	}
}

void FindPath( int sx, int sy, int x, int y ){
	memcpy(tmp_map, map, sizeof(map));
	BFSArray.clear();
	walk tmp;
	tmp.x = sx;
	tmp.y = sy;
	tmp.walk_count = 0;
	tmp.back = -1;
	BFSArray.push_back(tmp);

	int i = 0;
	while( i < BFSArray.size() ){
		if( BFSArray[i].x == x && BFSArray[i].y == y ){
			walk_queue.clear();
			target tmp2;
			while( BFSArray[i].walk_count != 0 ){
				tmp2.x = BFSArray[i].x;
				tmp2.y = BFSArray[i].y;
				walk_queue.push_back(tmp2);

				i = BFSArray[i].back;
			}

			break;
		}

		AddArray(BFSArray[i].x+1, BFSArray[i].y, BFSArray[i].walk_count+1, i); //right
		AddArray(BFSArray[i].x-1, BFSArray[i].y, BFSArray[i].walk_count+1, i); //left
		AddArray(BFSArray[i].x, BFSArray[i].y+1, BFSArray[i].walk_count+1, i); //below
		AddArray(BFSArray[i].x, BFSArray[i].y-1, BFSArray[i].walk_count+1, i); //above
		i++;
	}

	BFSArray.clear();
}

int login()
{
    int cou=0;
    string uname, pword, u, p;
    cout<<"Enter username: ";
    cin>>uname;
    cout<<"Enter password: ";
    cin>>pword;
    ifstream f1("login.txt");
    while(f1>>u>>p)
    {
        if(uname==u && pword==p)
            {
                cou++;
            }
    }
    f1.close();
    if(cou!=0)
        {
            cout<<uname<<" your login was successful\n";
            return 1;
        }
    else
    {
        cout<<"Invalid username\n";
        return 0;
    }

}

void signup()
{
    string uname, pword;
    int ptr=0;
    cout<<"Enter username: ";
    cin>>uname;
    cout<<"Enter password: ";
    cin>>pword;
    ofstream f2("login.txt", ios::app); //cursor will go to end before each output operation0
    f2<<uname<<' '<<pword<<' '<<ptr<<endl;
    cout<<"Registration Successful\n";
}



int main()
{
    a:
    cout<<"Press 1 to login\nPress 2 to signup\nPress 3 to exit\n";
    int ch;
    cin>>ch;
    switch(ch)
    {
    case 1:
        {
        int s = login();
        if(s==1)
            cout<<"WELCOME TO PACMAN GAME\n\n\n";
        else
            goto a;
        break;
    }
    case 2:
        {
        signup();
        goto a;
        break;
        }
    case 3:
        exit(0);
        break;
    default:
        cout<<"Invalid choice\n";
    }
    bool running = true;
	int x = 15; // hero x
	int y = 16; // hero y
	int old_x;
	int old_y;

	int ex = 1;
	int ey = 1;


	int pts = 0;

	cout<<"Instruction:\n1. Arrow Keys to move your hero\n2. Eat the dots produced by the Eater to gain points\n3. Don't get caught by the Eater\n\n";
	cout<<"H -> Hard\nN -> Normal\nE -> Easy\n\nInput : ";
	fflush(stdin);
	char diffi;
	int speedmod = 3;

	cin >> diffi;

	if( diffi == 'N' ){
		speedmod = 2;
	}else if( diffi == 'H' ){
		speedmod = 1;
	}

	system("cls");
    ShowMap();

	gotoxy( x, y );
	cout << "H";

	int frame = 0;

	FindPath( ex,ey,x,y );

	while(running){
		gotoxy( x, y );
		cout << " ";

		old_x = x;
		old_y = y;

		if ( GetAsyncKeyState( VK_UP ) ){
			if( map[y-1][x] == '.' )
                {
                    map[y-1][x]= ' ';
                    y--;
                    pts++;
			}
			else if( map[y-1][x] == ' ' )
                y--;
		}
		if ( GetAsyncKeyState( VK_DOWN ) ){
			if( map[y+1][x] == '.' )
                {
                     map[y+1][x] = ' ';
                     y++;
                     pts++;
            }
            else if( map[y+1][x] == ' ' )
                y++;
		}
		if ( GetAsyncKeyState( VK_LEFT ) ){
			if( map[y][x-1] == '.' ){
                    map[y][x-1] = ' ';
                    x--;
                    pts++;
            }
            else if( map[y][x-1] == ' ' )
                x--;
		}
		if ( GetAsyncKeyState( VK_RIGHT ) ){
			if( map[y][x+1] == '.' ){
                    map[y][x+1] = ' ';
                    x++;
                    pts++;
            }
            else if( map[y][x+1] == ' ' )
                x++;
		}

		if( old_x != x || old_y != y ){
			FindPath( ex,ey,x,y);
		}

		gotoxy( x,y );
		cout << "H";

		map[ey][ex] = '.';
		gotoxy( ex, ey );
		cout << ".";

		if( frame%speedmod == 0 && walk_queue.size() != 0 ){
			ex = walk_queue.back().x;
			ey = walk_queue.back().y;
			walk_queue.pop_back();
		}

		gotoxy( ex, ey );
		cout << "E";

		if( ex == x && ey == y ){
			break;
		}

		gotoxy( 32, 1 );
		cout << pts;
		Sleep(100);
		frame++;
}
    system("cls");
    getchar();
    cout<<"You lose and your score is: "<<pts<<endl;
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
	return 0;
}
