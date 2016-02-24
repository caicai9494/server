#!/bin/bash

# $1 file name

if [ -e $1.h ]; then
    echo "$1.h exists"
    echo "exiting..."
    exit
fi

if [ -e $1.cc ]; then
    echo "$1.cc exists"
    echo "exiting..."
    exit
fi

if [ -e $1.t.cc ]; then
    echo "$1.t.cc exists"
    echo "exiting..."
    exit
fi

file=$1
FILE=$(echo $file | awk '{print toupper($0)}')

echo "#ifndef ${FILE}_H 
#define ${FILE}_H

namespace LZ {

class $file {

  public:

    $file() {}

    ~$file() {}

  private:

};

} // close namespace

#endif" > $file.h

echo "#include <$file.h>

namespace LZ {

} // close namespace

" > $file.cc

echo "#include <$file.h> " > $file.t.cc
cat tool/template.cc >> $file.t.cc
