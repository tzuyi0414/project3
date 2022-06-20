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

int player;
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

int evaluate(int x,int y)
{


}

//judge whether the player or AI has legal position
bool isture(int x,int y)
{
    if (x < 0 | x >= 15 | y < 0 | y >= 15)
        return false;

    else if (board[x][y] == 1 | board[x][y] == 2)
        return false;

    else return true;
}

int minimax(int x,int y,int depth)
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
                        bestscore=max(bestscore,minimax(i,j,depth-1));
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
                        //board[i][j];
                        bestscore=min(bestscore,minimax(i,j,depth-1));
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

int main(int, char** argv) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
