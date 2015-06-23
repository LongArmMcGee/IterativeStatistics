#include "MyFunctions.hpp"
#include "Sequence.h"
#include "Assert.hpp"
#include "CSVFileHandler.hpp"

void Initialize()
{
    // This initializes the random number generator with a seed
    // (provided by current time?). This should only do once per program execution.
    srand(time(NULL));
}

/*
std::vector<RollParams*> PromptSequence(uint32_t& numIter)
{
// TODO (MWadswo#1#05/31/14): refactor prompts to a type checking (template?) function

    cout << "Welcome to Iterative Statistics!" << endl;

    // TODO (MWadswo#1#07/27/14): make use of the iterations param. I'm only running the rolls once right now
    //number of iterations (accuracy)
    cout << endl << "Enter the number of iterations for this sequence:";
    cin >> numIter;

    //number of dice rolls made in this sequence
    //ie: roll to hit, to wound, armor save will be 3
    uint16_t uNumRolls;
    cout << endl << "Enter number of rolls in this sequence:";
    cin >> uNumRolls;

    //vector to hold roll params
    std::vector<RollParams*> SequenceParams;

    //construct param structs
    for(int8_t i=0; i<uNumRolls; i++)
    {
        //constructor prompts and fills in struct vars
        RollParams* pPromptParams = new RollParams();
        //first roll special case
        if(i==0)
        {
            while(pPromptParams->numRolls==0)
            {
                cout << "The first roll must have greater than 0 dice rolled" << endl;
                pPromptParams = new RollParams();
            }
        }

        //add new params to vector
        SequenceParams.push_back(pPromptParams);
    }

    return SequenceParams;
}
*/
/*RollResults* RollD6(RollParams* pRollParams, RollResults* pPrevResults)
{
    //Return value to be assigned later
    RollResults* pReturnResults = new RollResults();
    //RollResults* ResultsReturn = &returnResults;

    //Used in for loop to store generated random value
    uint8_t randVal;

    //use numRolls from arg provided results struct 'previous' results if numRolls==0
    //this provides the 'sequence' functionality by using previous rolls results
    if(pRollParams->numRolls==0)
        pRollParams->numRolls=pPrevResults->ulPassRolls;

    //'dice rolling' loop
    for(uint32_t i=0; i<pRollParams->numRolls; i++)
    {
        //generate random number values 1-6
        randVal = rand() % 6 + 1;
        for(int i=0; i<pRollParams->passValues.size(); i++)
        {
            if(randVal==pRollParams->passValues[i])
                pReturnResults->ulPassRolls++;   //increment ulPassRolls if passing roll is made
        }
    }
    return pReturnResults;
};
*/

RollResults& RollD6(RollParams& ParamsInput, RollResults& PrevResults)
{
    //Return value to be assigned later
    RollResults ReturnResults = RollResults();
    // Values which will be considered a 'passing' roll
    const vector<uint16_t> PassValues = *(ParamsInput.GetPassValues());
    //Used in for loop to store generated random value
    uint8_t randVal;
    // Grab NumDice from RollParams input
    uint16_t NumDiceToRoll = ParamsInput.GetNumDice();

    //use the number of passing rolls from previous results if NumDice==0.
    // This is used to chain rolls together. Consider breaking this out into a
    // seperate bool member...
    if(ParamsInput.GetNumDice()==0){
            //ASSERT(false);
        // 2nd roll shows PrevResults with 0 PassRolls!
        // Grab previous results passing rolls to use
        NumDiceToRoll = PrevResults.GetulPassRolls();
        //cout << "RollD6 PrevResults.GetulPassRolls(): " << NumDiceToRoll << endl;
    }

    //'dice rolling' loop
    for(uint32_t i=0; i<NumDiceToRoll; i++)
    {
        //generate random number values 1-6
        randVal = rand() % 6 + 1;

        // Debug code to record rand values
        CSVFileHandler::PrintUintToCSV(randVal);

        for(uint16_t i=0; i<PassValues.size(); i++)
        {
            if(randVal==(PassValues[i]))//passValues[i])
            {
                //ASSERT(false); // I switched passvalues to private, check the above and below statemetn. Consider iterator.
                ReturnResults.IncPassRolls();   //increment ulPassRolls if passing roll is made
                //cout << "Inc Results" << endl;
            }
        }
    }
    return ReturnResults;
};

