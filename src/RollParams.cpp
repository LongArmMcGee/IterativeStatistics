#include "RollParams.hpp"
#include <iostream>  //cin, cout
#include <vector>
#include "Assert.hpp"

RollParams::RollParams(){

        uint8_t ubDiceType;
        cout << endl << "Die type?" << endl << "d6: 1" << endl;
        cin >> ubDiceType;

        //assign dieType for rollparams struct based on input
        diceType rollParamDieType=d6Die;
        if(ubDiceType==1)// TODO (MWadswo#1#06/01/14): add switch statement for other dice types
            rollParamDieType=d6Die;

        //prompt and assign number of dice to roll
        uint16_t uNumDice;
        cout << "Number of dice? 0 uses prev rolls results" << endl;
        cin >> uNumDice;

        int tempInt;
        cout << "Passing values? 0 to finish" << endl;
        do{
// TODO (MWadswo#3#12/13/14): Assert on bad input
            cin >> tempInt;
            if(tempInt<7 ){
               if(tempInt>0){
                m_PassValues->push_back(tempInt);
               }
            }
        } while(tempInt != 0);

        m_DieType = rollParamDieType;
        m_NumDice = uNumDice;
}

RollParams::RollParams(uint32_t NumDiceVal,
                       diceType DiceTypeVal,
                       std::vector<uint16_t>* ReRollValuesVal,
                       std::vector<uint16_t>* PassValuesVal):
m_NumDice(NumDiceVal),
m_DieType(DiceTypeVal),
m_ReRollValues(ReRollValuesVal),
m_PassValues(PassValuesVal)
{
// TODO (MWadswo#3#12/13/14): Assert check input values
//    SetNumRolls(NumDiceVal);
//    SetdieType(DiceTypeVal);
//    SetPassValues(PassValuesVal);
    cout << "RollParams C'tor" << endl;
    this->Print();
}

RollParams::~RollParams()
{
    //dtor
}

RollParams::RollParams(const RollParams& other)
{
    SetdieType(other.GetdieType());
    SetNumDice(other.GetNumDice());

/*    vector <uint16_t> PassVals;
    auto OtherPassVals = other.GetPassValues();
    for(auto i : OtherPassVals)
    {
        PassVals.push_back(i);
    }
    SetPassValues(PassVals);

    vector <uint16_t> ReRollVals;
    auto OtherReRollVals = other.GetRerollValues();
    for(auto i : OtherReRollVals)
    {
        ReRollVals.push_back(i);
    }

    SetRerollValues(ReRollVals);*/
// Are the members being over written because the roll params object cant be
// dynamically sized? So the 'vector' member being saved is really only a reference
// or something? As compared to what I expected: The full vector container and
// all of it's data contained inside the roll params object. This can't happen
// because the roll params object would have to be dynamically sized with the
// vector member.
// I came to this conclusion because if i take the following code
/*
    vector<uint16_t> tempVec;
    tempVec = other.GetRerollValues();
    SetRerollValues(tempVec);
    tempVec = other.GetPassValues();
    SetPassValues(tempVec);*/
// and reverse the order of the Pass/reroll vec/set the vector data is switched
// between Pass/Reroll and the 2nd one set is empty.
    vector<uint16_t>* NewPassVals = new vector<uint16_t>(*(other.GetPassValues()));
    vector<uint16_t>* NewReRollVals = new vector<uint16_t>(*(other.GetRerollValues()));

    SetPassValues(NewPassVals);
    SetRerollValues(NewReRollVals);

/*    cout << endl << "From Copy Ctor:" << endl;
    cout << "Other:" << endl;
    other.Print();
    cout << "This:" << endl;
    Print();
*/
}

RollParams& RollParams::operator=(const RollParams& rhs)
{
    // Fix this method before using
    bool Reviewed = false;
    ASSERT(Reviewed);

    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    //assignment operator
    this->SetdieType(rhs.GetdieType());
    this->SetNumDice(rhs.GetNumDice());;
    //Params
    auto LhsReRollsVec = this->GetRerollValues();
    auto RhsReRollsVec = rhs.GetRerollValues();
    //Results
    auto LhsPassValsVec = this->GetPassValues();
    auto RhsPassValsVec = rhs.GetPassValues();
// Let's see if these will still be handled on their own?
//    uint32_t m_NumRolls; //!< Member variable "m_NumRolls"
//        uint32_t m_NumIterations; //!< Member variable "m_NumIterations"
    for (auto i = RhsReRollsVec->begin(); i!=RhsReRollsVec->end(); i++)
    {
        LhsReRollsVec->push_back(*i);
    }

    for (auto i = RhsPassValsVec->begin(); i!=RhsPassValsVec->end(); i++)
    {
        LhsPassValsVec->push_back(*i);
    }
    return *this;
}

void RollParams::Print() const
{
    // Print header and
    cout << "RollParams Members" << endl;
    cout << "------------------" << endl;
    cout << "m_NumDice: " << GetNumDice() << endl;
    cout << "m_DieType: " << GetdieType() << endl;

    // Print ReRollValues
    cout << "ReRollValues:";
    for(auto it = m_ReRollValues->begin(); it != m_ReRollValues->end(); it++){
        cout << " " << *it;
    }

    cout << endl;

    // Print PassValues
    cout << "PassValues:";

    std::vector<uint16_t>::iterator BeginIt = m_PassValues->begin();
    std::vector<uint16_t>::iterator EndIt = m_PassValues->end();
    for(auto it = BeginIt; it != EndIt; it++){
        cout << " " << *it;
    }

    cout << endl;
}
