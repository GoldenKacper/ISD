#ifndef NEURALNETWORK_NEURAL_NETWORK_H
#define NEURALNETWORK_NEURAL_NETWORK_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define FILE_LINE_MAX_LENGTH 600
#define FILE_NUMBER_LENGTH 30

#define TOLERANCE_DEGREE 0.90f

#define TRAINING_SET_SIZE 100 // Size of each training set, should be 100
#define EPOCHS_NUMBER 10000 // the number of training epochs
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
    short x[DATA_FRAME_SIZE];
} DataFrame;

typedef struct DataPacket {
    DataFrame x[PACKET_SIZE];
} DataPacket;


/// init functions
void NN_init(NeuralNetwork *nn); // initialize a neural network
void NN_testInit(NeuralNetwork *nn, float initValue); // alternative NN_init for testing


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

// calculate average gradient of cost function
// result will be return as avgGradient
// calculates the gradient for some subset of the training set
// the subset starts with dataPacketStartIndex and ends with TRAINING_SET_SIZE
void calculateAverageGradient(Gradient *avgGradient, NeuralNetwork *nn, DataPacket *miniTrainingSet,
                              char *miniExpectedValues, int dataPacketStartIndex, int trainingSetSize);
void calculateGradient(Gradient *gradient, NeuralNetwork *nn, float *expectedValues); // calculate a single gradient
void finallGradientChange(Gradient *newGradient, Gradient *previousGradient); // calculate finall newGradient's values


/// saving and reading functions
void NN_save_to_text_file(NeuralNetwork nn, const char *filename); // save neural network's weights and bias into file
void NN_read_from_text_file(NeuralNetwork *nn, const char *filename); // read neural network's weights and bias from file


/// printing functions
void NN_print(NeuralNetwork nn); // printing neural network's weights and bias
void NN_neurons_values_print(NeuralNetwork nn); // printing neural network's neurons values
void NN_process_output_print(NeuralNetwork nn); // printing neural network output decision (char)
void gradient_print(Gradient gradient); // printing gradient's values



/// math functions
void calculateNeuralNetworkValues(NeuralNetwork *nn, DataPacket dp); // calculate each neuron value for neural network
float sigmoid(float x); // activation function
float dSigmoid(float x); // derivative of the activation function
float calculateDeltaChangingValue(float newGradientsValue, float previousGradientsValue); // calculate finall gradient's values
void NN_modify_values(NeuralNetwork *nn, Gradient *gradient); // modify neural network's weights and bias with a gradient values
void shuffleTrainingSet(DataPacket *trainingSet, int t_s_size, char *expectedValues); // shuffle a training set
float totalCostFunctionValue(float *costVector, int arraySize); // return average total cost function for training set
void costFunctionVector(float *costVector, NeuralNetwork *nn, float *expectedValues, int arraySize); //calculate cost function vector and set this floats into costVector


/// formulas needed to calculate the gradient
// calculated from the formulas marked on the sheet
float F_outputsWeights(NeuralNetwork *nn, int j_index, int k_index, float expectedOutputNeuron); // F - formula
float F_outputsBias(NeuralNetwork *nn, int j_index, float expectedOutputNeuron);
float F_hiddenWeights(NeuralNetwork *nn, int k_index, int i_index, const float *expectedOutputsNeurons);
float F_hiddenBias(NeuralNetwork *nn, int k_index, const float *expectedOutputsNeurons);


/// support functions
float drawNumber(); // draw a number between -0.5 and 0.5
void gradientInit(Gradient *gradient, int initValue); // initialize gradient variables on chosen value
void gradientReset(Gradient *gradient); // set gradient's values on 0
void swapGradient(Gradient *newGradient, Gradient *previousGradient); // Set previousGradient as newGradient: previousGradient = newGradient
void shuffle(int *array, size_t n); // shuffle an array
// !!!warn!!! if you change count of outputs neurons you have to rebuild this function
void convertExpVal(float *expValAsFloats, char value); // convert expected value as char to float array


/// cloning and coping functions
void cloneDataPackets(DataPacket *cloneDataPacket, DataPacket *dataPacket, int dp_size); // cloning dataPacket array to another dataPacket array
void copyDataPacket(DataPacket *sourceDataPacket, DataPacket *destinationDataPacket); // copy single dataPacket to another dataPacket
void cloneExpValues(char *cloneExpectedValues, const char *expectedValues, int dp_size); // cloning chars array to another chars array




/// testing function
// TODO any function for testing

#endif //NEURALNETWORK_NEURAL_NETWORK_H
