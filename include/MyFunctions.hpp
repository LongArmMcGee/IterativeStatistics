#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_HPP_INCLUDED

#include <stdlib.h> //rand, srand
#include <stdio.h>  //null
#include <time.h>   //time
#include <vector>
#include <iostream>  //cin, cout

#include "RollParams.hpp"
#include "RollResults.hpp"
#include "Status.hpp"
//test
#include "Sequence.h"

using namespace std;

//random # initialization
void Initialize();

//process statistics
void ProcessResults(std::vector<RollParams*>*, std::vector<RollResults*>*);

/*  MOVED to Sequence Class 1.10.15
//run sequence
float RunSequence(std::vector<RollParams*>* pRollParams,
                  std::vector<RollResults*>* pRollResults);
*/

std::vector<RollParams*> PromptSequence(uint32_t& numIter);

double CalcArrayMean(double* pArray, uint32_t ArrayLength);

void SequenceConstructor();

RollResults* RollDice(RollParams* pRollParams, RollResults* pRollResults);
//Roll based on Params
RollResults* RollD6(RollParams* pRollParams, RollResults* pRollResults);
//Roll based on prev results
RollResults* RollD6(RollResults* pRollResults);
RollResults* RollArtillery(RollParams* pRollParams);
RollResults* RollScatter(RollParams* pRollParams);

//Not with shit pointers
RollResults RollDice(RollParams& RollParams, RollResults& RollResults);
RollResults& RollD6(RollParams& RollParams, RollResults& PrevResults);

Sequence TestCode(std::vector<std::vector<uint16_t>> VecPassingValues,
                   std::vector<uint16_t> NumDice,
                   uint16_t NumRolls,
                   uint32_t NumIterations);

void AppendToCSV(uint16_t);
#endif // FUNCTIONS_HPP_INCLUDED
