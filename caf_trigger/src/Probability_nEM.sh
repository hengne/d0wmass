#!/bin/sh

# This is the ctest default script for running integrated tests.
# It is run from the directory where the component test is
# located.  This is a writeable directory.
#
# This file should be POSIX compliant.
#
# D. Adams 14dec98

# First argument is the executable name.
EXE=$1

# Second argument is the source directory.
SRCDIR=$2

# Third argument is the current installation directory.
# If package pkg is installed locally, its top level directory
# is $TOPDIR/pkg.
TOPDIR=$3

# Arguments 3-N specify the search path for packages.
# It consists of directory names separated by spaces.
# The script ctpkgpath will return the first directory in
# which the package is found.
# or, if not, will return the release package directory.
shift 2
TOPPATH="$* $BFDIST/releases/$BFCURRENT"

echo "test.TriggerVersions: 15.00" > cafe.config

# Run the component test.
# Add arguments if needed.
$EXE
STAT=$?
echo Component test returned status $STAT

exit $STAT
