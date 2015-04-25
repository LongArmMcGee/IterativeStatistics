#include <stdint.h>
#include "CSVFileHandler.hpp"
#include <cstdlib>
#include <stdio.h>

namespace CSVFileHandler{
    static uint16_t ExecutionNum = 0;
    static bool IsCSVInitialized = false;
    static uint16_t ManualBatchCntr = 0;
    FILE* RandNumCSVFile = NULL;
    #define BATCH_COUNT 10000

    void InitializeFileHandler(){
        FILE * RandNumCSVFile;

        RandNumCSVFile = fopen ("RandNumCSV.txt","a");

        IsCSVInitialized = true;
    };

    void RecordRandNumCSV(uint16_t RandNum){
        if(IsCSVInitialized){
            if(ManualBatchCntr == (BATCH_COUNT-1)){
                fprintf(RandNumCSVFile, ",\n");
            }

            fprintf(RandNumCSVFile,"," + IntToString(RandNum));
            ManualbatchCntr++;
        }
        else {
            InitializeFileHandler();
        }
    };
}
