#ifndef CHUNK_H
#define CHUNK_H
#include "MIL.h"
using namespace std;
const int MAX_CHUNK_SIZE=10;
const char WALL_BLOCK='%';
const char FILLED_BLOCK=' ';
const char ENTITY_BLOCK='E';
const char PLAYER_BLOCK='@';
const int MAX_ENTITY_IN_CHUNK=5;
int cord_to_chunk(int n_cord);
int* chunk_to_cord(int n_chunk);
struct chunk_buffer
{
    char x[MAX_CHUNK_SIZE+1];
};
struct map_buffer
{
    char x[MAX_CHUNK_SIZE*3+1];
};
class chunk
{
    private:
        int x_n,y_n;        //номер чанка
        int x_max,x_min,y_max,y_min;    //min начало чанка max конец чанка
        entity *entitys=new entity[MAX_ENTITY_IN_CHUNK];
        chunk_buffer *y;
    public:
        chunk();
        chunk(int x_p,int y_p);
        ~chunk();
        void chunk_generator();
        void upload_map();
        chunk_buffer* return_chunk_char();
        void setup_block(int *cord,char block);
        void setup_block(chunk_buffer *_y,int *cord,char block);       //работает с координатами ВНУТРИ НЕ КОНВЕРТИРУЕТ!
        char return_block(int *cord);       //работает с координатами ВНУТРИ НЕ КОНВЕРТИРУЕТ!
        int* cord_to_icord(int x_cord,int y_cord);      //конвертирует внешние координаты во внутрение
        int* cord_to_icord(int *cord);      //конвертирует внешние координаты во внутрение

        bool empty_entity();
        bool full_entity();
        void compress_entity();
        int first_empty_slot();
        bool error_entity_cord(int slot);
        int entity_errors();

        bool load_entity(char *name);
        bool upload_entity(char *name);
        bool missing_chunk(char *name,int x_s,int y_s);
        entity return_entity(char *name);
        bool entity_up(char *name);
        bool entity_down(char *name);
        bool entity_left(char *name);
        bool entity_right(char *name);
        int* return_entity_cord(char *name);
        bool find_entity(char *name);

        void load_map(int x_p,int y_p);

        chunk &operator =(chunk &_chunk)
        {
            x_n=_chunk.x_n;
            y_n=_chunk.y_n;
            x_max=_chunk.x_max;
            x_min=_chunk.x_min;
            y_max=_chunk.y_max;
            y_min=_chunk.y_min;
            for(int i=0;i<MAX_ENTITY_IN_CHUNK;i++)
                entitys[i]=_chunk.entitys[i];
            y=_chunk.y;
            return *this;
        }
};
#endif /*CHUNK_H*/
