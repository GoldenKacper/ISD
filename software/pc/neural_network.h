#ifndef NEURALNETWORK_NEURAL_NETWORK_H
#define NEURALNETWORK_NEURAL_NETWORK_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define FILE_LINE_MAX_LENGTH 600
#define FILE_NUMBER_LENGTH 30

#define TOLERANCE_DEGREE 0.90f

#define trainingSetSize 100 // Size of each training set
#define EPOCHS_NUMBER 100000 // the number of training epochs
#define LEARNING_RATE 0.6 // should be less
#define MOMENTUM 0.9 // we'll see

#define DATA_FRAME_SIZE 6
#define PACKET_SIZE 10
#define INPUT_DATA_COUNT DATA_FRAME_SIZE * PACKET_SIZE // 60

// Number of neurons on each layer
#define INPUT_NEURONS_COUNT  INPUT_DATA_COUNT // 60
#define HIDDEN_NEURONS_COUNT  60
#define OUTPUT_NEURONS_COUNT  5


// TO DELETE ? //
// Number of inputs to each layer
#define INPUT_OF_INPUTS_LAYER INPUT_DATA_COUNT // 60
#define INPUT_OF_HIDDEN_LAYER INPUT_NEURONS_COUNT * HIDDEN_NEURONS_COUNT // 3600
#define INPUT_OF_OUTPUTS_LAYER HIDDEN_NEURONS_COUNT * OUTPUT_NEURONS_COUNT // 300
// //

// Number of weights per neuron on each layer
#define HIDDEN_LAYER_WEIGHTS_COUNT INPUT_OF_HIDDEN_LAYER // 3600
#define OUTPUTS_LAYER_WEIGHTS_COUNT INPUT_OF_OUTPUTS_LAYER // 300

// Number of bias on each layer
#define HIDDEN_LAYER_BIAS_COUNT HIDDEN_NEURONS_COUNT // 60
#define OUTPUTS_LAYER_BIAS_COUNT OUTPUT_NEURONS_COUNT // 5

// Total number of weights and bias on each layer
#define HIDDEN_LAYER_SIZE HIDDEN_LAYER_WEIGHTS_COUNT + HIDDEN_LAYER_BIAS_COUNT // 3660
#define OUTPUTS_LAYER_SIZE OUTPUTS_LAYER_WEIGHTS_COUNT + OUTPUTS_LAYER_BIAS_COUNT // 305

// Total weights and bias size
#define TOTAL_WEIGHTS_AND_BIAS_COUNT HIDDEN_LAYER_SIZE + OUTPUTS_LAYER_SIZE // 3965

typedef struct NeuralNetwork {
    float hiddenWeights[HIDDEN_NEURONS_COUNT][INPUT_NEURONS_COUNT];
    float outputsWeights[OUTPUT_NEURONS_COUNT][HIDDEN_NEURONS_COUNT];
    float hiddenBias[HIDDEN_LAYER_BIAS_COUNT];
    float outputsBias[OUTPUTS_LAYER_BIAS_COUNT];

    float inputsNeurons[INPUT_NEURONS_COUNT];
    float hiddenNeurons[HIDDEN_NEURONS_COUNT];
    float outputsNeurons[OUTPUT_NEURONS_COUNT];
} NeuralNetwork;

typedef struct Gradient {
    float hiddenWeightsGradient[HIDDEN_NEURONS_COUNT][INPUT_NEURONS_COUNT];
    float outputsWeightsGradient[OUTPUT_NEURONS_COUNT][HIDDEN_NEURONS_COUNT];
    float hiddenBiasGradient[HIDDEN_LAYER_BIAS_COUNT];
    float outputsBiasGradient[OUTPUTS_LAYER_BIAS_COUNT];
} Gradient;

typedef struct DataFrame {
    uint16_t x[DATA_FRAME_SIZE];
} DataFrame;

typedef struct DataPacket {
    DataFrame x[PACKET_SIZE];
} DataPacket;


/// init functions
void NN_init(NeuralNetwork *nn); // initialize a neural network
void NN_testInit(NeuralNetwork *nn, int initValue); // alternative NN_init for testing


/// output functions
char NN_process_output(NeuralNetwork nn); // finall output value of neural network, this value will be sending to the app


/// learning functions

// main functions to learn
// it needs Neural Network and all DataPacket set for training
// the same amount expectedValues as trainingDataPacket array size
// trainingDataPacket array size is equal to expectedValues array size
// so trainingDataPacket[dpSize] and expectedValues[dpSize]
// the result of this function will be a learned network
void NN_learn(NeuralNetwork *neuralNetwork, DataPacket trainingDataPacket[], char expectedValues[], int dpSize,
              int epochsNumber);

void finallGradientChange(Gradient *newGradient, Gradient *previousGradient); // calculate finall newGradient's values

//void NN_learn_dp(NeuralNetwork nn, DataPacket dp, char expected);
//void NN_learn(NeuralNetwork nn, DataFrame dfs[], int count, char expected);


/// saving and reading functions
void NN_save_to_text_file(NeuralNetwork nn, const char *filename);
void NN_read_from_text_file(NeuralNetwork *nn, const char *filename);


/// printing functions
void NN_print(NeuralNetwork nn);
void NN_neurons_values_print(NeuralNetwork nn);
void NN_process_output_print(NeuralNetwork nn);
void gradient_print(Gradient gradient);


/// math functions
void calculateNeuralNetworkValues(NeuralNetwork *nn, DataPacket dp); // calculate each neuron value for neural network
float sigmoid(float x); // activation function
float dSigmoid(float x); // derivative of the activation function
float calculateDeltaChangingValue(float newGradientsValue, float previousGradientsValue); // calculate finall gradient's values
void NN_modify_values(NeuralNetwork *nn, Gradient *gradient); // modify neural network's weights and bias with a gradient values
// TODO costFunction to code


/// support functions
float drawNumber(); // draw a number between -0.5 and 0.5
void gradientInit(Gradient *gradient, int initValue); // initialize gradient variables on chosen value
void swapGradient(Gradient *newGradient, Gradient *previousGradient); // Set previousGradient as newGradient: previousGradient = newGradient

#endif //NEURALNETWORK_NEURAL_NETWORK_H
