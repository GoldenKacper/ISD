#include <stdio.h>
#include <string.h>

#include "neural_network.h"

#pragma region init functions


void NN_init(NeuralNetwork *nn) {
    // set hidden neurons weights on 0
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            nn->hiddenWeights[i][j] = drawNumber();
        }
    }

    // set outputs neurons weights on 0
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            nn->outputsWeights[i][j] = drawNumber();
        }
    }

    // set hidden neurons bias on 0
    for (int i = 0; i < HIDDEN_LAYER_BIAS_COUNT; ++i) {
        nn->hiddenBias[i] = drawNumber();
    }

    // set outputs neurons bias on 0
    for (int i = 0; i < OUTPUTS_LAYER_BIAS_COUNT; ++i) {
        nn->outputsBias[i] = drawNumber();
    }
}

void NN_testInit(NeuralNetwork *nn, int initValue) {
    // set hidden neurons weights on 0
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            nn->hiddenWeights[i][j] = initValue;
        }
    }

    // set outputs neurons weights on 0
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            nn->outputsWeights[i][j] = initValue;
        }
    }

    // set hidden neurons bias on 0
    for (int i = 0; i < HIDDEN_LAYER_BIAS_COUNT; ++i) {
        nn->hiddenBias[i] = initValue;
    }

    // set outputs neurons bias on 0
    for (int i = 0; i < OUTPUTS_LAYER_BIAS_COUNT; ++i) {
        nn->outputsBias[i] = initValue;
    }
}


#pragma endregion


#pragma region output functions


char NN_process_output(NeuralNetwork nn) {
#pragma region Instruciton
    // 0    1   2   3   4   | index
    // n    l   s   w   r   | symbol

    // Description of the symbols
    // n - not on person
    // l - lying
    // s - sitting / standing
    // w - walking
    // r - running

    // u - uncertain    | when flag > 1
    // d - doubtful     | when flag < 1
#pragma endregion

    uint8_t flag = 0;
    uint8_t index = 0;

    for (uint8_t i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        if (nn.outputsNeurons[i] >= TOLERANCE_DEGREE) {
            flag += 1;
            index = i;
        }
    }

    if (flag == 1) {
        switch (index) {
            case 0:
                return 'n';
            case 1:
                return 'l';
            case 2:
                return 's';
            case 3:
                return 'w';
            case 4:
                return 'r';
        }
    } else if (flag < 1) {
        return 'd';
    } else if (flag > 1) {
        return 'u';
    }
}


#pragma endregion


#pragma region learning functions


void NN_learn(NeuralNetwork *neuralNetwork, DataPacket *trainingDataPacket, char *expectedValues, int dpSize,
              int epochsNumber) {
    // create gradients
    Gradient newGradient;
    Gradient previousGradient;

    for (int epoch = 0; epoch < epochsNumber; ++epoch) {

        // shuffle a training set
        // TODO shuffle a training set

        // initialize gradients
        gradientInit(&newGradient, 0);
        gradientInit(&previousGradient, 0);

        // trainingSetSize(100) dataPackets of each trainingSet
        // calculate gradient of each training set and modified weights and bias
        for (int trainingSetNumber = 0; trainingSetNumber < dpSize / trainingSetSize; ++trainingSetNumber) {

            // average values of the gradient of cost function
            // Sets the new values into newGradient
            // TODO calculate average values gradient of cost function

            // use a function with learning rate and momentum
            // calculate a finall delta of weights and bias
            // modify newGradient's values: newGradient = ...
            finallGradientChange(&newGradient, &previousGradient);

            // modification of the values of weights and bias by the previously calculated newGradient's variables
            NN_modify_values(neuralNetwork, &newGradient);

            // Set previousGradient as newGradient: previousGradient = newGradient
            swapGradient(&newGradient, &previousGradient);
        }

    }
}

void finallGradientChange(Gradient *newGradient, Gradient *previousGradient) {
    // modify hiddenWeightsGradient and hiddenBiasGradient
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            newGradient->hiddenWeightsGradient[i][j] = calculateDeltaChangingValue(
                    newGradient->hiddenWeightsGradient[i][j], previousGradient->hiddenWeightsGradient[i][j]);
        }
        newGradient->hiddenBiasGradient[i] = calculateDeltaChangingValue(newGradient->hiddenBiasGradient[i],
                                                                         previousGradient->hiddenBiasGradient[i]);
    }

    // modify outputsWeightsGradient and outputsBiasGradient
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            newGradient->outputsWeightsGradient[i][j] = calculateDeltaChangingValue(
                    newGradient->outputsWeightsGradient[i][j], previousGradient->outputsWeightsGradient[i][j]);
        }
        newGradient->outputsBiasGradient[i] = calculateDeltaChangingValue(newGradient->outputsBiasGradient[i],
                                                                          previousGradient->outputsBiasGradient[i]);
    }
}


