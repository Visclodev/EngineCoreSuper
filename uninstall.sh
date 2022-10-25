#!/bin/bash

echo "removing shared lib from /lib"
sudo rm -f /lib/libEngineCoreSuper.so
echo "removing shared lib from /lib64"
sudo rm -f /lib64/libEngineCoreSuper.so
echo "removing include headers from /usr/include"
sudo rm -rf /usr/include/EngineCoreSuper

echo "removing build directory"
rm -rf build
echo "Done!"
