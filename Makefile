%-min-covering: %.graph
	src/minCoveringTree $< >$@

%-min-covering.tex: %.graph %-min-covering toTikz.py
	python3 toTikz.py -s $< $(word 2,$^) >$@

%-cycle: %.graph
	src/testCycleGraph $< >$@

%-cycle.tex: %.graph %-cycle toTikz.py
	python3 toTikz.py -s $< $(word 2,$^) >$@

%.pdf: %.tex
	pdflatex -output-directory $(@D) $^