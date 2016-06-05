#!/bin/bash
# 
# 

#
# This is needed for the SAM libraries who start
# additional threads (?). The batch system sets
# a giant stack size and adds it all up, until
# the job aborts with a 'too much virtual memory'
# signal.
#
ulimit -s 8192

debug()
{
    echo "SAM_DEFINITION = ${SAM_DEFINITION}"
    echo "LIB_DEFINITION = ${LIB_DEFINITION}"
    echo "SAM_PROJECT    = ${SAM_PROJECT}"
    echo "FILELIST       = ${FILELIST}"
    echo "NUM_JOBS       = ${NUM_JOBS}"
    echo "JOB_INDEX      = ${JOB_INDEX}"
    echo "EXECUTABLE     = ${EXECUTABLE}"
    echo "ARGUMENTS      = ${ARGUMENTS}"
    echo "NAME           = ${NAME}"
    echo "OUTPUT_HOST    = ${OUTPUT_HOST}"
    echo "OUTPUT_DIR     = ${OUTPUT_DIR}"
    echo "OUTPUT_FILES   = ${OUTPUT_FILES}"
    echo "INPUT_HOST     = ${INPUT_HOST}"
    echo "INPUT_DIR      = ${INPUT_DIR}"
    echo "INPUT_FILES    = ${INPUT_FILES}"
    echo "INPUT_TAR      = ${INPUT_TAR}"
    echo "SCRIPT_INIT    = ${SCRIPT_INIT}"
    echo "SCRIPT_SOURCE  = ${SCRIPT_SOURCE}"
    echo "SCRIPT_FINISH  = ${SCRIPT_FINISH}"
    echo "CLUSTER        = ${CLUSTER}"
    echo "HOST           = `hostname`"
    echo "RSYNC_OPTIONS  = ${RSYNC_OPTIONS}"
    echo "EXCLUDE        = ${EXCLUDE}"
    echo "GROUP          = ${GROUP}"
}

debug2()
{
    echo "======================================"
    echo "LD_LIBRARY_PATH = ${LD_LIBRARY_PATH}"
    echo "PATH            = ${PATH}"
    echo "ARGUMENTS       = ${ARGUMENTS}"
    echo "======================================"
}

debug

###########################
# timeout watchdog
###########################
watchdog()
{
    while /bin/true
    do
      sleep 600

      # These two files should exist
      [ -f ${EXECUTABLE_OUT} ] || return
      [ -f ${EXECUTABLE_ERR} ] || return

      # We check for EXECUTABLE_OUT, EXECUTABLE_ERR
      # If none of the two has changed for the last 6 hours
      # We kill the executable.

      if [ $(( `date +%s` - `stat -c %Y ${EXECUTABLE_OUT}` )) -lt 21600 ]; then
	  continue
      fi

      if [ $(( `date +%s` - `stat -c %Y ${EXECUTABLE_ERR}` )) -lt 21600 ]; then
	  continue
      fi

      echo "watchdog: output files have not changed for 6h, killing executable..."
      if [ "${SAM_PROJECT}" -a "${SAM_CPID_DESC}" ]; then
        echo "watchdog: trying to end SAM consumer"
        # If this command works then we need to give the job time to end. If it doesn't end then it still needs to be killed.
        sam end file processing -s --corbaCallTimeout=60 --retryMaxCount=5 --project=${SAM_PROJECT} --processDesc=${SAM_CPID_DESC}
        unset SAM_CPID_DESC # so we won't try stopping it again
        continue
      fi
      kill $1
      return
    done
}

##########################################
# untar file with proper options based on
# filename
##########################################
untar()
{
    TAR_OPT=""
    case $1 in
	*.gz)
	    TAR_OPT=z
	    ;;
	*.bz2)
	    TAR_OPT=j
	    ;;
	*.tgz)
	    TAR_OPT=z
	    ;;
	*.Z)
	    TAR_OPT=Z
	    ;;
    esac

    if tar --version | head -1 | fgrep -q 1.13
    then
	# old tar version
	tar ${TAR_OPT}xf $1
    else
	# new tar version
	tar --no-overwrite-dir -${TAR_OPT}xf  $1
    fi
}

