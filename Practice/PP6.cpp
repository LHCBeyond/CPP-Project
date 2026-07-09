#include <iostream>

void bubbleSort( int arr[], int size );
void bubbleSort( std::vector< int >& num );

int main()
{
    /*int arr[] = { 10, 2, 5, 6, 8, 9, 7, 1, 3, 4 };
    int size = sizeof( arr ) / sizeof( arr[ 0 ] );*/

    std::vector< int > num = { 10, 2, 5, 6, 8, 9, 7, 1, 3, 4 };

    for ( int i : num )
    {
        std::cout << i << " ";
    }
    std::cout << '\n';

    //bubbleSort( arr, size );
    bubbleSort( num );

    for ( int i : num )
    {
        std::cout << i << " ";
    }
}

void bubbleSort( int arr[], int size )
{
    int temp;
    for ( int i = 0; i < size - 1; i++ )
    {
        for ( int j = 0; j < size - i - 1; j++ )
        {
            if ( arr[ j ] > arr[ j + 1 ] )
            {
                temp = arr[ j ];
                arr[ j ] = arr[ j + 1 ];
                arr[ j + 1 ] = temp;
            }
        }
    }
}

void bubbleSort( std::vector< int >& num ) 
{
    int temp;
    for ( int i = 0; i < num.size() - 1; i++ )
    {
        for ( int j = 0; j < num.size() - i - 1; j++ )
        {
            if ( num[ j ] > num[ j + 1 ] )
            {
                std::swap( num[ j ], num[ j + 1 ] );
            }
        }
    }
}