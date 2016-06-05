#!/bin/sh
# This gets the environment
. /etc/bashrc
# The next part sets the current directory to the work
# directory as specified by the batch system
# $WORKDIR is set by sourcing /usr/local/etc/pbssetup.sh
# Some error checking is done.
WORKDIR="0NE"
if [ -r /usr/local/etc/pbssetup.sh ]; then
    . /usr/local/etc/pbssetup.sh
    echo "Found pbssetup.sh"
    echo "Workdir is now:"
    echo $WORKDIR
else
    echo "ERROR: Could not find /usr/local/etc/pbssetup.sh"
    echo "ERROR: Maybe the partition is not mounted correctly"
    echo "ERROR: Exiting..."
    exit 1
fi
if [ $WORKDIR = "0NE" ]; then
    echo "ERROR: WORKDIR is not defined, problem with batch system!"
    echo "ERROR: Exiting..."
    exit 1
fi
if [ $WORKDIR = $HOME ]; then
    echo "ERROR: WORKDIR is defined to be your homedir"
    echo "ERROR: This means there is a problem with setting WORKDIR!"
    echo "ERROR: Exiting..."
    exit 1
fi

# Go to working directory on executing machine
cd $WORKDIR

# personal scripts below

# copy working area 
cp -r MYWORKDIR .

# copy needed root files
cp ROOTFILE .

# compile and run wz_epmcs
cd epmcs/wz_epmcs/src
setup D0RunII p17.05.01
gmake clean
gmake all

ls ../../tupleMaker/*.root > filelist.txt
./run_pmcs -f filelist.txt -c PARAMETERSFILE -t 1

# save the results
cp result_wen.root COPIEDFILE
