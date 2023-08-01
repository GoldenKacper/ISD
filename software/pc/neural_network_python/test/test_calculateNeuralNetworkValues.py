import unittest

from src.neural_network import *


class TestCalculateNeuralNetworkValues(unittest.TestCase):
    def setUp(self) -> None:
        self._INPUT_NEURONS_COUNT = 6 * 10
        self._HIDDEN_NEURONS_COUNT = 60
        self._OUTPUT_NEURONS_COUNT = 5
        self._PACKET_SIZE = 10
        self._DATA_FRAME_SIZE = 6

        self.initDataPacket(0)
        self.initNeuralNetwork(0.)

    def initNeuralNetwork(self, value: float) -> None:
        # initialize neural network lists {

        # hiddenWeights
        self._hiddenWeights = []
        for i in range(self._HIDDEN_NEURONS_COUNT):
            self._hiddenWeightsSup = []
            self._hiddenWeights.append(self._hiddenWeightsSup)
            for j in range(self._INPUT_NEURONS_COUNT):
                self._hiddenWeights[i].append(value)

        # outputsWeights
        self._outputsWeights = []
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self._outputsWeightsSup = []
            self._outputsWeights.append(self._outputsWeightsSup)
            for j in range(self._HIDDEN_NEURONS_COUNT):
                self._outputsWeights[i].append(value)

        # hiddenBias
        self._hiddenBias = []
        for i in range(self._HIDDEN_NEURONS_COUNT):
            self._hiddenBias.append(value)

        # outputsBias
        self._outputsBias = []
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self._outputsBias.append(value)

        # inputsNeurons
        self._inputsNeurons = []
        for i in range(self._INPUT_NEURONS_COUNT):
            self._inputsNeurons.append(value)

        # hiddenNeurons
        self._hiddenNeurons = []
        for i in range(self._HIDDEN_NEURONS_COUNT):
            self._hiddenNeurons.append(value)

        # outputsNeurons
        self._outputsNeurons = []
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self._outputsNeurons.append(value)

        # } end init

    def initDataPacket(self, value: float) -> None:
        # initialize data packet lists {

        # dataPacket
        self._dataPacket = []
        for i in range(self._PACKET_SIZE):
            self._dataPacketSup = []
            self._dataPacket.append(self._dataPacketSup)
            for j in range(self._DATA_FRAME_SIZE):
                self._dataPacket[i].append(value)

        # } end init

    # is to check whether the test themselves work at all
    def test_always_correct(self):
        self.assertEqual(1, 1)

    def test_correct_operation_1(self):
        calculateNeuralNetworkValues(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                                     self._inputsNeurons, self._hiddenNeurons, self._outputsNeurons, self._dataPacket,
                                     self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                                     self._PACKET_SIZE, self._DATA_FRAME_SIZE)
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self.assertAlmostEqual(self._outputsNeurons[i], 0.5)

    def test_correct_operation_2(self):
        self.initDataPacket(1)
        self.initNeuralNetwork(1.)
        calculateNeuralNetworkValues(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                                     self._inputsNeurons, self._hiddenNeurons, self._outputsNeurons, self._dataPacket,
                                     self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                                     self._PACKET_SIZE, self._DATA_FRAME_SIZE)
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self.assertAlmostEqual(self._outputsNeurons[i], 1.)

    def test_correct_operation_3(self):
        self.initDataPacket(1)
        self.initNeuralNetwork(0.5)
        calculateNeuralNetworkValues(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                                     self._inputsNeurons, self._hiddenNeurons, self._outputsNeurons, self._dataPacket,
                                     self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                                     self._PACKET_SIZE, self._DATA_FRAME_SIZE)
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self.assertAlmostEqual(self._outputsNeurons[i], 1.)

    def test_correct_operation_4(self):
        self.initDataPacket(1)
        self.initNeuralNetwork(0.2)
        calculateNeuralNetworkValues(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                                     self._inputsNeurons, self._hiddenNeurons, self._outputsNeurons, self._dataPacket,
                                     self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                                     self._PACKET_SIZE, self._DATA_FRAME_SIZE)
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self.assertAlmostEqual(self._outputsNeurons[i], 0.999995)

    def test_correct_operation_5(self):
        self.initDataPacket(2)
        self.initNeuralNetwork(0.02)
        calculateNeuralNetworkValues(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                                     self._inputsNeurons, self._hiddenNeurons, self._outputsNeurons, self._dataPacket,
                                     self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                                     self._PACKET_SIZE, self._DATA_FRAME_SIZE)
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self.assertAlmostEqual(round(self._outputsNeurons[i], 6), 0.754361)

    def test_incorrect_operation(self):
        self.initDataPacket(2)
        self.initNeuralNetwork(0.02)
        calculateNeuralNetworkValues(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                                     self._inputsNeurons, self._hiddenNeurons, self._outputsNeurons, self._dataPacket,
                                     self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                                     self._PACKET_SIZE, self._DATA_FRAME_SIZE)
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self.assertNotAlmostEqual(self._outputsNeurons[i], 0.754361)

    def test_sigmoid(self):
        x = 1.
        y = sigmoid(x)
        self.assertAlmostEqual(y, 0.73105859756)

        x = 1.5
        y = sigmoid(x)
        self.assertAlmostEqual(y, 0.81757450104)

        x = 2.
        y = sigmoid(x)
        self.assertAlmostEqual(y, 0.88079708815)

        x = 0.
        y = sigmoid(x)
        self.assertAlmostEqual(y, 0.50000000000)

        x = -0.5
        y = sigmoid(x)
        self.assertAlmostEqual(y, 0.37754067779)
