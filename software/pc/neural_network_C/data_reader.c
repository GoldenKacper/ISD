#include "data_reader.h"

int countAllLinesOfDataFiles() {
    const char files[4][50] = {{"../../data/1 - lezenie.txt"},
                               {"../../data/2 - siedzenie stanie.txt"},
                               {"../../data/3 - chodzenie.txt"},
                               {"../../data/4 - bieganie.txt"}};
    //
    int filesNumber = 4; //

    int counterAllLines = 1;
    FILE *fptr;

    for (int i = 0; i < filesNumber; ++i) {
        // Open a file in read mode
        fptr = fopen(files[i], "r");

        char myString[255];
        char c;

        // If the file exist
        if (fptr != NULL) {
            // Extract characters from file and store in character c
            for (c = getc(fptr); c != EOF; c = getc(fptr))
                if (c == '\n') // Increment count if this character is newline
                    counterAllLines += 1;
            // If the file does not exist
        } else {
            printf("Not able to open the file.\n");
        }

        // Close the file
        fclose(fptr);
    }

    return counterAllLines;
}
