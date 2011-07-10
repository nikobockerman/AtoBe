#!/bin/sh

# A script to fetch GMock from source repository, compile it and run the tests.

PRE_WD=`pwd`

# Go to correct directory
cd `dirname $0`

# Get gmock from svn
echo "Fetching GMock source from http://googlemock.googlecode.com"
svn checkout http://googlemock.googlecode.com/svn/trunk/ gmock

cd gmock
echo "Running autoreconf..."
AUTOMAKE=automake-1.9 ACLOCAL=aclocal-1.9 autoreconf -f -v -i

mkdir build
cd build

echo "Running configure..."
../configure

echo "Running make..."
make -j3
echo "Running make check..."
make check

echo "All done"
# Go back to original directory
cd $PRE_WD
