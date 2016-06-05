# Use the following on IRIX 6.5 and Linux 2.4
# Last tested with p15.06.01
#
ROOTLIBS = `root-config --libs` -lMinuit
OPTCOMP = `root-config --cflags` 

CALDIR=../cal_regions
CALOBJECTS=cal_regions.o

SPECIALFLAGS= --exceptions
PDFMACRO =
ZBLIBFLAG =
#### TO TURN ON PDF WEIGHTS UNCOMMENT
# PDFMACRO= -D__USE_PDFS__
# PDFMACRO= -D__USE_PDFS_RESBOS__

#### TO TURN ON/OFF NEW ZB Library ROOT FORMAT
ZBLIBFLAG = -D__NEWZBLIB__

CFLAGS = -I$(LHAPDF_DIR)/include/ -I- -I. $(PDFMACRO) $(ZBLIBFLAG)
LFLAGS =

RCXX = $(CFLAGS) $(ROOTCFLAGS)
DBG = -g -L -O

### setup lhapdf v5_6_0
ifneq (,$(findstring USE,$(PDFMACRO)))
   LHAPDFLIB =$(LHAPDF_DIR)/lib/libLHAPDF.a 
else
   LHAPDFLIB = 
endif

ifdef SETUP_SAM_CPP_API
   SAMAPILIBS= -L$(SAM_CPP_API_DIR)/lib/so -lsam_cpp_api
   SAMCONTROL= -I$(SAM_CPP_API_DIR)/include -D__SETUP_SAM__
else
   SAMAPILIBS=
   SAMCONTROL=
endif

# make two libg2c.so

CC = ${GCC_DIR}/bin/g++ ${DBG} $(RCXX) $(OPTCOMP) 
F77 = ${GCC_DIR}/bin/g77

# fortran code needed for PDF reweight
all: run_pmcs

PMCSANA_DEPS=PHistoTools.hpp PCalTools.hpp PTools.hpp PParameterReader.hpp AnglesUtil.hpp 

run_pmcs: run_pmcs.o pmcsana.o pmcsana_Dict.o hist_files.o PMCSTH1.o PMCSTH1_Dict.o cal_regions.o PParameterReader.o GlobalParameters.o PMCSVtx.o PMCSParticle.o PMCSEMObj.o PMCSRecoil.o PMCSMet.o EMSmear.o EfficiencySmear.o SETefficiencySmear_base.o SETefficiencySmear.o SETefficiencySmear_LumiDispatch.o ZRecoilMethod_Util.o RecoilSmear.o  PMCSZCand.o PMCSWCand.o BlindingManagerPMCS.o ZAnalysis.o WAnalysis.o PMCSEvent.o PMCSMuon.o MuSmear.o JPsiMuAnalysis.o ZMuAnalysis.o ZNuNuAnalysis.o PMCSZMuCand.o PMCSJPsiMuCand.o BeamWeight.o TF2jan.o ZBLibraryClass.o MBLibraryClass.o SAMExpander.o SAMExpander_Dict.o TH2rclsa_Dict.o TH2rclsa.o HardRecoil_Manager.o
	$(CC)  -B${LINKTIME_DIR}/usr/X11R6/lib -B${RUNTIME_DIR}/usr/lib -B${LINKTIME_DIR}/lib -B${LINKTIME_DIR}/usr/lib -Wl,-rpath-link -Wl,${LINKTIME_DIR}/usr/X11R6/lib -Wl,-rpath-link -Wl,${RUNTIME_DIR}/usr/lib -Wl,-rpath-link -Wl,${LINKTIME_DIR}/lib -Wl,-rpath-link -Wl,${LINKTIME_DIR}/usr/lib run_pmcs.o pmcsana.o pmcsana_Dict.o hist_files.o PParameterReader.o GlobalParameters.o PMCSVtx.o PMCSParticle.o PMCSEMObj.o PMCSRecoil.o PMCSMet.o EMSmear.o EfficiencySmear.o  SETefficiencySmear_base.o SETefficiencySmear.o SETefficiencySmear_LumiDispatch.o ZRecoilMethod_Util.o RecoilSmear.o PMCSZCand.o PMCSWCand.o BlindingManagerPMCS.o ZAnalysis.o WAnalysis.o PMCSEvent.o PMCSMuon.o MuSmear.o JPsiMuAnalysis.o ZMuAnalysis.o ZNuNuAnalysis.o PMCSZMuCand.o PMCSJPsiMuCand.o BeamWeight.o TF2jan.o PMCSTH1.o  PMCSTH1_Dict.o ZBLibraryClass.o MBLibraryClass.o SAMExpander.o SAMExpander_Dict.o TH2rclsa.o TH2rclsa_Dict.o HardRecoil_Manager.o $(F77OBJS) ${CALOBJECTS} $(ROOTLIBS) $(LHAPDFLIB) $(SAMAPILIBS) -l g2c -o run_pmcs

