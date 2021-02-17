#!/bin/bash
set -x

build="debugx64"

if [ $(uname -m) = "aarch64" ];
then
	build="debuga64"
fi

cd Source
php "CliffyC.php" "linux_gmake"
cd ProjectGen
cd linux_gmake
make config=${build} clean
make config=${build}
cd ..
cd ..
cd ..
