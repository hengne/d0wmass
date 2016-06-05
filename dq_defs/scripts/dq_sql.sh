#! /bin/sh
# extract the various badruns lists from the dq and runs db's
#
# usage: sql.howto
#

. ${SETUPS_DIR}/setups.sh
setup oracle_client
sqlplus d0read/reader@d0ofprd1 << EOF

-- set page formats

set NEWPAGE NONE
set pagesize 0
set linesize 320
column trig_config_name format A50 ;

spool all-a.runs.db

select r.run_number, r.trig_config_name from runs.runs r where (r.run_number >= 151817 and r.run_number <= 219000 and r.recording like '1' and r.trig_config_name like 'official/global%') order by r.run_number asc ;

spool off
spool all-b1.runs.db

select r.run_number, r.trig_config_name from runs.runs r where (r.run_number > 219000 and r.run_number <= 234913 and r.recording like '1' and r.trig_config_name like 'official/global%') order by r.run_number asc ;

spool off
spool all-b2.runs.db

select r.run_number, r.trig_config_name from runs.runs r where (r.run_number >= 237342 and r.run_number <= 252918 and r.recording like '1' and r.trig_config_name like 'official/global%') order by r.run_number asc ;

spool off
spool all-b3.runs.db

select r.run_number, r.trig_config_name from runs.runs r where (r.run_number >= 255328 and r.run_number <= 262856 and r.recording like '1' and r.trig_config_name like 'official/global%') order by r.run_number asc ;

spool off
spool all-b4.runs.db

select r.run_number, r.trig_config_name from runs.runs r where (r.run_number >= 264071 and r.run_number <= 275727 and r.recording like '1' and r.trig_config_name like 'official/global%') order by r.run_number asc ;

spool off

spool cttx13-a.badruns.db

select q.run_number, q.qual_group, r.trig_config_name from runs.runs r, runs.run_quality q, runs.run_quality_params p where (q.run_number >= 151817 and q.run_number <= 219000 and q.qual_group = 'CTT') and (r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') and (p.run_number = q.run_number and ( p.par_name = 'cr13stat' and p.par_value != 'GOOD' and p.par_value != 'REASONABLE' ) ) order by q.run_number asc ;

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >= 151817 and q.run_number <= 219000 and q.qual_group = 'CTT') and (r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') and ( not exists (select '' from runs.run_crates c where r.run_number=c.run_number and c.crate_dec=19) ) order by q.run_number asc ;

spool off
spool cttx13-b1.badruns.db

select q.run_number, q.qual_group, r.trig_config_name from runs.runs r, runs.run_quality q, runs.run_quality_params p where (q.run_number > 219000 and q.run_number <= 234913 and q.qual_group = 'CTT') and (r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') and (p.run_number = q.run_number and ( p.par_name = 'cr13stat' and p.par_value != 'GOOD' and p.par_value != 'REASONABLE' ) ) order by q.run_number asc ;

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 219000 and q.run_number <= 234913 and q.qual_group = 'CTT') and (r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') and ( not exists (select '' from runs.run_crates c where r.run_number=c.run_number and c.crate_dec=19) ) order by q.run_number asc ;

spool off
spool cttx13-b2.badruns.db

select q.run_number, q.qual_group, r.trig_config_name from runs.runs r, runs.run_quality q, runs.run_quality_params p where (q.run_number > 237342 and q.run_number <= 252918 and q.qual_group = 'CTT') and (r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') and (p.run_number = q.run_number and ( p.par_name = 'cr13stat' and p.par_value != 'GOOD' and p.par_value != 'REASONABLE' ) ) order by q.run_number asc ;

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 237342 and q.run_number <= 252918 and q.qual_group = 'CTT') and (r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') and ( not exists (select '' from runs.run_crates c where r.run_number=c.run_number and c.crate_dec=19) ) order by q.run_number asc ;

spool off
spool cttx13-b3.badruns.db

select q.run_number, q.qual_group, r.trig_config_name from runs.runs r, runs.run_quality q, runs.run_quality_params p where (q.run_number > 255328 and q.run_number <= 262856 and q.qual_group = 'CTT') and (r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') and (p.run_number = q.run_number and ( p.par_name = 'cr13stat' and p.par_value != 'GOOD' and p.par_value != 'REASONABLE' ) ) order by q.run_number asc ;

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 255328 and q.run_number <= 262856 and q.qual_group = 'CTT') and (r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') and ( not exists (select '' from runs.run_crates c where r.run_number=c.run_number and c.crate_dec=19) ) order by q.run_number asc ;

spool off
spool cttx13-b4.badruns.db

select q.run_number, q.qual_group, r.trig_config_name from runs.runs r, runs.run_quality q, runs.run_quality_params p where (q.run_number > 264071 and q.run_number <= 275727 and q.qual_group = 'CTT') and (r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') and (p.run_number = q.run_number and ( p.par_name = 'cr13stat' and p.par_value != 'GOOD' and p.par_value != 'REASONABLE' ) ) order by q.run_number asc ;

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 264071 and q.run_number <= 275727 and q.qual_group = 'CTT') and (r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') and ( not exists (select '' from runs.run_crates c where r.run_number=c.run_number and c.crate_dec=19) ) order by q.run_number asc ;

spool off

spool muo-a.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >= 151817 and q.run_number <= 219000) and (q.qual_group = 'MUO' and q.quality != 'REASONABLE') and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%' order by q.run_number asc ;

spool off
spool muo-b1.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 219000 and q.run_number <= 234913) and (q.qual_group = 'MUO' and q.quality != 'REASONABLE') and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%' order by q.run_number asc ;

spool off
spool muo-b2.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=237342 and q.run_number <= 252918) and (q.qual_group = 'MUO' and q.quality != 'REASONABLE') and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%' order by q.run_number asc ;

spool off
spool muo-b3.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=255328 and q.run_number <= 262856) and (q.qual_group = 'MUO' and q.quality != 'REASONABLE') and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%' order by q.run_number asc ;

spool off
spool muo-b4.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=264071 and q.run_number <= 275727) and (q.qual_group = 'MUO' and q.quality != 'REASONABLE') and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%' order by q.run_number asc ;

