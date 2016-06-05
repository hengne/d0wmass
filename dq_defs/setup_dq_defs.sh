# Must cd to this directory and then source this.

export DQ_DEFS_DIR=`/bin/pwd`
bindir=${DQ_DEFS_DIR}/scripts

export PATH=${bindir}:`dropit -e ${bindir} PATH`
unset bindir
