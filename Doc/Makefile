TITLE = CyclePOV

TMP_DIR = latexCompilationFiles
PDFLATEX_FLAGS = -interaction=nonstopmode -output-directory=$(TMP_DIR)

DIRS = $(shell shopt -s globstar && echo **/) ./
DEPS = $(foreach DIR, $(DIRS), $(wildcard $(DIR)*.tex $(DIR)*.sty $(DIR)*.bib))

.PHONY: all, clean, pdf

all : pdf
pdf : $(TMP_DIR) $(TITLE).pdf

$(TITLE).pdf : $(DEPS)
	@#Triple compilación para actualizar las referencias
	pdflatex $(PDFLATEX_FLAGS) main.tex
	bibtex ${TMP_DIR}/main.aux
	pdflatex $(PDFLATEX_FLAGS) main.tex
	pdflatex $(PDFLATEX_FLAGS) main.tex
	mv ${TMP_DIR}/main.pdf $(TITLE).pdf

$(TMP_DIR) :
	@mkdir -v $(TMP_DIR)

clean:
	@-rm -v *.log 2>/dev/null; true
	@-rm -v *.aux 2>/dev/null; true
	@-rm -v *.pdf 2>/dev/null; true
	@-rm -v *.dvi 2>/dev/null; true
	@-rm -v *.toc 2>/dev/null; true
	@-rm -v *.out 2>/dev/null; true
	@-rm -v *.bbl 2>/dev/null; true
	@-rm -v *.blg 2>/dev/null; true
	@-rm -frv $(TMP_DIR) 2>/dev/null; true
	@mkdir $(TMP_DIR)
