#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdint.h>

#define DATA_FRAME_SIZE 6
#define PACKET_SIZE 10
#define INPUT_DATA_COUNT DATA_FRAME_SIZE * PACKET_SIZE

// Number of inputs to each layer
#define INPUT_COUNT_1 INPUT_DATA_COUNT
#define INPUT_COUNT_2 60
#define INPUT_COUNT_3 60

// Number of weigths per neuron on each layer
#define WEIGTH_COUNT_PER_NEURON_1 INPUT_COUNT_1
#define WEIGTH_COUNT_PER_NEURON_2 INPUT_COUNT_2
#define WEIGTH_COUNT_PER_NEURON_3 INPUT_COUNT_3

// Number of neurons on each layer
#define NEURON_COUNT_1  60
#define NEURON_COUNT_2  60
#define NEURON_COUNT_3  6

// Total number of weights on each layer
#define LAYER_SIZE_1 NEURON_COUNT_1 * WEIGTH_COUNT_PER_NEURON_1
#define LAYER_SIZE_2 NEURON_COUNT_2 * WEIGTH_COUNT_PER_NEURON_2
#define LAYER_SIZE_3 NEURON_COUNT_3 * WEIGTH_COUNT_PER_NEURON_3

// Total weight's size
#define TOTAL_WEIGTHS_COUNT LAYER_SIZE_1 + LAYER_SIZE_2 + LAYER_SIZE_3

typedef struct NeuralNetwork
{
    float weights1[LAYER_SIZE_1];
    float weights2[LAYER_SIZE_2];
    float weights3[LAYER_SIZE_3];    
} NeuralNetwork;

typedef struct DataFrame { uint16_t x[INPUT_DATA_COUNT]; } DataFrame;
typedef struct DataPacket { DataFrame x[PACKET_SIZE]; } DataPacket
void NN_init(NeuralNetwork nn);
void NN_print(NeuralNetwork nn);
char NN_process_input(NeuralNetwork nn, DataPacket dp);
void NN_learn_dp(NeuralNetwork nn, DataPacket dp, char expected);
void NN_learn(NeuralNetwork nn, DataFrame dfs[], int count, char expected);
void NN_save_to_text_file(NeuralNetwork nn, const char* filename);
void NN_read_from_text_file(NeuralNetwork nn, const char* filename);

#endif // NEURAL_NETWORK_H