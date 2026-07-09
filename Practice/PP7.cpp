#include <iostream>

int getDigit( const int number );
int sumOddDigits( const std::string cardNumber );
int sumEvenDigits( const std::string cardNumber );

int main()
{
    std::string cardNumber;
    int result = 0;

    std::cout << "Enter a credit card number: ";
    std::cin >> cardNumber;

    result = sumOddDigits( cardNumber ) + sumEvenDigits( cardNumber );
    if ( result % 10 == 0 )
    {
        std::cout << "This is a valid credit card number";
    }
    else 
    {
        std::cout << "This is not a valid credit card number";
    }

}

int getDigit( const int number )
{
    return number % 10 + ( number / 10 % 10 );
}

int sumOddDigits( const std::string cardNumber )
{
    int sum = 0;
    for ( int i = cardNumber.size() - 1; i >= 0; i -= 2 )
    {
        sum += cardNumber[ i ] - 48;
    }
    return sum;
}

int sumEvenDigits( const std::string cardNumber )
{
    int sum = 0;
    for ( int i = cardNumber.size() - 2; i >= 0; i -= 2 )
    {
        sum += getDigit(( cardNumber[ i ] - 48 ) * 2 );
    }
    return sum;
}
