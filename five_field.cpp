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

void five_field::swap(int& first_pos, int& second_pos)
{
    int tmp = first_pos;
    first_pos = second_pos;
    second_pos = tmp;
}

int five_field::max(int left_num, int right_num) 
{ 
    return (left_num > right_num)? left_num : right_num; 
}

int five_field::min(int left_num, int right_num) 
{ 
    return (left_num > right_num)?  right_num : left_num; 
}

bool five_field::is_move_player(int num_checker, Checker_pos& first_pos, Checker_pos& second_pos)
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
                do_move(IS_USER, num_checker-1, first_pos, second_pos);
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

                do_move(IS_USER, num_checker-1, first_pos, second_pos);
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

                do_move(IS_USER, num_checker-1, first_pos, second_pos);
                return true;
            }

            break;
    }
}

Checker_pos five_field::define_down_pos(Checker_pos position, bool is_type_player)
{
    int offset = 1;
    const int type_player = is_type_player? COMPUTER : USER;

    if ( is_check_borders(position.y + offset, position.x) && 
       ( map[position.y + offset][position.x] == type_player ||
         map[position.y + offset][position.x] == EMPTY) )
    {
        int place = map[position.y + offset][position.x];

        if (place == type_player)
        {
            for (offset++; is_check_borders(position.y + offset, position.x) && 
                            map[position.y + offset][position.x] == type_player; 
                    offset++);
            
            
            if ( is_check_borders(position.y + offset, position.x) && 
                    map[position.y + offset][position.x] == EMPTY )
                position.y += offset;
        }                
        else if (place == EMPTY)
            position.y += offset;
    }

    return position;
}

Checker_pos five_field::define_up_pos(Checker_pos position, bool is_type_player)
{
    int offset = 1;
    const int type_player = is_type_player? COMPUTER : USER;

    if ( is_check_borders(position.y-offset, position.x) && 
       ( map[position.y - offset][position.x] == type_player ||
         map[position.y - offset][position.x] == EMPTY)  )
    {
        int place = map[position.y - offset][position.x];
        
        if (place == type_player)
        {
            for (offset--; is_check_borders(position.y-offset, position.x) && 
                            map[position.y - offset][position.x] == type_player; 
                offset--);
            
            if ( is_check_borders(position.y-offset, position.x) && 
                 map[position.y - offset][position.x] == EMPTY)
                position.y -= offset;
        }
        else if (place == EMPTY)
            position.y -= offset;
    }

    return position;
}

Checker_pos five_field::define_right_pos(Checker_pos position, bool is_type_player)
{
    int offset = 1;
    const int type_player = is_type_player? COMPUTER : USER;

    if ( is_check_borders(position.y, position.x + offset) && 
       ( map[position.y][position.x + offset] == type_player ||
         map[position.y][position.x + offset] == EMPTY) )
    {
        int place = map[position.y][position.x + offset];

        if (place == type_player)
        {
            for (offset++; is_check_borders(position.y, position.x + offset) && 
                            map[position.y][position.x + offset] == type_player; 
                offset++);

            if ( is_check_borders(position.y, position.x + offset) && 
                    map[position.y][position.x + offset] == EMPTY)
                position.x += offset;
        }
        else if (place == EMPTY)
            position.x += offset;
    }

    return position;
}

Checker_pos five_field::define_left_pos(Checker_pos position, bool is_type_player)
{
    int offset = 1;
    const int type_player = is_type_player? COMPUTER : USER;

    if ( is_check_borders(position.y, position.x - offset) && 
       ( map[position.y][position.x - offset] == type_player ||
         map[position.y][position.x - offset] == EMPTY) )
    {
        int place = map[position.y][position.x - offset];

        if (place == type_player)
        {
            for (offset--; is_check_borders(position.y, position.x - offset) && 
                            map[position.y][position.x - offset] == type_player; 
                offset--);
            

            if ( is_check_borders(position.y, position.x - offset) && 
                    map[position.y][position.x - offset] == EMPTY)
                position.x -= offset;
        }                
        else if (place == EMPTY)
            position.x -= offset;
    }

    return position;
}

bool five_field::is_can_move(Checker_pos& first_pos, Checker_pos& second_pos)
{
    return (first_pos.x != second_pos.x || first_pos.y != second_pos.y);
}

void five_field::do_move(bool is_type_player, int i_checker, Checker_pos& first_pos, Checker_pos& second_pos)
{ 
    if (is_type_player == IS_COMPUTER)
    {
        map[second_pos.y][second_pos.x] = COMPUTER;
        coor_computer[COOR_Y][i_checker] = second_pos.y;
        coor_computer[COOR_X][i_checker] = second_pos.x;
    }
    else if (is_type_player == IS_USER)
    {
        map[second_pos.y][second_pos.x] = USER;
        coor_player[COOR_Y][i_checker] = second_pos.y;
        coor_player[COOR_X][i_checker] = second_pos.x;
    }

    map[first_pos.y][first_pos.x] = EMPTY;
}

