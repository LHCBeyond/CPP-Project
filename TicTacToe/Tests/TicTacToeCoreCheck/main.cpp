#include "TicTacToeCore/TicTacToeCore.h"

#include <cassert>
#include <iostream>

void testPlayerMovePlacesXAndComputerResponds()
{
    TicTacToeGame *game = ticTacToeCreateGame();
    ticTacToeResetGame( game, TicTacToeComputerTypeMinimax );

    assert( ticTacToePlayerMove( game, 0 ) == 1 );
    assert( ticTacToeCellAt( game, 0 ) == 'X' );

    int computerMoves = 0;

    for ( int i = 0; i < 9; i++ )
    {
        if ( ticTacToeCellAt( game, i ) == 'O' )
        {
            computerMoves++;
        }
    }

    assert( computerMoves == 1 );
    ticTacToeDestroyGame( game );
}

void testOccupiedCellCannotBeOverwritten()
{
    TicTacToeGame *game = ticTacToeCreateGame();
    ticTacToeResetGame( game, TicTacToeComputerTypeRandom );

    assert( ticTacToePlayerMove( game, 0 ) == 1 );
    assert( ticTacToePlayerMove( game, 0 ) == 0 );
    assert( ticTacToeCellAt( game, 0 ) == 'X' );

    ticTacToeDestroyGame( game );
}

void testMinimaxVsMinimaxEndsInTie()
{
    TicTacToeGame *game = ticTacToeCreateGame();
    ticTacToeResetGame( game, TicTacToeComputerTypeMinimaxVsMinimax );

    for ( int i = 0; i < 9; i++ )
    {
        if ( ticTacToeStatus( game ) != TicTacToeGameStatusInProgress )
        {
            break;
        }

        ticTacToeStepMinimaxVsMinimax( game );
    }

    assert( ticTacToeStatus( game ) == TicTacToeGameStatusTie );
    ticTacToeDestroyGame( game );
}

int main()
{
    testPlayerMovePlacesXAndComputerResponds();
    testOccupiedCellCannotBeOverwritten();
    testMinimaxVsMinimaxEndsInTie();

    std::cout << "TicTacToeCoreCheck passed.\n";
    return 0;
}
