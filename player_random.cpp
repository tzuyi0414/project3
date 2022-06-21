#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include<limits.h>
using namespace std;
#define MIN INT_MIN
#define MAX INT_MAX

enum SPOT_STATE 
{
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

struct Move
{   Move() {
        for(int i = 0; i < SIZE; i++) 
        {
            for(int j = 0; j < SIZE; j++) 
            {
                chess_new[i][j] = board[i][j];
            }
        }
        value=0;
        alpha=INT_MIN;
        beta=INT_MAX;
        user=player;
    }
    Move(int x,int y,Move temp)
    {
        for(int i = 0; i < SIZE; i++) 
        {
            for(int j = 0; j < SIZE; j++) 
            {
                chess_new[i][j] = temp.chess_new[i][j];
            }
        }
        chess_new[x][y] = temp.user;
        user=3-temp.user;
        alpha=INT_MIN;
        beta=INT_MAX;
        value=0;
    }
    int value,alpha,beta,user;
    array<array<int, SIZE>, SIZE> chess_new;
};
int m,n;
int player;
int opponent;
const int SIZE = 15;
array<array<int, SIZE>, SIZE> board;
array<array<int, SIZE>, SIZE> flag;

int flag=0;
int get_state (int x,int y);
Move minimax (int x,int y);
bool legal_position(int x,int y);

void read_board(ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

void write_valid_spot(ofstream& fout) {
    srand(time(NULL));
    //int x, y;
    // Keep updating the output until getting killed.
    while(true) {
        // Choose a random spot.
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                if(board[i][j]==EMPTY)
                {
                    i=m;
                    j=n;
                    
                }
            }
        }
        int x = m;//(rand() % SIZE);
        int y = n;//(rand() % SIZE);
        if (board[x][y] == EMPTY) 
        {
            fout << x << " " << y << endl;
            
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }
    }
}

