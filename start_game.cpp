#include "start_game.h"

void run(int size)
{
    //создаем карту с параметрами: размер карты
    five_field game(size);
    cout << "Game begin" << endl;
    game.show();
    
    //ПОКА не выйграл игрок или компьютер
    while ( true )
    {
        //ходит компьютер
        game.move_computer();
        game.show();
        if ( game.is_win_computer() ) break;
        
        game.move_player();
        game.show();
        if ( game.is_win_user() ) break;
    }

    if ( game.is_win_user() )
        cout << endl << "Win user!" << endl;
    else 
        cout << endl << "Win computer!" << endl;

}

char input_be_game()
{
    char value;
    cout << "Want to get out? press y/n: ";
    cin >> value;

    if ( (value != 'y' && value != 'n') || cin.peek() != '\n' )
        throw std::invalid_argument("error input!");
    
    return value;
}

int input_size()
{
    int value;
    cout << "Input size map(size: 6, 9, 12) = ";
    cin >> value;

    if ( value % 3 != 0 || value <= 0 || cin.peek() != '\n' )
        throw std::invalid_argument("error input!");

    return value;
}