RollResults RollDice(RollParams& Params, RollResults& Results)
{
    RollResults ReturnResults = RollResults();

    switch (Params.GetdieType())
    {
        case d6Die:
            ReturnResults = RollD6(Params, Results);
            break;
    }

    return ReturnResults;
};

//analyze results (and initial params) to determine relevant statistical data
void ProcessResults(std::vector<RollParams*> pParams, std::vector<RollResults*>* pResults)
{
//    uint8_t pParams->front()

};


//NOTE: RunSequence was moved to the Sequence class under the same name and different signature
//takes results vector and param vector and runs a loop to roll dice
/*float RunSequence(std::vector<RollParams*>* pRollParams,
                  std::vector<RollResults*>* pRollResults)
{
    // Iterate through the RollParams and ROLL THE DICE for each rollparam
    // and store into SequenceResults vector        diceType dieType;// = diceType::d6Die; //!< Member variable "dieType"
        uint32_t numRolls; //!< Member variable "numRolls"
        vector<uint16_t> rerollValues; //!< Member variable "rerollValues"
        vector<uint16_t> passValues; //!< Member variable "passValues"
    std::vector<RollParams*>::iterator itParams;
    std::vector<RollResults*>::iterator itResults;
    itResults = pRollResults->begin();
    itParams = pRollParams->begin();

    // loop through params vector
    for ( uint16_t n=0; n != pRollParams->size(); n++)
    {
        // CAN'T deref iterator to empty vector!
        // This means roll dice can't be called with the iterator pointing to
        // an empty results vector. Hence, the special n==0 case.
        if(n==0)
        {
            RollResults* pRollResultsFirst = new RollResults();
            RollResults* pResults = RollDice(*itParams, pRollResultsFirst);

            pRollResults->push_back(pResults);

            uint32_t testpassrolls = pResults->ulPassRolls;
            uint32_t testVecPassRolls = (*pRollResults)[0]->ulPassRolls;
#ifdef _DEBUG
//            cout << "First Results: " << static_cast<uint16_t>(testpassrolls) << endl;
//            cout << "First Results via vec: " << static_cast<uint16_t>(testVecPassRolls) << endl;
#endif // _DEBUG
        }
        else
        {
            pRollResults->push_back(RollDice(*itParams,(*pRollResults)[n-1]));
        }

        itParams++;
        itResults++;
    }

    RollParams* pTestOutParams  = pRollParams->front();
    //if((pRollResults->empty() != true))
    //{
    //skip iterator, get reference to vector contents
    RollResults* pTestOutResults = pRollResults->back();
    //}

    uint16_t firstNumRolls = pTestOutParams->numRolls;
    uint16_t lastPassRolls = static_cast<uint16_t>(pTestOutResults->ulPassRolls);

//        cout << "Sequence Results" << endl;
//        cout << "----------------" << endl;
//        cout << "Params numRolls: " << firstNumRolls << endl;
//        cout << "Results ulPassRolls: " << lastPassRolls << endl;

    // Float types so division will not be truncated
    float fPercentPass = 0;
    float fNumRolls = ((*pRollParams)[0]->numRolls);
    float fPassRolls =((pRollResults->back())->ulPassRolls);

    fPercentPass = fPassRolls / fNumRolls ;

    return fPercentPass;
};
*/

/** \brief  Helper function used to calculate an array of floats
 *
 * \param   float* pArray - A pointer to the arra
 * \param   uint32_t ArrayLength - Length of array
 * \return  double - Double precision value (prevent error during repeated sums)
 *
 */
double CalcArrayMean(double* pArray, uint32_t ArrayLength)
{
    double Sum=0.0;

    for(int i=0; i<ArrayLength; i++)
    {
        Sum += pArray[i];
    }

    double Mean = Sum / ArrayLength;

    return Mean;
};

