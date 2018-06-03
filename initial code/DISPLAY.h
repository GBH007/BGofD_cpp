#ifndef DISPLAY_H
#define DISPLAY_H
#include "MIL.h"
using namespace std;
const int MAX_DX_SIZE=50;
const int MAX_DY_SIZE=32;
const int MAX_SUPPORT_COLUMN_SIZE=17;
const int MAX_STATISTIC_SIZE=9;
const int MAX_CHAT_SIZE=20;
struct char_x_cord
{
    char y[MAX_DY_SIZE+1];
};
struct statistic_buffer
{
    char x[MAX_SUPPORT_COLUMN_SIZE+1];
};
class display
{
    private:
        char_x_cord x[MAX_DX_SIZE+1];
        ofstream display_log;
    public:
        display();
        ~display();
        bool display_log_record(char *record);
        bool refresh_chat(char *message);
        bool refresh_board(map_buffer *b_y);
        bool refresh_statistic(statistic_buffer *b_y);
        bool view_block_statistic(char b);
        bool view_thing_statistic(thing t);
        bool view_entity_statistic(entity *e);
        void print();
        void print_screen(char *fname);
};
#endif /*DISPLAY_H*/
