#include "TicTacToeCore/TicTacToeCore.h"

#include <array>
#include <cstdlib>
#include <ctime>

struct TicTacToeGame
{
    std::array< char, 9 > spaces;
    char player;
    char computer;
    char currentTurn;
    int computerType;
    TicTacToeGameStatus status;
};

namespace
{
    bool randomSeeded = false;

    void seedRandom()
    {
        if ( !randomSeeded )
        {
            srand( static_cast< unsigned int >( time( NULL ) ) );
            randomSeeded = true;
        }
    }

    bool checkWinner( const std::array< char, 9 > &spaces, char marker )
    {
        const int winningLines[ 8 ][ 3 ] =
        {
            { 0, 1, 2 },
            { 3, 4, 5 },
            { 6, 7, 8 },
            { 0, 3, 6 },
            { 1, 4, 7 },
            { 2, 5, 8 },
            { 0, 4, 8 },
            { 2, 4, 6 }
        };

        for ( int i = 0; i < 8; i++ )
        {
            if ( spaces[ winningLines[ i ][ 0 ] ] == marker &&
                 spaces[ winningLines[ i ][ 1 ] ] == marker &&
                 spaces[ winningLines[ i ][ 2 ] ] == marker )
            {
                return true;
            }
        }

        return false;
    }

    bool checkTie( const std::array< char, 9 > &spaces )
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

