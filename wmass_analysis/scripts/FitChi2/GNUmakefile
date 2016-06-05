CXX := g++
CXXFLAGS := -g

SHAREDFLAG := -shared

CPPFLAGS := -I. -I"$(ROOTSYS)/include"

CXXFLAGS += $(PLATFLAGS)
PWD=$(shell pwd)

OBJS = Parabola.o Parabola_dict.o \
	Parabola1D.o Parabola1D_dict.o \
	Parabola2D.o Parabola2D_dict.o \
	Parabola3D.o Parabola3D_dict.o

ROOTLIBS = "$(ROOTSYS)/lib/libGpad.so" "$(ROOTSYS)/lib/libGraf.so" \
	"$(ROOTSYS)/lib/libHist.so" \
	"$(ROOTSYS)/lib/libMatrix.so" \
	"$(ROOTSYS)/lib/libCint.so" "$(ROOTSYS)/lib/libCore.so"

all : Parabola.so

clean: 
	rm -f *.o *_dict.* *.dll *.a *.so *.exp *.obj *.lib

%.obj : %.C
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $*.C

%.obj : %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $*.cpp

%.o : %.C
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $*.C

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $*.cpp

#%_dict.cpp : %.hpp
#	rootcint -f $@ -c $*.hpp

Parabola_dict.cpp : Parabola.hpp  Parabola_LinkDef.h 
	rootcint -f $@ -c Parabola.hpp Parabola_LinkDef.h

Parabola1D_dict.cpp: Parabola1D.hpp Parabola1D_LinkDef.h 
	rootcint -f $@ -c Parabola1D.hpp Parabola1D_LinkDef.h

Parabola2D_dict.cpp: Parabola2D.hpp Parabola2D_LinkDef.h 
	rootcint -f $@ -c Parabola2D.hpp Parabola2D_LinkDef.h

Parabola3D_dict.cpp: Parabola3D.hpp Parabola3D_LinkDef.h 
	rootcint -f $@ -c Parabola3D.hpp Parabola3D_LinkDef.h

%_dict.cpp : %.h
	rootcint -f $@ -c $*.h

%_dict.cpp : %.hpp
	rootcint -f $@ -c $*.hpp

%.dll : %.obj %_dict.obj
	$(CXX) $(CXXFLAGS) $(SHAREDFLAG) $*.obj $*_dict.obj

Parabola.so: $(OBJS)
	$(CXX) $(CXXFLAGS) $(SHAREDFLAG) -o $@ $(OBJS) $(ROOTLIBS) $(ROOT_UTILS_LIBS) $(MY_LIBS)


######################################################################
#                                                                    #
# -- History --                                                      #
#                                                                    #
#                                                                    #
# As of 12/02/2009: First version written                            #
# RCLSA                                                              #
#                                                                    #
# As of 12/03/2009: Implemented LinkDef Makefile                     #
# RCLSA                                                              #
#                                                                    #
# As of 01/24/2010: Compilation and linkage errors debugged          #
# RCLSA                                                              #
#                                                                    #
######################################################################
