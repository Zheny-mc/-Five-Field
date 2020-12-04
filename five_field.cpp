#include "five_field.h"

//**************************************private****************************************
void five_field::set_units()
{
    //инициализация белых шашек
    for (int y = 0; y < SIZE_PETAL; ++y)//по строчно
    {
        for (int x = SIZE_PETAL; x < 2*SIZE_PETAL; ++x) //по столбцам
        {
            //заполняю поле белой шашкой
            map[y][x] = USER;
            //добавляю координаты белых шашек
            coor_player[COOR_Y].push_back(y);
            coor_player[COOR_X].push_back(x);
        }
    }

    //инициализация черных шашек
    for (int y = SIZE_PETAL; y < 2*SIZE_PETAL; ++y)//по строчно
    {
        for (int x = 0; x < SIZE_PETAL; ++x) //по столбцам
        {
            //заполняю поле черной шашкой
            map[y][x] = COMPUTER;
            //добавляю координаты черной шашки
            coor_computer[COOR_Y].push_back(y);
            coor_computer[COOR_X].push_back(x);
        }
    }
}

void five_field::set_empty_place()
{
    for (int y = SIZE_PETAL; y < 2*SIZE_PETAL; ++y) //построчно
    {
        for (int x = SIZE_PETAL; x < 3*SIZE_PETAL; ++x) //по столбцам
        {
            map[y][x] = EMPTY;
        }
    }

    for (int y = 2*SIZE_PETAL; y < 3*SIZE_PETAL; ++y) //построчно
    {
        for (int x = SIZE_PETAL; x < 2*SIZE_PETAL; ++x) //по столбцам
        {
            map[y][x] = EMPTY;
        }
    }
}

bool five_field::is_win_user(INT_VECTOR_2D& field)
{
    for (int y = 2*SIZE_PETAL; y < 3*SIZE_PETAL; ++y)
    {
        for (int x = SIZE_PETAL; x < 2*SIZE_PETAL; ++x)
        {
            if (field[y][x] != USER) 
                return false;
        }
    }

    return true;    
}

bool five_field::is_win_computer(INT_VECTOR_2D& field)
{
    for (int y = SIZE_PETAL; y < 2*SIZE_PETAL; ++y)
    {
        for (int x = 2*SIZE_PETAL; x < 3*SIZE_PETAL; ++x)
        {
            if (field[y][x] != COMPUTER) 
                return false;
        }
    }

    return true;   
}

bool five_field::is_check_borders(int y_i, int x_i)
{
        //преведение индексов к номерам
    int x = x_i + 1; 
    int y = y_i + 1;

    if ((x > SIZE_PETAL && x <= 2*SIZE_PETAL) && (y > 0 && y <= SIZE_PETAL))
        return true;
    else if ((x > 0 && x <= 3*SIZE_PETAL) && (y > SIZE_PETAL && y <= 2*SIZE_PETAL))
        return true;
    else if ((x > SIZE_PETAL && x <= 2*SIZE_PETAL) && (y > 2*SIZE_PETAL && y <= 3*SIZE_PETAL))
        return true;
    else
        return false;
}

bool five_field::is_move_player(checker_pos& first_pos, checker_pos& second_pos)
{
    if ( ! (is_check_borders(first_pos.y, first_pos.x) && 
            is_check_borders(second_pos.y, second_pos.x)) )
    {
        cout << "going out of the field" << endl;
        return false;   
    }

    if ( map[first_pos.y][first_pos.x] != USER)
    {
        cout << "current Checker computer" << endl;
        return false;
    }

    switch ( map[second_pos.y][second_pos.x] )
    {
        case USER:
            cout << "you can't turn on your checker" << endl;
            return false;   

        case COMPUTER:
            cout << "you can't turn on Stranger checker" << endl;
            return false;   
        
        case RELATED:
            cout << "Error" << endl;
            return false;   

        case EMPTY:
            if ( first_pos.x == second_pos.x && (abs(second_pos.y - first_pos.y) == 1) ||
                 first_pos.y == second_pos.y && (abs(second_pos.x - first_pos.x) == 1) )
            {
                swap(map[second_pos.y][second_pos.x], map[first_pos.y][first_pos.x]);
                return true;
            }

            if (first_pos.x == second_pos.x)
            {
                //вперед 
                if (second_pos.y > first_pos.y)
                {
                    for (int i = first_pos.y+1; i < second_pos.y; i++)
                    {
                        if ( map[i][first_pos.x] != USER)
                            return false;
                    }
                }
                //назад
                else
                {
                    for (int i = second_pos.y-1; i > first_pos.y+1; i--)
                    {
                        if ( map[i][first_pos.x] != USER)
                            return false;
                    }
                }

                swap(map[second_pos.y][second_pos.x], map[first_pos.y][first_pos.x]);
                return true;
            }
            else if (first_pos.y == second_pos.y)
            {
                //вправо
                if (second_pos.x > first_pos.x)
                {
                    for (int i = first_pos.x+1; i < second_pos.x; i++)
                    {
                        if ( map[first_pos.y][i] != USER)
                            return false;
                    }
                }
                //влево
                else
                {
                    for (int i = second_pos.x-1; i > first_pos.x+1; i--)
                    {
                        if ( map[first_pos.y][i] != USER)
                            return false;
                    }
                }

                swap(map[second_pos.y][second_pos.x], map[first_pos.y][first_pos.x]);
                return true;
            }

            break;
    }
}

//**************************************public*********************************************
five_field::five_field(int _SIZE_MAP) : SIZE_MAP(_SIZE_MAP), 
                                        SIZE_PETAL(SIZE_MAP / 3), 
                                        map(SIZE_MAP, vector<int>(SIZE_MAP)),
                                        coor_player(2),
                                        coor_computer(2)
{ 
    set_units();
    set_empty_place(); 
}



bool five_field::is_win_user()
{
    return is_win_user(map);
}

bool five_field::is_win_computer()
{
    return is_win_computer(map);
}

void five_field::swap(int& first_pos, int& second_pos)
{
    int tmp = first_pos;
    first_pos = second_pos;
    second_pos = tmp;
}

void five_field::move_player()
//ход игрока
{
    checker_pos first_pos; 
    checker_pos second_pos;
    
    while (true)
    {
        cout << "Input current place: ";
        cin >> first_pos.y >> first_pos.x;
        cout << "Input will place: ";
        cin >> second_pos.y >> second_pos.x;

        if (is_move_player(first_pos, second_pos)) 
            break;
        else 
            cout << "Try again!" << endl; 
    }
}

void five_field::show()
{
    //вывод букв столбцов
    cout << "  ";
    for (int i = 0; i < SIZE_MAP; ++i)
        cout << setw(2) << i << ' ';
    cout << endl;

    for (int y = 0; y < SIZE_MAP; ++y)
    {
        cout << setw(2) << y; //вывод номера строк

        for (auto x: map[y])
        {
            if (x == COMPUTER)
                cout << setw(2) << 'c';
            else if (x == USER)
                cout << setw(2) << 'u';
            else if (x == EMPTY)
                cout << setw(2) << '_';
            else if (x == RELATED)
                cout << setw(2) << ' ';
            
            cout << ' ';
        }
        cout << endl;
    }
}