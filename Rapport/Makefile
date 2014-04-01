SRC=$(wildcard *.tex)
PDF=$(SRC:.tex=.pdf)

all: $(PDF)

rebuild: nuke all

%.pdf: %.tex
	latex $<
	latex $<
	dvips $(shell basename $< .tex).dvi
	ps2pdf $(shell basename $< .tex).ps

nuke:
	rm -rf *.pdf *.ps *.dvi *.aux *.log *.tns *.out *.toc
