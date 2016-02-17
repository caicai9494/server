#!/bin/bash

# $1 FILE name

FILE=makefile.$1

if [ -e ${FILE} ]; then
    echo "makeFILE.$1 exists"
    echo "exiting..."
    exit
fi

echo 'CC=g++ 

LIBS=
LIBS_INC=.

TSK=
SRC=

PTHREAD_ENABLED=#-pthread

CPPFLAGS=-I$(LIBS_INC) -L$(LIBS) -g -std=c++11 $(PTHREAD_ENABLED)

all:
	$(CC) $(CPPFLAGS) -o $(TSK) $(SRC)

clean:
	rm -f *.o $(TSK)' > ${FILE}

