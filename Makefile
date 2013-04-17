%-min-covering: %.graph
	src/minCoveringTree $< >$@

%-min-covering.tex: %.graph %-min-covering toTikz.py
	python3 toTikz.py -s $< $(word 2,$^) >$@

%-cycle: %.graph
	src/testCycleGraph $< >$@

%-cycleV2: %.graph
	src/testCycleGraphV2 $< >$@

%-cycle.tex: %.graph %-cycle toTikz.py
	python3 toTikz.py -s $< $(word 2,$^) >$@

%-cycleV2.tex: %.graph %-cycleV2 toTikz.py
	python3 toTikz.py -s $< $(word 2,$^) >$@

%.pdf: %.tex
	pdflatex -output-directory $(@D) $^

clean:
	rm -f data/*-min-covering
	rm -f data/*-cycleV2
	rm -f data/*.tex
	rm -f data/*-cycle

mrproper: clean
	rm -f data/*.pdf