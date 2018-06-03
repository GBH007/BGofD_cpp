#ifndef MAP_H
#define MAP_H
#include "MIL.h"
using namespace std;
class c_map
{
    private:
        int x_mm,y_mm;
        chunk **cmap;
    public:
        c_map(int c_x,int c_y);         //работает с координатами игрока не чанка
        ~c_map();
        void map_up();
        void map_down();
        void map_left();
        void map_right();
        map_buffer* return_map_char();
        bool setup_block(int x_cord,int y_cord,char block);
        char return_block(int x_cord,int y_cord);

        void player_up();
        void player_down();
        void player_left();
        void player_right();
        int* return_entity_cord(char *name);
};
#endif /*MAP_H*/