    int minimax( std::array< char, 9 > &spaces, char opponent, char ai, bool isMaximizing )
    {
        if ( checkWinner( spaces, ai ) )
        {
            return 1;
        }

        if ( checkWinner( spaces, opponent ) )
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
                    spaces[ i ] = ai;
                    int score = minimax( spaces, opponent, ai, false );
                    spaces[ i ] = ' ';

                    if ( score > bestScore )
                    {
                        bestScore = score;
                    }
                }
            }

            return bestScore;
        }

        int bestScore = 1000;

        for ( int i = 0; i < 9; i++ )
        {
            if ( spaces[ i ] == ' ' )
            {
                spaces[ i ] = opponent;
                int score = minimax( spaces, opponent, ai, true );
                spaces[ i ] = ' ';

                if ( score < bestScore )
                {
                    bestScore = score;
                }
            }
        }

        return bestScore;
    }

    bool randomMove( std::array< char, 9 > &spaces, char marker )
    {
        int openCount = 0;

        for ( int i = 0; i < 9; i++ )
        {
            if ( spaces[ i ] == ' ' )
            {
                openCount++;
            }
        }

        if ( openCount == 0 )
        {
            return false;
        }

        int selectedOpenIndex = rand() % openCount;

        for ( int i = 0; i < 9; i++ )
        {
            if ( spaces[ i ] == ' ' )
            {
                if ( selectedOpenIndex == 0 )
                {
                    spaces[ i ] = marker;
                    return true;
                }

                selectedOpenIndex--;
            }
        }

        return false;
    }

    bool minimaxMove( std::array< char, 9 > &spaces, char opponent, char ai )
    {
        int bestScore = -1000;
        int bestMove = -1;

        for ( int i = 0; i < 9; i++ )
        {
            if ( spaces[ i ] == ' ' )
            {
                spaces[ i ] = ai;
                int score = minimax( spaces, opponent, ai, false );
                spaces[ i ] = ' ';

                if ( score > bestScore )
                {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }

        if ( bestMove == -1 )
        {
            return false;
        }

        spaces[ bestMove ] = ai;
        return true;
    }

    void updateNormalStatus( TicTacToeGame *game )
    {
        if ( checkWinner( game->spaces, game->player ) )
        {
            game->status = TicTacToeGameStatusPlayerWon;
        }
        else if ( checkWinner( game->spaces, game->computer ) )
        {
            game->status = TicTacToeGameStatusComputerWon;
        }
        else if ( checkTie( game->spaces ) )
        {
            game->status = TicTacToeGameStatusTie;
        }
        else
        {
            game->status = TicTacToeGameStatusInProgress;
        }
    }

    void updateMinimaxVsMinimaxStatus( TicTacToeGame *game )
    {
        if ( checkWinner( game->spaces, game->player ) )
        {
            game->status = TicTacToeGameStatusMinimaxXWon;
        }
        else if ( checkWinner( game->spaces, game->computer ) )
        {
            game->status = TicTacToeGameStatusMinimaxOWon;
        }
        else if ( checkTie( game->spaces ) )
        {
            game->status = TicTacToeGameStatusTie;
        }
        else
        {
            game->status = TicTacToeGameStatusInProgress;
        }
    }

    bool isGameOver( const TicTacToeGame *game )
    {
        return game->status != TicTacToeGameStatusInProgress;
    }
}

TicTacToeGame *ticTacToeCreateGame()
{
    seedRandom();

    TicTacToeGame *game = new TicTacToeGame;
    ticTacToeResetGame( game, TicTacToeComputerTypeMinimax );

    return game;
}

void ticTacToeDestroyGame( TicTacToeGame *game )
{
    delete game;
}

void ticTacToeResetGame( TicTacToeGame *game, int computerType )
{
    if ( game == NULL )
    {
        return;
    }

    game->spaces.fill( ' ' );
    game->player = 'X';
    game->computer = 'O';
    game->currentTurn = game->player;
    game->computerType = computerType;
    game->status = TicTacToeGameStatusInProgress;
}

int ticTacToePlayerMove( TicTacToeGame *game, int index )
{
    if ( game == NULL || isGameOver( game ) )
    {
        return 0;
    }

    if ( game->computerType == TicTacToeComputerTypeMinimaxVsMinimax )
    {
        return 0;
    }

    if ( index < 0 || index >= 9 || game->spaces[ index ] != ' ' )
    {
        return 0;
    }

    game->spaces[ index ] = game->player;
    game->currentTurn = game->computer;
    updateNormalStatus( game );

    if ( !isGameOver( game ) )
    {
        ticTacToeComputerMove( game );
    }

    return 1;
}

void ticTacToeComputerMove( TicTacToeGame *game )
{
    if ( game == NULL || isGameOver( game ) )
    {
        return;
    }

    if ( game->computerType == TicTacToeComputerTypeRandom )
    {
        randomMove( game->spaces, game->computer );
    }
    else
    {
        minimaxMove( game->spaces, game->player, game->computer );
    }

    game->currentTurn = game->player;
    updateNormalStatus( game );
}

void ticTacToeStepMinimaxVsMinimax( TicTacToeGame *game )
{
    if ( game == NULL || isGameOver( game ) )
    {
        return;
    }

    if ( game->computerType != TicTacToeComputerTypeMinimaxVsMinimax )
    {
        return;
    }

    if ( game->currentTurn == game->player )
    {
        minimaxMove( game->spaces, game->computer, game->player );
        game->currentTurn = game->computer;
    }
    else
    {
        minimaxMove( game->spaces, game->player, game->computer );
        game->currentTurn = game->player;
    }

    updateMinimaxVsMinimaxStatus( game );
}

char ticTacToeCellAt( const TicTacToeGame *game, int index )
{
    if ( game == NULL || index < 0 || index >= 9 )
    {
        return ' ';
    }

    return game->spaces[ index ];
}

int ticTacToeStatus( const TicTacToeGame *game )
{
    if ( game == NULL )
    {
        return TicTacToeGameStatusInProgress;
    }

    return game->status;
}

int ticTacToeCurrentTurn( const TicTacToeGame *game )
{
    if ( game == NULL )
    {
        return 'X';
    }

    return game->currentTurn;
}

int ticTacToeComputerType( const TicTacToeGame *game )
{
    if ( game == NULL )
    {
        return TicTacToeComputerTypeMinimax;
    }

    return game->computerType;
}
