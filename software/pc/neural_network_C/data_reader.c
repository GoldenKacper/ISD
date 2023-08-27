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
    int linesCounter = 0;

    FILE *fptr;

    for (int packetNumber = 0; packetNumber < filesNumber; ++packetNumber) {
        // Open a file in read mode
        fptr = fopen(files[packetNumber], "r");

        char singleLine[255];

        for (int i = 0; i < setOfCountedLinesOfFiles[packetNumber] - 1; ++i) {
            // If the file exist
            if (fptr != NULL) {
                fgets(singleLine, 255, fptr);
                assigningDataToDataPacket(&dataPackets[linesCounter], singleLine);
                assigningDataToExpectedValues(expectedValues, packetNumber, linesCounter);
                linesCounter++;

            } else {
                printf("Not able to open the file.\n");
                return false;
            }
        }

        // Close the file
        fclose(fptr);
    }

    return true;
}


void assigningDataToExpectedValues(char *expectedValues, int packetNumber, int index) {
    switch (packetNumber) {
        case 0:
            expectedValues[index] = 'l';
            break;
        case 1:
            expectedValues[index] = 's';
            break;
        case 2:
            expectedValues[index] = 'w';
            break;
        case 3:
            expectedValues[index] = 'r';
            break;
    }
}

void assigningDataToDataPacket(DataPacket *dataPacket, const char *dataLine) {
    int numbers[INPUT_DATA_COUNT];
    dataLineSplitter(numbers, dataLine);
    for (int i = 0; i < PACKET_SIZE; ++i) {
        for (int j = 0; j < DATA_FRAME_SIZE; ++j) {
            dataPacket->x[i].x[j] = numbers[i * 6 + j];
        }
    }
}

void dataLineSplitter(int *numbers, const char *dataLine) {
    int i = 0;
    char *number = strtok(dataLine, " ");

    while (number != NULL) {
        numbers[i] = charToInt(number);
        ++i;
        number = strtok(NULL, " ");
    }
}

int charToInt(const char *numberChar) {
    int numberInt = atoi(numberChar);
    return numberInt;
}


void dataPacket_print(DataPacket dataPacket) {
    printf("##### Data Packet printing: ...#####\n\n");
    for (int j = 0; j < PACKET_SIZE; ++j) {
        printf("### %d Packet ###\t", j);
        for (int k = 0; k < DATA_FRAME_SIZE; ++k) {
            printf("%d ", dataPacket.x[j].x[k]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void expectedValue_print(char expectedValue) {
    printf("##### Expected Value printing: ...#####\n\n");
    printf("Expected value: %c\n\n", expectedValue);
}
