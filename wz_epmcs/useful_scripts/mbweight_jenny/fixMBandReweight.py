#!/usr/bin/python
import re
import os
import math
import random

#NOTES:
#The input file, from Jan:  Patrice to produced Pythia MB events with ZB overlay. The corresponding MC request IDs are 197152-197176. Jan then ran over these events, and reconstructed the uT vector and SET, using the same "single neutrino subtraction" technique that was used with the Z -> nu nu events that were used to build the new model of the hard recoil. The results can be found in the ASCII file that is the input to this code.
#In this file, there is one line per event. The numbers for each event represent the following:true primary vertex x, true primary vertex y, true primary vertex z, number of reconstructed primary vertices, instantaneous luminosity, SET, minus ux, minus uy. For the last two variables I write "minus ux" (or y), because the code prints out METx, i.e. the negative of the x component of the uT vector.
#Idea of this code is to reweight the events in this file in such a way that SET spectrum as predicted by PMCS (that is, sum of hard, ZB and MB components) matches that of Z -> e e events. For this study, we look at the low lumi and zpt regions when trying to find agreement.
#Note that the weight is an integer per event (aka duplicating MB library lines).  We also remove events with 0 SET (aka MBset) and require the vtx cut.

f = open('/work/rebel-clued0/Other/Summer2013/epmcs_analysis_p21.26.00_newdefault_mbreweight/wz_epmcs/src/MBdump.txt')
fnew = open('MBdumpNewReweightspow04PROB.txt','w') #/work/rebel-clued0/Other/Summer2013/epmcs_analysis_p21.26.00_newdefault_mbreweight/wz_epmcs/src/

linetot = 0
outnum = 0
random.seed(33)
#print math.floor(2.3)
#print math.ceil(2.3)
for line in f:
    outnum = 0
    stuff = line.split("  ")
    #print stuff
    stuffx = stuff[2].split(" ")
    vtxs = stuff[0].split(" ")
    #print stuffx[0]
    if stuffx[0] != '0' and abs(float(vtxs[2])) < 60.0:
        outnum =  math.pow(float(stuffx[0]), 0.4)   
        randz = (random.random()) + math.floor(outnum)
        if randz < outnum:
            outnum = math.ceil(outnum)
        else:
            outnum = math.floor(outnum)
      
        for i in range (0, outnum):
            fnew.write(line)
            linetot = linetot + 1
            #print line
print linetot
     
#MBdumpNewReweightspow06PROB.txt
##15278308
#MBdumpNewReweightspow04PROB.txt
#8887389
#MBdumpNewReweightspow03PROB.txt
#6877862

