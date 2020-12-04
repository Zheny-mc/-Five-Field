#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

#define VECTOR_2D vector<vector<int>>

#define WHITE_PRICE_MOVE_DOWN  4
#define WHITE_PRICE_MOVE_UP    1
#define WHITE_PRICE_MOVE_LEFT  2
#define WHITE_PRICE_MOVE_RIGHT 3

#define BLACK_PRICE_MOVE_DOWN  3
#define BLACK_PRICE_MOVE_UP    2
#define BLACK_PRICE_MOVE_LEFT  1
#define BLACK_PRICE_MOVE_RIGHT 4

#define Y 0
#define X 1

#define EMPTY_PLACE -1
#define WHITE_PLACE 1
#define BLACK_PLACE 2

int SIZE_PETAL = 2;

bool is_check_borders(int size_petal, int y_i, int x_i)
{
        //преведение индексов к номерам
    int x = x_i + 1; 
    int y = y_i + 1;

    if ((x > size_petal && x <= 2*size_petal) && (y > 0 && y <= size_petal))
        return true;
    else if ((x > 0 && x <= 3*size_petal) && (y > size_petal && y <= 2*size_petal))
        return true;
    else if ((x > size_petal && x <= 2*size_petal) && (y > 2*size_petal && y <= 3*size_petal))
        return true;
    else
        return false;
}

int getWhiteHeurEval(VECTOR_2D& map, VECTOR_2D& coor_white_player)
{
    int eval = 0;

    for (int i = 0; i < coor_white_player.size(); ++i)
    {
        //Если позиция находиться в карте и там нет черной шашки
        //(Down)
        if ( is_check_borders(SIZE_PETAL, coor_white_player[i][Y] + 1, coor_white_player[i][X]) && 
             map[ coor_white_player[i][Y] + 1][ coor_white_player[i][X] ] != BLACK_PLACE )
        {
            int offset = 1; //смещение шашки по шашкам
            if ( map[ coor_white_player[i][Y]+offset ][ coor_white_player[i][X] ] == WHITE_PLACE )
            {
                for (offset++; is_check_borders(SIZE_PETAL, coor_white_player[i][Y]+offset, coor_white_player[i][X]) && 
                             map[ coor_white_player[i][Y]+offset ][ coor_white_player[i][X] ] == WHITE_PLACE; 
                offset++);
            }
            cout << "[" << coor_white_player[i][Y] << " : " << coor_white_player[i][X] << "]" << " -> ";
            cout << coor_white_player[i][Y]+offset << " : " << coor_white_player[i][X] << " = ";
            cout << map[ coor_white_player[i][Y]+offset ][ coor_white_player[i][X] ]<< endl;

            if ( is_check_borders(SIZE_PETAL, coor_white_player[i][Y]+offset, coor_white_player[i][X]) && 
                 map[ coor_white_player[i][Y]+offset ][ coor_white_player[i][X] ] == EMPTY_PLACE )
                eval += WHITE_PRICE_MOVE_DOWN;
        }
        
        //(UP)
        if ( is_check_borders(SIZE_PETAL, coor_white_player[i][Y] - 1, coor_white_player[i][X]) && 
             map[ coor_white_player[i][Y] - 1 ][ coor_white_player[i][X] ] != BLACK_PLACE )
        {
            int offset = -1; //смещение шашки по шашкам

            if ( map[ coor_white_player[i][Y]+offset ][ coor_white_player[i][X] ] == WHITE_PLACE )
            {
                for (offset--; is_check_borders(SIZE_PETAL, coor_white_player[i][Y]+offset, coor_white_player[i][X]) && 
                                map[ coor_white_player[i][Y]+offset ][ coor_white_player[i][X] ] == WHITE_PLACE;
                    offset--);
            }

            if ( is_check_borders(SIZE_PETAL, coor_white_player[i][Y]+offset, coor_white_player[i][X]) && 
                 map[ coor_white_player[i][Y]+offset ][ coor_white_player[i][X] ] == EMPTY_PLACE)
                eval += WHITE_PRICE_MOVE_UP;
        }

        //(RIGHT)
        if ( is_check_borders(SIZE_PETAL, coor_white_player[i][Y], coor_white_player[i][X] + 1) && 
             map[ coor_white_player[i][Y]][ coor_white_player[i][X] + 1 ] != BLACK_PLACE )
        {
            int offset = 1; //смещение шашки по шашкам
            
            if ( map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == WHITE_PLACE )
            {
                for (offset++; is_check_borders(SIZE_PETAL, coor_white_player[i][Y], coor_white_player[i][X]+offset) &&
                                map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == WHITE_PLACE; 
                    offset++);
            }

            if ( is_check_borders(SIZE_PETAL, coor_white_player[i][Y], coor_white_player[i][X]+offset) && 
                 map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == EMPTY_PLACE)
                eval += WHITE_PRICE_MOVE_RIGHT;
        }

        //(LEFT)
        if ( is_check_borders(SIZE_PETAL, coor_white_player[i][Y], coor_white_player[i][X] - 1) && 
             map[ coor_white_player[i][Y]][ coor_white_player[i][X] - 1 ] != BLACK_PLACE )
        {
            int offset = -1; //смещение шашки по шашкам
            
            if ( map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == WHITE_PLACE )
            {
                for (offset--; is_check_borders(SIZE_PETAL, coor_white_player[i][Y], coor_white_player[i][X]+offset) &&
                                map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == WHITE_PLACE; 
                    offset--);
            }

            if ( is_check_borders(SIZE_PETAL, coor_white_player[i][Y], coor_white_player[i][X]+offset) && 
                 map[ coor_white_player[i][Y] ][ coor_white_player[i][X]+offset ] == EMPTY_PLACE)
                eval += WHITE_PRICE_MOVE_LEFT;
        }
    }

    return eval;
}

