#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

#define VECTOR_2D vector<vector<int>>

#define WHITE_PRICE_MOVE_DOWN  4
#define WHITE_PRICE_MOVE_LEFT  2
#define WHITE_PRICE_MOVE_RIGHT 3

#define BLACK_PRICE_MOVE_DOWN  3
#define BLACK_PRICE_MOVE_UP    2
#define BLACK_PRICE_MOVE_RIGHT 4

#define Y 0
#define X 1

#define EMPTY -1
#define USER 1
#define COMPUTER 2
#define RELATED 0


int SIZE_PETAL = 2;

VECTOR_2D coor_player = {{0, 2}, {0, 3}, {1, 2}, {1, 3}};
VECTOR_2D coor_computer = {{2, 0}, {2, 1}, {3, 0}, {3, 1}};
VECTOR_2D map =
{
    {'*', '*',  1,  1, '*', '*'},
    {'*', '*',  1,  1, '*', '*'},
    { 2,   2,  -1, -1, -1,  -1 },
    { 2,   2,  -1, -1, -1,  -1 },
    {'*', '*', -1, -1, '*', '*'},
    {'*', '*', -1, -1, '*', '*'}
};


bool is_check_borders(int y_i, int x_i)
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


int get_user_Heur_Eval(VECTOR_2D& coor_white_player)
{
    int eval = 0;

    for (int i = 0; i < coor_white_player.size(); ++i)
    {
        //Если позиция находиться в карте и там нет черной шашки
        //(Down)
        if ( is_check_borders(coor_white_player[i][Y] + 1, coor_white_player[i][X]) && 
             map[ coor_white_player[i][Y] + 1][ coor_white_player[i][X] ] != COMPUTER )
        {
            int offset = 1; //смещение шашки по шашкам
            if ( map[ coor_white_player[i][Y]+offset ][ coor_white_player[i][X] ] == USER )
            {
                for (offset++; is_check_borders(coor_white_player[i][Y]+offset, coor_white_player[i][X]) && 
                             map[ coor_white_player[i][Y]+offset ][ coor_white_player[i][X] ] == USER; 
                offset++);
            }

            if ( is_check_borders(coor_white_player[i][Y]+offset, coor_white_player[i][X]) && 
                 map[ coor_white_player[i][Y]+offset ][ coor_white_player[i][X] ] == EMPTY )
                eval += WHITE_PRICE_MOVE_DOWN;
        }

        //(RIGHT)
        if ( is_check_borders(coor_white_player[i][Y], coor_white_player[i][X] + 1) && 
             map[ coor_white_player[i][Y]][ coor_white_player[i][X] + 1 ] != COMPUTER )
        {
            int offset = 1; //смещение шашки по шашкам
            
            if ( map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == USER )
            {
                for (offset++; is_check_borders(coor_white_player[i][Y], coor_white_player[i][X]+offset) &&
                                map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == USER; 
                    offset++);
            }

            if ( is_check_borders(coor_white_player[i][Y], coor_white_player[i][X]+offset) && 
                 map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == EMPTY)
                eval += WHITE_PRICE_MOVE_RIGHT;
        }

        //(LEFT)
        if ( is_check_borders(coor_white_player[i][Y], coor_white_player[i][X] - 1) && 
             map[ coor_white_player[i][Y]][ coor_white_player[i][X] - 1 ] != COMPUTER )
        {
            int offset = -1; //смещение шашки по шашкам
            
            if ( map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == USER )
            {
                for (offset--; is_check_borders(coor_white_player[i][Y], coor_white_player[i][X]+offset) &&
                                map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == USER; 
                    offset--);
            }

            if ( is_check_borders(coor_white_player[i][Y], coor_white_player[i][X]+offset) && 
                 map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == EMPTY)
                eval += WHITE_PRICE_MOVE_LEFT;
        }
    }

    return eval;
}

int get_computer_heur_eval(VECTOR_2D& coor_black_player)
{
    int eval = 0;

    for (int i = 0; i < coor_black_player.size(); ++i)
    {
        //Если позиция находиться в карте и там нет черной шашки
        //(Down)
        if ( is_check_borders(coor_black_player[i][Y] + 1, coor_black_player[i][X]) && 
             map[ coor_black_player[i][Y] + 1][ coor_black_player[i][X] ] != USER)
        {
            int offset = 1; //смещение шашки по шашкам
            
            if ( map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == COMPUTER )
            {
                for (offset++; is_check_borders(coor_black_player[i][Y]+offset, coor_black_player[i][X]) && 
                                map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == COMPUTER; 
                    offset++);
            }

            if ( is_check_borders(coor_black_player[i][Y]+offset, coor_black_player[i][X]) && 
                 map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == EMPTY )
                eval += BLACK_PRICE_MOVE_DOWN;
        }
       
        //(UP)
        if ( is_check_borders(coor_black_player[i][Y]-1, coor_black_player[i][X]) && 
             map[ coor_black_player[i][Y] - 1 ][ coor_black_player[i][X] ] != USER)
        {
            int offset = -1; //смещение шашки по шашкам
            
            if ( map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == COMPUTER )
            {
                for (offset--; is_check_borders(coor_black_player[i][Y]+offset, coor_black_player[i][X]) && 
                                map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == COMPUTER;
                    offset--);
            }

            if ( is_check_borders(coor_black_player[i][Y]+offset, coor_black_player[i][X]) && 
                 map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == EMPTY)
                eval += BLACK_PRICE_MOVE_UP;
        }
      
        //(RIGHT)
        if ( is_check_borders(coor_black_player[i][Y], coor_black_player[i][X] + 1) && 
             map[ coor_black_player[i][Y] ][ coor_black_player[i][X] + 1 ] != USER)
        {
            int offset = 1; //смещение шашки по шашкам

            if ( map[ coor_black_player[i][Y] ][ coor_black_player[i][X]+offset ] == COMPUTER )
            {
                for (offset++; is_check_borders(coor_black_player[i][Y], coor_black_player[i][X]+offset) &&
                             map[ coor_black_player[i][Y] ][ coor_black_player[i][X]+offset ] == COMPUTER; 
                offset++);
            }

            if ( is_check_borders(coor_black_player[i][Y], coor_black_player[i][X]+offset) && 
                 map[ coor_black_player[i][Y] ][ coor_black_player[i][X]+offset ] == EMPTY )
                eval += BLACK_PRICE_MOVE_RIGHT;
        }
    }
    
    return eval;
}

int getHeuristicEvaluation()
{
    return get_user_Heur_Eval(coor_player) - get_computer_heur_eval(coor_computer);
}


int main()
{
    cout << getHeuristicEvaluation() << endl;

    return 0;
}