CPP=gcc
LD=gcc
SPECIALFLAGS=--exceptions
ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS=$(shell root-config --libs)

CFLAGS = $(SPECIALFLAGS) -I- -I../ -I. -I./include -I../../include -I$(SRT_PUBLIC_CONTEXT)/include
LFLAGS = $(SPECIALFLAGS) -L../../lib/$(SRT_SUBDIR)/

RCXX=$(CFLAGS) $(ROOTCFLAGS)
RLXX=$(LFLAGS) $(ROOTLIBS)

TARGET=ExtractTurnOnCurves

SRC= $(TARGET).cpp

%.o: %.cpp
	$(CPP) $(RCXX) -c $<

all: $(TARGET)

$(TARGET).o: $(TARGET).cpp
	$(CPP) $(RCXX) -c $(TARGET).cpp
$(TARGET): $(SRC:.cpp=.o)
	$(LD) $(SRC:.cpp=.o) $(RLXX) -o $(TARGET)

clean:
	rm -rf ti_files
	rm -f *~ *.o
	rm -f $(TARGET)
