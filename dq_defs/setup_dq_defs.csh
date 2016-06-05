# Must cd to this directory and then source this.

setenv DQ_DEFS_DIR `/bin/pwd`
set bindir=${DQ_DEFS_DIR}/scripts

setenv PATH ${bindir}:`dropit -e ${bindir} PATH`
unset bindir
