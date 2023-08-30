from src.neural_network import *


def workshop_1() -> None:
    test_outputs_1 = [0.1, 0.1, 0., 0.9, 0.4]
    OUTPUT_NEURONS_COUNT = 5
    TOLERANCE_DEGREE = 0.90

    result = NN_process_output(test_outputs_1, OUTPUT_NEURONS_COUNT, TOLERANCE_DEGREE)
    print(result)


def workshop_2() -> None:
    INPUT_NEURONS_COUNT = 6 * 10
    HIDDEN_NEURONS_COUNT = 60
    OUTPUT_NEURONS_COUNT = 5
    PACKET_SIZE = 10
    DATA_FRAME_SIZE = 6

    # initialize neural network lists {

    # hiddenWeights
    hiddenWeights = []
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenWeightsSup = []
        hiddenWeights.append(hiddenWeightsSup)
        for j in range(INPUT_NEURONS_COUNT):
            hiddenWeights[i].append(1.)

    # outputsWeights
    outputsWeights = []
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsWeightsSup = []
        outputsWeights.append(outputsWeightsSup)
        for j in range(HIDDEN_NEURONS_COUNT):
            outputsWeights[i].append(1.)

    # hiddenBias
    hiddenBias = []
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenBias.append(1.)

    # outputsBias
    outputsBias = []
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsBias.append(1.)

    # inputsNeurons
    inputsNeurons = []
    for i in range(INPUT_NEURONS_COUNT):
        inputsNeurons.append(0.)

    # hiddenNeurons
    hiddenNeurons = []
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenNeurons.append(0.)

    # outputsNeurons
    outputsNeurons = []
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsNeurons.append(0.)

    # } end init

    # initialize data packet lists {

    # dataPacket
    dataPacket = []
    for i in range(PACKET_SIZE):
        dataPacketSup = []
        dataPacket.append(dataPacketSup)
        for j in range(DATA_FRAME_SIZE):
            dataPacket[i].append(1.)

    # } end init

    # calculating
    calculateNeuralNetworkValues(hiddenWeights, outputsWeights, hiddenBias, outputsBias, inputsNeurons, hiddenNeurons,
                                 outputsNeurons, dataPacket, INPUT_NEURONS_COUNT, HIDDEN_NEURONS_COUNT,
                                 OUTPUT_NEURONS_COUNT, PACKET_SIZE, DATA_FRAME_SIZE)

    print(outputsNeurons)


def workshop_3() -> None:
    INPUT_NEURONS_COUNT = 6 * 10
    HIDDEN_NEURONS_COUNT = 60
    OUTPUT_NEURONS_COUNT = 5

    # initialize neural network lists {

    # hiddenWeights
    hiddenWeights = []
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenWeightsSup = []
        hiddenWeights.append(hiddenWeightsSup)
        for j in range(INPUT_NEURONS_COUNT):
            hiddenWeights[i].append(1.)

    # outputsWeights
    outputsWeights = []
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsWeightsSup = []
        outputsWeights.append(outputsWeightsSup)
        for j in range(HIDDEN_NEURONS_COUNT):
            outputsWeights[i].append(1.)

    # hiddenBias
    hiddenBias = []
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenBias.append(1.)

    # outputsBias
    outputsBias = []
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsBias.append(1.)

    # } end init

    # saving
    NN_save_to_text_file(hiddenWeights, outputsWeights, hiddenBias, outputsBias, INPUT_NEURONS_COUNT,
                         HIDDEN_NEURONS_COUNT,
                         OUTPUT_NEURONS_COUNT, "test")


def workshop_4() -> None:
    INPUT_NEURONS_COUNT = 6 * 10
    HIDDEN_NEURONS_COUNT = 60
    OUTPUT_NEURONS_COUNT = 5

    # initialize neural network lists {

    # hiddenWeights
    hiddenWeights = []
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenWeightsSup = []
        hiddenWeights.append(hiddenWeightsSup)
        for j in range(INPUT_NEURONS_COUNT):
            hiddenWeights[i].append(0.)

    # outputsWeights
    outputsWeights = []
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsWeightsSup = []
        outputsWeights.append(outputsWeightsSup)
        for j in range(HIDDEN_NEURONS_COUNT):
            outputsWeights[i].append(0.)

    # hiddenBias
    hiddenBias = []
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenBias.append(0.)

    # outputsBias
    outputsBias = []
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsBias.append(0.)

    # } end init

    # loading
    NN_read_from_text_file(hiddenWeights, outputsWeights, hiddenBias, outputsBias, INPUT_NEURONS_COUNT,
                           HIDDEN_NEURONS_COUNT, OUTPUT_NEURONS_COUNT, "test")


