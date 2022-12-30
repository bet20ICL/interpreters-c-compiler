#!/bin/bash

echo "========================================"
echo " Cleaning the temporaries and outputs"
make clean

echo "========================================"
echo " Force building compiler"

make bin/c_compiler

if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
    exit 1;
fi
echo "========================================="

INPUT="$1"
FILENAME="$1"

if [[ "$1" ]]; then
    if [[ $FILENAME == *.c ]]; then
        echo "Testing input: ${FILENAME}"
        echo "========================================="
        ./test_one.sh ${FILENAME}
        if [[ "$?" -ne "0" ]]; then
            echo "${1} Failed"
        else
            echo "${1} Passed"
        fi
    else
        PASSED=0
        CHECKED=0
        b=$FILENAME;
        i=compiler_tests/in/$b
        echo "========================================="
        echo "Testing inputs from folder ${b}/" ;
        echo "========================================="
        for j in ${i}/*_driver.c; do
            t=$(basename ${j})
            f=${b}/${t%_driver.c}.c;
            echo "-------------------------------------"
            echo ""
            echo "Testing input: ${f}"
            ./test_one.sh ${f}
            if [[ "$?" -eq 0 ]]; then
                PASSED=$(( ${PASSED}+1 ));
            else
                echo "Fail"
            fi
            CHECKED=$(( ${CHECKED}+1 ));
            echo ""
        done
        echo "########################################"
        echo "Passed ${PASSED} out of ${CHECKED}".
        echo ""
    fi
    
else
    echo "No arguments, testing all inputs"
    PASSED=0
    CHECKED=0
    for i in compiler_tests/in/*; do
        b=$(basename ${i});
        if [[ $b == "ours" ]]; then
            echo "ignores"
        else
            echo "========================================="
            echo "Testing inputs from ${b}/" ;
            echo "========================================="
            for j in ${i}/*_driver.c; do
                t=$(basename ${j})
                f=${b}/${t%_driver.c}.c;

                echo "-------------------------------------"
                echo ""
                echo "Testing input: ${f}"
                ./test_one.sh ${f}
                if [[ "$?" -eq 0 ]]; then
                    PASSED=$(( ${PASSED}+1 ));
                else
                    echo "Fail"
                fi
                CHECKED=$(( ${CHECKED}+1 ));
                echo ""
            done
        fi
        
    done
    echo "########################################"
    echo "Passed ${PASSED} out of ${CHECKED}".
    echo ""
fi

