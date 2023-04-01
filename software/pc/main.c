#include <stdio.h>
#include "neural_network.h"

void myWorkshop_1();

int main() {
    myWorkshop_1();

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
    //NN_testInit(&nn);

    NN_read_from_text_file(&nn, "../test.txt");
#pragma endregion neural network and data packet initialized

    calculateNeuralNetworkValues(&nn, dataPacket);

//    nn.outputsNeurons[0] = 0.0f;
//    nn.outputsNeurons[1] = 0.95f;
//    nn.outputsNeurons[2] = 0.0f;
//    nn.outputsNeurons[3] = 0.0f;
//    nn.outputsNeurons[4] = 0.0f;
//    nn.outputsNeurons[5] = 0.0f;


#pragma region printing data
    // showing weights and bias
    NN_print(nn);

    // showing inputs neurons values
    NN_NeuronsValuesPrint(nn);

    // showing the decision of network
    NN_process_outputPrint(nn);

    // showing a TOTAL_WEIGHTS_AND_BIAS_COUNT
    printf("\n");
    printf("%d\n", TOTAL_WEIGHTS_AND_BIAS_COUNT);

//    NN_save_to_text_file(nn, "../test.txt");


#pragma endregion
}
