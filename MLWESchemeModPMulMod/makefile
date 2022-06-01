CPP=g++

FLAGS=-g -O2

AUTOFLAGS=-std=c++11 -pthread -march=native

OPS=-lntl -lgmp -lm

FILES= main.cpp encryption.cpp decryption.cpp helper.cpp

run:
	clear
	$(CPP) $(FLAGS) $(AUTOFLAGS) $(FILES) -o main $(OPS)
	./main