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

    calculateNeuralNetworkValues(hiddenWeights, outputsWeights, hiddenBias, outputsBias, inputsNeurons, hiddenNeurons,
                                 outputsNeurons, dataPacket, INPUT_NEURONS_COUNT, HIDDEN_NEURONS_COUNT,
                                 OUTPUT_NEURONS_COUNT, PACKET_SIZE, DATA_FRAME_SIZE)

    print(outputsNeurons)


if __name__ == '__main__':
    # workshop_1()
    workshop_2()
