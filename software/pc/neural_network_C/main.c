#include <stdio.h>
#include "neural_network.h"
#include "data_reader.h"


void myWorkshop_1(); // neural network - forward propagation
void myWorkshop_2(); // modify gradient and neural network
void myWorkshop_3(); // shuffle training sets and expectedValues array
void myWorkshop_4(); // calculate cost function
void myWorkshop_5(); // calculate gradient
void myWorkshop_6(); // learning

void myWorkshop_7(); // counting lines of all data files
void myWorkshop_8(); // assigns the data from the file to the variables

void learnTest_1(); // short general tests of learning neural network with all additions

/// General functions used to train Neural Network
void forwardPropagation(); // forward propagation with real data and results | Use for manual testing
void trainNeuralNetwork(); // training neural network with real data and results


int main() {
//    myWorkshop_1();
//    myWorkshop_2();
//    myWorkshop_3();
//    myWorkshop_4();
//    myWorkshop_5();
//    myWorkshop_6();

//    myWorkshop_7();
//    myWorkshop_8();

//    learnTest_1();

/// Only one of these functions should be uncomment
//    forwardPropagation();
    trainNeuralNetwork();

    return 0;
}

void myWorkshop_1() {
#pragma region setUp
    // Initialize dataPacket
    DataPacket dataPacket;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 6; ++j) {
            dataPacket.x[i].x[j] = 1;
        }
    }

    // Initialize neuralNetwork
    NeuralNetwork nn;
//    NN_init(&nn);
    NN_testInit(&nn, 1.f);

//    NN_read_from_text_file(&nn, "../test.txt");
#pragma endregion neural network and data packet initialized

    calculateNeuralNetworkValues(&nn, dataPacket);


#pragma region printing data
    // showing weights and bias
    NN_print(nn);

    // showing inputs neurons values
    NN_neurons_values_print(nn);

    // showing the decision of network
    NN_process_output_print(nn);

    // showing a TOTAL_WEIGHTS_AND_BIAS_COUNT
    printf("\n");
    printf("%d\n", TOTAL_WEIGHTS_AND_BIAS_COUNT);

//    NN_save_to_text_file(nn, "../test.txt");


#pragma endregion

}

void myWorkshop_2() {
    printf("New value:\t%f\n\n", calculateDeltaChangingValue(0.25f, 0.1f));

    Gradient gradient1;
    Gradient gradient2;

    gradientInit(&gradient1, 2);
    gradientInit(&gradient2, 1);

    gradient_print(gradient1);
    printf("\n\n\n\n");
    gradient_print(gradient2);
    printf("\n\n\n\n");

    finallGradientChange(&gradient1, &gradient2);
    swapGradient(&gradient1, &gradient2);

    // test
//    gradientInit(&gradient2, 0);
//    gradient2.outputsBiasGradient[4] = 1234;

    gradient_print(gradient1);
    printf("\n\n\n\n");
    gradient_print(gradient2);
    printf("\n\n\n\n");

    NeuralNetwork nn;
    NN_testInit(&nn, 0);

    NN_print(nn);
    printf("\n\n\n\n");

    NN_modify_values(&nn, &gradient1);

    NN_print(nn);
    printf("\n\n\n\n");
}

void myWorkshop_3() {
#pragma region setUp
    // create variables
    int arraySize = 6;
    DataPacket dataPackets[arraySize];
    char expectedValues[arraySize];

    // init dataPackets
    for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < PACKET_SIZE; ++j) {
            for (int k = 0; k < DATA_FRAME_SIZE; ++k) {
                dataPackets[i].x[j].x[k] = i;
            }
        }
    }

    // init expectedValues
    for (int i = 0; i < arraySize; ++i) {
        expectedValues[i] = (char) (97 + i);
    }
#pragma endregion


    shuffleTrainingSet(dataPackets, arraySize, expectedValues);


#pragma region printing data
    for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < PACKET_SIZE; ++j) {
            for (int k = 0; k < DATA_FRAME_SIZE; ++k) {
                printf("%u ", dataPackets[i].x[j].x[k]);
            }
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < arraySize; ++i) {
        printf("%c ", expectedValues[i]);
    }
