########################################################################################################
#  Created by Junjie Zhu Oct-13-05                                                                     #
#  Purpose: modify parameter.rc file and submit jobs to clued0                                         #
#  Instruction: You need to provide your working directory, the root file you want to run and          #
#                 the location of your output files                                                    #
#               (1) wz_epmcs package must located under WORK_DIR/ directory                            #
#               (2) the directory called STORE_DIR must be created                                     #
#               (3) you need to have your initial parameter.rc file in wz_epmcs/src directory          #
#               (4) you need to have run_clued0.sh in wz_epmcs/src directory                           #
#               (5) you need to provide a file called file.list which contains the absolute paths      #
#                   of all input root files
#               (6) the script will create a script called submit_jobs.sh in wz_epmcs/src directory    #
#                   you can then do "source submit_jobs.sh" to submit all jobs to clued0               #
#                                                                                                      #
#  To Run:   python calc_wmass_uncertainties.py                                                        #
########################################################################################################

#!/usr/bin/python
import sys, os, string

# your working directory, where you have wz_epmcs package
# no '/' at the end
WORK_DIR = "/work/okaara-clued0/junjie/SCRIPTS/epmcs"

# list of root files you want to run
FILE_LIST = "/work/okaara-clued0/junjie/SCRIPTS/epmcs/file.list"

# the name of the directory where the root files stored
# no '/' at the end
STORE_DIR = "/work/okaara-clued0/junjie/SCRIPTS/epmcs/store"

# uncertainty table 
# the name must match with the name in parameters.rc
uncertainties_table = [
                       ('Scale_CC', '0.0010'), 
                       ('Offset_CC', '0.048'),
                       ('Sampling_CC', '0.03'),
                       ('Constant_CC', '0.0023'),
                       ('Scale_HAD', '0.02'),
                       ('Sampling_HAD', '0.2'),
                       ('Constant_HAD_CC', '0.01'),
                       ('EtaResolution_Phys_CC', '0.00002'),
                       ('PhiResolution_Phys_CC', '0.000004'),
                       ('EtaResolution_Det_CC', '0.0040'),
                       ('PhiResolution_Det_CC', '0.0035'),
                       ('merge_fsr_radius', '0.1'),
                       ('alpha_mb', '0.05'),
                       ('u0_CC', '0.599'),
                       ('s_CC', '0.00059'),
                       ('WUparaCorr_CC', '0.01'),
                       ('VtxResolution', '0.2')
                      ]

table = dict(uncertainties_table)

###########################################################################
#  function to read a list of root files from file.list
###########################################################################
def read_file_list():
    files_in_list=[]
    
    fileList = open(FILE_LIST, 'r')    
    while 1:
        line = fileList.readline()
        if not line:
            break
        else:
            if(len(line)>1): 
                files_in_list.append(line)
            else:
                print 'WARNING: an empty line in %s' %(FILE_LIST)                
    return files_in_list

############################################################################
# create various parameters.rc file
############################################################################
def prepare_parameter_files():    
    # loop over all keys in uncertainties_table
    for key in table.keys():
        key_size = len(key)
        uncertainty = (float)(table[key])
        print 'Start to create parameter.rc for %s with uncertainty %f' %(key, uncertainty)
        
        parameterFileName=WORK_DIR+"/wz_epmcs/src/parameters.rc"
        parameterFile = open(parameterFileName, 'r')
        
        # names of two new files where the variable is changed by +1 sigma and -1 sigma
        newFileUpName = WORK_DIR+"/wz_epmcs/src/parameters_"+key+"_Up.rc"
        newFileDnName = WORK_DIR+"/wz_epmcs/src/parameters_"+key+"_Dn.rc"
        newFileUp = open(newFileUpName, 'w')
        newFileDn = open(newFileDnName, 'w')
        
        # modify values according to +1 sigma and -1 sigma                
        while 1:
            line = parameterFile.readline()
            if not line:
                break
            elif line[0:key_size]==key:
                split_line = line.split()
                central_value = split_line[1]
                up_value = (float)(central_value) + uncertainty
                dn_value = (float)(central_value) - uncertainty
#               print 'Central, Up, Down value = ', central_value, up_value, dn_value
                up_line = split_line[0] + "     " + (str)(up_value) + '\n'
                dn_line = split_line[0] + "     " + (str)(dn_value) + '\n'
                newFileUp.write(up_line)
                newFileDn.write(dn_line)
            else:
                newFileUp.write(line)
                newFileDn.write(line)

