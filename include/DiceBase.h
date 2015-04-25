#include "dice.cpp"

#ifndef DICEBASE_H
#define DICEBASE_H


class DiceBase
{
    public:
        /** Default constructor */
        DiceBase() {}
        virtual ~DiceBase()
   //     virtual RollDice()
    protected:
    private:
        diceType m_DiceType; //!< Member variable "m_DiceType"
};

#endif // DICEBASE_H
