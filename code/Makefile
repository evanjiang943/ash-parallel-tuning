# File       : Makefile
# Description: Makefile for M5 Neural Network
# Copyright 2023 Harvard University. All Rights Reserved.

.PHONY: all clean

CXX := g++
CXXFLAGS := -O3 -Wall -Wextra -std=c++11 -fopenmp
LDFLAGS := -fopenmp
SRCS := m5_ASH.cpp m5_SH.cpp m5_neural_network.cpp
OBJS := $(patsubst %.cpp, %.o, $(SRCS))
TARGETS := m5_ASH m5_SH

all: $(TARGETS)

m5_ASH: m5_ASH.o m5_neural_network.o
	$(CXX) $(LDFLAGS) $^ -o $@

m5_SH: m5_SH.o m5_neural_network.o
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)
