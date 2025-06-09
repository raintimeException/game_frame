#!/usr/bin/bash

set -xe

cc -g -Wall -Wextra -o app main.c ./raylib/libraylib.a -lm

time ./app
