#!/bin/bash

INPUT="data/compare_file"
OUTPUT="data/comparison"

POINT_SIZE=1.5

gnuplot -persist <<PLOT

set title "Cost of the covering depending on the method"

set yrange [0:*]

set xlabel "File"

set ylabel "Covering cost"

set datafile separator ";"

set tics out

#In case for building an eps-file ...
#set terminal postscript enhanced color solid eps 15
#set output "${OUTPUT}.eps"

#In case for building a png-file ...
set terminal png size 1024,768
set output "${OUTPUT}.png"

plot '${INPUT}' using 1 with points pointtype 7 pointsize ${POINT_SIZE} \
        title "cycle", \
     '${INPUT}' using 2 with points pointtype 7 pointsize ${POINT_SIZE} \
        lc rgb "blue" title "cycleV2"
quit
PLOT