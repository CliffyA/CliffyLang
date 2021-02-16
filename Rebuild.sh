#!/bin/bash
set -x
cd Source
php "CliffyC.php" "linux_gmake"
cd ProjectGen
cd linux_gmake
make config=debug64 clean
make config=debug64
cd ..
cd ..
cd ..
