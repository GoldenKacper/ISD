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
        // printing comment
        printf("\n\n### Epoch: %d ###\n\n", epoch);

        // shuffle a training set
        shuffleTrainingSet(trainingDataPacket, dpSize, expectedValues);

        // initialize gradients
        gradientInit(&newGradient, 0);
        gradientInit(&previousGradient, 0);

        // TRAINING_SET_SIZE(100) dataPackets of each trainingSet
        // calculate gradient of each training set and modified weights and bias
        for (int trainingSetNumber = 0; trainingSetNumber < dpSize; trainingSetNumber += TRAINING_SET_SIZE) {
            if (trainingSetNumber + TRAINING_SET_SIZE >= dpSize) {
                // average values of the gradient of cost function
                // Sets the new values into newGradient
                calculateAverageGradient(&newGradient, neuralNetwork, trainingDataPacket, expectedValues,
                                         trainingSetNumber, dpSize - trainingSetNumber);
            } else {
                // average values of the gradient of cost function
                // Sets the new values into newGradient
                calculateAverageGradient(&newGradient, neuralNetwork, trainingDataPacket, expectedValues,
                                         trainingSetNumber, TRAINING_SET_SIZE);

            }

            // use a function with learning rate and momentum
            // calculate a finall delta of weights and bias
            // modify newGradient's values: newGradient = ...
            finallGradientChange(&newGradient, &previousGradient);

            // modification of the values of weights and bias by the previously calculated newGradient's variables
            NN_modify_values(neuralNetwork, &newGradient);

            // Set previousGradient as newGradient: previousGradient = newGradient
            swapGradient(&newGradient, &previousGradient);

            // Reset gradient's values, sets them to 0
            gradientReset(&newGradient);
        }
    }
}

void calculateAverageGradient(Gradient *avgGradient, NeuralNetwork *nn, DataPacket *miniTrainingSet,
                              char *miniExpectedValues, int dataPacketStartIndex, int trainingSetSize) {
    // initialize variables
    Gradient gradient;
    float avgCost = 0.f;
    float avgCostVector[OUTPUT_NEURONS_COUNT];
    float costVector[OUTPUT_NEURONS_COUNT];
    float expectedValueAsFloats[OUTPUT_NEURONS_COUNT];

    for (int i = 0; i < trainingSetSize; ++i) {
        // reset the gradient before use
        gradientInit(&gradient, 0); // have to be 0

        // calculate neurons values for this example
        calculateNeuralNetworkValues(nn, miniTrainingSet[dataPacketStartIndex]);

        // calculate cost function vectors
        convertExpVal(expectedValueAsFloats, miniExpectedValues[dataPacketStartIndex]);
        costFunctionVector(costVector, nn, expectedValueAsFloats, OUTPUT_NEURONS_COUNT);

        // calculate one gradient of cost function
        calculateGradient(&gradient, nn, expectedValueAsFloats);

        // calculating and summing up the cost values
        avgCost += totalCostFunctionValue(costVector, OUTPUT_NEURONS_COUNT);

        // summing up the cost vectors values
        for (int j = 0; j < OUTPUT_NEURONS_COUNT; ++j) {
            avgCostVector[j] += costVector[j];
        }

        // summing up the gradients' hidden weights and bias values
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            for (int k = 0; k < INPUT_NEURONS_COUNT; ++k) {
                avgGradient->hiddenWeightsGradient[j][k] += gradient.hiddenWeightsGradient[j][k];
            }
            avgGradient->hiddenBiasGradient[j] += gradient.hiddenBiasGradient[j];
        }

        // summing up the gradients' outputs weights and bias values
        for (int j = 0; j < OUTPUT_NEURONS_COUNT; ++j) {
            for (int k = 0; k < HIDDEN_NEURONS_COUNT; ++k) {
                avgGradient->outputsWeightsGradient[j][k] += gradient.outputsWeightsGradient[j][k];
            }
            avgGradient->outputsBiasGradient[j] += gradient.outputsBiasGradient[j];
        }

        // increment index
        dataPacketStartIndex++;
    }

    // calculate average cost function vector
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        avgCostVector[i] /= trainingSetSize;
    }

    // calculate average cost function and print
    avgCost /= trainingSetSize;
    printf("Start index: %d\t|\tCost Of Gradient Function =\t%f\n\n", dataPacketStartIndex - trainingSetSize, avgCost);


    // calculate average gradient's hidden weights and bias values
    for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
        for (int k = 0; k < INPUT_NEURONS_COUNT; ++k) {
            avgGradient->hiddenWeightsGradient[j][k] /= trainingSetSize;
        }
        avgGradient->hiddenBiasGradient[j] /= trainingSetSize;
    }

    // calculate average gradient's outputs weights and bias values
    for (int j = 0; j < OUTPUT_NEURONS_COUNT; ++j) {
        for (int k = 0; k < HIDDEN_NEURONS_COUNT; ++k) {
            avgGradient->outputsWeightsGradient[j][k] /= trainingSetSize;
        }
        avgGradient->outputsBiasGradient[j] /= trainingSetSize;
    }
}

