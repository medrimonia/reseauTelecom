#!/bin/bash
CYCLES=($(ls data/*-cycle))
CYCLESV2=($(ls data/*-cycleV2))

REGEXP="[0-9]+\.[0-9]*|[0-9]+"

echo "cycles;cyclesV2"
for (( i = 0; i < ${#CYCLES[@]}; i++))
do
		printf $(grep "\#Total cost" ${CYCLES[i]}  | grep -E -o "$REGEXP")
    printf ";"
		printf $(grep "\#Total cost" ${CYCLESV2[i]} | grep -E -o "$REGEXP")
    printf "\n"
done