setpath()
{
for DIR in /usr/krb5/bin \
	   /usr/sbin \
	   /usr/afsws/bin \
	   /usr/afsws/etc \
	   /opt/SUNWspro/bin \
           /usr/ccs/bin \
 	   /usr/lang \
	   /usr/bsd \
	   /bin \
	   /usr/bin \
	   /usr/lbin \
	   /usr/ucb \
	   /etc \
	   /usr/etc \
	   /usr/bin/X11 \
	   /usr/kinet/bin \
	   /usr/local/bin \
	   /usr/sccs
do
	if [ -d ${DIR} ]
	then
		PATH=${PATH}${DIR}:
	fi
done
export PATH
}

get_sam_libraries()
{

    echo $1 $1

    echo '#!/usr/bin/env python' > getroot.py
    echo 'import os, sys, string, time, signal' >> getroot.py
    echo 'from re import *' >> getroot.py
    echo 'sam_station        = "fnal-cabsrv1"' >> getroot.py
    echo "project_definition = \"${1}\"" >> getroot.py
    echo 'snapshot_version   = "new"' >> getroot.py
    echo 'appname            = "generic"' >> getroot.py
    echo 'version            = "1"' >> getroot.py
    echo 'group              = "dzero"' >> getroot.py
    echo 'max_file_amt       = 1' >> getroot.py
    echo 'verbosity          = ""' >> getroot.py
    echo 'give_up            = 1' >> getroot.py
    echo 'def file_ready(filename):' >> getroot.py
    echo '    os.system("scp %s ./" % filename)' >> getroot.py
    echo '    return' >> getroot.py

    TEMP_SAM_PROJECT=${SAM_PROJECT}
    unset SAM_PROJECT

    local COUNT=5
    while [ ! -e ${LIB_DEFINITION}.tar.gz ] && [ ${COUNT} -gt 0 ]
    do
      sam run project --interactive getroot.py      
      COUNT=$(( ${COUNT} - 1 ))
    done
    if [ ! -e ${LIB_DEFINITION}.tar.gz ]; then
	exit 1
    fi
    tar -xzf ${LIB_DEFINITION}.tar.gz

    SAM_PROJECT=${TEMP_SAM_PROJECT}
    export SAM_PROJECT

}

######################################
# Add filelist/stageinlist arguments
# Split input lists if necessary
#
# $1 = filelist or stageinlist
# $2 = name of list file
######################################
handle_lists()
{
# If filelist and multiple jobs, modify arguments to skip files
if [ ! -z "${2}" ]; then
    if [ ${NUM_JOBS} -gt 1 ]; then
	#
	# Splitting the input file list
	#
	LENGTH=`wc -l ${2} |  awk '{ print $1; }'`
        # Round up the number of files per job
        FILES_PER_JOB=$(( LENGTH / NUM_JOBS + (LENGTH % NUM_JOBS == 0 ? 0 : 1 ) ))
	SKIP=$(( ${FILES_PER_JOB} * ${JOB_INDEX} ))
	LASTJOB=$(( ${SKIP} + $FILES_PER_JOB ))
	cat ${2} | awk '{((NR > '${SKIP}') && (NR <= '${LASTJOB}')) print}' > myfiles.list
#	ARGUMENTS="${ARGUMENTS} Input: ${1}:${2} SkipFiles: ${SKIP} Files: ${FILES_PER_JOB} "
	echo Split filelist: processing files ${SKIP} to $(( ${SKIP} + ${FILES_PER_JOB} ))
    else
	cp ${2} myfiles.list
#	ARGUMENTS="${ARGUMENTS} Input: ${1}:${2}"
    fi
    ARGUMENTS="${ARGUMENTS} -f myfiles.list"
fi

}

##########################
# Cluster specific setup
##########################

