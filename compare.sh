#!/bin/bash
CYCLES=($(ls data/*-cycle))
CYCLESV2=($(ls data/*-cycleV2))

echo "cycles;cyclesV2"
for (( i = 0; i < ${#CYCLES[@]}; i++))
do
		printf $(grep "\#.*" ${CYCLES[i]}  | grep -E -o "[0-9]+\.[0-9]*|[0-9]+")
    printf ";"
		printf $(grep "\#.*" ${CYCLESV2[i]} | grep -E -o "[0-9]+\.[0-9]*|[0-9]+")
    printf "\n"
done