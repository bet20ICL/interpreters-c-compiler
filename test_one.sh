#!/bin/bash

FILENAME="$1"
IPATH="compiler_tests/in/"${FILENAME}
BASENAME=$(basename ${FILENAME} .c)
DIRNAME=$(dirname ${FILENAME})
RPATH="compiler_tests/out/"${DIRNAME}
mkdir -p ${RPATH}


# compile input file, generate assembly
# echo "bin/c_compiler -S ${IPATH} -o ${RPATH}/${BASENAME}.s"
bin/c_compiler -S ${IPATH} -o ${RPATH}/${BASENAME}.s

# assemble the assembly program, generate object file
# echo "mips-linux-gnu-gcc -mfp32 -o ${RPATH}/${BASENAME}.o -c ${RPATH}/${BASENAME}.s"
mips-linux-gnu-gcc -g -mfp32 -o ${RPATH}/${BASENAME}.o -c ${RPATH}/${BASENAME}.s

# link object file with driver program, generate executable
# echo "mips-linux-gnu-gcc -mfp32 -static -o ${RPATH}/${BASENAME}.out ${RPATH}/${BASENAME}.o "compiler_tests/in/"${DIRNAME}/${BASENAME}_driver.c"
mips-linux-gnu-gcc -g -mfp32 -static -o ${RPATH}/${BASENAME}.out ${RPATH}/${BASENAME}.o "compiler_tests/in/"${DIRNAME}/${BASENAME}_driver.c

# emulate the executable on MIPS
# echo "qemu-mips ${RPATH}/${BASENAME}.out"
qemu-mips ${RPATH}/${BASENAME}.out