#!/bin/bash
WORK_PATH=$(cd $(dirname $0); pwd)
echo "WORK_PATH: ${WORK_PATH}"

cd ${WORK_PATH}/hmi
idf.py --preview set-target esp32c3
cp sdkconfig.defaults.esp32c3 sdkconfig
idf.py -p /dev/ttyUSB0 build flash monitor



