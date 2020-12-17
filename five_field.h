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

class Checker_pos
{
public:
    int x;
    int y;
};

class Move_PC
{
public:
    int ind_checker;
    Checker_pos checker;
    Checker_pos move_checker; 

    Move_PC(int x_y=0)
    {
        checker.x = move_checker.x = x_y;
        checker.y = move_checker.y = x_y;
    }
};

class five_field
{ 
private:
    const int SIZE_MAP;
    const int SIZE_PETAL;
    const int NUM_CHECKER;

    INT_VECTOR_2D map;
    INT_VECTOR_2D coor_player;
    INT_VECTOR_2D coor_computer; 
    int best_score;

    Checker_pos pos_checker_user;
    Checker_pos pos_checker_pc;

public:
//private:
    //************для конструктора**************
    void set_units();
    void set_empty_place(); 

    //*************для ходов*******************
    bool is_check_borders(int y_i, int x_i);
    void swap(int& first_pos, int& second_pos);
    int max(int left_num, int right_num);
    int min(int left_num, int right_num);
    int find_num_check(Checker_pos& first_pos);

    bool is_be_checker_pc_map(Checker_pos pos);
    bool is_be_checker_user_map(Checker_pos pos);
    //****************************************
    
    bool is_move_player(int num_checker, Checker_pos& first_pos, Checker_pos& second_pos);
    
    //***************вспомогательный ф-и для minimax********************************
    Checker_pos define_down_pos(Checker_pos position, bool is_type_player);
    Checker_pos define_up_pos(Checker_pos position, bool is_type_player);
    Checker_pos define_right_pos(Checker_pos position, bool is_type_player);
    Checker_pos define_left_pos(Checker_pos position, bool is_type_player);

    bool is_can_move(Checker_pos& first_pos, Checker_pos& second_pos);
    
    void do_move(bool is_type_player, int i_checker, Checker_pos& first_pos, Checker_pos& second_pos);
    
    int get_computer_heur_eval(INT_VECTOR_2D& coor_black_player);
    int get_user_Heur_Eval(INT_VECTOR_2D& coor_white_player);
    //**********************************************************************

    //оценочная ф-я
    int getHeuristicEvaluation();//- 
    //минимакс
    int run_minimax(bool is_type_moster, int depth);//-

//public:
    five_field(int _SIZE_MAP);

    bool is_win_user();
    bool is_win_computer();

    void move_player();
    void move_computer();//-

    //покажи карту
    void show();
};    


#endif 