#        print '%s created' %(newFileUpName)
#        print '%s created' %(newFileDnName)
        parameterFile.close()
        newFileUp.close()
        newFileDn.close()
#        print ' '

#######################################################################
# create various run_clued0_*.sh file
#######################################################################
def prepare_clued0_scripts():
    print '#############################################'
    print 'Now preparing scripts to submit jobs to clued0'
    print '#############################################'

    # get list of files to process
    files_to_process = read_file_list()
    print '# of root files to process: ', len(files_to_process)

    # loop over all keys in uncertainties_table
    for key in table.keys():
        key_size = len(key)
        uncertainty = (float)(table[key])
        print 'Start to create clued0 job script for %s with uncertainty %f' %(key, uncertainty)

        templateFileName = WORK_DIR+"/wz_epmcs/src/run_clued0.sh"
        templateFile = open(templateFileName, 'r')
        
        # names of two new files where the variable is changed by +1 sigma and -1 sigma
        newFileUpName = WORK_DIR+"/wz_epmcs/src/run_clued0_"+key+"_Up.sh"
        newFileDnName = WORK_DIR+"/wz_epmcs/src/run_clued0_"+key+"_Dn.sh"
        newFileUp = open(newFileUpName, 'w')
        newFileDn = open(newFileDnName, 'w')

        # read in template file
        while 1:
            line = templateFile.readline()
            if not line:
                break
            else:
                # copy working directory 
                if(string.find(line, "MYWORKDIR")>=0):
                    newline=line.replace('MYWORKDIR', WORK_DIR)
                    newFileUp.write(newline)
                    newFileDn.write(newline)
                # copy input root files
                elif(string.find(line, "ROOTFILE")>=0):
                    for n in range(len(files_to_process)):
                        file_name = (files_to_process[n])[:-1]
                        newline=line.replace('ROOTFILE', file_name)
                        newFileUp.write(newline)
                        newFileDn.write(newline)
                # copy parameter.rc file
                elif(string.find(line, "PARAMETERSFILE")>=0):
                    parametersFileName = "parameters_"+key+"_Up.rc"
                    newline = line.replace('PARAMETERSFILE', parametersFileName)    
                    newFileUp.write(newline)

                    parametersFileName = "parameters_"+key+"_Dn.rc"
                    newline = line.replace('PARAMETERSFILE', parametersFileName)    
                    newFileDn.write(newline)
                # copy output root files
                elif(string.find(line, "COPIEDFILE")>=0):
                    COPIED_ROOTFILE = STORE_DIR + "/epmcs_"+key+"_Up.root"
                    newline = line.replace('COPIEDFILE', COPIED_ROOTFILE)                
                    newFileUp.write(newline)

                    COPIED_ROOTFILE = STORE_DIR + "/epmcs_"+key+"_Dn.root"
                    newline = line.replace('COPIEDFILE', COPIED_ROOTFILE)                
                    newFileDn.write(newline)
                else:
                    newFileUp.write(line)
                    newFileDn.write(line)

#        print '%s created' %(newFileUpName)
#        print '%s created' %(newFileDnName)
        templateFile.close()
        newFileUp.close()
        newFileDn.close()
#        print ' '

def submit_job_scripts():
    print '#########################################################'
    print 'Now preparing a simple script to submit all jobs'
    print '#########################################################'

    # create one script to submit all jobs
    submitScriptsName = WORK_DIR+"/wz_epmcs/src/submit_jobs.sh"
    submitScripts = open(submitScriptsName, 'w')
    line = "#!/bin/sh" + '\n'
    submitScripts.write(line)
    
    # loop over all keys in uncertainties_table
    for key in table.keys():
        key_size = len(key)
        newFileUpName = WORK_DIR+"/wz_epmcs/src/run_clued0_"+key+"_Up.sh"
        newFileDnName = WORK_DIR+"/wz_epmcs/src/run_clued0_"+key+"_Dn.sh"
        line = "/usr/local/bin/cluesow -l cput=15:00:00 -l mem=512mb" + " " + newFileUpName + '\n'
        submitScripts.write(line)
        line = "/usr/local/bin/cluesow -l cput=15:00:00 -l mem=512mb" + " " + newFileDnName + '\n'
        submitScripts.write(line)

    submitScripts.close()
    print '%s created, you can use it to submit all jobs to clued0 system now' %(submitScriptsName)
    
###########################################
if(__name__=="__main__"):
    print 'Uncertainties table: '
    print uncertainties_table
    
    prepare_parameter_files()
    prepare_clued0_scripts()
    submit_job_scripts()
    
