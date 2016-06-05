#!/bin/sh
#export ZBLibraryRootPath=/rooms/surete/sahal/RunIIb
#export ZBLibraryRootPath=/rooms/wmass/rclsa/ZBLibrary_RunIIb34/FullMC 
#export ZBLibraryRootPath=/prj_root/3103/wz2_write/ddboline/RunIIb34
#export MBLibraryRootPath=/rooms/wmass 
#export TBLibraryRootPath=/rooms/wmass/hengne/TBLibrary
export ZBLibraryRootPath=${PWD}/extras
export MBLibraryRootPath=${PWD}/extras
export TBLibraryRootPath=${PWD}/extras

cd 2016Jun05
setup D0RunII p21.26.00 -O SRT_QUAL=maxopt
#setup root v4_04_02b_fbits_trefarray7_eh -q GCC_3_4_3:opt
export LINK_SHARED=yes
#setup gcc v3_4_3_dzero_so
setup lhapdf v5_8_1 -q GCC3_4_3