#pragma endregion


#pragma region save and read functions


void NN_save_to_text_file(NeuralNetwork nn, const char *filename) {
    FILE *fptr;
    fptr = fopen(filename, "w");

    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            fprintf(fptr, "%.6f ", nn.hiddenWeights[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");

    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            fprintf(fptr, "%.6f ", nn.outputsWeights[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");

    for (int i = 0; i < HIDDEN_LAYER_BIAS_COUNT; ++i) {
        fprintf(fptr, "%.6f ", nn.hiddenBias[i]);
    }
    fprintf(fptr, "\n");
    fprintf(fptr, "\n");
    for (int i = 0; i < OUTPUTS_LAYER_BIAS_COUNT; ++i) {
        fprintf(fptr, "%.6f ", nn.outputsBias[i]);
    }

    fclose(fptr);
}


void NN_read_from_text_file(NeuralNetwork *nn, const char *filename) {
    FILE *fptr;
    fptr = fopen(filename, "r");

    char line[FILE_LINE_MAX_LENGTH];

    int j;
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        j = 0;
        fgets(line, FILE_LINE_MAX_LENGTH, fptr);
        char *numbersHW = strtok(line, " ");
        while (numbersHW != NULL) {
            char *number = numbersHW;
            nn->hiddenWeights[i][j] = (float) atof(number);
            numbersHW = strtok(NULL, " ");
            j++;
        }
    }

    fgets(line, FILE_LINE_MAX_LENGTH, fptr);
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        j = 0;
        fgets(line, FILE_LINE_MAX_LENGTH, fptr);
        char *numbersOW = strtok(line, " ");
        while (numbersOW != NULL) {
            char *number = numbersOW;
            nn->outputsWeights[i][j] = (float) atof(number);
            numbersOW = strtok(NULL, " ");
            j++;
        }
    }

    fgets(line, FILE_LINE_MAX_LENGTH, fptr);
    j = 0;
    fgets(line, FILE_LINE_MAX_LENGTH, fptr);
    char *numbersHB = strtok(line, " ");
    while (numbersHB != NULL) {
        char *number = numbersHB;
        nn->hiddenBias[j] = (float) atof(number);
        numbersHB = strtok(NULL, " ");
        j++;
    }

    fgets(line, FILE_LINE_MAX_LENGTH, fptr);
    j = 0;
    fgets(line, FILE_LINE_MAX_LENGTH, fptr);
    char *numbersOB = strtok(line, " ");
    while (numbersOB != NULL) {
        char *number = numbersOB;
        nn->outputsBias[j] = (float) atof(number);
        numbersOB = strtok(NULL, " ");
        j++;
    }

    fclose(fptr);
}


#pragma endregion


#pragma region printing functions


void NN_print(NeuralNetwork nn) {
    printf("##### Neural Network printing: ...#####\n\n");

    //printing hidden layer ( weights and bias )
    printf("### Hidden layer ###\n\n");
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        printf("%d hidden neuron: \n", i);
        printf("bias: %f  |  ", nn.hiddenBias[i]);
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            printf("%f  ", nn.hiddenWeights[i][j]);
        }
        printf("\n\n");
    }

    //printing output layer ( weights and bias )
    printf("### Output layer ###\n\n");
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        printf("%d outputs neuron: \n", i);
        printf("bias: %f  |  ", nn.outputsBias[i]);
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            printf("%f  ", nn.outputsWeights[i][j]);
        }
        printf("\n\n");
    }
}

void NN_neurons_values_print(NeuralNetwork nn) {
    // printing values of inputs neurons
    printf("### Input layer  ###\n\n");
    printf("Inputs neurons values :\n");
    for (int i = 0; i < PACKET_SIZE; ++i) {
        for (int j = 0; j < DATA_FRAME_SIZE; ++j) {
            printf("%f   ", nn.inputsNeurons[i * 6 + j]);
        }
        printf("\n");
    }
    printf("\n");

    // printing values of hidden neurons
    printf("### Hidden layer  ###\n\n");
    printf("Hidden neurons values :\n");
    for (int i = 0; i < PACKET_SIZE; ++i) {
        for (int j = 0; j < DATA_FRAME_SIZE; ++j) {
            printf("%f   ", nn.hiddenNeurons[i * 6 + j]);
        }
        printf("\n");
    }
    printf("\n");

    // printing values of outputs neurons
    printf("### Output layer  ###\n\n");
    printf("Outputs neurons values :\n");
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        printf("%f   ", nn.outputsNeurons[i]);
    }
    printf("\n\n");
}

