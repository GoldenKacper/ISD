#ifndef NEURALNETWORK_DATA_READER_H
#define NEURALNETWORK_DATA_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "neural_network.h"


// 0 lying
// 1 sitting / standing
// 2 walking
// 3 running
// 4 not on person
// 5 all together
#define NUMBER_SETS_OF_COUNTED_LINES 6
#define SIZE_NUMBER_AS_CHAR 5 // sign - 1, maks 3 chars on number - 3, end of text character '\O' - 1 | 1 + 3 + 1 = 5
#define TRAINING_FLAG 0
#define TESTING_FLAG 1

// There should br as many files as states of neural network
// but for now we don't have 1 state (device not on person)
// change the data files inside the function itself
// add, remove, change, items to 'files' variable and modify 'filesNumber' accordingly
// IMPORTANT - the order of the files given for reading must match the order of the variables in the setOfCountedLinesOfFiles table
// flag is var which describes that you want to use training files or testing files
// flag == 0 : training files   |   flag == 1 : testing files
void countLinesOfEachDataFiles(int setOfCountedLinesOfFiles[], int flag);

// flag is var which describes that you want to use training files or testing files
// flag == 0 : training files   |   flag == 1 : testing files
int countSumOfLinesAllEDataFiles(int flag);

// the function assigns the data from the file to the dataPacket and expectedValue variables
// if function was run correctly this function will return 'true' else if something went wrong function will return 'false'
// flag is var which describes that you want to use training files or testing files
// flag == 0 : training files   |   flag == 1 : testing files
bool assignDataFromTheFileToVariables(DataPacket dataPackets[], char expectedValues[], int flag);

// function modify the expectedValues as a result expectedValues has values ready to use
void assigningDataToExpectedValues(char expectedValues[], int packetNumber, int index);

// saving data into dataPackets
void assigningDataToDataPacket(DataPacket *dataPackets, const char dataLine[]);

// split a one data line on many numbers
// change numbers on integers and save its to 'numbers[]'
void dataLineSplitter(int numbers[], const char dataLine[]);

// convert const string into integer
int charToInt(const char numberChar[]);

/// printing functions
void dataPacket_print(DataPacket dataPacket); // printing data packet's values
void expectedValue_print(char expectedValue); // printing expected value

#endif //NEURALNETWORK_DATA_READER_H
