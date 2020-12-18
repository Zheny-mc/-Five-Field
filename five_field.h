#ifndef FIVE_FIELD_H
#define FIVE_FIELD_H

#include <iostream>
#include <vector>
#include <iomanip>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::setw;

#define INT_VECTOR_2D vector<vector<int>>

#define USER 1
#define COMPUTER 2
#define EMPTY -1
#define RELATED 0

#define WHITE_PRICE_MOVE_DOWN  4
#define WHITE_PRICE_MOVE_LEFT  2
#define WHITE_PRICE_MOVE_RIGHT 3

#define BLACK_PRICE_MOVE_DOWN  3
#define BLACK_PRICE_MOVE_UP    2
#define BLACK_PRICE_MOVE_RIGHT 4

#define COOR_Y 0
#define COOR_X 1

#define MIN false 
#define MAX true

#define IS_USER false
#define IS_COMPUTER true

#define MAX_DEPTH 2
    
#define NOT_INITIALIZE -254
#define MIN_VALUE -50
#define MAX_VALUE 50

//положение шашки на карте
class Checker_pos
{
public:
    int x;
    int y;
};

//ход шашки компьютера
class Move_PC
{
public:
    int ind_checker;          //индекс шашки
    Checker_pos checker;      //исходная позиция шашки
    Checker_pos move_checker; //куда сходить

    Move_PC(int x_y=0)
    {
        checker.x = move_checker.x = x_y;
        checker.y = move_checker.y = x_y;
    }
};


class five_field
{ 
private:
    const int SIZE_MAP;    //размер карты
    const int SIZE_PETAL;  //размер лепестка
    const int NUM_CHECKER; //количество шашек

    INT_VECTOR_2D map;           //карта
    INT_VECTOR_2D coor_player;   //координаты юзера
    INT_VECTOR_2D coor_computer; //координаты игрока

public:
    //************для конструктора**************
    void set_units();       //установка юнитов на карту
    void set_empty_place(); //заполнение пустых мест на карте

    //*************для ходов*******************
    bool is_check_borders(int y_i, int x_i); //проверка границ
    int max(int left_num, int right_num);    
    int min(int left_num, int right_num);
    int find_num_check(Checker_pos& first_pos);//поиск шашки по координатам
    //****************************************
    
    bool is_move_player(int num_checker, Checker_pos& first_pos, Checker_pos& second_pos);
    
    //***************вспомогательный ф-и для minimax********************************
    //определение хода шашки
    Checker_pos define_down_pos(Checker_pos position, bool is_type_player);  //вниз
    Checker_pos define_up_pos(Checker_pos position, bool is_type_player);    //вверх
    Checker_pos define_right_pos(Checker_pos position, bool is_type_player); //вправо
    Checker_pos define_left_pos(Checker_pos position, bool is_type_player);  //влево

    //есть ли возможность сходить
    bool is_can_move(Checker_pos& first_pos, Checker_pos& second_pos);
    
    //ход
    void do_move(bool is_type_player, int i_checker, Checker_pos& first_pos, Checker_pos& second_pos);
    
    //получение оценки карты для компьютера
    int get_computer_heur_eval(INT_VECTOR_2D& coor_black_player);
    //получение оценки карты для юзера
    int get_user_Heur_Eval(INT_VECTOR_2D& coor_white_player);
    //**********************************************************************

    //оценочная ф-я
    int getHeuristicEvaluation();
    //минимакс
    int run_minimax(bool is_type_moster, int depth, int alpha, int beta);//-

    five_field(int _SIZE_MAP);

    bool is_win_user();     //победил юзер
    bool is_win_computer(); //победил компьютер

    void move_player();   //ход игрока
    void move_computer(); //ход компьютера

    //отрисовка карты
    void show();
};    


#endif 
