#ifndef THING_H
#define THING_H
#include "MIL.h"
using namespace std;
class thing
{
    private:
        int type;           //тип вещи 0-основная рука(кинжал) 1-вторичная рука(манускрипт/фолиант) 2-голова(повязка/шлем) 3-грудь(куртка/нагрудник) 4-ноги(штаны/поножи) 5-стопы(ботинки)
        int HP,rHP;         //HP количетво очков здоровья даваемое вещью rHP количетво очков здоровья востанавливаемых за ход даваемое вещью
        int MP,rMP;         //MP количетво очков маны даваемое вещью rMP количетво очков маны востанавливаемых за ход даваемое вещью
        int FR;             //ярость очки повышающие урон
        int ID;             //номер предмета в базе даных
    public:
        thing(int id);
        thing();
        ~thing();
        char* return_type_char();
        char* return_hp_char();
        char* return_rhp_char();
        char* return_mp_char();
        char* return_rmp_char();
        char* return_fr_char();
        char* return_id_char();
        int return_type_int();
        int return_hp_int();
        int return_rhp_int();
        int return_mp_int();
        int return_rmp_int();
        int return_fr_int();
        int return_id_int();
        void reconstruct(int id);
        void tt_0();        //entity.h
        bool cw0();         //false если все соответсвует норме true иначеж

        thing &operator =(thing &_thing)
        {
            allog("thing &operator = 1p");
            type=_thing.return_type_int();
            HP=_thing.return_hp_int();
            rHP=_thing.return_rhp_int();
            MP=_thing.return_mp_int();
            rMP=_thing.return_rmp_int();
            FR=_thing.return_fr_int();
            ID=_thing.return_id_int();
            return *this;
        };
};
#endif /*THING_H*/