run_pmcs.o: run_pmcs.cpp cal_regions.h
	$(CC) -c run_pmcs.cpp -o run_pmcs.o

pmcsana.o: pmcsana.cpp pmcsana.h ${PMCSANA_DEPS}
	$(CC) -c pmcsana.cpp -o pmcsana.o

PMCSTH1.o: PMCSTH1.cpp PMCSTH1.hpp
	$(CC) -c PMCSTH1.cpp -o PMCSTH1.o

hist_files.o: hist_files.cpp hist_files.hpp hist_nd.hpp 
	$(CC) -c hist_files.cpp -o hist_files.o

cal_regions.o: cal_regions.C cal_regions.h 
	$(CC) -c cal_regions.C -o cal_regions.o

pmcsana_Dict.cxx: pmcsana.h
	rootcint -f pmcsana_Dict.cxx -c $(PDFMACRO)  -I$(LHAPDF_DIR)/include pmcsana.h

pmcsana_Dict.o: pmcsana_Dict.cxx 
	$(CC) -c pmcsana_Dict.cxx -o pmcsana_Dict.o

PMCSTH1_Dict.cxx: PMCSTH1.hpp
	rootcint -f PMCSTH1_Dict.cxx -c PMCSTH1.hpp

PMCSTH1_Dict.o: PMCSTH1_Dict.cxx
	$(CC) -c PMCSTH1_Dict.cxx -o PMCSTH1_Dict.o


PParameterReader.o: PParameterReader.cpp PParameterReader.hpp
	$(CC) -c PParameterReader.cpp 

GlobalParameters.o: GlobalParameters.cpp GlobalParameters.hpp
	$(CC) -c GlobalParameters.cpp -o GlobalParameters.o 

PMCSVtx.o: PMCSVtx.cpp PMCSVtx.hpp
	$(CC) -c PMCSVtx.cpp -o PMCSVtx.o 

PMCSParticle.o: PMCSParticle.cpp PMCSParticle.hpp
	$(CC) -c PMCSParticle.cpp -o PMCSParticle.o 

PMCSEMObj.o: PMCSEMObj.cpp PMCSEMObj.hpp
	$(CC) -c PMCSEMObj.cpp -o PMCSEMObj.o 

PMCSMet.o: PMCSMet.cpp PMCSMet.hpp
	$(CC) -c PMCSMet.cpp -o PMCSMet.o 

PMCSRecoil.o: PMCSRecoil.cpp PMCSRecoil.hpp
	$(CC) -c PMCSRecoil.cpp -o PMCSRecoil.o 

PMCSMuon.o: PMCSMuon.cpp PMCSMuon.hpp
	$(CC) -c PMCSMuon.cpp -o PMCSMuon.o 

EMSmear.o: EMSmear.cpp EMSmear.hpp histograms.hpp
	$(CC) -c EMSmear.cpp -o EMSmear.o 

MuSmear.o: MuSmear.cpp MuSmear.hpp histograms.hpp
	$(CC) -c MuSmear.cpp -o MuSmear.o 

EfficiencySmear.o: EfficiencySmear.cpp EfficiencySmear.hpp histograms.hpp
	$(CC) -c EfficiencySmear.cpp -o EfficiencySmear.o 

SETefficiencySmear_base.o: SETefficiencySmear_base.cpp SETefficiencySmear_base.hpp
	$(CC) -c SETefficiencySmear_base.cpp -o SETefficiencySmear_base.o

SETefficiencySmear.o: SETefficiencySmear.cpp SETefficiencySmear.hpp
	$(CC) -c SETefficiencySmear.cpp -o SETefficiencySmear.o

SETefficiencySmear_LumiDispatch.o: SETefficiencySmear_LumiDispatch.cpp SETefficiencySmear_LumiDispatch.hpp
	$(CC) -c SETefficiencySmear_LumiDispatch.cpp -o SETefficiencySmear_LumiDispatch.o

ZRecoilMethod_Util.o: ZRecoilMethod_Util.cpp ZRecoilMethod_Util.hpp
	$(CC) -c ZRecoilMethod_Util.cpp -o ZRecoilMethod_Util.o

