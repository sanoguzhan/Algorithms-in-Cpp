ROOT=$(PWD)
CC=g++
SRC := $(ROOT)/src
CFLAGS := -std=c++11 -DEUCLID
INCLUDE_DIR := $(ROOT)/include

all: main

main: $(SRC)/knn.cpp
	$(CC) $(CFLAGS) $(SRC)/knn.cpp -o main -L$(ENVIRONMENT)/import/lib/ -I$(INCLUDE_DIR) -I$(ENVIRONMENT)/import/include -ldata

clean:
	rm main

