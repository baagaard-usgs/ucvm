#!/bin/bash
## 
## example of running on usc/hpc cluster
##

if [ -z "$UCVM_INSTALL_PATH" ]; then
  echo "Need to set UCVM_INSTALL_PATH to run >" ${0##*/} 
  exit
fi
source $UCVM_INSTALL_PATH/conf/ucvm_env.sh

BIN_DIR=${UCVM_INSTALL_PATH}/bin
CONF_DIR=${UCVM_INSTALL_PATH}/conf
TEST=basin_query_mpi_cencal_cvmsi

expect=$(mktemp) || exit 1
result=$(mktemp) || (trap 'rm -f "$expect"'; exit 1)

salloc -Q --ntasks=2 --time=00:10:00 srun -Q --ntasks=2 -o ${TEST}.srun.out ${BIN_DIR}/basin_query_mpi -b ${TEST}.simple -f ${CONF_DIR}/ucvm.conf -m cencal,cvmsi -i 20 -v 2500 -l 35.0,-122.5 -s 0.1 -x 16 -y 11

od ${TEST}.simple > $result 2>&1

cat > $expect << EOF_EXPECTED_RESULT
0000000 000000 137600 000000 137600 000000 137600 000000 137600
*
0000060 000000 000000 000000 000000 000000 000000 000000 000000
0000100 000000 137600 000000 137600 000000 137600 000000 137600
0000120 000000 137600 000000 042141 000000 042141 000000 042141
0000140 000000 137600 000000 137600 000000 137600 000000 000000
0000160 000000 000000 000000 000000 000000 000000 000000 000000
0000200 000000 137600 000000 137600 000000 137600 000000 137600
0000220 000000 137600 000000 042141 000000 042141 000000 042141
0000240 000000 042141 000000 137600 000000 000000 000000 000000
0000260 000000 000000 000000 000000 000000 000000 000000 000000
0000300 000000 137600 000000 137600 000000 137600 000000 137600
0000320 000000 042141 000000 042141 000000 042141 000000 042141
0000340 000000 042141 000000 042141 000000 042141 000000 000000
0000360 000000 000000 000000 000000 000000 000000 000000 000000
0000400 000000 137600 000000 137600 000000 137600 000000 042110
0000420 000000 042141 000000 042141 000000 042141 000000 042141
*
0000460 000000 042141 000000 000000 000000 000000 000000 000000
0000500 000000 137600 000000 137600 000000 042141 000000 042141
0000520 000000 042141 000000 042141 000000 042141 000000 042141
*
0000560 000000 042141 000000 042141 000000 042141 000000 000000
0000600 000000 137600 000000 042141 000000 042141 000000 042141
0000620 000000 042141 000000 042141 000000 042110 000000 042141
0000640 000000 042141 000000 042141 000000 042141 000000 042141
0000660 000000 042141 000000 042141 000000 042057 000000 042057
0000700 000000 042141 000000 042141 000000 042141 000000 042141
0000720 000000 042110 000000 042141 000000 042141 000000 042141
0000740 000000 042141 000000 042141 000000 042141 000000 042141
0000760 000000 042057 000000 042057 000000 042057 000000 042057
0001000 000000 042141 000000 042141 000000 042141 000000 042141
*
0001040 000000 042141 000000 042141 000000 042141 000000 042057
0001060 000000 042057 000000 042057 000000 042057 000000 042057
0001100 000000 042141 000000 042141 000000 042141 000000 042141
*
0001140 000000 042141 000000 042141 000000 042141 000000 042057
0001160 000000 042057 000000 042057 000000 042057 000000 042057
0001200 000000 042141 000000 042141 000000 042141 000000 042141
*
0001240 000000 042141 000000 042057 000000 042057 000000 042057
0001260 000000 042057 000000 042057 000000 042057 000000 042110
0001300
EOF_EXPECTED_RESULT

echo "Running examples_programs_basin basin_query_mpi_cencal_cvmsi"
if diff $result $expect > /dev/null 2>&1
then
  echo [SUCCESS]
else
  echo [FAILURE]
fi
                               
trap 'rm -f "$expect" "$result"' exit



