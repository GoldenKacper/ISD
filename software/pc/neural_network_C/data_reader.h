#ifndef NEURALNETWORK_DATA_READER_H
#define NEURALNETWORK_DATA_READER_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "neural_network.h"


// 0 lying
// 1 sitting / standing
// 2 walking
// 3 running
// 4 not on person
// 5 all together
#define NUMBER_SETS_OF_COUNTED_LINES 6


// There should br as many files as states of neural network
// but for now we don't have 1 state (device not on person)
// change the data files inside the function itself
// add, remove, change, items to 'files' variable and modify 'filesNumber' accordingly
// IMPORTANT - the order of the files given for reading must match the order of the variables in the setOfCountedLinesOfFiles table
void countLinesOfEachAndAllDataFiles(int setOfCountedLinesOfFiles[]);

// the function assigns the data from the file to the dataPacket and expectedValue variables
// if function was run correctly this function will return 'true' else if something went wrong function will return 'false'
bool assignDataFromTheFileToVariables(DataPacket dataPackets[], char expectedValues[], int setOfCountedLinesOfFiles[]);

#endif //NEURALNETWORK_DATA_READER_H
