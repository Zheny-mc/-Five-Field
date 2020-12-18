#include "start_game.h"

#define _PLAY_ 'n'

int main()
{
    try
    {
        char play = input_be_game();

        if (play == _PLAY_)
        {
            int size = input_size();
            run(size);
        }
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
    }


    return 0;
}

