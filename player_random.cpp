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
    int row, col;
};

int player;
int opponent;
const int SIZE = 3;
array<array<int, SIZE>, SIZE> board;

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
        if (board[x][y] == EMPTY) {
            fout << x << " " << y << std::endl;
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }
    }
}

int value_function_player(int x,int y)
{
    int count=0;
    int row_tmp=0,col_tmp=0,dia_LUP=0,dia_RUP=0;
    if(board[x][y]==player)
    {
        for(int i=-2;i<=2;i++)//check continuous chesses of row
        {
            int newx=x+i;

            if(newx>=0 && newx<15)
            {
                if(board[newx][y]==player)
                    count++;
                else
                    count=0;
            }
        }
        if(count>=3)
            row_tmp=1;

        for(int j=-2;j<=2;j++)//check continuous chesses of column
        {
            int newy=x+j;
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

        int val_player = row_tmp + col_tmp + dia_LUP + dia_RUP;
    }
}

// This will return the best possible move for the player
/*Move search_BestMove(int board[SIZE][SIZE])
{
    int bestvalue=MIN;
    Move bestMove;
    bestMove.row=-1;
    bestMove.col=-1;
 
    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)
        {
            if (board[i][j]==EMPTY)
            {
                board[i][j]=player;// move
 
                // compute evaluation function for this move.
                int moveVal=minimax(i,j);
                board[i][j]=EMPTY;
 
                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal>bestvalue)
                {
                    bestMove.row=i;
                    bestMove.col=j;
                    bestvalue=moveVal;
                }
            }
        }
    } 
    return bestMove;
}*/

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
int minimax(int x,int y)
{
    int bestscore=0,alpha=0,beta=0;

    if(depth==0)
        return bestscore;
    else
    {
        if(board[x][y]==player)
        {
            bestscore=MIN;
            for(int i=0;i<SIZE;i++)
            {
                for(int j=0;j<SIZE;j++)
                {
                    if(board[i][j]==EMPTY)
                    {
                        board[i][j]=player;
                        depth-1;
                        bestscore=max(bestscore,minimax(i,j));
                        board[i][j]=EMPTY;
                        alpha=max(alpha,bestscore);
                        if(alpha>=beta)
                            break;
                    }
                }
            }
            return bestscore;
        }
        else
        {
            bestscore=MAX;
            for(int i=0;i<SIZE;i++)
            {
                for(int j=0;j<SIZE;j++)
                {
                    if(board[i][j]==EMPTY)
                    {
                        board[i][j]=(3-player);//
                        depth-1;
                        bestscore=min(bestscore,minimax(i,j));
                        board[i][j]=EMPTY;
                        beta=min(beta,bestscore);
                        if(beta<=alpha)
                            break;
                    }
                }
            }
            return bestscore;
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
