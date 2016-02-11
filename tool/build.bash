#!/bin/bash

# $1 file name
file="${1%.*}"

g++ -std=c++11 $file.t.cc $file.cc -I.