/*int get_state(Move cur)
{
    int p=0,q=0;
    cur.chess_new[p][q];
    int count=0,val_3=0,val_4=0,val_5=0,i=0,j=0,newx=0,newy=0;
    int row_tmp=0,col_tmp=0,dia_LUP=0,dia_RUP=0;
    Move state_player;
    Move state_opponent;
    Move nextstate;
    
    if(cur.chess_new[p][q]==cur.user)
    {
        count=0;
        for(j=-1;j<=1;j++)//check continuous chesses of row
        {
            =y+j;

            if(legal_position(x,newy))
            {
                if(board[x][newy]==player)
                    count++;
                else
                    count=0;
            }
        }
        if(count==3)
            row_tmp=1;
        
        count=0;
        for(i=-1;i<=1;i++)//check continuous chesses of column
        {
            newx=x+i;
            if(legal_position(newx,y))
            {
                if(board[newx][y]==player)
                    count++;
                else
                    count=0;
            }
        }
        if(count==3)
            col_tmp=1;

        count=0;
        for(i=-1;i<=1;i++)//check continuous chesses of diag(\)
        {
            newx=x+i;
            newy=y+i;
            
            if(legal_position(newx,newy))
            {
                if(board[newx][newy]==player)
                    count++;
                else 
                    count=0;
            }
        }
        if(count==3)
            dia_LUP=1;

        count=0;
        for(i=-1;i<=1;i++)//check continuous chesses of diag(/)
        {
            newx=x+i;
            newy=y-i;
            
            if(legal_position(newx,newy))
            {
                if(board[newx][newy]==player)
                    count++;
                else 
                    count=0;
            }
        }
        if(count==3)
            dia_RUP=1;

        val_3 += row_tmp + col_tmp + dia_LUP + dia_RUP;

        if(val_3 != 0)
        {
            if(row_tmp != 0) //check there are continuous 4 or 5 chesses in row or not
            {
                j=1; //check the right way of the row
                newy=y+j;
                if(legal_position(x,newy))
                {
                    if(board[x][newy]==player)  //4 cont. chesses
                    {
                        if(board[x][newy+1]==player)//5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }

                j=-1;   //check the left way of the row
                newy=y+j;
                if(legal_position(x,newy))
                {
                    if(board[x][newy]==player)  //4 cont. chesses
                    {
                        if(board[x][newy-1]==player)//5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }
            }

            if(col_tmp != 0) //check there are continuous 4 or 5 chesses in column or not
            {
                i=1; //check the right way of the col
                newx=x+i;
                if(legal_position(newx,y))
                {
                    if(board[newx][y]==player)  //4 cont. chesses
                    {
                        if(board[newx+1][y]==player)//5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }

                i=-1;   //check the left way of the row
                newx=x+i;
                if(legal_position(newx,y))
                {
                    if(board[newx][y]==player)  //4 cont. chesses
                    {
                        if(board[newx-1][y]==player)//5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }
            }

            if(dia_LUP != 0) //check there are continuous 4 or 5 chesses in (\) or not
            {
                i=2; //check the right-down way 
                newx=x+i;
                newy=y+i;
                if(legal_position(newx,newy))
                {
                    if(board[newx][newy]==player) //4 cont. chesses
                    {
                        if(board[newx+1][newy+1]==player) //5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }

                i=-2; //check the right-up way 
                newx=x+i;
                newy=y+i;
                if(legal_position(newx,newy))
                {
                    if(board[newx][newy]==player) //4 cont. chesses
                    {
                        if(board[newx-1][newy-1]==player) //5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }
            }

            if(dia_RUP != 0) //check there are continuous 4 or 5 chesses in (/) or not
            {
                i=2; //check the left-down way 
                newx=x+i;
                newy=y-i;
                if(legal_position(newx,newy))
                {
                    if(board[newx][newy]==player) //4 cont. chesses
                    {
                        if(board[newx+1][newy-1]==player) //5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }

                i=-2;
                newx=x+i;
                newy=y-i;
                if(legal_position(newx,newy))
                {
                    if(board[newx][newy]==player)
                    {
                        if(board[newx-1][newy+1]==player)
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }
            }
        }
    }
    state_player.value = val_3 + val_4 + val_5;
    if(state_player.value>state_player.alpha)
        state_player.alpha=state_player.value;
    
    else if(state_player.value<state_player.beta)
        state_player.beta=state_player.value;


    //evaluate the state of opponent
    count=0,val_3=0,val_4=0,val_5=0;
    row_tmp=0,col_tmp=0,dia_LUP=0,dia_RUP=0;

    if(board[x][y] ==opponent)
    {
        count=0;
        for(j=-1;j<=1;j++)//check continuous chesses of row
        {
            newy=y+j;

            if(legal_position(x,newy))
            {
                if(board[x][newy]==opponent)
                    count++;
                else
                    count=0;
            }
        }
        if(count==3)
            row_tmp=1;
        
        count=0;
        for(i=-1;i<=1;i++)//check continuous chesses of column
        {
            newx=x+i;
            if(legal_position(newx,y))
            {
                if(board[newx][y]==opponent)
                    count++;
                else
                    count=0;
            }
        }
        if(count==3)
            col_tmp=1;

        count=0;
        for(i=-1;i<=1;i++)//check continuous chesses of diag(\)
        {
            newx=x+i;
            newy=y+i;
            
            if(legal_position(newx,newy))
            {
                if(board[newx][newy]==opponent)
                    count++;
                else 
                    count=0;
            }
        }
        if(count==3)
            dia_LUP=1;

        count=0;
        for(i=-1;i<=1;i++)//check continuous chesses of diag(/)
        {
            newx=x+i;
            newy=y-i;
            
            if(legal_position(newx,newy))
            {
                if(board[newx][newy]==opponent)
                    count++;
                else 
                    count=0;
            }
        }
        if(count==3)
            dia_RUP=1;

        val_3 += row_tmp + col_tmp + dia_LUP + dia_RUP;

        if(val_3 != 0)
        {
            if(row_tmp != 0) //check there are continuous 4 or 5 chesses in row or not
            {
                j=1; //check the right way of the row
                newy=y+j;
                if(legal_position(x,newy))
                {
                    if(board[x][newy]==opponent)  //4 cont. chesses
                    {
                        if(board[x][newy+1]==opponent)//5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }

                j=-1;   //check the left way of the row
                newy=y+j;
                if(legal_position(x,newy))
                {
                    if(board[x][newy]==opponent)  //4 cont. chesses
                    {
                        if(board[x][newy-1]==opponent)//5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }
            }

            if(col_tmp != 0) //check there are continuous 4 or 5 chesses in column or not
            {
                i=1; //check the right way of the col
                newx=x+i;
                if(legal_position(newx,y))
                {
                    if(board[newx][y]==opponent)  //4 cont. chesses
                    {
                        if(board[newx+1][y]==opponent)//5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }

                i=-1;   //check the left way of the row
                newx=x+i;
                if(legal_position(newx,y))
                {
                    if(board[newx][y]==opponent)  //4 cont. chesses
                    {
                        if(board[newx-1][y]==opponent)//5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }
            }

            if(dia_LUP != 0) //check there are continuous 4 or 5 chesses in (\) or not
            {
                i=2; //check the right-down way 
                newx=x+i;
                newy=y+i;
                if(legal_position(newx,newy))
                {
                    if(board[newx][newy]==opponent) //4 cont. chesses
                    {
                        if(board[newx+1][newy+1]==opponent) //5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }

                i=-2; //check the right-up way 
                newx=x+i;
                newy=y+i;
                if(legal_position(newx,newy))
                {
                    if(board[newx][newy]==opponent) //4 cont. chesses
                    {
                        if(board[newx-1][newy-1]==opponent) //5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }
            }

            if(dia_RUP != 0) //check there are continuous 4 or 5 chesses in (/) or not
            {
                i=2; //check the left-down way 
                newx=x+i;
                newy=y-i;
                if(legal_position(newx,newy))
                {
                    if(board[newx][newy]==opponent) //4 cont. chesses
                    {
                        if(board[newx+1][newy-1]==opponent) //5 cont. chesses
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }

                i=-2;
                newx=x+i;
                newy=y-i;
                if(legal_position(newx,newy))
                {
                    if(board[newx][newy]==opponent)
                    {
                        if(board[newx-1][newy+1]==opponent)
                        {
                            val_5++;
                            val_3--;
                        }
                        else
                        {
                            val_4++;
                            val_3--;
                        }
                    }
                }
            }
        }
    }
    state_opponent.value = val_4 + val_5;
    if(state_player.value>state_player.alpha)
        state_player.alpha=state_player.value;
    
    else if(state_player.value<state_player.beta)
        state_player.beta=state_player.value;

    //nextstate.value = state_player.value - state_opponent.value;

    return nextstate.value;
}*/

