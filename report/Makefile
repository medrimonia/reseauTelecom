
all: report.pdf

%.pdf: %.tex
	pdflatex $< && pdflatex $<

clean:
	rm -rf *.log
	rm -rf *.toc
	rm -rf *.aux

mrproper: clean
	rm -rf report.pdf