#pragma endregion
}

void myWorkshop_4() {
#pragma region setUp
    // create variables
    NeuralNetwork nn;
    NN_testInit(&nn, 0);

    int arraySize = 2;
    DataPacket dataPackets[arraySize];
    char expectedValues[arraySize];

    float expValAsFloats[OUTPUT_NEURONS_COUNT]; // have to be 5
    float costVector[OUTPUT_NEURONS_COUNT];

    // initialize variables
    expectedValues[0] = 'l';
    expectedValues[1] = 's';
#pragma endregion


    convertExpVal(expValAsFloats, expectedValues[0]);
    costFunctionVector(costVector, &nn, expValAsFloats, OUTPUT_NEURONS_COUNT);
    float cost = totalCostFunctionValue(costVector, OUTPUT_NEURONS_COUNT);


#pragma region printing data
    // printing variables
    printf("%c:\t", expectedValues[0]);
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        printf("%f ", expValAsFloats[i]);
    }
    printf("\n\n");
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        printf("%f ", costVector[i]);
    }
    printf("\n%f\n", cost);
#pragma endregion
}

void myWorkshop_5() {
#pragma region setUp
    //create variables
    NeuralNetwork nn;
    NN_testInit(&nn, 1);

    Gradient gradient;

    int arraySize = 5;
    DataPacket dataPackets[arraySize];
    char expectedValues[arraySize];

    // init gradient
    gradientInit(&gradient, 0);

    // init dataPackets
    for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < PACKET_SIZE; ++j) {
            for (int k = 0; k < DATA_FRAME_SIZE; ++k) {
                dataPackets[i].x[j].x[k] = 1;
            }
        }
    }

    // init expectedValues
    expectedValues[0] = 'n';
    expectedValues[1] = 'l';
    expectedValues[2] = 's';
    expectedValues[3] = 'w';
    expectedValues[4] = 'r';

    // setUp expected values for tests
    float test[5];
    test[0] = 0;
    test[1] = 0;
    test[2] = 0;
    test[3] = 0;
    test[4] = 0;
#pragma endregion

    // test of calculateAverageGradient
    calculateAverageGradient(&gradient, &nn, dataPackets, expectedValues, 0, 5);

    //gradient_print(gradient);

    // modify neural network for tests
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 60; ++j) {
            nn.outputsWeights[i][j] = 0.1f;
            nn.hiddenNeurons[j] = 0.1f;
        }
    }
    for (int i = 0; i < 60; ++i) {
        for (int j = 0; j < 60; ++j) {
            nn.hiddenWeights[i][j] = 0.1f;
            nn.inputsNeurons[j] = 0.1f;
        }
    }

#pragma region printing data
    // printing data
    NN_print(nn);
    NN_neurons_values_print(nn);

    printf("Formula 1 | function result: %f\n", F_outputsWeights(&nn, 0, 0, 0));
    printf("Formula 2 | function result: %f\n", F_outputsBias(&nn, 0, 0));
    printf("Formula 3 | function result: %f\n", F_hiddenWeights(&nn, 0, 0, test));
    printf("Formula 4 | function result: %f\n", F_hiddenBias(&nn, 0, test));
#pragma endregion

    // test of calculateAverageGradient
    calculateAverageGradient(&gradient, &nn, dataPackets, expectedValues, 0, 5);

    // print gradient
    gradient_print(gradient);
}

void myWorkshop_6() {
    //create variables
    NeuralNetwork nn;
    NN_testInit(&nn, 1);

    int arraySize = 8000; // max value is 8256 but I don't know why
    DataPacket dataPackets[arraySize];
    char expectedValues[arraySize];

    // init dataPackets
    for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < PACKET_SIZE; ++j) {
            for (int k = 0; k < DATA_FRAME_SIZE; ++k) {
                dataPackets[i].x[j].x[k] = i;
            }
        }
    }

    // setup expectedValues
    for (int i = 0; i < arraySize; ++i) {
        expectedValues[i] = 'n';
    }


    NN_learn(&nn, dataPackets, expectedValues, arraySize, 5);

    NN_print(nn);
}

