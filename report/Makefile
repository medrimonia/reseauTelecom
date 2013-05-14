
all: report.pdf

%.pdf: %.tex
	pdflatex $< && pdflatex $<

report.pdf: graph_sample.tex

clean:
	rm -rf *.log
	rm -rf *.toc
	rm -rf *.aux

mrproper: clean
	rm -rf report.pdf