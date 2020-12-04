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

#define COOR_Y 0
#define COOR_X 1

class checker_pos
{
public:
    int x;
    int y;
};

class five_field
{ 
private:
    const int SIZE_MAP;
    const int SIZE_PETAL;

    INT_VECTOR_2D map;
    INT_VECTOR_2D coor_player;
    INT_VECTOR_2D coor_computer; 

private:
    void set_units();
    void set_empty_place(); 

    bool is_win_user(INT_VECTOR_2D& field); 
    bool is_win_computer(INT_VECTOR_2D& field);

    bool is_check_borders(int y_i, int x_i);
    void swap(int& first_pos, int& second_pos);

    bool is_move_player(checker_pos& first_pos, checker_pos& second_pos);

    //int getHeuristicEvaluation(INT_VECTOR_2D& map, 
    //                           INT_VECTOR_2D& coor_player, 
    //                           INT_VECTOR_2D& coor_computer); 
    
    //int run_minimax(INT_VECTOR_2D& map, INT_VECTOR_2D& coor); //

public:
    five_field(int _SIZE_MAP);

    bool is_win_user();
    bool is_win_computer();

    void move_player();
    //void move_computer();

    void show();
};    


#endif 
