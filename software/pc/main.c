#include <stdio.h>

#include "neural_network.h"

int main(){
    NeuralNetwork nn;
    NN_init(nn);
    NN_print(nn);
    printf("%ld\n", TOTAL_WEIGTHS_COUNT*sizeof(float)); // This makes no sense (i'm stupid)
    return 0;
}