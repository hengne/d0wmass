#! /bin/sh
# run *after* dq_checker.sh has created runrange in the same directory.

rm -f QCD.runs
cat runrange | cut -d " " -f 2 | sort -u > QCD.runs

rm -f tt.in
touch tt.in
cat <<EOF >> tt.in
spool tt.out

set NEWPAGE NONE
set pagesize 0
set linesize 132
column trig_config_name format A50

EOF

for i in `cat QCD.runs`
do
  echo "select A.run_number, A.qual_group, A.quality, B.recording, B.trig_config_name, B.trig_config_type, B.physics, B.prescname from runs.run_quality A, runs.runs B where A.run_number=B.run_number and A.run_number=${i};" >> tt.in
done

rm -f tt.out

. ${SETUPS_DIR}/setups.sh
setup oracle_client
sqlplus d0read/reader@d0ofprd1 < tt.in

rm -f tt2.out
cat tt.out | egrep -v "^SQL>|rows selected.$|^$" | tr -s " " | sed -e "s/[ ]*$//" > tt2.out