int five_field::get_user_Heur_Eval(INT_VECTOR_2D& coor_white_player)
{
    int eval = 0;

    //ход
    Checker_pos first_pos;
    Checker_pos second_pos;

    for (int i_checker = 0; i_checker < NUM_CHECKER; i_checker++)
    {
        first_pos.y = coor_player[COOR_Y][i_checker];
        first_pos.x = coor_player[COOR_X][i_checker];

        //вниз
        second_pos = define_down_pos(first_pos, IS_USER); 
        if (is_can_move(first_pos, second_pos))
        {
            eval += WHITE_PRICE_MOVE_DOWN;
        }
        
        //вправо
        second_pos = define_right_pos(first_pos, IS_USER);
        if (is_can_move(first_pos, second_pos))
        {
            eval += WHITE_PRICE_MOVE_RIGHT;
        }
        
        //влево
        second_pos = define_left_pos(first_pos, IS_USER);
        if (is_can_move(first_pos, second_pos))
        {
            eval += WHITE_PRICE_MOVE_LEFT;
        }
    }

    return eval;
}

int five_field::get_computer_heur_eval(INT_VECTOR_2D& coor_black_player)
{
    int eval = 0;

    //ход
    Checker_pos first_pos;
    Checker_pos second_pos;

    for (int i_checker = 0; i_checker < NUM_CHECKER; i_checker++)
    {
        first_pos.y = coor_computer[COOR_Y][i_checker];
        first_pos.x = coor_computer[COOR_X][i_checker];

        //вправо
        second_pos = define_right_pos(first_pos, IS_COMPUTER);
        if (is_can_move(first_pos, second_pos))
        {
            eval += BLACK_PRICE_MOVE_RIGHT;
        }

        //вниз
        second_pos = define_down_pos(first_pos, IS_COMPUTER); 
        if (is_can_move(first_pos, second_pos))
        {
            eval += BLACK_PRICE_MOVE_DOWN;
        }
        
        //вверх
        second_pos = define_up_pos(first_pos, IS_COMPUTER);
        if (is_can_move(first_pos, second_pos))
        {
            eval += BLACK_PRICE_MOVE_UP;
        }
    }
    
    return eval;
}

int five_field::getHeuristicEvaluation()
{
    int eval_user = get_user_Heur_Eval(coor_player);
    int eval_computer = get_computer_heur_eval(coor_computer);
    return  eval_computer - eval_user;
} 

