cmake_minimum_required(VERSION 3.22)
project(neuralNetwork C)

set(CMAKE_C_STANDARD 23)

add_executable(neuralNetwork main.c neural_network.c neural_network.h test.c neural_network_for_micropython.c data_reader.c data_reader.h)
