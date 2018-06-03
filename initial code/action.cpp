#include "MIL.h"
using namespace std;
char* sort_comand(char *comand)
{
    allog("sort_comand 1p");
    char *cache=new char[BASIC_CACHE];
    int s=strlen(comand);
    for(int i=0;i<strlen(comand);i++)
        if(comand[i]==' ')
        {
            s=i;
            break;
        }
    for(int i=0;i<s;i++)
        cache[i]=comand[i];
    cache[s]=0;
    for(int i=0;i<strlen(comand)-s-1;i++)
        comand[i]=comand[i+s+1];
    return cache;
}
void action()
{
    allog("action 0p");
    entity *player=new entity("player");
    display *m=new display;
    c_map *t_map=new c_map(player->return_cord()[0],player->return_cord()[1]);
    delete player;
    char cache[BASIC_CACHE];
    m->refresh_board(t_map->return_map_char());
    m->print();
    while(true)
    {
        cin.getline(cache,BASIC_CACHE);
        if(!strcmp(cache,"exit"))break;
        char *cache2=sort_comand(cache);
        if(!strcmp(cache2,"go"))go(m,t_map,cache);
        //if(!strcmp(cache2,""))
    }

   // m.refresh_board(t_map->return_map_char());
   // m.print();



    delete t_map;
    delete m;
}
void go(display *m,c_map *t_map,char *comand)
{
    allog("go 3p");
    char *cache=sort_comand(comand);
    int c=atoi(comand);
    if(!c)c++;
    if(!strcmp(cache,"up"))
        for(int i=0;i<c;i++)
            go_up(m,t_map);
    if(!strcmp(cache,"down"))
        for(int i=0;i<c;i++)
            go_down(m,t_map);
    if(!strcmp(cache,"left"))
        for(int i=0;i<c;i++)
            go_left(m,t_map);
    if(!strcmp(cache,"right"))
        for(int i=0;i<c;i++)
            go_right(m,t_map);
}
void go_up(display *m,c_map *t_map)
{
    allog("go_up 2p");
    if(t_map->return_block(t_map->return_entity_cord("player")[0],t_map->return_entity_cord("player")[1]+1)!=WALL_BLOCK)
    {
        t_map->player_up();
        m->refresh_board(t_map->return_map_char());
        m->print();
    }
    else
    {
        m->refresh_chat("you can not just");
        m->print();
    }
}
void go_down(display *m,c_map *t_map)
{
    allog("go_down 2p");
    if(t_map->return_block(t_map->return_entity_cord("player")[0],t_map->return_entity_cord("player")[1]-1)!=WALL_BLOCK)
    {
        t_map->player_down();
        m->refresh_board(t_map->return_map_char());
        m->print();
    }
    else
    {
        m->refresh_chat("you can not just");
        m->print();
    }
}
void go_left(display *m,c_map *t_map)
{
    allog("go_left 2p");
    if(t_map->return_block(t_map->return_entity_cord("player")[0]-1,t_map->return_entity_cord("player")[1])!=WALL_BLOCK)
    {
        t_map->player_left();
        m->refresh_board(t_map->return_map_char());
        m->print();
    }
    else
    {
        m->refresh_chat("you can not just");
        m->print();
    }
}
void go_right(display *m,c_map *t_map)
{
    allog("go_right 2p");
    if(t_map->return_block(t_map->return_entity_cord("player")[0]+1,t_map->return_entity_cord("player")[1])!=WALL_BLOCK)
    {
        t_map->player_right();
        m->refresh_board(t_map->return_map_char());
        m->print();
    }
    else
    {
        m->refresh_chat("you can not just");
        m->print();
    }
}
