GRAPHS=$(wildcard data/*.graph)

CYCLES=$(GRAPHS:.graph=-cycle)
CYCLESV2=$(GRAPHS:.graph=-cycleV2)

all: cycles cyclesV2

cycles: $(CYCLES)

cyclesV2: $(CYCLESV2)

data/compare_file: cycles cyclesV2 compare.sh
	./compare.sh >$@

data/compare_time: cycles cyclesV2 compare_time.sh
	./compare_time.sh >$@

data/comparison.png: data/compare_file plot.sh
	./plot.sh

data/time_comparison.png: data/compare_time plot_time.sh
	./plot_time.sh

view-time-compare: data/time_comparison.png
	eog $<

view-compare: data/comparison.png
	eog $<

%-min-covering: %.graph
	src/minCoveringTree $< >$@

%-min-covering.tex: %.graph %-min-covering toTikz.py
	python3 toTikz.py -s $< $(word 2,$^) >$@

%-cycle: %.graph src/testCycleGraph
	src/testCycleGraph $< >$@

%-cycleV2: %.graph src/testCycleGraphV2
	src/testCycleGraphV2 $< >$@

%-cycle.tex: %.graph %-cycle toTikz.py
	python3 toTikz.py -s $< $(word 2,$^) >$@

%-cycleV2.tex: %.graph %-cycleV2 toTikz.py
	python3 toTikz.py -s $< $(word 2,$^) >$@

%.pdf: %.tex
	pdflatex -output-directory $(@D) $^

%.view: %.pdf
	evince $<

FORCE:

src/testCycleGraph: FORCE
	make -C src testCycleGraph

src/testCycleGraphV2: FORCE
	make -C src testCycleGraphV2

clean:
	rm -f data/*-min-covering
	rm -f data/*-cycleV2
	rm -f data/*.tex
	rm -f data/*-cycle
	rm -f data/compare_file
	rm -f data/comparison.png

mrproper: clean
	rm -f data/*.pdf