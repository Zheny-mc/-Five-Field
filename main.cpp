#include "five_field.h"

#define SIZE 3*1
/*
int main()
{
    //создаем карту с параметрами: размер карты
    five_field game(SIZE);
    cout << "Game begin" << endl;
    game.show();
    

    //ПОКА не выйграл игрок или компьютер
    while ( true )
    {
        game.move_player();
        game.show();
        if ( game.is_win_user() ) break;
        
        //ходит компьютер
        //**game.move_computer();
        //if ( game.is_win_computer() ) break;
        //game.show();
    }

    if ( game.is_win_user() )
        cout << endl << "Win user!" << endl;
    else 
        cout << endl << "Win computer!" << endl;
 
    return 0;
}
*/

int main()
{
    //создаем карту с параметрами: размер карты
    five_field game(SIZE);
    
    return 0;
}

