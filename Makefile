IMPORT_ROOT=$(PWD)/import
CC=g++
INCLUDE_DIR := $(IMPORT_ROOT)/include
SRC := $(IMPORT_ROOT)/src
CFLAGS := -std=c++11 -g
LIB_DATA := libdata.so

all : $(LIB_DATA)

$(LIB_DATA) : libdir objdir obj/preprocess.o obj/data.o
	$(CC) $(CFLAGS) -o $(IMPORT_ROOT)/lib/$(LIB_DATA) $(IMPORT_ROOT)/obj/*.o
	rm -r $(IMPORT_ROOT)/obj

libdir :
	mkdir -p $(IMPORT_ROOT)/lib

objdir :
	mkdir -p $(IMPORT_ROOT)/obj

obj/preprocess.o: $(SRC)/preprocess.cc
	$(CC) -fPIC $(CFLAGS) -o $(IMPORT_ROOT)/obj/preprocess.o -I$(INCLUDE_DIR) -c $(SRC)/preprocess.cc

obj/data.o: $(SRC)/data.cc
	$(CC) -fPIC $(CFLAGS) -o $(IMPORT_ROOT)/obj/data.o -I$(INCLUDE_DIR) -c $(SRC)/data.cc

clean:
	rm -r $(IMPORT_ROOT)/lib
	rm -r $(IMPORT_ROOT)/obj
