#!/bin/bash
g++ src/duipai.cpp -O2 -O3 -Ofast -o duipai -std=c++17 -Wall -lreadline -ltermcap -w -pthread
echo -e "\033[32;1mOK\033[0m"