#include "MIL.h"
using namespace std;
c_map::c_map(int c_x,int c_y)
{
    allog("c_map::c_map 2p");
    x_mm=cord_to_chunk(c_x);
    y_mm=cord_to_chunk(c_y);
    cmap=new chunk*[3];
    for(int i=0;i<3;i++)
        cmap[i]=new chunk[3];
    for(int j=0;j<3;j++)
        for(int i=0;i<3;i++)
            cmap[i][j].load_map((x_mm-1+i),(y_mm+1-j));
}
c_map::~c_map()
{
    allog("c_map::~c_map 0p");
    delete cmap;
}
void c_map::map_up()
{
    allog("c_map::map_up 0p");
    for(int i=0;i<3;i++)
        delete &cmap[i][0];
    for(int j=0;j<2;j++)
        for(int i=0;i<3;i++)
            cmap[i][j]=cmap[i][j+1];
    y_mm--;
    for(int i=0;i<3;i++)
        cmap[i][2].load_map((x_mm-1+i),(y_mm-1));
}
void c_map::map_down()
{
    allog("c_map::map_down 0p");
    for(int i=0;i<3;i++)
        delete &cmap[i][2];
    for(int j=2;j>0;j--)
        for(int i=0;i<3;i++)
            cmap[i][j]=cmap[i][j-1];
    y_mm++;
    for(int i=0;i<3;i++)
        cmap[i][0].load_map((x_mm-1+i),(y_mm+1));
}
void c_map::map_left()
{
    allog("c_map::map_left 0p");
    for(int i=0;i<3;i++)
        delete &cmap[0][i];
    for(int j=0;j<3;j++)
        for(int i=0;i<2;i++)
            cmap[i][j]=cmap[i+1][j];
    x_mm++;
    for(int i=0;i<3;i++)
        cmap[2][i].load_map((x_mm+1),(y_mm-1+i));
}
void c_map::map_right()
{
    allog("c_map::map_right 0p");
    for(int i=0;i<3;i++)
        delete &cmap[2][i];
    for(int j=0;j<3;j++)
        for(int i=2;i>0;i--)
            cmap[i][j]=cmap[i-1][j];
    x_mm--;
    for(int i=0;i<3;i++)
        cmap[0][i].load_map((x_mm-1),(y_mm-1+i));
}
map_buffer* c_map::return_map_char()
{
    allog("c_map::return_map_char 0p");
    map_buffer *b_y=new map_buffer[MAX_CHUNK_SIZE*3];
    chunk_buffer *c_b_y;
    for(int j=0;j<MAX_CHUNK_SIZE*3;j++)
        for(int i=0;i<=MAX_CHUNK_SIZE*3;i++)
            if(i==MAX_CHUNK_SIZE*3)b_y[j].x[i]=0;
            else b_y[j].x[i]=WALL_BLOCK;
    for(int j=0;j<3;j++)                        //#!
        for(int i=0;i<3;i++)
        {
            c_b_y=cmap[i][j].return_chunk_char();
            for(int j1=MAX_CHUNK_SIZE*j;j1<MAX_CHUNK_SIZE*(j+1);j1++)
                for(int i1=MAX_CHUNK_SIZE*i;i1<MAX_CHUNK_SIZE*(i+1);i1++)
                    b_y[j1].x[i1]=c_b_y[j1%MAX_CHUNK_SIZE].x[i1%MAX_CHUNK_SIZE];
        }
    return b_y;
}
bool c_map::setup_block(int x_cord,int y_cord,char block)
{
    allog("c_map::setup_block 3p");
    if(abs(x_mm-cord_to_chunk(x_cord))>1)return false;
    if(abs(y_mm-cord_to_chunk(y_cord))>1)return false;

    cmap[cord_to_chunk(x_cord)-x_mm+1][abs(cord_to_chunk(y_cord)-y_mm-1)].setup_block(cmap[cord_to_chunk(x_cord)-x_mm+1][abs(cord_to_chunk(y_cord)-y_mm-1)].cord_to_icord(x_cord,y_cord),block);
    return true;
}
char c_map::return_block(int x_cord,int y_cord)
{
    allog("c_map::return_block 2p");
    if(abs(x_mm-cord_to_chunk(x_cord))>1)return 0;
    if(abs(y_mm-cord_to_chunk(y_cord))>1)return 0;
    return cmap[cord_to_chunk(x_cord)-x_mm+1][abs(cord_to_chunk(y_cord)-y_mm-1)].return_block(cmap[cord_to_chunk(x_cord)-x_mm+1][abs(cord_to_chunk(y_cord)-y_mm-1)].cord_to_icord(x_cord,y_cord));
}
void c_map::player_up()
{
    allog("c_map::player_up 0p");
    if(cmap[1][1].missing_chunk("player",0,1))
    {
        cmap[1][1].entity_up("player");
        cmap[1][1].upload_entity("player");
        cmap[1][0].load_entity("player");
        map_down();
    }
    else cmap[1][1].entity_up("player");
}
void c_map::player_down()
{
    allog("c_map::player_down 0p");
    if(cmap[1][1].missing_chunk("player",0,-1))
    {
        cmap[1][1].entity_down("player");
        cmap[1][1].upload_entity("player");
        cmap[1][2].load_entity("player");
        map_up();
    }
    else cmap[1][1].entity_down("player");
}
void c_map::player_left()
{
    allog("c_map::player_left 0p");
    if(cmap[1][1].missing_chunk("player",-1,0))
    {
        cmap[1][1].entity_left("player");
        cmap[1][1].upload_entity("player");
        cmap[0][1].load_entity("player");
        map_right();
    }
    else cmap[1][1].entity_left("player");
}
void c_map::player_right()
{
    allog("c_map::player_right 0p");
    if(cmap[1][1].missing_chunk("player",1,0))
    {
        cmap[1][1].entity_right("player");
        cmap[1][1].upload_entity("player");
        cmap[2][1].load_entity("player");
        map_left();
    }
    else cmap[1][1].entity_right("player");
}
int* c_map::return_entity_cord(char *name)
{
    allog("c_map::return_entity_cord 1p");
    for(int j=0;j<3;j++)
        for(int i=0;i<3;i++)
           if(cmap[i][j].find_entity("player"))return cmap[i][j].return_entity_cord("player");
    return 0;
}
