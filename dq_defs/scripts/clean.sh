#! /bin/sh

sed -i -e 's/[ ]*$//' ${1}

#cat ${1} | egrep -v "RUN_NUMBER|----------|^$" > ${1}.tmp
#mv ${1}.tmp ${1}

bd=`echo ${1} | sed -e 's/.db//'`
rm -f ${bd}

# 1st one requires "official/global%", 2d just "%global%" (from the sql query)

#cat ${1} | egrep "official/global" | egrep -v "^SQL>|rows selected|^[ ]*$"| sort -u | sed -e 's/^[ ]*//' | cut -d" " -f1 > ${bd}
cat ${1} | egrep -v "^SQL>|rows selected|^[ ]*$"| sort -u | sed -e 's/^[ ]*//' | cut -d" " -f1 > ${bd}
