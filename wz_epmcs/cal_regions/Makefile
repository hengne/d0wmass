LIBS = `root-config --libs`
OPTCOMP = `root-config --cflags` 

SPECIALFLAGS= --exceptions
NFLAGS = $(SPECIALFLAGS)
CFLAGS = $(SPECIALFLAGS) -I- -I../ -I. 
LFLAGS = $(SPECIALFLAGS) -L../../lib/$(SRT_SUBDIR)/

RCXX=$(NFLAGS) $(ROOTCFLAGS)
DBG=#-g

CC = g++ ${DBG} $(RCXX) $(OPTCOMP) 

all: example

go: example
	./example

example: example.o cal_regions.o
	$(CC) example.o cal_regions.o $(LIBS) -o example

example.o: example.C
	$(CC) -c example.C

cal_regions.o: cal_regions.C cal_regions.h
	$(CC) -c cal_regions.C

clean:
	rm -rf example core ti_files *.o
  
