#ifndef MIF_H
#define MIF_H
#include "MIL.h"
using namespace std;
const int BASIC_CACHE=100;
bool read_sym(int &sym);
bool read_sym(int &sym, ifstream &fi);
void allog(char *cache);
void allog(int cache);
void sallog(char *cache);
void sallog(int cache);
void allog_s(char *cache);      //allog без переноса строки
void refresh_allog();           //очистка файла лога
void refresh_sallog();
bool positive_number(int number);   //false если number <0
bool p_o_n();                   //true(yes,y) false(another)
#endif /*MIF_H*/
