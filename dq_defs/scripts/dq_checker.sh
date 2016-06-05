#! /bin/bash

if [ $# -lt 2 ]
then
    echo "usage: `basename $0` <TRIG> <SKIM> [DB]"
    echo ""
    echo "<TRIG>    - trigger to consider"
    echo "<SKIM>    - datasets parent CSG skim, run genLBNtables for a list of available skims"
    echo "[DB]      - optional - DB format rather than Stage 3"
    echo "This script will go through all the necessary steps to collect the luminosity data"
    echo "for the full range of runs in a dataset."
    echo "You can feed a superset of bad runs, bad lbns, and good runs by creating a"
    echo "badRunsList, badLBNList, and/or goodRunsList file in the directory"
    echo ""
    echo "It should be followed by running 'dq_checker_sum.sh' to sum the luminosities in a"
    echo "range of runs."
    echo ""
    exit 1
fi


. /etc/bashrc
. ${SETUPS_DIR}/setups.sh

setup sam
setup lm_tools -d

#MAILTO="jonckheere@fnal.gov"

TRIG=${1}
SKIM=${2}
db="stage3"
if test "x${3}" = "xDB"
then
  db="lmdb"
fi

if test "x${SKIM}" = "xnone"
then
   SKIM_DIR="not_skimmed"
else
   SKIM_DIR=${SKIM}
fi

if test "x${MAILTO}" != "x"
then
  echo "dq_checker.sh ${SKIM} in `/bin/pwd` starting" | /bin/mail -s "dq_checker.sh ${SKIM} starting" ${MAILTO}
fi

echo "Skim:    ${SKIM}"

rm -f 001-${SKIM}.files
rm -f 000-runrange.list
rm -f 000-output.lumi

if test "${db}" = "stage3"
then
   ls ${SKIM_DIR} | sed -e 's/.parentage//' > 001-${SKIM}.files
   ls ${SKIM_DIR} | sed -e "s#.*#cat ${SKIM_DIR}/\0 | cut -f3 -d' '#" | sh > 000-runrange.list
else
   ls ${SKIM_DIR} | sed -e 's/.lumiDB//' > 001-${SKIM}.files
   ls ${SKIM_DIR} | sed -e "s#.*#cat ${SKIM_DIR}/\0 | cut -f5 -d' '#" | sh > 000-runrange.list
fi

cat 000-runrange.list | sort -n -u | sed -e "s/.*/${TRIG} \0 \0/" > tmp
mv -f tmp 000-runrange.list

getLuminosity --${db} --ignoremissingstreams --runrange 001-${SKIM}.files ./${SKIM_DIR}/ 000-runrange.list > 000-output.lumi

# Clean up working directory. We don't need these files, so unclutter
rm -rf out.caf
mkdir out.caf
for i in 001-${SKIM}.files*caf
do
   mv ${i} out.caf
done
rm -rf out.sum
mkdir out.sum
for i in 001-${SKIM}.files*sum
do
   mv ${i} out.sum
done
rm -rf out.badlbns
mkdir out.badlbns
for i in parentage*badlbns reconstructed*badlbns recorded*badlbns
do
   mv ${i} out.badlbns
done

# Extract the Run/Luminosity table
rm -f 000-${SKIM}.run_lum
cat 000-output.lumi | grep "^reconstructed" | grep "with bad" | sed -e 's/^.*[0-9]-//; s/ and.*://; s/ pb.*//' > 000-${SKIM}.run_lum

if test "x${MAILTO}" != "x"
then
  echo "dq_checker.sh ${SKIM} in `/bin/pwd` finished" | /bin/mail -s "dq_checker.sh ${SKIM} done" ${MAILTO}
fi
