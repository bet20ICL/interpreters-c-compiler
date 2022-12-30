#!/bin/bash
BASENAME=$(basename ${4} .s)
DIRNAME=$(dirname ${4})
ASTNAME=${DIRNAME}/${BASENAME}.stderr.txt
cat $2 | ./bin/compiler 2> $ASTNAME 1> $4