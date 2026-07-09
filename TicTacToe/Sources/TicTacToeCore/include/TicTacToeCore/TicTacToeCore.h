#ifndef TICTACTOE_CORE_H
#define TICTACTOE_CORE_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum TicTacToeComputerType
{
    TicTacToeComputerTypeRandom = 1,
    TicTacToeComputerTypeMinimax = 2,
    TicTacToeComputerTypeMinimaxVsMinimax = 3
} TicTacToeComputerType;

typedef enum TicTacToeGameStatus
{
    TicTacToeGameStatusInProgress = 0,
    TicTacToeGameStatusPlayerWon = 1,
    TicTacToeGameStatusComputerWon = 2,
    TicTacToeGameStatusTie = 3,
    TicTacToeGameStatusMinimaxXWon = 4,
    TicTacToeGameStatusMinimaxOWon = 5
} TicTacToeGameStatus;

typedef struct TicTacToeGame TicTacToeGame;

TicTacToeGame *ticTacToeCreateGame();
void ticTacToeDestroyGame( TicTacToeGame *game );
void ticTacToeResetGame( TicTacToeGame *game, int computerType );
int ticTacToePlayerMove( TicTacToeGame *game, int index );
void ticTacToeComputerMove( TicTacToeGame *game );
void ticTacToeStepMinimaxVsMinimax( TicTacToeGame *game );
char ticTacToeCellAt( const TicTacToeGame *game, int index );
int ticTacToeStatus( const TicTacToeGame *game );
int ticTacToeCurrentTurn( const TicTacToeGame *game );
int ticTacToeComputerType( const TicTacToeGame *game );

#ifdef __cplusplus
}
#endif

#endif
