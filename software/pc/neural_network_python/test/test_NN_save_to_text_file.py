import unittest

from src.neural_network import *


class TestNNSaveToTextFile(unittest.TestCase):
    def setUp(self) -> None:
        self._INPUT_NEURONS_COUNT = 6 * 10
        self._HIDDEN_NEURONS_COUNT = 60
        self._OUTPUT_NEURONS_COUNT = 5
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

        # } end init

    # is to check whether the test themselves work at all
    def test_always_correct(self):
        self.assertEqual(1, 1)

    def test_check_file_not_empty(self):
        NN_save_to_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                             self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                             "../test")
        file = open("test.txt", "r")
        data = file.read()
        self.assertTrue(data)
        file.close()

    def test_check_file_correct_saving_1(self):
        NN_save_to_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                             self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                             "../test")
        file = open("test.txt", "r")

        for i in range(self._HIDDEN_NEURONS_COUNT):
            data = file.readline()
            data_from_line = re.split(" ", data)
            for j in range(self._INPUT_NEURONS_COUNT):
                self._hiddenWeights[i][j] = float(data_from_line[j])

        data = file.readline()

        # read outputs weights of neural network
        for i in range(self._OUTPUT_NEURONS_COUNT):
            data = file.readline()
            data_from_line = re.split(" ", data)
            for j in range(self._HIDDEN_NEURONS_COUNT):
                self._outputsWeights[i][j] = float(data_from_line[j])

        data = file.readline()

        # read hidden bias of neural network
        data = file.readline()
        data_from_line = re.split(" ", data)
        for i in range(self._HIDDEN_NEURONS_COUNT):
            self._hiddenBias[i] = float(data_from_line[i])

        data = file.readline()

        # read outputs bias of neural network
        data = file.readline()
        data_from_line = re.split(" ", data)
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self._outputsBias[i] = float(data_from_line[i])

        file.close()

        for i in range(self._HIDDEN_NEURONS_COUNT):
            for j in range(self._INPUT_NEURONS_COUNT):
                self.assertAlmostEqual(self._hiddenWeights[i][j], 0.)

        for i in range(self._OUTPUT_NEURONS_COUNT):
            for j in range(self._HIDDEN_NEURONS_COUNT):
                self.assertAlmostEqual(self._outputsWeights[i][j], 0.)

        for i in range(self._HIDDEN_NEURONS_COUNT):
            self.assertAlmostEqual(self._hiddenBias[i], 0.)

        for i in range(self._OUTPUT_NEURONS_COUNT):
            self.assertAlmostEqual(self._outputsBias[i], 0.)

    def test_check_file_correct_saving_2(self):
        # initialize neural network lists {

        # hiddenWeights
        self._hiddenWeights = []
        for i in range(self._HIDDEN_NEURONS_COUNT):
            self._hiddenWeightsSup = []
            self._hiddenWeights.append(self._hiddenWeightsSup)
            for j in range(self._INPUT_NEURONS_COUNT):
                self._hiddenWeights[i].append(0.001)

        # outputsWeights
        self._outputsWeights = []
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self._outputsWeightsSup = []
            self._outputsWeights.append(self._outputsWeightsSup)
            for j in range(self._HIDDEN_NEURONS_COUNT):
                self._outputsWeights[i].append(2.3)

        # hiddenBias
        self._hiddenBias = []
        for i in range(self._HIDDEN_NEURONS_COUNT):
            self._hiddenBias.append(1.)

        # outputsBias
        self._outputsBias = []
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self._outputsBias.append(-0.9875)

        # } end init

        NN_save_to_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                             self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                             "../test")
        file = open("test.txt", "r")

        for i in range(self._HIDDEN_NEURONS_COUNT):
            data = file.readline()
            data_from_line = re.split(" ", data)
            for j in range(self._INPUT_NEURONS_COUNT):
                self._hiddenWeights[i][j] = float(data_from_line[j])

        data = file.readline()

        # read outputs weights of neural network
        for i in range(self._OUTPUT_NEURONS_COUNT):
            data = file.readline()
            data_from_line = re.split(" ", data)
            for j in range(self._HIDDEN_NEURONS_COUNT):
                self._outputsWeights[i][j] = float(data_from_line[j])

        data = file.readline()

        # read hidden bias of neural network
        data = file.readline()
        data_from_line = re.split(" ", data)
        for i in range(self._HIDDEN_NEURONS_COUNT):
            self._hiddenBias[i] = float(data_from_line[i])

        data = file.readline()

        # read outputs bias of neural network
        data = file.readline()
        data_from_line = re.split(" ", data)
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self._outputsBias[i] = float(data_from_line[i])

        file.close()

        for i in range(self._HIDDEN_NEURONS_COUNT):
            for j in range(self._INPUT_NEURONS_COUNT):
                self.assertAlmostEqual(self._hiddenWeights[i][j], 0.001)

        for i in range(self._OUTPUT_NEURONS_COUNT):
            for j in range(self._HIDDEN_NEURONS_COUNT):
                self.assertAlmostEqual(self._outputsWeights[i][j], 2.3)

        for i in range(self._HIDDEN_NEURONS_COUNT):
            self.assertAlmostEqual(self._hiddenBias[i], 1.)

        for i in range(self._OUTPUT_NEURONS_COUNT):
            self.assertAlmostEqual(self._outputsBias[i], -0.9875)

    def test_check_file_incorrect_check_saving(self):
        NN_save_to_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                             self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                             "../test")
        file = open("test.txt", "r")

        for i in range(self._HIDDEN_NEURONS_COUNT):
            data = file.readline()
            data_from_line = re.split(" ", data)
            for j in range(self._INPUT_NEURONS_COUNT):
                self._hiddenWeights[i][j] = float(data_from_line[j])

        data = file.readline()

        # read outputs weights of neural network
        for i in range(self._OUTPUT_NEURONS_COUNT):
            data = file.readline()
            data_from_line = re.split(" ", data)
            for j in range(self._HIDDEN_NEURONS_COUNT):
                self._outputsWeights[i][j] = float(data_from_line[j])

        data = file.readline()

        # read hidden bias of neural network
        data = file.readline()
        data_from_line = re.split(" ", data)
        for i in range(self._HIDDEN_NEURONS_COUNT):
            self._hiddenBias[i] = float(data_from_line[i])

        data = file.readline()

        # read outputs bias of neural network
        data = file.readline()
        data_from_line = re.split(" ", data)
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self._outputsBias[i] = float(data_from_line[i])

        file.close()

        for i in range(self._HIDDEN_NEURONS_COUNT):
            for j in range(self._INPUT_NEURONS_COUNT):
                self.assertNotAlmostEqual(self._hiddenWeights[i][j], 1.)

        with self.assertRaises(IndexError):
            for i in range(self._HIDDEN_NEURONS_COUNT):
                self.assertAlmostEqual(self._outputsBias[i], 0.)