/** \brief  This implements the iterations used to gain accuracy by
 *          repeatedly calling RunSequence and averaging the results.
 *          This is done by..
 *              -Running batches of 10,000 RunSequence calls
 *              -Averaging and saving these averaged results in an array
 *              -Finally performing a weighted (in case the number of iterations
*                is not an even 10,000) average on all results
 *
 * \param   numIterations Total number of iterations to be run
 * \param   pRollParams Pointer to RollParams struct
 * \param   pRollResults Pointer to RollResults struct
 * \return
 *
 */
 /*double BatchRoller(uint32_t numIterations,
                   std::vector<RollParams*>* pRollParams,
                   std::vector<RollResults*>* pRollResults)
{
    // Only do rolls in increments of 10k
    uint32_t numBatches = (numIterations/10000);
// TODO (MWadswo#3#12/13/14): Add assert mechanism and check for numBatches == 0

    // Averaged results of batches
    float Results[numBatches];
    // Results of each sequence run by full sized (10,000 iteration) batches
    float BatchSequenceResults[10000];
    // value to collect results
    double dReturnVal = 0.0;

// why use batches? prevent memory overrun.. determine memory usage per call of roll dice
// and multiply it by the number of rolls in the sequence and finally by the number of
// iterations to be done and use this number to calculate the number of rolls which will
// give the required memory.
    uint32_t IterationsCounter = numIterations;
    double SummedAverage = 0.0;

    //while(IterationsCounter > 0){
    for(int BatchCounter=numBatches; BatchCounter>0; BatchCounter--)
    {
        //    if(IterationsCounter > 10000){
        for(int i=0; i<10000; i++)
        {
            BatchSequenceResults[i] = RunSequence(pRollParams, pRollResults);
        }
        SummedAverage+= CalcArrayMean(BatchSequenceResults, 10000);
        IterationsCounter -= 100000;
#ifdef _DEBUG
        cout << "SummedAverage: " << SummedAverage << endl;
#endif // _DEBUG
        //    }
//                else{
//                    uint32_t savedNumIter = IterationsCounter;
//                    for(int i=0; i < IterationsCounter;i++){
//                        BatchSequenceResults[i] = RunSequence(pRollParams, pRollResults);
//                    }
//                    IterationsCounter = 0;
//                    dReturnVal += CalcArrayMean(BatchSequenceResults, savedNumIter);
//                }
    }
    dReturnVal = SummedAverage / numBatches;

    return dReturnVal;
};
*/


Sequence TestCode(std::vector<std::vector<uint16_t>> VecPassingValues,
                   std::vector<uint16_t> NumDice,
                   uint16_t NumRolls,
                   uint32_t NumIterations)
{
//    cout << "Test Code/n";
//    float pArray[10000];
//    std::fill(pArray, pArray+1000,.22222299999f);
//    std::fill(pArray+1000, pArray+2000,.22333399999f);
//    std::fill(pArray+2000, pArray+3000,.22111199999f);
//    std::fill(pArray+3000, pArray+4000,.22111199999f);
//    std::fill(pArray+4000, pArray+5000,.22333399999f);
//    std::fill(pArray+5000, pArray+10000,.22222299999f);
//    double Mean = CalcArrayMean(pArray, 10000);
//    printf("Mean %f/n", Mean);
//    cout << ".5, .5:" << Mean;
//
////    float resultsSequence = RunSequence(pSequenceParams, pSequenceResults);
//
//    cout << "Size of RollResults: "  << sizeof(RollResults) << endl;
//
//    cout << __cplusplus << endl;
//    cout << "End Test Code";
/*
    std::vector<uint16_t> PassValues12;
    PassValues12.push_back(1);
    PassValues12.push_back(2);

    RollResults EmptyResults = RollResults();
    std::vector<RollResults> ResultsVec;
    ResultsVec.push_back(EmptyResults);


    RollParams mainParams = RollParams( 2,
                            diceType::scatter,
                            PassValues12);
    std::vector<RollParams> ParamsVec;
    ParamsVec.push_back(mainParams);

    Sequence NewSequence;
    NewSequence.SetNumIterations(NumIterations);
    NewSequence.SetNumRolls(NumRolls);
    NewSequence.SetParamsVector(ParamsVec);
    NewSequence.SetResultsVector(ResultsVec);
*/

}

