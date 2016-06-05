g++ -g -O3 -Wall `root-config --cflags --glibs` `root-config --libs` ../../src/PParameterReader.cpp ../../src/SETefficiencySmear.cpp  perBinProfile.C MakeGenRec.C -o MakeGenRec
g++ -g -O3 -Wall `root-config --cflags --glibs` `root-config --libs` ../../src/PParameterReader.cpp ../../src/SETefficiencySmear.cpp perBinProfile.C ConvertRecoils2D.C -o ConvertRecoils2D
g++ -g -O3 -Wall `root-config --cflags --glibs` `root-config --libs` ../../src/PParameterReader.cpp ../../src/SETefficiencySmear.cpp perBinProfile.C ConvertRecoils2DRedo.C -o ConvertRecoils2DRedo
#I turned off the comments option for compiling MakeUEMap to suppress annoying warnings. If you want to see comments, just change the '-w' to '-Wall' int the 'g++' command
g++ -g -O3 -w `root-config --cflags --glibs` `root-config --libs` ../../src/PMCSVtx.cpp ../../src/PMCSParticle.cpp ../../src/PParameterReader.cpp  ../../src/PMCSTH1_Dict.cxx ../../src/PMCSEMObj.cpp ../../src/PMCSTH1.cpp ../../src/EMSmear.cpp ../../src/hist_files.cpp MakeUEMap.C -o MakeUEMap
g++ -g -O3 -Wall `root-config --cflags --glibs` `root-config --libs` CCSeparate.C -o CCSeparate
g++ -g -O3 -Wall `root-config --cflags --glibs` `root-config --libs` PhotFilter.C -o PhotFilter
g++ -g -O3 -Wall `root-config --cflags --glibs` `root-config --libs` UESeparate.C -o UESeparate
g++ -g -O3 -Wall `root-config --cflags --glibs` `root-config --libs` UESeparate_fullElectronInfo.C -o UESeparate_fullElectronInfo
g++ -g -O3 -Wall `root-config --cflags --glibs` `root-config --libs` Lumiseparate.C -o Lumiseparate
g++ -g -O3 -Wall `root-config --cflags --glibs` `root-config --libs` SETseparate.C -o SETseparate