void NN_process_output_print(NeuralNetwork nn) {
    char output = NN_process_output(nn);
    printf("### Decision ###\n\n");
    printf("Decision of network is:\t%c\n", output);
    printf("\n");
    printf("Instruction:\n");
    printf("// 0    1   2   3   4  | index\n"
           "// n    l   s   w   r  | symbol\n\n"
           "// Description of the symbols\n"
           "// n - not on person\n"
           "// l - lying\n"
           "// s - sitting / standing\n"
           "// w - walking\n"
           "// r - running\n"
           "// \n"
           "// u - uncertain    | when flag > 1\n"
           "// d - doubtful     | when flag < 1\n\n");
}


void gradient_print(Gradient gradient) {
    printf("##### Gradient printing: ...#####\n\n");

    //printing hidden layer Gradient ( weights and bias )
    printf("### Hidden layer Gradient ###\n\n");
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        printf("%d hidden neuron weights gradient: \n", i);
        printf("bias: %f  |  ", gradient.hiddenBiasGradient[i]);
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            printf("%f  ", gradient.hiddenWeightsGradient[i][j]);
        }
        printf("\n\n");
    }

    //printing output layer Gradient ( weights and bias )
    printf("### Output layer Gradient ###\n\n");
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        printf("%d outputs neuron weights gradient: \n", i);
        printf("bias: %f  |  ", gradient.outputsBiasGradient[i]);
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            printf("%f  ", gradient.outputsWeightsGradient[i][j]);
        }
        printf("\n\n");
    }
}


#pragma endregion


#pragma region math functions


void calculateNeuralNetworkValues(NeuralNetwork *nn, DataPacket dp) {
    // setting up a inputs neurons values
    for (int i = 0; i < PACKET_SIZE; ++i) {
        for (int j = 0; j < DATA_FRAME_SIZE; ++j) {
            nn->inputsNeurons[i * 6 + j] = (float) (dp.x[i].x[j]);
        }
    }

    // calculating a hidden neurons values
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        float value = nn->hiddenBias[i];
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            value += nn->hiddenWeights[i][j] * nn->inputsNeurons[j];
        }
        value = sigmoid(value);
        nn->hiddenNeurons[i] = value;
    }

    // calculating a outputs neurons values
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        float value = nn->outputsBias[i];
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            value += nn->outputsWeights[i][j] * nn->hiddenNeurons[j];
        }
        value = sigmoid(value);
        nn->outputsNeurons[i] = value;
    }
}

float sigmoid(float x) {
    return 1 / (1 + exp(-x));
}

float dSigmoid(float x) {
    return sigmoid(x) * (1 - sigmoid(x));
}

float calculateDeltaChangingValue(float newGradientsValue, float previousGradientsValue) {
    return (float) ((LEARNING_RATE * newGradientsValue) + (MOMENTUM * previousGradientsValue));
}

void NN_modify_values(NeuralNetwork *nn, Gradient *gradient) {
    // modify hidden weights and bias of neural network
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            nn->hiddenWeights[i][j] += gradient->hiddenWeightsGradient[i][j];
        }
        nn->hiddenBias[i] += gradient->hiddenBiasGradient[i];
    }

    // modify outputs weights and bias of neural network
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            nn->outputsWeights[i][j] += gradient->outputsWeightsGradient[i][j];
        }
        nn->outputsBias[i] += gradient->outputsBiasGradient[i];
    }
}


#pragma endregion


#pragma region support functions


float drawNumber() {
    return (float) rand() / ((float) RAND_MAX) - 0.5f;
}

void gradientInit(Gradient *gradient, int initValue) {
    // initialize hiddenWeightsGradient and hiddenBiasGradient
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            gradient->hiddenWeightsGradient[i][j] = initValue;
        }
        gradient->hiddenBiasGradient[i] = initValue;
    }

    // initialize outputsWeightsGradient and outputsBiasGradient
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            gradient->outputsWeightsGradient[i][j] = initValue;
        }
        gradient->outputsBiasGradient[i] = initValue;
    }
}

void swapGradient(Gradient *newGradient, Gradient *previousGradient) {
    // previousGradient = newGradient

    // swap hidden weights and bias of gradient
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            previousGradient->hiddenWeightsGradient[i][j] = newGradient->hiddenWeightsGradient[i][j];
        }
        previousGradient->hiddenBiasGradient[i] = newGradient->hiddenBiasGradient[i];
    }

    // swap outputs weights and bias of gradient
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            previousGradient->outputsWeightsGradient[i][j] = newGradient->outputsWeightsGradient[i][j];
        }
        previousGradient->outputsBiasGradient[i] = newGradient->outputsBiasGradient[i];
    }
}


#pragma endregion
