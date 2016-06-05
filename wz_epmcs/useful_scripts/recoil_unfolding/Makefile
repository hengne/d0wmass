ROOTLIBS = `root-config --libs` -lMinuit
OPTCOMP = `root-config --cflags` 

SPECIALFLAGS= --exceptions
MACRO =
#### TO TURN ON PDF WEIGHTS UNCOMMENT
#MACRO= -D__USE_PDFS__
CFLAGS = -I$(LHAPDF_DIR)/include/ -I- -I. $(MACRO)
LFLAGS =

RCXX = $(CFLAGS) $(ROOTCFLAGS)
DBG = -g -L -O

### setup lhapdf v5_6_0
LHAPDFLIB =$(LHAPDF_DIR)/lib/libLHAPDF.a 
SAMAPILIBS= -L$(SAM_CPP_API_DIR)/lib/so -lsam_cpp_api

# make two libg2c.so

CC = ${GCC_DIR}/bin/g++ ${DBG} $(RCXX) $(OPTCOMP)
F77 = ${GCC_DIR}/bin/g77

%.o: %.cpp
	$(CC) -c $< -o $(@F)

all: run_unfolding

run_unfolding: run_unfolding.o RecoilFile.o RecoilMap.o RecoilLibrary.o SETefficiencySmear.o PParameterReader.o
	$(CC) run_unfolding.o RecoilFile.o RecoilMap.o RecoilLibrary.o SETefficiencySmear.o PParameterReader.o $(ROOTLIBS) -o run_unfolding

clean:
	rm -rf *.o run_unfolding
