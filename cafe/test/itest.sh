#!/bin/sh

# This is the ctest default script for running integrated tests.
# It is run from the directory where the component test is
# located.  This is a writeable directory.
#
# This file should be POSIX compliant.
#

# Exit with error if two arguments are not present.
if [ $# -lt 2 ]; then
  echo Usage: $0 component_name source_dir
  exit 1;
fi

# First argument is the component name.
CNAME=$1

# Second argument is the source directory.
SRCDIR=$2

# Third argument is the current installation directory.
# If package pkg is installed locally, its top level directory
# is $TOPDIR/pkg.
# The script ctpkgpath will return that directory if it exists
# or, if not, will return the release package directory.
TOPDIR=$3
shift 2
TOPPATH=$*

##############################################################
#
# Commands to be run before the component test.
#

# Link the data file for testing
ln -sf $SRCDIR/run2b_data.root run2b_data.root
ln -sf $SRCDIR/run2a_data.root run2a_data.root
ln -sf $SRCDIR/run2b_mc.root run2b_mc.root
ln -sf $SRCDIR/run2a_mc.root run2a_mc.root

##############################################################

if [ x$LINK_SHARED = x ]; then
  echo "No shared linking -- test can not run."
  exit 0
fi

# Run the component test.

./itest
STAT=$?
echo Component test returned status $STAT

# Return immediately if test failed
if [ $STAT -ne 0 ]; then
  exit $STAT
fi 

##############################################################
#
# Commands to be run after the component test.
# Set STAT nonzero or return nonzero for errors.
#

##############################################################
#

# Display and return the component return status.
exit $STAT