void calculateGradient(Gradient *gradient, NeuralNetwork *nn, float *expectedValues) {
    // calculate gradient's values for outputs weights and bias
    for (int j_index = 0; j_index < OUTPUT_NEURONS_COUNT; ++j_index) {
        for (int k_index = 0; k_index < HIDDEN_NEURONS_COUNT; ++k_index) {
            gradient->outputsWeightsGradient[j_index][k_index] = F_outputsWeights(nn, j_index, k_index,
                                                                                  expectedValues[j_index]);
        }
        gradient->outputsBiasGradient[j_index] = F_outputsBias(nn, j_index, expectedValues[j_index]);
    }

    // calculate gradient's values for hidden weights and bias
    for (int k_index = 0; k_index < HIDDEN_NEURONS_COUNT; ++k_index) {
        for (int i_index = 0; i_index < INPUT_NEURONS_COUNT; ++i_index) {
            gradient->hiddenWeightsGradient[k_index][i_index] = F_hiddenWeights(nn, k_index, i_index, expectedValues);
        }
        gradient->hiddenBiasGradient[k_index] = F_hiddenBias(nn, k_index, expectedValues);
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
    // init variables
    FILE *fptr;
    fptr = fopen(filename, "w");

    // saving neural network's weights and bias
    // saving hidden weights
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            fprintf(fptr, "%.6f ", nn.hiddenWeights[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");

    // saving outputs weights
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            fprintf(fptr, "%.6f ", nn.outputsWeights[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");

    // saving hidden bias
    for (int i = 0; i < HIDDEN_LAYER_BIAS_COUNT; ++i) {
        fprintf(fptr, "%.6f ", nn.hiddenBias[i]);
    }
    fprintf(fptr, "\n");
    fprintf(fptr, "\n");

    // saving outputs bias
    for (int i = 0; i < OUTPUTS_LAYER_BIAS_COUNT; ++i) {
        fprintf(fptr, "%.6f ", nn.outputsBias[i]);
    }

    fclose(fptr);
}


void NN_read_from_text_file(NeuralNetwork *nn, const char *filename) {
    // init variables
    FILE *fptr;
    fptr = fopen(filename, "r");

    char line[FILE_LINE_MAX_LENGTH];
    int j;

    // read hidden weights of neural network
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

    // read outputs weights of neural network
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

    // read hidden bias of neural network
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

    // read outputs bias of neural network
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

void shuffleTrainingSet(DataPacket *trainingSet, int t_s_size, char *expectedValues) {
    // dataPackets cloning
    DataPacket cloneTrainingSet[t_s_size];
    cloneDataPackets(cloneTrainingSet, trainingSet, t_s_size);

    // expectedValues cloning
    char cloneExpectedValues[t_s_size];
    cloneExpValues(cloneExpectedValues, expectedValues, t_s_size);

    // initialize shuffle array
    int shuffleSet[t_s_size];
    for (int i = 0; i < t_s_size; ++i) {
        shuffleSet[i] = i;
    }

    // shuffle the shuffle array
    shuffle(shuffleSet, t_s_size);

    // change elements' order in original training set and expectedValues array
    for (int i = 0; i < t_s_size; ++i) {
        copyDataPacket(&cloneTrainingSet[shuffleSet[i]], &trainingSet[i]);
        expectedValues[i] = cloneExpectedValues[shuffleSet[i]];
    }
}

float totalCostFunctionValue(float *costVector, int arraySize) {
    // sum up a vector's values into one number
    float cost = 0.f;
    for (int i = 0; i < arraySize; ++i) {
        cost += costVector[i];
    }
    return cost;
}

void costFunctionVector(float *costVector, NeuralNetwork *nn, float *expectedValues, int arraySize) {
    // calculate cost function vector from formula
    for (int i = 0; i < arraySize; ++i) {
        costVector[i] = (nn->outputsNeurons[i] - expectedValues[i]) * (nn->outputsNeurons[i] - expectedValues[i]);
    }
}


#pragma endregion


#pragma region formulas needed to calculate the gradient


float F_outputsWeights(NeuralNetwork *nn, int j_index, int k_index, float expectedOutputNeuron) {
    float result;
    float z_j = 0.f;

    for (int k = 0; k < HIDDEN_NEURONS_COUNT; ++k) {
        z_j += nn->outputsWeights[j_index][k] * nn->hiddenNeurons[k];
    }
    z_j += nn->outputsBias[j_index];

    result = nn->hiddenNeurons[k_index] * dSigmoid(z_j) * 2 * (nn->outputsNeurons[j_index] - expectedOutputNeuron);
    return result;
}

float F_outputsBias(NeuralNetwork *nn, int j_index, float expectedOutputNeuron) {
    float result;
    float z_j = 0.f;

    for (int k = 0; k < HIDDEN_NEURONS_COUNT; ++k) {
        z_j += nn->outputsWeights[j_index][k] * nn->hiddenNeurons[k];
    }
    z_j += nn->outputsBias[j_index];

    result = 1 * dSigmoid(z_j) * 2 * (nn->outputsNeurons[j_index] - expectedOutputNeuron);
    return result;
}

float F_hiddenWeights(NeuralNetwork *nn, int k_index, int i_index, const float *expectedOutputsNeurons) {
    float result;
    float temp = 0.f;
    float z_k = 0.f;
    float z_j;

    for (int i = 0; i < INPUT_NEURONS_COUNT; ++i) {
        z_k += nn->hiddenWeights[k_index][i] * nn->inputsNeurons[i];
    }
    z_k += nn->hiddenBias[k_index];

    result = nn->inputsNeurons[i_index] * dSigmoid(z_k);

    for (int j = 0; j < OUTPUT_NEURONS_COUNT; ++j) {
        z_j = 0.f;

        for (int k = 0; k < HIDDEN_NEURONS_COUNT; ++k) {
            z_j += nn->outputsWeights[j][k] * nn->hiddenNeurons[k];
        }
        z_j += nn->outputsBias[j];

        temp += nn->outputsWeights[j][k_index] * dSigmoid(z_j) * 2 *
                (nn->outputsNeurons[j] - expectedOutputsNeurons[j]);
    }

    result *= temp;
    return result;
}

float F_hiddenBias(NeuralNetwork *nn, int k_index, const float *expectedOutputsNeurons) {
    float result;
    float temp = 0.f;
    float z_k = 0.f;
    float z_j;

    for (int i = 0; i < INPUT_NEURONS_COUNT; ++i) {
        z_k += nn->hiddenWeights[k_index][i] * nn->inputsNeurons[i];
    }
    z_k += nn->hiddenBias[k_index];

    result = 1 * dSigmoid(z_k);

    for (int j = 0; j < OUTPUT_NEURONS_COUNT; ++j) {
        z_j = 0.f;

        for (int k = 0; k < HIDDEN_NEURONS_COUNT; ++k) {
            z_j += nn->outputsWeights[j][k] * nn->hiddenNeurons[k];
        }
        z_j += nn->outputsBias[j];

        temp += nn->outputsWeights[j][k_index] * dSigmoid(z_j) * 2 *
                (nn->outputsNeurons[j] - expectedOutputsNeurons[j]);
    }

    result *= temp;
    return result;
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

void gradientReset(Gradient *gradient) {
    gradientInit(gradient, 0);
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

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffle(int *array, size_t n) {
    srand(time(NULL));
    int j, temp;
    for (size_t i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void convertExpVal(float *expValAsFloats, char value) {
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

    switch (value) {
        case 'n':
            expValAsFloats[0] = 1.f;
            expValAsFloats[1] = 0.f;
            expValAsFloats[2] = 0.f;
            expValAsFloats[3] = 0.f;
            expValAsFloats[4] = 0.f;
            break;
        case 'l':
            expValAsFloats[0] = 0.f;
            expValAsFloats[1] = 1.f;
            expValAsFloats[2] = 0.f;
            expValAsFloats[3] = 0.f;
            expValAsFloats[4] = 0.f;
            break;
        case 's':
            expValAsFloats[0] = 0.f;
            expValAsFloats[1] = 0.f;
            expValAsFloats[2] = 1.f;
            expValAsFloats[3] = 0.f;
            expValAsFloats[4] = 0.f;
            break;
        case 'w':
            expValAsFloats[0] = 0.f;
            expValAsFloats[1] = 0.f;
            expValAsFloats[2] = 0.f;
            expValAsFloats[3] = 1.f;
            expValAsFloats[4] = 0.f;
            break;
        case 'r':
            expValAsFloats[0] = 0.f;
            expValAsFloats[1] = 0.f;
            expValAsFloats[2] = 0.f;
            expValAsFloats[3] = 0.f;
            expValAsFloats[4] = 1.f;
            break;
        default:
            expValAsFloats[0] = 0.f;
            expValAsFloats[1] = 0.f;
            expValAsFloats[2] = 0.f;
            expValAsFloats[3] = 0.f;
            expValAsFloats[4] = 0.f;
            printf("\nError: something went wrong!\n!!! convertExpVal failed !!!\n");
            break;
    }
}


#pragma endregion


#pragma region cloning and coping functions


void cloneDataPackets(DataPacket *cloneDataPacket, DataPacket *dataPacket, int dp_size) {
    // cloning dataPacket array into another dataPacket array
    for (int i = 0; i < dp_size; ++i) {
        for (int j = 0; j < PACKET_SIZE; ++j) {
            for (int k = 0; k < DATA_FRAME_SIZE; ++k) {
                cloneDataPacket[i].x[j].x[k] = dataPacket[i].x[j].x[k];
            }
        }
    }
}

void copyDataPacket(DataPacket *sourceDataPacket, DataPacket *destinationDataPacket) {
    // copy dataPacket's values into another dataPacket's values
    for (int i = 0; i < PACKET_SIZE; ++i) {
        for (int j = 0; j < DATA_FRAME_SIZE; ++j) {
            destinationDataPacket->x[i].x[j] = sourceDataPacket->x[i].x[j];
        }
    }
}

void cloneExpValues(char *cloneExpectedValues, const char *expectedValues, int dp_size) {
    // cloning char array into another char array
    for (int i = 0; i < dp_size; ++i) {
        cloneExpectedValues[i] = expectedValues[i];
    }
}


#pragma endregion
