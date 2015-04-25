#include "RollParams.hpp"


#ifndef ROLLRESULTS_HPP
#define ROLLRESULTS_HPP

class RollResults
{
    public:
        /** Default constructor */
        RollResults();
        /** Default destructor */
        virtual ~RollResults();
        /** Access ulPassRolls
         * \return The current value of ulPassRolls
         */
        uint32_t GetulPassRolls() { return NumPassRolls; }
        /** Set ulPassRolls
         * \param val New value to set
         */
        void SetulPassRolls(uint32_t val) { NumPassRolls = val; }
        /** Access ulFailRolls
         * \return The current value of ulFailRolls
         */
        uint32_t GetulFailRolls() { return NumFailRolls; }
        /** Set ulFailRolls
         * \param val New value to set
         */
        void SetulFailRolls(uint32_t val) { NumFailRolls = val; }
        /** Access uResults
         * \return The current value of uResults
         */
       // uint16_t* GetuResults() { return uResults; }
        /** Set uResults
         * \param val New value to set
         */
        //void SetuResults(uint16_t val) { uResults = val; }
        /** Set Print members data
         */
        void Print();
        void IncPassRolls() { NumPassRolls++; }

        //uint16_t uResults[6]; //!< Member variable "uResults"  unnecessary, too much memory

    protected:
    private:
        uint32_t NumPassRolls; //!< Member variable "ulPassRolls"
        uint32_t NumFailRolls; //!< Member variable "ulFailRolls"

};

#endif // ROLLRESULTS_HPP