//judge whether the player or AI has legal position
bool legal_position(int x,int y)
{
    if ((x < 0) | (x >= 15) | (y < 0) | (y >= 15))
        return false;

    else if ((board[x][y] == 1) | (board[x][y] == 2))
        return false;

    else return true;
}

int depth=5;

int minimax(int x,int y,int d,int user,Move last)
{
    //int alpha=0,beta=0;
    //Move best={best.col=-1,best.row=-1,best.value=0};//initialize
    Move temp = Move(x, y, last);//initialize
    
    if(d==0)
    {
        //return get_state(temp);
    }
    
    else
    {
        if(user==player)
        {
            temp.value=MIN;
            for(int i=0;i<SIZE;i++)
            {
                for(int j=0;j<SIZE;j++)
                {
                    if(legal_position(i,j))
                    {
                        board[i][j]=player;
                        temp = Move(i,j,last);
                        temp.value=max(temp.value,minimax(i,j, d-1,opponent,temp));
                        board[i][j]=EMPTY;
                        if(temp.value>temp.alpha && d==depth)
                        {
                            m = i;
                            n = j;
                        }
                        temp.alpha=max(temp.alpha,temp.value);      
                        if(temp.alpha>=temp.beta)
                            break;
                    }
                }
            }
            return temp.value;
        }
        else
        {
            temp.value=MAX;
            for(int i=0;i<SIZE;i++)
            {
                for(int j=0;j<SIZE;j++)
                {
                    if(legal_position(i,j))
                    {
                        board[i][j]=(3-player);
                        temp = Move(i,j,last);
                        temp.value=min(temp.value,minimax(i,j,d-1,player,temp));
                        board[i][j]=EMPTY;
                        temp.beta=min(temp.beta,temp.value);
                        if(temp.beta<=temp.alpha)
                            break;
                    }
                }
            }
            return temp.value;
        }
    }
}

int main(int, char** argv) 
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
