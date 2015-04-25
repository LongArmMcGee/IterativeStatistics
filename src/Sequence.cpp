#include "Sequence.h"
#include "dice.hpp"
#include "RollParams.hpp"
#include "RollResults.hpp"
#include "assert.hpp"


Sequence::Sequence()
{
    //ctor
    cout << "default ctor";
}

/** \brief  This parameterized constructor is used to create and
 *          intialize a complete sequence object.
 *
 * \param   VecPassingValues - Vector of vectors used as passing values
 *          for each roll that makes the larger whole of the sequence
 * \param   NumDice - Vector for number of dice per roll of sequence
 * \param   NumRolls - Number of rolls which make up the sequence.
            Used to know how many params are required.
 * \param   NumIteration - Sets sequence member m_NumIterations
 *
 * \return  None - Constructor
 *
 */
Sequence::Sequence(std::vector<std::vector<uint16_t>*> VecPassingValues,
                   std::vector<std::vector<uint16_t>*> VecReRollValues,
                   std::vector<uint16_t> NumDice,
                   uint16_t NumRolls,
                   uint32_t NumIterations):
m_NumRolls(NumRolls),
m_NumIterations(NumIterations)
{
    //RollResults EmptyResults = RollResults();
    std::vector<RollResults>* ResultsVec = new  std::vector<RollResults>;
    //ResultsVec->push_back(EmptyResults);
    SetResultsVector(ResultsVec);

    // Check if parameters are consistent
    ASSERT(VecPassingValues.size() == NumRolls);
    ASSERT(VecReRollValues.size() == NumRolls);
    ASSERT(NumDice.size() == NumRolls);
    ASSERT(NumIterations>0);

    // Create & Fill RollParams vec to assign to m_ParamsVector
    vector<RollParams>* TempVec = new vector<RollParams>;
    // Fill Params Vector
    for(int i=0; i<NumRolls; i++)
    {
        RollParams* ParamsVecInput = new RollParams(NumDice[i],
                                              diceType::d6Die,
                                              VecReRollValues[i],
                                              VecPassingValues[i]);
    TempVec->push_back(*ParamsVecInput);
    }

    SetParamsVector(TempVec);
}

Sequence::~Sequence()
{
    //dtor
}

Sequence::Sequence(const Sequence& other)
{
    //copy ctor
    // Review this method before using
    bool Reviewed = false;
    ASSERT(Reviewed);
}

Sequence& Sequence::operator=(const Sequence& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    //assignment operator
    //Params
    auto LhsParamsVec = this->GetParamsVector();
    auto RhsParamsVec = rhs.GetParamsVector();
    //Results
    auto LhsResultsVec = this->GetResultsVector();
    auto RhsResultsVec = rhs.GetResultsVector();
// Let's see if these will still be handled on their own?
//    uint32_t m_NumRolls; //!< Member variable "m_NumRolls"
//        uint32_t m_NumIterations; //!< Member variable "m_NumIterations"
    for (auto i = RhsParamsVec->begin(); i!=RhsParamsVec->end(); i++)
    {
        LhsParamsVec->push_back(*i);
    }

    for (auto i = RhsResultsVec->begin(); i!=RhsResultsVec->end(); i++)
    {
        LhsResultsVec->push_back(*i);
    }

    return *this;
}

float Sequence::RunSequence()
{
    // Iterate through the RollParams and ROLL THE DICE for each rollparam
    // and store into SequenceResults vector
    std::vector<RollParams>::iterator itParams;
    std::vector<RollResults>::iterator itResults;
    itParams = GetParamsVector()->begin();
    itResults = GetResultsVector()->begin();

    // loop through params vector
    for ( uint16_t n=0; n != GetParamsVector()->size(); n++)
    {
        // CAN'T deref iterator to empty vector!
        // This means roll dice can't be called with the iterator pointing to
        // an empty results vector. Hence, the special n==0 case.
        if(n==0)
        {
            RollResults RollResultsFirst = RollResults();
            RollResults Results = RollDice(*itParams, RollResultsFirst);

            m_ResultsVector->push_back(Results);
            //cout << endl << "RunSequence Roll Results" << endl;
            //Results.Print();
            uint16_t testsize = m_ResultsVector->size();
            //cout << "ResultsVec#" << n << " Size: " << testsize;// << m_ResultsVector->size();
            //(m_ResultsVector->at(n)).Print();
        }
        else
        {
            //ASSERT(false); // Make this result vector assigned via the set and use a heap var
            RollResults Results = RollDice(*itParams,(*m_ResultsVector)[n-1]);
            m_ResultsVector->push_back(Results);

            //cout << endl << "RunSequence Roll Results";
            //Results.Print();

        }
        //*(GetParamsVector()).Print();

        itParams++;
        itResults++;
    }

    // Float types so division will not be truncated
    float fPercentPass = 0;
    float fNumRolls = GetParamsVector()->front().GetNumDice();//numRolls);
    float fPassRolls = GetResultsVector()->back().GetulPassRolls();//ulPassRolls;

    fPercentPass = fPassRolls / fNumRolls ;



    return fPercentPass;
}


/** \brief  This implements the iterations used to gain accuracy by
 *          repeatedly calling RunSequence and averaging the results.
 *          This is done by..
 *              -Running batches of 10,000 RunSequence calls
 *              -Averaging and saving these averaged results in an array
 *              -Finally performing a weighted (in case the number of iterations
 *               is not an even 10,000) average on all results
 *
 * \return
 *
 */
double Sequence::BatchRoller()
{
    // Only do rolls in increments of 10k
    uint32_t numBatches = (m_NumIterations/10000);

    ASSERT(numBatches > 0);

    // Results of each sequence run by full sized (10,000 iteration) batches
    double BatchSequenceResults[10000];
    // value to collect results
    double dReturnVal = 0.0;

    uint32_t IterationsCounter = m_NumIterations;
    double SummedAverage = 0.0f;

    //while(IterationsCounter > 0){
    for(int BatchCounter=numBatches; BatchCounter>0; BatchCounter--)
    {
        //    if(IterationsCounter > 10000){
        for(int i=0; i<10000; i++)
        {
            BatchSequenceResults[i] = RunSequence();
        }
        double BatchMean = CalcArrayMean(BatchSequenceResults, 10000);
        SummedAverage+= BatchMean;
#ifdef _DEBUG
        cout << "BatchMean: " << BatchMean << endl;
#endif // _DEBUG
    }
    dReturnVal = SummedAverage / numBatches;

    return dReturnVal;
};

void Sequence::Print()
{
    cout << endl << "Sequence Print" ;
    cout << endl << "--------------" << endl;
    //Print Parameters vector
    vector<RollParams> PVec = *(GetParamsVector());
    if(PVec.size() == 0)
    {
        cout << "Empty Params Vector" << endl;
    }
    for(std::size_t i=0; i<PVec.size();i++)
    {
        cout << "Params Vec #" << i << endl;
        PVec[i].Print();
    }
    // Print Results Vector
    vector<RollResults> RVec = *(GetResultsVector());
    if(RVec.size() == 0)
    {
        cout << "Empty Results Vector" << endl;
    }
    for(std::size_t i=0; i<RVec.size();i++)
    {
        cout << "Results Vec #" << i << endl;
        RVec[i].Print();
    }
    cout << endl << "**************" << endl;
}
