#!/bin/bash
cd C_H_File
gcc -w *.c -o SystemRun -lsqlite3
./SystemRun
rm SystemRun

