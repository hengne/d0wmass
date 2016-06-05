#!/bin/sh
# Stop project script
# expects environment: SAM_PROJECT
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

# Dump the project and consumer status

tmp_file=/tmp/sam.user.log.$$
sam dump project --project="$SAM_PROJECT" > $tmp_file 2>&1
CID=`cat $tmp_file | grep "CID=" | awk '{print substr($1,5)}' | sed "s/://"`
cat $tmp_file
rm -f $tmp_file
sam dump consumer --cid="$CID" --project="$SAM_PROJECT"

# Stop the SAM project
echo "Stopping the project ${SAM_PROJECT}"
sam stop project --force --project=${SAM_PROJECT}
sam get project summary --project=${SAM_PROJECT}