void myWorkshop_7() {
    // init counters
    int setOfCountedLinesOfFiles[NUMBER_SETS_OF_COUNTED_LINES];

    // line counting without it you can't initialize the variables
    countLinesOfEachDataFiles(setOfCountedLinesOfFiles,
                              TRAINING_FLAG); // when I did this I don't have testing files but in this place should be TESTING_FLAG

    // printing
    for (int i = 0; i < 6; ++i) {
        printf("%d\n", setOfCountedLinesOfFiles[i]);
    }
}

void myWorkshop_8() {
    // init counters
    int setOfCountedLinesOfFiles[NUMBER_SETS_OF_COUNTED_LINES];

    // line counting without it you can't initialize the variables
    countLinesOfEachDataFiles(setOfCountedLinesOfFiles,
                              TRAINING_FLAG); // when I did this I don't have testing files but in this place should be TESTING_FLAG

    // assigning all lines to a separate variable to improve readability
    int numberOfAllLines = setOfCountedLinesOfFiles[5];

    // init variables
    DataPacket dataPackets[numberOfAllLines];
    char expectedValues[numberOfAllLines];

    // reading...
    bool readSuccessfully = assignDataFromTheFileToVariables(dataPackets, expectedValues,
                                                             TRAINING_FLAG); // when I did this I don't have testing files but in this place should be TESTING_FLAG

    // printing results
    if (readSuccessfully) {
        printf("\nSuccessfully read data from files\n\n");
    } else {
        printf("\nSomething went wrong\n\n");
    }

    printf("%d\n", numberOfAllLines);
    dataPacket_print(dataPackets[8110]);
    expectedValue_print(expectedValues[8110]);
}

void learnTest_1() {
    // init counters
    int setOfCountedLinesOfFiles[NUMBER_SETS_OF_COUNTED_LINES];

    // line counting without it you can't initialize the variables
    countLinesOfEachDataFiles(setOfCountedLinesOfFiles, TRAINING_FLAG); // for learning has to be TRAINING_FLAG

    // assigning all lines to a separate variable to improve readability
    int numberOfAllLines = setOfCountedLinesOfFiles[5];

    // init variables
    DataPacket dataPackets[numberOfAllLines];
    char expectedValues[numberOfAllLines];

    // reading...
    bool readSuccessfully = assignDataFromTheFileToVariables(dataPackets, expectedValues,
                                                             TRAINING_FLAG); // for learning has to be TRAINING_FLAG

    // printing results
    if (readSuccessfully) {
        printf("\nSuccessfully read data from files\n\n");
    } else {
        printf("\nSomething went wrong\n\n");
    }

    // create variables needed for neural network
    NeuralNetwork nn;
    //NN_read_from_text_file(&nn, "../neuralNetwork.txt");


    NN_init(&nn);
    // printing randomly selected network
    NN_print(nn);


    // learning
    NN_learn(&nn, dataPackets, expectedValues, numberOfAllLines - 2, 5); //  numberOfAllLines-2 because

    // printing result
    NN_print(nn);

    NN_save_to_text_file(nn, "../neuralNetwork.txt");
}

void forwardPropagation() {
    // init variables
    NeuralNetwork nn;
    NN_read_from_text_file(&nn, "../neuralNetwork.txt");

    int numberOfAllLines = countSumOfLinesAllEDataFiles(TESTING_FLAG);
    DataPacket dataPackets[numberOfAllLines];
    char expectedValues[numberOfAllLines];

    // create one variable
    int exampleNumber = 0; // enter the sample number for the manual test

    // reading...
    bool readSuccessfully = assignDataFromTheFileToVariables(dataPackets, expectedValues, TESTING_FLAG);

    // printing results
    if (readSuccessfully) {
        printf("\nSuccessfully read data from files\n\n");
    } else {
        printf("\nSomething went wrong\n\n");
    }

    calculateNeuralNetworkValues(&nn, dataPackets[exampleNumber]);

    // showing weights and bias
    NN_print(nn);

    // showing inputs neurons values
    NN_neurons_values_print(nn);

    // showing the decision of network
    NN_process_output_print(nn);

    dataPacket_print(dataPackets[exampleNumber]);
    expectedValue_print(expectedValues[exampleNumber]);

    testNeuralNetworkKnowledge(&nn, dataPackets, expectedValues, numberOfAllLines);
}


