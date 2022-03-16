#!/bin/sh

mkdir -p valgrind-output

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-output/valgrind-out.txt \
         /code/build/src/tests/cpp/unit-test $@