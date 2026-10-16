#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
objects=$(find build -maxdepth 1 -name '*.o' ! -name main.o)
c++ -std=c++17 -fPIC -I. -Ibuild tests/smoke.cpp $objects \
    $(pkg-config --cflags --libs Qt6Widgets Qt6Concurrent Qt6Core5Compat) -o build/smoke
QT_QPA_PLATFORM=offscreen build/smoke "$PWD/build/smoke.png"
