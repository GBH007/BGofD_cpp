#include "MIL.h"
using namespace std;
display::display()
{
    allog("display::display 0p");
    display_log.open("logs/display.log");
    for(int j=0;j<MAX_DY_SIZE;j++)
        for(int i=0;i<MAX_DX_SIZE;i++)
            if((i==0)||(i==MAX_SUPPORT_COLUMN_SIZE+1)||(i==MAX_DX_SIZE-1)||(j==0)||(j==MAX_DY_SIZE-1)||((j==MAX_STATISTIC_SIZE+1)&&(i<MAX_SUPPORT_COLUMN_SIZE+1)))
                x[i].y[j]='#';
            else
                if((i>0)&&(j>10)&&(i<18)&&(j<31))
                    x[i].y[j]='~';
                else
                    x[i].y[j]=' ';
}
display::~display()
{
    allog("display::~display 0p");
    display_log_record("delete display");
}
bool display::display_log_record(char *record)
{
    allog("display::display_log_record 1p");
    if(display_log<<record<<endl)return true;
    else return false;
}
bool display::refresh_chat(char *message)
{
    allog("display::refresh_chat 1p");
    display_log_record("add chat record:");
    display_log_record(message);
    int i,j;
    for(j=MAX_STATISTIC_SIZE+3;j<MAX_DY_SIZE-1;j++)
        for(i=1;i<=MAX_SUPPORT_COLUMN_SIZE;i++)
            x[i].y[j-1]=x[i].y[j];
    i=1;
    j=MAX_STATISTIC_SIZE+MAX_CHAT_SIZE+1;
    for(;i<=MAX_SUPPORT_COLUMN_SIZE;i++)
        if(i<=strlen(message))x[i].y[j]=message[i-1];
        else x[i].y[j]=32;
    return true;
}
void display::print()
{
    allog("display::print 0p");
    system("clear");
    for(int j=0;j<MAX_DY_SIZE;j++)
    {
        for(int i=0;i<MAX_DX_SIZE;i++)
            cout<<x[i].y[j];
        cout<<endl;
    }

}
bool display::view_block_statistic(char b)
{
    allog("display::view_block_statistic 1p");
    char fname[BASIC_CACHE],cache[BASIC_CACHE];
    strncpy(fname,"block_info/",50);
    fname[strlen(fname)]=b;
    fname[strlen(fname)+1]=0;
    strncpy(&fname[strlen(fname)],".info",49);
    ifstream fi(fname);
    int j=0;
    statistic_buffer b_y[MAX_STATISTIC_SIZE];
    for(int i=0;i<MAX_STATISTIC_SIZE;i++)
        b_y[i].x[0]=0;
    while((fi)&&(j<MAX_STATISTIC_SIZE))
    {
        fi.getline(cache,BASIC_CACHE);
        strncpy(b_y[j].x,cache,MAX_SUPPORT_COLUMN_SIZE);
        j++;
    }
    if(refresh_statistic(b_y))return true;
    else return false;
}
bool display::refresh_statistic(statistic_buffer *b_y)
{
    allog("display::refresh_statistic 1p");
    display_log_record("refresh statistic");
    for(int j=1;j<=MAX_STATISTIC_SIZE;j++)
        for(int i=1;i<=MAX_SUPPORT_COLUMN_SIZE;i++)
            x[i].y[j]=' ';
    for(int j=1;j<=MAX_STATISTIC_SIZE;j++)
        for(int i=1;i<=MAX_SUPPORT_COLUMN_SIZE;i++)
            if(b_y[j-1].x[i-1])x[i].y[j]=b_y[j-1].x[i-1];
            else break;
    return true;
}
bool display::view_thing_statistic(thing t)
{
    allog("display::view_thing_statistic 1p");
    statistic_buffer b_y[MAX_STATISTIC_SIZE];
    for(int i=0;i<MAX_STATISTIC_SIZE;i++)
        for(int j=0;j<MAX_SUPPORT_COLUMN_SIZE;j++)
            b_y[i].x[j]=0;
    strncpy(b_y[0].x,t.return_type_char(),MAX_SUPPORT_COLUMN_SIZE);
    strncpy(b_y[1].x,t.return_hp_char(),MAX_SUPPORT_COLUMN_SIZE);
    strncpy(b_y[2].x,t.return_rhp_char(),MAX_SUPPORT_COLUMN_SIZE);
    strncpy(b_y[3].x,t.return_mp_char(),MAX_SUPPORT_COLUMN_SIZE);
    strncpy(b_y[4].x,t.return_rmp_char(),MAX_SUPPORT_COLUMN_SIZE);
    strncpy(b_y[5].x,t.return_fr_char(),MAX_SUPPORT_COLUMN_SIZE);
    if(refresh_statistic(b_y))return true;
    else return false;
}
bool display::view_entity_statistic(entity *e)
{
    allog("display::view_entity_statistic 1p");
    statistic_buffer b_y[MAX_STATISTIC_SIZE];
    for(int i=0;i<MAX_STATISTIC_SIZE;i++)
        for(int j=0;j<MAX_SUPPORT_COLUMN_SIZE;j++)
            b_y[i].x[j]=0;
    strncpy(b_y[0].x,e->return_name_char(),MAX_SUPPORT_COLUMN_SIZE);
    strncpy(b_y[1].x,e->return_lv_char(),MAX_SUPPORT_COLUMN_SIZE);
    strncpy(b_y[2].x,e->return_hp_char(),MAX_SUPPORT_COLUMN_SIZE);
    strncpy(b_y[3].x,e->return_mp_char(),MAX_SUPPORT_COLUMN_SIZE);
    strncpy(b_y[4].x,e->return_fr_char(),MAX_SUPPORT_COLUMN_SIZE);
    strncpy(b_y[5].x,e->return_cord_char(),MAX_SUPPORT_COLUMN_SIZE);
    if(refresh_statistic(b_y))return true;
    else return false;
}
bool display::refresh_board(map_buffer *b_y)
{
    allog("display::refresh_board 1p");
    display_log_record("refresh board");
    for(int j=1;j<MAX_CHUNK_SIZE*3+1;j++)
        for(int i=MAX_SUPPORT_COLUMN_SIZE+2;i<MAX_SUPPORT_COLUMN_SIZE+2+MAX_CHUNK_SIZE*3;i++)
            x[i].y[j]=WALL_BLOCK;

    for(int j=1;j<=MAX_CHUNK_SIZE*3;j++)
        for(int i=MAX_SUPPORT_COLUMN_SIZE+2;i<MAX_SUPPORT_COLUMN_SIZE+2+MAX_CHUNK_SIZE*3;i++)
            if(b_y[j-1].x[i-MAX_SUPPORT_COLUMN_SIZE-2])x[i].y[j]=b_y[j-1].x[i-MAX_SUPPORT_COLUMN_SIZE-2];
            else break;

    return true;
}
void display::print_screen(char *fname)
{
    allog("display::print_screen 1p");
    ofstream fo(fname);
    for(int j=0;j<MAX_DY_SIZE;j++)
    {
        for(int i=0;i<MAX_DX_SIZE;i++)
            fo<<x[i].y[j];
        fo<<endl;
    }
}
