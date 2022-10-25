#!/bin/bash

mkdir -p build
cd build
cmake ..
make
cd ..

cp src/*.hpp include/EngineCoreSuper/.
mkdir -p include/EngineCoreSuper/Components
cp src/Components/*.hpp include/EngineCoreSuper/Components/.
mkdir -p include/EngineCoreSuper/Systems
cp src/Systems/*.hpp include/EngineCoreSuper/Systems/.

echo "Copying shared library in /lib/"
sudo cp build/libEngineCoreSuper.so /lib/.

echo "Copying shared library in /lib64/"
sudo cp build/libEngineCoreSuper.so /lib64/.

echo "Copying include header files in /usr/include/"
sudo cp -r include/* /usr/include/.
