import unittest

from src.neural_network import *


class TestIntegrationTest(unittest.TestCase):
    def setUp(self) -> None:
        self._INPUT_NEURONS_COUNT = 6 * 10
        self._HIDDEN_NEURONS_COUNT = 60
        self._OUTPUT_NEURONS_COUNT = 5
        self._PACKET_SIZE = 10
        self._DATA_FRAME_SIZE = 6
        self._TOLERANCE_DEGREE = 0.90

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

    def test_correct_operation_result_d(self):
        NN_save_to_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                             self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                             "../test")

        NN_read_from_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                               self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                               "../test")

        calculateNeuralNetworkValues(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                                     self._inputsNeurons, self._hiddenNeurons, self._outputsNeurons, self._dataPacket,
                                     self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                                     self._PACKET_SIZE, self._DATA_FRAME_SIZE)

        result = NN_process_output(self._outputsNeurons, self._OUTPUT_NEURONS_COUNT, self._TOLERANCE_DEGREE)

        NN_save_to_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                             self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                             "../test")

        self.assertEqual(result, "d")

    def test_correct_operation_result_u(self):
        self.initNeuralNetwork(1.)
        NN_save_to_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                             self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                             "../test")

        NN_read_from_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                               self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                               "../test")

        calculateNeuralNetworkValues(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                                     self._inputsNeurons, self._hiddenNeurons, self._outputsNeurons, self._dataPacket,
                                     self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                                     self._PACKET_SIZE, self._DATA_FRAME_SIZE)

        result = NN_process_output(self._outputsNeurons, self._OUTPUT_NEURONS_COUNT, self._TOLERANCE_DEGREE)

        NN_save_to_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                             self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                             "../test")

        self.assertEqual(result, "u")

    def test_correct_operation_result_l(self):
        self.initDataPacket(1)

        NN_read_from_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                               self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                               "../test_result_l")

        calculateNeuralNetworkValues(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                                     self._inputsNeurons, self._hiddenNeurons, self._outputsNeurons, self._dataPacket,
                                     self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                                     self._PACKET_SIZE, self._DATA_FRAME_SIZE)

        result = NN_process_output(self._outputsNeurons, self._OUTPUT_NEURONS_COUNT, self._TOLERANCE_DEGREE)

        NN_save_to_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                             self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                             "../test_result_l")

        self.assertEqual(result, "l")