spool off

spool smt-a.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >= 151817 and q.run_number <= 219000) and (q.qual_group = 'SMT' and q.quality != 'REASONABLE') and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%' order by q.run_number asc ;

spool off
spool smt-b1.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 219000 and q.run_number <= 234913) and (q.qual_group = 'SMT' and q.quality != 'REASONABLE') and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%' order by q.run_number asc ;

spool off
spool smt-b2.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=237342 and q.run_number <= 252918) and (q.qual_group = 'SMT' and q.quality != 'REASONABLE') and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%' order by q.run_number asc ;

spool off
spool smt-b3.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=255328 and q.run_number <= 262856) and (q.qual_group = 'SMT' and q.quality != 'REASONABLE') and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%' order by q.run_number asc ;

spool off
spool smt-b4.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=264071 and q.run_number <= 275727) and (q.qual_group = 'SMT' and q.quality != 'REASONABLE') and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%' order by q.run_number asc ;

spool off

spool calon-a.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >= 151817 and q.run_number <= 219000) and (q.qual_group = 'CAL' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool calon-b1.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 219000 and q.run_number <= 234913) and (q.qual_group = 'CAL' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool calon-b2.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=237342 and q.run_number <= 252918) and (q.qual_group = 'CAL' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool calon-b3.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=255328 and q.run_number <= 262856) and (q.qual_group = 'CAL' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool calon-b4.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=264071 and q.run_number <= 275727) and (q.qual_group = 'CAL' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off

spool calt-b1.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 219000 and q.run_number <= 234913) and (q.qual_group = 'CAL1' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool calt-b2.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=237342 and q.run_number <= 252918) and (q.qual_group = 'CAL1' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool calt-b3.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=255328 and q.run_number <= 262856) and (q.qual_group = 'CAL1' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool calt-b4.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=264071 and q.run_number <= 275727) and (q.qual_group = 'CAL1' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off

spool cft-a.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >= 151817 and q.run_number <= 219000) and (q.qual_group = 'CFT' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool cft-b1.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 219000 and q.run_number <= 234913) and (q.qual_group = 'CFT' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool cft-b2.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=237342 and q.run_number <= 252918) and (q.qual_group = 'CFT' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool cft-b3.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=255328 and q.run_number <= 262856) and (q.qual_group = 'CFT' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool cft-b4.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=264071 and q.run_number <= 275727) and (q.qual_group = 'CFT' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off

spool ctt-a.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >= 179038 and q.run_number <= 219000) and (q.qual_group = 'CTT' and q.quality = 'BAD' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool ctt-b1.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 219000 and q.run_number <= 234913) and (q.qual_group = 'CTT' and q.quality != 'GOOD' and q.quality != 'REASONABLE' and q.quality != 'UNKNOWN' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool ctt-nocert-b1.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number > 219000 and q.run_number <= 234913) and (q.qual_group = 'CTT' and q.quality = 'UNKNOWN' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool ctt-b2.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=237342 and q.run_number <= 252918) and (q.qual_group = 'CTT' and q.quality != 'GOOD' and q.quality != 'REASONABLE' and q.quality != 'UNKNOWN' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool ctt-b3.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=255328 and q.run_number <= 262856) and (q.qual_group = 'CTT' and q.quality != 'GOOD' and q.quality != 'REASONABLE' and q.quality != 'UNKNOWN' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool ctt-b4.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=264071 and q.run_number <= 275727) and (q.qual_group = 'CTT' and q.quality != 'GOOD' and q.quality != 'REASONABLE' and q.quality != 'UNKNOWN' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off

spool ctt-nocert-b2.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=237342 and q.run_number <= 252918) and (q.qual_group = 'CTT' and q.quality = 'UNKNOWN' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool ctt-nocert-b3.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=255328 and q.run_number <= 262856) and (q.qual_group = 'CTT' and q.quality = 'UNKNOWN' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
spool ctt-nocert-b4.badruns.db

select q.run_number, q.qual_group, q.quality, r.trig_config_name from runs.runs r, runs.run_quality q where (q.run_number >=264071 and q.run_number <= 275727) and (q.qual_group = 'CTT' and q.quality = 'UNKNOWN' and r.run_number=q.run_number and r.recording like '1' and r.trig_config_name like 'official/global%') order by q.run_number asc ;

spool off
EOF

# after official/global% add  "and prescname not like 'scraping'" to remove scraping runs


for i in *db
do
  `dirname $0`/clean.sh ${i}
done