int five_field::run_minimax(bool is_type_moster, int depth)
{
    int test = NOT_INITIALIZE;

    if ( depth == MAX_DEPTH )
        return getHeuristicEvaluation();

    Move_PC best_move(NOT_INITIALIZE);
    int MinMax = IS_COMPUTER? MIN_VALUE : MAX_VALUE;

    //выбираем ход который нам выгодней
    if (is_type_moster)
    {
        //-------------------------------------
        Checker_pos first_pos;
        Checker_pos second_pos;

        for (int i_checker = 0; i_checker < NUM_CHECKER; i_checker++)
        {
            first_pos.y = coor_computer[COOR_Y][i_checker];
            first_pos.x = coor_computer[COOR_X][i_checker];
            
            //вправо
            second_pos = define_right_pos(first_pos, IS_COMPUTER);
            if (is_can_move(first_pos, second_pos))
            {
                //хожу
                do_move(IS_COMPUTER, i_checker, first_pos, second_pos);
                
                //считаю
                test = run_minimax(MAX, depth+1);
                
                if ( test > MinMax )
                {
                    best_move.checker = first_pos;
                    best_move.move_checker = second_pos;
                    best_move.ind_checker = i_checker;

                    MinMax = test;
                }
                
                //  отменяй ход
                do_move(IS_COMPUTER, i_checker, second_pos, first_pos);
            }

            //вниз
            second_pos = define_down_pos(first_pos, IS_COMPUTER);
            if (is_can_move(first_pos, second_pos))
            {
                //хожу
                do_move(IS_COMPUTER, i_checker, first_pos, second_pos);
                
                //считаю
                test = run_minimax(MAX, depth+1);
                
                if ( test > MinMax )
                {
                    best_move.checker = first_pos;
                    best_move.move_checker = second_pos;
                    best_move.ind_checker = i_checker;
                    
                    MinMax = test;
                }
                
                //  отменяй ход
                do_move(IS_COMPUTER, i_checker, second_pos, first_pos);
            }

            //вверх
            second_pos = define_up_pos(first_pos, IS_COMPUTER);
            if (is_can_move(first_pos, second_pos))
            {
                //хожу
                do_move(IS_COMPUTER, i_checker, first_pos, second_pos);
                
                //считаю
                test = run_minimax(MAX, depth+1);
                
                if ( test > MinMax )
                {
                    best_move.checker = first_pos;
                    best_move.move_checker = second_pos;
                    best_move.ind_checker = i_checker;
                    
                    MinMax = test;
                }
                
                //  отменяй ход
                do_move(IS_COMPUTER, i_checker, second_pos, first_pos);
            }
        }
        //------------------------
    }
    //противник выбираем ход, который нам не выгоден нам
    else
    {
        //ход
        Checker_pos first_pos;
        Checker_pos second_pos;

        for (int i_checker = 0; i_checker < NUM_CHECKER; i_checker++)
        {
            first_pos.y = coor_player[COOR_Y][i_checker];
            first_pos.x = coor_player[COOR_X][i_checker];

            //вниз
            second_pos = define_down_pos(first_pos, IS_USER); //ошибка определения позиции
            if (is_can_move(first_pos, second_pos))
            {
                //хожу
                do_move(IS_USER, i_checker, first_pos, second_pos);
                
                //считаю
                test = run_minimax(MIN, depth+1);
                
                if ( test < MinMax )
                {
                    best_move.checker = first_pos;
                    best_move.move_checker = second_pos;
                    best_move.ind_checker = i_checker;
                    
                    MinMax = test;
                }
                
                //  отменяй ход
                do_move(IS_USER, i_checker, second_pos, first_pos);
            }
            
            //вправо
            second_pos = define_right_pos(first_pos, IS_USER);
            if (is_can_move(first_pos, second_pos))
            {
                //хожу
                do_move(IS_USER, i_checker, first_pos, second_pos);
                
                //считаю
                test = run_minimax(MIN, depth+1);
                
                if ( test < MinMax )
                {
                    best_move.checker = first_pos;
                    best_move.move_checker = second_pos;
                    best_move.ind_checker = i_checker;
                    
                    MinMax = test;
                }
                
                //  отменяй ход
                do_move(IS_USER, i_checker, second_pos, first_pos);
            }
            
            //влево
            second_pos = define_left_pos(first_pos, IS_USER);
            if (is_can_move(first_pos, second_pos))
            {
                //хожу
                do_move(IS_USER, i_checker, first_pos, second_pos);
                
                //считаю
                test = run_minimax(MIN, depth+1);
                
                if ( test < MinMax )
                {
                    best_move.checker = first_pos;
                    best_move.move_checker = second_pos;
                    best_move.ind_checker = i_checker;
                    
                    MinMax = test;
                }
                
                //  отменяй ход
                do_move(IS_USER, i_checker, second_pos, first_pos);
            }
            
        }
    }

    if ( best_move.checker.x == NOT_INITIALIZE ||
         best_move.checker.y == NOT_INITIALIZE ||
         best_move.move_checker.x == NOT_INITIALIZE ||
         best_move.move_checker.y == NOT_INITIALIZE)
        return getHeuristicEvaluation();

    //если нашли лучший ход, то ходим
    if ( depth == 0 && 
         best_move.checker.x != NOT_INITIALIZE &&
         best_move.checker.y != NOT_INITIALIZE &&
         best_move.move_checker.x != NOT_INITIALIZE &&
         best_move.move_checker.y != NOT_INITIALIZE)
    {
        //ходим 
        do_move(is_type_moster, best_move.ind_checker, best_move.checker, best_move.move_checker);
    }

    return MinMax;
}

//**************************************public*********************************************
five_field::five_field(int _SIZE_MAP) : SIZE_MAP(_SIZE_MAP), 
                                        SIZE_PETAL(SIZE_MAP / 3),
                                        NUM_CHECKER(SIZE_PETAL * SIZE_PETAL), 
                                        map(SIZE_MAP, vector<int>(SIZE_MAP)),
                                        coor_player(2),
                                        coor_computer(2),
                                        best_score(NOT_INITIALIZE)
{ 
    set_units();
    set_empty_place(); 
}

bool five_field::is_win_user()
{
    for (int y = 2*SIZE_PETAL; y < 3*SIZE_PETAL; ++y)
    {
        for (int x = SIZE_PETAL; x < 2*SIZE_PETAL; ++x)
        {
            if (map[y][x] != USER) 
                return false;
        }
    }

    return true; 
}

bool five_field::is_win_computer()
{
    for (int y = SIZE_PETAL; y < 2*SIZE_PETAL; ++y)
    {
        for (int x = 2*SIZE_PETAL; x < 3*SIZE_PETAL; ++x)
        {
            if (map[y][x] != COMPUTER) 
                return false;
        }
    }

    return true;
}

int five_field::find_num_check(Checker_pos& first_pos)
{
    int num_checker;

    for (int i = 0; i < NUM_CHECKER; i++)
    {
        if (coor_player[COOR_X][i] == first_pos.x && 
            coor_player[COOR_Y][i] == first_pos.y)
            num_checker = i+1; 
    }

    return num_checker;
}

void five_field::move_player()
//ход игрока
{
    
    Checker_pos first_pos; 
    int num_cheker;
    Checker_pos second_pos;

    while (true)
    {
        cout << "Input current place: ";
        cin >> first_pos.y >> first_pos.x;
        
        num_cheker = find_num_check(first_pos);
        
        cout << "Input will place: ";
        cin >> second_pos.y >> second_pos.x;
        

        if (is_move_player(num_cheker, first_pos, second_pos)) 
            break;
        else 
            cout << "Try again!" << endl; 
    }
}

void five_field::move_computer()
{
    run_minimax(IS_COMPUTER, 0);
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