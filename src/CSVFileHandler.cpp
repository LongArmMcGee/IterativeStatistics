#include <iostream>  //cin, cout
#include <stdint.h>
#include <cstdlib>
#include <stdio.h>
#include <string>     // std::string, std::stoi
#include "CSVFileHandler.hpp"

/** \brief CSVFileHandler is a quick and dirty namespace to print out a comma
 *         delimited file.
 *
 */

namespace CSVFileHandler{

    static uint16_t ExecutionNum = 0;
    static bool IsCSVInitialized = false;
    static uint16_t ManualBatchCntr = 0;
    static FILE* pFileCSV = NULL;

    // Hard coded for 10,000 batch count
    #define BATCH_COUNT 10000

    void InitializeFileHandler(){
        // Open file in append mode
        pFileCSV = fopen ("RandNumCSV.txt","a");

        IsCSVInitialized = true;
    };

    void PrintUintToCSV(uint16_t RandNum){
        if(IsCSVInitialized){
            if(ManualBatchCntr == (BATCH_COUNT-1)){
                fprintf(pFileCSV, ",\n");
            }

            // format string
            std::string str = std::to_string(RandNum) + ',';

            // fprintf uses cstyle string
            fprintf(pFileCSV,str.c_str());
            ManualBatchCntr++;
        }
        else{
            std::cout << std::endl << "Warning: File not initialized, initializing now."
                 << std::endl;
            InitializeFileHandler();
        }
    };
}
