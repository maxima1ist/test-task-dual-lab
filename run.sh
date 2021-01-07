#!/bin/bash

set -e

g++ -w -std=c++17 src/main.cpp src/timetable.h src/timetable.cpp -o timetable
./timetable

echo All tests passed!