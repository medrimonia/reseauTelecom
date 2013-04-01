%-min-covering: %.graph
	src/minCoveringTree $^ >$@

%-min-covering.tex: %.graph %-min-covering
	python3 toTikz.py -s $^ >$@

%.pdf: %.tex
	pdflatex -output-directory $(@D) $^