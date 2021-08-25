
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

struct Move
{
    int row, col;
};

char player = 'x', opponent = 'o';

bool aFilled = false, bFilled = false, cFilled = false;
bool dFilled = false, eFilled = false, fFilled = false;
bool gFilled = false, hFilled = false, iFilled = false;

// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

// This is the evaluation function as discussed
// in the previous article ( http://goo.gl/sJgv68 )
int evaluate(char b[3][3])
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0] == b[row][1] &&
            b[row][1] == b[row][2])
        {
            if (b[row][0] == player)
                return +10;
            else if (b[row][0] == opponent)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col < 3; col++)
    {
        if (b[0][col] == b[1][col] &&
            b[1][col] == b[2][col])
        {
            if (b[0][col] == player)
                return +10;

            else if (b[0][col] == opponent)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == player)
            return +10;
        else if (b[0][0] == opponent)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[0][2] == player)
            return +10;
        else if (b[0][2] == opponent)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(char board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (isMovesLeft(board) == false)
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == '_')
                {
                    // Make the move
                    board[i][j] = player;

                    // Call minimax recursively and choose
                    // the maximum value
                    best = max(best,
                        minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == '_')
                {
                    // Make the move
                    board[i][j] = opponent;

                    // Call minimax recursively and choose
                    // the minimum value
                    best = min(best,
                        minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

// This will return the best possible move for the ai
Move findBestMove(char board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Check if cell is empty
            if (board[i][j] == '_')
            {
                // Make the move
                board[i][j] = player;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = '_';

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    printf("The value of the best Move is : %d\n\n",
        bestVal);

    return bestMove;
}

// Driver code
int main()
{
    bool playAgain;
    string again;

    do
    {
        string choice;
        bool validChoise;
        bool someoneWon = false;

        // Resets all spots to not be filled, for if choosing to play again
        aFilled = false, bFilled = false, cFilled = false;
        dFilled = false, eFilled = false, fFilled = false;
        gFilled = false, hFilled = false, iFilled = false;

        char board[3][3] =
        {
            { '_', '_', '_' },
            { '_', '_', '_' },
            { '_', '_', '_' }
        };

        cout << "You are o, your opponent is x" << endl;

        do
        {

            //Prints the board --------------------------------------------
            cout << endl;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (j == 0)
                    {
                        cout << "   ";
                    }

                    cout << board[i][j] << " ";

                    if (j == 2)
                    {
                        cout << endl;
                    }
                }
            }
            cout << endl;
            //Ends printing the board -------------------------------------

            do
            {
                validChoise = true;
                cout << "Where would you like to go? (Pick a letter a - i)" << endl << "   a  b  c" << endl << "   d  e  f" << endl << "   g  h  i" << endl;
                cin >> choice;

                //Checks if player's move is valid, updates board if it is, asks them to try again if it isn't
                //Clunky, but effective
                if (choice == "a" && aFilled == false)
                {
                    board[0][0] = 'o';
                    aFilled = true;
                }
                else if (choice == "b" && bFilled == false)
                {
                    board[0][1] = 'o';
                    bFilled = true;
                }
                else if (choice == "c" && cFilled == false)
                {
                    board[0][2] = 'o';
                    cFilled = true;
                }
                else if (choice == "d" && dFilled == false)
                {
                    board[1][0] = 'o';
                    dFilled = true;
                }
                else if (choice == "e" && eFilled == false)
                {
                    board[1][1] = 'o';
                    eFilled = true;
                }
                else if (choice == "f" && fFilled == false)
                {
                    board[1][2] = 'o';
                    fFilled = true;
                }
                else if (choice == "g" && gFilled == false)
                {
                    board[2][0] = 'o';
                    gFilled = true;
                }
                else if (choice == "h" && hFilled == false)
                {
                    board[2][1] = 'o';
                    hFilled = true;
                }
                else if (choice == "i" && iFilled == false)
                {
                    board[2][2] = 'o';
                    iFilled = true;
                }
                else
                {
                    cout << "Not a valid option! Try again" << endl;
                    validChoise = false;
                }

            } while (validChoise == false);


            system("cls");

            // Computer's turn -------------------------------------------------
            Move bestMove = findBestMove(board);
            board[bestMove.row][bestMove.col] = 'x';

            if (bestMove.row == 0 && bestMove.col == 0)
            {
                aFilled = true;
            }
            else if (bestMove.row == 0 && bestMove.col == 1)
            {
                bFilled = true;
            }
            else if (bestMove.row == 0 && bestMove.col == 2)
            {
                cFilled = true;
            }
            else if (bestMove.row == 1 && bestMove.col == 0)
            {
                dFilled = true;
            }
            else if (bestMove.row == 1 && bestMove.col == 1)
            {
                eFilled = true;
            }
            else if (bestMove.row == 1 && bestMove.col == 2)
            {
                fFilled = true;
            }
            else if (bestMove.row == 2 && bestMove.col == 0)
            {
                gFilled = true;
            }
            else if (bestMove.row == 2 && bestMove.col == 1)
            {
                hFilled = true;
            }
            else if (bestMove.row == 2 && bestMove.col == 2)
            {
                iFilled = true;
            }
            // Computer's turn end ---------------------------------------------


            //Checks if someone has won or if board is full
            if (minimax(board, 0, false) == 10 || minimax(board, 0, false) == -10 || isMovesLeft(board) == false)
            {
                someoneWon = true;
            }

        } while (someoneWon == false);


        //Prints the board --------------------------------------------
        cout << endl;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (j == 0)
                {
                    cout << "   ";
                }

                cout << board[i][j] << " ";

                if (j == 2)
                {
                    cout << endl;
                }
            }
        }
        cout << endl;
        //Ends printing the board -------------------------------------

        if (minimax(board, 0, false) == 10)
        {
            cout << "Computer wins!";
        }
        else if (minimax(board, 0, false) == -10)
        {
            cout << "Player wins!";
        }
        else
        {
            cout << "Nobody wins!";
        }

        bool againError;

        do
        {

            cout << endl << "Play Again? (y for y, n for no)" << endl;
            cin >> again;

            againError = false;

            if (again == "y")
            {
                playAgain = true;
            }
            else if (again == "n")
            {
                playAgain = false;
            }
            else
            {
                cout << "Not a valid option bud, try again" << endl;
                againError = true;
            }
        } while (againError == true);

        system("cls");


    } while (playAgain == true);

    return 0;
}

//printf("The Optimal Move is :\n");
//printf("ROW: %d COL: %d\n\n", bestMove.row, bestMove.col);
