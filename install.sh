#!/bin/bash

mkdir build
cd build
cmake ..
make
cd ..

echo "Copying shared library in /lib/"
sudo cp build/libEngineCoreSuper.so /lib/.

echo "Copying include header files in /usr/include/"
sudo cp -r include/* /usr/include/.
