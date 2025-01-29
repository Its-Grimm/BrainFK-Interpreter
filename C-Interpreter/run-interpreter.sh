#!/bin/bash

gcc -o runfile main.c stack.c
./runfile && rm runfile
