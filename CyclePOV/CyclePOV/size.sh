#!/bin/bash

find ./ -name '*.o' | xargs arm-none-eabi-size --total
echo
arm-none-eabi-size $1.elf
