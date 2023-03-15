#include <stdio.h>

#include "neural_network.h"

void NN_init(NeuralNetwork nn){
    for(int i=0; i<LAYER_SIZE_1; ++i){
        nn.weights1[i] = 0;
    }
    for(int i=0; i<LAYER_SIZE_2; ++i){
        nn.weights2[i] = 0;
    }
    for(int i=0; i<LAYER_SIZE_3; ++i){
        nn.weights3[i] = 0;
    } 
}

void NN_print(NeuralNetwork nn){
    for(int i=0; i<LAYER_SIZE_1; ++i){
        printf("%f ",nn.weights1[i]);
    }
    printf("\n");
    for(int i=0; i<LAYER_SIZE_2; ++i){
        printf("%f ",nn.weights2[i]);
    }
    printf("\n");
    for(int i=0; i<LAYER_SIZE_3; ++i){
        printf("%f ",nn.weights3[i]);
    } 
    printf("\n");
}