#!/bin/bash
WORK_PATH=$(cd $(dirname $0); pwd)
echo "WORK_PATH: ${WORK_PATH}"

cd ${WORK_PATH}/hmi_sim
mkdir build
cd build
cmake ..
make -j4
${WORK_PATH}/hmi_sim/bin/main


