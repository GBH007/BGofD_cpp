#ifndef ACTION_H
#define ACTION_H
#include "MIL.h"
using namespace std;
char* sort_comand(char *comand);        //возврашает первое ключевое слово изменяет строку убирая ключево слово
void action();
void go(display *m,c_map *t_map,char *comand);
void go_up(display *m,c_map *t_map);
void go_down(display *m,c_map *t_map);
void go_left(display *m,c_map *t_map);
void go_right(display *m,c_map *t_map);
#endif /*ACTION_H*/
