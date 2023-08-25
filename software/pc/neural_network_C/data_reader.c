#include "data_reader.h"

void countLinesOfEachAndAllDataFiles(int *setOfCountedLinesOfFiles) {
    const char files[4][50] = {{"../../data/1 - lezenie.txt"},
                               {"../../data/2 - siedzenie stanie.txt"},
                               {"../../data/3 - chodzenie.txt"},
                               {"../../data/4 - bieganie.txt"}};
    // IMPORTANT - the order of the files given for reading must match the order of the variables in the setOfCountedLinesOfFiles table
    int filesNumber = 4; //

    int counterAllFileLines = 1;
    int counterSingleFileLines = 1;

    FILE *fptr;

    for (int i = 0; i < filesNumber; ++i) {

        // Open a file in read mode
        fptr = fopen(files[i], "r");

        char c;

        // If the file exist
        if (fptr != NULL) {
            // Extract characters from file and store in character c
            for (c = getc(fptr); c != EOF; c = getc(fptr))
                if (c == '\n') {// Increment count if this character is newline
                    counterAllFileLines += 1;
                    counterSingleFileLines += 1;
                }
            // If the file does not exist
        } else {
            printf("Not able to open the file.\n");
        }

        // Close the file
        fclose(fptr);

        setOfCountedLinesOfFiles[i] = counterSingleFileLines;
        counterSingleFileLines = 1;
    }
    setOfCountedLinesOfFiles[4] = 0; // because we dont have this file
    setOfCountedLinesOfFiles[5] = counterAllFileLines;
}

bool assignDataFromTheFileToVariables(DataPacket *dataPackets, char *expectedValues, int *setOfCountedLinesOfFiles) {
    const char files[4][50] = {{"../../data/1 - lezenie.txt"},
                               {"../../data/2 - siedzenie stanie.txt"},
                               {"../../data/3 - chodzenie.txt"},
                               {"../../data/4 - bieganie.txt"}};
    int filesNumber = 4; //

    FILE *fptr;

    for (int i = 0; i < filesNumber; ++i) {
        // Open a file in read mode
        fptr = fopen(files[i], "r");

        char singleLine[255];

        // If the file exist
        if (fptr != NULL) {
            fgets(singleLine, 255, fptr);
            // Print the file content
            printf("%s", singleLine); // TODO to delete !!! remember

        } else {
            printf("Not able to open the file.\n");
            return false;
        }

        // Close the file
        fclose(fptr);
    }


    return true;
}
