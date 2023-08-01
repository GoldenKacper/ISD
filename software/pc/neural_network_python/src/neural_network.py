import numpy as np


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


def sigmoid(x: float) -> float:
    return 1 / (1 + np.exp(-x))

# !!! works !!!
# def testttt(neurons: list[list[float]]) -> None:
#     for i in range(3):
#         for j in range(2):
#             neurons[i][j] = 1.
