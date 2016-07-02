#!/bin/bash

clang -cc1 global.c -emit-llvm

llc -march=cpp global.ll
