###########################
#!/usr/bin/env python
# created by Junjie Zhu to create submit script for W mass analysis
#
###########################

import string, getopt, sys, random, math, time, os, shutil

###########################
## Global parameters
###########################
doQCDBkgStudy = 0
doSMBkgStudy = 0

# whether we want to vary Z mass cut
varyZMassCuts = 0
ZMassCuts1_Vary = [70, 110]
ZMassCuts2_Vary = [50, 130]
ZMassCuts_Default = [70, 110]

# whether we want to vary Z Ut cut
varyZUtCuts = 1
ZUtCuts_Vary = [15, 30, 1000]
ZUtCuts_Default = [15]

# whether we want to vary # of tracks requirement
varyNumTrks = 1
NumTrks_Vary = [1, 2]
NumTrks_Default = 1

# data or MC
doStudyData = 0

CONFIGFILENAME_DATA = 'cafe.config'
CONFIGFILENAME_MC = 'cafe.config.geant'

SAM_DATA = ["WMASS-2EM-from-EMinclusive-p1709-ROOT-wm1", "WMASS-2EM-from-EMinclusive-PASS3-p17.09.03-ROOT-wm1"]
SAM_MC = ["wzcross-zee-nosup01all-MC-caf"]

SCRIPT_NAME='sub_script'
CABSRV = 'cabsrv1'
BATCH_QUEUE = 'medium'

# number of jobs for each dataset definition
NUMJOBS = 1

###########################
def create_configfiles():

    if varyZMassCuts==1:
        ZMass = ZMassCuts1_Vary + ZMassCuts2_Vary
    else:
        ZMass = ZMassCuts_Default

    if varyZUtCuts==1:
        ZUt = ZUtCuts_Vary
    else:
        ZUt = ZUtCuts_Default

    if varyNumTrks==1:
        NumTrks = NumTrks_Vary
    else:
        NumTrks = NumTrks_Default

    if doStudyData == 1:
        SAM = SAM_DATA
    else:
        SAM = SAM_MC

    # a script to submit all jobs
    SUB_SCRIPT_All = 'submit_all.sh'
    submit_all_file=open(SUB_SCRIPT_All, 'w')
    submit_all_file.write("setup caf_tools \n")
    submit_all_file.write("setup sam \n")
 
    for numtrks in NumTrks:
        for zut in ZUt:
            for imass in range(0, varyZMassCuts+1):

                # open the original configuration file
                if doStudyData == 1:
                    old_file_name=CONFIGFILENAME_DATA
                else:
                    old_file_name=CONFIGFILENAME_MC
                    
                old_file=open(old_file_name)
                    
                # open a new configuration file
                file_index = "ZUt_"+(str)(zut)+"_Trk_"+(str)(numtrks)+"_Mass_"+(str)(ZMass[2*imass])+"_"+(str)(ZMass[2*imass+1])
                new_file_name = old_file_name+"_"+file_index
                new_file=open(new_file_name, 'w')
                
                # loop over each line in the old file
                # and replace the right parameter
                for line in old_file.readlines():
                    
                    if string.find(line, "myname.NumZSpatialTrk:")>=0:                  # spatial track matching
                        newline = "myname.NumZSpatialTrk: "+(str)(numtrks) + "\n"      
                    elif string.find(line, "myname.ZMassCut1:")>=0:                     # Z mass cut
                        newline = "myname.ZMassCut1: "+(str)(ZMass[2*imass]) + "\n"    
                    elif string.find(line, "myname.ZMassCut2:")>=0:                     # Z mass cut
                        newline = "myname.ZMassCut2: "+(str)(ZMass[2*imass+1]) + "\n"  
                    elif string.find(line, "myname.ZUtCut:")>=0:                        # Z uT cut (be careful about ZUtCut_lower)
                        newline = "myname.ZUtCut: "+(str)(zut)+"\n"
                    elif string.find(line, "myname.QCDBkgStudy:")>=0:                   # study QCD background
                        if doQCDBkgStudy==1:
                            newline = "myname.QCDBkgStudy: true \n"
                        else:
                            newline = "myname.QCDBkgStudy: false \n"
                    elif string.find(line, "myname.SMBkgStudy:")>=0:                    # study SM background
                        if doSMBkgStudy==1:
                            newline = "myname.SMBkgStudy: true \n"
                        else:
                            newline = "myname.SMBkgStudy: false \n"
                    else:
                        newline = line
                        
                    new_file.write(newline)

                # open a new script file
                new_script_name = SCRIPT_NAME+"_"+old_file_name+"_"+file_index+".sh"
                new_script=open(new_script_name, 'w')

                # for different dataset definitions
                for sam in SAM:
                    submit_script = "runcafe -" + CABSRV + " -def=" + sam + " -outdir=`pwd` -exe=./shbin/Linux2.4-GCC_3_4-maxopt/cafe " + "-name=output_" + sam + "-" + old_file_name + "_" + (str)(file_index) + " -jobs=" + (str)(NUMJOBS) + " -- " + (str)(new_file_name) + "\n"
                    new_script.write(submit_script)
                    submit_all_file.write(submit_script)
                
                # close files
                old_file.close()
                new_file.close()
                new_script.close()

    # close submit all file
    submit_all_file.close()
            
###########################
if __name__=="__main__":
    create_configfiles()
