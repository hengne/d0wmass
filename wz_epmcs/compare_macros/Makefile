# Use the following on IRIX 6.5 and Linux 2.4


LIBS = `root-config --libs`
OPTCOMP = `root-config --cflags` 

SPECIALFLAGS= --exceptions
CFLAGS = $(SPECIALFLAGS) -I- -I../ -I.
LFLAGS = $(SPECIALFLAGS) -L../../lib/$(SRT_SUBDIR)/

RCXX=$(CFLAGS) $(ROOTCFLAGS)

#CC = KCC -n32 --exceptions --thread_safe -O $(OPTCOMP)
#CC = KCC +K0 --exceptions --thread_safe -O $(OPTCOMP)
CC = g++ -g $(RCXX) $(OPTCOMP) 

all: run_zee run_wenu run_znunu run_zee_minuit run_chi2 dumpHist
# link_zee

dumpHist: dumpHist.o
	$(CC) dumpHist.o $(LIBS) -o dumpHist

dumpHist.o: dumpHist.cpp
	$(CC) -c dumpHist.cpp -o dumpHist.o

run_zee: zeecomp.o PParameterReader.o
	$(CC) zeecomp.o PParameterReader.o $(LIBS) -o zeecomp

zeecomp.o: zeecomp.cpp  PParameterReader.hpp
	$(CC) -c zeecomp.cpp -o zeecomp.o

run_zee_minuit: zeecomp_minuit.o  PParameterReader.o 
	$(CC) zeecomp_minuit.o PParameterReader.o $(LIBS) -o zeecomp_minuit

zeecomp_minuit.o: zeecomp_minuit.cpp PParameterReader.hpp
	$(CC) -c zeecomp_minuit.cpp -o zeecomp_minuit.o

run_wenu: wenucomp.o BlindingAuthority.o BlindingManagerParser.o OffsetMass.o OffsetEngine.o OffsetWidth.o OffsetWidthP0.o OffsetWidthP1.o OffsetWidthP2.o OffsetMassP0.o OffsetMassP1.o OffsetMassP2.o PParameterReader.o
	$(CC) wenucomp.o BlindingAuthority.o BlindingManagerParser.o OffsetMass.o OffsetWidth.o OffsetEngine.o OffsetWidthP0.o OffsetWidthP1.o OffsetWidthP2.o OffsetMassP0.o OffsetMassP1.o OffsetMassP2.o PParameterReader.o $(LIBS) -o wenucomp

wenucomp.o: wenucomp.cpp wmass_blinding_util PParameterReader.hpp
	$(CC) -c wenucomp.cpp  -o wenucomp.o

run_znunu: znunucomp.o  PParameterReader.o 
	$(CC) znunucomp.o PParameterReader.o $(LIBS) -o znunucomp

znunucomp.o: znunucomp.cpp PParameterReader.hpp
	$(CC) -c znunucomp.cpp -o znunucomp.o

calc_chi2_for_2_files.o: calc_chi2_for_2_files.cpp
	$(CC) -c calc_chi2_for_2_files.cpp -o calc_chi2_for_2_files.o

PParameterReader.o: PParameterReader.cpp PParameterReader.hpp
	$(CC) -c PParameterReader.cpp 

run_chi2: calc_chi2_for_2_files.o
	$(CC) calc_chi2_for_2_files.o $(LIBS) -o calc_chi2_for_2_files

BlindingAuthority.o: BlindingAuthority.cpp wmass_blinding_util
	$(CC) -c BlindingAuthority.cpp -o BlindingAuthority.o

BlindingManagerParser.o: BlindingManagerParser.cpp wmass_blinding_util
	$(CC) -c BlindingManagerParser.cpp -o BlindingManagerParser.o

OffsetMass.o: OffsetMass.cpp wmass_blinding_util
	$(CC) -c OffsetMass.cpp -o OffsetMass.o

OffsetWidth.o: OffsetWidth.cpp wmass_blinding_util
	$(CC) -c OffsetWidth.cpp -o OffsetWidth.o

OffsetMassP0.o: OffsetMassP0.cpp wmass_blinding_util
	$(CC) -c OffsetMassP0.cpp -o OffsetMassP0.o

OffsetWidthP0.o: OffsetWidthP0.cpp wmass_blinding_util
	$(CC) -c OffsetWidthP0.cpp -o OffsetWidthP0.o

OffsetMassP1.o: OffsetMassP1.cpp wmass_blinding_util
	$(CC) -c OffsetMassP1.cpp -o OffsetMassP1.o

OffsetWidthP1.o: OffsetWidthP1.cpp wmass_blinding_util
	$(CC) -c OffsetWidthP1.cpp -o OffsetWidthP1.o

OffsetMassP2.o: OffsetMassP2.cpp wmass_blinding_util
	$(CC) -c OffsetMassP2.cpp -o OffsetMassP2.o

OffsetWidthP2.o: OffsetWidthP2.cpp wmass_blinding_util
	$(CC) -c OffsetWidthP2.cpp -o OffsetWidthP2.o

OffsetEngine.o: OffsetEngine.cpp wmass_blinding_util
	$(CC) -c OffsetEngine.cpp -o OffsetEngine.o

wmass_blinding_util:
	ln -sf ../../wmass_blinding_util/wmass_blinding_util wmass_blinding_util

BlindingAuthority.cpp:
	ln -sf ../../wmass_blinding_util/src/BlindingAuthority.cpp BlindingAuthority.cpp

BlindingManagerParser.cpp:
	ln -sf ../../wmass_blinding_util/src/BlindingManagerParser.cpp BlindingManagerParser.cpp

OffsetMass.cpp:
	ln -sf ../../wmass_blinding_util/src/OffsetMass.cpp OffsetMass.cpp
OffsetWidth.cpp:
	ln -sf ../../wmass_blinding_util/src/OffsetWidth.cpp OffsetWidth.cpp

OffsetMassP0.cpp:
	ln -sf ../../wmass_blinding_util/src/OffsetMassP0.cpp OffsetMassP0.cpp
OffsetWidthP0.cpp:
	ln -sf ../../wmass_blinding_util/src/OffsetWidthP0.cpp OffsetWidthP0.cpp
OffsetMassP1.cpp:
	ln -sf ../../wmass_blinding_util/src/OffsetMassP1.cpp OffsetMassP1.cpp
OffsetWidthP1.cpp:
	ln -sf ../../wmass_blinding_util/src/OffsetWidthP1.cpp OffsetWidthP1.cpp
OffsetMassP2.cpp:
	ln -sf ../../wmass_blinding_util/src/OffsetMassP2.cpp OffsetMassP2.cpp
OffsetWidthP2.cpp:
	ln -sf ../../wmass_blinding_util/src/OffsetWidthP2.cpp OffsetWidthP2.cpp

OffsetEngine.cpp:
	ln -sf ../../wmass_blinding_util/src/OffsetEngine.cpp OffsetEngine.cpp

PParameterReader.cpp:
	ln -sf ../src/PParameterReader.cpp PParameterReader.cpp 
PParameterReader.hpp:
	ln -sf ../src/PParameterReader.hpp PParameterReader.hpp

#link_zee:
#	ln -sf /rooms/wmass/jenny/zeebackgroundfiles/ zeebackgroundfiles
clean:
	\rm -f *.o
	\rm -f *~
	\rm -fr wenucomp
	\rm -fr zeecomp
	\rm -fr znunucomp	
	\rm -fr zeecomp_minuit
	\rm -fr calc_chi2_for_2_files
	\rm -fr dumpHist
