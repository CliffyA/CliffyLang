#!/bin/bash
set -x

build="debugx64"

if [ $(uname -m) = "aarch64" ];
then
	build="debuga64"
fi

cd Source
php "CliffyC.php" "linux_gmake"
php "CliffyC.php" "cmake"
cd ProjectGen
cd linux_gmake
make config=${build}
cd ..
cd ..
cd ..
