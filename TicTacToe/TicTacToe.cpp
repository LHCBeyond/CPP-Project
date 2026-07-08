#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>

void drawBoard( char *spaces );
int chooseComputerType();
void playerMove( char *spaces, char player );
void computerMove( char *spaces, char player, char computer, int computerType );
void randomComputerMove( char *spaces, char computer );
void minimaxComputerMove( char *spaces, char player, char computer );
int minimax( char *spaces, char player, char computer, bool isMaximizing );
bool checkWinner( char *spaces, char marker );
bool checkTie( char *spaces );

int main()
{
    char spaces[ 9 ] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', };
    char player = 'X'; 
    char computer = 'O';
    int computerType;
    bool running = true;

    srand( time( NULL ) );
    computerType = chooseComputerType();
    drawBoard( spaces );

    if ( computerType == 3 )
    {
        while ( running )
        {
            minimaxComputerMove( spaces, computer, player );
            std::cout << "Minimax X moved.\n";
            drawBoard( spaces );

            if ( checkWinner( spaces, player ) )
            {
                std::cout << "MINIMAX X WINS!";
                running = false;
                break;
            }

            if ( checkTie( spaces ) )
            {
                std::cout << "TIE!\n";
                running = false;
                break;
            }

            minimaxComputerMove( spaces, player, computer );
            std::cout << "Minimax O moved.\n";
            drawBoard( spaces );

            if ( checkWinner( spaces, computer ) )
            {
                std::cout << "MINIMAX O WINS!";
                running = false;
                break;
            }

            if ( checkTie( spaces ) )
            {
                std::cout << "TIE!\n";
                running = false;
                break;
            }
        }
    }
    else
    {
        while ( running )
        {
            playerMove( spaces, player );
            drawBoard( spaces );
            if ( checkWinner( spaces, player ) )
            {
                std::cout << "YOU WIN!";
                running = false;
                break;
            }
            if ( checkTie( spaces ) )
            {
                std::cout << "TIE!\n";
                running = false;
                break;
            }
            computerMove( spaces, player, computer, computerType );
            drawBoard( spaces );
            if ( checkWinner( spaces, computer ) )
            {
                std::cout << "YOU LOSE!";
                running = false;
                break;
            }
            if ( checkTie( spaces ) )
            {
                std::cout << "TIE!\n";
                running = false;
                break;
            }
        }
    }

    return 0;
}

void drawBoard( char *spaces )
{
    std::cout << '\n';
    std::cout << "     |     |     \n";
    std::cout << "  " << spaces[ 0 ] << "  |  " << spaces[ 1 ] << "  |  " << spaces[ 2 ] << "   \n";
    std::cout << "_____|_____|_____\n";
    std::cout << "     |     |     \n";
    std::cout << "  " << spaces[ 3 ] << "  |  " << spaces[ 4 ] << "  |  " << spaces[ 5 ] << "   \n";
    std::cout << "_____|_____|_____\n";
    std::cout << "     |     |     \n";
    std::cout << "  " << spaces[ 6 ] << "  |  " << spaces[ 7 ] << "  |  " << spaces[ 8 ] << "   \n";
    std::cout << "     |     |     \n";
    std::cout << '\n';
}

int chooseComputerType()
{
    int computerType;

    do
    {
        std::cout << "Choose computer type:\n";
        std::cout << "1. Random computer\n";
        std::cout << "2. Minimax computer\n";
        std::cout << "3. Minimax computer vs minimax computer\n";
        std::cout << "Enter your choice: ";
        std::cin >> computerType;

        if ( std::cin.fail() )
        {
            std::cin.clear();
            std::cin.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
            computerType = 0;
        }
    } while ( computerType != 1 && computerType != 2 && computerType != 3 );

    return computerType;
}

