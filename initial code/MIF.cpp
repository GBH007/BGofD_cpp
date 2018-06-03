#include "MIL.h"
using namespace std;
bool read_sym(int &sym)
{
    allog("read_sym 1p");
    char cache[BASIC_CACHE];
    if(!cin.getline(cache,BASIC_CACHE))return false;
    sym=atoi(cache);
    return true;
}
bool read_sym(int &sym, ifstream &fi)
{
    allog("read_sym 2p");
    char cache[BASIC_CACHE];
    if(!fi.getline(cache,BASIC_CACHE))return false;
    sym=atoi(cache);
    return true;
}
void allog(char *cache)
{
    ofstream f_alllog("logs/all.log",ios::app);
    f_alllog<<cache<<endl;
}
void allog(int cache)
{
    ofstream f_alllog("logs/all.log",ios::app);
    f_alllog<<cache<<endl;
}
void sallog(char *cache)
{
    ofstream f_alllog("logs/sall.log",ios::app);
    f_alllog<<cache<<endl;
}
void sallog(int cache)
{
    ofstream f_alllog("logs/sall.log",ios::app);
    f_alllog<<cache<<endl;
}
void allog_s(char *cache)
{
    ofstream f_alllog("logs/all.log",ios::app);
    f_alllog<<cache;
}
void refresh_allog()
{
   ofstream f_alllog("logs/all.log");
   f_alllog.close();
}
void refresh_sallog()
{
   ofstream f_alllog("logs/sall.log");
   f_alllog.close();
}
bool positive_number(int number)
{
    allog("positive_number 1p");
    if(number<0)return false;
    else return true;
}
bool p_o_n()
{
    allog("p_o_n 0p");
    char cache[BASIC_CACHE];
    cin.getline(cache,BASIC_CACHE);
    if(!strcmp(cache,"yes"))return true;
    if(!strcmp(cache,"y"))return true;
    if(!strcmp(cache,"YES"))return true;
    if(!strcmp(cache,"Y"))return true;
    return false;
}
