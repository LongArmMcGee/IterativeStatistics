//#include <iostream>  //cin, cout
//#include <vector>
//#include "RollParams.hpp"
//#include "RollResults.hpp"
//using namespace std;

#ifndef DICE_HPP_INCLUDED
#define DICE_HPP_INCLUDED

enum diceType{
  d6Die = 1,
  scatter,
  artillery
};

enum d6Die{
    side1=1,
    side2,
    side3,
    side4,
    side5,
    side6
};

enum scatterDie{
    hit1=1,
    hit2,
    arrow1,
    arrow2,
    arrow3,
    arrow4
};

enum artilleryDie{
    misfire=1,
    value2,
    value4,
    value6,
    value8,
    value10
};

/*
std::ostream& operator<<(std::ostream& out, const d6Die value){
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(value){
        PROCESS_VAL(ErrorA);
        PROCESS_VAL(ErrorB);
        PROCESS_VAL(ErrorC);
    }
#undef PROCESS_VAL

    return out << s;
}
*/

#endif // DICE_HPP_INCLUDED
