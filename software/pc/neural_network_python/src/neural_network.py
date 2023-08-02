import re

import math


# list must contain OUTPUT_NEURONS_COUNT floats (outputsNeurons[OUTPUT_NEURONS_COUNT] -> outputsNeurons[5]) |
# OUTPUT_NEURONS_COUNT = 5 | TOLERANCE_DEGREE = 0.90
def NN_process_output(outputsNeurons: list[float], OUTPUT_NEURONS_COUNT: int, TOLERANCE_DEGREE: float) -> str:
    # 0   1   2   3   4    | index
    # n   l   s   w   r    | symbol

    # Description of the symbols
    # n - not on person
    # l - lying
    # s - sitting / standing
    # w - walking
    # r - running

    # u - uncertain | when flag > 1
    # d - doubtful | when flag < 1

    flag = 0
    index = 0

    for i in range(OUTPUT_NEURONS_COUNT):
        if outputsNeurons[i] >= TOLERANCE_DEGREE:
            flag += 1
            index = i

    if flag == 1:
        match index:
            case 0:
                return "n"
            case 1:
                return "l"
            case 2:
                return "s"
            case 3:
                return "w"
            case 4:
                return "r"

    elif flag < 1:
        return "d"
    elif flag > 1:
        return "u"


# INPUT_NEURONS_COUNT = 6*10, HIDDEN_NEURONS_COUNT = 60, OUTPUT_NEURONS_COUNT = 5,
# PACKET_SIZE = 10, DATA_FRAME_SIZE = 6
#
# typedef struct NeuralNetwork {
#     float hiddenWeights[HIDDEN_NEURONS_COUNT][INPUT_NEURONS_COUNT];
#     float outputsWeights[OUTPUT_NEURONS_COUNT][HIDDEN_NEURONS_COUNT];
#     float hiddenBias[HIDDEN_LAYER_BIAS_COUNT];
#     float outputsBias[OUTPUTS_LAYER_BIAS_COUNT];
#
#     float inputsNeurons[INPUT_NEURONS_COUNT];
#     float hiddenNeurons[HIDDEN_NEURONS_COUNT];
#     float outputsNeurons[OUTPUT_NEURONS_COUNT];
# } NeuralNetwork;
def calculateNeuralNetworkValues(hiddenWeights: list[list[float]], outputsWeights: list[list[float]],
                                 hiddenBias: list[float], outputsBias: list[float], inputsNeurons: list[float],
                                 hiddenNeurons: list[float], outputsNeurons: list[float], dataPacket: list[list[int]],
                                 INPUT_NEURONS_COUNT: int, HIDDEN_NEURONS_COUNT: int, OUTPUT_NEURONS_COUNT: int,
                                 PACKET_SIZE: int, DATA_FRAME_SIZE: int) -> None:
    # setting up a inputs neurons values
    for i in range(PACKET_SIZE):
        for j in range(DATA_FRAME_SIZE):
            inputsNeurons[i * 6 + j] = float(dataPacket[i][j])

    # calculating a hidden neurons values
    for i in range(HIDDEN_NEURONS_COUNT):
        value = hiddenBias[i]
        for j in range(INPUT_NEURONS_COUNT):
            value += hiddenWeights[i][j] * inputsNeurons[j]
        value = sigmoid(value)
        hiddenNeurons[i] = value

    # calculating a outputs neurons values
    for i in range(OUTPUT_NEURONS_COUNT):
        value = outputsBias[i]
        for j in range(HIDDEN_NEURONS_COUNT):
            value += outputsWeights[i][j] * hiddenNeurons[j]
        value = sigmoid(value)
        outputsNeurons[i] = value


