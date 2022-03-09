#!/bin/sh

find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\|h\|c\|hh\)' -exec clang-format -style=file -i {} \;