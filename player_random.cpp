#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>
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
const int SIZE = 3;
array<array<int, SIZE>, SIZE> board;
Move get_state (int x,int y);
Move minimax (int x,int y);

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
    int x, y;
    // Keep updating the output until getting killed.
    while(true) {
        // Choose a random spot.
        int x = (rand() % SIZE);
        int y = (rand() % SIZE);
        if (board[x][y] == EMPTY) 
        {
            fout << x << " " << y << endl;
            Move minimax(x,y);
            cout<<minimax.row<<" "<<minimax.col<<'\n';
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }
    }
}

Move get_state(int x,int y)
{
    int count=0,val_player=0;
    int row_tmp=0,col_tmp=0,dia_LUP=0,dia_RUP=0;
    Move bestMove;
    bestMove.col=-1;
    bestMove.row=-1;

    if(board[x][y]==player)
    {
        for(int i=-2;i<=2;i++)//check continuous chesses of col
        {
            int newx=x+i;

            if(newx>=0 && newx<15)
            {
                if(board[newx][y]==player)
                    count++;
                else
                {
                    if(count>=3)
                        int tmp=1;
                    count=0;
                }
            }
        }
        if(count>=3)
            row_tmp=1;

        for(int j=-2;j<=2;j++)//check continuous chesses of column
        {
            int newy=y+j;
            count=0;

            if(newy>=0 && newy<15)
            {
                if(board[x][newy]==player)
                    count++;
                else
                    count=0;
            }
        }
        if(count>=3)
            col_tmp=1;

        for(int i=-2;i<=2;i++)//check continuous chesses of diag(\)
        {
            int newx=x+i;
            int newy=y+i;
            int count=0;
            if(newx>=0 && newx<15 && newy>=0 && newy<15)
            {
                if(board[newx][newy]==player)
                    count++;
                else 
                    count=0;
            }
        }
        if(count>=3)
            dia_LUP=1;

        for(int i=-2;i<=2;i++)//check continuous chesses of diag(/)
        {
            int newx=x+i;
            int newy=y-i;
            int count=0;
            if(newx>=0 && newx<15 && newy>=0 && newy<15)
            {
                if(board[newx][newy]==player)
                    count++;
                else 
                    count=0;
            }
        }
        if(count>=3)
            dia_RUP=1;

        val_player = row_tmp + col_tmp + dia_LUP + dia_RUP;
        return bestMove;
    }
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
