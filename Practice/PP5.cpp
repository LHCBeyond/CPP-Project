#include <iostream>
#include <ctime>

using std::cout;
using std::cin;

char getUserChoice();
char getComputerChoice();
void showChoice( char choice );
void chooseWinner( char player, char computer );

int main()
{
    char player;
    char computer;

    player = getUserChoice();
    cout << "Your choice: ";
    showChoice( player );

    computer = getComputerChoice();
    cout << "Computer's choice: ";
    showChoice( computer );

    chooseWinner( player, computer );
}

char getUserChoice()
{
    char player;
    cout << "Rock Paper Scissor Game";
    do
    {
        cout << "pick a choice:\n";
        cout << "'r' for rock\n";
        cout << "'p' for paper\n";
        cout << "'s' for scissor\n";
        cin >> player;
    } while ( player != 'r' && player != 's' && player != 'p' );

    return player;
}

char getComputerChoice()
{
    char computer;

    srand( time( NULL ) );
    int num = rand() % 3 + 1;

    switch ( num )
    {
        case 1: return 'r';
        case 2: return 'p';
        case 3: return 's';
    }
    return computer;
}

void showChoice( char choice )
{
    switch ( choice )
    {
        case 'r': cout << "rock\n";
                break;
        case 'p': cout << "paper\n";
                break;
        case 's': cout << "scissor\n";
                break; 
    }
}

void chooseWinner( char player, char computer )
{
    switch ( player )
    {
        case 'r':   if ( computer == 'r' )
                    {
                        cout << "It's a tie!\n";
                    }
                    else if ( computer == 'p' )
                    {
                        cout << "You lose!\n";
                    }
                    else
                    {
                        cout << "You win!\n";
                    }
                    break;
        case 'p':   if ( computer == 'p' )
                    {
                        cout << "It's a tie!\n";
                    }
                    else if ( computer == 's' )
                    {
                        cout << "You lose!\n";
                    }
                    else
                    {
                        cout << "You win!\n";
                    }
                    break;
        case 's':   if ( computer == 's' )
                    {
                        cout << "It's a tie!\n";
                    }
                    else if ( computer == 'r' )
                    {
                        cout << "You lose!\n";
                    }
                    else
                    {
                        cout << "You win!\n";
                    }
                    break;
    }
}