#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <cmath>
#include <string>

char Board[3][3];
const char plr = 'O';
const char computer = 'X';

typedef std::string string;
string Winner = " ";

void SetBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int x = 0; x < 3; x++)
        {
            Board[i][x] = ' ';
        }
    };
}

void PrintBoard()
{
    std::cout << "\x1B[2J\x1B[H";
    printf(" %c | %c | %c", Board[0][0], Board[0][1], Board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c", Board[1][0], Board[1][1], Board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c\n", Board[2][0], Board[2][1], Board[2][2]);
}

char ValidateWinner()
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (!(Board[i][0] == ' ') && Board[i][0] == Board[i][1] && Board[i][0] == Board[i][2])
        {
            return Board[i][0];
        }
    };
    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (!(Board[0][i] == ' ') && Board[0][i] == Board[1][i] && Board[0][i] == Board[2][i])
        {
            return Board[0][i];
        }
    };
    // Check diagonals
    for (int i = 0; i < 3; i++)
    {
        if (!(Board[0][0] == ' ') && Board[0][0] == Board[1][1] && Board[0][0] == Board[2][2])
        {
            return Board[0][0];
        }
        else if (!(Board[0][2] == ' ') && Board[0][2] == Board[1][1] && Board[0][2] == Board[2][0])
        {
            return Board[0][2];
        }
    };

    return ' ';
};

int AvailableSpaces()
{
    int Sum = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (Board[i][x] == ' ')
            {
                Sum++;
            }
        }
    }
    return Sum;
}

void ComputerMove()
{
    srand(time(0));
    int x = rand() % 3;
    int y = rand() % 3;

    if (AvailableSpaces() > 0)
    {
        if (Board[x][y] != ' ')
        {
            do
            {
                x = rand() % 3;
                y = rand() % 3;
            } while (Board[x][y] != ' ');
        }

        Board[x][y] = computer;
        return;
    }
}

void PlayerMove()
{
    char WinnerSymbol = ValidateWinner();

    if (WinnerSymbol == ' ' && AvailableSpaces() == 0)
    {
        Winner = "Tie";
    }
    else if (WinnerSymbol == plr)
    {
        Winner = "Player";
    }
    else if (WinnerSymbol == computer)
    {
        Winner = "Computer";
    }

    if (!(Winner == " "))
    {
        std::cout << "We have a winner: " << Winner << std::endl;
        std::cout << "Would you like to play again? (Type Y to play again)" << std::endl;
        string Input;
        std::cin >> Input;

        if (Input == "y" || Input == "Y")
        {
            SetBoard();
            PrintBoard();
        }
        else
        {
            std::cout << "Thanks for playing!" << std::endl;
            return;
        }
    }

    int x;
    int y;

    std::cout << "Enter a row (#1-3): " << std::endl;
    std::cin >> x;

    std::cout << "Enter a column (#1-3): " << std::endl;
    std::cin >> y;
    x--;
    y--;

    if (!(x > -1 && x < 2 && y > -1 && y < 2))
    {
        std::cout << "Error: Number(s) not found in defined scope range!" << std::endl;
        PlayerMove();
        return;
    }

    std::cout << x << std::endl;

    if (Board[x] && !(Board[x][y] != ' '))
    {
        Board[x][y] = plr;
        ComputerMove();
        PrintBoard();
    }
    else
    {
        std::cout << "Error: Illegal action!" << std::endl;
    }

    PlayerMove();
}

int main()
{
    SetBoard();
    PrintBoard();
    PlayerMove();
}