#####################################################################################
#
# A new cluster can be added here by defining the
# following functions:
#
# get_ticket()               : aquire a kerberos ticket (if appropriate)
# copy_in(source,dest,host)  : stage in data to batch node
# copy_out(source,dest,host) : stage out data from batch node to dest
# copy_dir_in(source, dest, host) : copy in working directory, 
#                              can be implemented by copy_in()
#
#################################################################################### 

case "${CLUSTER}" in

clued0)

    ##############################
    # create the work area
    ##############################
    if [ -d /batch ]; then
	WORKAREA=/batch/${PBS_JOBID}
    else
	WORKAREA=/work/local/batchjobs/${PBS_JOBID}
    fi

    if ! mkdir -p ${WORKAREA}
    then
	echo "No WORKAREA: ${WORKAREA} on `hostname`"
	exit 1
    fi
    
    get_ticket()
    {
	true
    }

    copy_in()
    {
	cp -r $1 $2
    }

    copy_out()
    {
	cp -r $1 $2
    }

    copy_dir_in()
    {
	rsync -prz ${RSYNC_OPTIONS} ${EXCLUDE} ${1%/} $2
    }

    . /etc/bashrc
    # . /D0/ups/etc/setups.sh
    ;;

cab*)

    ##############################
    # create the work area
    ##############################

    WORKAREA=/scratch/${PBS_JOBID}
    cd ${WORKAREA} || exit 1
    unset UPS_DIR UPS_SHELL SETUP_UPS SETUPS_DIR
    source /usr/products/etc/setups.sh

    setup setpath
    setup limit_transfers

    get_ticket()
    {
        /usr/krb5/bin/kbatch
        # On SL4 /usr/krb5/bin/klist doesn't support the -5
	# flag, while on SL5 we need it or we get an error
        # since we have no Kerberos 4 tickets
        /usr/kerberos/bin/klist -5 || return 1

        # This runs in the background and will be killed when
	# the batch system stops our job and signals the whole
        # process group.
        while true; do sleep 28000; /usr/krb5/bin/kbatch; done &

    }

    copy_in()
    {
	local host
	[ "$3" != "NFS" ] && host=$3
	limit_transfers -v ${host:+--queue=}${host} rsync -p -r ${host}${host:+:}${1%/} $2
    }

    copy_dir_in()
    {
	local host
	[ "$3" != "NFS" ] && host=$3
	# ${1%/} strips a trailing slash if present
	limit_transfers -v ${host:+--queue=}${host} rsync -prz ${RSYNC_OPTIONS} ${EXCLUDE} ${host}${host:+:}${1%/} $2 
    }

    copy_out()
    {
	local host COUNT=3
	[ "$3" != "NFS" ] && host=$3
	while [ ${COUNT} -gt 0 ]
	do
	  limit_transfers -v ${host:+--queue=}${host} rsync -p -r ${1%/} ${host}${host:+:}$2
	  local rval=$?
	  if [ $rval -eq 0 ]
	  then
	      break
	  else
	      COUNT=$(( ${COUNT} - 1 ))
	      sleep $(( ${RANDOM} / 1000 ))
	  fi
	done
	return $rval
    }
    ;;

*)
    echo "Unknown cluster: ${CLUSTER}"
    exit 1
    ;;
esac

export WORKAREA
cd ${WORKAREA} || exit 1

export RESULT_DIR=`basename ${NAME}`-${PBS_JOBID}
mkdir ${RESULT_DIR}

#
# Get kerberos ticket if necessary.
#
get_ticket || exit 1

#
# Copy in the initial directory and all 
# additional directories/files.
#
if [ ! -z "${INPUT_TAR}" ]; then
    copy_in ${INPUT_TAR} . ${INPUT_HOST}
    untar `basename ${INPUT_TAR}` || exit 2
else
    copy_dir_in ${INPUT_DIR} . ${INPUT_HOST}
    cd `basename ${INPUT_DIR}` || exit 2
fi

# We require that D0RunII is setup.
setup D0RunII ${SRT_BASE_RELEASE} -O SRT_QUAL=${SRT_QUAL}
setup lhapdf -q GCC3_4_3
setup d0tools
setup sam
export LINK_SHARED=yes 
cd wz_epmcs/src

