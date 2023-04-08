#include <stdio.h>
#include "neural_network.h"

void myWorkshop_1(); // neural network - forward propagation
void myWorkshop_2(); // modify gradient and neural network
void myWorkshop_3(); // calculate gradient

int main() {
//    myWorkshop_1();
    myWorkshop_2();

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
