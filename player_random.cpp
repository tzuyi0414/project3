#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;
#define MIN -1000
#define MAX 1000

enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

struct Move
{
    int row, col,value;
};

int player;
int opponent;
const int SIZE = 15;
array<array<int, SIZE>, SIZE> board;
Move get_state (int x,int y);
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
        int x = (rand() % SIZE);
        int y = (rand() % SIZE);
        if (board[x][y] == EMPTY) 
        {
            fout << x << " " << y << endl;
            minimax(x,y);
            cout<<minimax(x,y).row<<" "<<minimax(x,y).col<<'\n';
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }
    }
}

Move get_state(int x,int y)
{
    int count=0,val_3=0,val_4=0,val_5=0;
    int row_tmp=0,col_tmp=0,dia_LUP=0,dia_RUP=0;
    Move state_player, state_opponent,nextstate;

    if(board[x][y]==player)
    {
        count=0;
        for(int j=-1;j<=1;j++)//check continuous chesses of row
        {
            int newy=y+j;

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
        for(int i=-1;i<=1;i++)//check continuous chesses of column
        {
            int newx=x+i;
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
        for(int i=-1;i<=1;i++)//check continuous chesses of diag(\)
        {
            int newx=x+i;
            int newy=y+i;
            
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
        for(int i=-1;i<=1;i++)//check continuous chesses of diag(/)
        {
            int newx=x+i;
            int newy=y-i;
            
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
                int j=1; //check the right way of the row
                int newy=y+j;
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

                int j=-1;   //check the left way of the row
                int newy=y+j;
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
                int i=1; //check the right way of the col
                int newx=x+i;
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

                int i=-1;   //check the left way of the row
                int newx=x+i;
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
                int i=2; //check the right-down way 
                int newx=x+i;
                int newy=y+i;
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

                int i=-2; //check the right-up way 
                int newx=x+i;
                int newy=y+i;
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
                int i=2; //check the left-down way 
                int newx=x+i;
                int newy=y-i;
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

                int i=-2;
                int newx=x+i;
                int newy=y-i;
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


    //evaluate the state of opponent
    int count=0,val_3=0,val_4=0,val_5=0;
    int row_tmp=0,col_tmp=0,dia_LUP=0,dia_RUP=0;

    if(board[x][y] ==opponent)
    {
        count=0;
        for(int j=-1;j<=1;j++)//check continuous chesses of row
        {
            int newy=y+j;

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
        for(int i=-1;i<=1;i++)//check continuous chesses of column
        {
            int newx=x+i;
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
        for(int i=-1;i<=1;i++)//check continuous chesses of diag(\)
        {
            int newx=x+i;
            int newy=y+i;
            
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
        for(int i=-1;i<=1;i++)//check continuous chesses of diag(/)
        {
            int newx=x+i;
            int newy=y-i;
            
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
                int j=1; //check the right way of the row
                int newy=y+j;
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

                int j=-1;   //check the left way of the row
                int newy=y+j;
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
                int i=1; //check the right way of the col
                int newx=x+i;
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

                int i=-1;   //check the left way of the row
                int newx=x+i;
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
                int i=2; //check the right-down way 
                int newx=x+i;
                int newy=y+i;
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

                int i=-2; //check the right-up way 
                int newx=x+i;
                int newy=y+i;
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
                int i=2; //check the left-down way 
                int newx=x+i;
                int newy=y-i;
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

                int i=-2;
                int newx=x+i;
                int newy=y-i;
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

    nextstate.value = state_player.value - state_opponent.value;
    return nextstate;
}


//judge whether the player or AI has legal position
bool legal_position(int x,int y)
{
    if (x < 0 | x >= 15 | y < 0 | y >= 15)
        return false;

    else if (board[x][y] == 1 | board[x][y] == 2)
        return false;

    else return true;
}

int depth=SIZE;
Move minimax(int x,int y)
{
    int alpha=0,beta=0;
    Move best;

    if(depth==0)
        return best;
    else
    {
        if(board[x][y]==player)
        {
            best.value=MIN;
            for(int i=0;i<SIZE;i++)
            {
                for(int j=0;j<SIZE;j++)
                {
                    if(legal_position(i,j))
                    {
                        board[i][j]=player;
                        get_state(i,j);
                        depth-1;
                        best.value=max(best.value,minimax(i,j).value);
                        board[i][j]=EMPTY;
                        alpha=max(alpha,best.value);
                        
                        if(alpha>=beta)
                            break;
                    }
                }
            }
            return best;
        }
        else
        {
            best.value=MAX;
            for(int i=0;i<SIZE;i++)
            {
                for(int j=0;j<SIZE;j++)
                {
                    if(legal_position(i,j))
                    {
                        board[i][j]=(3-player);//
                        get_state(i,j);
                        depth-1;
                        best.value=min(best.value,minimax(i,j).value);
                        board[i][j]=EMPTY;
                        beta=min(beta,best.value);
                        if(beta<=alpha)
                            break;
                    }
                }
            }
            return best;
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
