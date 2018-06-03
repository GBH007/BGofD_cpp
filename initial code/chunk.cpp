#include "MIL.h"
using namespace std;
int cord_to_chunk(int n_cord)
{
    allog("cord_to_chunk 1p");
    if(positive_number(n_cord))return n_cord/10;
    else return (n_cord+1)/10-1;
}
int* chunk_to_cord(int n_chunk)
{
    allog("chunk_to_cord 1p");
    int *n_cord=new int[2];
    if(positive_number(n_chunk))
    {
        n_cord[0]=n_chunk*10;
        n_cord[1]=(n_chunk+1)*10-1;
    }
    else
    {
        n_cord[0]=(n_chunk+1)*10-1;
        n_cord[1]=n_chunk*10;
    }
    return n_cord;
}
chunk::chunk()
{
    allog("chunk::chunk 0p");
    y=new chunk_buffer[MAX_CHUNK_SIZE];
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        entitys[i].tt_0();
    for(int j=0;j<MAX_CHUNK_SIZE;j++)
        for(int i=0;i<=MAX_CHUNK_SIZE;i++)
            y[j].x[i]=WALL_BLOCK;
    x_n=-100;                                               //#e
    y_n=-100;
}
chunk::chunk(int x_p,int y_p)
{
    allog("chunk::chunk 2p");
    char cache[BASIC_CACHE];
    strncpy(cache,"map/",5);
    sprintf(&cache[strlen(cache)],"%d",x_p);
    strncpy(&cache[strlen(cache)],"_",3);
    sprintf(&cache[strlen(cache)],"%d",y_p);
    strncpy(&cache[strlen(cache)],".chunk",10);
    ifstream fi(cache);
    x_n=x_p;
    y_n=y_p;
    x_min=chunk_to_cord(x_p)[0];
    x_max=chunk_to_cord(x_p)[1];
    y_min=chunk_to_cord(y_p)[0];
    y_max=chunk_to_cord(y_p)[1];
    y=new chunk_buffer[MAX_CHUNK_SIZE];
    for(int i=0;i<MAX_CHUNK_SIZE;i++)
        if(fi)fi.getline(y[i].x,MAX_CHUNK_SIZE+1);
        else y[i].x[0]=0;
    for(int j=0;j<MAX_CHUNK_SIZE;j++)
        for(int i=strlen(y[j].x);i<=MAX_CHUNK_SIZE;i++)
            if(i==MAX_CHUNK_SIZE)y[j].x[i]=0;
            else y[j].x[i]=WALL_BLOCK;
    strncpy(cache,"map/",5);
    sprintf(&cache[strlen(cache)],"%d",x_n);
    strncpy(&cache[strlen(cache)],"_",3);
    sprintf(&cache[strlen(cache)],"%d",y_n);
    strncpy(&cache[strlen(cache)],".ent",5);
    if(fi)fi.close();
    fi.open(cache);
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        entitys[i].tt_0();
    while(fi)
    {
        fi.getline(cache,BASIC_CACHE);
        if(strlen(cache)<2)continue;
        entitys[first_empty_slot()].reconstruct(cache);
    }
    entity_errors();
}
chunk::~chunk()
{
    allog("chunk::~chunk 0p");
    upload_map();
    char cache[BASIC_CACHE];
    strncpy(cache,"map/",5);
    sprintf(&cache[strlen(cache)],"%d",x_n);
    strncpy(&cache[strlen(cache)],"_",3);
    sprintf(&cache[strlen(cache)],"%d",y_n);
    strncpy(&cache[strlen(cache)],".ent",10);
    ofstream fo(cache);
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!entitys[i].cw0())fo<<entitys[i].return_name()<<endl;
}
void chunk::chunk_generator()
{
    allog("chunk::chunk_generator 0p");
    bool walls[4];          //0-up 1-down 2-left 3-right
    walls[0]=walls[1]=walls[2]=walls[3]=0;
    cout<<"enter x cord\n";
    read_sym(x_n);
    cout<<"enter y cord\n";
    read_sym(y_n);
    x_min=chunk_to_cord(x_n)[0];
    x_max=chunk_to_cord(x_n)[1];
    y_min=chunk_to_cord(y_n)[0];
    y_max=chunk_to_cord(y_n)[1];
    entitys=0;
    cout<<"construct wall up y/n\n";
    walls[0]=p_o_n();
    cout<<"construct wall down y/n\n";
    walls[1]=p_o_n();
    cout<<"construct wall left y/n\n";
    walls[2]=p_o_n();
    cout<<"construct wall right y/n\n";
    walls[3]=p_o_n();
    for(int j=0;j<MAX_CHUNK_SIZE;j++)
        for(int i=0;i<=MAX_CHUNK_SIZE;i++)
            if(i==MAX_CHUNK_SIZE)y[j].x[i]=0;
            else y[j].x[i]=FILLED_BLOCK;
    if(walls[0])
        for(int i=0;i<MAX_CHUNK_SIZE;i++)
            y[0].x[i]=WALL_BLOCK;
    if(walls[1])
        for(int i=0;i<MAX_CHUNK_SIZE;i++)
            y[MAX_CHUNK_SIZE-1].x[i]=WALL_BLOCK;
    if(walls[2])
        for(int i=0;i<MAX_CHUNK_SIZE;i++)
            y[i].x[0]=WALL_BLOCK;
    if(walls[3])
        for(int i=0;i<MAX_CHUNK_SIZE;i++)
            y[i].x[MAX_CHUNK_SIZE-1]=WALL_BLOCK;
    upload_map();
}
void chunk::upload_map()
{
    allog("chunk::upload_map 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"map/",5);
    sprintf(&cache[strlen(cache)],"%d",x_n);
    strncpy(&cache[strlen(cache)],"_",3);
    sprintf(&cache[strlen(cache)],"%d",y_n);
    strncpy(&cache[strlen(cache)],".chunk",10);
    ofstream fo(cache);
    for(int i=0;i<MAX_CHUNK_SIZE;i++)
        fo<<y[i].x<<endl;

}
chunk_buffer* chunk::return_chunk_char()
{
    allog("chunk::return_chunk_char 0p");
    chunk_buffer *_y=new chunk_buffer[MAX_CHUNK_SIZE];
    for(int j=0;j<MAX_CHUNK_SIZE;j++)
        for(int i=0;i<=MAX_CHUNK_SIZE;i++)
            _y[j].x[i]=y[j].x[i];
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!entitys[i].cw0())
        {
            if(entitys[i].player())setup_block(_y,cord_to_icord(entitys[i].return_cord()),PLAYER_BLOCK);
            else setup_block(_y,cord_to_icord(entitys[i].return_cord()),ENTITY_BLOCK);
        }
    return _y;
}
void chunk::setup_block(int *cord,char block)
{
    allog("chunk::setup_block 2p");
    y[cord[1]].x[cord[0]]=block;
}
void chunk::setup_block(chunk_buffer *_y,int *cord,char block)
{
    allog("chunk::setup_block 3p");
    _y[cord[1]].x[cord[0]]=block;
}
char chunk::return_block(int *cord)
{
    allog("chunk::return_block 2p");
    return y[cord[1]].x[cord[0]];
}
int* chunk::cord_to_icord(int x_cord,int y_cord)
{
    allog("chunk::cord_to_icord 2p");
    int *icord=new int[2];
    if(x_cord<0)icord[0]=x_cord-x_min+9;
    else icord[0]=x_cord-x_min;
    if(y_cord<0)icord[1]=abs(y_cord-y_min);
    else icord[1]=abs(y_cord-y_min-9);
    return icord;
}
int* chunk::cord_to_icord(int *cord)
{
    allog("chunk::cord_to_icord 1p");
    int *icord=new int[2];
    if(cord[0]<0)icord[0]=cord[0]-x_min+9;
    else icord[0]=cord[0]-x_min;
    if(cord[1]<0)icord[1]=abs(cord[1]-y_min);
    else icord[1]=abs(cord[1]-y_min-9);
    return icord;
}
bool chunk::empty_entity()
{
    allog("chunk::empty_entity 0p");
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!entitys[i].cw0())return false;
    return true;
}
bool chunk::full_entity()
{
    allog("chunk::full_entity 0p");
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(entitys[i].cw0())return false;
    return true;
}
void chunk::compress_entity()
{
    allog("chunk::compress_entity 0p");
    int j=0;
    while(j<MAX_ENTITY_IN_CHUNK)
    {
        if(entitys[j].cw0())
            for(int i=j;i<MAX_ENTITY_IN_CHUNK-1;i++)
                if(!entitys[i+1].cw0())entitys[i]=entitys[i+1];
                else entitys[i].tt_0();
        j++;
    }
}
int chunk::first_empty_slot()
{
    allog("chunk::first_empty_slot 0p");
    compress_entity();
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(entitys[i].cw0())return i;
    return -1;
}
bool chunk::error_entity_cord(int slot)
{
    allog("chunk::error_entity_thing 1p");
    if(x_n!=cord_to_chunk(entitys[slot].return_cord()[0]))return false;
    if(y_n!=cord_to_chunk(entitys[slot].return_cord()[1]))return false;
    return true;
}
int chunk::entity_errors()
{
    allog("chunk::entity_errors 0p");
    ifstream fi("map/errors.ent");
    int c=0;
    char cache[BASIC_CACHE];
    while(fi)
    {
        fi.getline(cache,BASIC_CACHE);
        if(strlen(cache)<2)continue;
        c++;
        entitys[first_empty_slot()].reconstruct(cache);
    }
    if(fi)fi.close();
    ofstream fo("map/errors.ent");
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if((!error_entity_cord(i))&&(!entitys[i].cw0()))
        {
            fo<<entitys[i].return_name()<<endl;
            entitys[i].tt_0();
            c--;
        }
    compress_entity();
    return c;
}
bool chunk::load_entity(char *name)
{
    allog("chunk::load_entity 1p");
    return entitys[first_empty_slot()].reconstruct(name);
}
bool chunk::upload_entity(char *name)
{
    allog("chunk::upload_entity 1p");
    int search_index=-1;
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!strcmp(entitys[i].return_name(),name))
        {
            search_index=i;
            break;
        }
    if(search_index==-1)return false;
    entitys[search_index].~entity();
    entitys[search_index].tt_0();
    compress_entity();
    return true;
}
bool chunk::missing_chunk(char *name,int x_s,int y_s)
{
    allog("chunk::missing_chunk 3p");
    int search_index=-1;
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!strcmp(entitys[i].return_name(),name))
        {
            search_index=i;
            break;
        }
    if(search_index==-1)return false;
    if(x_n!=cord_to_chunk(entitys[search_index].return_cord()[0]+x_s))return true;
    if(y_n!=cord_to_chunk(entitys[search_index].return_cord()[1]+y_s))return true;
    return false;
}
entity chunk::return_entity(char *name)
{
    allog("chunk::return_entity 1p");
    int search_index=-1;
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!strcmp(entitys[i].return_name(),name))
        {
            search_index=i;
            break;
        }
    if(search_index==-1)return 0;
    else return entitys[search_index];
}
bool chunk::entity_up(char *name)
{
    allog("chunk::entity_up 1p");
    int search_index=-1;
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!strcmp(entitys[i].return_name(),name))
        {
            search_index=i;
            break;
        }
    if(search_index==-1)return false;
    entitys[search_index].up();
    return true;
}
bool chunk::entity_down(char *name)
{
    allog("chunk::entity_down 1p");
    int search_index=-1;
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!strcmp(entitys[i].return_name(),name))
        {
            search_index=i;
            break;
        }
    if(search_index==-1)return false;
    entitys[search_index].down();
    return true;
}
bool chunk::entity_left(char *name)
{
    allog("chunk::entity_left 1p");
    int search_index=-1;
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!strcmp(entitys[i].return_name(),name))
        {
            search_index=i;
            break;
        }
    if(search_index==-1)return false;
    entitys[search_index].left();
    return true;
}
bool chunk::entity_right(char *name)
{
    allog("chunk::entity_right 1p");
    int search_index=-1;
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!strcmp(entitys[i].return_name(),name))
        {
            search_index=i;
            break;
        }
    if(search_index==-1)return false;
    entitys[search_index].right();
    return true;
}
int* chunk::return_entity_cord(char *name)
{
    allog("chunk::return_entity_cord 1p");
    int search_index=-1;
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!strcmp(entitys[i].return_name(),name))
        {
            search_index=i;
            break;
        }
    if(search_index==-1)return 0;
    else return entitys[search_index].return_cord();
}
bool chunk::find_entity(char *name)
{
    allog("chunk::find_entity 1p");
    int search_index=-1;
    for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
        if(!strcmp(entitys[i].return_name(),name))
        {
            search_index=i;
            break;
        }
    if(search_index==-1)return false;
    else return true;
}
void chunk::load_map(int x_p,int y_p)
{
    allog("chunk::load_map 2p");
    char cache[BASIC_CACHE];
    strncpy(cache,"map/",5);
    sprintf(&cache[strlen(cache)],"%d",x_p);
    strncpy(&cache[strlen(cache)],"_",3);
    sprintf(&cache[strlen(cache)],"%d",y_p);
    strncpy(&cache[strlen(cache)],".chunk",10);
    ifstream fi(cache);
    x_n=x_p;
    y_n=y_p;
    x_min=chunk_to_cord(x_p)[0];
    x_max=chunk_to_cord(x_p)[1];
    y_min=chunk_to_cord(y_p)[0];
    y_max=chunk_to_cord(y_p)[1];
    for(int i=0;i<MAX_CHUNK_SIZE;i++)
        if(fi)fi.getline(y[i].x,MAX_CHUNK_SIZE+1);
        else y[i].x[0]=0;
    for(int j=0;j<MAX_CHUNK_SIZE;j++)
        for(int i=strlen(y[j].x);i<=MAX_CHUNK_SIZE;i++)
            if(i==MAX_CHUNK_SIZE)y[j].x[i]=0;
            else y[j].x[i]=WALL_BLOCK;
    strncpy(cache,"map/",5);
    sprintf(&cache[strlen(cache)],"%d",x_n);
    strncpy(&cache[strlen(cache)],"_",3);
    sprintf(&cache[strlen(cache)],"%d",y_n);
    strncpy(&cache[strlen(cache)],".ent",5);
    if(fi)fi.close();
    fi.open(cache);
    while(fi)
    {
        fi.getline(cache,BASIC_CACHE);
        if(strlen(cache)<2)continue;
        entitys[first_empty_slot()].reconstruct(cache);
    }
    entity_errors();
}