if [ "${CLUSTER}" = "clued0" ]
then
   setup sam
else
   setup sam -q ${CLUSTER}
fi

for file in ${INPUT_FILES}
do
  copy_in ${file} . ${PBS_O_HOST}  || echo "Cannot copy: ${file}"
done

if [ -n ${LIB_DEFINITION} ]; then
    get_sam_libraries ${LIB_DEFINITION} || echo "Cannot copy libraries from SAM"
fi

export PATH=${PATH}${SRT_PRIVATE_CONTEXT}/shbin/${SRT_SUBDIR}:${SRT_PUBLIC_CONTEXT}/shbin/${SRT_SUBDIR}:.

# Check executable first
if [ ! -x ${EXECUTABLE} ]; then
    echo "Executable ${EXECUTABLE} not found !"
    exit 1
fi

export SAM_PROJECT

# If only one job and SAM project, start it ourself
if [ ${NUM_JOBS} -eq 1 -a ! -z "${SAM_PROJECT}" ]; then
    echo "Starting SAM Project with definition: ${SAM_DEFINITION}, name = ${SAM_PROJECT}"
    if ! sam start project --defname=${SAM_DEFINITION} --group=${GROUP} --project=${SAM_PROJECT} ${SAM_FILECUT}
    then
	echo "Cannot start SAM project with definition: ${SAM_DEFINITION}"
	exit 1
    fi
fi

EXECUTABLE_OUT=`basename ${EXECUTABLE}`.out
EXECUTABLE_ERR=`basename ${EXECUTABLE}`.err

# If SAM project, modify cafe arguments
if [ "${SAM_PROJECT}" ]; then
    export SAM_CPID_DESC=${PBS_JOBID}
#    ARGUMENTS="${ARGUMENTS} Input: sam:definition SAM.ProcessDescription: ${SAM_CPID_DESC}"
fi

# If filelist and multiple jobs, modify arguments to skip files

if [ ! -z "${FILELIST}" ]; then
    handle_lists listfile ${FILELIST}
elif [ ! -z "${STAGEINLIST}" ]; then
    handle_lists stageinlist ${STAGEINLIST}
fi

#debug2

if [ ! -z "${SCRIPT_SOURCE}" ]; then
    source ${SCRIPT_SOURCE}
fi

if [ ! -z "${SCRIPT_INIT}" ]; then
    ${SCRIPT_INIT}
fi

#${EXECUTABLE} ${ARGUMENTS} > ${EXECUTABLE_OUT}
${EXECUTABLE} ${ARGUMENTS} > ${EXECUTABLE_OUT} 2> ${EXECUTABLE_ERR} &
JOBPID=$!
watchdog $JOBPID &
wait $JOBPID
RESULT=$?

if [ ! -z "${SCRIPT_FINISH}" ]; then
    ${SCRIPT_FINISH} ${RESULT}
fi

shopt -s nullglob
mv ${EXECUTABLE_OUT} ${EXECUTABLE_ERR} ${OUTPUT_FILES} ${WORKAREA}/${RESULT_DIR}

get_ticket
{ cd ${WORKAREA} && copy_out ${RESULT_DIR} ${OUTPUT_DIR} ${OUTPUT_HOST} ; } || RESULT=$?

if [ "$SAM_PROJECT" ]; then
 
    if [ ${RESULT} -eq 0 ]; then
	# Mark the sam consumer as completed
	SAM_CPID=$(sam get consumer process ids --project=${SAM_PROJECT} --desc=${SAM_CPID_DESC}) && [ "$SAM_CPID" ] && sam commit process --processId=${SAM_CPID} --status=completed
    fi
    
    if [ ${NUM_JOBS} -eq 1 ]; then
	echo "Stopping SAM project"
	sam stop project --force --project=${SAM_PROJECT}
	sam get project summary --project=${SAM_PROJECT}
    fi
fi

exit ${RESULT}