def workshop_5() -> None:
    INPUT_NEURONS_COUNT = 6 * 10
    HIDDEN_NEURONS_COUNT = 60
    OUTPUT_NEURONS_COUNT = 5
    PACKET_SIZE = 10
    DATA_FRAME_SIZE = 6
    TOLERANCE_DEGREE = 0.90

    # initialize neural network lists {

    # hiddenWeights
    hiddenWeights = []
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenWeightsSup = []
        hiddenWeights.append(hiddenWeightsSup)
        for j in range(INPUT_NEURONS_COUNT):
            hiddenWeights[i].append(0.)

    # outputsWeights
    outputsWeights = []
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsWeightsSup = []
        outputsWeights.append(outputsWeightsSup)
        for j in range(HIDDEN_NEURONS_COUNT):
            outputsWeights[i].append(0.)

    # hiddenBias
    hiddenBias = []
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenBias.append(0.)

    # outputsBias
    outputsBias = []
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsBias.append(0.)

    # inputsNeurons
    inputsNeurons = []
    for i in range(INPUT_NEURONS_COUNT):
        inputsNeurons.append(0.)

    # hiddenNeurons
    hiddenNeurons = []
    for i in range(HIDDEN_NEURONS_COUNT):
        hiddenNeurons.append(0.)

    # outputsNeurons
    outputsNeurons = []
    for i in range(OUTPUT_NEURONS_COUNT):
        outputsNeurons.append(0.)

    # } end init

    # initialize data packet lists {

    # dataPacket
    dataPacket = []
    for i in range(PACKET_SIZE):
        dataPacketSup = []
        dataPacket.append(dataPacketSup)
        for j in range(DATA_FRAME_SIZE):
            dataPacket[i].append(1)


    # Added because I have to make few tests and compare it with results in neural network in C

    # dataPacket[0][0] = -1
    # dataPacket[0][1] = 1
    # dataPacket[0][2] = 0
    # dataPacket[0][3] = -1
    # dataPacket[0][4] = 0
    # dataPacket[0][5] = 1
    #
    # dataPacket[1][0] = -1
    # dataPacket[1][1] = 2
    # dataPacket[1][2] = 0
    # dataPacket[1][3] = -1
    # dataPacket[1][4] = 0
    # dataPacket[1][5] = 1
    #
    # dataPacket[2][0] = -1
    # dataPacket[2][1] = 2
    # dataPacket[2][2] = 0
    # dataPacket[2][3] = -1
    # dataPacket[2][4] = 0
    # dataPacket[2][5] = 1
    #
    # dataPacket[3][0] = -1
    # dataPacket[3][1] = 2
    # dataPacket[3][2] = 0
    # dataPacket[3][3] = -1
    # dataPacket[3][4] = 0
    # dataPacket[3][5] = 1
    #
    # dataPacket[4][0] = -1
    # dataPacket[4][1] = 3
    # dataPacket[4][2] = 0
    # dataPacket[4][3] = -1
    # dataPacket[4][4] = 0
    # dataPacket[4][5] = 1
    #
    # dataPacket[5][0] = -2
    # dataPacket[5][1] = 3
    # dataPacket[5][2] = 0
    # dataPacket[5][3] = -1
    # dataPacket[5][4] = 0
    # dataPacket[5][5] = 0
    #
    # dataPacket[6][0] = -2
    # dataPacket[6][1] = 3
    # dataPacket[6][2] = 0
    # dataPacket[6][3] = -1
    # dataPacket[6][4] = 0
    # dataPacket[6][5] = 1
    #
    # dataPacket[7][0] = -2
    # dataPacket[7][1] = 3
    # dataPacket[7][2] = 0
    # dataPacket[7][3] = -1
    # dataPacket[7][4] = 0
    # dataPacket[7][5] = 1
    #
    # dataPacket[8][0] = -2
    # dataPacket[8][1] = 2
    # dataPacket[8][2] = 0
    # dataPacket[8][3] = -1
    # dataPacket[8][4] = 0
    # dataPacket[8][5] = 1
    #
    # dataPacket[9][0] = -2
    # dataPacket[9][1] = 2
    # dataPacket[9][2] = 0
    # dataPacket[9][3] = -1
    # dataPacket[9][4] = 0
    # dataPacket[9][5] = 1

    # } end init

    # loading
    NN_read_from_text_file(hiddenWeights, outputsWeights, hiddenBias, outputsBias, INPUT_NEURONS_COUNT,
                           HIDDEN_NEURONS_COUNT, OUTPUT_NEURONS_COUNT, "neuralNetwork")

    # calculating
    calculateNeuralNetworkValues(hiddenWeights, outputsWeights, hiddenBias, outputsBias, inputsNeurons, hiddenNeurons,
                                 outputsNeurons, dataPacket, INPUT_NEURONS_COUNT, HIDDEN_NEURONS_COUNT,
                                 OUTPUT_NEURONS_COUNT, PACKET_SIZE, DATA_FRAME_SIZE)

    # returning result
    result = NN_process_output(outputsNeurons, OUTPUT_NEURONS_COUNT, TOLERANCE_DEGREE)

    # saving
    # we don't have to use this function !!!
    NN_save_to_text_file(hiddenWeights, outputsWeights, hiddenBias, outputsBias, INPUT_NEURONS_COUNT,
                         HIDDEN_NEURONS_COUNT, OUTPUT_NEURONS_COUNT, "neuralNetwork")

    # showing results
    print("Result: " + result)
    print(outputsNeurons)


if __name__ == '__main__':
    # workshop_1() # NN_process_output
    # workshop_2() # calculateNeuralNetworkValues
    # workshop_3() # NN_save_to_text_file
    # workshop_4() # NN_read_from_text_file
    workshop_5()  # All functions together
