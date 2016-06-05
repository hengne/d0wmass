#!/usr/bin/env python
#
#  Simple script to get prescales
#
#  USAGE:  python GetPrescale runnum_low runnum_high triggername
#
#  OUTPUT: runs with prescales for a given trigger within a given runrange
#
#  Original author: ???
#  modified by:     Liang Li, October 2008
#                   Carsten Magass, March 2005
#

import dcoracle,pprint
import sys

if len (sys.argv) != 4:
    print "Usage: python %s runnum_low runnum_high triggername" %sys.argv[0]
    sys.exit (1)

runnum_low = int (sys.argv[1])
runnum_high = int (sys.argv[2])
trigger = str (sys.argv[3])

class Sqlbase:
    def __init__ (self, dbc):
        self.__dbc = dbc
        self.__cursor = dbc.cursor()
        return

    def dbc (self):
        return self.__dbc

    def sql (self, sqlexpr, args1 = (), args2 = ()):
        self.__cursor.execute (sqlexpr, args1, args2)
        return self.__cursor.fetchall ()

def runTrigger(sql,runnum_low, runnum_high):
    l=sql.sql("select "
              "Run_Number "
              ",Trg_Type "
              ",to_number(Bit_Num) Bit_Num "
              ", Bit_Name,Prescale,Depend_Bit "
              "from   runs.run_trigs "
              "where  (Run_Number >:p1) "
              "and (Run_Number <:p2) "
              "order by Run_Number DESC,Eg_Num,Trg_Type,Bit_Num,Bit_Name,Prescale,Depend_Bit "
              ,runnum_low, runnum_high)
    DATA={'L1name':{},'L2name':{},'L3name':{},'L1bit':{},'L2bit':{},'L3bit':{}}
    RUNS={}
    for i in l:
        runnum,level,bit,name,prescale,depend=i
        bit=int(bit)
        if prescale==None: prescale='1'
        if prescale.endswith('%'):
            prescale=float(prescale[0:len(prescale)-1])
        else:
            prescale=float(prescale)
        DATA[level].setdefault(bit,{})['name']=name
        DATA[level.replace('bit','name')][name]=DATA[level][bit]
        DATA[level][bit][level]=bit
        DATA[level][bit]['prescale']=prescale
        if level=='L2bit':
            DATA[level][bit]['L1bit']=int(depend)
        elif level=='L3bit':
            if (depend==None):
                print i
            else:
                DATA[level][bit]['L2bit']=int(depend)
                DATA[level][bit]['L1bit']=int(DATA['L2bit'].get(int(depend),{}).get('L1bit',-1))
                DATA[level][bit]['L1prescale']=DATA['L1bit'].get(DATA[level][bit]['L1bit'],{}).get('prescale',-1)
                RUNS.setdefault(runnum,{})[name]=DATA[level][bit]['L1prescale']
    return RUNS

rundbc = Sqlbase(dcoracle.Connect ("runs/d0run_data@d0onprd"))
DATA=runTrigger(rundbc,runnum_low, runnum_high)
del rundbc

def sorted(list):
    list.sort()
    return list

for run in sorted(DATA.keys()):
    if DATA[run].has_key(trigger): 
        print run , DATA[run][trigger]
        
