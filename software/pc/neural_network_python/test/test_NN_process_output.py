import unittest

from src.neural_network import *


class TestNNProcessOutput(unittest.TestCase):
    def setUp(self) -> None:
        self._OUTPUT_NEURONS_COUNT = 5
        self._TOLERANCE_DEGREE = 0.90

        self._test_outputs_1 = [0.1, 0.1, 0., 0.9, 0.4]

    # is to check whether the test themselves work at all
    def test_always_correct(self):
        self.assertEqual(1, 1)

    def test_correct_operation(self):
        self.setUp()
        result = NN_process_output(self._test_outputs_1, self._OUTPUT_NEURONS_COUNT, self._TOLERANCE_DEGREE)
        self.assertEqual(result, "w")

        self._test_outputs_1 = [0.1, 0.99, 0., 0.09, 0.4]
        result = NN_process_output(self._test_outputs_1, self._OUTPUT_NEURONS_COUNT, self._TOLERANCE_DEGREE)
        self.assertEqual(result, "l")

    def test_incorrect_operation(self):
        self.setUp()
        result = NN_process_output(self._test_outputs_1, self._OUTPUT_NEURONS_COUNT, self._TOLERANCE_DEGREE)
        self.assertNotEqual(result, "n")

    def test_correct_operation_with_result_d(self):
        self.setUp()
        self._test_outputs_1 = [0.2, 0.1, 0.3, 0.4, 0.5]
        result = NN_process_output(self._test_outputs_1, self._OUTPUT_NEURONS_COUNT, self._TOLERANCE_DEGREE)
        self.assertEqual(result, "d")

    def test_correct_operation_with_result_u(self):
        self.setUp()
        self._test_outputs_1 = [0.9, 0.91, 0.3, 0.95, 0.5]
        result = NN_process_output(self._test_outputs_1, self._OUTPUT_NEURONS_COUNT, self._TOLERANCE_DEGREE)
        self.assertEqual(result, "u")