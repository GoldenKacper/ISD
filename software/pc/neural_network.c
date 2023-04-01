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

void NN_testInit(NeuralNetwork *nn) {
    // set hidden neurons weights on 0
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        for (int j = 0; j < INPUT_NEURONS_COUNT; ++j) {
            nn->hiddenWeights[i][j] = 1;
        }
    }

    // set outputs neurons weights on 0
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        for (int j = 0; j < HIDDEN_NEURONS_COUNT; ++j) {
            nn->outputsWeights[i][j] = 1;
        }
    }

    // set hidden neurons bias on 0
    for (int i = 0; i < HIDDEN_LAYER_BIAS_COUNT; ++i) {
        nn->hiddenBias[i] = 1;
    }

    // set outputs neurons bias on 0
    for (int i = 0; i < OUTPUTS_LAYER_BIAS_COUNT; ++i) {
        nn->outputsBias[i] = 1;
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

void NN_NeuronsValuesPrint(NeuralNetwork nn) {
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

void NN_process_outputPrint(NeuralNetwork nn) {
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


#pragma endregion


#pragma region save and read functions


void NN_save_to_text_file(NeuralNetwork nn, const char* filename) {
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


void NN_read_from_text_file(NeuralNetwork* nn, const char *filename) {
    FILE *fptr;
    fptr = fopen(filename, "r");

    char line[FILE_LINE_MAX_LENGTH];

    int j;
    for (int i = 0; i < HIDDEN_NEURONS_COUNT; ++i) {
        j = 0;
        fgets(line, FILE_LINE_MAX_LENGTH, fptr);
        char* numbersHW = strtok(line, " ");
        while (numbersHW != NULL) {
            char* number = numbersHW;
            nn->hiddenWeights[i][j] = (float) atof(number);
            numbersHW = strtok(NULL, " ");
            j++;
        }
    }

    fgets(line, FILE_LINE_MAX_LENGTH, fptr);
    for (int i = 0; i < OUTPUT_NEURONS_COUNT; ++i) {
        j = 0;
        fgets(line, FILE_LINE_MAX_LENGTH, fptr);
        char* numbersOW = strtok(line, " ");
        while (numbersOW != NULL) {
            char* number = numbersOW;
            nn->outputsWeights[i][j] = (float) atof(number);
            numbersOW = strtok(NULL, " ");
            j++;
        }
    }

    fgets(line, FILE_LINE_MAX_LENGTH, fptr);
    j = 0;
    fgets(line, FILE_LINE_MAX_LENGTH, fptr);
    char* numbersHB = strtok(line, " ");
    while (numbersHB != NULL) {
        char* number = numbersHB;
        nn->hiddenBias[j] = (float) atof(number);
        numbersHB = strtok(NULL, " ");
        j++;
    }

    fgets(line, FILE_LINE_MAX_LENGTH, fptr);
    j = 0;
    fgets(line, FILE_LINE_MAX_LENGTH, fptr);
    char* numbersOB = strtok(line, " ");
    while (numbersOB != NULL) {
        char* number = numbersOB;
        nn->outputsBias[j] = (float) atof(number);
        numbersOB = strtok(NULL, " ");
        j++;
    }

    fclose(fptr);
}


#pragma endregion


#pragma region support functions


float drawNumber() {
    return (float) rand() / ((float) RAND_MAX) - 0.5f;
}


#pragma endregion
