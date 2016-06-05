#!/usr/bin/env python
# This is to generate a list of 'trigger version #' vs. 'run #'
# reads the runs database, can also have a cutoff at a given trigger version #
# Example: mkruntrigvlist.py [16.22] 
#
# Setup instructions:
# setup python_dcoracle
#

# -------------------------------------------------
class Sqlbase:
    def __init__ (self, dbc):
        self.__dbc = dbc
        self.__cursor = dbc.cursor()
        return

    def dbc (self):
        return self.__dbc

    def sql (self, sqlexpr, args = ()):
        self.__cursor.execute (sqlexpr, args)
        return self.__cursor.fetchall ()

# -------------------------------------------------

import dcoracle, sys

runsdb = dcoracle.Connect ("samread/reader@d0ofprd1")
sqldb = Sqlbase(runsdb)

#l = sqldb.sql("select run_number, trig_config_vers  from runs.runs where trig_config_type='physics' and trig_config_name='official/global_CalMuon' order by run_number")
l = sqldb.sql("select run_number, trig_config_vers  from runs.runs where trig_config_type='physics' and trig_config_name='official/global_CMT' order by run_number")
runsdb.close ()

runs = []
for (run,trig) in l:
    runs.append((run,trig))

cutoff=0
if len(sys.argv) == 2:
    cutoff = float(sys.argv[1])

#print "Run#  ", "TrigVer#"

for (run,tv) in runs:
    tv=float(tv)
    if tv >= cutoff:
       print run,int(tv*100)
