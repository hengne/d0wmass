
SRC := $(wildcard *.sgml)

all: $(SRC:.sgml=.html) $(SRC:.sgml=.pdf)

%.html : %.sgml
	linuxdoc -B html $<

%.pdf : %.sgml
	linuxdoc -B latex -o pdf $<


clean:
	rm -rf *.html *.pdf *~

