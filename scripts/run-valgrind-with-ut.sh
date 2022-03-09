#!/bin/sh

mkdir -p output

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=output/valgrind-out.txt \
         /code/build/src/tests/cpp/unit-test $@