void trainNeuralNetwork() {
#pragma region Training section

    // init counters
    int setOfCountedLinesOfFiles[NUMBER_SETS_OF_COUNTED_LINES];

    // line counting without it you can't initialize the variables
    countLinesOfEachDataFiles(setOfCountedLinesOfFiles, TRAINING_FLAG); // for learning has to be TRAINING_FLAG

    // assigning all lines to a separate variable to improve readability
    int numberOfAllLines = setOfCountedLinesOfFiles[5];

    // init data variables
    DataPacket trainingDataPackets[numberOfAllLines];
    char trainingExpectedValues[numberOfAllLines];

    // reading... save data from file into trainingDataPackets and trainingExpectedValues
    bool readSuccessfully = assignDataFromTheFileToVariables(trainingDataPackets, trainingExpectedValues,
                                                             TRAINING_FLAG); // for learning has to be TRAINING_FLAG

    // printing reading's results
    if (readSuccessfully) {
        printf("\nSuccessfully read data from files\n\n");
    } else {
        printf("\nSomething went wrong\n\n");
    }

    // create epochs number
    int epochsNumber = 1; // enter the epochs number

    // create neural network
    NeuralNetwork nn;

    // NN_init(&nn); // first run require to use this function | Warning - this function will reset all progress! but if the network is not saved, nothing will happen

    // reading neural network from file (reading progress)
    NN_read_from_text_file(&nn, "../neuralNetwork.txt"); // every subsequent startup must be with this function

    // printing randomly selected network
    //NN_print(nn); // used to see the neural network right after drawing the weights and bias | after first run should be commented

    // learning... | most important function
    NN_learn(&nn, trainingDataPackets, trainingExpectedValues, numberOfAllLines - 2, epochsNumber); //  numberOfAllLines-2 because

    // printing neural network to see the learning results
    NN_print(nn); // used to see the neural network's weights and bias right after learning function

    // saving neural network into file (saving progress)
    // ! Warning ! - wrong use may result in writing incorrect data to the file and thus destroying the neural network
    NN_save_to_text_file(nn, "../neuralNetwork.txt"); // if you want to save the learning effect it should be used

#pragma endregion

#pragma region Mechanical Testing section

    // count new number of all lines for testing files
    numberOfAllLines = countSumOfLinesAllEDataFiles(TESTING_FLAG);

    // create new variables for dataPackets and expectedValues for testing
    DataPacket testingDataPackets[numberOfAllLines];
    char testingExpectedValues[numberOfAllLines];

    // reading... save data from file into trainingDataPackets and trainingExpectedValues
    readSuccessfully = assignDataFromTheFileToVariables(testingDataPackets, testingExpectedValues, TESTING_FLAG);

    // printing reading's results
    if (readSuccessfully) {
        printf("\nSuccessfully read data from files\n\n");
    } else {
        printf("\nSomething went wrong\n\n");
    }

    // the most important function for testing
    // tests the network on a test set and displays the detailed report
    testNeuralNetworkKnowledge(&nn, testingDataPackets, testingExpectedValues, numberOfAllLines);

#pragma endregion

#pragma region Manual Testing section

    // ! Important !
    // It can only be done after the 'Mechanical Testing section'
    // because the variables are prepared there for testing

    // create one variable
    int exampleNumber = 0; // enter the sample number for the manual test

    // calculate neural network for given example
    calculateNeuralNetworkValues(&nn, testingDataPackets[exampleNumber]);

    // <-- These functions will allow you to carefully analyze the given example and compare the result with the expected one
    // showing weights and bias
    //NN_print(nn); // uncomment for more detailed information

    // showing inputs neurons values
    NN_neurons_values_print(nn);

    // showing the decision of network
    NN_process_output_print(nn);

    // showing dataPacket and expectedValue
    dataPacket_print(testingDataPackets[exampleNumber]);
    expectedValue_print(testingExpectedValues[exampleNumber]);
    // --> End showing section

#pragma endregion
}
