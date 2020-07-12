IMPORT_ROOT=$(PWD)
CC=g++
INCLUDE_DIR := $(IMPORT_ROOT)/include
SRC := $(IMPORT_ROOT)/src
CFLAGS := -shared -std=c++11 -g -Wall -fmax-errors=10 -Wextra
LIB_DATA := libdata.so

all : $(LIB_DATA)

$(LIB_DATA) : libdir objdir obj/preprocess.o obj/data.o
	$(CC) $(CFLAGS) -o $(IMPORT_ROOT)/lib/$(LIB_DATA) $(IMPORT_ROOT)/obj/*.o
	rm -r $(IMPORT_ROOT)/obj

libdir :
	mkdir -p $(IMPORT_ROOT)/lib

objdir :
	mkdir -p $(IMPORT_ROOT)/obj

obj/preprocess.o: $(SRC)/preprocess.cpp
	$(CC) -fPIC $(CFLAGS) -o $(IMPORT_ROOT)/obj/preprocess.o -I$(INCLUDE_DIR) -c $(SRC)/preprocess.cpp

obj/data.o: $(SRC)/data.cpp
	$(CC) -fPIC $(CFLAGS) -o $(IMPORT_ROOT)/obj/data.o -I$(INCLUDE_DIR) -c $(SRC)/data.cpp

clean:
	rm -r $(IMPORT_ROOT)/lib
	rm -r $(IMPORT_ROOT)/obj