RecoilSmear.o: RecoilSmear.cpp RecoilSmear.hpp histograms.hpp
	$(CC) -c RecoilSmear.cpp -o RecoilSmear.o

PMCSZCand.o: PMCSZCand.cpp PMCSZCand.hpp
	$(CC) -c PMCSZCand.cpp -o PMCSZCand.o

PMCSWCand.o: PMCSWCand.cpp PMCSWCand.hpp
	$(CC) -c PMCSWCand.cpp -o PMCSWCand.o

PMCSZMuCand.o: PMCSZMuCand.cpp PMCSZMuCand.hpp
	$(CC) -c PMCSZMuCand.cpp -o PMCSZMuCand.o

PMCSJPsiMuCand.o: PMCSJPsiMuCand.cpp PMCSJPsiMuCand.hpp
	$(CC) -c PMCSJPsiMuCand.cpp -o PMCSJPsiMuCand.o

ZAnalysis.o: ZAnalysis.cpp ZAnalysis.hpp histograms.hpp
	$(CC) -c ZAnalysis.cpp -o ZAnalysis.o

WAnalysis.o: WAnalysis.cpp WAnalysis.hpp histograms.hpp
	$(CC) -c WAnalysis.cpp -o WAnalysis.o

BlindingManagerPMCS.o: BlindingManagerPMCS.cpp wmass_blinding_util
	$(CC) -c BlindingManagerPMCS.cpp -o BlindingManagerPMCS.o

ZMuAnalysis.o: ZMuAnalysis.cpp ZMuAnalysis.hpp histograms.hpp
	$(CC) -c ZMuAnalysis.cpp -o ZMuAnalysis.o

JPsiMuAnalysis.o: JPsiMuAnalysis.cpp JPsiMuAnalysis.hpp histograms.hpp
	$(CC) -c JPsiMuAnalysis.cpp -o JPsiMuAnalysis.o

ZNuNuAnalysis.o: ZNuNuAnalysis.cpp ZNuNuAnalysis.hpp histograms.hpp
	$(CC) -c ZNuNuAnalysis.cpp -o ZNuNuAnalysis.o

PMCSEvent.o: PMCSEvent.cpp PMCSEvent.hpp
	$(CC) -c PMCSEvent.cpp -o PMCSEvent.o

BeamWeight.o: BeamWeight.cpp BeamWeight.hpp
	$(CC) -c BeamWeight.cpp -o BeamWeight.o

TF2jan.o: TF2jan.cpp TF2jan.h
	$(CC) -c TF2jan.cpp -o TF2jan.o

ZBLibraryClass.o: ZBLibraryClass.cpp ZBLibraryClass.h
	$(CC) -c ZBLibraryClass.cpp -o ZBLibraryClass.o

MBLibraryClass.o: MBLibraryClass.cpp MBLibraryClass.h
	$(CC) -c MBLibraryClass.cpp -o MBLibraryClass.o

cal_regions.h:
	ln -sf ${CALDIR}/cal_regions.h cal_regions.h

cal_regions.C:
	ln -sf ${CALDIR}/cal_regions.C cal_regions.C

wmass_blinding_util:
	ln -sf ../../wmass_blinding_util/wmass_blinding_util wmass_blinding_util
 
BlindingManagerPMCS.cpp:
	ln -sf ../../wmass_blinding_util/src/BlindingManagerPMCS.cpp BlindingManagerPMCS.cpp

SAMExpander_Dict.cxx: SAMExpander.hpp
	rootcint -f SAMExpander_Dict.cxx -c SAMExpander.hpp

SAMExpander_Dict.o: SAMExpander_Dict.cxx
	$(CC) -c SAMExpander_Dict.cxx -o SAMExpander_Dict.o

SAMExpander.o:
	$(CC) $(SAMCONTROL) -c SAMExpander.cpp -o SAMExpander.o

TH2rclsa_Dict.cxx: TH2rclsa.h
	rootcint -f $@ -c $^

TH2rclsa_Dict.o: TH2rclsa_Dict.cxx
	$(CC) -c $^ -o $@

TH2rclsa.o: TH2rclsa.cpp
	$(CC) -c $^ -o $@

HardRecoil_Manager.o: HardRecoil_Manager.cpp HardRecoil_Manager.hpp
	$(CC) -c $< -o $@

clean:
	\rm -f *.o
	\rm -fr *~
	\rm -fr pmcsana_Dict.h
	\rm -fr TH2rclsa_Dict.h
	\rm -fr TH2rclsa_Dict.cxx
	\rm -fr *.cxx
	\rm -fr run_pmcs
