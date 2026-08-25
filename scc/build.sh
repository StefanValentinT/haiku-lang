#!/bin/sh

set -xe

clang -std=c99 -Isrc src/*.c -include src/prelude.h -o scc -O0 \
  -Wall -Wextra -Wpedantic -Wfloat-equal -Wpointer-arith -Wconversion \
  -fsanitize=address -g # for debugging
