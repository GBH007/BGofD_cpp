#include "MIL.h"
using namespace std;
thing::thing()
{
    allog("thing::thing 0p");
    tt_0();
}
thing::thing(int id)
{
    allog("thing::thing 1p");
    tt_0();
    ID=id;
    char fname[BASIC_CACHE];
    strncpy(fname,"thing_info/",20);
    sprintf(&fname[strlen(fname)],"%d",id);
    strncpy(&fname[strlen(fname)],".info",20);
    ifstream fi(fname);
    if(fi)
    {
        read_sym(type,fi);
        read_sym(HP,fi);
        read_sym(rHP,fi);
        read_sym(MP,fi);
        read_sym(rMP,fi);
        read_sym(FR,fi);
    }
    else tt_0();
}
thing::~thing()//#!
{
    allog("thing::~thing 0p");
    char fname[BASIC_CACHE];
    strncpy(fname,"thing_info/",20);
    sprintf(&fname[strlen(fname)],"%d",ID);
    strncpy(&fname[strlen(fname)],".info",20);
    ofstream fo(fname);
    fo<<type<<endl;
    fo<<HP<<endl;
    fo<<rHP<<endl;
    fo<<MP<<endl;
    fo<<rMP<<endl;
    fo<<FR<<endl;
}
char* thing::return_type_char()
{
    allog("thing::return_type_char 0p");
    if(type==0)return "type: dagger";
    else if(type==1)return "type: offhand";
        else if(type==2)return "type: helmet";
            else if(type==3)return "type: chestplate";
                else if(type==4)return "type: leggins";
                    else if(type==5)return "type: boots";
                        else return "no type";
}
char* thing::return_hp_char()
{
    allog("thing::return_hp_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"hp: ",5);
    sprintf(&cache[strlen(cache)],"%d",HP);
    return cache;
}
char* thing::return_rhp_char()
{
    allog("thing::return_rhp_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"rhp: ",6);
    sprintf(&cache[strlen(cache)],"%d",rHP);
    return cache;
}
char* thing::return_mp_char()
{
    allog("thing::return_mp_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"mp: ",5);
    sprintf(&cache[strlen(cache)],"%d",MP);
    return cache;
}
char* thing::return_rmp_char()
{
    allog("thing::return_rmp_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"rmp: ",6);
    sprintf(&cache[strlen(cache)],"%d",rMP);
    return cache;
}
char* thing::return_fr_char()
{
    allog("thing::return_fr_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"fr: ",5);
    sprintf(&cache[strlen(cache)],"%d",FR);
    return cache;
}
char* thing::return_id_char()
{
    allog("thing::return_id_char 0p");
    char cache[BASIC_CACHE];
    strncpy(cache,"id: ",5);
    sprintf(&cache[strlen(cache)],"%d",ID);
    return cache;
}
int thing::return_type_int()
{
    allog("thing::return_type_int 0p");
    return type;
}
int thing::return_hp_int()
{
    allog("thing::return_hp_int 0p");
    return HP;
}
int thing::return_rhp_int()
{
    allog("thing::return_rhp_int 0p");
    return rHP;
}
int thing::return_mp_int()
{
    allog("thing::return_mp_int 0p");
    return MP;
}
int thing::return_rmp_int()
{
    allog("thing::return_rmp_int 0p");
    return rMP;
}
int thing::return_fr_int()
{
    allog("thing::return_fr_int 0p");
    return FR;
}
int thing::return_id_int()
{
    allog("thing::return_id_int 0p");
    return ID;
}
void thing::reconstruct(int id)
{
    allog("thing::reconstruct 1p");
    tt_0();
    ID=id;
    if(id>0)
    {
    char fname[BASIC_CACHE];
        strncpy(fname,"thing_info/",20);
        sprintf(&fname[strlen(fname)],"%d",id);
        strncpy(&fname[strlen(fname)],".info",20);
        ifstream fi(fname);
        read_sym(type,fi);
        read_sym(HP,fi);
        read_sym(rHP,fi);
        read_sym(MP,fi);
        read_sym(rMP,fi);
        read_sym(FR,fi);
    }
}
void thing::tt_0()
{
    allog("thing::tt_0 0p");
    type=ID=-1;
    HP=rHP=MP=rMP=FR=0;
}
bool thing::cw0()
{
    allog("thing::cw0 0p");
    if(ID<1)return true;
    if(type<0)return true;
    if(type>5)return true;
    return false;
}
