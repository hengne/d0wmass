#! /bin/bash

if [ $# -lt 2 ]
then
    echo "usage: $0 SKIM BADRUNS [MINRUN] [MAXRUN]"
    echo ""
    echo "SKIM    - datasets parent CSG skim, run genLBNtables for a list of available skims"
    echo "BADRUNS - file containing a list of bad runs files used seperately to calculate"
    echo "          the luminosity"
    echo "MINRUN  - [optional] minimum run number to sum, default 0"
    echo "MAXRUN  - [optional] maximum run number to sum, default 9999999"
    echo ""
    echo "This script will sum the luminosity for the run range specified, removing runs"
    echo "listed in each of the files listed in BADRUNS."
    echo "It uses the data previously put into the working directory by dq_checker.sh."
    echo ""
    exit 1
fi


SKIM=${1}
BADRUNS=${2}

MINRUN=0
MAXRUN=9999999

if [ ${3} ]
then
    MINRUN=${3}
fi

if [ ${4} ]
then
    MAXRUN=${4}
fi

echo "Skim:    ${SKIM}"
echo "Badruns: ${BADRUNS}"
echo "Minrun:  ${MINRUN}"
echo "Maxrun:  ${MAXRUN}"

# Sum all runs
totalSUM="0.0"
totalNRUNS=0
while read RUN LUM
do
   if [ ${RUN} -ge ${MINRUN}  -a ${RUN} -le ${MAXRUN} ]
   then
      LUM=`echo ${LUM} | sed -e 's/\(.*\)e\(.*\)/scale=10; \1 * 10^\2/' | bc`
      totalSUM=`echo ${totalSUM} + ${LUM} | bc`
      ((totalNRUNS+=1))
   fi
done < 000-${SKIM}.run_lum
echo "Total Luminosity: ${totalSUM}"
echo "Total Runs: ${totalNRUNS}"

# Loop over badruns lists in ${BADRUNS} == list of lists
# Sum just the badruns
for RUNLIST in `cat ${BADRUNS}`
do
    badSUM="0.0"
    badNRUNS=0
    for RUN in `cat ${RUNLIST}`
    do
       if [ ${RUN} -ge ${MINRUN}  -a ${RUN} -le ${MAXRUN} ]
       then
           LUM=`egrep "^${RUN}" 000-${SKIM}.run_lum`
           if [ "x${LUM}" != "x" ]
           then
              LUM=`echo ${LUM}| cut -d " " -f 2 | sed -e 's/\(.*\)e\(.*\)/scale=10; \1 * 10^\2/' | bc`
               badSUM=`echo ${badSUM} + ${LUM} | bc`
               ((badNRUNS+=1))
           fi
       fi
    done

    echo "${RUNLIST} Bad Luminosity: ${badSUM}"
    echo "${RUNLIST} Bad Runs: ${badNRUNS}"
done

