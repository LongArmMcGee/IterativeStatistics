#include <iostream>  //cin, cout
#include "RollResults.hpp"


RollResults::RollResults() :
    NumPassRolls(0),
    NumFailRolls(0)
{
}


RollResults::~RollResults()
{
    //dtor
}


void RollResults::Print()
{
    // Print header and
    cout << "RollResults Members" << endl;
    cout << "------------------" << endl;
    cout << "NumPassRolls: " << NumPassRolls << endl;
}