# INPUT_NEURONS_COUNT = 6*10, HIDDEN_NEURONS_COUNT = 60, OUTPUT_NEURONS_COUNT = 5,
# filename - name without extension, for example ("test") | function add extension '.txt'
#
# HIDDEN_NEURONS_COUNT = HIDDEN_LAYER_BIAS_COUNT
# OUTPUT_NEURONS_COUNT = OUTPUTS_LAYER_BIAS_COUNT
#
#     float hiddenWeights[HIDDEN_NEURONS_COUNT][INPUT_NEURONS_COUNT];
#     float outputsWeights[OUTPUT_NEURONS_COUNT][HIDDEN_NEURONS_COUNT];
#     float hiddenBias[HIDDEN_NEURONS_COUNT];
#     float outputsBias[OUTPUT_NEURONS_COUNT];
def NN_save_to_text_file(hiddenWeights: list[list[float]], outputsWeights: list[list[float]],
                         hiddenBias: list[float], outputsBias: list[float],
                         INPUT_NEURONS_COUNT: int, HIDDEN_NEURONS_COUNT: int, OUTPUT_NEURONS_COUNT: int,
                         filename: str) -> None:
    # init variables
    file = open("src/" + filename + ".txt", "w")

    # saving neural network's weights and bias
    # saving hidden weights
    for i in range(HIDDEN_NEURONS_COUNT):
        for j in range(INPUT_NEURONS_COUNT):
            file.write(str(round(hiddenWeights[i][j], 6)) + " ")
        file.write("\n")
    file.write("\n")

    # saving outputs weights
    for i in range(OUTPUT_NEURONS_COUNT):
        for j in range(HIDDEN_NEURONS_COUNT):
            file.write(str(round(outputsWeights[i][j], 6)) + " ")
        file.write("\n")
    file.write("\n")

    # saving hidden bias
    for i in range(HIDDEN_NEURONS_COUNT):
        file.write(str(round(hiddenBias[i], 6)) + " ")
    file.write("\n\n")

    # saving outputs bias
    for i in range(OUTPUT_NEURONS_COUNT):
        file.write(str(round(outputsBias[i], 6)) + " ")

    file.close()


# INPUT_NEURONS_COUNT = 6*10, HIDDEN_NEURONS_COUNT = 60, OUTPUT_NEURONS_COUNT = 5,
# filename - name without extension, for example ("test") | function add extension '.txt'
#
# HIDDEN_NEURONS_COUNT = HIDDEN_LAYER_BIAS_COUNT
# OUTPUT_NEURONS_COUNT = OUTPUTS_LAYER_BIAS_COUNT
#
#     float hiddenWeights[HIDDEN_NEURONS_COUNT][INPUT_NEURONS_COUNT];
#     float outputsWeights[OUTPUT_NEURONS_COUNT][HIDDEN_NEURONS_COUNT];
#     float hiddenBias[HIDDEN_NEURONS_COUNT];
#     float outputsBias[OUTPUT_NEURONS_COUNT];
def NN_read_from_text_file(hiddenWeights: list[list[float]], outputsWeights: list[list[float]],
                           hiddenBias: list[float], outputsBias: list[float],
                           INPUT_NEURONS_COUNT: int, HIDDEN_NEURONS_COUNT: int, OUTPUT_NEURONS_COUNT: int,
                           filename: str) -> None:
    # init variables
    file = open("src/" + filename + ".txt", "r")

    # read hidden weights of neural network
    for i in range(HIDDEN_NEURONS_COUNT):
        data = file.readline()
        data_from_line = re.split(" ", data)
        for j in range(INPUT_NEURONS_COUNT):
            hiddenWeights[i][j] = float(data_from_line[j])

    data = file.readline()

    # read outputs weights of neural network
    for i in range(OUTPUT_NEURONS_COUNT):
        data = file.readline()
        data_from_line = re.split(" ", data)
        for j in range(HIDDEN_NEURONS_COUNT):
            outputsWeights[i][j] = float(data_from_line[j])

    data = file.readline()

    # read hidden bias of neural network
    data = file.readline()
    data_from_line = re.split(" ", data)
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenBias[i] = float(data_from_line[i])

    data = file.readline()

    # read outputs bias of neural network
    data = file.readline()
    data_from_line = re.split(" ", data)
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsBias[i] = float(data_from_line[i])

    file.close()


def sigmoid(x: float) -> float:
    return 1 / (1 + math.exp(-x))

# !!! works !!!
# def testttt(neurons: list[list[float]]) -> None:
#     for i in range(3):
#         for j in range(2):
#             neurons[i][j] = 1.
