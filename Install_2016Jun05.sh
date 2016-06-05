#!/bin/sh

setup D0RunII p21.26.00  -O SRT_QUAL=maxopt

newrel p21.26.00 2016Jun05
cd 2016Jun05
addpkg -h wz_epmcs 
addpkg -h wmass_blinding_util

cd wz_epmcs/src

#setup root v4_04_02b_fbits_trefarray7_eh -q GCC_3_4_3:opt
export LINK_SHARED=yes
#setup gcc v3_4_3_dzero_so
setup lhapdf v5_8_1 -q GCC3_4_3
#setup ld v2_16_1 -f Linux+2.4 -z /d0usr/products/upsdb

##gmake all
#cp ../../../scripts/localtest.sh .
#cp parameters.rc.geant parameters.rc.geant.test
#cp parameters.rc parameters.rc.test
#ln -s ../../../samples/*list .
##cd ../../

##cp -r wz_epmcs/compare_macros . 
##cd compare_macros
##sed "s/..\/wmass_blinding_util/wmass_blinding_util/g" Makefile > .tmp.txt
##mv .tmp.txt Makefile
##gmake all
#ln -s ../../references/fullmc_* .
#ln -s ../../references/data_*.root .
##cd ../

#ln -s ../extras* .
#ln -s ../samples/*list .
#cp ../scripts/del_jobs.sh .
#cp ../scripts/run_epmcs.sh .
#cp ../scripts/stat_jobs.sh .
#cp ../scripts/submit_pmcs.sh .
#mkdir cabout
#cp ../scripts/domerge_and_compare_wen.sh cabout/
#cp ../scripts/domerge_and_compare_zee.sh cabout/
#cp ../scripts/domerge_and_compare_wen_dt.sh cabout/
#cp ../scripts/domerge_and_compare_zee_dt.sh cabout/
#cp ../scripts/merge.sh cabout/
#cp wz_epmcs/src/parameters.rc .
#cp wz_epmcs/src/parameters.rc.geant .

#cd cabout
#cp ../../samples/merge.sh .
#cp ../../samples/domerge_and_compare*sh .
#cd ../

export ZBLibraryRootPath=${PWD}/extras
export MBLibraryRootPath=${PWD}/extras
export TBLibraryRootPath=${PWD}/extras/TBLibrary

