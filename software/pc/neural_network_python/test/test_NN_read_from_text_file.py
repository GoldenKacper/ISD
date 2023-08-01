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

    def test_always_correct(self):
        self.assertEqual(1, 1)

    def test_check_lists_not_empty(self):
        NN_read_from_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                               self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                               "../test")

        self.assertTrue(self._hiddenWeights)
        self.assertTrue(self._outputsWeights)
        self.assertTrue(self._hiddenBias)
        self.assertTrue(self._outputsBias)

        test_list = []
        self.assertFalse(test_list)

    def test_check_file_correct_reading_1(self):
        file = open("test.txt", "w")

        # saving neural network's weights and bias
        # saving hidden weights
        for i in range(self._HIDDEN_NEURONS_COUNT):
            for j in range(self._INPUT_NEURONS_COUNT):
                file.write(str(round(self._hiddenWeights[i][j], 6)) + " ")
            file.write("\n")
        file.write("\n")

        # saving outputs weights
        for i in range(self._OUTPUT_NEURONS_COUNT):
            for j in range(self._HIDDEN_NEURONS_COUNT):
                file.write(str(round(self._outputsWeights[i][j], 6)) + " ")
            file.write("\n")
        file.write("\n")

        # saving hidden bias
        for i in range(self._HIDDEN_NEURONS_COUNT):
            file.write(str(round(self._hiddenBias[i], 6)) + " ")
        file.write("\n\n")

        # saving outputs bias
        for i in range(self._OUTPUT_NEURONS_COUNT):
            file.write(str(round(self._outputsBias[i], 6)) + " ")

        file.close()

        NN_read_from_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                               self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                               "../test")

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

    def test_check_file_correct_reading_2(self):
        # initialize neural network lists {

        # hiddenWeights
        self._hiddenWeights = []
        for i in range(self._HIDDEN_NEURONS_COUNT):
            self._hiddenWeightsSup = []
            self._hiddenWeights.append(self._hiddenWeightsSup)
            for j in range(self._INPUT_NEURONS_COUNT):
                self._hiddenWeights[i].append(1237.123412)

        # outputsWeights
        self._outputsWeights = []
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self._outputsWeightsSup = []
            self._outputsWeights.append(self._outputsWeightsSup)
            for j in range(self._HIDDEN_NEURONS_COUNT):
                self._outputsWeights[i].append(0.0543)

        # hiddenBias
        self._hiddenBias = []
        for i in range(self._HIDDEN_NEURONS_COUNT):
            self._hiddenBias.append(0.)

        # outputsBias
        self._outputsBias = []
        for i in range(self._OUTPUT_NEURONS_COUNT):
            self._outputsBias.append(1.11)

        # } end init

        file = open("test.txt", "w")

        # saving neural network's weights and bias
        # saving hidden weights
        for i in range(self._HIDDEN_NEURONS_COUNT):
            for j in range(self._INPUT_NEURONS_COUNT):
                file.write(str(round(self._hiddenWeights[i][j], 6)) + " ")
            file.write("\n")
        file.write("\n")

        # saving outputs weights
        for i in range(self._OUTPUT_NEURONS_COUNT):
            for j in range(self._HIDDEN_NEURONS_COUNT):
                file.write(str(round(self._outputsWeights[i][j], 6)) + " ")
            file.write("\n")
        file.write("\n")

        # saving hidden bias
        for i in range(self._HIDDEN_NEURONS_COUNT):
            file.write(str(round(self._hiddenBias[i], 6)) + " ")
        file.write("\n\n")

        # saving outputs bias
        for i in range(self._OUTPUT_NEURONS_COUNT):
            file.write(str(round(self._outputsBias[i], 6)) + " ")

        file.close()

        NN_read_from_text_file(self._hiddenWeights, self._outputsWeights, self._hiddenBias, self._outputsBias,
                               self._INPUT_NEURONS_COUNT, self._HIDDEN_NEURONS_COUNT, self._OUTPUT_NEURONS_COUNT,
                               "../test")

        for i in range(self._HIDDEN_NEURONS_COUNT):
            for j in range(self._INPUT_NEURONS_COUNT):
                self.assertAlmostEqual(self._hiddenWeights[i][j], 1237.123412)

        for i in range(self._OUTPUT_NEURONS_COUNT):
            for j in range(self._HIDDEN_NEURONS_COUNT):
                self.assertAlmostEqual(self._outputsWeights[i][j], 0.0543)

        for i in range(self._HIDDEN_NEURONS_COUNT):
            self.assertAlmostEqual(self._hiddenBias[i], 0.)

        for i in range(self._OUTPUT_NEURONS_COUNT):
            self.assertAlmostEqual(self._outputsBias[i], 1.11)
