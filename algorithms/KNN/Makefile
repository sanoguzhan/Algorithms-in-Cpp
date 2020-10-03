ROOT=$(PWD)
CC=g++
SRC := $(ROOT)/src
CFLAGS := -std=c++11 -DEUCLID
INCLUDE_DIR := $(ROOT)/include

all: knn

knn: $(SRC)/knn.cpp
	$(CC) $(CFLAGS) $(SRC)/knn.cpp -o knn -L$(ENVIRONMENT)/import/lib/ -I$(INCLUDE_DIR) -I$(ENVIRONMENT)/import/include -ldata

clean:
	rm knn