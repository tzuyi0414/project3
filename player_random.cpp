#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;
#define MIN -10000
#define MAX 10000

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

// This will return the best possible move for the player
Move search_BestMove(int board[SIZE][SIZE])
{
    int bestvalue=MIN;
    Move bestMove;
    bestMove.row=-1;
    bestMove.col=-1;
 
    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
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
