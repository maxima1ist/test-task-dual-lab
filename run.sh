#!/bin/bash

set -e

g++ -w -std=c++17 src/main.cpp src/timetable.h src/timetable.cpp -o timetable.out
./timetable.out

echo The program worked correctly!