#ifndef ROLLPARAMS_HPP
#define ROLLPARAMS_HPP

#include "dice.hpp"
#include <stdint.h> //uint types, //TODO: find where they actually are
//#include <stdio.h>  //null
#include <vector>
using namespace std;

class RollParams
{
    public:
        /** Default constructor */
        RollParams();

        /** Parameter driven construct */
        RollParams( uint32_t NumDiceVal,
                    diceType DieTypeVal,
                    std::vector<uint16_t>* ReRollValues,
                    std::vector<uint16_t>* PassValues);

        /** Default destructor */
        ~RollParams();

        /** Copy constructor
         *  \param other Object to copy from
         */
        RollParams(const RollParams& other);

        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        RollParams& operator=(const RollParams& other);

        /** Access dieType
         * \return The current value of dieType
         */
        diceType GetdieType() const { return m_DieType; }

        /** Set dieType
         * \param val New value to set
         */
        void SetdieType(diceType val) { m_DieType = val; }

        /** Access numRolls
         * \return The current value of numRolls
         */
        uint32_t GetNumDice() const { return m_NumDice; }

        /** Set numRolls
         * \param val New value to set
         */
        void SetNumDice(uint32_t val) { m_NumDice = val; }

        /** Access rerollValues
         * \return The current value of rerollValues
         */
        vector<uint16_t>* GetRerollValues() const { return m_ReRollValues; }

        /** Set rerollValues
         * \param val New value to set
         */
        void SetRerollValues(vector<uint16_t>* val) { m_ReRollValues = val; }

        /** Set PassValues
         * \param val New value to set
         */
        void SetPassValues(vector<uint16_t>* val) { m_PassValues = val; }

        /** Access passValues
         * \return The current value of passValues
         */
        vector<uint16_t>* GetPassValues() const { return m_PassValues; }

        void Print() const;

    protected:
    private:
        diceType m_DieType;// = diceType::d6Die; //!< Member variable "dieType"
        uint32_t m_NumDice; //!< Member variable "numRolls"
        vector<uint16_t>* m_ReRollValues; //!< Member variable "rerollValues"
        vector<uint16_t>* m_PassValues; //!< Member variable "passValues"

};

#endif // ROLLPARAMS_HPP
