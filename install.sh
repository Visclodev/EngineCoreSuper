#!/bin/bash

mkdir build
cd build
cmake ..
make
cd ..

cp src/*.hpp include/EngineCoreSuper/.
mkdir include/EngineCoreSuper/Components
cp src/Components/*.hpp include/EngineCoreSuper/Components/.
mkdir include/EngineCoreSuper/Systems
cp src/Systems/*.hpp include/EngineCoreSuper/Systems/.

echo "Copying shared library in /lib/"
sudo cp build/libEngineCoreSuper.so /lib/.

echo "Copying include header files in /usr/include/"
sudo cp -r include/* /usr/include/.
