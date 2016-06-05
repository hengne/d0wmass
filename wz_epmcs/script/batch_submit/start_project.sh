#!/bin/sh
#
# Start project script
#
# expects in environment: SAM_DEFINITION, SAM_PROJECT, SAM_FILECUT (should be --fileCut=... or empty)
# 

case "${CLUSTER}" in
    clued0)
	. /etc/bashrc
	;;
    cab*)
	. /usr/local/etc/setups.sh
	;;
    *)
	echo "Unknown cluster: ${CLUSTER}"
	exit 1
	;;
esac

setup setpath
if [ ${CLUSTER} = "clued0" ]; then
    setup sam
else
    setup sam -q ${CLUSTER}
fi

sam start project --defname=${SAM_DEFINITION} --group=${SAM_WORKGROUP} --project=${SAM_PROJECT} ${SAM_FILECUT}
# return value is exit status of 'sam start project'
