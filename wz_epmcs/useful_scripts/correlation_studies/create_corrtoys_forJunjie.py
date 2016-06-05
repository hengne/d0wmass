# This script will make as many parameters.rc (and/or *geant) files as the lines in the corrparameters_toys.txt file

# So if you have 100 lines in corrparameters_toys.txt, this will make 100 parameters.rc files for 100 toys

#!/usr/bin/env python

import string, getopt, sys, random, math, time, os, shutil


input_txtfile = '/QQQ/RRR/SSS/corgen/'
wzepmcs_dir = '/MMM/NNN/PPP/wzepmcs/wz_epmcs/src'
parameter_dir = '/XXX/YYY/ZZZ/parameter_files'

def create_resbos_script_per_job():

    infilename = input_txtfile + "corrparameters_toys.txt"
    infile = open(infilename, 'r')
    line = infile.readline()
    
    os.system('cp %s/parameters.rc  parameters.rc.tmp \n' %(wzepmcs_dir) )
    job = 0

    while line:
        print line
        if len(line)>1:
            entry = string.split(line)

            alpha = float(entry[0])
            beta = float(entry[1])
            scaleA = float(entry[2])
            scaleB = float(entry[3])
            samplA = float(entry[4])
            alphamb = float(entry[5])

            print 'writing out %s %s %s %s now "\n' %(scaleA, scaleB, samplA, alphamb)
            
            os.system('sed -e "s/Scale\_CC:                 1.01112/Scale\_CC:                 '+(str)(alpha)+'/g" parameters.rc.tmp > parameters.rc.tmp1 \n')
            os.system('sed -e "s/Offset\_CC:                -0.40364/Offset\_CC:                '+(str)(beta)+'/g" parameters.rc.tmp1 > parameters.rc.tmp2 \n')  

            os.system('sed -e "s/Scale\_HAD\_bifurcate\_A:     0.941258/Scale\_HAD\_bifurcate\_A:     '+(str)(scaleA)+'/g" parameters.rc.tmp2 > parameters.rc.tmp3 \n')
            os.system('sed -e "s/Scale\_HAD\_bifurcate\_B:     1.20163/Scale\_HAD\_bifurcate\_B:     '+(str)(scaleB)+'/g" parameters.rc.tmp3 > parameters.rc.tmp4 \n')
            os.system('sed -e "s/Relsampling\_HAD\_bifurcate\_A:  1.08391/Relsampling\_HAD\_bifurcate\_A:  '+(str)(samplA)+'/g" parameters.rc.tmp4 > parameters.rc.tmp5 \n')
            os.system('sed -e "s/alpha\_mb:    0.618028/alpha\_mb:    '+(str)(alphamb)+'/g" parameters.rc.tmp5 > parameters.rc.tmp6 \n')
            
            
            os.system('cp parameters.rc.tmp6 parameters.rc_toy_' +(str)(job)+ ' \n')
            os.system('mv parameters.rc_toy_' +(str)(job)+ ' %s \n' %(parameter_dir) )
            
            job = job + 1

        line = infile.readline()
    

    infile.close()

##############################
if __name__=="__main__":
    create_resbos_script_per_job()
