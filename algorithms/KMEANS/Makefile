ROOT=$(PWD)
CC=g++
SRC := $(ROOT)/src
CFLAGS := -std=c++11 -DEUCLID
INCLUDE_DIR := $(ROOT)/include

all: kmeans

kmeans: $(SRC)/kmeans.cpp
	$(CC) $(CFLAGS) $(SRC)/kmeans.cpp -o kmeans -L$(ENVIRONMENT)/import/lib/ -I$(INCLUDE_DIR) -I$(ENVIRONMENT)/import/include/ -ldata

clean:
	rm kmeans