#include "MIL.h"
using namespace std;
entity::entity()
{
    allog("entity::entity 0p");
    tt_0();
}
entity::entity(char *_name)
{
    allog("entity::entity 1p");
    tt_0();
    char cache[BASIC_CACHE];
    strncpy(cache,"entity/",9);
    strncpy(&cache[strlen(cache)],_name,BASIC_CACHE);
    strncpy(&cache[strlen(cache)],".ent",5);
    ifstream fi(cache);
    strncpy(name,_name,BASIC_CACHE);
    read_sym(LV,fi);
    read_sym(XP,fi);
    read_sym(pHP,fi);
    read_sym(pMP,fi);
    read_sym(x_cord,fi);
    read_sym(y_cord,fi);
    for(int i=0;i<6;i++)
    {
        int id=-1;
        read_sym(id,fi);
        tier[i].reconstruct(id);
    }
    while(fi)
    {
        int id=0;
        read_sym(id,fi);
        if(id>0)add_thing_bag(id);
    }
}
entity::~entity()
{
    allog("entity::~entity 0p");
    fstream fs("logs/entity.log",ios::app);
    fs<<"destructor "<<name<<endl;
    char cache[BASIC_CACHE];
    strncpy(cache,"entity/",9);
    strncpy(&cache[strlen(cache)],name,BASIC_CACHE);
    strncpy(&cache[strlen(cache)],".ent",5);
    ofstream fo(cache);
    fo<<LV<<endl;
    fo<<XP<<endl;
    fo<<rHP<<endl;
    fo<<pMP<<endl;
    fo<<x_cord<<endl;
    fo<<y_cord<<endl;
    for(int i=0;i<6;i++)
        fo<<tier[i].return_id_int()<<endl;
    for(int i=0;i<MAX_BAG_SIZE;i++)
        if(!bag[i].cw0())fo<<bag[i].return_id_int()<<endl;
}
bool entity::add_thing_bag(int id)
{
    allog("entity::add_thing_bag 1p");
    bag[first_empty_slot()].reconstruct(id);
}
int entity::calc_hp_tier()
{
    allog("entity::calc_hp_tier 0p");
    int hp=0;
    for(int i=0; i<6; i++)
        hp+=tier[i].return_hp_int();
    return hp;
}
int entity::calc_rhp_tier()
{
    allog("entity::calc_rhp_tier 0p");
    int rhp=0;
    for(int i=0; i<6; i++)
        rhp+=tier[i].return_rhp_int();
    return rhp;
}
int entity::calc_mp_tier()
{
    allog("entity::calc_mp_tier 0p");
    int mp=0;
    for(int i=0; i<6; i++)
        mp+=tier[i].return_mp_int();
    return mp;
}
int entity::calc_rmp_tier()
{
    allog("entity::calc_rmp_tier 0p");
    int rmp=0;
    for(int i=0; i<6; i++)
        rmp+=tier[i].return_rmp_int();
    return rmp;
}
int entity::calc_fr_tier()
{
    allog("entity::calc_fr_tier 0p");
    int fr=0;
    for(int i=0; i<6; i++)
        fr+=tier[i].return_fr_int();
    return fr;
}
void entity::refresh_lv()
{
    allog("entity::refresh_lv 0p");
    int xp_lv=DEFAULT_STEP_XP*pow(DEFAULT_LEVEL_CONSTANT_1,LV)/pow(DEFAULT_LEVEL_CONSTANT_2,LV);
    while(XP>=xp_lv)
    {
        XP-=xp_lv;
        LV++;
        xp_lv=DEFAULT_STEP_XP*pow(DEFAULT_LEVEL_CONSTANT_1,LV)/pow(DEFAULT_LEVEL_CONSTANT_2,LV);
    }
    if(LV>MAX_LV)LV=MAX_LV;
}
void entity::refresh_stat()
{
    allog("entity::refresh_stat 0p");
    HP=calc_hp_tier()+calc_hp_lv();
    rHP=calc_rhp_tier()+calc_rhp_lv();
    MP=calc_mp_tier()+calc_mp_lv();
    rMP=calc_rmp_tier()+calc_rmp_lv();
    FR=calc_fr_tier()+calc_fr_lv();
}
void entity::refresh_pstat()
{
    allog("entity::refresh_pstat 0p");
    refresh_stat();
    pHP+=rHP;
    pMP+=rMP;
    if(pHP>HP)pHP=HP;
    if(pMP>MP)pMP=MP;
}
int entity::lv_gradient()
{
    allog("entity::lv_gradient 0p");
    refresh_lv();
    return pow(DEFAULT_LEVEL_CONSTANT_1,LV)/pow(DEFAULT_LEVEL_CONSTANT_2,LV);
}
int entity::calc_hp_lv()
{
    allog("entity::calc_hp_lv 0p");
    return DEFAULT_HP*lv_gradient();
}
int entity::calc_rhp_lv()
{
    allog("entity::calc_rhp_lv 0p");
    return DEFAULT_rHP*lv_gradient();
}
int entity::calc_mp_lv()
{
    allog("entity::calc_mp_lv 0p");
    return DEFAULT_MP*lv_gradient();
}
int entity::calc_rmp_lv()
{
    allog("entity::calc_rmp_lv 0p");
    return DEFAULT_rMP*lv_gradient();
}
int entity::calc_fr_lv()
{
    allog("entity::calc_fr_lv 0p");
    return DEFAULT_FR*lv_gradient();
}
bool entity::equip_thing(int id)
{
    allog("entity::equip_thing 1p");
    if(empty_bag())return false;
    thing _thing_eq=(id);
    int type_eq=_thing_eq.return_type_int();
    if((type_eq<0)||(type_eq>5))return false;
    int search_thing=-1;
    for(int i=0;i<MAX_BAG_SIZE;i++)
        if(id==bag[i].return_id_int())
        {
            search_thing=i;
            break;
        }
    if(search_thing==-1)return false;
    bag[search_thing].~thing();
    bag[search_thing].tt_0();
    if((tier[type_eq].return_type_int()>=0)&&(tier[type_eq].return_type_int()<6))
        bag[first_empty_slot()].reconstruct(tier[type_eq].return_id_int());
    tier[type_eq].reconstruct(id);
    return true;
}
char* entity::return_name_char()
{
    allog("entity::return_name_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"n:",3);
    strncpy(&cache[strlen(cache)],name,50);
    return cache;
}
char* entity::return_lv_char()
{
    allog("entity::return_lv_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"l:",3);
    sprintf(&cache[strlen(cache)],"%d",LV);
    strncpy(&cache[strlen(cache)],"|",3);
    sprintf(&cache[strlen(cache)],"%d",XP);
    return cache;
}
char* entity::return_hp_char()
{
    allog("entity::return_hp_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"h:",3);
    sprintf(&cache[strlen(cache)],"%d",pHP);
    strncpy(&cache[strlen(cache)],"\\",3);
    sprintf(&cache[strlen(cache)],"%d",HP);
    strncpy(&cache[strlen(cache)],"+",3);
    sprintf(&cache[strlen(cache)],"%d",rHP);
    return cache;
}
char* entity::return_mp_char()
{
    allog("entity::return_mp_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"m:",3);
    sprintf(&cache[strlen(cache)],"%d",pMP);
    strncpy(&cache[strlen(cache)],"\\",3);
    sprintf(&cache[strlen(cache)],"%d",MP);
    strncpy(&cache[strlen(cache)],"+",3);
    sprintf(&cache[strlen(cache)],"%d",rMP);
    return cache;
}
char* entity::return_fr_char()
{
    allog("entity::return_fr_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"f:",3);
    sprintf(&cache[strlen(cache)],"%d",FR);
    return cache;
}
char* entity::return_cord_char()
{
    allog("entity::return_cord_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"c:",3);
    sprintf(&cache[strlen(cache)],"%d",x_cord);
    strncpy(&cache[strlen(cache)],"|",3);
    sprintf(&cache[strlen(cache)],"%d",y_cord);
    return cache;
}
int* entity::return_cord()
{
    allog("entity::return_cord 0p");
    int *cord=new int[2];
    cord[0]=x_cord;
    cord[1]=y_cord;
    return cord;
}
bool entity::player()
{
    allog("entity::player 0p");
    if(!strcmp(name,DEFAULT_PLAYER_NAME))return true;
    else return false;
}
void entity::tt_0()
{
    allog("entity::tt_0 0p");
    HP=rHP=pHP=0;
    MP=rMP=pMP=0;
    FR=0;
    XP=LV=0;
    x_cord=y_cord=0;
    name[0]=0;
    for(int i=0;i<MAX_BAG_SIZE;i++)
        bag[i].tt_0();
}
char* entity::return_name()
{
    allog("entity::return_name 0p");
    return name;
}
bool entity::empty_bag()
{
    allog("entity::empty_bag 0p");
    for(int i=0;i<MAX_BAG_SIZE;i++)
        if(!bag[i].cw0())return false;
    return true;
}
bool entity::full_bag()
{
    allog("entity::full_bag 0p");
    for(int i=0;i<MAX_BAG_SIZE;i++)
        if(bag[i].cw0())return false;
    return true;
}
void entity::compress_bag()
{
    allog("entity::compress_bag 0p");
    int j=0;
    while(j<MAX_BAG_SIZE)
    {
        if(bag[j].cw0())
            for(int i=j;i<MAX_BAG_SIZE-1;i++)
                if(!bag[i+1].cw0())bag[i]=bag[i+1];
                else bag[i].tt_0();
        j++;
    }
}
int entity::first_empty_slot()
{
    allog("entity::first_empty_slot 0p");
    compress_bag();
    for(int i=0;i<MAX_BAG_SIZE;i++)
        if(bag[i].cw0())return i;
    return -1;
}
int entity::error_bag()
{
    allog("entity::error_bag 0p");
    int c=0;
    for(int i=0;i<MAX_BAG_SIZE;i++)
        if(!error_bag_thing(i))
        {
            bag[i].tt_0();
            c++;
        }
    compress_bag();
    return c;
}
bool entity::error_bag_thing(int slot)
{
    allog("entity::error_bag_thing 1p");
    if(bag[slot].cw0())return false;
    return true;
}
bool entity::cw0()
{
    allog("entity::cw0 0p");
    if(strlen(name)<2)return true;
    return false;
}
bool entity::reconstruct(char *_name)
{
    allog("entity::reconstruct 1p");
    tt_0();
    char cache[BASIC_CACHE];
    strncpy(cache,"entity/",9);
    strncpy(&cache[strlen(cache)],_name,BASIC_CACHE);
    strncpy(&cache[strlen(cache)],".ent",5);
    ifstream fi(cache);
    if(!fi)return false;
    strncpy(name,_name,BASIC_CACHE);
    read_sym(LV,fi);
    read_sym(XP,fi);
    read_sym(pHP,fi);
    read_sym(pMP,fi);
    read_sym(x_cord,fi);
    read_sym(y_cord,fi);
    for(int i=0;i<6;i++)
    {
        int id=-1;
        read_sym(id,fi);
        tier[i].reconstruct(id);
    }
    while(fi)
    {
        int id=0;
        read_sym(id,fi);
        if(id>0)add_thing_bag(id);
    }
    return true;
}
