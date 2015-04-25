#include <stdint.h>
#include <vector>
#include "RollParams.hpp"
#include "RollResults.hpp"
#include "Status.hpp"
#include "MyFunctions.hpp"

#ifndef SEQUENCE_H
#define SEQUENCE_H


class Sequence
{
    public:
        float RunSequence();

        double BatchRoller(uint32_t numIterations,
                   std::vector<RollParams*>* pRollParams,
                   std::vector<RollResults*>* pRollResults);

        //Rolls numRolls number of
        double BatchRoller();


        /** Default constructor */
        Sequence();
        /** Parameter constructor */
        Sequence(std::vector<std::vector<uint16_t>*> VecPassingValues,
                 std::vector<std::vector<uint16_t>*> VecReRollValues,
                 std::vector<uint16_t> NumDice,
                 uint16_t NumRolls,
                 uint32_t NumIterations);
        /** Default destructor */
        virtual ~Sequence();

        /** Copy constructor
         *  \param other Object to copy from
         */
        Sequence(const Sequence& other);

        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Sequence& operator=(const Sequence& other);

        /** Access m_NumRolls
         * \return The current value of m_NumRolls
         */
        uint32_t GetNumRolls() { return m_NumRolls; }

        /** Set m_NumRolls
         * \param val New value to set
         */
        void SetNumDice(uint32_t val) { m_NumRolls = val; }

        /** Access m_NumIterations
         * \return The current value of m_NumIterations
         */
        uint32_t GetNumIterations() { return m_NumIterations; }

        /** Set m_NumIterations
         * \param val New value to set
         */
        void SetNumIterations(uint32_t val) { m_NumIterations = val; }

        /** Access m_ResultsVector
         * \return The current value of m_ResultsVector
         */
        std::vector<RollParams>* GetParamsVector() const { return m_ParamsVector; }
        /** Set m_ResultsVector
         * \param val New value to set
         */
        void SetResultsVector(std::vector<RollResults>* val) { m_ResultsVector = val; }
        /** Access m_ResultsVector
         * \return The current value of m_ResultsVector
         */
        std::vector<RollResults>* GetResultsVector() const { return m_ResultsVector; }
        /** Set m_ResultsVector
         * \param val New value to set
         */
        void SetParamsVector(std::vector<RollParams>* val) { m_ParamsVector = val; }

        /** Print members data
        */
        void Print();

    protected:
    private:
        uint32_t m_NumRolls; //!< Member variable "m_NumRolls"
        uint32_t m_NumIterations; //!< Member variable "m_NumIterations"
        std::vector<RollParams>* m_ParamsVector; //!< Member variable "m_ResultsVector"
        std::vector<RollResults>* m_ResultsVector; //!< Member variable "m_ResultsVector"
};

#endif // SEQUENCE_H