int getBlackHeurEval(VECTOR_2D& map, VECTOR_2D& coor_black_player)
{

    int eval = 0;

    for (int i = 0; i < coor_black_player.size(); ++i)
    {
        //Если позиция находиться в карте и там нет черной шашки
        //(Down)
        if ( is_check_borders(SIZE_PETAL, coor_black_player[i][Y] + 1, coor_black_player[i][X]) && 
             map[ coor_black_player[i][Y] + 1][ coor_black_player[i][X] ] != WHITE_PLACE)
        {
            int offset = 1; //смещение шашки по шашкам
            
            if ( map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == BLACK_PLACE )
            {
                for (offset++; is_check_borders(SIZE_PETAL, coor_black_player[i][Y]+offset, coor_black_player[i][X]) && 
                                map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == BLACK_PLACE; 
                    offset++);
            }

            if ( is_check_borders(SIZE_PETAL, coor_black_player[i][Y]+offset, coor_black_player[i][X]) && 
                 map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == EMPTY_PLACE )
                eval += BLACK_PRICE_MOVE_DOWN;
        }
       
        //(UP)
        if ( is_check_borders(SIZE_PETAL, coor_black_player[i][Y]-1, coor_black_player[i][X]) && 
             map[ coor_black_player[i][Y] - 1 ][ coor_black_player[i][X] ] != WHITE_PLACE)
        {
            int offset = -1; //смещение шашки по шашкам
            
            if ( map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == BLACK_PLACE )
            {
                for (offset--; is_check_borders(SIZE_PETAL, coor_black_player[i][Y]+offset, coor_black_player[i][X]) && 
                                map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == BLACK_PLACE;
                    offset--);
            }

            if ( is_check_borders(SIZE_PETAL, coor_black_player[i][Y]+offset, coor_black_player[i][X]) && 
                 map[ coor_black_player[i][Y]+offset ][ coor_black_player[i][X] ] == EMPTY_PLACE)
                eval += BLACK_PRICE_MOVE_UP;
        }
      
        //(RIGHT)
        if ( is_check_borders(SIZE_PETAL, coor_black_player[i][Y], coor_black_player[i][X] + 1) && 
             map[ coor_black_player[i][Y] ][ coor_black_player[i][X] + 1 ] != WHITE_PLACE)
        {
            int offset = 1; //смещение шашки по шашкам

            if ( map[ coor_black_player[i][Y] ][ coor_black_player[i][X]+offset ] == BLACK_PLACE )
            {
                for (offset++; is_check_borders(SIZE_PETAL, coor_black_player[i][Y], coor_black_player[i][X]+offset) &&
                             map[ coor_black_player[i][Y] ][ coor_black_player[i][X]+offset ] == BLACK_PLACE; 
                offset++);
            }

            if ( is_check_borders(SIZE_PETAL, coor_black_player[i][Y], coor_black_player[i][X]+offset) && 
                 map[ coor_black_player[i][Y] ][ coor_black_player[i][X]+offset ] == EMPTY_PLACE )
                eval += BLACK_PRICE_MOVE_RIGHT;
        }
        
        //(LEFT)
        if ( is_check_borders(SIZE_PETAL, coor_black_player[i][Y], coor_black_player[i][X] - 1) && 
             map[ coor_black_player[i][Y] ][ coor_black_player[i][X] - 1 ] != WHITE_PLACE)
        {
            int offset = -1; //смещение шашки по шашкам
            
            if ( map[ coor_black_player[i][Y] ][ coor_black_player[i][X]+offset ] == BLACK_PLACE )
            {
                for (offset--; is_check_borders(SIZE_PETAL, coor_black_player[i][Y], coor_black_player[i][X]+offset) &&
                                map[ coor_black_player[i][Y] ][ coor_black_player[i][X]+offset ] == BLACK_PLACE; 
                    offset--);
            }

            if ( is_check_borders(SIZE_PETAL, coor_black_player[i][Y], coor_black_player[i][X]+offset) && 
                 map[ coor_black_player[i][Y] ][ coor_black_player[i][X]+offset ] == EMPTY_PLACE)
                eval += BLACK_PRICE_MOVE_LEFT;
        }
    }
    
    return eval;
}

int getHeuristicEvaluation(VECTOR_2D& map, VECTOR_2D& coor_white_player, VECTOR_2D& coor_black_player)
{
    return  getWhiteHeurEval(map, coor_white_player) - getBlackHeurEval(map, coor_black_player);
}

int run()
{
    VECTOR_2D coor_white_player = {{0, 2}, {0, 3}, {1, 2}, {1, 3}};
    VECTOR_2D coor_black_player = {{2, 0}, {2, 1}, {3, 0}, {3, 1}};
    VECTOR_2D map =
    {
        {'*', '*',  1,  1, '*', '*'},
        {'*', '*',  1,  1, '*', '*'},
        { 2,   2,  -1, -1, -1,  -1 },
        { 2,   2,  -1, -1, -1,  -1 },
        {'*', '*', -1, -1, '*', '*'},
        {'*', '*', -1, -1, '*', '*'}
    };

    cout << getHeuristicEvaluation(map, coor_white_player, coor_black_player) << endl;
        
    return 0;
}