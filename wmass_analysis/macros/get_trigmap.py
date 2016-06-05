#!/usr/bin/env python
#
# Created:  Jan 7, 2003 John Gardner
#           by ripping off Reiner Hauser's 'getbits.py' created
#           by ripping off Marco's original 'makeL1L2TrigMap.py'
#
# usage:
#    get_good_trigs.py <run_number> [ <last_run_number> ]
#
# return list of preferred triggers in this order
# E1_SHT25|E1_SHT27




# Modified by M Yan
# Modifed by S Yacoob

# Before usage, type: setup python_dcoracle first

import os
import sys
import string

# quick check first...
if len(sys.argv) < 2:
    print "Usage: %s <run_number>" % sys.argv[0]
    sys.exit(1)

firstrun = int(sys.argv[1])

if len(sys.argv) == 3:
    lastrun = int(sys.argv[2])
else:
    lastrun = firstrun

# this may take some time
# so put it after the commandline checks...

try:
   import dcoracle
except:
   sys.stderr.write('\nGetPrescaleL3Trigger: to use this script you need the dcoracle module for Python\n')
   sys.stderr.write('                        type setup python_dcoracle and then rerun the script\n\n')
   sys.exit(2)

db = dcoracle.Connect("d0read/reader@d0ofprd1.fnal.gov") #offline
# db = dcoracle.Connect("d0read/reader@d0onprd.fnal.gov") # online

cursor = db.cursor()

# make a list of good runs
goodruns = []
query="select run_number, run_type, trig_config_name, trig_config_type, physics, recording, store from runs.runs where (run_number>=%d and run_number<=%d) order by run_number ASC" % (firstrun,lastrun)
cursor .execute(query)
result = cursor.fetchall()
for (run, run_type, trig_config_name, trig_config_type, physics, recording, store) in result:
  goodrun = 0
  if (recording == '1'):
    if (run_type == 'Physics' ):
      goodrun = 1
    if (physics == '1'):
      goodrun = 1
    if ((string.find(trig_config_name,"global") >= 0) and (store > 0) and (goodrun == 0)):
      goodrun = 1
    if ((trig_config_type != 'physics') and (physics == '0') and (store == None) ):
      goodrun = 0
  if (goodrun):
    goodruns.append(run)

# make a new query for each good run since multiple run queries give unreliable results
for run_number in goodruns:
  query="select run_number, bit_name, bit_num, trg_type, depend_bit, prescale from runs.run_trigs where run_number = %d" % run_number
  cursor.execute(query)

  result = cursor.fetchall()

  has_E1_SHT25 = 0
  has_E1_SHT27 = 0
 
  
  prescale_map = {}
  
  for (run, name, bit_num, trg_type, depend_bit, prescale) in result:
    if prescale is None:
      prescale = "1"
    
    if trg_type == "L1bit":
      prescale_map[bit_num] = prescale
    
    if name == "E1_SHT25": 
      has_E1_SHT25 = 1
      depend_E1_SHT25 = depend_bit
    
    if name == "E1_SHT27": 
      has_E1_SHT27 = 1
      depend_E1_SHT27 = depend_bit
    

      
  prescale_E1_SHT25 = "0"
  if has_E1_SHT25:
    prescale_E1_SHT25 = prescale_map[depend_E1_SHT25]
        
  prescale_E1_SHT27 = "0"
  if has_E1_SHT27:
    prescale_E1_SHT27 = prescale_map[depend_E1_SHT27]
                
  line = str(run_number)
  if prescale_E1_SHT25 == "1":
    line = line + " E1_SHT25"  
    if prescale_E1_SHT27 == "1":
      line = line + " E1_SHT27"      
  elif prescale_E1_SHT27 == "1":   
    line = line + " E1_SHT27"   
        
  if line != str(run_number):
    print line

cursor.close()  
