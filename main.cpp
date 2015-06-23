#include <iostream>  //cin, cout
#include "dice.hpp"
#include "MyFunctions.hpp" //initialization
#include <stdlib.h> //rand, srand
#include <stdio.h>  //null
#include <time.h> //time
#include <vector>
//using namespace std; from dice.hpp
#include "RollParams.hpp"
#include "RollResults.hpp"
#include "Sequence.h"
#include "assert.hpp"
int main()
{
    //seeds srand
    Initialize();

    // Sequence C'tor Parameters
    //PASS VALUE VECTORS
    std::vector<uint16_t>* VecValues0 = new std::vector<uint16_t>{0};
    std::vector<uint16_t>* VecValues1 = new std::vector<uint16_t>{1};
    std::vector<uint16_t>* VecValues12 = new std::vector<uint16_t>{1,2};
    std::vector<uint16_t>* VecValues123 = new std::vector<uint16_t>{1,2,3};
    std::vector<uint16_t>* VecValues1to6 = new std::vector<uint16_t>{1,2,3,4,5,6};
    // Iterations for accuracy
    uint32_t numIterations = 100000;
    //NUM DICE VECTORS
    std::vector<uint16_t> NumDiceParam;
    NumDiceParam.push_back(20);
    NumDiceParam.push_back(0);
    //NumDiceParam.push_back(0);
    //Construct Input PassValues Vector
    std::vector<std::vector<uint16_t>*> SequencePassValues;
    SequencePassValues.push_back(VecValues123);
    SequencePassValues.push_back(VecValues123);
    //SequencePassValues.push_back(VecValues123);
    // Construct Input ReRoll Vector
    std::vector<std::vector<uint16_t>*> SequenceReRollValues;
    SequenceReRollValues.push_back(VecValues1);
    SequenceReRollValues.push_back(VecValues1);
    //SequenceReRollValues.push_back(VecValues1);
    // Number of rolls to check vector lengths
    uint16_t NumberRolls = 2;

    //TestCode
    /*
    Sequence TestCodeSequence = TestCode(SequencePassValues,
                                 NumDiceParam,
                                 NumberRolls,
                                 numIterations);
    std::vector<RollParams> TestCodeSeqParam = TestCodeSequence.GetParamsVector();

    if(TestCodeSeqParam.size()>0)
    {
        RollParams TestCodeParams = TestCodeSeqParam.front();
    }
 */
    Sequence testSequence = Sequence(SequencePassValues,
                                     SequenceReRollValues,
                                     NumDiceParam,
                                     NumberRolls,
                                     numIterations);

    testSequence.Print();
    size_t TestSeqSize = testSequence.GetResultsVector()->size();
    float results = testSequence.BatchRoller();

    cout << "% pass of rolls: " << results << endl;

    uint16_t repeat=1;
    while(repeat)
    {
        Initialize();
        testSequence.BatchRoller();
        cout << "again? 1/0" << endl;
        cin >> repeat;
    }
    // Pause
    while (1){};

    return 0;
}