void playerMove( char *spaces, char player )
{
    int number;

    do
    {
        std::cout << "Enter a spot to place a marker (1-9): ";
        std::cin >> number;

        if ( std::cin.fail() )
        {
            std::cin.clear();
            std::cin.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
            continue;
        }

        if ( number >= 1 && number <= 9 && spaces[ number - 1 ] == ' ' )
        {
            spaces[ number - 1 ] = player;
            break;
        }
    } while ( true );
}

void computerMove( char *spaces, char player, char computer, int computerType )
{
    if ( computerType == 1 )
    {
        randomComputerMove( spaces, computer );
    }
    else
    {
        minimaxComputerMove( spaces, player, computer );
    }
}

void randomComputerMove( char *spaces, char computer )
{
    int number;

    while ( true )
    {
        number = rand() % 9;
        if ( spaces[ number ] == ' ' )
        {
            spaces[ number ] = computer;
            break;
        }
    }
}

void minimaxComputerMove( char *spaces, char player, char computer )
{
    int bestScore = -1000;
    int bestMove = -1;

    for ( int i = 0; i < 9; i++ )
    {
        if ( spaces[ i ] == ' ' )
        {
            spaces[ i ] = computer;
            int score = minimax( spaces, player, computer, false );
            spaces[ i ] = ' ';

            if ( score > bestScore )
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    if ( bestMove != -1 )
    {
        spaces[ bestMove ] = computer;
    }
}

int minimax( char *spaces, char player, char computer, bool isMaximizing )
{
    if ( checkWinner( spaces, computer ) )
    {
        return 1;
    }

    if ( checkWinner( spaces, player ) )
    {
        return -1;
    }

    if ( checkTie( spaces ) )
    {
        return 0;
    }

    if ( isMaximizing )
    {
        int bestScore = -1000;

        for ( int i = 0; i < 9; i++ )
        {
            if ( spaces[ i ] == ' ' )
            {
                spaces[ i ] = computer;
                int score = minimax( spaces, player, computer, false );
                spaces[ i ] = ' ';

                if ( score > bestScore )
                {
                    bestScore = score;
                }
            }
        }

        return bestScore;
    }
    else
    {
        int bestScore = 1000;

        for ( int i = 0; i < 9; i++ )
        {
            if ( spaces[ i ] == ' ' )
            {
                spaces[ i ] = player;
                int score = minimax( spaces, player, computer, true );
                spaces[ i ] = ' ';

                if ( score < bestScore )
                {
                    bestScore = score;
                }
            }
        }

        return bestScore;
    }
}

bool checkWinner( char *spaces, char marker )
{
    if ( spaces[ 0 ] == marker && spaces[ 1 ] == marker && spaces[ 2 ] == marker )
    {
        return true;
    }

    if ( spaces[ 3 ] == marker && spaces[ 4 ] == marker && spaces[ 5 ] == marker )
    {
        return true;
    }

    if ( spaces[ 6 ] == marker && spaces[ 7 ] == marker && spaces[ 8 ] == marker )
    {
        return true;
    }

    if ( spaces[ 0 ] == marker && spaces[ 3 ] == marker && spaces[ 6 ] == marker )
    {
        return true;
    }

    if ( spaces[ 1 ] == marker && spaces[ 4 ] == marker && spaces[ 7 ] == marker )
    {
        return true;
    }

    if ( spaces[ 2 ] == marker && spaces[ 5 ] == marker && spaces[ 8 ] == marker )
    {
        return true;
    }

    if ( spaces[ 0 ] == marker && spaces[ 4 ] == marker && spaces[ 8 ] == marker )
    {
        return true;
    }

    if ( spaces[ 2 ] == marker && spaces[ 4 ] == marker && spaces[ 6 ] == marker )
    {
        return true;
    }

    return false;
}

bool checkTie( char *spaces )
{
    for ( int i = 0; i < 9; i++ )
    {
        if ( spaces[ i ] == ' ' )
        {
            return false;
        }
    }

    return true;
}
