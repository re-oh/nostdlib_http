#!/bin/sh

gcc -nostdlib -std=c99 -fno-stack-protector -no-pie -o ./build/build main.c