#ifndef ENTITY_H
#define ENTITY_H
#include "MIL.h"
using namespace std;
const int DEFAULT_HP=100;
const int DEFAULT_rHP=10;
const int DEFAULT_MP=80;
const int DEFAULT_rMP=8;
const int DEFAULT_FR=0;
const int DEFAULT_STEP_XP=30;               //ск-ко опыта нужно для перехода с 1лв на 2-й
const int DEFAULT_LEVEL_CONSTANT_1=11;      //стат*c1^lv/c2^lv
const int DEFAULT_LEVEL_CONSTANT_2=10;
const int MAX_LV=50;
const char DEFAULT_PLAYER_NAME[BASIC_CACHE]="player";
const int MAX_BAG_SIZE=10;
class entity
{
    private:
        int HP,rHP,pHP;     //pHP текущее хп
        int MP,rMP,pMP;     //pMP текущая мана
        int FR;
        int XP,LV;
        int x_cord,y_cord;
        char name[BASIC_CACHE];
        thing *tier=new thing[6];      //вещи надетые на персонажа
        thing *bag=new thing[MAX_BAG_SIZE];         //сумка с вещами
    public:
        entity();
        entity(char *_name);
        ~entity();
        bool add_thing_bag(int id);
        int calc_hp_tier();
        int calc_rhp_tier();
        int calc_mp_tier();
        int calc_rmp_tier();
        int calc_fr_tier();
        void refresh_lv();
        void refresh_stat();
        void refresh_pstat();   //обновление pHP,pMP
        int lv_gradient();
        int calc_hp_lv();
        int calc_rhp_lv();
        int calc_mp_lv();
        int calc_rmp_lv();
        int calc_fr_lv();
        bool equip_thing(int id);

        char* return_name_char();
        char* return_lv_char();
        char* return_hp_char();
        char* return_mp_char();
        char* return_fr_char();
        char* return_cord_char();

        int* return_cord();
        bool player();          //true если это игрок false иначе
        void tt_0();            //обнуление всех зн-й
        char* return_name();

        int* return_uhp()
        {
            int *uhp=new int[3];
            uhp[0]=HP;
            uhp[1]=rHP;
            uhp[2]=pHP;
            return uhp;
        };
        int* return_ump()
        {
            int *ump=new int[3];
            ump[0]=MP;
            ump[1]=rMP;
            ump[2]=pMP;
            return ump;
        };
        int return_fr(){return FR;};
        int* return_uxp()
        {
            int *uxp=new int[2];
            uxp[0]=XP;
            uxp[1]=LV;
            return uxp;
        };
        thing* return_tier(){return tier;};
        thing* return_bag(){return bag;};

        bool empty_bag();               //false если сумка не пуста true иначе
        bool full_bag();                //true если свободных мест в сумке нет false иначе
        void compress_bag();            //10100->11000 убирает свободные полости
        int first_empty_slot();         //возвращает номер 1-го свободного слота в сумке
        int error_bag();                //автоматически удаляет несушестующие вещи возвращает кол-во удаленых
        bool error_bag_thing(int slot); //проверяет на существование вещь true если вещь существует false иначе

        bool cw0();
        bool reconstruct(char *_name);

        void up(){y_cord++;};
        void down(){y_cord--;};
        void left(){x_cord--;};
        void right(){x_cord++;};

        entity &operator =(entity &_entity)
        {
            strncpy(name,_entity.return_name(),BASIC_CACHE);
            HP=_entity.return_uhp()[0];
            rHP=_entity.return_uhp()[1];
            pHP=_entity.return_uhp()[2];
            MP=_entity.return_ump()[0];
            rMP=_entity.return_ump()[1];
            pMP=_entity.return_ump()[2];
            FR=_entity.return_fr();
            XP=_entity.return_uxp()[0];
            LV=_entity.return_uxp()[1];
            x_cord=_entity.return_cord()[0];
            y_cord=_entity.return_cord()[1];
            tier=_entity.return_tier();
            bag=_entity.return_bag();
            return *this;
        };
};
#endif /*ENTITY_H*/
