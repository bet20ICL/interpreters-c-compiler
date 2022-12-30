#!/bin/bash

FILENAME="$1"
IPATH="compiler_tests/in/"${FILENAME}
BASENAME=$(basename ${FILENAME} .c)
DIRNAME=$(dirname ${FILENAME})
RPATH="compiler_tests/ref/"${DIRNAME}
mkdir -p ${RPATH}

# compile input file, generate assembly
echo "mips-linux-gnu-gcc -S -mfp32 ${IPATH} -o ${RPATH}/${BASENAME}.s"
mips-linux-gnu-gcc -S -mfp32 ${IPATH} -o ${RPATH}/${BASENAME}.s

# assemble the assembly program, generate object file
echo "mips-linux-gnu-gcc -mfp32 -o ${RPATH}/${BASENAME}.o -c ${RPATH}/${BASENAME}.s"
mips-linux-gnu-gcc -mfp32 -o ${RPATH}/${BASENAME}.o -c ${RPATH}/${BASENAME}.s

# link object file with driver program, generate executable
echo "mips-linux-gnu-gcc -mfp32 -static -o ${RPATH}/${BASENAME}.out ${RPATH}/${BASENAME}.o "compiler_tests/in/"${DIRNAME}/${BASENAME}_driver.c"
mips-linux-gnu-gcc -mfp32 -static -o ${RPATH}/${BASENAME}.out ${RPATH}/${BASENAME}.o "compiler_tests/in/"${DIRNAME}/${BASENAME}_driver.c

# emulate the executable on MIPS
echo "qemu-mips ${RPATH}/${BASENAME}.out"
qemu-mips ${RPATH}/${BASENAME}.out

if [[ "$?" -ne "0" ]]; then
        echo "Failed"
    else
        echo "Passed"
fi
