TARGET     = doku

all : settings pdf # dvi # pdf ps 

dvi  : $(TARGET).dvi
pdf  : $(TARGET).pdf
ps   : $(TARGET).ps
html : $(TARGET).html

settings : 
	@echo ==================================
	@echo "TARGET    = $(TARGET)"
	@echo ==================================


$(TARGET).pdf : $(TARGET).tex 
	pdflatex $(TARGET).tex
	bibtex $(TARGET)
	pdflatex $(TARGET).tex
	pdflatex $(TARGET).tex


$(TARGET).dvi : $(TARGET).tex 
	latex $(TARGET).tex
	bibtex $(TARGET)
	latex $(TARGET).tex
	latex $(TARGET).tex

$(TARGET).html : $(TARGET).tex
	hevea -fix $(TARGET).tex

%.ps : %.dvi 
	dvips -o $@ $<

#%.pdf : %.dvi
#	dvipdfm -p letter $<


archive : pdf 
	tar -cvhzf $(TARGET).tgz Makefile *.cls *.bib *.tex fig/*.eps *.pdf


clean :
	rm -f *.aux *.dvi *.ps *.log *.out *.bbl *.blg *~ *.sav *.bak
	rm -f $(TARGET).tgz
	rm -f $(TARGET).pdf
	rm -f *.html *.gif *.haux *.htoc
	rm -f $(TARGET)*.png
	rm -f $(TARGET).image.tex

submit : $(TARGET).pdf
	cp $(TARGET).pdf submit/SPPEXA_HA_Part_B_full.pdf

cvsimport : clean
	cvs import -m "Initial Import" cluster fuerling 

